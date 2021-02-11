#ifdef STEAM_APP_ID

#include <fstream>

#include "modio.h"
#include <iostream>
#include <steam_api.h>
#include <isteamuser.h>

#include "c++/schemas/Terms.h"

const char* APPID_PATH = "steam_appid.txt";

void printLink(const modio::Link& link);
void printButton(const modio::Button& button, char keyChar);

/// <summary>
/// Boilerplate class to fetch the encrypted app ticket from steam
/// </summary>
class EncryptedAppTicketFetcher
{
public:
  EncryptedAppTicketFetcher() = delete;
  EncryptedAppTicketFetcher(modio::Instance& instance);
  /// <summary>
  /// Blocking unitl the app ticket is retrieved, returns true on success
  /// </summary>
  bool retrieveEncryptedAppTicket();

  bool getCachedAppTicket(uint8** ticket, uint32& ticket_size);
private:
  void onEncryptedAppTicketResponse(EncryptedAppTicketResponse_t* pEncryptedAppTicketResponse, bool bIOFailure);
  inline bool hasRetrievedTicket() const
  {
    return mState == State::Success || mState == State::Failed;
  }
  CCallResult< EncryptedAppTicketFetcher, EncryptedAppTicketResponse_t > mEncryptedAppTicketResponseCallResult;

  modio::Instance& mInstance;

  enum class State{
    Idle,
    Fetching,
    Success,
    Failed
  };
  State mState = State::Idle;

  enum{ TicketSize = 1024 };

  uint8 mTicket[TicketSize];
  uint32 mTicketSize = -1;
};

class AuthStateMachine
{
public:
  AuthStateMachine(modio::Instance& instance) :
    mInstance(instance),
    mTicketFetcher(instance)
  {
  }

  bool updateStateMachine()
  {
    bool require_further_processing = true;
    bool waiting_for_callback = false;

    switch(mState)
    {
      case AuthState::RetrieveAppTicket:
      {
        // Blocking 
        require_further_processing = mTicketFetcher.retrieveEncryptedAppTicket();
        mState = AuthState::AuthingWithSteam;
        break;
      }
      case AuthState::AuthingWithSteam:
      {
        uint8* ticket = nullptr;
        uint32 ticket_size = 0;

        bool got_terms = false;
        modio::Terms terms_obj;

        if( mTicketFetcher.getCachedAppTicket(&ticket, ticket_size) )
        {
          waiting_for_callback = true;
          
          mInstance.steamAuth(ticket, ticket_size, mHasGivenConsent, [this, &waiting_for_callback](const modio::Response& response)
          {
            mResponse = response;
            waiting_for_callback = false;

            mState = AuthState::ProcessingSteamAuth;
          });
        }
        break;
      }
      case AuthState::ProcessingSteamAuth:
      {
        if(mResponse.code == 200)
        {
          // Successfully authed
          mRunWithoutAccount = false;
          require_further_processing = false;
          std::cout << "Successfully authed with steam" << std::endl;
          break;
        }
        else if(mResponse.error.error_ref == 11051)
        {
          waiting_for_callback = true;
          mInstance.getTerms(MODIO_SERVICE_STEAM, [this, &waiting_for_callback](const modio::Response& response, const modio::Terms& terms)
            {
              mResponse = response;
              mTerms = terms;
              
              waiting_for_callback = false;
              mState = AuthState::ShowTerms;
            });
        }
        else
        {
          printError(mResponse, "ProcessingSteamAuth");
          require_further_processing = false;
        }
        break;  
      }
      case AuthState::ShowTerms:
      {
        if(mResponse.code != 200)
        {
          printError(mResponse, "ShowTerms");
          require_further_processing = false;
          break;
        }

        std::cout << mTerms.plaintext << std::endl;
        printLink(mTerms.manage);
        printLink(mTerms.privacy);
        printLink(mTerms.terms);
        printLink(mTerms.website);
        printButton(mTerms.agree, 'Y');
        printButton(mTerms.disagree, 'N');

        while (int character = std::cin.get())
        {
          if (character == 'Y' || character == 'y')
          {
            mState = AuthState::AuthingWithSteam;
            mHasGivenConsent = true;
            require_further_processing = true;
            break;
          }
          if (character == 'N' || character == 'n')
          {
            std::cout << "Sorry, we can't sign in with steam without you giving mod.io consent to process your data." << std::endl;
            require_further_processing = false;
            break;
          }
        }
      }
    }

    while (waiting_for_callback)
    {
      mInstance.sleep(10);
      mInstance.process();
      SteamAPI_RunCallbacks();
    }

    return require_further_processing;
  }

  bool runNotLoggedIn() const
  {
    return mRunWithoutAccount;
  }
private:
  void printError(const modio::Response& response, const std::string& state) const
  {
    std::cout << "Error received in state: " << state << std::endl;
    std::cout << "Got HTTP code: " << mResponse.code << " and mod.io error code: " << mResponse.error.error_ref << std::endl;
    std::cout << mResponse.error.message << std::endl;
  }
  enum class AuthState
  {
    RetrieveAppTicket,
    AuthingWithSteam,
    ProcessingSteamAuth,
    ShowTerms
  } mState = AuthState::RetrieveAppTicket;

  modio::Instance& mInstance;
  EncryptedAppTicketFetcher mTicketFetcher;
  modio::Response mResponse;
  modio::Terms mTerms;
  bool mHasGivenConsent = false;
  bool mRunWithoutAccount = true;
};

int main()
{

  // Boilerplate code just to ensure that you can setup the APPID through CMAKE to test the steam auth
  std::ofstream appid_file(APPID_PATH, std::ios_base::out | std::ios_base::trunc);
  appid_file << STEAM_APP_ID;
  appid_file.close();

  // Ensure that you have updated environment, game_id and api_key. Also, ensure that you have set API Authentication via Steam field in your games option
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  bool steam_init_result = SteamAPI_Init();
  assert(steam_init_result && "Failed to initialize steam. Ensure that STEAMWORKS_APP_ID is properly set and that you have proper access to the app id");

  // Remove the lingering APPID textfile
  std::remove(APPID_PATH);

  AuthStateMachine state_machine(modio_instance);
  bool work_pending = false;
  do
  {
    work_pending = state_machine.updateStateMachine();

  } while(work_pending);

  if(state_machine.runNotLoggedIn())
  {
    std::cout << "Running the game without any logged in mod.io account" << std::endl;
  }

  SteamAPI_Shutdown();

  std::cout << "Process finished" << std::endl;
  return 0;
}

EncryptedAppTicketFetcher::EncryptedAppTicketFetcher(modio::Instance& instance) :
  mInstance(instance)
{
}

bool EncryptedAppTicketFetcher::retrieveEncryptedAppTicket()
{
  mState = State::Fetching;

  static const char* k_unSecretData = "k_unSecretData";
  SteamAPICall_t hSteamAPICall = SteamUser()->RequestEncryptedAppTicket(&k_unSecretData, sizeof(k_unSecretData));
  mEncryptedAppTicketResponseCallResult.Set(hSteamAPICall, this, &EncryptedAppTicketFetcher::onEncryptedAppTicketResponse);

  while (!hasRetrievedTicket())
  {
    mInstance.sleep(10);
    mInstance.process();
    SteamAPI_RunCallbacks();
  }

  return mState == State::Success;
}

bool EncryptedAppTicketFetcher::getCachedAppTicket(uint8** ticket, uint32& ticket_size)
{
  if(mState == State::Success)
  {
    *ticket = mTicket;
    ticket_size = mTicketSize;
    return true;
  }

  return false;
}


void EncryptedAppTicketFetcher::onEncryptedAppTicketResponse(EncryptedAppTicketResponse_t* pEncryptedAppTicketResponse, bool bIOFailure)
{
  // State defaults to failed
  mState = State::Failed;

  if (bIOFailure)
  {
    printf("There has been an IO Failure when requesting the Encrypted App Ticket.\n");
    return;
  }

  switch (pEncryptedAppTicketResponse->m_eResult)
  {
  case k_EResultOK:
  {
    if (SteamUser()->GetEncryptedAppTicket(mTicket, sizeof(mTicket), &mTicketSize))
    {
      mState = State::Success;
    }
    else
    {
      printf("GetEncryptedAppTicket failed.\n");
    }
  }
  break;
  case k_EResultNoConnection:
    printf("Calling RequestEncryptedAppTicket while not connected to steam results in this error.\n");
    break;
  case k_EResultDuplicateRequest:
    printf("Calling RequestEncryptedAppTicket while there is already a pending request results in this error.\n");
    break;
  case k_EResultLimitExceeded:
    printf("Calling RequestEncryptedAppTicket more than once per minute returns this error.\n");
    break;
  }
}

void printLink(const modio::Link& link)
{
  if (link.required)
  {
    std::cout << "Visit " << link.text << " on " << link.url << std::endl;
  }
}

void printButton(const modio::Button& button, char keyChar)
{
  std::cout << "[" << keyChar << "] " << button.text << std::endl;
}

#else
#include "modio.h"
#include <iostream>

int main()
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();
    }
  };

  auto finish = [&]() {
    finished = true;
  };

  // Auth works by providing the Appdata param given by the Galaxy SDK
  const unsigned char* rgubTicket = NULL;
  u32 cubTicket = 0;
  modio_instance.steamAuth(rgubTicket, cubTicket, false, [&](const modio::Response& response) {
    std::cout << "Response code: " << response.code << std::endl;

    if (response.code == 200)
      std::cout << "Please enter the 5 digit security code: ";
    else
      std::cout << "Error sending code" << std::endl;

    finish();
    });

  wait();

  std::cout << "Process finished" << std::endl;
  return 0;
}
#endif
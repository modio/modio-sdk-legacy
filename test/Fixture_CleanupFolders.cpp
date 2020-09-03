#include "Fixture_CleanupFolders.h"
#include "c/ModioC.h"
#include "../src/WindowsFilesystem.h"

#if defined(MODIO_WINDOWS_DETECTED)
#include <aclapi.h>
#include <sddl.h>
#endif

std::vector<std::string> Fixture_CleanupFolders::allowedFolders = { ".cmake", "bin", "CMakeFiles", "ext", "lib", "Testing", "kaka" };

void Fixture_CleanupFolders::DeleteTransientDirectories()
{
  for (auto& it : ghc::filesystem::directory_iterator(ghc::filesystem::current_path()))
  {
    std::vector<ghc::filesystem::path> toDelete;
    if (it.is_directory() && !isAllowedDirectory(it.path()))
    {
      toDelete.push_back(it.path());
    }
    for (auto& path : toDelete)
    {
      setFilePermission(path.generic_u8string(), true);
      ghc::filesystem::remove_all(path);
    }
  }
}

void Fixture_CleanupFolders::setFilePermission(std::string fileName, bool access)
{
#if defined(MODIO_WINDOWS_DETECTED)
  PSID pEveryoneSID = NULL;
  PACL pACL = NULL;
  EXPLICIT_ACCESS ea[1];
  SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;

  // Create a well-known SID for the Everyone group.
  AllocateAndInitializeSid(&SIDAuthWorld, 1,
    SECURITY_WORLD_RID,
    0, 0, 0, 0, 0, 0, 0,
    &pEveryoneSID);

  // Initialize an EXPLICIT_ACCESS structure for an ACE.
  ZeroMemory(&ea, 1 * sizeof(EXPLICIT_ACCESS));
  ea[0].grfAccessPermissions = 0xFFFFFFFF;
  ea[0].grfAccessMode = access ? GRANT_ACCESS : DENY_ACCESS;
  ea[0].grfInheritance = NO_INHERITANCE;
  ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
  ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
  ea[0].Trustee.ptstrName = (LPTSTR)pEveryoneSID;

  // Create a new ACL that contains the new ACEs.
  SetEntriesInAcl(1, ea, NULL, &pACL);

  // Initialize a security descriptor.  
  PSECURITY_DESCRIPTOR pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR,
    SECURITY_DESCRIPTOR_MIN_LENGTH);

  InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION);

  // Add the ACL to the security descriptor. 
  SetSecurityDescriptorDacl(pSD,
    TRUE,     // bDaclPresent flag   
    pACL,
    FALSE);   // not a default DACL 


  //Change the security attributes
  SetFileSecurity(modio::windows_platform::utf8ToWstr(fileName).c_str(), DACL_SECURITY_INFORMATION, pSD);

  if (pEveryoneSID)
    FreeSid(pEveryoneSID);
  if (pACL)
    LocalFree(pACL);
  if (pSD)
    LocalFree(pSD);
#else
  std::error_code ec; 
  ghc::filesystem::permissions(fileName.c_str(), access ? ghc::filesystem::perms::all : ghc::filesystem::perms::none, ec);
#endif
}

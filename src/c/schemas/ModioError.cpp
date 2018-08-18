#include "c/schemas/ModioError.h"

extern "C"
{
  void modioInitError(ModioError* error, nlohmann::json error_json)
  {
    error->code = -1;
    if(modio::hasKey(error_json, "code"))
      error->code = error_json["code"];

    error->message = NULL;
    if(modio::hasKey(error_json, "message"))
    {
      std::string message_str = error_json["message"];
      error->message = new char[message_str.size() + 1];
      strcpy(error->message, message_str.c_str());
    }

    error->errors_array = NULL;
    error->errors_array_size = 0;
    if(modio::hasKey(error_json, "errors"))
    {
      nlohmann::json errors_json = error_json["errors"];
      error->errors_array_size = (u32)errors_json.size();
      error->errors_array = new char*[error->errors_array_size];

      int i = 0;
      for(auto it=errors_json.begin(); it!=errors_json.end(); it++)
      {

        std::string errors_str = it.key();// + ": " + std::string(i.value());
        errors_str += ": ";
        std::string error_value = it.value();
        errors_str += error_value;
        error->errors_array[i]= new char[errors_str.size() + 1];
        strcpy(error->errors_array[i], errors_str.c_str());
        i++;
      }
    }
  }

  void modioFreeError(ModioError* error)
  {
    if(error)
    {
      if(error->message)
        delete[] error->message;

      if(error->errors_array)
      {
        for(u32 i=0; i<error->errors_array_size; i++)
        {
          delete[] error->errors_array[i];
        }
      }
    }
  }
}

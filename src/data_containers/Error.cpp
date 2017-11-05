#include "data_containers/Error.h"

extern "C"
{
  void modioInitError(ModioError* error, json error_json)
  {
    error->code = -1;
    if(modio::hasKey(error_json, "code"))
      error->code = error_json["code"];

    error->message = NULL;
    if(modio::hasKey(error_json, "message"))
    {
      string message_str = error_json["message"];
      error->message = new char[message_str.size() + 1];
      strcpy(error->message, message_str.c_str());
    }

    error->errors_array = NULL;
    error->errors_array_size = 0;
    if(modio::hasKey(error_json, "errors"))
    {
      json errors_json = error_json["errors"];
      error->errors_array_size = errors_json.size();
      error->errors_array = new char*[error->errors_array_size];

      int i = 0;
      for(auto it=errors_json.begin(); it!=errors_json.end(); it++)
      {

        string errors_str = it.key();// + ": " + string(i.value());
        errors_str += ": ";
        //errors_str += string(it.value());
        error->errors_array[i]= new char[errors_str.size() + 1];
        strcpy(error->errors_array[i], errors_str.c_str());
        i++;
      }
    }
  }

  void modioFreeError(ModioError* error)
  {
    delete error;
  }
}

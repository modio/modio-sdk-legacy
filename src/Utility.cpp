#include "Utility.h"

namespace modworks
{
  string dataToJsonString(char* data, size_t size)
  {
    int brackets = 0;
    string response;
    for(int i=0; i<(int)size; i++)
    {
      if(data[i]=='{')
        brackets++;

      if(brackets>0)
      {
        response+=data[i];
      }

      if(data[i]=='}')
        brackets--;
    }
    return response;
  }

  string toString(int number)
  {
      if (number == 0)
          return "0";

      if(number < 0)
          return "-"+toString(-number);

      std::string temp="";
      std::string returnvalue="";
      while (number>0)
      {
          temp+=number%10+48;
          number/=10;
      }
      for (int i=0;i<(int)temp.length();i++)
          returnvalue+=temp[temp.length()-i-1];
      return returnvalue;
  }

  void createDirectory(string directory)
  {
    #ifdef LINUX
      mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif

    #ifdef WINDOWS
      CreateDirectory(directory.c_str() ,NULL);
    #endif
  }

  bool writeLogLine(string text)
  {
    ofstream log_file(".modworks/log", ios::app);
    log_file<<text<<"\n";
    log_file.close();
    return true;
  }
}

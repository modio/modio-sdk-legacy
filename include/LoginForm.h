#include "Utility.h"

#ifdef LINUX
#include <gtk/gtk.h>
#endif

#ifdef WINDOWS
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <windows.h>
#endif

#include <iostream>
#include <functional>
#include <thread>

using namespace std;

#ifdef LINUX
struct LoginParams
{
  GtkWidget* email_input;
  GtkWidget* password_input;
  function< void(int result) > callback;
  GtkWidget *window;
};

void onLoginButtonPressed(GtkWidget *widget, gpointer data);
void activate(GtkApplication *app, gpointer user_data);
void loginFormThread(function< void(int result) > callback);
#endif

void showLoginForm(function< void(int result) > callback);

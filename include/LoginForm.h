#include <gtk/gtk.h>
#include <iostream>
#include <functional>
#include <thread>

using namespace std;

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
void showLoginForm(function< void(int result) > callback);

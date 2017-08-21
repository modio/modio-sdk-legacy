#include "LoginForm.h"

void onLoginButtonPressed(GtkWidget *widget, gpointer data)
{
  LoginParams* login_params = (LoginParams*)data;

  const gchar *gchar_email;
  gchar_email = gtk_entry_get_text(GTK_ENTRY(login_params->email_input));

  const gchar *gchar_password;
  gchar_password = gtk_entry_get_text(GTK_ENTRY(login_params->password_input));

  string email = gchar_email;
  string password = gchar_password;

  gtk_widget_hide(login_params->window);

  //TODO: Login to Modworks

  login_params->callback(1);
  delete login_params;
}

void activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title(GTK_WINDOW (window), "Modworks Login");
  gtk_window_set_default_size(GTK_WINDOW (window), 300, 200);

  button_box = gtk_grid_new();
  gtk_container_add (GTK_CONTAINER(window), button_box);

  GtkWidget *email_input = gtk_entry_new();
  gtk_container_add(GTK_CONTAINER(button_box), email_input);

  GtkWidget *password_input = gtk_entry_new ();
  gtk_container_add(GTK_CONTAINER (button_box), password_input);
  gtk_entry_set_visibility((GtkEntry*)password_input, false);

  LoginParams* login_params = (LoginParams*)user_data;
  login_params->email_input = email_input;
  login_params->password_input = password_input;
  login_params->window = window;

  button = gtk_button_new_with_label("Login");
  g_signal_connect(button, "clicked", G_CALLBACK (onLoginButtonPressed), login_params);
  //g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_hide), window);
  gtk_container_add(GTK_CONTAINER (button_box), button);

  gtk_widget_show_all(window);
}

void loginFormThread(function< void(int result) > callback)
{
  GtkApplication *app;
  int status;

  LoginParams* login_params = new LoginParams;
  login_params->callback = callback;

  app = gtk_application_new ("modworks.sdk.login", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), login_params);
  status = g_application_run (G_APPLICATION (app), 0, 0);
  g_object_unref (app);
}

void showLoginForm(function< void(int result) > callback)
{
  std::thread show_login_form_thread(loginFormThread, callback);
  show_login_form_thread.detach();
}

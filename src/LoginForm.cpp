#include "LoginForm.h"

#ifdef LINUX
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
#endif

#define WINDOWS

#ifdef WINDOWS
HWND email_entry, password_entry, login_button, close_button;
LRESULT CALLBACK windowProcedureCallback(HWND, UINT, WPARAM, LPARAM);
function< void(int result) > callback;

void loginFormThread(function< void(int result) > callback_param)
{
	callback = callback_param;
    WNDCLASSEX wincl;
    wincl.hInstance = GetModuleHandle(NULL);
    wincl.lpszClassName = "modworks.sdk.login";
    wincl.lpfnWndProc = windowProcedureCallback;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if(!RegisterClassEx (&wincl))
        return;

    HWND hwnd = CreateWindowEx(
           0,
           "modworks.sdk.login",
           "Modworks Login", /* title */
           WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT, CW_USEDEFAULT, /* position on the screen */
           240, 140, /* width, height */
           HWND_DESKTOP,
           NULL,
           GetModuleHandle(NULL),
           NULL
           );

    ShowWindow(hwnd, 10);

	MSG messages;
    while(GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
}

LRESULT CALLBACK windowProcedureCallback(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == WM_CREATE)
	{
		email_entry = CreateWindow("EDIT","", WS_VISIBLE | WS_BORDER | WS_CHILD, 10, 10, 200, 20, hwnd, (HMENU) 1, NULL, NULL);
		password_entry = CreateWindow("EDIT","",WS_VISIBLE | WS_BORDER | WS_CHILD | ES_PASSWORD, 10, 40, 200, 20, hwnd, (HMENU) 2, NULL, NULL);
		login_button = CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_BORDER | WS_CHILD, 10, 70, 70, 20, hwnd, (HMENU) 3, NULL, NULL);
		close_button = CreateWindow("BUTTON", "Close", WS_VISIBLE | WS_BORDER | WS_CHILD, 140, 70, 70, 20, hwnd, (HMENU) 4, NULL, NULL);
	}
	else if(message == WM_COMMAND)
	{
		if(LOWORD(wParam) == 3)
		{
			int email_lenght = GetWindowTextLength(email_entry) + 1;
			char* email_char = new char[email_lenght];
			GetWindowText(email_entry, &email_char[0], email_lenght);
			
			int password_lenght = GetWindowTextLength(password_entry) + 1;
			char* password_char = new char[password_lenght];
			GetWindowText(password_entry, &password_char[0], password_lenght);
			
			string email = email_char;
			string password = password_char;

			cout<<"Email: "<<email<<endl;
			cout<<"Password: "<<password<<endl;
			
			callback(1);
			
			delete[] email_char;
			delete[] password_char;
		}
		
		if(LOWORD(wParam) == 4)
		{
			PostQuitMessage(0);
		}
	}
	else if(message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	else
	{
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

    return 0;
}
#endif

void showLoginForm(function< void(int result) > callback)
{
  std::thread show_login_form_thread(loginFormThread, callback);
  show_login_form_thread.detach();
}

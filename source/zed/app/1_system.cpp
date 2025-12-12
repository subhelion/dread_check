#include "1_system/files.cpp"
#include "1_system/profiler.cpp"

#include <zed.h>
#include <zed/app.h>
#include <zed/platform/windows.h>

#include <dwmapi.h>
#pragma comment( lib, "dwmapi.lib" )

#define l_param_get_x( lp ) ( (int)(short)LOWORD( lp ) )
#define l_param_get_y( lp ) ( (int)(short)HIWORD( lp ) )

void app_system_step() {
	WaitForSingleObjectEx( app.graphics.waitable, INFINITE, true );

	MSG msg;

	while ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) ) {
		if ( msg.message == WM_QUIT ) { app.quit = true; break; }
		TranslateMessage( &msg );
		DispatchMessage ( &msg );
	}
}

void app_system_size() {
	RECT client_rectangle;
	GetClientRect( (HWND)app.system.window, &client_rectangle );

	app.graphics.display_size.x = client_rectangle.right  - client_rectangle.left;
	app.graphics.display_size.y = client_rectangle.bottom - client_rectangle.top;

	app.size = true;
}

void app_system_dpi() {
	app.system.device_dpi = GetDpiForWindow( (HWND)app.system.window );
}

// window

// float windowBorder = 1.0;

// user
void main_on_system_event( app_system_event );

//
void app_input_on_system_event_for_mouse   ( app_system_event event );
void app_input_on_system_event_for_keyboard( app_system_event event );

LRESULT CALLBACK app_window_procedure( HWND window, UINT message, WPARAM w_param, LPARAM l_param ) {
	switch ( message ) {
		// todo Clipboard Messages
		// todo Clipboard Notifications
		// todo Common Dialog Box Notifications
		// todo Cursor Notifications
		// todo Data Copy Message
		// todo Desktop Window Manager Messages

		// device

		case WM_DEVICECHANGE: {
			// todo

			break;
		}

		case WM_DPICHANGED: {
			app_system_dpi();

			break;
		}

		// todo Dialog Box Notifications
		// todo Dynamic Data Exchange Messages
		// todo Dynamic Data Exchange Notifications
		// todo Hook Notifications
		// todo Keyboard Accelerator Messages
		// todo Keyboard Accelerator Notifications
		// todo Keyboard Input Messages

		// keyboard

		case WM_KEYDOWN:
		case WM_KEYUP: {
			app_system_event event = { window, message, w_param, l_param };
			app_input_on_system_event_for_keyboard( event );
			return 0;
		}

		// case WM_ACTIVATE:
		// case WM_APPCOMMAND:
		// case WM_CHAR:
		// case WM_DEADCHAR:
		// case WM_HOTKEY:
		// case WM_KILLFOCUS:
		// case WM_SETFOCUS:
		// case WM_SYSDEADCHAR:
		// case WM_SYSKEYDOWN:
		// case WM_SYSKEYUP:
		// case WM_UNICHAR:

		// todo Menu Notifications

		// mouse

		case WM_MOUSEACTIVATE:
		case WM_MOUSEHOVER:
		case WM_MOUSEHWHEEL:
		case WM_MOUSELEAVE:
		case WM_MOUSEMOVE:
		case WM_MOUSEWHEEL: {
			app_system_event event = { window, message, w_param, l_param };
			main_on_system_event( event );
			return 0;
		}

		case WM_LBUTTONDBLCLK:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_XBUTTONDBLCLK:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP: {
			app_system_event event = { window, message, w_param, l_param };
			app_input_on_system_event_for_keyboard( event );
			main_on_system_event( event );
			return 0;
		}

		// todo Multiple Document Interface Messages

		// raw input

		case WM_INPUT: {
			app_system_event event = { window, message, w_param, l_param };
			app_input_on_system_event_for_mouse( event );
			return 0;
		}

		// todo Scroll Bar Notifications
		// todo Timer Notifications
		// todo Window Messages

		// window

		case WM_ACTIVATEAPP: {
			if ( (bool)w_param == true ) {
				app.system.idle = false;
				// app_hide_cursor();
			} else {
				app.system.idle = true;
				// zed_show_cursor();
			}

			break;
		}

		// case WM_CANCELMODE:
		// case WM_CHILDACTIVATE:

		// case WM_COMPACTING:
		// case WM_CREATE:

		case WM_CLOSE: {
			return 0;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}

		// case WM_ENABLE:
		// case WM_GETICON:
		// case WM_INPUTLANGCHANGE:
		// case WM_INPUTLANGCHANGEREQUEST:
		// case WM_NCACTIVATE:

		// todo

		case WM_NCHITTEST: {
			if ( app.config.window.type != app_window_type_app_borderless ) break;

			//

			LRESULT result;

			POINT point;
			point.x = l_param_get_x( l_param );
			point.y = l_param_get_y( l_param );

			RECT client;
			GetWindowRect( window, &client );

			point.x = point.x - client.left;
			point.y = point.y - client.top;

			int w = client.right - client.left - 1;
			int h = client.bottom - client.top - 1;

			// todo interrogate these crappy rectangle tests
			if ( point.x < 0 || point.y < 0 || point.x > w || point.y > h ) {
				return HTNOWHERE;
			}

			int xx = 1, yy = 1;

			// todo use TOPEXTENDWIDTH etc
			if ( point.x <= 12     ) { xx = 0; }
			if ( point.x >= w - 12 ) { xx = 2; }
			if ( point.y <= 12     ) { yy = 0; }
			if ( point.y >= h - 12 ) { yy = 2; }

			//todo actual caption area
			if ( xx == 1 && yy == 1 ) {
				if ( point.y <= 45 ) {
					if ( point.x >= app.system.device_size.x - 96 ) {
						//closeHover = true;
						return HTCLOSE;
					} else {
						return HTCAPTION;
					}
				}
			}

			LRESULT grid[3][3] = {
				{ HTTOPLEFT,    HTTOP,    HTTOPRIGHT    },
				{ HTLEFT,       HTCLIENT, HTRIGHT       },
				{ HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
			};

			return grid[ yy ][ xx ];
		}

		case WM_NCCALCSIZE: {
			if ( app.config.window.type != app_window_type_app_borderless ) break;
			// if ( (bool)w_param == true ) return 0;
			break;
		}

		// case WM_NCCREATE:
		// case WM_NCDESTROY:
		// case WM_NULL:
		// case WM_QUERYDRAGICON:
		// case WM_QUERYOPEN:
		// case WM_SHOWWINDOW:
		// case WM_STYLECHANGED:
		// case WM_STYLECHANGING:
		// case WM_THEMECHANGED:
		// case WM_USERCHANGED:
		// case WM_WINDOWPOSCHANGED:
		// case WM_WINDOWPOSCHANGING:

		// window moving & sizing

		// case WM_MOVE:
		// case WM_MOVING:

		// case WM_GETMINMAXINFO:

		case WM_ENTERSIZEMOVE: {
			app.system.idle = true;
			break;
		}

		case WM_EXITSIZEMOVE: {
			app.system.idle = false;
			break;
		}

		// todo doesn't minimize
		case WM_SIZE: {
			switch ( w_param ) {
				case SIZE_MAXIMIZED:
				case SIZE_RESTORED: {
					app_system_size();

					// todo is_sizing is never assigned
					if ( app.system.sizing ) {
						// todo re-render held frame, not render a new one
						// app_graphics_draw();
					}

					app.system.idle = false;
					break;
				}

				case SIZE_MINIMIZED: {
					app.system.idle = true;
					break;
				}
			}

			return 0;
		}

		// case WM_SIZING:
	}

	return DefWindowProc( window, message, w_param, l_param );
}

void app_system_window_init() {
	HINSTANCE instance = GetModuleHandle( 0 );

	WNDCLASS window_class      = {};
	window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	window_class.lpfnWndProc   = app_window_procedure;
	window_class.hInstance     = instance;
	window_class.lpszClassName = "app_window_class";
	window_class.hCursor       = LoadCursor( 0, IDC_ARROW );

	RegisterClass( &window_class );

	//

	uint style = 0;

	int width;
	int height;

	switch ( app.config.window.type ) {
		case app_window_type_game: {
			style |= WS_POPUP;

			width  = app.system.device_size.x;
			height = app.system.device_size.y;

			break;
		}

		case app_window_type_app: {
			style |= WS_OVERLAPPEDWINDOW;
			style |= WS_MAXIMIZE;

			width  = GetSystemMetrics( SM_CXMAXIMIZED );
			height = GetSystemMetrics( SM_CYMAXIMIZED );

			break;
		}

		case app_window_type_app_borderless: {
			style |= WS_POPUP;
			style |= WS_BORDER;
			style |= WS_MINIMIZEBOX;
			style |= WS_MAXIMIZEBOX;
			style |= WS_MAXIMIZE;

			// todo without this maximixed becomes fullscreen
			style |= WS_CAPTION;

			width  = GetSystemMetrics( SM_CXMAXIMIZED );
			height = GetSystemMetrics( SM_CYMAXIMIZED );

			break;
		}

		case app_window_type_legacy: {
			style |= WS_OVERLAPPEDWINDOW;

			if ( app.config.window.width ) {
				width  = app.config.window.width;
				height = app.config.window.height;
			} else {
				style |= WS_MAXIMIZE;

				width  = GetSystemMetrics( SM_CXMAXIMIZED );
				height = GetSystemMetrics( SM_CYMAXIMIZED );
			}

			break;
		}
	}

	// style = style | WS_VISIBLE;

	app.system.window = CreateWindowEx(
		0,
		window_class.lpszClassName,
		app.config.title,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		0,
		0,
		instance,
		0
	);

	if ( app.config.window.type == app_window_type_app_borderless ) {
		MARGINS margins = { 0, 0, 0, 1 };
		DwmExtendFrameIntoClientArea( (HWND)app.system.window, &margins );
		SetWindowPos( (HWND)app.system.window, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED );
	}
}

//

void app_system_init_before() {
	app.system.device_size.x = GetSystemMetrics( SM_CXSCREEN );
	app.system.device_size.y = GetSystemMetrics( SM_CYSCREEN );
}

void app_system_init() {
	app_system_window_init();
	app_system_size();
	app_system_dpi();

	//

	app_system_files_init();
	app_system_profiler_init();

	//

	DWORD length = array_count( app.user );
	GetUserName( app.user, &length );
}

void app_system_init_after() {
	if ( app.options.headless ) return;

	ShowWindow( (HWND)app.system.window, SW_SHOW );

	// note
	// app.graphics.swap_chain->SetFullscreenState( true, 0 );

	// confine cursor
	// app_hide_cursor();
}

//
// Created by never on 2018/9/11.
//

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <eh.h>
#include "console.h"
#include "PropsUtils.h"

static bool s_bQuit = false;

BOOL CtrlHandler( DWORD fdwCtrlType )
{
    switch( fdwCtrlType )
    {
        // Handle the CTRL-C signal. 
        case CTRL_C_EVENT:
            printf( "Ctrl-C event\n\n" );
            Beep( 750, 300 );
            s_bQuit = true;
            return( TRUE );

            // CTRL-CLOSE: confirm that the user wants to exit. 
        case CTRL_CLOSE_EVENT:
            Beep( 600, 200 );
            printf( "Ctrl-Close event\n\n" );
            s_bQuit = true;
            return( FALSE );

            // Pass other signals to the next handler. 
        case CTRL_BREAK_EVENT:
            Beep( 900, 200 );
            printf( "Ctrl-Break event\n\n" );
            return FALSE;

        case CTRL_LOGOFF_EVENT:
            Beep( 1000, 200 );
            printf( "Ctrl-Logoff event\n\n" );
            return FALSE;

        case CTRL_SHUTDOWN_EVENT:
            Beep( 750, 500 );
            printf( "Ctrl-Shutdown event\n\n" );
            return FALSE;

        default:
            return FALSE;
    }
}

namespace console
{
    void Init(void)
    {
        SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );

        SetConsoleTitleW(Pogo::PropsUtils::MakeString(L"app.title").data());
    }

    bool isToClose(void)
    {
        if (s_bQuit)
        {
            return true;
        }

        if (_kbhit())
        {
            int ch = _getch();

            if (ch == 'q')
            {
                return true;
            }
        }

        return false;
    }
}

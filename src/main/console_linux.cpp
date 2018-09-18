/******************************************************************************
*file name    : console_linux.cpp
*owner        :
*description  :
*modified     : 4/19/2009 1:54:04 PM
******************************************************************************/

/*
$Author$
$Source$
$RCSfile$
$Date$
$Log$
*/

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/param.h>
#include "vstdlib/icommandline.h"
#include "console.h"
#include "tier0/dbg.h"
#include <execinfo.h>
#include <signal.h>
#include <exception>
#include <iostream>
#include "Exception.h"
#include <sys/stat.h>


using namespace std;

void daemonize(void)
{
	int childpid, fd;

    /* ignore terminal I/O, stop signals */
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    /* fork to put us in the background (whether or not the user specified ''&'' on the command line */
    if ((childpid = fork()) < 0)
    {
		fputs("failed to fork first children", stderr);
		exit(1);
    }
	else if (childpid > 0)
	{
		exit(0); /* terminate parent, continue in child */
	}

	setsid();
      /* lose controlling terminal */
	if ((fd = open("/dev/tty",O_RDWR)) >= 0)
	{
		ioctl(fd,TIOCNOTTY,NULL);
		close(fd);
	}


	/* close any open file descriptors */
	for (int i = 0/*, size = getdtablesize()*/; i < NOFILE; i ++)
	{
		close(i);
	}

	/* set working directory to allow filesystems to be unmounted */

    chdir("/");
	/* clear the inherited umask */
	umask(0);
}

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


class ExceptionTracer
{
public:
	ExceptionTracer()
	{
		void * array[25];
		int nSize = backtrace(array, 25);
		char ** symbols = backtrace_symbols(array, nSize);
		for (int i = 0; i < nSize; i++)
		{
			Msg("%s\n", symbols[i]);
		}
		free(symbols);
	}
};

template <class SignalExceptionClass> class SignalTranslator
{
private:
	class SingleTonTranslator
	{
	public:
		SingleTonTranslator()
		{
			signal(SignalExceptionClass::GetSignalNumber(), SignalHandler);
		}

		static void SignalHandler(int)
		{
			throw SignalExceptionClass();
		}
	};

public:
	SignalTranslator()
	{
		static SingleTonTranslator s_objTranslator;
	}
};

// An example for SIGSEGV
class SegmentationFault : public ExceptionTracer, public std::exception
{
public:
	static int GetSignalNumber() {return SIGSEGV;}
};

SignalTranslator<SegmentationFault> g_objSegmentationFaultTranslator;

// An example for SIGFPE
class FloatingPointException : public ExceptionTracer, public std::exception
{
public:
	static int GetSignalNumber() {return SIGFPE;}
};

SignalTranslator<FloatingPointException> g_objFloatingPointExceptionTranslator;

class ExceptionHandler
{
private:
    class SingleTonHandler
    {
    public:
        SingleTonHandler()
        {
            set_terminate(Handler);
        }

        static void Handler()
        {
            // Exception from construction/destruction of global variables
            try
            {
                // re-throw
                throw;
            }
            catch (SegmentationFault &)
            {
                cout << "SegmentationFault" << endl;
            }
            catch (FloatingPointException &)
            {
                cout << "FloatingPointException" << endl;
            }
            catch (...)
            {
                cout << "Unknown Exception" << endl;
            }

            //if this is a thread performing some core activity
            abort();
            // else if this is a thread used to service requests
            // pthread_exit();
        }
    };

public:
    ExceptionHandler()
    {
        static SingleTonHandler s_objHandler;
    }
};

//ExceptionHandler g_objExceptionHandler;

static bool s_bToClose = false;

static void sig_handler(int sig, siginfo_t *si, void *unused)
{
	Msg("Got signal %d\n", sig);

    if (sig == SIGINT)
    {
        s_bToClose = true;
    }
    else if (sig == SIGTERM)
    {
        s_bToClose = true;
    }
/*    else if (sig == SIGILL)
    {
    	ExceptionTracer tracer;
    }
    else if (sig == SIGSEGV)
    {
    	ExceptionTracer tracer;
    }
*/
}

namespace console
{
	void Init(void)
	{
		try
		{
	//		*((int*)0) = 0;
		}
		catch (SegmentationFault& e)
		{
			Msg("ddddddddddddddddd\n");
		}

        if (CommandLine()->CheckParm("-d"))
        {
            daemonize();
        }

        struct sigaction sa;
        sa.sa_flags = SA_SIGINFO|SA_ONESHOT|SA_NOMASK;
        sigemptyset(&sa.sa_mask);
        sa.sa_sigaction = sig_handler;
        if (sigaction(SIGINT, &sa, NULL) == -1)
        {
            handle_error("sigaction, SIGINT");
        }

        if (sigaction(SIGTERM, &sa, NULL) == -1)
        {
            handle_error("sigaction, SIGTERM");
        }

        signal(SIGALRM, SIG_IGN);
        signal(SIGPIPE, SIG_IGN);

/*      if (sigaction(SIGILL, &sa, NULL) == -1)
        {
            handle_error("sigaction, SIGILL");
        }

        if (sigaction(SIGSEGV, &sa, NULL) == -1)
        {
            handle_error("sigaction, SIGSEGV");
        }
*/
	}

    bool isToClose(void)
    {
        return s_bToClose;
    }
}


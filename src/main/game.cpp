//
// Created by never on 18-9-18.
//



#include "launcher.h"
#include "module.h"
#include "ifilesystem.h"
#include "filesystem.h"
#include "vstdlib/icommandline.h"
#include "PropsUtils.h"
#include "tier0/dbg.h"
#include "PogoCommon.h"
#include "console.h"
#include "game.h"
#include "logsystem.h"

#define SERVER_ROOT "QOOLU_SERVER_ROOT"

#define PIDFILE "main.pid"

static std::string server_root;

void recordpid()
{
    FILE *fp = fopen(PIDFILE, "w");
    if (!fp)
    {
        Error("Could not open file[%s] to write the process id.\n", PIDFILE);
    }

    __pid_t pid = getpid();

    fprintf(fp, "%d", pid);
    fclose(fp);
}

void game_init()
{
#ifdef _LINUX
    char *root = getenv(SERVER_ROOT);

	if (root == NULL)
	{
		Error("%s, Could not find the env param : %s please set the environment param first\n", __FUNCTION__, server_root.data());
	}

	server_root = root;

#endif

    if (!LoadAppSystems())
    {
        Error("%s : Failed to call load app systems\n", __FUNCTION__);
    }

    g_pFileSystem->SetGameDirectory(server_root.data());

    g_pFileSystem->AddSearchPath(server_root.data(), "ROOT_PATH", PATH_ADD_TO_HEAD);

    console::Init();

    if (!logsystem::Instance()->Init(server_root.data()))
    {
        Error("%s : Init logsystem error, exit \n", __FUNCTION__);
    }

    const char *props = CommandLine()->ParmValue("-props", "");

    Msg("Start loading properties : %s\n", props);

    std::wstring wp = Pogo::NarrowToWide(props);

    if (!Pogo::PropsUtils::LoadProperties(wp) || Pogo::PropsUtils::m_spProperties->IsEmpty())
    {
        Error("%s, Failed to load properties from file : %s\n", __FUNCTION__, props);
    }

    if (!Module_Init())
    {
        Error("%s, Init Module Error\n", __FUNCTION__);
    }

    recordpid();

    Msg("All modules inited successfully.\n");
    Msg("=======================================================\n");
}

static void game_run()
{
    int sleep_time = Pogo::PropsUtils::MakeInt(L"sleep.int", 10);

    bool running = true;

    while (running)
    {
        if (Module_Update() == -1)
        {
            running = false;

            continue;
        }

        if (sleep_time > 0)
        {
            Pogo::sleep(sleep_time);
        }

        if (console::isToClose())
        {
            running = false;
        }
    }
}

void game_shutdown()
{
    Msg("=======================================================\n");
    Msg("Application is exiting...\n");

    Module_Shutdown();

    UnloadAppSystems();

    Msg("All modules were unloaded.\n");
    Msg("=======================================================\n");

    unlink(PIDFILE);
}

int game(int argc, char* argv[])
{
    CommandLine()->CreateCmdLine(argc, argv);

    game_init();

    game_run();

    game_shutdown();

    return 0;
}


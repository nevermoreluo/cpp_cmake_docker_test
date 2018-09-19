/******************************************************************************
*file name    : module.cpp
*owner        :
*description  :
*modified     : 2008-6-1 16:09:21
******************************************************************************/

/*
$Author$
$Source$
$RCSfile$
$Date$
$Log$
*/

#include "launcher.h"
#include "module.h"
#include "appframework/iappsystem.h"
#include "imodule.h"
#include "PropsUtils.h"
#include "utlvector.h"

static CUtlVector<IMoudle*> moudle_list;

static bool Internal_Load(const std::wstring& prefix)
{
	std::string dll = Pogo::WideToNarrow(Pogo::PropsUtils::MakeString(prefix + L".dll", L""));

#ifdef __linux__
	size_t f = dll.rfind(".dll");
	if (f != std::string::npos)
	{
		dll.replace(f, 4, ".so");
	}
#endif

	CreateInterfaceFn fn = (CreateInterfaceFn)AddAppSystem(dll.data());

	if (!fn)
	{
		Error("Load dll : (%s) error, this module has not been loaded\n", dll.data());

		return false;
	}

	std::string inter = Pogo::WideToNarrow(Pogo::PropsUtils::MakeString(prefix + L".interface", L""));

	IMoudle *pMoudle = (IMoudle*)fn(inter.data(), NULL);

	if (!pMoudle)
	{
		Warning("Could not get the IAppSystem entry point by the interface name : %s, in the module : %s\n", inter.data(), dll.data());
	}

	bool br = pMoudle->Connect(LauncherFactory);

	if (!br)
	{
		return false;
	}

	int ir = pMoudle->Init(Pogo::PropsUtils::m_spProperties);

	if (ir == INIT_FAILED)
	{
		return false;
	}

	moudle_list.AddToTail(pMoudle);

	return true;
}

bool Module_Init(void)
{
	std::vector<std::wstring> modules = Pogo::PropsUtils::MakeStringVector(L"modules.list");

	for (size_t i = 0; i < modules.size(); i ++)
	{
		Msg("start loading :%s\n", Pogo::WideToNarrow(modules[i]).data());

		bool br = Internal_Load(modules[i]);

		if (!br)
		{
			Msg("Error while loading :%s\n\n", Pogo::WideToNarrow(modules[i]).data());

			return false;
		}

		Msg("finish loading :%s\n\n", Pogo::WideToNarrow(modules[i]).data());
	}

	return true;
}

int Module_Update(void)
{
	for (int i = 0; i < moudle_list.Count(); i ++)
	{
		if (moudle_list[i])
		{
			if (moudle_list[i]->Run() == IMoudle::RUN_RETURN_ERROR)
			{
				return -1;
			}
		}
	}

	return 0;
}

void Module_Shutdown(void)
{
	Msg("Module_Shutdown start.\n");

	while (moudle_list.Count())
	{
        if (moudle_list[0])
        {
            moudle_list[0]->Shutdown();
            moudle_list[0]->Disconnect();
        }

		moudle_list.Remove(0);
	}

	Msg("Module_Shutdown end.\n");
}

/******************************************************************************
*file name    : launcher.cpp
*owner        : Andy
*description  : 
*modified     : 2004/12/11
******************************************************************************/ 

#include "interface.h"
#include "ifilesystem.h"
#include "tier0/dbg.h"
#include "utlvector.h"
#include "launcher.h"

struct module_interface_t
{
	CSysModule *module;
	CreateInterfaceFn fn;
};

static CUtlVector<module_interface_t> module_interface_list;

//-----------------------------------------------------------------------------
// An aggregate class factory encompassing all factories in all loaded DLLs
//-----------------------------------------------------------------------------
void* LauncherFactory(const char *pName, int *pReturnCode)
{
	void *pRetVal = NULL;

	// FIXME: Really, we should just load the DLLs in order
	// and search in the order loaded. This is sort of a half-measure hack
	// to get to where we need to go

	// First ask ourselves
	pRetVal = Sys_GetFactoryThis()( pName, pReturnCode );
	if (pRetVal)
		return pRetVal;

	// First ask the file system...
	pRetVal = GetFileSystemFactory()( pName, pReturnCode );
	if (pRetVal)
		return pRetVal;

	for (int i = 0; i < module_interface_list.Count(); i ++)
	{
		module_interface_t& mi = module_interface_list[i];

		pRetVal = mi.fn( pName, pReturnCode );
		
		if (pRetVal)
		{
			return pRetVal;
		}
	}

	return NULL;
}


//-----------------------------------------------------------------------------
// Loads, unloads major systems
//-----------------------------------------------------------------------------
bool LoadAppSystems( )
{
	// Start up the file system
	FileSystem_LoadFileSystemModule();
	if (!FileSystem_Init())
		return false;

	return true;
}


void UnloadAppSystems()
{
	while (module_interface_list.Count() >= 1)
	{
		int i = module_interface_list.Count() - 1;

		if (module_interface_list[i].module)
		{
			FileSystem_UnloadModule(module_interface_list[i].module);
		}
		
		module_interface_list.Remove(i);
	}

	FileSystem_UnloadFileSystemModule();
}

void* AddAppSystem(const char *dll)
{
	module_interface_t mi = {0};

	mi.module = FileSystem_LoadModule(dll);
		
	if (!mi.module)
	{
		Error( "Unable to load %s\n", dll );
		return NULL;
	}

	mi.fn = Sys_GetFactory(mi.module);
	if (!mi.fn)
	{
		Error( "Unable to get %s factory\n", dll );
		return NULL;
	}

	module_interface_list.AddToTail(mi);

	return (void*)mi.fn;
}

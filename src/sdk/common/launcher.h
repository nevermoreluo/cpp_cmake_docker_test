/******************************************************************************
*file name    : launcher.h
*owner        : Andy
*description  : 
*modified     : 2004/12/11
******************************************************************************/ 

#ifndef ENGINE_LAUNCHER_H
#define ENGINE_LAUNCHER_H

bool LoadAppSystems(void);

void* LauncherFactory(const char *pName, int *pReturnCode);

void* AddAppSystem(const char *dll);

void UnloadAppSystems(void);

#endif

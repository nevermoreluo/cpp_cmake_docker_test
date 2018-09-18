/******************************************************************************
*file name    : module.h
*owner        : 
*description  : 
*modified     : 2008-6-1 16:09:04
******************************************************************************/ 

/*
$Author$
$Source$
$RCSfile$
$Date$
$Log$
*/

#ifndef MODULE_H
#define MODULE_H
#ifdef _WIN32
#pragma once
#endif

bool Module_Init(void);

int Module_Update(void);

void Module_Shutdown(void);


#endif // MODULE_H

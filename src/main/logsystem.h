//
// Created by never on 18-9-18.
//


#ifndef LOGSYSTEM_H_
#define LOGSYSTEM_H_

#include "tier0/dbg.h"
#include <stdio.h>

class logsystem
{
public:
    logsystem();

    virtual ~logsystem();

public:
    bool Init(const char *server_path);

    static logsystem *Instance();

    const char *TimeString();

    void Log(SpewType_t type, char const *msg);

private:
    bool OpenLogFile(const char *server_path);

private:
    FILE *m_fp;
};

#endif /* LOGSYSTEM_H_ */


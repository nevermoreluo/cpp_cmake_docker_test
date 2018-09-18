//
// Created by never on 18-9-18.
//



#include "logsystem.h"
#include <stdio.h>
#include <time.h>
#include "vstdlib/icommandline.h"
#include <string>


static SpewRetval_t MySpewFunc( SpewType_t type, char const *pMsg )
{
    logsystem::Instance()->Log(type, pMsg);

    if( type == SPEW_ASSERT )
        return SPEW_DEBUGGER;
    else if( type == SPEW_ERROR )
        return SPEW_ABORT;
    else
        return SPEW_CONTINUE;
}


logsystem::logsystem()
{
    m_fp = NULL;
}

logsystem::~logsystem()
{
    if (m_fp)
    {
        fclose(m_fp);
        m_fp = NULL;
    }
}

bool logsystem::Init(const char *server_path)
{
    if (CommandLine()->CheckParm("-d"))
    {
        if (!OpenLogFile(server_path))
        {
            return false;
        }
    }

    SpewOutputFunc(MySpewFunc);

    return true;
}

bool logsystem::OpenLogFile(const char *server_path)
{
    std::string file = server_path;
    file += "/";
    file += "ql-" + std::string(TimeString()) + ".log";

    if (!(m_fp = fopen(file.data(), "w")))
    {
        Error("could not open log file :[%s] to write", file.data());
        return false;
    }
}

logsystem *logsystem::Instance()
{
    static logsystem ls;

    return &ls;
}

const char *logsystem::TimeString()
{
    time_t t = time(NULL);

    tm* lt = localtime(&t);

    if (lt)
    {
        static char str_tm[128];

        sprintf(str_tm, "%d-%.2d-%.2d-%.2d-%.2d-%.2d", lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);

        return str_tm;
    }

    return "";
}

void logsystem::Log(SpewType_t type, char const *msg)
{
    const char *type_desc[] = { "MSG", "WARNING", "ASSERT", "ERROR", "LOG" };

    if (m_fp)
    {
        fprintf(m_fp, "[%s][%s] %s", TimeString(), type_desc[type], msg);
        fflush(m_fp);
    }
    else
    {
        printf("[%s][%s] %s", TimeString(), type_desc[type], msg);
    }
}




#include <stdio.h>
#include "tier0/platform.h"
#include "vstdlib/strtools.h"

int main(int argc, char **argv)
{
		Plat_Alloc(100);
		
        const CPUInformation& info = GetCPUInformation();

        printf("cpu speed : %d\n", info.m_Speed);

        printf("mmx = %d\n", info.m_bMMX);

        printf("cpu name = %s\n",       info.m_szProcessorID);

//      CCycleCount count;

//      count.Sample();

//      char name[128];

//      Q_snprintf(name, sizeof(name), "count = %d", count.GetMilliseconds());

//      printf("%s\n", name);

        return 0;
}
 

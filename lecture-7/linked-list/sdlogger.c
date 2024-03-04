#include "include/sdlogger.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void sdlogger(unsigned long ulErrorType, int iLine, const char *szFile, const char *pszFormat, ...){

    va_list vaArgumentPointer;
    char szOutputString[256] = {0};
    time_t tTimeAndDate = 0;
    char szFileName[256] = {0};
    const char *pszType = (ulErrorType == 1) ? "error" : "debug";

    static FILE *fLogFile = NULL;

    if(fLogFile == NULL){
        tTimeAndDate = time(NULL);
        snprintf(szFileName,256-1,"debug_%li.txt", tTimeAndDate);
        fLogFile = fopen(szFileName, "a");
    }

    va_start(vaArgumentPointer,pszFormat);
    vsnprintf(szOutputString,256-1,pszFormat,vaArgumentPointer);
    va_end(vaArgumentPointer);

    fprintf(fLogFile,"%s, %d: %s %s\n",szFile,iLine,pszType,szOutputString);

}
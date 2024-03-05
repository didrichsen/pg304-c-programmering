//
// Created by Simen Didrichsen on 03/03/2024.
//

#ifndef PG304_C_PROGRAMMERING_SDLOGGER_H
#define PG304_C_PROGRAMMERING_SDLOGGER_H

void sdlogger(unsigned long ulErrorType, int iLine, const char *szFile, const char *pszFormat, ...);

#define sddebug(...) sdlogger(0,__LINE__,__FILE__, __VA_ARGS__)
#define sderror(...) sdlogger(1,__LINE__,__FILE__, __VA_ARGS__)

#endif //PG304_C_PROGRAMMERING_SDLOGGER_H

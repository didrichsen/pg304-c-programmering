/* PGDBGLOG.H header file ---------------------------------------------------------------------

 Project     : Exam-2022 PG3401 H21 - Oppgave 3
 Author      : Bengt �stby
 Revision    : 1.0
 Description : Header file for the "PG Debug Logger" system, this file and the corresponding
               source file could also be placed in a my-static-library project, but I have decided to
               copy this file into all projects to maintain isolation between projects since
               this is an exam and the examiner might want to just look at one task isolated.

--------------------------------------------------------------------------------------------*/

#ifndef __PGDBGLOGGER_H__
#define __PGDBGLOGGER_H__

extern int glob_bTraceEnabled;

void PgDbgLogger(unsigned long ulErrorType, int iLine, const char* szFile, const char* pszFormat, ...);

#define pgdebug(...) if (glob_bTraceEnabled == 1){ PgDbgLogger(0, __LINE__, __FILE__, __VA_ARGS__);}
#define pgerror(...) PgDbgLogger(1, __LINE__, __FILE__, __VA_ARGS__)

void PgDbgInitialize(void);

#endif //__PGDBGLOGGER_H_
/* End of file ------------------------------------------------------------------------------*/

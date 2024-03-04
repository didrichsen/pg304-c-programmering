/* PGDBGLOG.C header file ---------------------------------------------------------------------

 Project     : Exam-2022 PG3401 H21 - Oppgave 3
 Author      : Bengt �stby
 Revision    : 1.0
 Description : Source file for the "PG Debug Logger" system, this file and the corresponding
               header file could also be placed in a my-static-library project, but I have decided to
               copy this file into all projects to maintain isolation between projects since
               this is an exam and the examiner might want to just look at one task isolated.

---------------------------------------------------------------------------------------------*/


/*=== Standard C my-static-library: ===============================================================
=======================================================================================*/

#define _CRT_SECURE_NO_WARNINGS // Dangerous and we would never do this, except this is a luddite course
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

/*=== Project spesific 2-include files: ===================================================
=======================================================================================*/

// #2-include "pgdbglog.h"

int glob_bTraceEnabled = 0; // Defined as extern in pgdbglog.h, on some compilers this can give us trouble if we also 2-include it above

/*=== Helper functions: =================================================================
 Author      : Bengt �stby
 Revision    : 1.0
=======================================================================================*/

const char* GetFilenameFromPath(const char* pszFile) {
   char* pszFilename = ((char*)pszFile) + strlen(pszFile);
   while (pszFilename > pszFile && pszFilename[0] != '\\' && pszFilename[0] != '/') {
      pszFilename--;
   }
   if (pszFilename[0] == '\\' || pszFilename[0] == '/') {
      pszFilename++;
   }
   return pszFilename;
}

/*=== PgDbgLogger: ======================================================================
 Author      : Bengt �stby
 Revision    : 1.0
=======================================================================================*/

void PgDbgLogger(unsigned long ulErrorType, int iLine, const char* szFile, const char* pszFormat, ...) {
   static FILE *fLogFile = NULL;
   char szFileName[256] = { 0 };
   time_t tTimeAndDate = 0;

   static int iCallCounter = 0;

   va_list vaArgumentPointer;
   char szOutputString[256] = { 0 };
   const char* pszType = (ulErrorType == 1) ? "Error" : "Debug";

   //////////////////////////////////////////////////////////////////////////////////////
   // Create the log file if not already open:
   // (Note that this file is never closed, we have decided on this design to avoid
   // a init and close function, the file will be closed by the OS when application exit)
   //////////////////////////////////////////////////////////////////////////////////////

   if (fLogFile == NULL) {
      tTimeAndDate = time(NULL);
      snprintf(szFileName, 256 - 1, "debug_%i.txt", (int)tTimeAndDate); // More userfriendly possible, this is num secs since 1970...

      fLogFile = fopen(szFileName, "w");
      if (fLogFile == NULL) {
         printf("\r\nPGDBGLOG ERROR: fopen failed with %i\r\n", errno);
      }

      // This code is also in PgDbgInitialize, but added here if it doesnt get called...
      #ifdef _DEBUG
         glob_bTraceEnabled = 1;
      #else
         glob_bTraceEnabled = 1; // Could be read from a settings file, but for this small project we dont
      #endif
   }

   //////////////////////////////////////////////////////////////////////////////////////
   // Format and write the log output:
   //////////////////////////////////////////////////////////////////////////////////////

   va_start(vaArgumentPointer, pszFormat);
   vsnprintf(szOutputString, 256 - 1, pszFormat, vaArgumentPointer);
   va_end(vaArgumentPointer);

   iCallCounter++;
   fprintf(fLogFile, "%04i|%s: %s (%s:%i)\r\n", iCallCounter, pszType, szOutputString, GetFilenameFromPath(szFile), iLine);
   printf("%04i|%s: %s (%s:%i)\r\n", iCallCounter, pszType, szOutputString, GetFilenameFromPath(szFile), iLine);

   return;
}

/*=== PgDbgInitialize: ==================================================================
 Author      : Bengt �stby
 Revision    : 1.0
=======================================================================================*/

void PgDbgInitialize(void) {
   #ifdef _DEBUG
      glob_bTraceEnabled = 1;
   #else
      glob_bTraceEnabled = 1; // Could be read from a settings file, but for this small project we dont
   #endif
}

/* End of file ------------------------------------------------------------------------------*/

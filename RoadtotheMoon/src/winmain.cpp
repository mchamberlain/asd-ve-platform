/*
This file is part of the ASD Assist VE Platform.

For the latest info, see http://asd-ve-platform.sourceforge.net/

Copyright (c) 2009 Morné Chamberlain & Stellenbosch University

The ASD Assist VE Platform is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (with the added restriction
that this work and any derivative works may only be used for non-commercial purposes)
as published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The ASD Assist VE Platform is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

//Below is some crap to get the winmain function to call main with the correct args
//It is a basic version of SDL's solution
#if !defined(__MINGW32__) && (defined(__WIN32__) || defined(_WIN32) || defined(_WIN64))

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv);

static int ParseCommandLine(char *cmdline, char **argv) 
{
	char *bufp;
	int argc;

	argc = 0;
	bufp = cmdline;
	while ( *bufp ) 
	{
		/* Skip leading whitespace */
		while ( isspace(*bufp) ) 
		{
			++bufp;
		}
		/* Skip over argument */
		if ( *bufp == '"' ) 
		{
			++bufp;
			if ( *bufp ) 
			{
				if ( argv ) 
				{
					argv[argc] = bufp;
				}
				++argc;
			}
			/* Skip over word */
			while ( *bufp && (*bufp != '"') ) 
			{
				++bufp;
			}
		} 
		else 
		{
			if ( *bufp ) 
			{
				if ( argv ) 
				{
					argv[argc] = bufp;
				}
				++argc;
			}
			/* Skip over word */
			while ( *bufp && ! isspace(*bufp) ) 
			{
				++bufp;
			}
		}
		if ( *bufp ) 
		{
			if ( argv ) 
			{
				*bufp = '\0';
			}
			++bufp;
		}
	}
	if ( argv ) 
	{
		argv[argc] = NULL;
	}
	return(argc);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw) 
{
	char **argv;
	int argc,nLen;
	char *cmdline, *bufp;
	//extern int main(int,char**);

  (void)(sw);
  (void)(hInst);
  (void)(hPrev);
	(void)(szCmdLine);

	/* Grab the command line */
	bufp = GetCommandLine();
	nLen = strlen(bufp)+1;
	cmdline = (char*)malloc(sizeof(char) * nLen);
	if (cmdline == NULL) {
    printf("Out of memory\n");
    return 1;
	}
	strncpy(cmdline, bufp, nLen);

	argc = ParseCommandLine(cmdline, NULL);
	argv = (char**)malloc(sizeof(char*) * (argc+1));
	if (argv == NULL) {
    printf("Out of memory\n");
    return 1;
	}
	if (argc > 0) {
    ParseCommandLine(cmdline, argv);
	}

	return main(argc, argv);
}

#endif

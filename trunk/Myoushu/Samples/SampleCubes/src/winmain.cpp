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

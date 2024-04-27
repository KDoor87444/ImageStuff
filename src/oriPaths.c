#include "oriPaths.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#if defined(WIN32) || defined(_WIN32)
	#include <Shlwapi.h>

	#define PS "\\"

	int getCurrentExePath(char* path, int size) {
		GetModuleFileNameA(NULL, path, size);
		PathRemoveFileSpecA(path);
		return 0;
	}
#else
	#define PS "/"

	int getCurrentExePath(char* path, int size) {
		printf("This does not fucking exist nerd");
		return -1;
	}
#endif
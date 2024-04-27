#if defined(WIN32) || defined(_WIN32)
	#define PS "\\"
#else
	#define PS "/"
#endif

int getCurrentExePath(char* path, int size);
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* loadFile( const char* filename ) {
	FILE* fp = fopen( filename, "r" );
	if (fp == NULL) {
		fprintf(stderr, "Error: cannot open \"%s\"\n", filename);
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	size_t len = ftell(fp);
	rewind(fp);
	char* buf = (char*)malloc(sizeof(char) * (len + 4));
	size_t size = fread(buf, sizeof(char), len, fp);
	fclose(fp);
	buf[size] = '\0';
	return (const char*)buf;
}


const char* getBaseName( const char* progname ) {
#if defined(_WIN32) || defined(_WIN64)
	const char* ptr = (strrchr(progname, '\\') == NULL) ? progname : (strrchr(progname, '\\') + 1);
#else // Unix, Linux, MacOS
	const char* ptr = (strrchr(progname, '/') == NULL) ? progname : (strrchr(progname, '/') + 1);
#endif
	char* buf = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));
	strcpy(buf, ptr);
	if (strrchr(buf, '.') != NULL) { // cut-off ".exe", if exists
		*(strrchr(buf, '.')) = '\0';
	}
	return (const char*)buf;
}

const char* getVertName( const char* basename) {
	static char buf[256];
	sprintf(buf, "%s.vert", basename);
	return (const char*)buf;
}

const char* getFragName( const char* basename) {
	static char buf[256];
	sprintf(buf, "%s.frag", basename);
	return (const char*)buf;
}


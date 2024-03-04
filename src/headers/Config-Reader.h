#pragma once

/*
*	Author: Ahmed Magdy
*	Date:   3/4/2024
*   Descirption:
*   - Config file structure should be as follows:
*     - each config directive should be placed on a seperate line
*     - each line should contain a dirctive name without any spaces then a semi colon ';' and then a value
*     - sample config file:
*       dir-template-path: C:\Users\Documents\index.html
*     - important notes:
*       - no spaces are allowed in the directive name
*       - no double or single qoutes are allowed to surround any string value
*   Result Codes:
*	-1: Reached End Of File
*   -2: No Value Found for the Current Directive
*   -3: Unknown Directive
*/

#include <Windows.h>

#include <string.h>

#define PATH_LEN 255
#define BUFF_LEN 4096

typedef struct {

	char dirTemplatePath[PATH_LEN];
	size_t maxThreadsCount;

} ConfigObject;

static void ExtractNextDirective(char* str, ConfigObject* cfg, int* resultCode) {
	char* nextToken;
	char* directive = strtok_s(str, ";", &nextToken);

	if (directive != NULL) {
		char* value = strtok_s(NULL, ";", &nextToken);

		if (value != NULL) {
			*resultCode = 0;
			if (strncmp("dir-template-path", directive, strlen(directive)) == 0) {
				CopyMemory(cfg->dirTemplatePath, value, strlen(value));
			}
			else if (strncmp("max-threads", directive, strlen(directive)) == 0) {
				cfg->maxThreadsCount = atoi(value);
			}
			else {
				*resultCode = -3;
			}
		}
		else {
			*resultCode = -2;
		}
	}
	else {
		*resultCode = EOF;
	}
}


static ConfigObject ParseConfig(char buffer[], DWORD len) {
	size_t i = 0, startOfLine = 0;
	ConfigObject cfg;
	ZeroMemory(&cfg, sizeof(cfg));
	int resultCode = 0;

	for (; i < len; ++i) {
		if (buffer[i] == '\n') {
			buffer[i-1] = '\0';
			ExtractNextDirective(buffer + startOfLine, &cfg, &resultCode);
			startOfLine = i+1;
		}
	}

	return cfg;
}

ConfigObject ReadConfig(const char* filePath) {
	HANDLE fileHandle = CreateFileA(filePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (fileHandle == INVALID_HANDLE_VALUE) {
		fileHandle = CreateFileA(filePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	char buffer[BUFF_LEN];
	ZeroMemory(buffer, BUFF_LEN);
	DWORD readBytes = 0;

	BOOL readResult = ReadFile(fileHandle, buffer, BUFF_LEN, &readBytes, NULL);

	return ParseConfig(buffer, readBytes);
}
#ifndef JTW1572_LAB01_H
#define JTW1572_LAB01_H

#include<sys/types.h>
#include<dirent.h>
#include<stdint.h>
#include<stdlib.h>

#define MAXFILENAMELENGTH 100
#define MAXDIRECTORYNAMELENGTH 200

// The <dirent.h> header defines the directory stream
// type as typedef struct __dirstream DIR. The <dirent.h>
// header also defines the directory entry structure as
// struct dirent. Both types will be stored in the
// typedef struct DIRECTORYENTRY DirectoryEntry structure.
typedef struct DIRECTORYENTRY
{
	DIR* directoryStream;
	struct dirent* directoryInformation;
}	DirectoryEntry;

// The FileSearch() function will begin traversing the
// files and directories starting at the current directory.
uint32_t FileSearch();

// The GetFileSize() function returns the size of the file;
// the file name will be passed as a char*.
uint32_t GetFileSize(char* fileName);

// The GetEntries() function will traverse through the entries
// in the currentWorkingDirectory.
uint32_t GetEntries(char* currentWorkingDirectory);

#endif

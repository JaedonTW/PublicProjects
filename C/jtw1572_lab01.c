#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>
#include"jtw1572_lab01.h"

uint32_t GetFileSize(char* fileName)
{
	// The file is opened and the length of the file is
	// gathered by using fseek() to traverse to the end of 
	// the file.
	FILE* filePointer = fopen(fileName,"r");
	fseek(filePointer,0,SEEK_END);
	uint32_t fileSize = ftell(filePointer);
	fclose(filePointer);
	return fileSize;
}

uint32_t GetEntries(char* currentWorkingDirectory)
{
	// constantDirectory is the current working directory. Having 
	// a reference to the constant directory is important as the 
	// currentWorkingDirectory argument will be concatenated with
	// the newest entry found.
	char* constantDirectory = malloc(sizeof(char)*100);
	strcpy(constantDirectory,currentWorkingDirectory);

	// Allocate memory for the DirectoryEntry
	DirectoryEntry* entry = calloc(1,sizeof(DirectoryEntry));
	entry->directoryInformation = calloc(1,sizeof(struct dirent));
	entry->directoryStream = opendir(currentWorkingDirectory);

	printf("Current Working Directory: %s\n\n",currentWorkingDirectory);

	// directoryTotal will hold the total size of all
	// contents in all directories.
	uint32_t directoryTotal = 0;

	// fileStatusStructure will hold the information found
	// in each file.
	struct stat* fileStatusStructure = calloc(1,sizeof(struct stat));
	
	for(entry->directoryInformation = readdir(entry->directoryStream);(entry->directoryInformation) != NULL; entry->directoryInformation = readdir(entry->directoryStream))
	{	
		strcpy(currentWorkingDirectory,constantDirectory);

		// readdir() returns NULL at the end of
		// a directory. At this point, we can return
		// the total size of all files found.
		if(entry->directoryInformation == NULL)
		{
			printf("\n");
			return 0;
		}

		strcat(currentWorkingDirectory,"/");
		strcat(currentWorkingDirectory,entry->directoryInformation->d_name);	
		stat(currentWorkingDirectory,fileStatusStructure);

		// If the entry found is a file, find the size of the file
		// and add it to the directoryTotal variable.
		if(S_ISREG(fileStatusStructure->st_mode))
		{
			directoryTotal = directoryTotal + GetFileSize(currentWorkingDirectory);
			printf("File Name: %s ----- ",entry->directoryInformation->d_name);
			printf("Size: %d bytes\n",GetFileSize(currentWorkingDirectory));
		}

		// If the entry found is a directory, call GetEntries()
		// --- THIS IS WHERE THE RECURSIVE CALL IS LOCATED ------
		else if(S_ISDIR(fileStatusStructure->st_mode) && strcmp(entry->directoryInformation->d_name,"..")!=0 && strcmp(entry->directoryInformation->d_name,".")!=0)
		{
			printf("\nDirectory Entry Found\n\n");
			char* newDir = calloc(100,sizeof(char));
			strcpy(newDir,currentWorkingDirectory);
			directoryTotal = directoryTotal + GetEntries(newDir);
			printf("Current Working Directory: %s\n\n",constantDirectory);
		}
	}

	printf("\n");	
	return directoryTotal;
}

uint32_t FileSearch()
{
	printf("\n");

	// Get the current working directory
	char* currentWorkingDirectory = calloc(1,sizeof(char) * MAXFILENAMELENGTH);
	getcwd(currentWorkingDirectory,MAXFILENAMELENGTH);

	// Open the directory stream and begin the GetEntries()
	// function that will be called recursively.	
	return GetEntries(currentWorkingDirectory);
}


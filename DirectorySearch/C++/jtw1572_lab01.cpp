#include<cstdlib>
#include<iostream>
#include<fstream>
#include<unistd.h>
#include<cstdint>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include"jtw1572_lab01.h"
#include<string.h>

using std::ifstream;
using std::cout;

uint32_t GetFileSize(char* fileName)
{
	ifstream fileInput;
	fileInput.open(fileName, std::fstream::in);	
	fileInput.seekg(0,fileInput.end);
	uint32_t fileSize = fileInput.tellg();
	fileInput.close();
	return fileSize;
}

uint32_t GetEntries(char* currentWorkingDirectory)
{
	// constantDirectory is the current working directory. Having 
	// a reference to the constant directory is important as the 
	// currentWorkingDirectory argument will be concatenated with
	// the newest entry found.
	char* constantDirectory = (char*) malloc(sizeof(char)*100);
	strcpy(constantDirectory,currentWorkingDirectory);

	// Allocate memory for the DirectoryEntry
	DirectoryEntry* entry = (DirectoryEntry*) calloc(1,sizeof(DirectoryEntry));
	entry->directoryInformation = (struct dirent*) calloc(1,sizeof(struct dirent));
	entry->directoryStream = opendir(currentWorkingDirectory);

	cout<<"Current Working Directory: "<<currentWorkingDirectory<<"\n\n";

	// directoryTotal will hold the total size of all
	// contents in all directories.
	uint32_t directoryTotal = 0;

	// fileStatusStructure will hold the information found
	// in each file.
	struct stat* fileStatusStructure = (struct stat*) calloc(1,sizeof(struct stat));
	
	for(entry->directoryInformation = readdir(entry->directoryStream);(entry->directoryInformation) != NULL; entry->directoryInformation = readdir(entry->directoryStream))
	{	
		strcpy(currentWorkingDirectory,constantDirectory);

		// readdir() returns NULL at the end of
		// a directory. At this point, we can return
		// the total size of all files found.
		if(entry->directoryInformation == NULL)
		{
			cout<<"\n";
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
			cout<<"File Name: " <<entry->directoryInformation->d_name <<" ----- ";
			cout<<"Size: "<<GetFileSize(currentWorkingDirectory) <<" bytes\n";
		}

		// If the entry found is a directory, call GetEntries()
		// --- THIS IS WHERE THE RECURSIVE CALL IS LOCATED ------
		else if(S_ISDIR(fileStatusStructure->st_mode) && strcmp(entry->directoryInformation->d_name,"..")!=0 && strcmp(entry->directoryInformation->d_name,".")!=0)
		{
			cout<<"\nDirectory Entry Found\n\n";
			char* newDir = (char*) calloc(100,sizeof(char));
			strcpy(newDir,currentWorkingDirectory);
			directoryTotal = directoryTotal + GetEntries(newDir);
			cout<<"Current Working Directory: "<<constantDirectory<<"\n\n";
		}
	}

	cout<<"\n";	
	return directoryTotal;
}

uint32_t FileSearch()
{
	cout<<"\n";

	// Get the current working directory
	char* currentWorkingDirectory = (char*) calloc(1,sizeof(char) * MAXFILENAMELENGTH);
	getcwd(currentWorkingDirectory,MAXFILENAMELENGTH);

	// Open the directory stream and begin the GetEntries()
	// function that will be called recursively.	
	return GetEntries(currentWorkingDirectory);
}


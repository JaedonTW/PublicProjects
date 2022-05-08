#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdint.h>
#include<dirent.h>
#include"jtw1572_lab01.h"

int main(int argc,char** argv)
{
	// totalSize will hold the total size of all files in the 
	// current directory as well as all subdirectories
	uint32_t totalSize = 0;

	char* fileName = malloc(sizeof(char) * MAXFILENAMELENGTH);
	char* directoryName = malloc(sizeof(char) * MAXDIRECTORYNAMELENGTH);

	// The process will begin by obtaining the 
	// current directory name and beginning the 
	// recursive file search.
	getcwd(directoryName,MAXDIRECTORYNAMELENGTH);
	totalSize = FileSearch(directoryName);

	printf("The total size of all files: %d bytes\n\n",totalSize);

	free(fileName);
	free(directoryName);

	return EXIT_SUCCESS;
}


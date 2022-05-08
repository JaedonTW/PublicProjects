#include<cstdlib>
#include<iostream>
#include<unistd.h>
#include<cstdint>
#include<dirent.h>
#include"jtw1572_lab01.h"

int main(int argc,char** argv)
{
	// totalSize will hold the total size of all files in the 
	// current directory as well as all subdirectories
	uint32_t totalSize = 0;

	char* fileName = (char*) malloc(sizeof(char) * MAXFILENAMELENGTH);
	char* directoryName = (char*) malloc(sizeof(char) * MAXDIRECTORYNAMELENGTH);

	// The process will begin by obtaining the 
	// current directory name and beginning the 
	// recursive file search.
	getcwd(directoryName,MAXDIRECTORYNAMELENGTH);
	totalSize = FileSearch();

	std::cout<<"The total size of all files: "<<totalSize<<" bytes"<<std::endl;

	free(fileName);
	free(directoryName);

	return EXIT_SUCCESS;
}


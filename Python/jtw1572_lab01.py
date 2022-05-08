import fileinput
import os
import stat

def GetFileSize(fileName):
    file = open(fileName);
    file.seek(0, os.SEEK_END);
    return file.tell();

def GetEntries(currentWorkingDirectory):
    # constantDirectory is the current working directory. Having 
    # a reference to the constant directory is important as the 
    # currentWorkingDirectory argument will be concatenated with
    # the newest entry found.
    constantDirectory = currentWorkingDirectory;

    print "\n","Current Working Directory:",currentWorkingDirectory,"\n";
    # directoryTotal will hold the total size of all
    # contents in all directories.

    directoryContents = os.listdir(constantDirectory);

    i =0

    directoryTotal = 0;

    while i<len(directoryContents):
        currentWorkingDirectory = constantDirectory + '/' + directoryContents[i]
        print(currentWorkingDirectory);

        # If the entry found is a file, find the size of the file
        # and add it to the directoryTotal variable.
        if stat.S_ISREG(os.stat(directoryContents[i]).st_mode):
            directoryTotal = directoryTotal + GetFileSize(currentWorkingDirectory);
            print "File Name:",directoryContents[i],"----- Size:",GetFileSize(currentWorkingDirectory),"bytes";       

        # If the entry found is a directory, call GetEntries()
        # --- THIS IS WHERE THE RECURSIVE CALL IS LOCATED ------
        elif stat.S_ISDIR(os.stat(directoryContents[i]).st_mode):
            print "\nDirectory Entry Found";
            newDir = currentWorkingDirectory;
            os.chdir(currentWorkingDirectory);
            directoryTotal = directoryTotal + GetEntries(newDir);
            os.chdir(constantDirectory);
            print "\n","Current Working Directory:",constantDirectory,"\n";

        i = i+1;	
        
    return directoryTotal;

def FileSearch():

    # Get the current working directory
    currentWorkingDirectory = os.getcwd();

    # Open the directory stream and begin the GetEntries()
    # function that will be called recursively.	
    return GetEntries(currentWorkingDirectory);


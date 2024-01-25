void addProcesses(struct node* ready_queue)
{
	// File handling
	FILE* fp;
	int file_count; // Number of files in newProc - used to determine pid
	char file_contents[50]; // To store read file contents
	char fileloc[50]; // Location of current file in the directory structure
        char* token; // Used for retrieving niceness and proctime from file
	char* dirname = "../newProc"; // Hard-coded
	DIR *processDir; // Will point to newProc
	struct dirent *file; // Current file being examined
	// Process Variables
	int niceness; // Current process' niceness
	double proctime; // Current process' proctime

	/* Open newProc directory and check for presence of files*/
	processDir = opendir(dirname);
	if (processDir == NULL){
		printf("No new processes available. Closing program.\n");
		return 1;
	}
	
	// Read from files in the new process directory. Add processes to ready queue one by one
	while ( (file = readdir(processDir)) ){
		if ((strcmp(file->d_name, ".") == 0) || (strcmp(file->d_name, "..") == 0)){
			continue;
		}
		file_count++; // Used for pid
	        
		// File location in the form ../newProc/(FILE)
		strcpy(fileloc, dirname);
	        strncat(fileloc, "/", 2);
		strncat(fileloc, file->d_name, 30);
                // Point to file - goes to next process if file can't be opened
                fp = fopen(fileloc, "r");
                if (fp == NULL){
                        printf("Could not open file.\n");
			continue;
                }
		// Read file and put into file_contents
                while (fgets(file_contents, 50, fp)){
                }

                // Get niceness
                token = strtok(file_contents, " ");
                niceness = atoi(token);
		// Get proctime
                token = strtok(NULL, " ");
                proctime = atof(token);

		// After reading from file, make a new process and add to ready queue
		printf("Adding %s to ready queue...\n", file->d_name);
		ready_queue = push(struct node *process, file_count, 1, niceness, initial_time, proctime);
	}

	closedir(processDir);
}

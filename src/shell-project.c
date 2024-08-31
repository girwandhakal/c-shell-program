
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#define MAX_LINE 80 /* The maximum length command */

int main(void) {
    char *args[MAX_LINE/2 + 1]; /* command line arguments , this is an array of string pointers*/
    char cmd[MAX_LINE/2 + 1];
    char *token;
    bool should_wait = true; // wait for the child process or not
    bool redirect = false;
    int pid;
    int should_run = 1; /* flag to determine when to exit the program */
    while (should_run) {
        printf("gdhakal_%d> ", (int)getpid()); // Prompt showing current process ID
        fgets(cmd, MAX_LINE, stdin); // Read the command input from the user

        // Remove the newline character from the end of the input
        cmd[strcspn(cmd, "\n")] = '\0';

        if (strcmp(cmd, "exit") == 0) { // Check if the user entered the exit command
            should_run = 0; // Set the flag to exit the program
        }

        fflush(stdout); // Clear the output buffer

        int i = 0;
        token = strtok(cmd, " "); // Split the input command into tokens

        // Fill the args array with pointers to each token
        while (token != NULL) { 
            args[i] = strdup(token); // Allocate memory and copy the token
            if(strcmp(args[i], ">") == 0) { // Check if the output redirection symbol '>' is present
                redirect = true; // Set the redirection flag
            }
            token = strtok(NULL, " "); // Move to the next token
            i++;
        }

        args[i] = NULL; // Null-terminate the args array

        // Check if the last argument is '&', indicating that the process should run in the background
        if(args[i - 1] != NULL && strcmp(args[i-1], "&") == 0) {
            should_wait = false; // Set the flag to not wait for the child process
            args[i-1] = NULL; // Remove '&' from the arguments list
        }

        pid = fork(); // Create a child process

        if(pid < 0) { // Error occurred during fork
            printf("Error in child creation\n");
            return 1; // Exit with error
        }
        else if(pid == 0) { // Child process block
            if(redirect) { 
                int fd = open(args[i-1], O_WRONLY | O_TRUNC | O_CREAT, "0666"); // Open the output file
                dup2(fd, STDOUT_FILENO); // Redirect stdout to the output file
                close(fd); 
            }
            execvp(args[0], args); // Execute the command
        }
        else { // Parent process block
            if(should_wait) { 
                int parent_wait = waitpid(pid, NULL, 0); 
            }
        }

    return 0;
}

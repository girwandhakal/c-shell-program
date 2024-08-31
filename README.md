# Simple Shell Command Processor

This project is a C program that simulates a basic shell command processor. It reads user input, parses commands, and supports basic features like executing commands, output redirection, and background process execution.

## Features

- **Command Execution**: Executes commands entered by the user.
- **Output Redirection**: Redirects the output of a command to a file using the `>` symbol.
- **Background Execution**: Executes commands in the background using the `&` symbol.
- **Exit Command**: Exits the shell when the user types `exit`.

### Command Format

1. **Execute Commands**: Simply type the command you want to execute and press Enter.
    
    * Example: `ls -l`

2. **Output Redirection**: Use the `>` symbol to redirect the output to a file.
    
    * Example: `echo "Hello, World!" > output.txt`

3. **Background Execution**: Use the `&` symbol to run the command in the background.
    
    * Example: `sleep 10 &`

4. **Exit**: Type `exit` to terminate the shell session.

## Code Overview

- **Input Handling**: The program reads input from the user, removes newline characters, and tokenizes the command.
- **Command Parsing**: Tokens are analyzed to determine if output redirection or background execution is requested.
- **Process Creation**: The program uses `fork()` to create a child process for command execution.
- **Redirection**: If output redirection is requested, it redirects standard output to the specified file.
- **Background Execution**: If the command is to be run in the background, the parent process does not wait for the child to finish.






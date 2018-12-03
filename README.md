# MKS65C-shell

## Shell Features:
Reads a line at a time

Parsees the line to separate the command from its arguments

Then forks and execs the command

The parent process waits until the exec'd program exits and then it reads the next command.

Can exec commands, cd, exit, simple redirectiion, and simple pipes

### Attempted:
Separate multiple commands on one line with ;

## Bugs:
Only single commands can be parsed with ;. Even if the commands are executed, the shell may be exited. Or, only first command is executed.

## Restrictions:
All items on the command line are to be separated by a single space

Redirection is limited to a single < or > 

Piping (|) limited to a single pipe

## Function Headers:
void start();

void print_dir();

char * read_line();

void parse_space(char * input, char ** parsed);

int parse_pipe(char * input, char ** pipes);

int parse_redirect(char * input, char ** pipes);

int parse_args(char * input, char ** parsed, char ** parsed_pipe);

int exec_builtin(char ** parsed);

void exec_cmd(char ** parsed);

void exec_pipe(char ** parsed, char ** parsed_pipe);

void exec_redirect(char ** parsed, char ** parsed_pipe);

void exec_args(int exec_num, char ** parsed, char ** parsed_pipe);

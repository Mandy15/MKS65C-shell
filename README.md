# MKS65C-shell
A description of what features your shell implements
A description of what features you attempted to implement but were unsuccessful
Any bugs or things you want me to know about your program
I am much more forgiving of reported bugs than bugs I discover while testing
A copy of every function header
An example of the readme file can be found in the github repository for this assignment

## Shell Features:

### Attempted:

## Bugs/Restrictions:


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

void start();

void print_dir();

char * read_line();

void parse_space(char * input, char ** parsed);

int parse_pipe(char * input, char ** parsed_pipe);

int parse_args(char * input, char ** parsed, char ** parsed_pipe);

void exec_cmd(char ** parsed);

void exec_pipe(char ** parsed_pipe);

void exec_args(int exec_num, char ** parsed, char ** parsed_pipe);

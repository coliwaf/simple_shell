#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <sys/types.h>

#define UNUSED __attribute__((unused))

typedef struct get_builtins
{
	char *com;

	void (*f)(char *name, char **av, int status, char **env);
} get_b;

char **tokenize_av(char **av, char *buffer, ssize_t chars_read);
char *which_command(char *command);
int check_space(char *str, ssize_t n);
void execute_command(char *command, char **arguments, char **env);
int print_prompt(char *cwd);
char *get_host_name(void);
void free_as(char **av);
char *which_file(char *com);
char **test(char **av);

void _perror(char *name, char **av, int status, char **env);
void exit_b(char *name, char **av, int status, char **env);
void alias_b(char *name, char **av, int status, char **env);
void _cd(char *name, char **av, int status, char **env);
void _env(char *name, char **av, int status, char **env);
void (*get_builtins(char *command))(char *name, char **av, int status, char **env);
#endif

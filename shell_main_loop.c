#include "shell.h"

/**
 * main_shell - programs' main shell loop
 * @data: the param & return data struct
 * @argv: the arg vector param
 * Return: on success - 0 , on error - 1 , or resulting error code
 */
int main_shell(data_s *data, char **argv)
{
	ssize_t res = 0;
	int builtin_ret = 0;

	while (res != -1 && builtin_ret != -2)
	{
		clear_data(data);
		if (active_terminal(data))
			_puts("$ ");

		err_putchar(NEGATIVE_ONE);
		res = get_input(data);
		if (res != -1)
		{
			set_data(data, argv);
			builtin_ret = select_builtin(data);
			if (builtin_ret == -1)
				fetch_command(data);
		}
		else if (active_terminal(data))
			_putchar('\n');

		free_data(data, 0);
	}

	create_update_history(data);
	free_data(data, 1);
	if (!active_terminal(data) && data->status)
		exit(data->status);

	if (builtin_ret == -2)
	{
		if (data->err_code == -1)
			exit(data->status);
		exit(data->err_code);
	}

	return (builtin_ret);
}

/**
 * select_builtin - finds and selects a builtin command
 * @data: param & return data struct
 * Return: if builtin not found -1 ,
 *         if builtin found and executed successfully 0,
 *         if builtin found but not successful 1,
 *         if builtin signals exit() 2
 */
int select_builtin(data_s *data)
{
	int i;
	int builtin_result = -1;
	builtin_cmds builtin_lst[] = {
		{"env", prnt_env},
		{"help", handle_help},
		{"cd", handle_curr_dir},
		{"alias", handle_alias},
		{"history", handle_history},
		{"exit", handle_exiting},
		{"setenv", set_the_environ},
		{"unsetenv", unset_the_environ},
		{NULL, NULL}
	};

	for (i = 0; builtin_lst[i].type; i++)
		if (_strcmp(data->argv[0], builtin_lst[i].type) == 0)
		{
			data->ln_count++;
			builtin_result = builtin_lst[i].func(data);
			break;
		}

	return (builtin_result);
}

/**
 * fetch_command - finds a command in PATH
 * @data: the param & return data struct
 */
void fetch_command(data_s *data)
{
	char *path = NULL;
	int i, j;

	data->path = data->argv[0];
	if (data->ln_count_flag == 1)
	{
		data->ln_count++;
		data->ln_count_flag = 0;
	}

	for (i = 0, j = 0; data->arg[i]; i++)
		if (!is_delimiter(data->arg[i], " \t\n"))
			j++;

	if (!j)
		return;

	path = fetch_cmd_in_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		process_fork(data);
	}
	else
	{
		if ((active_terminal(data) || _getenv(data, "PATH=")
					|| data->argv[0][0] == '/') && _is_exec(data, data->argv[0]))
			process_fork(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * process_fork - forks new process to run cmd
 * @data: the param & return data struct
 */
void process_fork(data_s *data)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

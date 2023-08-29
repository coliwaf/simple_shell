 #include "shell.h"

/**
 * handle_exiting - exits this shell
 * @data: Struct containing potential args.
 * Return: 0 if data.argv[0] != "exit", else
 * exits with provided status
 */
int handle_exiting(data_s *data)
{
	int chk_exit, i = 0;

	if (data->argv[1])
	{
		while (data->argv[1][i])
		{
			if (_isalpha(data->argv[1][i++]) != 0)
			{
				data->status = 2;
				print_error(data, "Illegal number: ");
				err_puts(data->argv[1]);
				err_putchar('\n');
				return (1);
			}
			else
			{
				chk_exit = numb_atoi_err(data->argv[1]);
				if (chk_exit == -1 || chk_exit == -2)
				{
					data->status = 2;
					print_error(data, "Illegal number: ");
					err_puts(data->argv[1]);
					err_putchar('\n');
					return (1);
				}
			}
		}

		data->err_code = numb_atoi_err(data->argv[1]);
		return (-2);
	}

	data->err_code = -1;
	return (-2);
}

/**
 * handle_curr_dir - This function changes the current directory(cd) of process
 * @data: Struct containing potential args
 *
 * Return: Always 0
 */
int handle_curr_dir(data_s *data)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Directory does not exist");
	if (!data->argv[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		err_puts(data->argv[1]), err_putchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * handle_help - changes the current directory of the process
 * @data: Struct containing potential args
 * Return: Always 0
 */
int handle_help(data_s *data)
{
	char **arg_array;

	arg_array = data->argv;
	_puts("Help works! \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * handle_history - displays history list, preceded
 *              by line numbers, starting at 0, one command by line.
 * @data: Struct containing potential args
 *  Return: Always 0
 */
int handle_history(data_s *data)
{
	_list_prnt(data->history);
	return (0);
}

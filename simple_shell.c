#include "shell.h"

/**
 * main - entry point
 * @argc: arguments count param
 * @argv: arguments vector param
 * Return: 0 on success otherwise 1 if error is encountered
 */
int main(int argc, char *argv[])
{
	data_s data[] = {DATA_INIT};
	int file_descr = 2;

	if (argc == 2)
	{
		file_descr = open(argv[1], O_RDONLY);
		if (file_descr == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				err_puts(argv[0]);
				err_puts(": 0: Failed to open file ");
				err_puts(argv[1]);
				err_putchar('\n');
				err_putchar(NEGATIVE_ONE);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->retrv_file_descriptor = file_descr;
	}

	create_env(data);
	get_history(data);
	main_shell(data, argv);
	return (EXIT_SUCCESS);
}

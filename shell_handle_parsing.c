#include "shell.h"

/**
 * _is_exec - checks if file is executable
 * @data: data struct
 * @path: file path
 * Return: 0 if false, 1 if true
 */
int _is_exec(data_s *data, char *path)
{
	struct stat s;

	(void)data;
	if (!path || stat(path, &s))
		return (0);

	if (s.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * _char_dupli - duplicates the given chars
 * @pathstr: PATH var str
 * @start: starting index param
 * @stop: Stopping index param
 * Return: ptr to the created buffer
 */
char *_char_dupli(char *pathstr, int start, int stop)
{
	static char buffr[1024];
	int i = 0;
	int j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffr[j++] = pathstr[i];
	buffr[j] = 0;
	return (buffr);
}

/**
 * fetch_cmd_in_path - finds cmd from the fetched PATH string
 * @data: data struct
 * @pathstr: PATH string
 * @cmd: command to look for
 * Return: NULL if not found, full path if found
 */
char *fetch_cmd_in_path(data_s *data, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && str_starts_with(cmd, "./"))
		if (_is_exec(data, cmd))
			return (cmd);

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _char_dupli(pathstr, curr_pos, i);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (_is_exec(data, path))
				return (path);

			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}


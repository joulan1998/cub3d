#include "../../headers/cub3d.h"

/**
 * @brief Counts the number of dots in a filename, excluding the first character.
 *
 * This function iterates through the given filename string and counts the number
 * of dot ('.') characters it contains, starting from the second character.
 *
 * @param filename The name of the file as a null-terminated string.
 * @return The number of dots found in the filename.
 */
static int	count_dots(const char *filename)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	while (filename[i])
	{
		if (filename[i] == '.' && i != 0) //~ we don't count a dot if it's the first thing because the file might be hidden but have a valid extension
			dot_count++;
		i++;
	}
	return (dot_count);
}

/**
 * @brief Checks if the given file path has the specified file extension.
 *
 * This function takes a file path and an extension as input and checks if the file
 * at the given path has the specified extension. It splits the file path by '/'
 * to extract the filename, then checks if the filename has exactly one dot and
 * if the extension matches the specified extension.
 *
 * @param file_path The path to the file to be checked.
 * @param ext The expected file extension (including the dot, e.g., ".txt").
 * @return true if the file has the specified extension, false otherwise.
 */
bool	is_valid_file_extension(const char *file_path, const char *ext)
{
	char	**split;
	char	*filename;
	int		i;

	if (!file_path || !ext)
		return (false);
	split = ft_split((char *)file_path, '/');
	if (!split)
		return (false);
	i = 0;
	while (split[i])
		i++;
	if (i == 0)
		return (free_strings(split), false);
	filename = split[i - 1];
	if (count_dots(filename) != 1 || ft_strrchr(filename, '.') == filename)
		return (free_strings(split), false);
	if (ft_strcmp(ft_strrchr(filename, '.'), ext) != 0)
		return (free_strings(split), false);
	return (free_strings(split), true);
}

/**
 * @brief Checks if the given file path is valid and accessible.
 *
 * This function attempts to open the file at the specified path in read-only mode.
 * If the file can be opened, it is considered a valid path and the function returns true.
 * If the file cannot be opened, it is considered an invalid path and the function returns false.
 *
 * @param path The file path to check.
 * @return true if the file path is valid and accessible, false otherwise.
 */
bool is_valid_path(const char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (false);
    return (close(fd), true);
}

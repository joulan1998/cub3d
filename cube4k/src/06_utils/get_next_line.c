
#include "../../headers/cub3d.h"

static char	*ft_strchr2(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)(&s[i]));
	return (NULL);
}

static char	*read_line(int fd, char *buffer, char *saved)
{
	int		bytes_read;
	char	*temp;
	char	*newline_ptr;

	bytes_read = 1;
	newline_ptr = ft_strchr2(saved, '\n');
	while (newline_ptr == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, 10);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = saved;
		saved = ft_strjoin(saved, buffer);
		free(temp);
		newline_ptr = ft_strchr2(saved, '\n');
	}
	if (bytes_read == -1 || (bytes_read <= 0 && saved && saved[0] == '\0'))
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	return (saved);
}

static char	*extract_line(char **saved, int i)
{
	char	*line;
	char	*temp;

	while ((*saved)[i] != '\n' && (*saved)[i] != '\0')
		i++;
	if ((*saved)[i] == '\n')
	{
		line = ft_substr(*saved, 0, i + 1);
		temp = *saved;
		*saved = ft_strdup(*saved + i + 1);
		free(temp);
		if ((*saved)[0] == '\0')
		{
			free(*saved);
			*saved = NULL;
		}
	}
	else
	{
		line = ft_strdup(*saved);
		free(*saved);
		*saved = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	char		*line;

	if (fd < 0 || 10 <= 0)
		return (NULL);
	buffer = (char *)malloc((10 + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!saved)
		saved = ft_strdup("");
	saved = read_line(fd, buffer, saved);
	free(buffer);
	if (!saved)
		return (NULL);
	line = extract_line(&saved, 0);
	if (!line)
	{
		free(saved);
		saved = NULL;
	}
	return (line);
}

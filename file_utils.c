/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:42:38 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	count_dots( char *filename)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	while (filename[i])
	{
		if (filename[i] == '.' && i != 0)
			dot_count++;
		i++;
	}
	return (dot_count);
}

bool	is_valid_file_extension(char *file_path, char *ext)
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
	if (count_dots(filename) != 1 || ft_strrchr1(filename, '.') == filename)
		return (free_strings(split), false);
	if (ft_strcmp1(ft_strrchr1(filename, '.'), ext) != 0)
		return (free_strings(split), false);
	return (free_strings(split), true);
}

bool	is_valid_path( char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	return (close(fd), true);
}

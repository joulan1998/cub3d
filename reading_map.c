/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:57:48 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/19 15:58:26 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char **reading_map(int fd)
{
    if (fd < 3)
    {
        puts("error in fd");
        exit(1);
    }
    char *buffer = malloc(sizeof(char) * 101); // +1 for null-terminator
    if (!buffer)
        return NULL;

    char *total = malloc(1);
    if (!total)
    {
        free(buffer);
        return NULL;
    }
    total[0] = '\0'; // Initialize as an empty string

    ssize_t readen;
    while ((readen = read(fd, buffer, 100)) > 0)
    {
        buffer[readen] = '\0'; // Null-terminate the read data
        char *new_total = ft_strjoin(total, buffer);
        if (!new_total)
        {
            free(buffer);
            free(total);
            return NULL;
        }
        free(total); // Free the old `total` before reassigning
        total = new_total;
    }

    free(buffer); // Free buffer after reading is complete

    if (readen < 0) // Check for read error
    {
        free(total);
        return NULL;
    }

    char **result = ft_split(total, '\n');
    free(total); // Free the concatenated string
    return result;
}
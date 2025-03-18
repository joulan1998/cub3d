// split_utils.c
#include "../../../headers/cub3d.h"

static int count_parts(const char *s)
{
    int counter;
    int found_space;

    counter = 0;
    found_space = 0;
    while (*s)
    {
        while (*s && ft_isspace(*s))
            s++;
        if (*s && !ft_isspace(*s))
        {
            while (*s && !ft_isspace(*s))
                s++;
            counter++;
            if (*s)
                found_space = 1;
            while (*s && ft_isspace(*s))
                s++;
            if (*s && found_space)
                counter++;
        }
    }
    if (counter > 2)
        return (2);
    return (counter);
}

static int identifier_length(const char *s)
{
    int index;

    index = 0;
    while (s[index] && !ft_isspace(s[index]))
        index++;
    return (index);
}

static void *free_memory(char **result, int length)
{
    int index;

    index = 0;
    while (index < length)
        free(result[index++]);
    free(result);
    return (NULL);
}

/**
 * @brief Splits a string into two parts at the first space character.
 *
 * This function splits the input string at the first occurrence of a space,
 * creating an array with the identifier (before the space) and value (everything
 * after the first space, including additional spaces), followed by a NULL terminator.
 * Leading spaces are skipped before the identifier.
 *
 * @param line The input string to split.
 * @return Array of two strings (identifier, value, NULL) or NULL if invalid.
 */
char **split_two(char *line)
{
    char    **result;
    int     index;
    int     parts_count;
    int     id_len;

    if (!line)
        return (NULL);
    parts_count = count_parts(line);
    if (parts_count != 2)
        return (NULL);
    result = malloc(sizeof(char *) * (parts_count + 1));
    if (!result)
        return (NULL);
    index = 0;
    while (*line && ft_isspace(*line))
        line++;
    id_len = identifier_length(line);
    result[index] = ft_substr((char *)line, 0, id_len);
    if (!result[index])
        return (free_memory(result, index));
    index++;
    line += id_len;
    result[index] = ft_strdup((char *)line);
    if (!result[index])
        return (free_memory(result, index));
    index++;
    result[index] = NULL;
    return (result);
}
// parsing_map_utils.c
#include "../../headers/cub3d.h"

static bool is_valid_character(char c)
{
    if (c == '0' || c == '1' | c == 'N' || c == 'S'
        || c == 'E' || c == 'W' || c == ' ')
        return (true);
    return (false);
}

/**
 * @brief Checks if a given line is empty or contains only whitespace characters.
 *
 * This function iterates through the characters of the provided line and checks
 * if all characters are either spaces or newline characters. If the line contains
 * only these characters or is completely empty, the function returns true.
 *
 * @param line The line to be checked.
 * @return true if the line is empty or contains only whitespace characters, false otherwise.
 */
bool check_if_empty_line(char *line) // ! might be problematic
{
    size_t i;

    i = 0;
    if (!line)
        return (true);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && (line[i] < 9 || line[i] > 13) && line[i] != '\n')
            return (false);
        i++;
    }
    return (true);
}

/**
 * @brief Checks if a given line is valid according to specific rules.
 *
 * This function verifies if the provided line contains only valid characters
 * and ensures that no map content characters appear after an empty line has been found.
 *
 * @param tracker A pointer to a t_tracker structure that keeps track of parsing state.
 * @param line A string representing the line to be checked.
 * @return true if the line is valid, false otherwise.
 */
bool check_if_valid(t_tracker *tracker, char *line)
{
    int i;

    i = 0;
    if (!tracker || !line)
        return (false);
    while (line[i])
    {
        if (!ft_strchr(VALID_MAP_CHARS, line[i]))
            return (false);
        if (ft_strchr(MAP_CONTENT_CHARS, line[i]) && tracker->found_empty_line)
            return (false);
        i++;
    }
    tracker->found_empty_line = check_if_empty_line(line);
    return (true);
}

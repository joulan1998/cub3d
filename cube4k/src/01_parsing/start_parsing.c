//start_parsing.c
#include "../../headers/cub3d.h"

static bool validate_map_content(t_params *params)
{
    int i;
    int j;
    int size;

    i = 0;  // Changed from 1 to 0 to check all lines
    size = arr_len(params->map);
    while (i < size)
    {
        j = 0;
        // Skip leading spaces
        while (params->map[i][j] && params->map[i][j] == ' ')
            j++;
        // Check if first non-space char is '1'
        if (params->map[i][j] != '1')
            return (false);
        // Check last non-space char is '1'
        j = ft_strlen(params->map[i]) - 1;
        while (j >= 0 && params->map[i][j] == ' ')
            j--;
        if (params->map[i][j] != '1')
            return (false);
        i++;
    }
    return (true);
}

static bool validate_horizontal_borders(t_params *params)
{
    int i;
    int j;

    i = 0;
    while (params->map[0][i])
    {
        if (!ft_isspace(params->map[0][i]) && params->map[0][i] != '1') // ~ We check if the only characters in the first line are spaces or walls
            return (print_message(PARSING_ERROR, INVALID_MAP), false);
        i++;
    }
    j = arr_len(params->map) - 1; // ~ the last line in the map
    i = 0;
    while (params->map[j][i])
    {
        if (!ft_isspace(params->map[j][i]) && params->map[j][i] != '1') // ~ We check if the only characters in the last line are spaces or walls
            return (print_message(PARSING_ERROR, INVALID_MAP), false);
        i++;
    }
    return (true);
}

static bool found_player_position(char *map_line)
{
    if (ft_strchr(map_line, 'N') || ft_strchr(map_line, 'S')
        || ft_strchr(map_line, 'E') || ft_strchr(map_line, 'W'))
        return (true);
    return (false);
}

bool is_valid_player(char **map)
{
    t_tracker tracker;
    int i;

    ft_memset(&tracker, 0, sizeof(t_tracker));
    i = 0;
    while (map[i])
    {
        if (found_player_position(map[i]) == true) // ~ if we find the player
        {
            if (tracker.found_the_player == true) // ~ if we already found the player
                return (print_message(PARSING_ERROR, MULTIPLE_PLAYERS), false);
            tracker.found_the_player = true;
        }
        i++;
    }
    return (tracker.found_the_player);
}

bool is_valid_map(t_params *params)
{
    int i;
    int j;
    bool valid;

    if (arr_len(params->map) < 3) // todo: free the params if false
        return (print_message(PARSING_ERROR, INVALID_MAP), false);
    if (is_valid_player(params->map) == false) // ~ We validate that there is only one player in the map
        return (print_message(PARSING_ERROR, INVALID_PLAYER), false);
    if (validate_horizontal_borders(params) == false)
        return (print_message(PARSING_ERROR, INVALID_MAP_BORDERS), false);
    if (validate_map_content(params) == false)
        return (print_message(PARSING_ERROR, INVALID_MAP_CONTENT), false);
    return (true);
}

bool    parser(t_params *params, char *map_file)
{
    int     fd;
    char *line;
    t_tracker tracker;
    bool extracted;
    t_map *map;

    map = NULL;
    ft_memset(&tracker, 0, sizeof(tracker)); //? initialize tracker struct with 0s
    fd = open(map_file, O_RDONLY);
    if (fd == -1)
        return (print_message(OPEN_ERROR, map_file), false);
    line = get_next_line(fd);
    while (line) // ~ We read the configuration file and try to parse it
    {
        if (parse_file_line(line, &tracker, params) == true)
            if (parse_map_line(line, &map, &tracker, params) == false) // ~ if one of the parameters is missing before the map line we return false
                return (ft_cleanlst(&map), free(line), false); // ! we exit here even tho the map is good
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    if (tracker.found_the_map == false) // ~ If we didn't find the map
        return (print_message(PARSING_ERROR, INVALID_MAP), false);
    extracted = extract_cleaned_map(params, &map); // ~ We extract the cleaned map from the linked list
    if (extracted == false)
        return (print_message(PARSING_ERROR, "Extraction Error"), false);
    return (is_valid_map(params));
}

#include "../../headers/cub3d.h"

static bool found_player_position(char *map_line)
{
    if (ft_strchr(map_line, 'N') || ft_strchr(map_line, 'S')
        || ft_strchr(map_line, 'E') || ft_strchr(map_line, 'W'))
        return (true);
    return (false);
}

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
        if (params->map[0][i] != '1') // ~ We check if the only characters in the first line are spaces or walls
            return (false);
        i++;
    }
    j = arr_len(params->map) - 1; // ~ the last line in the map
    i = 0;
    while (params->map[j][i])
    {
        if (params->map[j][i] != '1') // ~ We check if the only characters in the last line are spaces or walls
            return (false);
        i++;
    }
    return (true);
}

bool is_valid_player(char **map)
{
    // ? wtf, why do we create a new tracker here
    bool found_the_player;
    int i;

    i = 0;
    while (map[i])
    {
        if (found_player_position(map[i]) == true) // ~ if we find the player
        {
            if (found_the_player == true) // ~ if we already found the player
                return (print_message(PARSING_ERROR, MULTIPLE_PLAYERS), false);
            found_the_player = true;
        }
        i++;
    }
    return (found_the_player);
}

/**
 * @brief Checks a segment of the map for validity.
 *
 * This function iterates over a segment of the map defined by the parameters
 * and checks if the segment is valid. A segment is considered invalid if it
 * contains the character '0' or if a player position is found in the row.
 *
 * @param params Pointer to the parameters structure containing the map.
 * @param i Index of the row in the map to check.
 * @param start Starting index of the segment to check.
 * @param len_curr Length of the current segment to check.
 * @return true if the segment is valid, false otherwise.
 */
static bool check_segment(t_params *params, int i, size_t start, size_t len_curr)
{
    size_t  j;

    j = start;
    while (j < len_curr && j < start)
        j++;
    while (j < len_curr)
    {
        if (params->map[i][j] == '0'
            || (found_player_position(params->map[i])))
            return (false);
        j++;
    }
    return (true);
}

static bool check_extended_zeros(t_params *params)
{
    int     i;
    size_t  len_prev;
    size_t  len_curr;
    size_t  len_next;

    int size = arr_len(params->map);
    i = 1;
    while (i < size - 1)
    {
        len_prev = ft_strlen(params->map[i - 1]);
        len_curr = ft_strlen(params->map[i]);
        len_next = ft_strlen(params->map[i + 1]);
        if (len_curr > len_prev || len_curr > len_next)
        {
            if (len_curr > len_prev)
                if (!check_segment(params, i, len_prev, len_curr))
                    return (false);
            if (len_curr > len_next)
                if (!check_segment(params, i, len_next, len_curr))
                    return (false);
        }
        i++;
    }
    return (true);
}

/**
 * @brief Validates that a texture file exists and can be opened.
 *
 * Checks the file extension and attempts to open the file in read-only mode.
 *
 * @param texture The texture file path to validate.
 * @return true if the file has a .xpm extension and can be opened, false otherwise.
 */
 static bool validate_texture_file(char *texture)
 {
     int fd;
    
     if (!is_valid_file_extension(texture, ".xpm"))
         return (print_message(PARSING_ERROR, INVALID_TEXTURE_EXT), false);
     fd = open(texture, O_RDONLY);
     if (fd == -1)
         return (print_message(PARSING_ERROR, INVALID_TEXTURE_FILE), false);
     close(fd);
     return (true);
 }
 
 /**
  * @brief Validates all texture files in the params structure.
  *
  * Ensures each texture (NO, SO, WE, EA) has a .xpm extension and can be opened.
  *
  * @param params Pointer to the t_params structure containing texture paths.
  * @return true if all textures are valid, false otherwise.
  */
bool validate_textures(t_params *params)
{
    if (!validate_texture_file(params->no_texture))
        return (false);
    if (!validate_texture_file(params->so_texture))
        return (false);
    if (!validate_texture_file(params->we_texture))
        return (false);
    if (!validate_texture_file(params->ea_texture))
        return (false);
    return (true);
}

bool is_valid_map(t_params *params)
{
    int i;
    int j;
    bool valid;

    // ! why do we check for only 3 lines in the map?
    if (arr_len(params->map) < 3) // todo: free the params if false
        return (print_message(PARSING_ERROR, INVALID_MAP), false);
    if (validate_textures(params) == false)
        return (false);
    if (is_valid_player(params->map) == false) // ~ We validate that there is only one player in the map
        return (print_message(PARSING_ERROR, INVALID_PLAYER), false);
    if (validate_horizontal_borders(params) == false)
        return (print_message(PARSING_ERROR, INVALID_MAP_BORDERS), false);
    if (validate_map_content(params) == false)
        return (print_message(PARSING_ERROR, INVALID_MAP_CONTENT), false);
    // here we need to check for outilers and also count the width of the map
    if (check_extended_zeros(params) == false)
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
        {
            if (parse_map_line(line, &map, &tracker, params) == false) // ~ if one of the parameters is missing before the map line we return false
                return (ft_cleanlst(&map), free(line), false);
        }
        else
        {
            if (tracker.found_unkown == true)
                return (print_message(PARSING_ERROR, UNKOWN_OBJECT), free(line), close(fd), ft_cleanlst(&map), false);
            else if (tracker.found_duplicate == true)
                return (print_message(PARSING_ERROR, FOUND_DUPLICATE), free(line), close(fd), ft_cleanlst(&map), false);
        }
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

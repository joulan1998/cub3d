//parsing_map.c
#include "../../headers/cub3d.h"

// todo: recode the logic for these functions
/**
 * @brief Parses a texture line and updates the corresponding texture parameter and tracker.
 *
 * This function takes an index `i`, a pointer to `t_params`, a pointer to `t_tracker`, and a 
 * split line array `splited_line`. Depending on the value of `i`, it sets the appropriate 
 * texture parameter in `params` and marks the corresponding tracker as true.
 *
 * @param i The index indicating which texture to parse (1 for NO, 2 for SO, 3 for WE, 4 for EA).
 * @param params A pointer to the `t_params` structure where the texture paths are stored.
 * @param tracker A pointer to the `t_tracker` structure used to track which textures have been set.
 * @param splited_line An array of strings representing the split line containing the texture information.
 */
static void parse_texture_line(int i, t_params *params, t_tracker *tracker, char **splited_line)
{
    // todo: make it validate the path of the texture file here
    if (i == 1)
    {
        tracker->no_tracker = true;
        params->no_texture = ft_strtrim(splited_line[1], "\n");
    }
    else if (i == 2)
    {
        tracker->so_tracker = true;
        params->so_texture = ft_strtrim(splited_line[1], "\n");
    }
    else if (i == 3)
    {
        tracker->we_tracker = true;
        params->we_texture = ft_strtrim(splited_line[1], "\n");
    }
    else if (i == 4)
    {
        tracker->ea_tracker = true;
        params->ea_texture = ft_strtrim(splited_line[1], "\n");
    }
}
/**
 * @brief Parses a line of the map configuration file and updates the parameters and tracker accordingly.
 *
 * This function checks the first element of the split line to determine the type of configuration line.
 * Depending on the type, it calls the appropriate parsing function or updates the tracker and parameters.
 *
 * @param params Pointer to the parameters structure to be updated.
 * @param tracker Pointer to the tracker structure to be updated.
 * @param splited_line Array of strings representing the split line to be parsed.
 *
 * The function handles the following types of lines:
 * - "NO": Calls parse_texture_line with texture type 1.
 * - "SO": Calls parse_texture_line with texture type 2.
 * - "WE": Calls parse_texture_line with texture type 3.
 * - "EA": Calls parse_texture_line with texture type 4.
 * - "F": Updates the floor color in params and sets floor_tracker to true in tracker.
 * - "C": Updates the ceiling color in params and sets ceiling_tracker to true in tracker.
 * - Lines starting with '1': Sets found_the_map to true in tracker.
 */

static void parse_param_line(t_params *params, t_tracker *tracker, char **splited_line)
{
    if (ft_strcmp(splited_line[0], "NO") == 0)
        parse_texture_line(1, params, tracker, splited_line);
    else if (ft_strcmp(splited_line[0], "SO") == 0)
        parse_texture_line(2, params, tracker, splited_line);
    else if (ft_strcmp(splited_line[0], "WE") == 0)
        parse_texture_line(3, params, tracker, splited_line);
    else if (ft_strcmp(splited_line[0], "EA") == 0)
        parse_texture_line(4, params, tracker, splited_line);
    else if (ft_strcmp(splited_line[0], "F") == 0)
    {
        tracker->floor_tracker = true;
        params->floor_color = parse_color(splited_line);
    }
    else if (ft_strcmp(splited_line[0], "C") == 0)
    {
        tracker->ceiling_tracker = true;
        params->ceiling_color = parse_color(splited_line);
    }
    else if (splited_line[0][0] == '1')
        tracker->found_the_map = true;
}

/**
 * @brief Checks if the map is fully parsed and valid, then processes the map line.
 *
 * This function performs several checks to ensure that the map parsing is complete and valid.
 * It verifies if all required parameters have been tracked, checks the validity of the current line,
 * and adds the line to the map if it is not empty.
 *
 * @param line The current line being processed.
 * @param map A double pointer to the map structure.
 * @param tracker A pointer to the tracker structure containing flags for required parameters.
 * @param params A pointer to the parameters structure (not used in the current implementation).
 * 
 * @return Returns false if any required parameter is missing, if the line is invalid, or if an error occurs.
 *         Otherwise, it returns nothing (void).
 */
bool parse_map_line(char *line, t_map **map, t_tracker *tracker, t_params *params)
{
    static int counter = 0;
    if (params->ceiling_color == -1 || params->floor_color == -1)
        return (print_message(PARSING_ERROR, RGB_ERROR), false);
    if (tracker->no_tracker == false || tracker->so_tracker == false
        || tracker->we_tracker == false || tracker->ea_tracker == false
        || tracker->floor_tracker == false || tracker->ceiling_tracker == false) // ~ We check if all required parameters are tracked
        return (print_message(PARSING_ERROR, MAP_ORDER_ERROR), false);
    if (check_if_valid(tracker, line) == false) // ~ We check if the line is valid
        return (print_message(PARSING_ERROR, INVALID_MAP), false); // todo: test the function in this condition again cuz it looks sus
    if (check_if_empty_line(line) == false) // ~ If the line isn't empty
        ft_addlst(map, ft_createlst(line)); // ~ We make a new node and add it to the map list
    // else if (check_if_empty_line(line) == true && tracker->found_the_map == true)
    //     return (false);
    counter++;
    return (true);
}

/**
 * @brief Extracts and cleans the map from the linked list and stores it in the params structure.
 *
 * This function takes a linked list of map lines, trims each line, and stores the cleaned lines
 * in the params structure. It also handles memory allocation for the map array in the params structure.
 *
 * @param params A pointer to the t_params structure where the cleaned map will be stored.
 * @param map A double pointer to the linked list of map lines to be cleaned and extracted.
 * @return true if the map was successfully extracted and cleaned, false otherwise.
 */
bool extract_cleaned_map(t_params *params, t_map **map)
{
    int i;
    int size;
    t_map *current;

    i = 0;
    size = ft_sizelst(*map);
    if (size <= 0)
        return (ft_cleanlst(map), printf(INVALID_MAP), false);
    params->map = malloc((size + 1) * sizeof(char *));
    if (!params->map)
        return (ft_cleanlst(map), printf(MALLOC_ERROR), false);
    params->map_height = size;
    current = *map;
    while (i < size && current != NULL)
    {
        params->map[i] = ft_strdup(current->line); // todo: handle segv here
        current = current->next;
        i++;
    }
    params->map[i] = NULL;
    return (ft_cleanlst(map), true); // todo: free current before exiting
}

/**
 * @brief Handles parsing of color lines (F and C) from the map file.
 *
 * Processes lines starting with "F " or "C ", joining RGB components into a single
 * string and passing it to parse_param_line for further processing.
 *
 * @param line The line to parse.
 * @param tracker Tracker structure for parsing state.
 * @param params Parameters structure to update.
 * @param splited_line Split line array.
 * @return true if parsing succeeds or should continue, false on error.
 */
static bool parse_color_line(char *line, t_tracker *tracker, t_params *params,
char **splited_line)
{
    char *rgb_str;
    char *temp;
    int i;

    if (arr_len(splited_line) < 2)
        return (free_strings(splited_line), false);
    rgb_str = ft_strdup(splited_line[1]);
    i = 2;
    while (i < arr_len(splited_line))
    {
        temp = rgb_str;
        rgb_str = ft_strjoin(rgb_str, splited_line[i]);
        free(temp);
        i++;
    }
    free(splited_line[1]);
    splited_line[1] = rgb_str;
    parse_param_line(params, tracker, splited_line);
    free_strings(splited_line);
    return (tracker->found_the_map);
}

/**
* @brief Handles parsing of texture lines or map start.
*
* Processes lines for textures (NO, SO, WE, EA) or the start of the map (lines
* starting with '1'), ensuring they have exactly two tokens unless it's a map line.
*
* @param line The line to parse.
* @param tracker Tracker structure for parsing state.
* @param params Parameters structure to update.
* @return true if parsing succeeds or should continue, false on error.
*/
static bool parse_texture_or_map(char *line, t_tracker *tracker, t_params *params)
{
    char **splited_line;

    splited_line = ft_split(line, ' ');
    if (splited_line == NULL)
        return (printf(SPLIT_FAILED), false);
    if (arr_len(splited_line) != 2 && splited_line[0][0] != '1')
        return (free_strings(splited_line), false);
    parse_param_line(params, tracker, splited_line);
    free_strings(splited_line);
    return (tracker->found_the_map);
}

/**
* @brief Parses a line from the map file and updates tracker and params.
*
* Processes a single line, skipping empty lines appropriately, and delegates to
* specific handlers for color lines or texture/map lines based on content.
*
* @param line The line to be parsed.
* @param tracker Tracker structure for parsing state.
* @param params Parameters structure to update.
* @return true if line is parsed or skipped successfully, false on error.
*/
bool parse_file_line(char *line, t_tracker *tracker, t_params *params)
{
    char **splited_line;

    if (line[0] == '\n' && tracker->found_the_map == true)
        return (true);
    if (line[0] == '\n')
        return (false);
    if (tracker->found_the_map == true)
        return (true);
    if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
    {
        splited_line = ft_split(line, ' ');
        return (parse_color_line(line, tracker, params, splited_line));
    }
    return (parse_texture_or_map(line, tracker, params));
}

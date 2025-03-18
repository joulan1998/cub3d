//parsing_map_colors.c
#include "../../headers/cub3d.h"

static int count_commas(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == ',')
            count++;
        i++;
    }
    return (count);
}

/**
 * @brief Converts an array of RGB string values to an ARGB integer.
 *
 * This function takes an array of strings representing RGB values and converts them to an integer
 * in the ARGB format. The alpha value is set to 255 (fully opaque).
 *
 * @param rgb An array of strings representing the RGB values. The array must contain exactly 3 elements.
 * @param splited_line An array of strings representing the split line (not used in this function).
 * @return The ARGB integer value if the conversion is successful, or -1 if there is an error.
 *
 * @note The function checks if the RGB values are within the valid range (0-255). If the array does not
 *       contain exactly 3 elements or if any value is out of range, an error message is printed and -1 is returned.
 */
static int convert_rgb(char **rgb, char **splited_line)
{
    int r, g, b;

    if (arr_len(rgb) != 3)
        return (/*print_message(PARSING_ERROR, RGB_ERROR),*/ -1);
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (/*print_message(PARSING_ERROR, RGB_ERROR),*/ -1);
    return (r << 24 | g << 16 | b << 8 | 255);
}

/**
 * @brief Parses a color from a given line.
 *
 * This function takes a line that is expected to contain RGB color values
 * separated by commas, trims any newline characters, splits the line into
 * individual RGB components, and converts these components into a single
 * integer color value.
 *
 * @param splited_line A double pointer to the line containing the RGB values.
 *                     The line is expected to be split into tokens, where the
 *                     second token contains the RGB values.
 * 
 * @return The integer representation of the color if successful, or -1 if an
 *         error occurs. Possible errors include:
 *         - Incorrect number of commas in the line.
 *         - Failure to split the line into RGB components.
 *         - Failure to convert the RGB components into a color.
 */
int parse_color(char **splited_line)
{
    char **rgb;
    int  color;
    char *trimmed_line;
    int commas_counter;

    trimmed_line = ft_strtrim(splited_line[1], "\n"); // Trim newline from RGB string
    commas_counter = count_commas(trimmed_line);
    if (commas_counter != 2) // Check for exactly 2 commas
        return (/*print_message(PARSING_ERROR, RGB_ERROR),*/ -1);
    rgb = ft_split(trimmed_line, ','); // Split by commas
    if (!rgb)
        return (print_message(PARSING_ERROR, SPLIT_FAILED), -1);
    
    color = convert_rgb(rgb, splited_line);
    free_strings(rgb);
    free(trimmed_line);
    return (color);
}

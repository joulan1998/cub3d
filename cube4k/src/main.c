# include "../headers/cub3d.h"

bool init_and_parse(t_params **params, char *filepath)
{
    if (is_valid_file_extension(filepath, ".cub") == false)
        return (print_message(INVALID_FILE_EXTENSION, filepath), false);
    if (is_valid_path(filepath) == false)
        return (print_message(INVALID_PATH, filepath), false);
    *params = malloc(sizeof(t_params));
    if (!(*params))
        return (print_message(PARSING_ERROR, MALLOC_ERROR), false);
    init_params(*params);
    if (parser(*params, filepath) == false)
        return (free_params(*params), *params = NULL, false);
    return (true);
}

int main(int argc, char **argv)
{
    t_params *params;

    if (argc != 2)
        return (printf(INVALID_NBR_ARGS), EXIT_FAILURE);
    if (init_and_parse(&params, argv[1]) == false)
        return (EXIT_FAILURE);

    // render here
    
    free_params(params);
    return (EXIT_SUCCESS);
}

# include "../headers/cub3d.h"
void print_parsed_to_file(t_params *params)
{
	int i = 0;

	if (!params)
	{
		printf(PARSING_ERROR);
		return ;
	}
	printf("================================================== Map ==================================================\n");
	printf("north texture: %s\n", params->no_texture);
	printf("south texture: %s\n", params->so_texture);
	printf("West Texture: %s\n", params->we_texture);
	printf("East Texture: %s\n", params->ea_texture);
	printf("\n");
	printf("Floor Color: %d\n", params->floor_color);
	printf("Ceiling Color: %d\n", params->ceiling_color);
	printf("\n");
	printf("map_width: %lu\n", params->map_width);
	printf("Map Height: %lu\n", params->map_height);
	printf("\n");

	while (params->map && params->map[i])
	{
		printf("%s\n", params->map[i++]);
	}
	printf("================================================== Map ==================================================\n");
}

int main(int argc, char **argv)
{
	t_params *params;

	if (argc != 2) // ? We check if the number of arguments is valid
		return (printf(INVALID_NBR_ARGS), EXIT_FAILURE);
	if (is_valid_file_extension(argv[1], ".cub") == false) // ? We check if the file has the correct extension
		return (print_message(INVALID_FILE_EXTENSION, argv[1]), EXIT_FAILURE);
	if (is_valid_path(argv[1]) == true)
	{
		params = malloc(sizeof(t_params));
		if (!params)
			return (printf(MALLOC_ERROR), EXIT_FAILURE);
		init_params(params); // ? We intiialize the params struct with NULL/Error values
		if (parser(params, argv[1]) == false)  // ? We parse the map file and store the values in the params struct
			return (/*print_parsed_to_file(params), */free_params(params), EXIT_FAILURE);
		print_parsed_to_file(params);
		// todo: render here
		free_params(params);
	}
	else
		return (print_message(INVALID_PATH, argv[1]), EXIT_FAILURE);
}


// todo: filename with spaces shouldn't be trimmed UwU 
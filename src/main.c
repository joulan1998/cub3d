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
	printf("north texture: [%s]\n", params->no_texture);
	printf("south texture: [%s]\n", params->so_texture);
	printf("West Texture: [%s]\n", params->we_texture);
	printf("East Texture: [%s]\n", params->ea_texture);
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
	t_params 	*params;
	t_player	*player;
	t_root		*root;
	void		*mlx;
	void		*win;

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
		// ~ rendering code here
		player = malloc(sizeof (t_player));
		if (!player)
			printf("allocation for payer error\n");
		root = malloc(sizeof (t_root));
		if (!root)
			printf("allocation for payer error\n");
		set_player(player);
		initialize_data(root, params, player);
		free_params(params);
		update (&root);
		mlx_key_hook(root->win, move_player, root);
		mlx_loop(root->mlx);
		free_params(params);
	}
	else
		return (print_message(INVALID_PATH, argv[1]), EXIT_FAILURE);
}

// int main()
// {
// 	char *line = "WE              assets/             textures/texture.xpm";
// 	char **splited_line = split_two(line);

// 	int i = 0;

// 	if (!splited_line)
// 	{
// 		printf("NULL\n");
// 		return (0);
// 	}
// 	while (splited_line[i])
// 	{
// 		printf("%s\n", splited_line[i]);
// 		i++;
// 	}
// 	return (0);
// }

// todo: filename with spaces shouldn't be trimmed UwU 
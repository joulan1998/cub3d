/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:51:12 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/21 17:19:59 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void f()
{
	system("leaks cub3D");
}

int	check_wall(int y, int x, char **map)
{
	return ((map[y][x] == WALL));
}

int	set_player(t_player *p)
{
	p->player_x = (int *)malloc(sizeof(int));
	p->player_y = (int *)malloc(sizeof(int));
	if (!p || !p->player_x || !p->player_y)
	{
		ft_err("error allocation!", 1);
		return (1);
	}
	p->walkspeed = 100;
	p->turnspeed = 45 * (M_PI / 180);
	*p->player_x = 0;
	*p->player_y = 0;
	p->turndir = 0;
	p->walkdir = 0;
	p->rot_angl = M_PI / 1;
	return (0);
}

bool	init_and_parse(t_params **params, char *filepath)
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

int	main(int argc, char **argv)
{
	t_params	*params;
	t_player	*player;
	t_root		*root;

	atexit(f);
	
	if (argc != 2)
		return (printf(INVALID_NBR_ARGS), EXIT_FAILURE);
	if (init_and_parse(&params, argv[1]) == false)
		return (EXIT_FAILURE);
	player = malloc(sizeof (t_player));
	root = malloc(sizeof (t_root));
	if (!player || !root)
		printf("allocation error\n");
	if (set_player(player))
		return(free(root), free (player), 1);
	initialize_data(root, params, player);
	free_params(params);
	update (&root);
	mlx_key_hook(root->win, move_player, root);
	// exit(5);
	mlx_loop(root->mlx);
	return (0);
}

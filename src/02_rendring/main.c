/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:51:12 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/18 16:03:07 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../headers/cub3d.h"

void f()
{
	system("leaks cub3D");
}
int	check_wall(int y, int x, char **map)
{
	return ((map[y][x] == WALL));
}

void	set_player(t_player *p)
{
	p->player_x = (int *)malloc(sizeof(int));
	p->player_y = (int *)malloc(sizeof(int));
	if (!p || !p->player_x || !p->player_y) // ! leak here if one of them is allocated sucessfully and one isn't
	{
		puts("error allocation!");
		exit(1);
	}
	p->walkspeed = 100;
	p->turnspeed = 45 * (M_PI / 180);
	*p->player_x = 0;
	*p->player_y = 0;
	p->turndir = 0;
	p->walkdir = 0;
	p->rot_angl = M_PI / 1;
}

int	main()
{
	t_player	*player;
	t_root		*root;
	void		*mlx;
	void		*win;
	//int			fd;
	char		**map;

	atexit(f);
	player = malloc(sizeof (t_player));
	if (!player)
		puts("allocation for payer error\n");// invalid function
	root = malloc(sizeof (t_root));
	//fd = open("./map.txt", O_RDONLY, 0);
	//map = reading_map (fd);
	set_player(player);
	initialize_data(root, &map, player);
	update (&root);
	mlx_key_hook(root->win, move_player, root);
	mlx_loop(root->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:51:12 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/11 13:16:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	check_wall(int y, int x, char **map)
{
	return ((map[y][x] == WALL));
}

void	set_player(t_player *p)
{
	p->player_x = (int *)malloc(sizeof(int));
	p->player_y = (int *)malloc(sizeof(int));
	if (!p || !p->player_x || !p->player_y)
	{
		puts("error allocation!");
		exit(1);
	}
	p->walkSpeed = 100;
	p->turnSpeed = 45 * (M_PI / 180);
	*p->player_x = 0;
	*p->player_y = 0;
	p->turnDir = 0;
	p->walkDir = 0;
	p->rotationAngle = M_PI / 2;
}

int	main()
{
	t_player	*player;
	t_root		*root;
	int			fd;
	void		*mlx;
	void		*win;
	char		**map;

	player = malloc(sizeof (t_player));
	if (!player)
		puts("allocation for payer error\n");
	root = malloc(sizeof (t_root));
	fd = open("./map.txt", O_RDONLY, 0);
	map = reading_map (fd);
	set_player(player);
	initialize_data(root, &map, player);
	update (&root);
	mlx_key_hook(root->win, move_player, root);
	mlx_loop(root->mlx);
	return (0);
}

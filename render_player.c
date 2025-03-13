/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:38:46 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/13 15:20:25 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	render_player(t_root *root)
{
	draw_circle(root, create_pos((float)*(root->player->player_x) * SCALE,
			(float)*(root->player->player_y) * SCALE), RED, 2);
}

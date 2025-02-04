/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:38:46 by ael-garr          #+#    #+#             */
/*   Updated: 2025/02/03 17:25:39 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	render_player(t_root *root)
{
	draw_circle(root, *(root->player->player_y) * SCALE,
		*(root->player->player_x) * SCALE, RED, 2);
}

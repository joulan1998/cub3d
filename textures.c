/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:17:01 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/24 21:31:00 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	load_xpm_texture(void *mlx, char *texture_path, t_mlx *texture)
{
	texture->img = mlx_xpm_file_to_image
		(mlx, texture_path, &texture->width, &texture->height);
	if (!texture->img)
	{
		ft_err("Error: Failed to load texture from ", 1);
		ft_err(texture_path, 1);
		ft_err("\n", 1);
		return (1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		ft_err("Error: Failed to get texture data address\n", 0);
		mlx_destroy_image(mlx, texture->img);
		return (1);
	}
	return (1);
}

int	get_texture_pixel(t_mlx *texture, int tex_x, int tex_y)
{
	int	pixel_index;

	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0);
	pixel_index = (tex_y * texture->line_length)
		+ (tex_x * (texture->bits_per_pixel / 8));
	return (*(int *)(texture->addr + pixel_index));
}

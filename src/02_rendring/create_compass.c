/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_compass.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:25:35 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/18 16:01:36 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../headers/cub3d.h"

t_compass	*create_compass(bool f_u, bool f_d, bool f_r, bool f_l)
{
	t_compass	*result;

	result = (t_compass *)malloc(sizeof(t_compass) * 1);
	if (!result)
		return (NULL);
	result->f_u = f_u;
	result->f_d = f_d;
	result->f_r = f_r;
	result->f_l = f_l;
	return (result);
}

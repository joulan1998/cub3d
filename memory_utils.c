/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:48:44 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/21 17:16:39 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	free_params(t_params *params)
{
	if (!params)
		return ;
	// free(params->so_texture);
	// free(params->no_texture);
	// free(params->we_texture);
	// free(params->ea_texture);
	printf("######## >>> %p\n", &params->map[0]);
	// free_strings(params->map);
	// free(params);
}

void	free_strings(char **strings)
{
	int	i;

	if (!strings)
		return ;
	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

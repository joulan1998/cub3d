/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:29:35 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/24 21:29:41 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h" // For strdup

void	immegrate_map(char ***to, char ***from)
{
	int	i;

	i = 0;
	if (!from || !*from)
	{
		*to = NULL;
		return ;
	}
	while ((*from)[i])
		i++;
	*to = (char **)malloc((i + 1) * sizeof(char *));
	if (!*to)
		return ;
	i = 0;
	while ((*from)[i])
	{
		(*to)[i] = ft_strdup((*from)[i]);
		i++;
	}
	(*to)[i] = NULL;
}

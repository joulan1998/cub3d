/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:21:31 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/21 15:35:39 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	ft_err(char *msg, int to_return)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
	return (to_return);
}

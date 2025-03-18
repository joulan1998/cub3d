/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:48:05 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/11 09:34:53 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_environ	*ft_lstnew_env(char *var, char *value)
{
	t_environ	*ptr;

	ptr = malloc (sizeof(t_environ));
	if (!ptr && !var)
		return (NULL);
	ptr->var = var;
	if (value == NULL)
		ptr->value = NULL;
	else
		ptr->value = value;
	ptr->next = NULL;
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:45:09 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 14:48:33 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

t_map	*ft_createlst(char *line)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		return (print_message(PARSING_ERROR, MALLOC_ERROR), NULL);
	node->line = ft_strtrim(line, "\n");
	node->next = NULL;
	return (node);
}

void	ft_addlst(t_map **head, t_map *node)
{
	t_map	*current;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
}

int	ft_sizelst(t_map *head)
{
	int		i;
	t_map	*current;

	if (!head)
		return (0);
	i = 0;
	current = head;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	ft_cleanlst(t_map **head)
{
	t_map	*current;
	t_map	*tmp;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->line);
		free(tmp);
	}
	head = NULL;
}

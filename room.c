/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:37:43 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/28 20:53:37 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	new(t_rooms *last, char **tmp)
{
	t_rooms *new;

	if (!(new = malloc(sizeof(t_rooms))))
	{
		ft_putstr_fd("Memory allocation failed", 2);
		exit(0);
	}
	new->name = ft_strdup(tmp[0]);
	new->coord_x = ft_atoi(tmp[1]);
	new->coord_y = ft_atoi(tmp[2]);
	new->next = NULL;
	if (!last)
		last = new;
	else
		last->next = new;
}

/*
** Seeing if coordinates correspond to another room already. If yes, it changes
** its name.
*/

int		to_check(t_rooms **begin, char **tmp)
{
	t_rooms *lst;

	lst = *begin;
	while (lst)
	{
		if (lst->coord_x == ft_atoi(tmp[1]) && lst->coord_y == ft_atoi(tmp[2]))
		{
			lst->name = ft_strdup(tmp[0]);
			return (1);
		}
		if (lst->name == tmp[0])
		{
			lst->coord_x = ft_atoi(tmp[1]);
			lst->coord_y = ft_atoi(tmp[2]);
			return (1);
		}
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	new(lst, tmp);
	return (0);
}

int		room(t_data *data, char *line)
{
	char	**tmp;

	if (!(tmp = ft_strsplit(line, ' ')))
	{
		ft_putstr_fd("Memory allocation failed", 2);
		exit(0);
	}
	if (data->start && (data->start == tmp[0] ||
		(data->start_x == ft_atoi(tmp[1]) && data->start_y == ft_atoi(tmp[2]))))
		return (start_end_values(data, tmp, 0));
	if (data->end && (data->end == tmp[0] ||
		(data->end_x == ft_atoi(tmp[1]) && data->end_y == ft_atoi(tmp[2]))))
		return (start_end_values(data, tmp, 1));
	to_check(&data->rooms, tmp);
	free(tmp);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:37:43 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/10 14:54:31 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int			len_tab(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
		i++;
	return (i);
}

void		new(t_rooms *last, char **tmp, t_data *data, int i)
{
	t_rooms *new;

	if (!(new = malloc(sizeof(t_rooms))))
		error(data, MEM);
	if (i == 1 || i == 2)
		data->start = new;
	if (i == 0 || i == 2)
		data->end = new;
	new->name = ft_strdup(tmp[0]);
	new->coord_x = ft_atoi(tmp[1]);
	new->coord_y = ft_atoi(tmp[2]);
	new->i_end = -1;
	new->i_start = -1;
	new->ant = 0;
	new->order = 0;
	new->links = NULL;
	new->next = NULL;
	if (!last)
		data->rooms = new;
	else
		last->next = new;
}

/*
** Seeing if coordinates correspond to another room already. If yes, it changes
** its name.
*/

void		to_check(t_data *data, char **tmp, int i)
{
	t_rooms *lst;

	lst = data->rooms;
	while (lst)
	{
		if (lst->coord_x == ft_atoi(tmp[1]) && lst->coord_y == ft_atoi(tmp[2]))
		{
			lst->name = ft_strdup(tmp[0]);
			data->start = (i == 1 || i == 2) ? lst : data->start;
			data->end = (i == 0 || i == 2) ? lst : data->end;
			return ;
		}
		if (!ft_strcmp(lst->name, tmp[0]))
		{
			lst->coord_x = ft_atoi(tmp[1]);
			lst->coord_y = ft_atoi(tmp[2]);
			data->start = (i == 1 || i == 2) ? lst : data->start;
			data->end = (i == 0 || i == 2) ? lst : data->end;
			return ;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	new(lst, tmp, data, i);
}

void		free_tab(char **t)
{
	int		i;

	i = -1;
	while (t[++i])
		free(t[i]);
	free(t);
}

int			room(t_data *data, char *line, int i)
{
	char	**tmp;
	int		x;
	int		y;

	x = 1;
	y = 0;
	if (!(tmp = ft_strsplit(line, ' ')))
		error(data, MEM);
	if (tmp[0][0] == 'L' || tmp[0][0] == '#' || data->link || len_tab(tmp) != 3)
		return (0);
	while (x < 3)
	{
		y = 0;
		while (tmp[x][y])
		{
			if (!ft_isdigit(tmp[x][y++]))
				return (0);
		}
		x++;
	}
	to_check(data, tmp, i);
	free_tab(tmp);
	return (1);
}

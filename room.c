/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:37:43 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/31 15:08:19 by edeveze          ###   ########.fr       */
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
		error(MEM);
	if (i == 1 || i == 2)
		data->start = new;
	if (i == 0 || i == 2)
		data->end = new;
	new->name = ft_strdup(tmp[0]);
	new->coord_x = ft_atoi(tmp[1]);
	new->coord_y = ft_atoi(tmp[2]);
	new->indice = -1;
	new->ant = 0;
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
		if (lst->next)
			lst = lst->next;
		else
			break ;
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

	if (!(tmp = ft_strsplit(line, ' ')))
		error(MEM);
	if (tmp[0][0] == 'L'|| len_tab(tmp) != 3)
	{
		data->error = NAME;
		return (0);
	}
	if (len_tab(tmp) != 3)
	{
		data->error = LEN;
		return (0);
	}
	to_check(data, tmp, i);
	free_tab(tmp);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:37:43 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/01 16:09:26 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		len_tab(char **tmp)
{
	int i;

	i = 0;
	while (tmp[i])
		i++;
	return (i);
}

void	new(t_rooms *last, char **tmp, t_data *data, int i)
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

int		to_check(t_data *data, char **tmp, int i)
{
	t_rooms *lst;

	lst = data->rooms;
	while (lst)
	{
		if (lst->coord_x == ft_atoi(tmp[1]) && lst->coord_y == ft_atoi(tmp[2]))
		{
			lst->name = ft_strdup(tmp[0]);
			data->start = (i == 1 || i == 2) ? data->start : lst;
			data->end = (i == 0 || i == 2) ? data->end : lst;
			return (1);
		}
		if (!ft_strcmp(lst->name, tmp[0]))
		{
			lst->coord_x = ft_atoi(tmp[1]);
			lst->coord_y = ft_atoi(tmp[2]);
			data->start = (i == 1 || i == 2) ? lst : data->start;
			data->end = (i == 0 || i == 2) ? lst : data->end;
			return (1);
		}
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	new(lst, tmp, data, i);
	return (0);
}

void	free_tab(char **t)
{
	int i;

	i = -1;
	while (t[++i])
		free(t[i]);
	free(t);
}

int		room(t_data *data, char *line, int i)
{
	char	**tmp;

	if (!(tmp = ft_strsplit(line, ' ')))
		error(MEM);
	if (len_tab(tmp) != 3)
		return (0);
	// verif tmp
	to_check(data, tmp, i);
	free_tab(tmp);
	return (1);
}

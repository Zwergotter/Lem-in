/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:25:27 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/02 18:42:46 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		addlast_tube(t_data *data, t_tubes *new)
{
	t_tubes	*lst;
	t_rooms *room;
	int		i;
	int		j;

	lst = data->tubes;
	room = data->rooms;
	i = 1;
	j = 1;
	while (room)
	{
		if (!ft_strcmp(new->room1, room->name))
			i = 0;
		if (!ft_strcmp(new->room2, room->name))
			j = 0;
		room = room->next;
	}
	if (i || j)
		return (0);
	if (lst == 0)
	{
		data->tubes = new;
		return (1);
	}
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (1);
}

int		tube(t_data *data, char *line)
{
	int		i;
	int		j;
	t_tubes	*tube;

	i = 0;
	j = 0;
	tube = palloc(sizeof(t_tubes));
	while (line[i] && line[i] != '-')
		i++;
	tube->room1 = ft_strsub(line, 0, i++);
	j = i;
	while (line[j] && line[j] != '-')
		j++;
	if (j == i || line[j] == '-')
		return (0);
	tube->room2 = ft_strsub(line, i, j - i);
	tube->next = NULL;
	if (!ft_strcmp(tube->room1, tube->room2))
		return (0);
	return (addlast_tube(data, tube));
}

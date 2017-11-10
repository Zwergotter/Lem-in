/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:25:27 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/10 23:51:57 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

t_rooms		**realloc_rooms(t_rooms **tab, t_rooms *link)
{
	int		i;
	t_rooms **new;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i] == link)
			return (tab);
		i++;
	}
	new = palloc(sizeof(t_rooms *) * (i + 2));
	i = 0;
	while (tab && tab[i])
	{
		new[i] = tab[i];
		++i;
	}
	new[i] = link;
	new[i + 1] = 0;
	free(tab);
	return (new);
}

void		free_rooms(char *room1, char *room2)
{
	free(room1);
	free(room2);
}

int			giving_links(t_data *data, char *room1, char *room2)
{
	t_rooms *room;
	t_rooms	*first;
	t_rooms	*second;

	room = data->rooms;
	first = NULL;
	second = NULL;
	data->link = 1;
	while (room)
	{
		if (!ft_strcmp(room1, room->name))
			first = room;
		if (!ft_strcmp(room2, room->name))
			second = room;
		room = room->next;
	}
	if (!first || !second)
	{
		free_rooms(room1, room2);
		return (0);
	}
	first->links = realloc_rooms(first->links, second);
	second->links = realloc_rooms(second->links, first);
	free_rooms(room1, room2);
	return (1);
}

int			attributing_rooms(t_data *data, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[j] == ' ')
		j++;
	i = j;
	while (line[i] && line[i] != '-')
		i++;
	if (j == i)
		return (0);
	data->room1 = ft_strsub(line, j, i - j);
	i++;
	j = i;
	while (line[j] && line[j] != '-')
		j++;
	if (j == i || line[j] == '-')
	{
		free(data->room1);
		return (0);
	}
	data->room2 = ft_strsub(line, i, j - i);
	return (1);
}

int			tube(t_data *data, char *line)
{
	if (!attributing_rooms(data, line))
		return (0);
	if (!ft_strcmp(data->room1, data->room2))
	{
		data->link = 1;
		free_rooms(data->room1, data->room2);
		return (1);
	}
	return (giving_links(data, data->room1, data->room2));
}

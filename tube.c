/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:25:27 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/30 17:17:21 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

t_rooms		**realloc_rooms(t_rooms **tab, t_rooms *link)
{
	int 	i;
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
	new[i + 1]  = 0;
	free(tab);
	return (new);
}

int			giving_links(t_data *data, char *room1, char *room2)
{
	t_rooms *room;
	t_rooms	*first;
	t_rooms	*second;

	room = data->rooms;
	first = NULL;
	second = NULL;
	while (room)
	{
		if (!ft_strcmp(room1, room->name))
			first = room;
		if (!ft_strcmp(room2, room->name))
			second = room;
		room = room->next;
	}
	if (!first || !second)
		return (0);
	first->links = realloc_rooms(first->links, second);
	second->links = realloc_rooms(second->links, first);
	free(room1);
	free(room2);
	return (1);
}

int			tube(t_data *data, char *line)
{
	int		i;
	int		j;
	char 	*room1;
	char 	*room2;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '-')
		i++;
	room1 = ft_strsub(line, 0, i++);
	j = i;
	while (line[j] && line[j] != '-')
		j++;
	if (j == i || line[j] == '-')
		return (0);
	room2 = ft_strsub(line, i, j - i);
	if (!ft_strcmp(room1, room2))
	{
		free(room1);
		free(room2);
		return (1);
	}
	return (giving_links(data, room1, room2));
}
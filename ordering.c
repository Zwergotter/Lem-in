/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:50:08 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/06 20:53:49 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	sort_links(t_data *data)
{
	int i;
	t_rooms *tmp;
	t_rooms *room;

	i = -1;
	tmp = data->rooms;
	room = tmp;
	while (tmp)
	{
		i = -1;
		while (tmp->indice > -1 && tmp->links[++i])
		{
			if (tmp->links[i + 1] &&
				tmp->links[i]->order > tmp->links[i + 1]->order)
			{
				room = tmp->links[i];
				tmp->links[i] = tmp->links[i + 1];
				tmp->links[i + 1] = room;
				i = -1;
			}
		}
		tmp = tmp->next;
	}
}

void	ordering_indice(t_data *data)
{
	int  i;
	t_rooms *tmp;

	i = -1;
	tmp = data->rooms;
	while (tmp)
	{
		i = -1;
		while (tmp->indice > -1 && tmp->links[++i])
		{
			if (tmp->links[i]->indice && tmp->links[i]->indice < tmp->indice)
				tmp->order++;
		}
		tmp = tmp->next;
	}
	sort_links(data);
}

void swapping(t_rooms *set, t_rooms *first, t_rooms *second)
{
	set->next = second;
	first->next = first;
	first->next = second->next;
	second->next = first;
}

void	ordering_rooms(t_data *data)
{
	t_rooms *tmp;

	tmp = data->rooms;
	while (tmp->next)
	{
		if (tmp->next->next && tmp->next->order > tmp->next->next->order)
		{
			swapping(tmp, tmp->next, tmp->next->next);
			tmp = data->rooms;
		}
		tmp = tmp->next;
	}
}

void	ordering(t_data *data)
{
	data->start->ant = data->n_ants;
	ordering_indice(data);
	ordering_rooms(data);
}
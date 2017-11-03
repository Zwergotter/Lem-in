/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 21:27:54 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/03 21:26:20 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/lem_in.h"

/*
** Here to display which ant moves to where.
*/

void	one_answer(int ant, char *room, int i)
{
	if (i)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(room);
}

/*
** Special case when we are on start and there's still ants in it.
** Because we can send one or more ants if there's rooms and we still have
** some in start.
*/

int	dispatching_ants(t_data *data, t_rooms *start, int count)
{
	int ant;
	int j;
	int indice;
	
	j = -1;
	indice = start->indice - 2;
	ant = data->n_ants - start->ant + 1;
	while (++indice < data->imax)
	{
		j = -1;
		while (start->links[++j])
		{
			if (start->ant && start->links[j]->indice == indice && !start->links[j]->ant)
			{
				start->links[j]->ant = ant;
				one_answer(ant, start->links[j]->name, count);
				count++;
				start->ant--;
				ant = data->n_ants - start->ant + 1;
			}
		}
	}
	return (0);
}

/*
** A room address is sent. Thanks to this one, we're checking all rooms linked
** to it, trying to find one that is equal to i - 1 and either the linked room
** is the end or there's no ant in, meaning that we can move an ant in it.
*/

int	checking_each(t_data *data, t_rooms *r, int i, int count)
{
	int j;

	j = -1;
	while (r->links[++j])
	{
		if (r->links[j]->indice == i - 1 && r->links[j] != data->start && (r->links[j] == data->end || !(r->links[j]->ant)))
		{
			if (r->links[j] != data->end)
				r->links[j]->ant = r->ant;
			else
				r->links[j]->ant += 1;
			one_answer(r->ant, r->links[j]->name, count);
			count++;
			r->ant = 0;
			return (count);
		}
	}
	return (count);
}

void	final(t_data *data)
{
	int i;
	int count;
	t_rooms *r;

	i = 0;
	count = 0;
	while (i < data->imax)
	{
		i++;
		r = data->rooms;
		while (r)
		{
			if (r->indice == i && r->ant && r != data->start)
				count = checking_each(data, r, i, count);
			r = r->next;
		}
	}
	if (data->start->ant)
		dispatching_ants(data, data->start, count);
	ft_putchar('\n');
}

void	set_indice(t_rooms *r, int i, t_data *data)
{
	int c;

	c = -1;
	while (r->links[++c])
	{
		if (r->links[c]->indice > i || r->links[c]->indice == -1)
		{
			r->links[c]->indice = i;
			if (r->links[c] != data->start)
			{
				set_indice(r->links[c], i + 1, data);
				if (data->imax < i + 1)
					data->imax = i + 1;
			}
		}
	}
}

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
		while (tmp->links[++i])
		{
			if (tmp->links[i + 1] && tmp->links[i]->order > tmp->links[i + 1]->order)
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

void	ordering(t_data *data)
{
	int  i;
	t_rooms *tmp;

	i = -1;
	tmp = data->rooms;
	while (tmp)
	{
		i = -1;
		while(tmp->links[++i])
		{
			if (tmp->links[i]->indice < tmp->indice)
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

void	finish(t_data *data)
{
	int i;

	one_answer(1, data->end->name, 0);
	i = 1;
	while (i != data->n_ants)
	{
		++i;
		one_answer(i, data->end->name, 1);
	}
	ft_putchar('\n');
}

void	lem_in(t_data *data)
{
	data->end->indice = 0;
	set_indice(data->end, 1, data);
	if (data->start->indice == -1)
		error(NO_PATH);
	data->start->ant = data->n_ants;
	ordering(data);
	ordering_rooms(data);
	if (data->start->indice == 1)
	{
		finish(data);
		return ;
	}
	while (data->end->ant < data->n_ants)
		final(data);
}
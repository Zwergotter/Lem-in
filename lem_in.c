/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 21:27:54 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/10 15:20:01 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Here to display which ant moves to where.
*/

void		one_answer(int ant, char *room, int i)
{
	if (i)
		ft_putchar(' ');
	ft_putstr(CYN"L");
	ft_putnbr(ant);
	ft_putstr(RESET"-"PNK);
	ft_putstr(room);
	ft_putstr(""RESET);
}

/*
** Special case when we are on start and there's still ants in it.
** Because we can send one or more ants if there's rooms and we still have
** some in start.
*/

int			dispatching_ants(t_data *data, t_rooms *start, int count)
{
	int		ant;
	int		j;
	int		indice;

	j = -1;
	indice = start->i_end - 2;
	ant = data->n_ants - start->ant + 1;
	while (++indice < data->imax)
	{
		j = -1;
		while (start->links[++j])
		{
			if (start->ant && start->links[j]->i_end == indice &&
				!start->links[j]->ant &&
				start->ant > start->links[j]->i_end - start->i_end)
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

int			checking_each(t_data *data, t_rooms *r, int i, int count)
{
	int		j;

	j = -1;
	while (r->links[++j])
	{
		if (r->links[j]->i_end == i - 1 && r->links[j] != data->start &&
			(r->links[j] == data->end || !(r->links[j]->ant)))
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

/*
** Algo that will move ants checking room one by one according to their i_end,
** starting from data->rooms as the first one.
** If room i_end == i, there's ant in it and it's not start, will call
** checking_each.
** If we reach start, will call disptaching_ants.
** So at the end it displays all ants' movements for one turn, where count helps
** us to see if something was written before or not on one line, so we can add
** a space or not before writing the new movement.
*/

void		final(t_data *data)
{
	int		i;
	int		count;
	t_rooms *r;

	i = 0;
	count = 0;
	while (i < data->imax)
	{
		i++;
		r = data->rooms;
		while (r)
		{
			if (r->i_end == i && r->ant && r != data->start)
				count = checking_each(data, r, i, count);
			r = r->next;
		}
	}
	if (data->start->ant)
		dispatching_ants(data, data->start, count);
	ft_putchar('\n');
}

/*
** Will set start and end indices by calling set_data.
** Then will call ordering to sort links and rooms.
** Finally if end indice for start room is equal to 1, it means that start and
** end rooms are directly connected, so we can move each ant until the end.
** If not, we call final to dispatch them all.
*/

void		lem_in(t_data *data)
{
	int		i;

	i = 1;
	set_data(data);
	if (data->start->i_end == -1)
		error(data, NO_PATH);
	ordering(data);
	if (data->start->i_end == 1)
	{
		one_answer(1, data->end->name, 0);
		while (i != data->n_ants)
		{
			++i;
			one_answer(i, data->end->name, 1);
		}
		ft_putchar('\n');
		return ;
	}
	while (data->end->ant < data->n_ants)
		final(data);
}

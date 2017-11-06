/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:54:11 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/06 20:56:31 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	set_istart(t_rooms *r, int i, t_data *data)
{
	int c;

	c = -1;
	while (r->links[++c])
	{
		if (r->links[c]->istart > i || r->links[c]->istart == -1)
		{
			r->links[c]->istart = i;
			if (r->links[c] != data->end)
				set_istart(r->links[c], i + 1, data);
		}
	}
}

void	set_indice(t_rooms *r, int i, t_data *data)
{
	int c;

	c = -1;
	while (r->links[++c])
	{
		if ((r->istart > r->links[c]->istart || r == data->end) &&
			(r->links[c]->indice > i || r->links[c]->indice == -1))
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

void	set_data(t_data *data)
{
	data->end->indice = 0;
	data->start->istart = 0;
	set_istart(data->start, 1, data);
	set_indice(data->end, 1, data);
}
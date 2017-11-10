/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:54:11 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/10 15:16:45 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	set_i_start(t_rooms *r, int i, t_data *data)
{
	int c;

	c = -1;
	while (r->links[++c])
	{
		if (r->links[c]->i_start > i || r->links[c]->i_start == -1)
		{
			r->links[c]->i_start = i;
			if (r->links[c] != data->end)
				set_i_start(r->links[c], i + 1, data);
		}
	}
}

void	set_i_end(t_rooms *r, int i, t_data *data)
{
	int c;

	c = -1;
	while (r->links[++c])
	{
		if ((r->i_start > r->links[c]->i_start || r == data->end) &&
			(r->links[c]->i_end > i || r->links[c]->i_end == -1))
		{
			r->links[c]->i_end = i;
			if (r->links[c] != data->start)
			{
				set_i_end(r->links[c], i + 1, data);
				if (data->imax < i + 1)
					data->imax = i + 1;
			}
		}
	}
}

void	set_data(t_data *data)
{
	data->end->i_end = 0;
	data->start->i_start = 0;
	set_i_start(data->start, 1, data);
	set_i_end(data->end, 1, data);
}

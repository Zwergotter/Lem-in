/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:05:00 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/07 13:54:08 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		main(void)
{
	t_data	*data;

	data = palloc(sizeof(t_data));
	init_data(data);
	ft_putstr(data->all);
	ft_putchar('\n');
	if (data->start && data->start == data->end)
		error(SAME);
	if (data->start && data->end && data->start->links && data->end->links)
		lem_in(data);
	else
		what_error(data);
	return (0);
}

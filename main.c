/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:05:00 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/04 22:45:30 by edeveze          ###   ########.fr       */
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
	if (data->error)
		error(data->error);
	if (data->start == data->end && data->start)
		error(SAME);
	
	if (data->start && data->end)
	{
		if (data->start->links && data->end->links)
			lem_in(data);
		else
			error(NO_PATH);
	}
	else
		ft_putstr("ERROR\n");
	// ordering(data);
	// ft_putstr_fd(data->start, 2);
	// ft_putchar_fd('\n', 2);
	// ft_putstr_fd(data->end, 2);
	// ft_putchar_fd('\n', 2);
	// while (data->tubes)
	// {
	// 	ft_putstr_fd("\nFirst tube: ", 2);
	// 	ft_putstr_fd(data->tubes->tube1, 2);
	// 	ft_putstr_fd(" And second tube: ", 2);
	// 	ft_putstr_fd(data->tubes->tube2, 2);
	// 	data->tubes = data->tubes->next;
	// }
	// while (data->rooms)
	// {
	// 	ft_putstr_fd("\nName of room: ", 2);
	// 	ft_putstr_fd(data->rooms->name, 2);
	// 	ft_putstr_fd("  x: ", 2);
	// 	ft_putnbr_fd(data->rooms->coord_x, 2);
	// 	ft_putstr_fd("  y: ", 2);
	// 	ft_putnbr_fd(data->rooms->coord_y, 2);
	// 	data->rooms = data->rooms->next;
	// }
	return (0);
}

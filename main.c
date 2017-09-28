/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:05:00 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/28 21:06:42 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		main(void)
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
		error(MEM);
	init_data(data);
	ft_putstr_fd(data->start, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(data->end, 2);
	ft_putchar_fd('\n', 2);
	while (data->tubes)
	{
		ft_putstr_fd("\nFirst tube: ", 2);
		ft_putstr_fd(data->tubes->tube1, 2);
		ft_putstr_fd(" And second tube: ", 2);
		ft_putstr_fd(data->tubes->tube2, 2);
		data->tubes = data->tubes->next;
	}
	while (data->rooms)
	{
		ft_putstr_fd("\nName of room: ", 2);
		ft_putstr_fd(data->rooms->name, 2);
		ft_putstr_fd("  x: ", 2);
		ft_putnbr_fd(data->rooms->coord_x, 2);
		ft_putstr_fd("  y: ", 2);
		ft_putnbr_fd(data->rooms->coord_y, 2);
		data->rooms = data->rooms->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:05:00 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/10 14:39:08 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	option(t_data *data, int ac, char **av)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < ac - 1)
	{
		i++;
		j = 0;
		if (av[i][j] == '-')
		{
			while(av[i][j])
			{
				if (av[i][j] == 'O')
					data->O = 1;
				j++;
			}
		}
	}
}

int		main(int ac, char **av)
{
	t_data	*data;

	data = palloc(sizeof(t_data));
	data->O = 0;
	option(data, ac, av);
	init_data(data);
	ft_putstr(data->all);
	ft_putchar('\n');
	if (data->start && data->start == data->end)
		error(data, SAME);
	if (data->start && data->end && data->start->links && data->end->links)
		lem_in(data);
	else
		what_error(data);
	return (0);
}

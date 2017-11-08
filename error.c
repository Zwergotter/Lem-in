/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:00:13 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/07 11:52:01 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	error(t_error error)
{
	if (error == NOT_NB)
		ft_putstr_fd(RED"Nope, the first line isn't a positive integer.\n", 2);
	if (error == ZERO)
		ft_putstr_fd(RED"You gave me 0 ant. How can I move them then?\n", 2);
	if (error == MEM)
		ft_putstr_fd(GRN"Memory allocation failed\n", 2);
	if (error == SAME)
		ft_putstr_fd(PNK"Start and End are the same room. Duh.\n", 2);
	if (error == NO_PATH)
		ft_putstr_fd(PNK"No path linking Start and End.\n", 2);
	if (error == START_END)
		ft_putstr_fd(PNK"Start and End don't exist. What did you expect?\n", 2);
	if (error == START)
		ft_putstr_fd(PNK"ERROR 404: Start not found.\n", 2);
	if (error == END)
		ft_putstr_fd(PNK"No End no lem-in.\n", 2);
	if (error == LINK)
		ft_putstr_fd(YEL"Rooms not connected. Not even with one link.\n", 2);
	if (error == ROOM)
		ft_putstr_fd(MAG"Yep, you forgot the rooms.\n", 2);
	exit(0);
}

void	what_error(t_data *data)
{
	if (!data->rooms)
		error(ROOM);
	if (!data->start && !data->end)
		error(START_END);
	if (!data->start)
		error(START);
	if (!data->end)
		error(END);
	if (!data->link)
		error(LINK);
	if (!data->end->links || !data->start->links)
		error(NO_PATH);
}

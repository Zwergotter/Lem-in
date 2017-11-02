/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:00:13 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/31 15:15:03 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	error(t_error error)
{
	if (error == NOT_NB)
		ft_putstr_fd("Invalid ants' number\n", 2);
	if (error == MEM)
		ft_putstr_fd("Memory allocation failed\n", 2);
	if (error == SAME)
		ft_putstr_fd("\033[0;31mStart and end are the same room\n\033[0m", 2);
	if (error == NO_PATH)
		ft_putstr_fd("\033[0;31mThere's no path linking start and end\n\033[0m", 2);
	if (error == LEN)
		ft_putstr_fd("\033[0;31mNot enough data for a room\n\033[0m", 2);
	if (error == NAME)
		ft_putstr_fd("\033[0;31mIllegal room's name\n\033[0m", 2);
	exit(0);
}

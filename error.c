/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:00:13 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/28 21:10:35 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	error(t_error error)
{
	if (error == MEM)
		ft_putstr_fd("Memory allocation failed", 2);
	if (error == NB_ANTS)
		ft_putstr_fd("Wrong number of ants given", 2);
	if (error == NOT_NB)
		ft_putstr_fd("Invalid number, must only contains digits", 2);
	exit(0);
}

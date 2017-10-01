/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:00:13 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/01 16:12:39 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	error(t_error error)
{
	if (error == NOT_NB)
		ft_putstr_fd("Invalid number, must only contains digits and be positiv", 2);
	exit(0);
}

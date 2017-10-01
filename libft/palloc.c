/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 16:49:10 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/30 16:49:12 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*palloc(int i)
{
	void *s;

	s = malloc(i);
	if (!s)
	{
		perror(NULL);
		exit(errno);
	}
	return (s);
}

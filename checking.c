/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 18:46:04 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/07 10:14:12 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int	connection(t_data *data, char *str)
{
	t_tubes *pos;
	t_tubes *tmp;

	pos = NULL;
	tmp = data->tubes;
	while (tmp && !ft_strcmp(data->start->name, str))
	{
		while (tmp && (ft_strcmp(str, tmp->room1) &&
			ft_strcmp(str, tmp->room2)))
		{
			if (tmp != pos && (!ft_strcmp(str, tmp->room1) &&
				!ft_strcmp(str, tmp->room2)))
			{
				str = !ft_strcmp(str, tmp->room1) ? ft_strdup(tmp->room1) :
				ft_strdup(tmp->room2);
				pos = tmp;
				tmp = data->tubes;
			}
			tmp = tmp->next;
		}
	}
	if (!ft_strcmp(data->start->name, str))
		return (1);
	return (0);
}

int	checking(t_data *data)
{
	char *tmp;

	if (data->start == data->end)
		return (0);
	tmp = ft_strdup(data->end->name);
	if (!connection(data, tmp))
		error(NOPE);
	return (1);
}

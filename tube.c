/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:25:27 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/28 21:06:20 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	addlast_tube(t_tubes **begin, t_tubes *new)
{
	t_tubes	*lst;

	lst = *begin;
	if (lst == 0)
	{
		*begin = new;
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

int		tube(t_data *data, char *line)
{
	int 	i;
	int		j;
	t_tubes	*tube;

	i = 0;
	j = 0;
	if (!(tube = malloc(sizeof(t_tubes))))
		error(MEM);
	while (line[i] && line[i] != '-')
		i++;
	if (i == 0)
		return (0);
	tube->tube1 = ft_strsub(line, 0, i++);
	j = i;
	while (line[j])
		j++;
	if (j == i)
		return (0);
	tube->tube2 = ft_strsub(line, i, j - i);
	tube->next = NULL;
	addlast_tube(&data->tubes, tube);
	return (1);
}

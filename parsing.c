/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:05:53 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/25 18:49:50 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	addlast_room(t_rooms **begin, t_rooms *new)
{
	t_rooms	*lst;

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

int		room(t_data *data, char *line)
{
	int 	i;
	t_rooms	*room;

	i = 0;
	if (!(room = malloc(sizeof(t_rooms))))
	{
		ft_putstr_fd("Memory allocation failed", 2);
		exit (0);
	}
	while (line[i] && line[i] != ' ')
		i++;
	if (i == 0)
		return (0);
	room->name = ft_strsub(line, 0, i++);
	room->coord_x = ft_atoi(line + i);
	while (line[i] && line[i] != ' ')
		i++;
	room->coord_y = ft_atoi(line + i + 1);
	room->next = NULL;
	addlast_room(&data->rooms, room);
	return (1);
}

int		tube(t_data *data, char *line)
{
	int 	i;
	int		j;
	t_tubes	*tube;

	i = 0;
	j = 0;
	if (!(tube = malloc(sizeof(t_tubes))))
	{
		ft_putstr_fd("Memory allocation failed", 2);
		exit (0);
	}
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

int		other(t_data *data, char *line)
{
	int i;

	i = 0;

	while (line[i] && (line[i] != ' ' && line[i] != '-'))
		i++;
	if (line[i] == '-' && tube(data, line))
		return (1);
	if (line[i] == ' ' && room(data, line))
		return (1);
	return (0);
}

int		hash_line(t_data *data, char *line)
{
	int i;
	int which;

	i = 0;
	which = 0;
	if (ft_strcmp("##start", line) == 0 || ft_strcmp("##end", line) == 0)
	{
		if (line[2] == 'e')
			which = 1;
		get_next_line(0, &line);
		while (line[i] && line[i] != ' ')
			i++;
		if (!which)
		{
			data->start = ft_strsub(line, 0, i);
			i += 1;
			data->start_x = ft_atoi(line + i);
			while (line[i] && line[i] != ' ')
				i++;
			data->start_y = ft_atoi(line + i + 1);
		}
		else
		{
			data->end = ft_strsub(line, 0, i);
			i += 1;
			data->end_x = ft_atoi(line + i);
			while (line[i] && line[i] != ' ')
				i++;
			data->end_y = ft_atoi(line + i + 1);
		}
	}
	return (1);
}

void	set_values(t_data *data, char *number)
{
	data->start = NULL;
	data->start_x = 0;
	data->start_y = 0;
	data->end = NULL;
	data->end_x = 0;
	data->end_y = 0;
	data->rooms = NULL;
	data->tubes = NULL;
	data->n_ants = ft_atoi(number);
	if (data->n_ants < 0)
	{
		ft_putstr_fd("Wrong number of ants given", 2);
		exit (0);
	}
}

void	init_data(t_data *data)
{
	char *line;
	char *number;
	char buf[2];
	int result;
	int ret;

	result = 1;
	buf[1] = 0;
	number = ft_strdup("");
	while ((ret = read(0, buf, 1)) != 0 && ret != -1)
	{
		if (ft_isdigit(*buf))
			number = ft_strjoinfree(number, buf, 1);
		else if (*buf  == '\n')
			break;
		else
		{
		ft_putstr_fd("Invalid number, must only contains digits", 2);
		exit (0);
		}
	}
	set_values(data, number);
	while (result && get_next_line(0, &line) && ft_isprint(line[0]))
	{
		if (line[0] == '#')
			result = hash_line(data, line);
		else
			result = other(data, line);
	}
}

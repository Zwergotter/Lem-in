/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:05:53 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/28 21:04:15 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int			start_end_values(t_data *data, char **tmp, int i)
{
	if (!i)
	{
		data->start = ft_strdup(tmp[0]);
		data->start_x = ft_atoi(tmp[1]);
		data->start_y = ft_atoi(tmp[2]);
	}
	else
	{
		data->end = ft_strdup(tmp[0]);
		data->end_x = ft_atoi(tmp[1]);
		data->end_y = ft_atoi(tmp[2]);
		if (i == 2)
		{
			data->start = ft_strdup(data->end);
			data->start_x = data->end_x;
			data->start_y = data->end_y;
		}
	}
	free(tmp);
	return (1);
}

int			other(t_data *data, char *line)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] != ' ' && line[i] != '-'))
		i++;
	if (line[i] == '-' && tube(data, line))
		return (1);
	if (line[i] == ' ' && room(data, line))
		return (1);
	return (0);
}

int			hash_line(t_data *data, char *line)
{
	int		i;
	char	**tmp;

	i = 0;
	if (ft_strcmp("##start", line) == 0 || ft_strcmp("##end", line) == 0)
	{
		if (line[2] == 'e')
			i = 1;
		data->all = ft_strjoinfree(data->all, line, 3);
		data->all = ft_strjoinfree(data->all, "\n", 1);
		get_next_line(0, &line);
		while (ft_strcmp("##start", line) == 0 || ft_strcmp("##end", line) == 0)
		{
			if (i != 2 && ((line[2] == 's' && !i) || (line[2] == 'e' && i)))
				i = line[2] == 'e' ? 1 : 0;
			else
				i = 2;
			data->all = ft_strjoinfree(data->all, line, 3);
			data->all = ft_strjoinfree(data->all, "\n", 1);
			get_next_line(0, &line);
		}
		if (!(tmp = ft_strsplit(line, ' ')))
			error(MEM);
		start_end_values(data, tmp, i);
	}
	return (1);
}

void		set_values(t_data *data, char *number)
{
	data->start = NULL;
	data->start_x = 0;
	data->start_y = 0;
	data->end = NULL;
	data->end_x = 0;
	data->end_y = 0;
	data->rooms = NULL;
	data->tubes = NULL;
	data->all = ft_strdup("");
	data->n_ants = ft_atoi(number);
	if (data->n_ants < 0)
		error(NB_ANTS);
	data->all = ft_strjoinfree(data->all, number, 3);
	data->all = ft_strjoinfree(data->all, "\n", 1);
}

void		init_data(t_data *data)
{
	char	*line;
	char	*number;
	char	buf[2];
	int		ret;

	buf[1] = 0;
	number = ft_strdup("");
	while ((ret = read(0, buf, 1)) != 0 && ret != -1)
	{
		if (ft_isdigit(*buf))
			number = ft_strjoinfree(number, buf, 1);
		else if (*buf == '\n')
			break ;
		else
			error(NOT_NB);
	}
	read(0, buf, 1);
	ret = 1;
	set_values(data, number);
	// get_next_line(0, &line);
	// free(line);
	while (ret && get_next_line(0, &line) && ft_isprint(line[0]))
	{
				ft_putstr_fd("\nline in while: ", 2);
		ft_putstr_fd(line, 2);
		ret = (line[0] == '#') ? hash_line(data, line) : other(data, line);
		if (ret)
		{
			data->all = ft_strjoinfree(data->all, line, 3);
			data->all = ft_strjoinfree(data->all, "\n", 1);
		}
	}
}

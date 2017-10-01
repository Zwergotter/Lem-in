/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:05:53 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/01 15:53:26 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int			other(t_data *data, char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] == '-' && tube(data, line))
		return (1);
	if (line[i] == ' ' && room(data, line, -1))
		return (1);
	return (0);
}

int			hash_line(t_data *data, char **line)
{
	int		i;

	i = 0;
	if (ft_strcmp("##start", *line) == 0 || ft_strcmp("##end", *line) == 0)
	{
		if ((*line)[2] == 'e')
			i = 1;
		data->all = ft_strjoinfree(data->all, *line, 3);
		data->all = ft_strjoinfree(data->all, "\n", 1);
		get_next_line(0, line);
		while (ft_strcmp("##start", *line) == 0 || ft_strcmp("##end", *line) == 0)
		{
			if (((*line)[2] == 's' && i == 1) || ((*line)[2] == 'e' &&  i == 0))
				i = 2;
			data->all = ft_strjoinfree(data->all, *line, 3);
			data->all = ft_strjoinfree(data->all, "\n", 1);
			get_next_line(0, line);
		}
		room(data, *line, i);
	}
	return (1);
}

void		set_values(t_data *data, char *number)
{
	data->start = NULL;
	data->end = NULL;
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
	ret = 1;
	set_values(data, number);
	while (ret && get_next_line(0, &line) && ft_isprint(line[0]))
	{
		ret = (line[0] == '#') ? hash_line(data, &line) : other(data, line);
		if (ret)
		{
			data->all = ft_strjoinfree(data->all, line, 3);
			data->all = ft_strjoinfree(data->all, "\n", 1);
		}
	}
}

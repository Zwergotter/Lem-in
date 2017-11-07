/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:05:53 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/07 14:23:40 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

char		*join_line(char *s1, char *s2)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	new = malloc(len);
	if (new == NULL)
		return (NULL);
	*new = 0;
	if (s1)
		ft_strcat(new, s1);
	ft_strcat(new, s2);
	ft_strcat(new, "\n");
	free(s1);
	return (new);
}

int			other(t_data *data, char *line)
{
	int		i;

	i = 0;
	ft_putstr("\033[0;31m\nHere and line 0 is: \n\033[0m");
	ft_putchar(line[0]);
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] == '-' && tube(data, line))
		return (1);
	if (line[i] == ' ' && room(data, line, -1))
		return (1);
	data->error = ILLEGAL;
	return (0);
}

int			hash_line(t_data *data, char **line)
{
	int	i;

	i = 0;
	if (ft_strcmp("##start", *line) == 0 || ft_strcmp("##end", *line) == 0)
	{
		if ((*line)[2] == 's')
			i = 1;
		data->all = join_line(data->all, *line);
		get_next_line(0, line);
		while (ft_strcmp("##start", *line) == 0 ||
			ft_strcmp("##end", *line) == 0)
		{
			if (((*line)[2] == 's' && i == 0) || ((*line)[2] == 'e' && i == 1))
				i = 2;
			data->all = join_line(data->all, *line);
			get_next_line(0, line);
		}
		room(data, *line, i);
	}
	return (1);
}

void		set_values(t_data *data, char *number)
{
	data->error = NONE;
	data->start = NULL;
	data->end = NULL;
	data->rooms = NULL;
	data->imax = 0;
	data->n_ants = ft_atoi(number);
	// data->all = NULL;
	data->all = join_line(data->all, number);
}

void		ant_number(t_data *data)
{
	char	*number;
	char	buf[2];
	int		ret;

	buf[1] = 0;
	number = ft_strdup("");
	data->all = NULL;
	while ((ret = read(0, buf, 1)) != 0 && ret != -1)
	{
		if (*buf == '#')
		{
			while (*buf && *buf != '\n')
				ret = read(0, buf, 1);
		}
		if (ft_isdigit(*buf))
				number = ft_strjoinfree(number, buf, 1);
		if (*buf == '\n' && number[0])
			break ;
		if (*buf != '\n' && !ft_isdigit(*buf) && *buf != '#')
			error(NOT_NB);
	}
	set_values(data, number);
}

void		init_data(t_data *data)
{
	char	*line;
	int		ret;

	ant_number(data);
	ret = 1;
	while (ret && get_next_line(0, &line) && ft_isprint(line[0]))
	{
		ret = (line[0] == '#') ? hash_line(data, &line) : other(data, line);
		if (ret)
			data->all = join_line(data->all, line);
		free(line);
	}
}

// void		init_data(t_data *data)
// {
// 	char	*line;
// 	char	*number;
// 	char	buf[2];
// 	int		ret;

// 	buf[1] = 0;
// 	number = ft_strdup("");
// 	while ((ret = read(0, buf, 1)) != 0 && ret != -1)
// 	{
// 		if (ft_isdigit(*buf))
// 			number = ft_strjoinfree(number, buf, 1);
// 		else if (*buf == '\n')
// 			break ;
// 		else
// 			error(NOT_NB);
// 	}
// 	ret = 1;
// 	set_values(data, number);
// 	while (ret && get_next_line(0, &line) && ft_isprint(line[0]))
// 	{
// 		ret = (line[0] == '#') ? hash_line(data, &line) : other(data, line);
// 		if (ret)
// 			data->all = join_line(data->all, line);
// 		free(line);
// 	}
// }

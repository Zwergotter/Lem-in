/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:05:53 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/11 00:10:29 by edeveze          ###   ########.fr       */
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
	while (line[i] && line[i] != '-')
		i++;
	if (line[i] == '-' && tube(data, line))
		return (1);
	if (!line[i] && room(data, line, -1))
		return (1);
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
		free(*line);
		get_next_line(0, line);
		while ((*line)[0] == '#')
		{
			if ((ft_strcmp("##start", *line) == 0 && i == 0) ||
				(ft_strcmp("##end", *line) == 0 && i == 1))
				i = 2;
			data->all = join_line(data->all, *line);
			free(*line);
			get_next_line(0, line);
		}
		if (!(**line) || !room(data, *line, i))
			return (0);
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
	data->link = 0;
	data->n_ants = ft_atoi(number);
	if (!data->n_ants)
		error(data, ZERO);
	data->all = NULL;
	data->room1 = NULL;
	data->room2 = NULL;
	data->all = join_line(data->all, number);
	free(number);
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
		else if (*buf == '\n' && number[0])
			break ;
		else
			error(data, NOT_NB);
	}
	ret = 1;
	set_values(data, number);
	while (ret && get_next_line(0, &line) && ft_isprint(line[0]))
	{
		ret = (line[0] == '#') ? hash_line(data, &line) : other(data, line);
		if (ret)
			data->all = join_line(data->all, line);
		free(line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:05:53 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/01 16:34:07 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

char	*join_line(char *s1, char *s2, int nb)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = ft_strnew(len);
	if (new == NULL)
		return (NULL);
	new = ft_strcpy(new, s1);
	new = ft_strcat(new, s2);
	new = ft_strcat(new, "\n");
	if (nb == 1 || nb == 3)
		free(s1);
	if (nb == 2 || nb == 3)
		free(s2);
	return (new);
}

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
		data->all = join_line(data->all, *line, 3);
		get_next_line(0, line);
		while (ft_strcmp("##start", *line) == 0 || ft_strcmp("##end", *line) == 0)
		{
			if (((*line)[2] == 's' && i == 1) || ((*line)[2] == 'e' &&  i == 0))
				i = 2;
			data->all = join_line(data->all, *line, 3);
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
	data->all = join_line(data->all, number, 3);
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
			data->all = join_line(data->all, line, 3);
	}
}

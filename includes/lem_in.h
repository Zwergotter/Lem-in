/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:05:29 by edeveze           #+#    #+#             */
/*   Updated: 2017/10/01 16:35:10 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

typedef	enum 		e_error
{
	MEM, NOT_NB
}					t_error;

typedef struct		s_rooms
{
	char			*name;
	int				coord_x;
	int				coord_y;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_tubes
{
	char			*tube1;
	char			*tube2;
	struct s_tubes	*next;
}					t_tubes;

typedef struct		s_data
{
	t_rooms			*start;
	t_rooms			*end;
	int				n_ants;
	t_rooms			*rooms;
	t_tubes			*tubes;
	char			*all;
}					t_data;

int		tube(t_data *data, char *line);
int		room(t_data *data, char *line, int i);

int		start_end_values(t_data *data, char **tmp, int i);
void	init_data(t_data *data);

void	error(t_error error);

void	free_tab(char **t);

#endif

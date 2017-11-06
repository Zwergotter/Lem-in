/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:05:29 by edeveze           #+#    #+#             */
/*   Updated: 2017/11/06 20:55:34 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

typedef	enum 		e_error
{
	NONE, MEM, NOT_NB, NAME, LEN, SAME, NO_PATH, ERROR
}					t_error;

typedef struct		s_rooms
{
	char			*name;
	int				coord_x;
	int				coord_y;
	struct s_rooms	**links;
	struct s_rooms	*next;
	int				indice;
	int				istart;
	int				ant;
	int				order;
}					t_rooms;

typedef struct		s_data
{
	t_error			error;
	t_rooms			*start;
	t_rooms			*end;
	int				n_ants;
	t_rooms			*rooms;
	char			*all;
	int				imax;
}					t_data;

int		tube(t_data *data, char *line);
int		room(t_data *data, char *line, int i);

int		start_end_values(t_data *data, char **tmp, int i);
void	init_data(t_data *data);

void	error(t_error error);

void	free_tab(char **t);

void	ordering(t_data *data);

void	set_data(t_data *data);

void	lem_in(t_data *data);

#endif

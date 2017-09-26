/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:05:29 by edeveze           #+#    #+#             */
/*   Updated: 2017/09/25 15:41:20 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

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
	char			*start;
	int				start_x;
	int				start_y;
	char			*end;
	int				end_x;
	int				end_y;
	int				n_ants;
	t_rooms			*rooms;
	t_tubes			*tubes;
}					t_data;

void	init_data(t_data *data);

#endif

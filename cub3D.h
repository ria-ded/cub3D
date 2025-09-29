/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:47:36 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/29 23:21:59 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		ceiling_color;
	int		floor_color;
}			t_config;

typedef struct s_player
{
	double	x;
	double	y;
}			t_player;

typedef struct s_map
{
	char	**grid;		//probably create and use t_point instead of char
	int		width;
	int		height;
}			t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
	t_config	*config;
}				t_data;

// HELPER

#endif
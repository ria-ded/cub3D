/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:47:36 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/07 15:50:47 by svolkau          ###   ########.fr       */
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
// # include <stdbool.h>
# include "libft.h"

# define HEIGHT 900
# define WIDTH 1200

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define CEILING 0
# define FLOOR 1

typedef struct s_config
{
	char	*tex[4];
	int		color[2];
}			t_config;

typedef struct s_player
{
	double	x;
	double	y;
}			t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}			t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_config	config;
}				t_data;

// INIT
int		init_player(t_player *player);
int		init_config(t_config *config);
int		init_data(t_data *g, char *file);

// PARSER
int		parse_line(t_data *g, char *line);
int		parse_config(t_data *g, int fd);
int		parse_file(t_data *g, char *file);

// PARSER TEX
int		validate_format(char *file, char *format);
int		set_texture(t_config *config, int dir, char *val);

// PARSER_COLOR
int		set_color(t_config *config, int dir, char *val);
int		extract_rgb_val(char *val);
int		create_trgb(int t, int r, int g, int b);

// MAP_PARSER

// ENENTS

// PROJECT

// RENDER

// CLEANUP
void	free_config(t_config *config);
void	free_arr(char **arr);
// void	free_map(t_map *map);
void	free_data(t_data *g);

#endif
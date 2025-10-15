/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:47:36 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/15 12:07:37 by svolkau          ###   ########.fr       */
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
	char	orient;
	int		x;
	int		y;
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
	char			*str;
	int				index;
	struct s_map	*next;	
}					t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_map		*map;
	t_player	player;
	t_config	config;
}				t_data;

// INIT
void	init_player(t_player *player);
void	init_config(t_config *config);
int		init_data(t_data *g, char *file);

// PARSER
int		parse_line(t_data *g, char *line);
int		parse_config(t_data *g, int fd);
int		parse_file(t_data *g, char *file);
int		empty_line(char *line);

// PARSER TEX
int		validate_format(char *file, char *format);
int		set_texture(t_config *config, int dir, char *val);

// PARSER_COLOR
int		set_color(t_config *config, int dir, char *val);
int		extract_rgb_val(char *val);
int		create_trgb(int rgb[3]);

// PARSER_MAP
void	map_reader(t_data *cb3d, int fd);
int		check_pos(t_map *map, t_map *priv, int pos, char *set);
void	check_map_valid_char(t_data *cb3d);
void	check_player_pos(t_data *cb3d, t_map *head, t_map *priv, int pos);

// PARSER_MAP_WALL
int		map_size(t_map *map);
char	**map_to_arr(t_map *map);
int		check_path(char **gr, int y, int x, int rows);
int		validate_path(char **gridmap, t_data *cb3d);
void	check_wall_path(t_data *cb3d);

// PARSER_MAP_ADD
void	mapadd_back(t_map **map, t_map *mapnew);
t_map	*map_new(char *str, int index);
t_map	*map_last(t_map *map);

// PRINT
void	error_printer(char *msg, t_data *cb3d);
void	print_map(t_map *map);
void	print_gridmap(char **map);
void	print_player(t_player player);
void	print_config(t_config config);

// ENENTS

// PROJECT

// RENDER

// CLEANUP
void	free_config(t_config *config);
void	free_arr(char **arr);
void	free_data(t_data *g);
void	del(char *str);
void	map_delone(t_map *map, void (*del)(char *));
void	free_map(t_map **map, void (*del)(char *));

#endif
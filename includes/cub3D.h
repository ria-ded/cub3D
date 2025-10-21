/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:47:36 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/21 14:04:25 by svolkau          ###   ########.fr       */
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

# define HEIGHT 768
# define WIDTH 1024
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_A 97
# define KEY_D 100
# define KEY_W 119
# define KEY_S 115

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define CEILING 0
# define FLOOR 1

typedef struct s_texture
{
	char	*type;		
	int		width;
	int		height;
	char	*path;
	int		*color_arr;
}			t_texture;

typedef struct s_config
{
	struct s_texture	tex[4];
	int					color[2];
}						t_config;

typedef struct s_player
{
	char	orient;
	int		x;
	int		y;
}			t_player;

typedef struct s_img
{
	void	*img;
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
	int			fd;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			step_x;
	int			step_y;
	int			side;
	int			hit;
	int			map_x;
	int			map_y;
	int			tex_x;
	int			tex_y;
	float		wall_x;
	double		perp_wall_dist;
	double		side_d_x;
	double		side_d_y;
	double		delta_d_x;
	double		delta_d_y;
	double		camera_x;
	double		ray_dirx;
	double		ray_diry;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx;
	void		*win;
	char		*win_data;
	t_map		*map;
	char		**gridmap;
	t_img		img;
	t_player	player;
	t_config	config;
}				t_data;

// INIT
void	init_image(t_img *img);
void	init_config(t_config *config);
int		init_data(t_data *g, char *file);
void	init_main_data(t_data *g);
void	init_color_arrs(t_data *g);

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
void	print_config(t_config config);
void	print_color_arr(t_texture tex);

// RCAST
void	cast_rays(t_data *g);
void	set_ray(t_data *g);
void	move_ray(t_data *g);
void	distance(t_data *g);
void	draw(t_data *g);

// RCAST_ADD
void	draw_object(t_data *g);
void	set_pos(t_data *g);
int		get_texture(t_data *g);
void	get_delta_dist(t_data *g);

// PROJECT
void	start_game(t_data *g);
int		handlevent(int keycode, t_data *g);
int		closewin(t_data *g);

// RENDER
void	set_orient_values(t_data *g, double x, double y, double px, double py);
void	set_orient(t_data *g);
void	set_pixel(t_data *g, int x, int y, int color);
void	draw_cf(t_data *g, char flag);
void	print_display(t_data *g);

// CLEANUP
void	free_config(t_config *config);
void	free_arr(char **arr);
void	free_data(t_data *g);
void	map_delone(t_map *map);
void	free_map(t_map **map);

// COLOR
void	add_color_arr(t_data *g, int text);
int		*make_color_arr(t_data*g, int text);
void	check_format_p3(char *line, t_data *g);
void	get_size(t_data *g, int text);
void	make_split_color(char *line, int *rez, int *j);

#endif
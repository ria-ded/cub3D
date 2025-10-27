/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:47:36 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/26 22:03:23 by mdziadko         ###   ########.fr       */
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
# include <stdbool.h>
# include "libft.h"

# ifdef __linux__
#  include <X11/X.h>
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_W 119
#  define KEY_S 115
# else
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_W 13
#  define KEY_S 1
# endif

# define HEIGHT 900
# define WIDTH 1200

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define CEILING 0
# define FLOOR 1

# define FOV 66

# define X 0
# define Y 1

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_config
{
	char	*tex_path[4];
	t_img	tex[4];
	int		color[2];
}			t_config;

typedef struct s_ray
{
	double	dir[2];
	double	camera_x;
	double	side_dist[2];
	double	delta_dist[2];
	double	perp_wall_dist;
	int		map[2];
	int		step[2];
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_ray;

typedef struct s_player
{
	int		player_found;
	char	orient;
	int		x;
	int		y;
	double	pos[2];
	double	dir[2];
	double	plane[2];
}			t_player;

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
	t_img		img;
	t_map		*map;
	t_player	player;
	t_ray		ray;
	char		**mapa;
	t_config	c;
	char		*file;
	int			has_exited;
}				t_data;

// INIT
int		init_player(t_player *player);
int		init_config(t_config *c);
int		init_data(t_data *g, char *av);

// PARSER
int		empty_line(char *line);
int		parse_line(t_data *g, char *line);
int		parse_config(t_data *g, int fd);
void	parse_map(t_data *g, int fd);
int		parse_file(t_data *g);

// PARSER_TEX
bool	validate_format(char *file, char *format);
int		set_texture(t_config *c, int dir, char *val);

// PARSER_COLOR
int		set_color(t_config *c, int dir, char *val);
int		extract_rgb_val(char *val);
int		create_trgb(int t, int r, int g, int b);

// PARSER_MAP
void	map_reader(t_data *cb3d, int fd);
int		check_pos(t_map *map, t_map *priv, int pos, char *set);
void	set_player_pos(t_data *cb3d, t_map *head, t_map *priv, int pos);
void	check_map_valid_char(t_data *cb3d);

// PARSER_MAP_WALL
char	**map_to_arr(t_map *map);
int		check_path(char **gr, int y, int x, int rows);
int		validate_path(char **gr, t_data *cb3d);
void	check_wall_path(t_data *cb3d);

// PARSER_MAP_UTILS
int		map_size(t_map *map);
t_map	*map_last(t_map *map);
int		map_add_back(t_map **map, t_map *mapnew);
t_map	*map_new(char *str, int index);
void	map_delone(t_map *map, void (*del)(char *));

// PRINT
void	print_err(char *msg, t_data *cb3d);
void	printf_config(t_config *c);
void	print_map(t_map *map);
void	print_grid(char **gr);

// SETUP
void	setup_game(t_data *g);
void	set_plane(t_player *p);
void	set_dir(t_player *p);
void	load_texture(t_data *g);

// EVENTS
int		close_win(t_data *g);
int		handle_keys(int keycode, t_data *g);
void	handle_events(t_data *g);

// MOVE
void	move_forward(t_data *g);
void	move_backward(t_data *g);
void	move_left(t_data *g);
void	move_right(t_data *g);

// ROTATION
void	turn_right(t_data *g);
void	turn_left(t_data *g);

// DRAW
void	draw_line(t_data *g, int dir, int screen_x);
void	put_texture(t_data *g, double tex[2], int dir, int x);
void	pixel_put(t_data *g, int x, int y, int color);
void	clear_frame(t_data *g);

// RENDER
void	init_ray(t_ray *r, t_player *p);
bool	hit_wall(t_ray *r, char **map);
bool	calc_dist(t_ray *r, t_player *p);
int		wall_dir(t_ray *r);
int		render(t_data	*g);

// CLEANUP
void	del(char *str);
void	free_map(t_map **map, void (*del)(char *));
void	free_config(t_data *g);
void	free_arr(char **arr);
void	free_data(t_data *g);

#endif
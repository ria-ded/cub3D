/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:45:48 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/22 16:49:33 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**map_to_arr(t_map *map)
{
	char	**g;
	t_map	*temp;
	int		i;

	g = malloc(sizeof(char *) * (map_size(map) + 1));
	if (!g)
		return (NULL);
	temp = map;
	i = 0;
	while (temp)
	{
		g[i] = ft_strdup(temp->str);
		if (!g[i])
			return (free_arr(g), NULL);
		i++;
		temp = temp->next;
	}
	g[i] = NULL;
	return (g);
}

int	check_path(char **g, int y, int x, int rows)
{
	int	c;

	c = 0;
	g[y][x] = '3';
	if (y < 0 || y >= rows || x < 0 || x >= (int)ft_strlen(g[y]))
		return (0);
	if (y + 1 < rows && x < (int)ft_strlen(g[y + 1])
		&& ft_strchr("0WSEN", g[y + 1][x]))
		return (1);
	else if (y + 1 < rows && x < (int)ft_strlen(g[y + 1]) && g[y + 1][x] == '1')
		c += check_path(g, y + 1, x, rows);
	if (y - 1 >= 0 && x < (int)ft_strlen(g[y - 1])
		&& ft_strchr("0WSEN", g[y - 1][x]))
		return (1);
	else if (y - 1 >= 0 && x < (int)ft_strlen(g[y - 1]) && g[y - 1][x] == '1')
		c += check_path(g, y - 1, x, rows);
	if (x + 1 < (int)ft_strlen(g[y]) && ft_strchr("0WSEN", g[y][x + 1]))
		return (1);
	else if (x + 1 < (int)ft_strlen(g[y]) && g[y][x + 1] == '1')
		c += check_path(g, y, x + 1, rows);
	if (x - 1 >= 0 && ft_strchr("0WSEN", g[y][x - 1]))
		return (1);
	else if (x - 1 >= 0 && g[y][x - 1] == '1')
		c += check_path(g, y, x - 1, rows);
	return (c);
}

int	validate_path(char **g, t_data *cb3d)
{
	int		y;
	int		x;
	int		rows;

	y = -1;
	rows = map_size(cb3d->map);
	while (++y < rows)
	{
		x = -1;
		while (++x < (int)ft_strlen(g[y]))
		{
			if (g[y][x] == '1')
			{
				if (!check_path(g, y, x, rows))
					return (0);
			}
		}
	}
	return (1);
}

void	check_wall_path(t_data *cb3d)
{
	char	**g;

	g = map_to_arr(cb3d->map);
	if (!g)
		print_err("Malloc", cb3d);
	if (!validate_path(g, cb3d))
	{
		free_arr(g);
		print_err("Map is not correct", cb3d);
	}
	free_arr(g);
}

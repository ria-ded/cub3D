/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:45:48 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/13 11:07:11 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**map_to_arr(t_map *map)
{
	char	**gr;
	t_map	*temp;
	int		i;

	gr = malloc(sizeof(char *) * (map_size(map) + 1));
	if (!gr)
		return (NULL);
	temp = map;
	i = 0;
	while (temp)
	{
		gr[i] = ft_strdup(temp->str);
		if (!gr[i])
			return (free_arr(gr), NULL);
		i++;
		temp = temp->next;
	}
	gr[i] = NULL;
	return (gr);
}

int	check_path(char **gr, int y, int x, int rows)
{
	int	c;

	c = 0;
	gr[y][x] = '3';
	if (y < 0 || y >= rows || x < 0 || x >= (int)ft_strlen(gr[y]))
		return (0);
	if (y + 1 < rows && x < (int)ft_strlen(gr[y + 1])
		&& ft_strchr("0WSEN", gr[y + 1][x]))
		return (1);
	else if (y + 1 < rows && x < (int)ft_strlen(gr[y + 1]) && gr[y + 1][x] == '1')
		c += check_path(gr, y + 1, x, rows);
	if (y - 1 >= 0 && x < (int)ft_strlen(gr[y - 1])
		&& ft_strchr("0WSEN", gr[y - 1][x]))
		return (1);
	else if (y - 1 >= 0 && x < (int)ft_strlen(gr[y - 1]) && gr[y - 1][x] == '1')
		c += check_path(gr, y - 1, x, rows);
	if (x + 1 < (int)ft_strlen(gr[y]) && ft_strchr("0WSEN", gr[y][x + 1]))
		return (1);
	else if (x + 1 < (int)ft_strlen(gr[y]) && gr[y][x + 1] == '1')
		c += check_path(gr, y, x + 1, rows);
	if (x - 1 >= 0 && ft_strchr("0WSEN", gr[y][x - 1]))
		return (1);
	else if (x - 1 >= 0 && gr[y][x - 1] == '1')
		c += check_path(gr, y, x - 1, rows);
	return (c);
}

int	validate_path(char **gr, t_data *cb3d)
{
	int		y;
	int		x;
	int		rows;

	y = -1;
	rows = map_size(cb3d->map);
	while (++y < rows)
	{
		x = -1;
		while (++x < (int)ft_strlen(gr[y]))
		{
			if (gr[y][x] == '1')
			{
				if (!check_path(gr, y, x, rows))
					return (0);
			}
		}
	}
	return (1);
}

void	check_wall_path(t_data *cb3d)
{
	char	**gr;

	gr = map_to_arr(cb3d->map);
	if (!gr)
		print_err("Malloc", cb3d);
	if (!validate_path(gr, cb3d))
	{
		free_arr(gr);
		print_err("Map is not correct", cb3d);
	}
	free_arr(gr);
}

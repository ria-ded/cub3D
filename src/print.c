/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:06:39 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/20 13:35:14 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	error_printer(char *msg, t_data *cb3d)
{
	printf("%s\n", msg);
	free_data(cb3d);
	exit(1);
}

void	print_map(t_map *map)
{
	while (map)
	{
		printf("%s", map->str);
		map = map->next;
	}
	printf("\n");
}

void	print_gridmap(char **map)
{
	int	j;
	int	i;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			printf("%c", map[i][j]);
		printf("\n");
	}
}

void	print_config(t_config config)
{
	printf("NO: %s\n", config.tex[NO].path);
	printf("SO: %s\n", config.tex[SO].path);
	printf("WE: %s\n", config.tex[WE].path);
	printf("EA: %s\n", config.tex[EA].path);
	printf("Ceiling: %d\n", config.color[CEILING]);
	printf("Floor: %d\n", config.color[FLOOR]);
}

void	print_color_arr(t_texture tex)
{
	int	i;

	i = -1;
	while (++i < (tex.width * tex.height))
		printf("index: %d, color: %d\n", i, tex.color_arr[i]);
}

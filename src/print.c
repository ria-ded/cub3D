/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:06:39 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/15 11:20:50 by svolkau          ###   ########.fr       */
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
	}
	printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:57 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/07 18:22:01 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_map	*maplast(t_map *map)
{
	if (map == NULL)
		return (NULL);
	while (map->next != NULL)
		map = map->next;
	return (map);
}

void	mapadd_back(t_map **map, t_map *mapnew)
{
	t_map	*last;

	if (!mapnew)
		return ;
	if (*map)
	{
		last = maplast(*map);
		last->next = mapnew;
	}
	else
		*map = mapnew;
}

t_map	*mapnew(char *str, int index)
{
	t_map	*mapnew;

	mapnew = malloc(sizeof(t_map));
	if (!mapnew)
		return (NULL);
	mapnew->str = str;
	mapnew->index = index;
	mapnew->next = NULL;
	return (mapnew);
}

void	freegridmap(char **grid)
{
	char	**temp;

	temp = grid;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(grid);
}

void	printmap(t_map *map)
{
	while (map)
	{
		printf("%s", map->str);
		map = map->next;
	}
	printf("\n");
}

void	printgridmap(char **map)
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
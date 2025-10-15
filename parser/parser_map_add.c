/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:57 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/15 11:29:06 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_map	*map_last(t_map *map)
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
		last = map_last(*map);
		last->next = mapnew;
	}
	else
		*map = mapnew;
}

t_map	*map_new(char *str, int index)
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

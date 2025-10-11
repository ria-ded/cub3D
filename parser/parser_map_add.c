/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:57 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/08 21:54:02 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	mapdelone(t_map *map, void (*del)(char *))
{
	if (!del)
		return ;
	if (map)
	{
		(*del)(map->str);
		free(map);
	}
}

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

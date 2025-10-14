/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:17:57 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/13 11:07:16 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	map_size(t_map *map)
{
	int	i;

	if (!map)
		return (-1);
	i = 0;
	while (map)
	{
		map = map->next;
		i++;
	}
	return (i);
}

void	map_delone(t_map *map, void (*del)(char *))
{
	if (!del)
		return ;
	if (map)
	{
		(*del)(map->str);
		free(map);
	}
}

t_map	*map_last(t_map *map)
{
	if (map == NULL)
		return (NULL);
	while (map->next != NULL)
		map = map->next;
	return (map);
}

int	map_add_back(t_map **map, t_map *mapnew)
{
	t_map	*last;

	if (!mapnew)
		return (1);
	if (*map)
	{
		last = map_last(*map);
		last->next = mapnew;
	}
	else
		*map = mapnew;
	return (0);
}

t_map	*map_new(char *str, int index)
{
	t_map	*mapnew;

	if (!str)
		return (NULL);
	mapnew = malloc(sizeof(t_map));
	if (!mapnew)
		return (NULL);
	mapnew->str = str;
	mapnew->index = index;
	mapnew->next = NULL;
	return (mapnew);
}

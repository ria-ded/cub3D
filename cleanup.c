/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:43:22 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/10 22:22:42 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	del(char *str)
{
	if (str)
		free(str);
}

void	free_map(t_map **map, void (*del)(char *))
{
	t_map	*tmp;

	if (!map || !*map)
		return ;
	while (map && *map)
	{
		tmp = (*map)->next;
		mapdelone(*map, del);
		*map = tmp;
	}
	*map = NULL;
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_config(t_config *config)
{
	if (config->tex[NO])
		free(config->tex[NO]);
	if (config->tex[SO])
		free(config->tex[SO]);
	if (config->tex[WE])
		free(config->tex[WE]);
	if (config->tex[EA])
		free(config->tex[EA]);
}

void	free_data(t_data *g)
{
	if (!g)
		return ;
	if (g->file)
		free(g->file);
	free_config(&g->config);
	free_map(&g->map, del);
	if (g->mlx && g->img.img)
	{
		mlx_destroy_image(g->mlx, g->img.img);
		g->img.img = NULL;
	}
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
	# ifdef __linux__
		mlx_destroy_display(g->mlx);
		free (g->mlx);
	# endif
	}
}

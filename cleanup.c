/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:43:22 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/06 14:09:41 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	free_config(&g->config);
	// free_map(&g->map);
	if (g->mlx && g->img.img)
	{
		mlx_destroy_image(g->mlx, g->img.img);
		g->img.img = NULL;
	}
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
# ifdef __linux__
	mlx_destroy_display(g->mlx);
	free (g->mlx);
# endif
}

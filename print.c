/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:12:54 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/12 11:42:33 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_err(char *msg, t_data *cb3d)
{
	printf("Error\n");
	printf("%s\n", msg);
	free_data(cb3d);
	exit(1);
}

void	printf_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("config->tex[%i] = %s\n", i, config->tex[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		printf("config->col[%i] = %i\n", i, config->color[i]);
		i++;
	}
}

void	print_map(t_map *map)
{
	while (map)
	{
		printf("%s\n", map->str);
		map = map->next;
	}
	// printf("\n");
}

void	print_grid(char **grid)
{
	int	j;
	int	i;

	i = -1;
	while (grid[++i])
	{
		j = -1;
		while (grid[i][++j])
			printf("%c", grid[i][j]);
		printf("\n");
	}
	// printf("\n");
}

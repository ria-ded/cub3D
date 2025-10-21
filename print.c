/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:12:54 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/21 11:32:50 by mdziadko         ###   ########.fr       */
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
		printf("config->tex[%i] = %s\n", i, config->tex_path[i]);
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
}

void	print_grid(char **gr)
{
	int	j;
	int	i;

	i = 0;
	while (gr[i])
	{
		j = 0;
		while (gr[i][j])
		{
			printf("%c", gr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

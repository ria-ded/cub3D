/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:53:31 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/07 09:42:10 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	printf_config(t_config *config)
{
	for (int i = 0; i < 4; i++)
		printf("config->tex[%i] = %s\n", i, config->tex[i]);
	for (int i = 0; i < 2; i++)
		printf("config->col[%i] = %i\n", i, config->color[i]);
}

int	main(int argc, char **argv)
{
	t_data	g;

	if (argc != 2)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (validate_format(argv[1], ".cub"))
		return (1);
	if (init_data(&g, argv[1]))
		return (1);

	// TEST
	printf_config(&g.config);

	// mlx_loop(g.mlx);
	free_data(&g);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:53:31 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/07 18:58:27 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	char *trimmed;

	if (argc != 2 || (argv[1][0] == '.' && argv[1][1] == '.'))
		return (printf("Error: wrong number of arguments\n"), 1);
	trimmed = ft_strtrim(argv[1], " ");
	if (validate_format(trimmed, ".cub"))
		return (free(trimmed), 1);
	if (init_data(&g, trimmed))
		return (free(trimmed), 1);
	// TEST
	//printf_config(&g.config);
	// mlx_loop(g.mlx);
	free_data(&g);
	free(trimmed);
}

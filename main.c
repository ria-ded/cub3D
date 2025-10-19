/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <svolkau@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:53:31 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/19 20:27:31 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_data	g;
	char *trimmed;

	if (argc != 2 || (argv[1][0] == '.' && argv[1][1] == '.'))
		return (printf("Error: wrong number of arguments or ../\n"), 1);
	trimmed = ft_strtrim(argv[1], " ");
	if (validate_format(trimmed, ".cub"))
		return (free(trimmed), 1);
	if (init_data(&g, trimmed))
		return (free(trimmed), 1);
	start_game(&g);
	free_data(&g);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:53:31 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/10 18:14:55 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_data	g;

	if (argc != 2)
		return (printf("Error\nwrong number of arguments\n"), 1);
	if ((argv[1][0] == '.' && argv[1][1] == '.'))
		return (printf("Error\nrelative path\n"), 1);
	if (init_data(&g, argv[1]))
		return (1);
	// mlx_loop(g.mlx);
	free_data(&g);
}

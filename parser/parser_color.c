/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:23:39 by mdziadko          #+#    #+#             */
/*   Updated: 2025/10/21 13:19:34 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	create_trgb(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int	extract_rgb_val(char *val)
{
	char	*trimmed;
	int		num;

	trimmed = ft_strtrim(val, " ");
	if (!trimmed)
		return (perror("Error: strtrim\n"), -1);
	if (!ft_isnum(trimmed))
		return (printf("Error: rgb is not a number\n"), -1);
	num = ft_atoi(trimmed);
	free(trimmed);
	if (num < 0 || num > 255)
		return (printf("Error: wrong rgb code\n"), -1);
	return (num);
}

int	set_color(t_config *config, int dir, char *val)
{
	char	**split;
	int		rgb[3];
	int		i;

	if (config->color[dir] != -1)
		return (printf("Error: repetitive element\n"), 1);
	split = ft_split(val, ',');
	if (!split)
		return (perror("Error: split\n"), 1);
	i = 0;
	while (split[i])
	{
		if (i >= 3)
			return (printf("Error: wrong rgb code\n"), free_arr(split), 1);
		rgb[i] = extract_rgb_val(split[i]);
		if (rgb[i] < 0)
			return (free_arr(split), 1);
		i++;
	}
	free_arr(split);
	if (i != 3)
		return (printf("Error: wrong rgb code\n"), 1);
	config->color[dir] = create_trgb(rgb);
	return (0);
}

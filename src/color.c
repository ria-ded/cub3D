/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:14:38 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/16 16:20:53 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	arr_size(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
		i++;
	return(i);
}

void	valid_texture(t_data *g, int text)
{
	int	i;

	i = -1;
	while (++i < g->config.tex[text].height * g->config.tex[text].width)
	{
		if (!g->config.tex[text].color_arr[i])
			error_printer("Error: Not valid texture", g);
	}
}

void	get_size(t_data *g, int text)
{
	char	*line;
	char	**split;

	line = get_next_line(g->fd);
	line[ft_strlen(line) - 1] = '\0';
	split = NULL;
	if (line)
	{
		split = ft_split(line, ' ');
		if (split[0] && split[1] && ft_atoi(split[0]) > 0 && ft_atoi(split[1]) > 0)
		{
			g->config.tex[text].width = ft_atoi(split[0]);
			g->config.tex[text].height = ft_atoi(split[1]);
		}
		else
		{
			free(line);
			free_arr(split);
			error_printer("Error: Not valid texture", g);
		}
	}
	free_arr(split);
	free(line);
}

void check_format_p3(char *line, t_data *g)
{
	if (line[0] != 'P' || line[1] != '3')
	{
		free(line);
		error_printer("Error: Not valid texture", g);
	}
	free(line);
}

int	*make_color_arr(t_data*g, int text)
{
	int		i;
	int		j;
	int		*rez;
	char	*line;
	char	**split;

	rez = malloc(sizeof(int) * g->config.tex[text].height * g->config.tex[text].width);
	line = get_next_line(g->fd);
	j = 0;
	while (line)
	{
		if (line[0] != '\n')
		{
			split = ft_split(line, ' ');
			if ((arr_size(split) - 1) % 3 != 0)
			{
				free_arr(split);
				free(line);
				free(rez);
				error_printer("Error: Not valid texture1", g);
			}
			i = 0;
			while (split[i])
			{
				if (split[i][0] != '\n')
				{
					if (j > (g->config.tex[text].height * g->config.tex[text].width) - 1)
					{
						free_arr(split);
						free(line);
						free(rez);
						error_printer("Error: Not valid texture", g);
					}
					rez[j++] = create_trgb((int [3]){ft_atoi(split[i]), ft_atoi(split[i + 1]), ft_atoi(split[i + 2])});
					i += 3;
				}
				else
					break;
			}
			free_arr(split);
		}
		free(line);
		line = get_next_line(g->fd);
	}
	return (rez);
}

void	add_color_arr(t_data *g, int text)
{
	char	*line;

	g->fd = open(g->config.tex[text].path, O_RDONLY);
	line = get_next_line(g->fd);
	check_format_p3(line, g);
	get_size(g, text);
	line = get_next_line(g->fd);
	free(line);
	g->config.tex[text].color_arr = make_color_arr(g, text);
	valid_texture(g, text);
	close(g->fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:14:38 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/20 13:39:05 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_size(t_data *g, int text)
{
	char	*line;
	char	**spl;

	line = get_next_line(g->fd);
	line[ft_strlen(line) - 1] = '\0';
	spl = NULL;
	if (line)
	{
		spl = ft_split(line, ' ');
		if (spl[0] && spl[1] && ft_atoi(spl[0]) > 0 && ft_atoi(spl[1]) > 0)
		{
			g->config.tex[text].width = ft_atoi(spl[0]);
			g->config.tex[text].height = ft_atoi(spl[1]);
		}
		else
		{
			free(line);
			free_arr(spl);
			error_printer("Error: Not valid texture", g);
		}
	}
	free_arr(spl);
	free(line);
}

void	check_format_p3(char *line, t_data *g)
{
	if (line[0] != 'P' || line[1] != '3')
	{
		free(line);
		error_printer("Error: Not valid texture", g);
	}
	free(line);
}

void	make_split_color(char *line, int *rez, int *j)
{
	char	**spl;
	int		i;

	if (line[0] != '\n')
	{
		spl = ft_split(line, ' ');
		i = 0;
		while (spl[i] && spl[i + 1] && spl[i + 2])
		{
			if (spl[i][0] != '\n')
			{
				rez[(*j)++] = create_trgb((int [3]){ft_atoi(spl[i]),
						ft_atoi(spl[i + 1]), ft_atoi(spl[i + 2])});
				i += 3;
			}
			else
				break ;
		}
		free_arr(spl);
	}
}

int	*make_color_arr(t_data*g, int text)
{
	int		j;
	int		*rez;
	char	*line;

	rez = malloc(sizeof(int) * g->config.tex[text].height
			* g->config.tex[text].width);
	if (!rez)
		error_printer("Error: malloc failed for color array", g);
	line = get_next_line(g->fd);
	j = 0;
	while (line)
	{
		make_split_color(line, rez, &j);
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
	close(g->fd);
}

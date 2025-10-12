/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:05:01 by svolkau           #+#    #+#             */
/*   Updated: 2025/10/12 11:42:43 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	map_reader(t_data *cb3d, int fd)
{
	char	*line;
	int		i;
	int		map_ended;

	i = 0;
	map_ended = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (empty_line(line) && i)
			map_ended = 1;
		if (!empty_line(line) && !map_ended)
			mapadd_back(&cb3d->map, mapnew(ft_strtrim(line, "\n"), i++));
		else if (!empty_line(line) && map_ended)
		{
			free(line);
			print_err("Something after map", cb3d);
		}
		free(line);
	}
	if (!i)
		print_err("Map is empty", cb3d);
}

int	check_pos(t_map *map, t_map *priv, int pos, char *set)
{
	if (pos > 0 && (!map->str[pos - 1] || !ft_strchr(set, map->str[pos - 1])))
		return (0);
	if (!map->str[pos + 1] || !ft_strchr(set, map->str[pos + 1]))
		return (0);
	if (!priv || !ft_strchr(set, priv->str[pos]))
		return (0);
	if (!map->next || !map->next->str[pos]
		|| !ft_strchr(set, map->next->str[pos]))
		return (0);
	return (1);
}

void	set_player_pos(t_data *cb3d, t_map *head, t_map *priv, int pos)
{
	if (cb3d->player.player_found)
		print_err("Too many players", cb3d);
	cb3d->player.player_found++;
	cb3d->player.orient = head->str[pos];
	cb3d->player.x = pos;
	cb3d->player.y = head->index;
	if (!check_pos(head, priv, pos, "10"))
		print_err("Not correct player start position", cb3d);
}

void	check_map_valid_char(t_data *cb3d)
{
	int		i;
	t_map	*priv;
	t_map	*head;

	priv = NULL;
	head = cb3d->map;
	while (head)
	{
		i = -1;
		while (head->str[++i])
		{
			if (!ft_strchr("EWNS10", head->str[i]) && !ft_isspace(head->str[i]))
				print_err("Not correct character in map", cb3d);
			if (head->str[i] == ' ')
				head->str[i] = '2';
			if (head->str[i] == '0' && !check_pos(head, priv, i, "EWNS10"))
				print_err("Wall or floor is not correct", cb3d);
			if (ft_strchr("EWNS", head->str[i]))
				set_player_pos(cb3d, head, priv, i);
		}
		priv = head;
		head = head->next;
	}
	if (!cb3d->player.player_found)
		print_err("No player start position", cb3d);
}

/*
int	check_pos(t_map *map, t_map *priv, int pos, char *set)
{
	if ((!map->str[pos - 1] || !ft_strchr(set, map->str[pos - 1]))
		|| !map->str[pos + 1] || !ft_strchr(set, map->str[pos + 1])
		|| !priv || !ft_strchr(set, priv->str[pos])
		|| !map->next || !map->next->str[pos]
		|| !ft_strchr(set, map->next->str[pos]))
		return (0);
	return (1);
}

void	check_player_pos(t_data *cb3d, t_map *head, t_map *priv, int pos)
{
	int	c;

	c = 0;
	if (++c != 1)
		print_err("Too many players", cb3d);
	else
	{
		cb3d->player.orient = head->str[pos];
		cb3d->player.x = pos;
		cb3d->player.y = head->index;
	}
	if (!check_pos(head, priv, pos, "10"))
		print_err("Not correct player start position", cb3d);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:29:15 by omizin            #+#    #+#             */
/*   Updated: 2025/05/09 20:43:42 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**split_map_into_lines(char *map)
{
	char	**lines;

	lines = ft_split(map, '\n');
	return (lines);
}

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

static char	*read_and_join_lines(int fd, char *first_line, unsigned long width)
{
	char	*line;
	char	*joined;
	char	*tmp;

	if (width != ft_strlen(first_line) - 1)
		return (free(first_line), NULL);
	joined = ft_strdup(first_line);
	free(first_line);
	if (!joined)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (width != ft_strlen(line) - 1)
			return (free(line), free(joined), NULL);
		tmp = ft_strjoin(joined, line);
		free(joined);
		joined = tmp;
		free(line);
		line = get_next_line(fd);
	}
	return (joined);
}

char	*ft_get_map(char *argv)
{
	int				fd;
	char			*line;
	char			*joined;
	unsigned long	width;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error with map name/path\n"), NULL);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ft_printf("Empty map or read error\n"), NULL);
	width = ft_strlen(line) - 1;
	joined = read_and_join_lines(fd, line, width);
	close(fd);
	return (joined);
}

int	ft_map_check(char *map, t_map *map_struct)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (map[i] == 'C')
			map_struct->coin++;
		else if (map[i] == 'P')
			map_struct->player++;
		else if (map[i] == 'E')
			map_struct->exit++;
		else if (map[i] == '\n')
			map_struct->height++;
		else if (map[i] == '0' || map[i] == '1' || map[i] == '\r')
			;
		else
			return (ft_printf("Wrong map |%c|\n", map[i]), 1);
		i++;
	}
	if (map_struct->coin < 1 || map_struct->player != 1 || map_struct->exit != 1)
		return (ft_printf("Error: Incorrect map content \n"), 1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:18:20 by omizin            #+#    #+#             */
/*   Updated: 2025/05/05 13:21:18 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_line_check(char *line, int width)
{
	int	i;
	int	coin;
	int	player;
	int	exit;
	int	wall;

	i = 0;
	coin = 0;
	player = 0;
	exit = 0;
	wall = 0;
	if (line[i] != '1' && line[width] != '1')
		return (ft_printf("Wall is missing\n"), -1);
	while (i < width)
	{
		if (line[i] == '1')
			wall++;
		else if (line[i] == 'C')
			coin++;
		else if (line[i] == 'E')
			exit++;
		else if (line[i] == 'P')
			player++;
		else if (line[i] == '0')
		{
			i++;
			continue ;
		}
		else
			return (ft_printf("Wrong map |%c|\n", line[i]), -1);
		i++;
	}
	if (wall == width)
		return (1);
	else
		return (0);
}

int	ft_input_check(char *argv)
{
	int				fd;
	unsigned long	width;
	char			*line;
	char			*joined;

	joined = ft_strdup("");
	fd = open(argv, O_RDONLY);
	if (!fd)
		return(ft_printf("Error with map name/path\n"), 1);
	line = get_next_line(fd);
	width = ft_strlen(line) - 1;
	while (line != NULL)
	{
		if (width != ft_strlen(line) - 1)
			return(free(line), free(joined), ft_printf("Error_Map is assymetric\n"), 1);
		ft_printf("line : %s", line);
		//ft_line_check(line, width);
		joined = ft_strjoin(joined, line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("Error_argc is not 2\n"), 1);
	ft_printf("Hello, so_long!\n");
	//ft_printf("%s", argv[1]);
	ft_input_check(argv[1]);
	return (0);
}

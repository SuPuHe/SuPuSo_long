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

void	free_all_gnl(void)
{
	int				fd;
	t_gnl			*gnl;
	static t_gnl	**gnl_array_ptr;

	gnl_array_ptr = NULL;
	if (!gnl_array_ptr)
		gnl_array_ptr = (t_gnl **)get_gnl_array();
	fd = 0;
	while (fd < 1024)
	{
		gnl = gnl_array_ptr[fd];
		if (gnl)
		{
			if (gnl->buf)
				free(gnl->buf);
			free(gnl);
			gnl_array_ptr[fd] = NULL;
		}
		fd++;
	}
}

char	*ft_get_map(char *argv)
{
	int				fd;
	unsigned long	width;
	char			*line;
	char			*joined;
	char			*tmp;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error with map name/path\n"), NULL);
	joined = ft_strdup("");
	line = get_next_line(fd);
	if (!line)
		return (free(joined), close(fd), ft_printf("Empty map or read error\n"), NULL);
	width = ft_strlen(line) - 1;
	while (line != NULL)
	{
		if (width != ft_strlen(line) - 1)
			return (free(line), free(joined), close(fd), ft_printf("Error_Map is assymetric\n"), NULL);
		tmp = ft_strjoin(joined, line);
		free(joined);
		joined = tmp;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (joined);
}

int	ft_map_check(char *map)
{
	t_map	map_struct;
	int		i;

	i = 0;
	map_struct = (t_map){0, 0, 0, 0};
	while (map[i])
	{
		ft_printf("DEBUG: map[i]=%d ('%c') at i=%d\n", map[i], map[i], i);
		if (map[i] == 'C')
			map_struct.coin++;
		else if (map[i] == 'P')
			map_struct.player++;
		else if (map[i] == 'E')
			map_struct.exit++;
		else if (map[i] == '1')
			map_struct.wall++;
		else if (map[i] == '0' || map[i] == '\n' || map[i] == '\0')
			;
		else
			return (ft_printf("Wrong map |%c|\n", map[i]), 1);
		i++;
	}
	if (map_struct.coin < 1 || map_struct.player != 1 || map_struct.exit != 1)
		return (ft_printf("Error: Map is missing coin/player/exit\n"), 1);
	else
		return (0);
}

int	main(int argc, char **argv)
{
	char	*map;

	if (argc != 2)
		return (ft_printf("Error_argc is not 2\n"), 1);
	map = ft_get_map(argv[1]);
	ft_map_check(map);
	free(map);
	free_all_gnl();
	return (0);
}

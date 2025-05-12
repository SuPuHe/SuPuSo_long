/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:17:42 by omizin            #+#    #+#             */
/*   Updated: 2025/05/12 14:33:46 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
// # include "../mlx/include/MLX42/MLX42.h"
# include <fcntl.h>

typedef struct s_map
{
	char	**map;
	char	**copy_map;
	int		x;
	int		y;
	int		coin;
	int		player;
	int		exit;
	int		coin_check;
	int		exit_check;
}	t_map;

void	free_split(char **lines);
void	free_all_gnl(void);
void	cleanup_map(t_map *map);

int		get_input(t_map *map);
int		ft_map_check(t_map *map);
int		ft_get_map(char *argv, t_map *map);

char	**split_map_into_lines(char *map);
char	**copy_map(char **map, int y);

#endif

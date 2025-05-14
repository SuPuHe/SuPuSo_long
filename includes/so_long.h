/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:17:42 by omizin            #+#    #+#             */
/*   Updated: 2025/05/14 13:59:28 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "../mlx/include/MLX42/MLX42.h"
# include <fcntl.h>

# define PIXEL 128

typedef struct s_texture
{
	mlx_texture_t	*player;
	mlx_texture_t	*coin;
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
	mlx_texture_t	*exit;
	mlx_texture_t	*win;
	mlx_texture_t	*lose;
	mlx_texture_t	*enemy;
}	t_texture;

typedef struct s_img
{
	mlx_image_t	*player;
	mlx_image_t	*coin;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*exit;
	mlx_image_t	*win;
	mlx_image_t	*lose;
	mlx_image_t	*enemy;
}	t_img;

typedef struct s_map
{
	char	**map;
	char	**copy_map;
	int		x;
	int		y;
	int		coin;
	int		player;
	int		player_x;
	int		player_y;
	int		exit;
	int		coin_check;
	int		exit_check;
	mlx_t	*mlx;
	//t_img	*img;
	mlx_image_t			*wall;
	mlx_image_t			*floor;
	mlx_image_t			*player_img;
	mlx_image_t			*collectible;
	mlx_image_t			*exit_img;
}	t_map;

void	free_split(char **lines);
void	free_all_gnl(void);
void	cleanup_map(t_map *map);

int		get_input(t_map *map, char **argv, int argc);
int		ft_map_check(t_map *map);
int		ft_get_map(char *argv, t_map *map);

char	**split_map_into_lines(char *map);
char	**copy_map(char **map, int y);

#endif

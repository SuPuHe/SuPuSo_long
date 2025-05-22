/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:17:42 by omizin            #+#    #+#             */
/*   Updated: 2025/05/22 13:51:31 by omizin           ###   ########.fr       */
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
	//mlx_texture_t	*player;
	mlx_texture_t	*coin;
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
	mlx_texture_t	*exit;
	mlx_texture_t	*win;
	mlx_texture_t	*lose;
	//mlx_texture_t	*enemy;
}	t_texture;

typedef enum e_state {
	IDLE,
	RUN
}	t_state;

typedef enum e_dir {
	RIGHT,
	LEFT
}	t_dir;

typedef struct s_img
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*collectible;
	mlx_image_t	*exit_img;
	mlx_image_t	*player_img;
	mlx_image_t	*enemy;
}	t_img;

typedef struct s_player
{
	int				x;
	int				y;
	int				pixel_x;
	int				pixel_y;
	int				target_pixel_x;
	int				target_pixel_y;
	int				is_moving;
	int				move_speed;
	t_state			state;
	t_dir			dir;
	int				frame;
	int				frame_counter;
	mlx_texture_t	*textures[6];
	mlx_texture_t	*run[8];
}	t_player;


typedef struct s_enemy
{
	int				x;
	int				y;
	char			under;
	int				pixel_x;
	int				pixel_y;
	int				target_pixel_x;
	int				target_pixel_y;
	int				is_moving;
	int				move_speed;
	int				frame;
	int				frame_counter;
	t_dir			dir;
	mlx_texture_t	*texture[4];
	mlx_texture_t	*mirror[4];
}	t_enemy;


typedef struct s_map
{
	char	**map;
	char	**copy_map;
	int		x;
	int		y;
	int		coin;
	int		player_count;
	int		exit;
	int		coin_check;
	int		exit_check;
	int		moves;
	mlx_t	*mlx;

	t_player	player;
	t_enemy		enemy;
	t_img		img;
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

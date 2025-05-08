/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:17:42 by omizin            #+#    #+#             */
/*   Updated: 2025/05/08 12:58:11 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>

typedef struct s_map
{
	int	height;
	int	coin;
	int	player;
	int	exit;
}	t_map;

typedef struct s_map_copy
{
	int		height;
	int		width;
	int		x;
	int		y;
	int		coin;
	int		exit;
	char	**map_copy;
}	t_map_copy;

#endif

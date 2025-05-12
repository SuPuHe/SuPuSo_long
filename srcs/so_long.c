/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:18:20 by omizin            #+#    #+#             */
/*   Updated: 2025/05/12 14:47:05 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		return (ft_printf("Error: argc is not 2\n"), 1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4) != 0)
		return (ft_printf("Error: map is not in .ber format\n"), 1);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (1);
	if (ft_get_map(argv[1], map))
		return (free(map), 1);
	if (get_input(map))
		return (free(map), 1);
	cleanup_map(map);
	free(map);
	return (0);
}

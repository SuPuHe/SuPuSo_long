/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:18:20 by omizin            #+#    #+#             */
/*   Updated: 2025/05/08 13:27:26 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	*map;
	t_map	map_struct;

	map_struct = (t_map){0, 0, 0, 0};
	if (argc != 2)
		return (ft_printf("Error: argc is not 2\n"), 1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4) != 0)
		return (ft_printf("map is not in .ber format\n", 1));
	map = ft_get_map(argv[1]);
	if (!map)
		return (free_all_gnl(), 1);
	if (get_input(map, &map_struct) == 1)
		return (1);
	free(map);
	return (0);
}

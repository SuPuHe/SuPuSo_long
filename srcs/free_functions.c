/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:24:07 by omizin            #+#    #+#             */
/*   Updated: 2025/05/09 20:25:42 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_split(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

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

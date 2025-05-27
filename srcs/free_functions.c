/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:24:07 by omizin            #+#    #+#             */
/*   Updated: 2025/05/12 14:34:01 by omizin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_if_not_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free_if_not_null((void **)&arr[i]);
		i++;
	}
	free_if_not_null((void **)&arr);
}

void	cleanup_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	free_split(map->map);
	map->map = NULL;
	free_split(map->copy_map);
	map->copy_map = NULL;
	if (map->img.coin_instances)
	{
		i = 0;
		while (i < map->y)
		{
			free(map->img.coin_instances[i]);
			i++;
		}
		free(map->img.coin_instances);
	}
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

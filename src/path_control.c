#include "../inc/cub3d.h"
#include "../inc/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	so_path(t_cub3d *cub, char **path)
{
	if (!cub->so_path && path[1] && !path[2] && cub->compass_count <= 6 && cub->map_size == 0)
	{
		cub->so_path = path[1];
		cub->compass_count++;
	}
	else
		return (end_malloc(cub), exit(EXIT_FAILURE)); // bu duruma bakılacak
}

void	no_path(t_cub3d *cub, char **path)
{
	if (!cub->no_path && path[1] && !path[2] && cub->compass_count <= 6 && cub->map_size == 0)
	{
		cub->no_path = path[1];
		cub->compass_count++;
	}
	else
		return (end_malloc(cub), exit(EXIT_FAILURE)); // bu duruma bakılacak
}

void	we_path(t_cub3d *cub, char **path)
{
	if (!cub->we_path && path[1] && !path[2] && cub->compass_count <= 6 && cub->map_size == 0)
	{
		cub->we_path = path[1];
		cub->compass_count++;
	}
	else
		return (end_malloc(cub), exit(EXIT_FAILURE)); // bu duruma bakılacak
}

void	ea_path(t_cub3d *cub, char **path)
{
	if (!cub->ea_path && path[1] && !path[2] && cub->compass_count <= 6 && cub->map_size == 0)
	{
		cub->ea_path = path[1];
		cub->compass_count++;
	}
	else
		return (end_malloc(cub), exit(EXIT_FAILURE)); // bu duruma bakılacak
}

int	get_color(char **color)
{
	return (ft_atoi(color[0]) << 16 | ft_atoi(color[1]) << 8 |  ft_atoi(color[2]));
}

void	colour_f_and_c(t_cub3d *cub, char **path)
{
	char	**colour;

	if (path[1] && !path[2] && cub->compass_count <= 6 && cub->map_size == 0)
	{
		if (path[1][0] != ',' && path[1][ft_strlen(path[1]) - 1] != ',')
		{
			colour = ft_split(cub, path[1], ',');
			if (colour[3] == NULL)
			{
				if ((ft_strncmp(path[0], "F", 1) == 0))
					cub->f_colour = get_color(colour);
				else if ((ft_strncmp(path[0], "C", 1) == 0))
					cub->c_colour = get_color(colour);
			}
			else
				return (end_malloc(cub), exit(EXIT_FAILURE));
			// bu duruma bakılacak
		}
	}
	else
		return (end_malloc(cub), exit(EXIT_FAILURE)); // bu duruma bakılacak
}

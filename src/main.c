/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:10:56 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/08/23 18:16:19 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/get_next_line/get_next_line.h"
#include "../inc/libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void	file_name_check(char *str)
{
	size_t	i;

	if (!str)
		return (ft_putstr_fd("dosya uzantısı hatalı", 2), exit(EXIT_FAILURE));
	i = ft_strlen(str);
	if (str[i - 1] != 'b' && str[i - 2] != 'u' && str[i - 3] != 'c' && str[i
		- 4] != '.')
		return (ft_putstr_fd(str, 2), ft_putstr_fd(" :dosya uzantısı hatalı",
				2), exit(EXIT_FAILURE));
}

void	name_control(t_cub3d *cub, char *filename)
{
	char	*new_name;

	new_name = NULL;
	file_name_check(filename);
	cub->map_fd = open(filename, O_RDONLY);
	if (cub->map_fd < 0)
	{
		new_name = ft_strjoin("maps/", filename);
		if (my_malloc(cub->block, new_name))
			return (ft_putstr_fd(MALLOC, 2), end_malloc(cub),
				exit(EXIT_FAILURE));
		cub->map_fd = open(new_name, O_RDONLY);
		if (cub->map_fd < 0)
			return (ft_putstr_fd(MNF, 2), end_malloc(cub), exit(EXIT_FAILURE));
		cub->map_name = new_name;
	}
	else
	{
		cub->map_name = ft_strdup(filename);
		if (my_malloc(cub->block, cub->map_name))
			return (ft_putstr_fd(MALLOC, 2), end_malloc(cub),
				exit(EXIT_FAILURE));
	}
}

// renk kodları burda alınabilir
void	compass_control(t_cub3d *cub, char *line, char *append_space,
		char **ptr)
{
	line = get_next_line(cub->map_fd);
	while (line)
	{
		my_malloc(cub->block, line); // bu kısımda NULL kontrolü yapılmalı
		ptr = ft_split(cub, line, ' ');
		append_space = ft_strjoin(ptr[0], " ");
		if (my_malloc(cub->block, append_space))
			return (ft_putstr_fd(MALLOC, 2), end_malloc(cub),
				exit(EXIT_FAILURE));
		if (ft_strncmp(append_space, "SO ", 3) == 0)
			so_path(cub, ptr);
		else if (ft_strncmp(append_space, "NO ", 3) == 0)
			no_path(cub, ptr);
		else if (ft_strncmp(append_space, "WE ", 3) == 0)
			we_path(cub, ptr);
		else if (ft_strncmp(append_space, "EA ", 3) == 0)
			ea_path(cub, ptr);
		else if (ft_strncmp(append_space, "F ", 2) == 0
			|| ft_strncmp(append_space, "C ", 2) == 0)
			colour_f_and_c(cub, ptr);
		else if (line && line[0] != '\n')
			cub->map_size++;
		line = get_next_line(cub->map_fd);
	}
	close(cub->map_fd);
}

void	compass_file_contorl(t_cub3d *cub)
{
	int	fd;

	fd = open(cub->so_path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("erişilemeyen dosya", 2), end_malloc(cub),
			exit(EXIT_FAILURE));
	fd = open(cub->no_path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("erişilemeyen dosya", 2), end_malloc(cub),
			exit(EXIT_FAILURE));
	fd = open(cub->we_path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("erişilemeyen dosya", 2), end_malloc(cub),
			exit(EXIT_FAILURE));
	fd = open(cub->ea_path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("erişilemeyen dosya", 2), end_malloc(cub),
			exit(EXIT_FAILURE));
}

void	read_map(t_cub3d *cub, char *line)
{
    int i;

    i = 0;
	cub->map_fd = open(cub->map_name, O_RDONLY);
	if (cub->map_fd < 0)
		return (ft_putstr_fd("erişilemeyen dosya", 2), end_malloc(cub),
			exit(EXIT_FAILURE));
	cub->map = ft_calloc(cub->map_size, sizeof(char *));
	if (my_malloc(cub->block, cub->map))
		return (ft_putstr_fd(MALLOC, 2), end_malloc(cub), exit(EXIT_FAILURE));
	line = get_next_line(cub->map_fd);
	while (line)
	{
		my_malloc(cub->block, line); // bu kısımda NULL kontrolü yapılmalı
		if(line && (line[0] == '1' || line[0] == '0'))
        {
            cub->map[i] = line;
            i++;
        }
		line = get_next_line(cub->map_fd);
	}
    cub->map[i] = 0;
}

void	map_control(t_cub3d *cub, char *filename)
{
	char	*line;
	char	*append_space;
	char	**ptr;

	line = NULL;
	append_space = NULL;
	ptr = NULL;
	name_control(cub, filename);
	compass_control(cub, line, append_space, ptr);
	// compass_file_contorl(cub);
	if (cub->map_size > 0)
		read_map(cub, line);
    // else durumu eklenmeli
}

void	init_cub(t_cub3d *cub)
{
	cub->block = malloc_starter();
	cub->map_fd = 0;
    cub->map = NULL;
	cub->so_path = NULL;
	cub->no_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->map_size = 0;
	cub->compass_count = 0;
}

void	end_malloc(t_cub3d *cub)
{
	ft_lstclear_memory(&cub->block, free);
}

int	main(int ac, char **av)
{
	t_cub3d cub;

	if (ac == 2)
	{
		init_cub(&cub);
		map_control(&cub, av[1]);
		end_malloc(&cub);
	}
	else
		return (ft_putstr_fd(ARG_NUM, 2), FALSE);
	return (TRUE);
}
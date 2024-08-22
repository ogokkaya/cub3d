#include <fcntl.h>
#include "../inc/libft/libft.h"
#include <stdlib.h>
#include "../inc/get_next_line/get_next_line.h"
#include "../inc/cub3d.h"
#include <stdio.h>

static void	file_name_check(char *str)
{
	size_t	i;

	if (!str)
		return (ft_putstr_fd("dosya uzantısı hatalı", 2), exit(EXIT_FAILURE));
	i = ft_strlen(str);
	if (str[i - 1] != 'b' && str[i - 2] != 'u' && str[i - 3] != 'c' && str[i
			- 4] != '.')
		return (ft_putstr_fd(str, 2),ft_putstr_fd(" :dosya uzantısı hatalı", 2), exit(EXIT_FAILURE));
}

void name_control(t_cub3d *cub,char *filename)
{
    char *new_name;

    new_name = NULL;
    file_name_check(filename);
    cub->map_fd = open(filename, O_RDONLY);
    if(cub->map_fd < 0)
    {
        new_name = ft_strjoin("maps/", filename);
        if(my_malloc(cub->block, new_name))
            return(ft_putstr_fd(MALLOC, 2), end_malloc(cub),exit(EXIT_FAILURE));
        cub->map_fd = open(new_name, O_RDONLY);
        if(cub->map_fd < 0)
            return(ft_putstr_fd(MNF, 2), end_malloc(cub) ,exit(EXIT_FAILURE));
        cub->map_name = new_name;
    }
    else
    {
        cub->map_name = ft_strdup(filename);
        if(my_malloc(cub->block, cub->map_name))
            return(ft_putstr_fd(MALLOC, 2), end_malloc(cub) ,exit(EXIT_FAILURE));
    }
}

// renk kodları burda alınabilir
void compass_control(t_cub3d *cub)
{
    char *line;
    char **ptr;
    char *str;

    line = get_next_line(cub->map_fd); // malloc freee ler düzenlenicek
    while (line)
    {
        ptr = ft_split(cub ,line, ' ');
        str = ft_strjoin(ptr[0], " ");
        if(my_malloc(cub->block, str))
            return(ft_putstr_fd(MALLOC, 2), end_malloc(cub), exit(EXIT_FAILURE));
        if(ft_strncmp(str, "SO ", 3) == 0)
            so_path(cub, ptr);
        else if (ft_strncmp(str, "NO ", 3) == 0)
            no_path(cub, ptr);
        else if (ft_strncmp(str, "WE ", 3) == 0)
            we_path(cub, ptr);
        else if (ft_strncmp(str, "EA ", 3) == 0)
            ea_path(cub, ptr);
        line = get_next_line(cub->map_fd);
    }
}

void map_control(t_cub3d *cub, char *filename)
{
    name_control(cub,filename);
    compass_control(cub);
    // dosyaların erişilebilir olduğu kontrol edilecek
}

void init_cub(t_cub3d *cub)
{
    cub->block = malloc_starter();
    cub->map_fd = 0;
    cub->so_path = NULL;
    cub->no_path = NULL;
    cub->we_path = NULL;
    cub->ea_path = NULL;
    cub->compass_count = 0;
}

void	end_malloc(t_cub3d *cub)
{
	ft_lstclear_memory(&cub->block, free);
}

int main(int ac ,char **av)
{
    t_cub3d cub;

    if(ac == 2)
    {
        init_cub(&cub);
        map_control(&cub, av[1]);
        end_malloc(&cub);
    }
    else
        return(ft_putstr_fd(ARG_NUM, 2),FALSE);
    return(TRUE);
}
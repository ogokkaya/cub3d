#include "../inc/cub3d.h"
#include <stdlib.h>

void    so_path(t_cub3d *cub, char **path)
{
    if(!cub->so_path && path[1] && !path[2] && cub->compass_count <= 4)
    {
        cub->so_path = path[1];
        cub->compass_count++;
    }
    else
        return(end_malloc(cub), exit(EXIT_FAILURE));// bu duruma bakılacak
}

void    no_path(t_cub3d *cub, char **path)
{
    if(!cub->no_path && path[1] && !path[2] && cub->compass_count <= 4)
    {
        cub->no_path = path[1];
        cub->compass_count++;
    }
    else
        return(end_malloc(cub), exit(EXIT_FAILURE));// bu duruma bakılacak
}

void   we_path(t_cub3d *cub, char **path)
{
    if(!cub->we_path && path[1] && !path[2] && cub->compass_count <= 4)
    {
        cub->we_path = path[1];
        cub->compass_count++;
    }
    else
        return(end_malloc(cub), exit(EXIT_FAILURE));// bu duruma bakılacak
}

void    ea_path(t_cub3d *cub, char **path)
{
    if(!cub->ea_path && path[1] && !path[2] && cub->compass_count <= 4)
    {
        cub->ea_path = path[1];
        cub->compass_count++;
    }
    else
        return(end_malloc(cub), exit(EXIT_FAILURE));// bu duruma bakılacak
}

void colour_f_and_c(t_cub3d *cub, char **path, )
{

}

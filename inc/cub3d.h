#ifndef CUB3D_H
#define CUB3D_H


#define TRUE 0
#define FALSE 1
#define BUFFER_SIZE 1

//unsual
# define MALLOC " Error\nCould not allocate memory\n"
#define ARG_NUM "Error\n2 arguments are required for the program to run\n"
#define MNF "Error\nMap not found!\n"


typedef struct s_cub3d
{
	char 			   *map_name;
	char 				*so_path;
	char 				*no_path;
	char 				*we_path;
	char 				*ea_path;
	int 				compass_count;
	int 				map_fd;
	struct s_block     *block;
}               t_cub3d;


typedef struct s_block
{
	void				*allocate;
	struct s_block		*next;
}						t_block;


t_block			*malloc_starter(void);
int				my_malloc(t_block *block, void *address);
void			end_malloc(t_cub3d *cub);
void			ft_lstclear_memory(t_block **lst, void (*del)(void *));
void 			so_path(t_cub3d *cub, char **path);
void 			no_path(t_cub3d *cub, char **path);
void 			we_path(t_cub3d *cub, char **path);
void    		ea_path(t_cub3d *cub, char **path);

#endif
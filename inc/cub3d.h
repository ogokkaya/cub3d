#ifndef CUB3D_H
#define CUB3D_H

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 1200

#  if defined(__APPLE__) && defined(__MACH__)
	# define ESC_KEY 53
	# define P_KEY 35

	# define W_KEY 13
	# define S_KEY 1
	# define A_KEY 0
	# define D_KEY 2

	# define LEFT_KEY 123
	# define RIGHT_KEY 124
#  elif __linux__
	# define ESC_KEY 65307
	# define W_KEY 119
	# define S_KEY 115
	# define A_KEY 97
	# define D_KEY 100

	# define LEFT_KEY 65361
	# define RIGHT_KEY 65363
#  else
	#error "Unsupported operating system"
#  endif

#define TRUE 0
#define FALSE 1
#define BUFFER_SIZE 1

# define ROTATE_SPEED 0.05
# define MOVE_SPEED 0.055

//unsual
# define MALLOC " Error\nCould not allocate memory\n"
#define ARG_NUM "Error\n2 arguments are required for the program to run\n"
#define MNF "Error\nMap not found!\n"

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	p;
	int	left;
	int	right;
}				t_keys;

typedef struct s_player
{
	t_coord		pos;
	t_coord		dir;
	t_coord		plane;
	t_keys	movement;
}				t_player;

typedef struct	s_wall
{
	int	start;
	int	end;
	int	height;
}				t_wall;

typedef struct s_ray
{
	t_coord	ray;
	t_coord	dir;
	t_coord	side;
	t_coord	delta;
	t_coord	step;
	t_coord	plane;
	t_wall	wall;
	double	dist;
	int		side_hit;

}				t_ray;

typedef struct s_image
{
	char	*name;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			ray_count;
	char		**map;
	t_coord		on_map;
	t_ray		rays;
	t_image		main_img;
	t_image		north;
	t_image		south;
	t_image		east;
	t_image		west;
	t_player	player;
}				t_game;

typedef struct s_cub3d
{
	t_game				game;
	char 			  	*map_name;
	char 				**map;
	char 				**copy_map;
	char 				*clone_map;
	char 				*so_path;
	char 				*no_path;
	char 				*we_path;
	char 				*ea_path;
	int					char_x;
	int					char_y;
	int 				c_colour;
	int 				f_colour;
	int 				map_size;
	int 				compass_count;
	int 				map_fd;
	struct s_block     *block;
	struct s_block     *block2;
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
void 			compass_path(t_cub3d *cub, char **path, char *c_path);
void 			colour_f_and_c(t_cub3d *cub, char **path);
int				get_color(char **color);

void	hook(t_cub3d *game);
void	move_player(t_game *game);
void	put_pixel(t_image *img, int x, int y, int color);
void	draw_verticle_line(t_game *game, int ray_index);
void	minimap(t_game *game);
int	raycast(t_game *game);

#endif
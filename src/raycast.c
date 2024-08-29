#include "../inc/cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	calc_first_step(t_game *game)
{
	if (game->rays.dir.x < 0)
	{
		game->rays.step.x = -1;
		game->rays.side.x = (game->player.pos.x - game->on_map.x) * game->rays.delta.x;
	}
	else
	{
		game->rays.step.x = 1;
		game->rays.side.x = (game->on_map.x + 1.0 - game->player.pos.x) * game->rays.delta.x;
	}
	if (game->rays.dir.y < 0)
	{
		game->rays.step.y = -1;
		game->rays.side.y = (game->player.pos.y - game->on_map.y) * game->rays.delta.y;
	}
	else
	{
		game->rays.step.y = 1;
		game->rays.side.y = (game->on_map.y + 1.0 - game->player.pos.y) * game->rays.delta.y;
	}
}

void	init_ray(t_game *game, int ray_index)
{
	double	camera_x;

	camera_x =  2 * ray_index / (double)WINDOW_WIDTH - 1;
	game->rays.plane.x = game->player.plane.x * camera_x;
	game->rays.plane.y = game->player.plane.y * camera_x;
	game->rays.dir.x = game->player.dir.x + game->rays.plane.x;
	game->rays.dir.y = game->player.dir.y + game->rays.plane.y;
	game->rays.delta.x = fabs(1 / game->rays.dir.x);
	game->rays.delta.y = fabs(1 / game->rays.dir.y);
	game->on_map.x = (int)game->player.pos.x;
	game->on_map.y = (int)game->player.pos.y;
}

void	find_dist(t_game *game)
{
	while (1)
	{
		if (game->rays.side.x < game->rays.side.y)
		{
			game->rays.side.x += game->rays.delta.x;
			game->on_map.x += game->rays.step.x;
			game->rays.side_hit = 0;
		}
		else
		{
			game->rays.side.y += game->rays.delta.y;
			game->on_map.y += game->rays.step.y;
			game->rays.side_hit = 1;
		}
		if (game->map[(int)game->on_map.y][(int)game->on_map.x] == '1')
			break ;
	}
	if (game->rays.side_hit == 0)
		game->rays.dist = game->rays.side.x - game->rays.delta.x;
	else
		game->rays.dist = game->rays.side.y - game->rays.delta.y;
}

void	calc_wall_height(t_game *game)
{
	game->rays.wall.height = (int)(WINDOW_HEIGHT / game->rays.dist);
	game->rays.wall.start = -game->rays.wall.height / 2 + WINDOW_HEIGHT / 2;
	if (game->rays.wall.start < 0 || game->rays.wall.start >= WINDOW_HEIGHT)
		game->rays.wall.start = 0;
	game->rays.wall.end = game->rays.wall.height / 2 + WINDOW_HEIGHT / 2;
	if (game->rays.wall.end >= WINDOW_HEIGHT || game->rays.wall.end < 0)
		game->rays.wall.end = WINDOW_HEIGHT;
}

int	raycast(t_game *game)
{
	int	ray_index;

	ray_index = 0;
	move_player(game);
	while (ray_index < WINDOW_WIDTH)
	{
		init_ray(game, ray_index);
		calc_first_step(game);
		find_dist(game);
		calc_wall_height(game);
		draw_verticle_line(game, ray_index);
		ray_index++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->main_img.img, 0, 0);
	return (TRUE);
}

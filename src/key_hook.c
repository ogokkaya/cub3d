#include <math.h>
#include <stdlib.h>
#include "../inc/cub3d.h"
#include "../mlx/mlx.h"

int	exit_hook(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->main_img.img);
	exit(0);
}

/* int	check_plane_is_in_wall(t_game *game, int	flag)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		if (flag && game->map[(int)game->player.pos.y][(int)(game->player.pos.x + game->rays[i].plane.x)] == '1')
			return (0);	
		if (!flag && game->map[(int)(game->player.pos.y + game->rays[i].plane.y)][(int)game->player.pos.x] == '1')
			return (0);
		i++;
	}
	return (1);
} */

void	move_player(t_game *game)
{
	t_coord tmp_plane;
	t_coord	tmp_dir;

	if (game->player.movement.w)
	{
		if (game->map[(int)(game->player.pos.y + game->player.dir.y * (MOVE_SPEED))][(int)game->player.pos.x] == '0' /* && */ /* check_plane_is_in_wall(game, 0) */)
			game->player.pos.y += game->player.dir.y * MOVE_SPEED;
		if (game->map[(int)game->player.pos.y][(int)(game->player.pos.x + game->player.dir.x * (MOVE_SPEED))] == '0' /* && */ /* check_plane_is_in_wall(game, 1) */)
			game->player.pos.x += game->player.dir.x * MOVE_SPEED;
	}
	if (game->player.movement.s)
	{
		if (game->map[(int)game->player.pos.y][(int)(game->player.pos.x - game->player.dir.x * (MOVE_SPEED))] == '0' /* && */ /* check_plane_is_in_wall(game, 1) */)
			game->player.pos.x -= game->player.dir.x * MOVE_SPEED;
		if (game->map[(int)(game->player.pos.y - game->player.dir.y * (MOVE_SPEED))][(int)game->player.pos.x] == '0' /* && */ /* check_plane_is_in_wall(game, 0) */)
			game->player.pos.y -= game->player.dir.y * MOVE_SPEED;
	}
	if (game->player.movement.a)
	{
		if (game->map[(int)game->player.pos.y][(int)(game->player.pos.x + game->player.dir.y * (MOVE_SPEED))] == '0' /* && */ /* check_plane_is_in_wall(game, 1) */)
			game->player.pos.x += game->player.dir.y * MOVE_SPEED;
		if (game->map[(int)(game->player.pos.y - game->player.dir.x * (MOVE_SPEED))][(int)game->player.pos.x] == '0' /* && */ /* check_plane_is_in_wall(game, 0) */)
			game->player.pos.y -= game->player.dir.x * MOVE_SPEED;
	}
	if (game->player.movement.d)
	{
		if (game->map[(int)game->player.pos.y][(int)(game->player.pos.x - game->player.dir.y * (MOVE_SPEED))] == '0' /* && */ /* check_plane_is_in_wall(game, 1) */)
			game->player.pos.x -= game->player.dir.y * MOVE_SPEED;
		if (game->map[(int)(game->player.pos.y + game->player.dir.x * (MOVE_SPEED))][(int)game->player.pos.x] == '0' /* && */ /* check_plane_is_in_wall(game, 0) */)
			game->player.pos.y += game->player.dir.x * MOVE_SPEED;
	}
	if (game->player.movement.left)
	{
		tmp_dir = game->player.dir;
		game->player.dir.x = tmp_dir.x * cos(-ROTATE_SPEED) - tmp_dir.y * sin(-ROTATE_SPEED);
		game->player.dir.y = tmp_dir.x * sin(-ROTATE_SPEED) + tmp_dir.y * cos(-ROTATE_SPEED);
		tmp_plane = game->player.plane;
		game->player.plane.x = tmp_plane.x * cos(-ROTATE_SPEED) - tmp_plane.y * sin(-ROTATE_SPEED);
		game->player.plane.y = tmp_plane.x * sin(-ROTATE_SPEED) + tmp_plane.y * cos(-ROTATE_SPEED);
	}
	if (game->player.movement.right)
	{
		tmp_dir = game->player.dir;
		game->player.dir.x = tmp_dir.x * cos(ROTATE_SPEED) - tmp_dir.y * sin(ROTATE_SPEED);
		game->player.dir.y = tmp_dir.x * sin(ROTATE_SPEED) + tmp_dir.y * cos(ROTATE_SPEED);
		tmp_plane = game->player.plane;
		game->player.plane.x = tmp_plane.x * cos(ROTATE_SPEED) - tmp_plane.y * sin(ROTATE_SPEED);
		game->player.plane.y = tmp_plane.x * sin(ROTATE_SPEED) + tmp_plane.y * cos(ROTATE_SPEED);
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		exit_hook(game);
	if (keycode == P_KEY)
	{
		game->player.movement.p = !game->player.movement.p;
		if (game->player.movement.p)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
		mlx_mouse_move(game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	if (keycode == W_KEY)
		game->player.movement.w = 1;
	if (keycode == S_KEY)
		game->player.movement.s = 1;
	if (keycode == A_KEY)
		game->player.movement.a = 1;
	if (keycode == D_KEY)
		game->player.movement.d = 1;
	if (keycode == LEFT_KEY)
		game->player.movement.left = 1;
	if (keycode == RIGHT_KEY)
		game->player.movement.right = 1;
	return (1);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->player.movement.w = 0;
	if (keycode == S_KEY)
		game->player.movement.s = 0;
	if (keycode == A_KEY)
		game->player.movement.a = 0;
	if (keycode == D_KEY)
		game->player.movement.d = 0;
	if (keycode == LEFT_KEY)
		game->player.movement.left = 0;
	if (keycode == RIGHT_KEY)
		game->player.movement.right = 0;
	return (1);
}

int	mouse_rotate(int x, int y, t_game *game)
{
	t_coord tmp_dir;
	t_coord tmp_plane;

	if (game->player.movement.p)
	{
		mlx_mouse_get_pos(game->win, &x, &y);
		tmp_dir = game->player.dir;
		game->player.dir.x = tmp_dir.x * cos((x - WINDOW_WIDTH / 2) * 0.005) - tmp_dir.y * sin((x - WINDOW_WIDTH / 2) * 0.005);
		game->player.dir.y = tmp_dir.x * sin((x - WINDOW_WIDTH / 2) * 0.005) + tmp_dir.y * cos((x - WINDOW_WIDTH / 2) * 0.005);
		tmp_plane = game->player.plane;
		game->player.plane.x = tmp_plane.x * cos((x - WINDOW_WIDTH / 2) * 0.005) - tmp_plane.y * sin((x - WINDOW_WIDTH / 2) * 0.005);
		game->player.plane.y = tmp_plane.x * sin((x - WINDOW_WIDTH / 2) * 0.005) + tmp_plane.y * cos((x - WINDOW_WIDTH / 2) * 0.005);
		mlx_mouse_move(game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	return (1);
}

void	hook(t_cub3d *cub)
{
	mlx_hook(cub->game.win, 17, 0, exit_hook, &cub->game);
	mlx_hook(cub->game.win, 2, 1L<<1, key_press, &cub->game);
	mlx_hook(cub->game.win, 3, 1L<<0, key_release, &cub->game);
	mlx_hook(cub->game.win, 6, 1L<<4, mouse_rotate, &cub->game);
}


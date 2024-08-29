#include "../inc/cub3d.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = (img->size_line * y) + (x * img->bits_per_pixel / 8);
	*((unsigned int *)(offset + img->addr)) = color;
}



void	draw_verticle_line(t_game *game, int ray_index)
{
	int	i;

	i = 0;
	while (i < game->rays.wall.start)
	{
		put_pixel(&game->main_img, ray_index, i, 0x000000FF);
		i++;
	}
	i = 0;
	while (game->rays.wall.start + i < game->rays.wall.end)
	{
		if (game->rays.side_hit == 0)
			put_pixel(&game->main_img, ray_index, game->rays.wall.start + i, 0x00FFFF00);
		else
			put_pixel(&game->main_img, ray_index, game->rays.wall.start + i, 0x00FF0000);
		i++;
	}
	i = 0;
	while (game->rays.wall.end + i < WINDOW_HEIGHT)
	{
		put_pixel(&game->main_img, ray_index, game->rays.wall.end + i, 0x0000FF00);
		i++;
	}
}

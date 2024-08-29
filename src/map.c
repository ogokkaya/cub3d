#include <stdlib.h>
#include <string.h>
#include "../inc/cub3d.h"
#include <stdio.h>
void	minimap(t_game *game)
{
	unsigned int	max_height;
	unsigned int	max_width;
	unsigned int	x;
	unsigned int	y;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	max_height = WINDOW_HEIGHT / 5;
	max_width = WINDOW_WIDTH / 5;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			x = j * max_width / 10;
			while (x < (j + 1) * max_width / 10)
			{
				y = i * max_height / 10;
				while (y < (i + 1) * max_height / 10)
				{
					/* printf("%d - %d\n", i, j); */
					printf("%u -%u\n", x, y);
					printf("%u\n", max_height);
					if (game->map[i][j] == '1')
						put_pixel(&game->main_img, x, y, 0x0000FFFF);
					if (game->map[i][j] == '0')
						put_pixel(&game->main_img, x, y, 0x00000000);
					y++;
				}
				x++;
			}
			j++;
		}
		i++;
	}
	put_pixel(&game->main_img, game->player.pos.x * max_width / 10, game->player.pos.y * max_height / 10, 0x00FF0000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:11:18 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/08 22:34:48 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#define RES 100000

typedef	struct s_pointers
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		x;
	int		y;
}				t_pointers;

int		on_key(int key, t_pointers *param)
{
	int i;
	t_pointers *pt;

	pt = param;

	i = key;
	if (key == 53)
	{
		mlx_destroy_window(pt->mlx_ptr, pt->win_ptr);
		pt->mlx_ptr = 0;
		exit(0);
	}
	return (1);
}

int		on_click(int button, int x, int y, t_pointers *param)
{
	printf("button: %d x: %d, y: %d\n",button, x, y);
	mlx_pixel_put(param->mlx_ptr, param->win_ptr, x, y, 0x000fff);
	return (1);
}

void	draw_line(t_pointers *p, int x2, int y2)
{
	int i;
	int j;
	int err;
	int dx;
	int dy;

	i = p->x;
	j = p->y;
	if (i > x2)
		ft_swap(&i, &x2);
	if (j > y2)
		ft_swap(&j, &y2);
	dx = x2 - i;
	dy = y2 - j;
	err = dy - dx;
	ft_mod(&err);
	while (i < (x2 - 1) || j < (y2 - 1))
	{
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, i, j, 0x000fff);
		if (err >= 0)
		{
			j += 1;
			err -= dx;
		}
		else
		{
			i += 1;
			err += dy;
		}
	}
}

int		main(void)
{
	t_pointers *ptrs;
	int x2;
	int y2;

	ptrs = malloc(sizeof(t_pointers));
	ptrs->x = 250;
	ptrs->y = 250;
	ptrs->mlx_ptr = mlx_init();
	ptrs->win_ptr = mlx_new_window(ptrs->mlx_ptr, 500, 500, "mlx 42");
	x2 = 250;
	y2 = 500;
	while (x2 > 0)
	{
		draw_line(ptrs, x2, y2);
		x2--;
	}

	mlx_key_hook(ptrs->win_ptr, on_key, ptrs);
	mlx_mouse_hook(ptrs->win_ptr, on_click, ptrs);
	mlx_loop(ptrs->mlx_ptr);
}

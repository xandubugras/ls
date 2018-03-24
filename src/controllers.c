/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:57:16 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/09 12:14:35 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

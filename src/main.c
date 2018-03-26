/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:11:18 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/26 12:18:33 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	free_grid(t_grid **grid)
{
	int		i;
	int		j;

	j = 0;
	while (grid[j])
	{
		i = 0;
		while (grid[j][i].last == 0)
		{
			i++;
		}
		free(grid[j]);
		j++;
	}
	free(grid[j]);
}

int			main(int argc, char **argv)
{
	t_pointers	*ptrs;
	t_grid		**grid;

	if (argc != 2)
		return (1);
	grid = get_grid(argv[1]);
	convert_to_3d(grid);
	ptrs = malloc(sizeof(t_pointers));
	ptrs->mlx_ptr = mlx_init();
	ptrs->win_ptr = mlx_new_window(ptrs->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "mlx 42");
	link_points(ptrs, grid);
	mlx_key_hook(ptrs->win_ptr, on_key, ptrs);
	mlx_loop(ptrs->mlx_ptr);
	free(ptrs->mlx_ptr);
	free(ptrs->win_ptr);
	free(ptrs);
	free_grid(grid);
	return (0);
}

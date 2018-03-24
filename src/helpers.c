/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:58:11 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/23 19:14:27 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/fdf.h>

int		get_grid_height(char *file_name)
{
	int i;
	int fd;
	int asd;
	char *content;

	fd = open(file_name, O_RDONLY);
	i = 0;
	while ((asd = get_next_line(fd, &content)) != 0)
		i++;
	return (i);
}

int		get_grid_width_and_split(char ***splitted_line, int fd)
{
	char	*current_line;
	int		i;

	get_next_line(fd, &current_line);
	*splitted_line = ft_strsplit(current_line, ' ');
	i = 0;
	while ((*splitted_line)[i] != 0)
		i++;
	free(current_line);
	return (i);
}

static void	free_splitted_line(char **splitted_line)
{
	int j;

	j = 0;
	while (splitted_line[j] != 0)
	{
		free(splitted_line[j]);
		j++;
	}
}

t_grid	**get_grid(char *file_name)
{
	char	**splitted_line;
	t_grid	**grid;
	int		fd;
	int		i;
	int		j;
	int		height;

	fd = open(file_name, O_RDONLY); //opens file
	height = get_grid_height(file_name); // gets number of lines by iterating through the file
	grid = malloc(sizeof(t_grid *) * (height + 1)); // mallocs the size of the grid
	grid[height] = 0; // makes the last one 0
	j = 0; 
	while (j < height)
	{
		i = get_grid_width_and_split(&splitted_line, fd);
		grid[j] = construct_grid(i);
		grid[j][i - 1].last = 1;
		i = 0;
		while (1)
		{
			grid[j][i].z = ft_atoi(splitted_line[i]);
			grid[j][i].y = j * SCALE;
			grid[j][i].x = i * SCALE;
			if (grid[j][i].last)
				break;
			i++;
		}
		free_splitted_line(splitted_line);
		j++;
	}
	free(splitted_line);
	return (grid);
}

t_grid	*construct_grid(int num_of_grids)
{
	t_grid	*grid;
	int		i;

	grid = malloc(sizeof(t_grid) * num_of_grids);
	i = 0;
	while (i < num_of_grids)
	{
		grid[i].x = 0;
		grid[i].y = 0;
		grid[i].z = 0;
		grid[i].last = 0;
		i++;
	}
	return (grid);
}

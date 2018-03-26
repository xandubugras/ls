/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:58:11 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/26 12:16:32 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/fdf.h>

int			get_grid_height(char *file_name)
{
	int		i;
	int		fd;
	int		asd;
	char	*content;

	fd = open(file_name, O_RDONLY);
	i = 0;
	while ((asd = get_next_line(fd, &content)) != 0)
	{
		i++;
		free(content);
	}
	return (i);
}

int			get_grid_width_and_split(char ***splitted_line, int fd)
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

void		set_grid_line(int fd, t_grid **grid, int j)
{
	int		i;
	char	**splitted_line;

	i = get_grid_width_and_split(&splitted_line, fd);
	grid[j] = construct_grid(i);
	grid[j][i - 1].last = 1;
	i = 0;
	while (1)
	{
		grid[j][i].z = ft_atoi((splitted_line)[i]);
		grid[j][i].y = j * SCALE;
		grid[j][i].x = i * SCALE;
		if (grid[j][i].last)
			break ;
		i++;
	}
	free_splitted_line(splitted_line);
	free(splitted_line);
}

t_grid		**get_grid(char *file_name)
{
	t_grid	**grid;
	int		fd;
	int		j;
	int		height;

	fd = open(file_name, O_RDONLY);
	height = get_grid_height(file_name);
	grid = malloc(sizeof(t_grid *) * (height + 1));
	grid[height] = 0;
	j = 0;
	while (j < height)
	{
		set_grid_line(fd, grid, j);
		j++;
	}
	return (grid);
}

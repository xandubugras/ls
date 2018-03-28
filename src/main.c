/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:11:18 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 09:26:08 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"


int			main(int argc, char **argv)
{
	int				i;
	char			*target_name;
	t_input 		*input;

	system("clear");
	target_name = ".";
	input = new_input();
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			set_flags(argv[i], input);
		else
			break ;
		i++;
	}
	ft_ls(&(argv[i]), input, argc - i, ".");
}
/*
	if((directory = opendir(target_name)) == NULL)
	{
		target_name = ".";
		//list_file_only
		return (1);
	}
	while ((dir_info = readdir(directory)) != NULL)
	{
		ft_printf("file name: %s\n", dir_info->d_name);
		ft_printf("file type: %d\n", (dir_info->d_type));
		printf("file size: %lld\n", file_info.st_size);
		printf("file type: %d\n\n", file_info.st_mode);
	}
	ls -l abc cdb
	argc = 4
	argc - i = 2
*/

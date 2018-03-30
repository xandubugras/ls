/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:11:18 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/29 17:08:24 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

/*
** the main is responsible for setting the flags based on the arguments
*/

int		main(int argc, char **argv)
{
	int				i;
	char			*target_name;
	t_input			*input;

	target_name = ft_strdup(".");
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
	ft_ls(&(argv[i]), input, argc - i, target_name);
	free(target_name);
	free(input);
}

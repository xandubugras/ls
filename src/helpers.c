/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:32:32 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/27 15:06:27 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

void	*print_no_file_dir_err(char *file_name)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

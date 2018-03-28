/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:55:51 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 13:40:53 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

t_input	*new_input(void)
{
	t_input *new;

	new = malloc(sizeof(t_input));
	new->l = 0;
	new->R = 0;
	new->a = 0;
	new->r = 0;
	new->t = 0;
	return (new);
}

void	set_flags(char *arg, t_input *input)
{
	if (ft_strchr(arg, 'l'))
		input->l = 1;
	if (ft_strchr(arg, 'R'))
		input->R = 1;
	if (ft_strchr(arg, 'a'))
		input->a = 1;
	if (ft_strchr(arg, 'r'))
		input->r = 1;
	if (ft_strchr(arg, 't'))
		input->t = 1;
}	

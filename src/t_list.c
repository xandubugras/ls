/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 09:10:54 by adubugra          #+#    #+#             */
/*   Updated: 2018/03/28 09:31:55 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

t_file	*add_tlist_end(t_file **root, char *target_name, char *current_dir)
{
	t_file *t;

	if (!(*root))
	{
		*root = create_file(target_name, current_dir);
		ft_printf("add_tlist_end err: root is empty\n");
		return (*root);
	}
	t = *root;
	while (t->next != NULL)
		t = t->next;
	if ((t->next = create_file(target_name, current_dir)) == NULL)
		return (0);
	return (t->next);
}

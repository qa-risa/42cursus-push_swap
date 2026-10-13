/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:50:40 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:58:02 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max_index(t_stack *s)
{
	int	i;
	int	pos;

	pos = 0;
	i = 1;
	while (i < s->size)
	{
		if (s->data[i] > s->data[pos])
			pos = i;
		i++;
	}
	return (pos);
}

void	rotate_b_to_top(t_ps *ps, int pos)
{
	if (pos <= ps->b.size / 2)
	{
		while (pos > 0)
		{
			ps_op(ps, OP_RB);
			pos--;
		}
	}
	else
	{
		pos = ps->b.size - pos;
		while (pos > 0)
		{
			ps_op(ps, OP_RRB);
			pos--;
		}
	}
}

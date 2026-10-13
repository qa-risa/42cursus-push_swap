/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:50:48 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:58:04 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	int_sqrt(int n)
{
	int	i;

	i = 1;
	while ((i + 1) * (i + 1) <= n)
		i++;
	return (i);
}

static int	find_nearest_eligible(t_stack *a, int bound)
{
	int	i;

	i = 0;
	while (i <= a->size / 2)
	{
		if (a->data[i] < bound)
			return (i);
		if (a->data[a->size - 1 - i] < bound)
			return (a->size - 1 - i);
		i++;
	}
	return (0);
}

static void	push_to_chunks(t_ps *ps, int factor)
{
	int	pushed;
	int	pos;
	int	win;

	pushed = 0;
	while (ps->a.size > 0)
	{
		win = factor * int_sqrt(ps->a.size) / 4;
		pos = find_nearest_eligible(&ps->a, pushed + win);
		rotate_a_to_top(ps, pos);
		ps_op(ps, OP_PB);
		if (ps->b.size > 1 && ps->b.data[0] < pushed)
			ps_op(ps, OP_RB);
		pushed++;
	}
}

void	sort_medium(t_ps *ps)
{
	push_to_chunks(ps, CHUNK_FACTOR);
	while (ps->b.size > 0)
	{
		rotate_b_to_top(ps, find_max_index(&ps->b));
		ps_op(ps, OP_PA);
	}
}

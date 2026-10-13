/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:50:55 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/16 20:25:21 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_index(t_stack *s)
{
	int	i;
	int	pos;

	pos = 0;
	i = 1;
	while (i < s->size)
	{
		if (s->data[i] < s->data[pos])
			pos = i;
		i++;
	}
	return (pos);
}

void	rotate_a_to_top(t_ps *ps, int pos)
{
	if (pos <= ps->a.size / 2)
	{
		while (pos > 0)
		{
			ps_op(ps, OP_RA);
			pos--;
		}
	}
	else
	{
		pos = ps->a.size - pos;
		while (pos > 0)
		{
			ps_op(ps, OP_RRA);
			pos--;
		}
	}
}

void	sort_three(t_ps *ps)
{
	t_stack	*a;

	a = &ps->a;
	if (a->size < 2 || ps_is_sorted(a))
		return ;
	if (a->size == 2)
	{
		ps_op(ps, OP_SA);
		return ;
	}
	if (a->data[0] > a->data[1] && a->data[0] > a->data[2])
		ps_op(ps, OP_RA);
	else if (a->data[1] > a->data[0] && a->data[1] > a->data[2])
		ps_op(ps, OP_RRA);
	if (ps->a.data[0] > ps->a.data[1])
		ps_op(ps, OP_SA);
}

static void	rotate_min_up(t_ps *ps, int pos)
{
	while (pos > 0)
	{
		ps_op(ps, OP_RA);
		pos--;
	}
}

void	sort_simple(t_ps *ps)
{
	while (ps->a.size > 3)
	{
		if (ps->count <= 5)
			rotate_a_to_top(ps, find_min_index(&ps->a));
		else
			rotate_min_up(ps, find_min_index(&ps->a));
		ps_op(ps, OP_PB);
	}
	sort_three(ps);
	while (ps->b.size > 0)
		ps_op(ps, OP_PA);
}

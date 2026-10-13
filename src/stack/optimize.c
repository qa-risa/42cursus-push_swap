/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:51:07 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 12:01:22 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_inverse_pair(int a, int b)
{
	if ((a == OP_RA && b == OP_RRA) || (a == OP_RRA && b == OP_RA))
		return (1);
	if ((a == OP_RB && b == OP_RRB) || (a == OP_RRB && b == OP_RB))
		return (1);
	if ((a == OP_RR && b == OP_RRR) || (a == OP_RRR && b == OP_RR))
		return (1);
	if ((a == OP_PA && b == OP_PB) || (a == OP_PB && b == OP_PA))
		return (1);
	if (a == b && (a == OP_SA || a == OP_SB || a == OP_SS))
		return (1);
	return (0);
}

static int	merge_pair_code(int a, int b)
{
	if ((a == OP_SA && b == OP_SB) || (a == OP_SB && b == OP_SA))
		return (OP_SS);
	if ((a == OP_RA && b == OP_RB) || (a == OP_RB && b == OP_RA))
		return (OP_RR);
	if ((a == OP_RRA && b == OP_RRB) || (a == OP_RRB && b == OP_RRA))
		return (OP_RRR);
	return (-1);
}

static void	cancel_pass(t_rec *r, int *changed)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < r->size)
	{
		if (i + 1 < r->size && is_inverse_pair(r->codes[i], r->codes[i + 1]))
		{
			i += 2;
			*changed = 1;
		}
		else
		{
			r->codes[j] = r->codes[i];
			j++;
			i++;
		}
	}
	r->size = j;
}

static void	merge_pass(t_rec *r, int *changed)
{
	int	i;
	int	j;
	int	m;

	i = 0;
	j = 0;
	while (i < r->size)
	{
		m = -1;
		if (i + 1 < r->size)
			m = merge_pair_code(r->codes[i], r->codes[i + 1]);
		r->codes[j] = r->codes[i];
		if (m >= 0)
		{
			r->codes[j] = m;
			*changed = 1;
			i++;
		}
		j++;
		i++;
	}
	r->size = j;
}

void	optimize_sequence(t_rec *rec)
{
	int	changed;

	changed = 1;
	while (changed)
	{
		changed = 0;
		cancel_pass(rec, &changed);
		merge_pass(rec, &changed);
	}
}

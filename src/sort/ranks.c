/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:50:28 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:57:58 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_smaller(t_stack *a, int i)
{
	int	j;
	int	c;

	c = 0;
	j = 0;
	while (j < a->size)
	{
		if (a->data[j] < a->data[i])
			c++;
		j++;
	}
	return (c);
}

void	assign_ranks(t_ps *ps)
{
	int	*r;
	int	i;

	r = malloc(sizeof(int) * ps->a.size);
	if (!r)
		ps_error(ps);
	i = 0;
	while (i < ps->a.size)
	{
		r[i] = count_smaller(&ps->a, i);
		i++;
	}
	i = 0;
	while (i < ps->a.size)
	{
		ps->a.data[i] = r[i];
		i++;
	}
	free(r);
}

double	compute_disorder(t_stack *a)
{
	long	inv;
	long	pairs;
	int		i;
	int		j;

	inv = 0;
	pairs = 0;
	i = 0;
	while (i < a->size)
	{
		j = i + 1;
		while (j < a->size)
		{
			pairs++;
			if (a->data[i] > a->data[j])
				inv++;
			j++;
		}
		i++;
	}
	if (pairs == 0)
		return (0.0);
	return ((double)inv / (double)pairs);
}

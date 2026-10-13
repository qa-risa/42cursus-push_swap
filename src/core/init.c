/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:49:49 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:57:44 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_init(t_ps *ps)
{
	int	i;

	ps->a.data = NULL;
	ps->a.size = 0;
	ps->b.data = NULL;
	ps->b.size = 0;
	ps->record.codes = NULL;
	ps->record.size = 0;
	ps->record.capacity = 0;
	ps->count = 0;
	ps->strategy = STRAT_ADAPTIVE;
	ps->chosen = STRAT_ADAPTIVE;
	ps->bench_mode = 0;
	ps->disorder = 0.0;
	i = 0;
	while (i < OP_COUNT)
	{
		ps->op_count[i] = 0;
		i++;
	}
}

void	ps_alloc(t_ps *ps, int n)
{
	ps->a.data = malloc(sizeof(int) * n);
	ps->b.data = malloc(sizeof(int) * n);
	if (!ps->a.data || !ps->b.data)
		ps_error(ps);
}

void	ps_free(t_ps *ps)
{
	free(ps->a.data);
	free(ps->b.data);
	free(ps->record.codes);
	ps->a.data = NULL;
	ps->b.data = NULL;
	ps->record.codes = NULL;
}

void	ps_error(t_ps *ps)
{
	write(2, "Error\n", 6);
	if (ps)
		ps_free(ps);
	exit(1);
}

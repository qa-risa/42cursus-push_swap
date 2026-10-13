/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:50:01 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:57:51 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	pick_strategy_by_disorder(double d)
{
	if (d < LOW_DISORDER)
		return (STRAT_SIMPLE);
	if (d < HIGH_DISORDER)
		return (STRAT_MEDIUM);
	return (STRAT_COMPLEX);
}

static void	run_selected_strategy(t_ps *ps)
{
	ps->chosen = ps->strategy;
	if (ps->strategy == STRAT_ADAPTIVE)
		ps->chosen = pick_strategy_by_disorder(ps->disorder);
	if (ps_is_sorted(&ps->a))
		return ;
	if (ps->a.size <= 5)
		sort_simple(ps);
	else if (ps->chosen == STRAT_SIMPLE)
		sort_simple(ps);
	else if (ps->chosen == STRAT_MEDIUM)
		sort_medium(ps);
	else
		sort_complex(ps);
}

int	main(int argc, char **argv)
{
	t_ps	ps;

	ps_init(&ps);
	ps_parse(&ps, argc - 1, argv + 1);
	if (ps.count > 0)
	{
		ps.disorder = compute_disorder(&ps.a);
		assign_ranks(&ps);
		run_selected_strategy(&ps);
		print_ops(&ps);
		if (ps.bench_mode)
			print_bench(&ps);
	}
	ps_free(&ps);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:51:19 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:58:19 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*strategy_name(int strat)
{
	if (strat == STRAT_SIMPLE)
		return ("simple");
	if (strat == STRAT_MEDIUM)
		return ("medium");
	if (strat == STRAT_COMPLEX)
		return ("complex");
	return ("adaptive");
}

static char	*strategy_class(int strat)
{
	if (strat == STRAT_SIMPLE)
		return ("O(n^2)");
	if (strat == STRAT_MEDIUM)
		return ("O(n*sqrt(n))");
	if (strat == STRAT_COMPLEX)
		return ("O(n log n)");
	return ("disorder-based");
}

static void	print_percent(double d)
{
	long	v;

	v = (long)(d * 10000.0 + 0.5);
	ft_putnbr_fd(v / 100, 2);
	ft_putstr_fd(".", 2);
	ft_putnbr_fd((v / 10) % 10, 2);
	ft_putnbr_fd(v % 10, 2);
	ft_putstr_fd("%\n", 2);
}

static void	print_counts(t_ps *ps)
{
	int	i;

	i = 0;
	while (i < OP_COUNT)
	{
		ft_putstr_fd("[bench] ", 2);
		ft_putstr_fd(op_name(i), 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(ps->op_count[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}

void	print_bench(t_ps *ps)
{
	ft_putstr_fd("[bench] disorder: ", 2);
	print_percent(ps->disorder);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putstr_fd(strategy_name(ps->strategy), 2);
	if (ps->strategy == STRAT_ADAPTIVE)
	{
		ft_putstr_fd(" -> ", 2);
		ft_putstr_fd(strategy_name(ps->chosen), 2);
	}
	ft_putstr_fd(" [", 2);
	ft_putstr_fd(strategy_class(ps->chosen), 2);
	ft_putstr_fd("]\n[bench] total operations: ", 2);
	ft_putnbr_fd(ps->record.size, 2);
	ft_putstr_fd("\n", 2);
	print_counts(ps);
}

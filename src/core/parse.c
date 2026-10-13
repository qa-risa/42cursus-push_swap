/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:50:21 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:57:55 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	parse_flag(t_ps *ps, const char *s)
{
	if (ft_strcmp(s, "--simple") == 0)
		ps->strategy = STRAT_SIMPLE;
	else if (ft_strcmp(s, "--medium") == 0)
		ps->strategy = STRAT_MEDIUM;
	else if (ft_strcmp(s, "--complex") == 0)
		ps->strategy = STRAT_COMPLEX;
	else if (ft_strcmp(s, "--adaptive") == 0)
		ps->strategy = STRAT_ADAPTIVE;
	else if (ft_strcmp(s, "--bench") == 0)
		ps->bench_mode = 1;
	else
		ps_error(ps);
}

static void	parse_all_numbers(t_ps *ps, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!(av[i][0] == '-' && av[i][1] == '-'))
			parse_arg_numbers(ps, av[i]);
		i++;
	}
}

void	ps_parse(t_ps *ps, int ac, char **av)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1] == '-')
			parse_flag(ps, av[i]);
		else
			n += count_tokens(ps, av[i]);
		i++;
	}
	ps->count = n;
	if (n == 0)
		return ;
	ps_alloc(ps, n);
	parse_all_numbers(ps, ac, av);
	check_duplicates(ps);
}

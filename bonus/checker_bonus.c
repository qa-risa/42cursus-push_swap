/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:51:01 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/06 18:20:26 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	checker_parse(t_ps *ps, int ac, char **av)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (i < ac)
	{
		n += count_tokens(ps, av[i]);
		i++;
	}
	ps->count = n;
	ps_alloc(ps, n);
	i = 0;
	while (i < ac)
	{
		parse_arg_numbers(ps, av[i]);
		i++;
	}
	check_duplicates(ps);
}

static int	read_line(t_ps *ps, char *buf)
{
	int		i;
	int		r;
	char	c;

	i = 0;
	r = read(0, &c, 1);
	while (r > 0 && c != '\n')
	{
		if (i >= 15)
			ps_error(ps);
		buf[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	if (r < 0)
		ps_error(ps);
	buf[i] = '\0';
	if (r == 0 && i == 0)
		return (0);
	return (1);
}

static int	op_from_name(const char *s)
{
	if (ft_strcmp(s, "sa") == 0)
		return (OP_SA);
	if (ft_strcmp(s, "sb") == 0)
		return (OP_SB);
	if (ft_strcmp(s, "ss") == 0)
		return (OP_SS);
	if (ft_strcmp(s, "pa") == 0)
		return (OP_PA);
	if (ft_strcmp(s, "pb") == 0)
		return (OP_PB);
	if (ft_strcmp(s, "ra") == 0)
		return (OP_RA);
	if (ft_strcmp(s, "rb") == 0)
		return (OP_RB);
	if (ft_strcmp(s, "rr") == 0)
		return (OP_RR);
	if (ft_strcmp(s, "rra") == 0)
		return (OP_RRA);
	if (ft_strcmp(s, "rrb") == 0)
		return (OP_RRB);
	if (ft_strcmp(s, "rrr") == 0)
		return (OP_RRR);
	return (-1);
}

static void	read_and_exec(t_ps *ps)
{
	char	buf[16];
	int		code;

	while (read_line(ps, buf) == 1)
	{
		code = op_from_name(buf);
		if (code < 0)
			ps_error(ps);
		ps_apply(ps, code);
	}
}

int	main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (0);
	ps_init(&ps);
	checker_parse(&ps, argc - 1, argv + 1);
	read_and_exec(&ps);
	if (ps_is_sorted(&ps.a) && ps.b.size == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	ps_free(&ps);
	return (0);
}

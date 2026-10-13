/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:50:14 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:57:53 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_one_number(t_ps *ps, const char *s, int *i)
{
	long	val;
	long	sign;
	int		dig;

	val = 0;
	sign = 1;
	dig = 0;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	while (ft_isdigit(s[*i]))
	{
		val = val * 10 + (s[*i] - '0');
		if (val * sign > 2147483647 || val * sign < -2147483648)
			ps_error(ps);
		dig++;
		(*i)++;
	}
	if (dig == 0 || (s[*i] != '\0' && !ft_isspace(s[*i])))
		ps_error(ps);
	return ((int)(val * sign));
}

int	count_tokens(t_ps *ps, const char *s)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ft_isspace(s[i]))
			i++;
		if (s[i] != '\0')
			n++;
		while (s[i] != '\0' && !ft_isspace(s[i]))
			i++;
	}
	if (n == 0)
		ps_error(ps);
	return (n);
}

void	parse_arg_numbers(t_ps *ps, const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ft_isspace(s[i]))
			i++;
		if (s[i] != '\0')
		{
			ps->a.data[ps->a.size] = parse_one_number(ps, s, &i);
			ps->a.size++;
		}
	}
}

void	check_duplicates(t_ps *ps)
{
	int	i;
	int	j;

	i = 0;
	while (i < ps->a.size)
	{
		j = i + 1;
		while (j < ps->a.size)
		{
			if (ps->a.data[i] == ps->a.data[j])
				ps_error(ps);
			j++;
		}
		i++;
	}
}

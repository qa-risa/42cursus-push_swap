/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:51:25 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:58:16 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*op_name(int code)
{
	if (code == OP_SA)
		return ("sa");
	if (code == OP_SB)
		return ("sb");
	if (code == OP_SS)
		return ("ss");
	if (code == OP_PA)
		return ("pa");
	if (code == OP_PB)
		return ("pb");
	if (code == OP_RA)
		return ("ra");
	if (code == OP_RB)
		return ("rb");
	if (code == OP_RR)
		return ("rr");
	if (code == OP_RRA)
		return ("rra");
	if (code == OP_RRB)
		return ("rrb");
	return ("rrr");
}

static void	print_op(t_ps *ps, int code)
{
	ft_putstr_fd(op_name(code), 1);
	ft_putstr_fd("\n", 1);
	ps->op_count[code]++;
}

void	print_ops(t_ps *ps)
{
	int	i;

	optimize_sequence(&ps->record);
	i = 0;
	while (i < ps->record.size)
	{
		print_op(ps, ps->record.codes[i]);
		i++;
	}
}

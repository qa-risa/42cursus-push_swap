/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:51:01 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:58:12 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_push(t_stack *src, t_stack *dst)
{
	int	i;

	if (src->size == 0)
		return ;
	i = dst->size;
	while (i > 0)
	{
		dst->data[i] = dst->data[i - 1];
		i--;
	}
	dst->data[0] = src->data[0];
	dst->size++;
	i = 0;
	while (i < src->size - 1)
	{
		src->data[i] = src->data[i + 1];
		i++;
	}
	src->size--;
}

static void	record_grow(t_ps *ps)
{
	int	*new_codes;
	int	new_capacity;
	int	i;

	new_capacity = ps->record.capacity * 2;
	if (new_capacity == 0)
		new_capacity = 256;
	new_codes = malloc(sizeof(int) * new_capacity);
	if (!new_codes)
		ps_error(ps);
	i = 0;
	while (i < ps->record.size)
	{
		new_codes[i] = ps->record.codes[i];
		i++;
	}
	free(ps->record.codes);
	ps->record.codes = new_codes;
	ps->record.capacity = new_capacity;
}

static void	record_add(t_ps *ps, int code)
{
	if (ps->record.size == ps->record.capacity)
		record_grow(ps);
	ps->record.codes[ps->record.size] = code;
	ps->record.size++;
}

void	ps_apply(t_ps *ps, int code)
{
	if (code == OP_SA || code == OP_SS)
		stack_swap(&ps->a);
	if (code == OP_SB || code == OP_SS)
		stack_swap(&ps->b);
	if (code == OP_PA)
		stack_push(&ps->b, &ps->a);
	if (code == OP_PB)
		stack_push(&ps->a, &ps->b);
	if (code == OP_RA || code == OP_RR)
		stack_rotate(&ps->a);
	if (code == OP_RB || code == OP_RR)
		stack_rotate(&ps->b);
	if (code == OP_RRA || code == OP_RRR)
		stack_reverse_rotate(&ps->a);
	if (code == OP_RRB || code == OP_RRR)
		stack_reverse_rotate(&ps->b);
}

void	ps_op(t_ps *ps, int code)
{
	ps_apply(ps, code);
	record_add(ps, code);
}

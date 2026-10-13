/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:51:13 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/08 11:58:14 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_swap(t_stack *s)
{
	int	tmp;

	if (s->size < 2)
		return ;
	tmp = s->data[0];
	s->data[0] = s->data[1];
	s->data[1] = tmp;
}

void	stack_rotate(t_stack *s)
{
	int	tmp;
	int	i;

	if (s->size < 2)
		return ;
	tmp = s->data[0];
	i = 0;
	while (i < s->size - 1)
	{
		s->data[i] = s->data[i + 1];
		i++;
	}
	s->data[s->size - 1] = tmp;
}

void	stack_reverse_rotate(t_stack *s)
{
	int	tmp;
	int	i;

	if (s->size < 2)
		return ;
	tmp = s->data[s->size - 1];
	i = s->size - 1;
	while (i > 0)
	{
		s->data[i] = s->data[i - 1];
		i--;
	}
	s->data[0] = tmp;
}

int	ps_is_sorted(t_stack *s)
{
	int	i;

	i = 0;
	while (i + 1 < s->size)
	{
		if (s->data[i] > s->data[i + 1])
			return (0);
		i++;
	}
	return (1);
}

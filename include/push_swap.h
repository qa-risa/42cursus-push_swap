/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 03:49:31 by aiwane            #+#    #+#             */
/*   Updated: 2026/07/06 18:20:31 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

# define OP_SA 0
# define OP_SB 1
# define OP_SS 2
# define OP_PA 3
# define OP_PB 4
# define OP_RA 5
# define OP_RB 6
# define OP_RR 7
# define OP_RRA 8
# define OP_RRB 9
# define OP_RRR 10
# define OP_COUNT 11

# define STRAT_ADAPTIVE 0
# define STRAT_SIMPLE 1
# define STRAT_MEDIUM 2
# define STRAT_COMPLEX 3

# define CHUNK_FACTOR 7
# define LOW_DISORDER 0.2
# define HIGH_DISORDER 0.5

typedef struct s_stack
{
	int		*data;
	int		size;
}			t_stack;

typedef struct s_rec
{
	int		*codes;
	int		size;
	int		capacity;
}			t_rec;

typedef struct s_ps
{
	t_stack	a;
	t_stack	b;
	t_rec	record;
	int		count;
	int		strategy;
	int		chosen;
	int		bench_mode;
	int		op_count[OP_COUNT];
	double	disorder;
}			t_ps;

void		ps_init(t_ps *ps);
void		ps_alloc(t_ps *ps, int n);
void		ps_free(t_ps *ps);
void		ps_error(t_ps *ps);
void		ps_parse(t_ps *ps, int ac, char **av);
int			count_tokens(t_ps *ps, const char *s);
void		parse_arg_numbers(t_ps *ps, const char *s);
void		check_duplicates(t_ps *ps);
void		stack_swap(t_stack *s);
void		stack_rotate(t_stack *s);
void		stack_reverse_rotate(t_stack *s);
void		stack_push(t_stack *src, t_stack *dst);
int			ps_is_sorted(t_stack *s);
void		ps_apply(t_ps *ps, int code);
void		ps_op(t_ps *ps, int code);
void		optimize_sequence(t_rec *rec);
char		*op_name(int code);
void		print_ops(t_ps *ps);
int			ft_strcmp(const char *a, const char *b);
int			ft_isdigit(int c);
int			ft_isspace(int c);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putnbr_fd(long n, int fd);
void		assign_ranks(t_ps *ps);
double		compute_disorder(t_stack *a);
int			find_min_index(t_stack *s);
int			find_max_index(t_stack *s);
void		rotate_b_to_top(t_ps *ps, int pos);
void		rotate_a_to_top(t_ps *ps, int pos);
void		sort_three(t_ps *ps);
void		sort_simple(t_ps *ps);
void		sort_medium(t_ps *ps);
void		sort_complex(t_ps *ps);
void		print_bench(t_ps *ps);

#endif

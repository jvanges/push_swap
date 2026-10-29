/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

/*
** Op indexes used for the per-operation counters (bench mode).
*/
enum	e_op
{
	OP_SA = 0,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_COUNT
};

/*
** t_ctx holds both stacks (top = index 0), the recorded operation
** stream and the benchmark counters.
*/
typedef struct s_ctx
{
	int		*a;
	int		*b;
	int		size_a;
	int		size_b;
	int		cap;
	long	counts[OP_COUNT];
	char	*ops;
	size_t	ops_len;
	size_t	ops_cap;
	int		record;
}	t_ctx;

typedef struct s_flags
{
	int		bench;
	char	strategy;
	double	disorder;
	long	mistakes;
	long	total_pairs;
}	t_flags;

typedef struct s_strat
{
	const char	*name;
	const char	*class;
}	t_strat;

/* parse.c */
int		count_numbers(int argc, char **argv);
int		parse_args(int argc, char **argv, t_ctx *ctx, t_flags *fl);
long	ft_atol_check(const char *s, int *ok);

/* stack.c */
int		ctx_init(t_ctx *ctx, int cap);
void	ctx_free(t_ctx *ctx);
int		is_sorted(t_ctx *ctx);
void	compress_ranks(t_ctx *ctx);

/* ops_record.c */
void	record_op(t_ctx *ctx, int op, const char *name, size_t len);

/* ops.c */
void	do_sa(t_ctx *ctx);
void	do_sb(t_ctx *ctx);
void	do_pa(t_ctx *ctx);
void	do_pb(t_ctx *ctx);
void	do_ra(t_ctx *ctx);
void	do_rb(t_ctx *ctx);
void	do_rra(t_ctx *ctx);
void	do_rrb(t_ctx *ctx);

/* utils.c */
void	free_strs(char **strs);
int		i_sqrt(int n);
int		index_of_min(int *stack, int size);
int		index_of_max(int *stack, int size);
void	rot_to_top(t_ctx *ctx, int idx, int is_b);

/* disorder.c */
void	compute_disorder(t_ctx *ctx, t_flags *fl);

/* sort_small.c */
void	sort_small(t_ctx *ctx);

/* strategies */
void	sort_simple(t_ctx *ctx);
void	sort_medium(t_ctx *ctx);
void	sort_complex(t_ctx *ctx);
void	sort_adaptive(t_ctx *ctx, t_flags *fl, t_strat *st);

/* dispatch.c */
t_strat	dispatch(t_ctx *ctx, t_flags *fl);

/* bench.c */
void	print_bench(t_ctx *ctx, t_flags *fl, t_strat st);

#endif

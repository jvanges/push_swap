/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Index in b of the largest element strictly smaller than x,
** i.e. the element x must be pushed on top of to keep b sorted
** descending (circularly). Falls back to the current maximum of b
** when x is a new extreme.
*/
static int	predecessor_index(t_ctx *ctx, int x)
{
	int	i;
	int	pred;

	pred = -1;
	i = 0;
	while (i < ctx->size_b)
	{
		if (ctx->b[i] < x && (pred == -1 || ctx->b[i] > ctx->b[pred]))
			pred = i;
		i++;
	}
	if (pred == -1)
		pred = index_of_max(ctx->b, ctx->size_b);
	return (pred);
}

/*
** Insertion sort adaptation, O(n^2) in push_swap operations but
** near-linear on low-disorder inputs: b is kept sorted (circularly,
** descending from its maximum) and every new top of a is inserted
** at its correct position with at most |b|/2 rotations. Popping b
** back (pa) then yields a sorted ascending stack a.
*/
static void	sort_insert(t_ctx *ctx)
{
	while (ctx->size_a > 0)
	{
		if (ctx->size_b > 1)
			rot_to_top(ctx, predecessor_index(ctx, ctx->a[0]), 1);
		do_pb(ctx);
	}
	rot_to_top(ctx, index_of_max(ctx->b, ctx->size_b), 1);
	while (ctx->size_b > 0)
		do_pa(ctx);
}

/*
** Adaptive strategy: the internal method is selected from the
** disorder measured on the initial stack (before any move):
**   disorder < 0.2         -> insertion sort, O(n^2)
**   0.2 <= disorder < 0.5  -> chunk sort,      O(n sqrt(n))
**   disorder >= 0.5        -> radix sort,      O(n log n)
*/
void	sort_adaptive(t_ctx *ctx, t_flags *fl, t_strat *st)
{
	if (fl->disorder < 0.2)
	{
		st->name = "Adaptive: insertion sort (low disorder)";
		st->class = "O(n^2)";
		sort_insert(ctx);
	}
	else if (fl->disorder < 0.5)
	{
		st->name = "Adaptive: chunk sort (medium disorder)";
		st->class = "O(n*sqrt(n))";
		sort_medium(ctx);
	}
	else
	{
		st->name = "Adaptive: radix sort LSD (high disorder)";
		st->class = "O(n log n)";
		sort_complex(ctx);
	}
}

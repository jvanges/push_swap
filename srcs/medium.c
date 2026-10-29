/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Push to b every rank below the current chunk limit.
** Lower-half ranks are rotated to the bottom of b so that the
** biggest values stay close to the top for the pull-back phase.
*/
static void	push_chunks(t_ctx *ctx, int chunk_size)
{
	int	limit;
	int	pushed;
	int	half;

	limit = chunk_size;
	pushed = 0;
	while (ctx->size_a > 0)
	{
		if (ctx->a[0] < limit)
		{
			do_pb(ctx);
			pushed++;
			if (pushed == limit && limit < ctx->cap)
			{
				limit += chunk_size;
				if (limit > ctx->cap)
					limit = ctx->cap;
			}
			half = limit - chunk_size + (chunk_size >> 1);
			if (ctx->b[0] < half)
				do_rb(ctx);
		}
		else
			do_ra(ctx);
	}
}

/*
** Chunk sort, O(n * sqrt(n)) in push_swap operations:
** ranks are pushed to b in sqrt(n) ascending chunks, then pulled
** back to a by always extracting the current maximum of b.
*/
void	sort_medium(t_ctx *ctx)
{
	int	chunk_size;
	int	chunks;

	chunks = i_sqrt(ctx->cap);
	if (chunks < 1)
		chunks = 1;
	chunk_size = (ctx->cap + chunks - 1) / chunks;
	push_chunks(ctx, chunk_size);
	while (ctx->size_b > 0)
	{
		rot_to_top(ctx, index_of_max(ctx->b, ctx->size_b), 1);
		do_pa(ctx);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Selection sort adaptation (O(n^2) in push_swap operations):
** repeatedly locate the minimum of a, rotate it to the top and pb.
** b then holds the extracted ranks in descending order from top
** to bottom; sort_small() sorts the 3 biggest kept in a and the
** pa sequence rebuilds a sorted ascending stack.
*/
void	sort_simple(t_ctx *ctx)
{
	while (ctx->size_a > 3)
	{
		rot_to_top(ctx, index_of_min(ctx->a, ctx->size_a), 0);
		do_pb(ctx);
	}
	sort_small(ctx);
}

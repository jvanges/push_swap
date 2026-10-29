/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_3(t_ctx *ctx)
{
	int	*a;

	a = ctx->a;
	if (a[0] > a[1] && a[0] > a[2])
		do_ra(ctx);
	else if (a[1] > a[0] && a[1] > a[2])
		do_rra(ctx);
	if (ctx->a[0] > ctx->a[1])
		do_sa(ctx);
}

/*
** Optimal-ish sorts for tiny inputs (n <= 5), used by every strategy
** since the complexity class does not change the constant factor here.
*/
void	sort_small(t_ctx *ctx)
{
	if (ctx->size_a == 2)
	{
		if (ctx->a[0] > ctx->a[1])
			do_sa(ctx);
		return ;
	}
	while (ctx->size_a > 3)
	{
		rot_to_top(ctx, index_of_min(ctx->a, ctx->size_a), 0);
		do_pb(ctx);
	}
	sort_3(ctx);
	while (ctx->size_b > 0)
		do_pa(ctx);
}

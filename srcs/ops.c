/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_sa(t_ctx *ctx)
{
	int	tmp;

	if (ctx->size_a < 2)
		return ;
	tmp = ctx->a[0];
	ctx->a[0] = ctx->a[1];
	ctx->a[1] = tmp;
	record_op(ctx, OP_SA, "sa\n", 3);
}

void	do_sb(t_ctx *ctx)
{
	int	tmp;

	if (ctx->size_b < 2)
		return ;
	tmp = ctx->b[0];
	ctx->b[0] = ctx->b[1];
	ctx->b[1] = tmp;
	record_op(ctx, OP_SB, "sb\n", 3);
}

void	do_pa(t_ctx *ctx)
{
	int	val;

	if (ctx->size_b == 0)
		return ;
	val = ctx->b[0];
	ft_memmove(ctx->b, ctx->b + 1, sizeof(int) * (ctx->size_b - 1));
	ctx->size_b--;
	ft_memmove(ctx->a + 1, ctx->a, sizeof(int) * ctx->size_a);
	ctx->size_a++;
	ctx->a[0] = val;
	record_op(ctx, OP_PA, "pa\n", 3);
}

void	do_pb(t_ctx *ctx)
{
	int	val;

	if (ctx->size_a == 0)
		return ;
	val = ctx->a[0];
	ft_memmove(ctx->a, ctx->a + 1, sizeof(int) * (ctx->size_a - 1));
	ctx->size_a--;
	ft_memmove(ctx->b + 1, ctx->b, sizeof(int) * ctx->size_b);
	ctx->size_b++;
	ctx->b[0] = val;
	record_op(ctx, OP_PB, "pb\n", 3);
}

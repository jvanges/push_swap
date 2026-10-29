/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_ra(t_ctx *ctx)
{
	int	tmp;

	if (ctx->size_a < 2)
		return ;
	tmp = ctx->a[0];
	ft_memmove(ctx->a, ctx->a + 1, sizeof(int) * (ctx->size_a - 1));
	ctx->a[ctx->size_a - 1] = tmp;
	record_op(ctx, OP_RA, "ra\n", 3);
}

void	do_rb(t_ctx *ctx)
{
	int	tmp;

	if (ctx->size_b < 2)
		return ;
	tmp = ctx->b[0];
	ft_memmove(ctx->b, ctx->b + 1, sizeof(int) * (ctx->size_b - 1));
	ctx->b[ctx->size_b - 1] = tmp;
	record_op(ctx, OP_RB, "rb\n", 3);
}

void	do_rra(t_ctx *ctx)
{
	int	tmp;

	if (ctx->size_a < 2)
		return ;
	tmp = ctx->a[ctx->size_a - 1];
	ft_memmove(ctx->a + 1, ctx->a, sizeof(int) * (ctx->size_a - 1));
	ctx->a[0] = tmp;
	record_op(ctx, OP_RRA, "rra\n", 4);
}

void	do_rrb(t_ctx *ctx)
{
	int	tmp;

	if (ctx->size_b < 2)
		return ;
	tmp = ctx->b[ctx->size_b - 1];
	ft_memmove(ctx->b + 1, ctx->b, sizeof(int) * (ctx->size_b - 1));
	ctx->b[0] = tmp;
	record_op(ctx, OP_RRB, "rrb\n", 4);
}

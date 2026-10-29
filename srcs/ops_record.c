/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*grow_buffer(t_ctx *ctx, size_t need)
{
	char	*new_ops;

	if (ctx->ops_cap == 0)
		ctx->ops_cap = 4096;
	while (ctx->ops_cap < need)
		ctx->ops_cap *= 2;
	new_ops = malloc(ctx->ops_cap);
	if (!new_ops)
	{
		ctx_free(ctx);
		write(2, "Error\n", 6);
		exit(1);
	}
	if (ctx->ops)
		ft_memcpy(new_ops, ctx->ops, ctx->ops_len);
	free(ctx->ops);
	return (new_ops);
}

/*
** Bump the op counter and, in record mode, append the op name
** to the accumulated output stream.
*/
void	record_op(t_ctx *ctx, int op, const char *name, size_t len)
{
	size_t	need;

	ctx->counts[op]++;
	if (!ctx->record)
		return ;
	need = ctx->ops_len + len;
	if (need > ctx->ops_cap)
		ctx->ops = grow_buffer(ctx, need);
	ft_memcpy(ctx->ops + ctx->ops_len, name, len);
	ctx->ops_len += len;
}

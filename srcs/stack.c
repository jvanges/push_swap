/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ctx_init(t_ctx *ctx, int cap)
{
	int	i;

	ctx->cap = cap;
	ctx->size_a = 0;
	ctx->size_b = 0;
	ctx->ops = NULL;
	ctx->ops_len = 0;
	ctx->ops_cap = 0;
	ctx->record = 1;
	ctx->a = malloc(sizeof(int) * cap);
	if (!ctx->a)
		return (0);
	ctx->b = malloc(sizeof(int) * cap);
	if (!ctx->b)
	{
		free(ctx->a);
		return (0);
	}
	i = 0;
	while (i < OP_COUNT)
	{
		ctx->counts[i] = 0;
		i++;
	}
	return (1);
}

void	ctx_free(t_ctx *ctx)
{
	free(ctx->a);
	free(ctx->b);
	free(ctx->ops);
	ctx->a = NULL;
	ctx->b = NULL;
	ctx->ops = NULL;
}

int	is_sorted(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i + 1 < ctx->size_a)
	{
		if (ctx->a[i] > ctx->a[i + 1])
			return (0);
		i++;
	}
	return (1);
}

/*
** Replace every value of stack a by its rank in [0, n):
** 0 is the smallest value, n-1 the biggest.
*/
void	compress_ranks(t_ctx *ctx)
{
	int	i;
	int	j;
	int	rank;
	int	*ranks;

	ranks = malloc(sizeof(int) * ctx->size_a);
	if (!ranks)
		return ;
	i = 0;
	while (i < ctx->size_a)
	{
		rank = 0;
		j = 0;
		while (j < ctx->size_a)
		{
			if (ctx->a[j] < ctx->a[i])
				rank++;
			j++;
		}
		ranks[i] = rank;
		i++;
	}
	while (--i >= 0)
		ctx->a[i] = ranks[i];
	free(ranks);
}

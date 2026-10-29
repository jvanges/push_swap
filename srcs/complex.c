/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** LSD radix sort on compressed ranks, O(n log n) in push_swap
** operations: ceil(log2(n)) passes, each pass costs exactly n
** operations to split a (ra keeps bit 1, pb sends bit 0) plus
** one pa per element pushed to b (~n/2 on random inputs).
*/
void	sort_complex(t_ctx *ctx)
{
	int	bit;
	int	bits;
	int	i;
	int	n;

	bits = 0;
	n = ctx->cap;
	while (((n - 1) >> bits) != 0)
		bits++;
	bit = 0;
	while (bit < bits)
	{
		i = 0;
		while (i < n)
		{
			if ((ctx->a[0] >> bit) & 1)
				do_ra(ctx);
			else
				do_pb(ctx);
			i++;
		}
		while (ctx->size_b > 0)
			do_pa(ctx);
		bit++;
	}
}

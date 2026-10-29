/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_strat	dispatch(t_ctx *ctx, t_flags *fl)
{
	t_strat	st;

	if (ctx->size_a <= 5)
	{
		st.name = "Small sort (n <= 5)";
		st.class = "O(1)";
		sort_small(ctx);
	}
	else if (fl->strategy == 's')
	{
		st.name = "Simple: selection sort";
		st.class = "O(n^2)";
		sort_simple(ctx);
	}
	else if (fl->strategy == 'm')
	{
		st.name = "Medium: chunk sort";
		st.class = "O(n*sqrt(n))";
		sort_medium(ctx);
	}
	else if (fl->strategy == 'c')
	{
		st.name = "Complex: radix sort LSD";
		st.class = "O(n log n)";
		sort_complex(ctx);
	}
	else
		sort_adaptive(ctx, fl, &st);
	return (st);
}

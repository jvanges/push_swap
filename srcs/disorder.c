/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Disorder = mistakes / total_pairs, where a mistake is a pair
** (i < j) with a[i] > a[j]. Measured on the raw initial stack,
** before any operation.
*/
void	compute_disorder(t_ctx *ctx, t_flags *fl)
{
	int	i;
	int	j;

	fl->mistakes = 0;
	fl->total_pairs = 0;
	i = 0;
	while (i < ctx->size_a)
	{
		j = i + 1;
		while (j < ctx->size_a)
		{
			fl->total_pairs++;
			if (ctx->a[i] > ctx->a[j])
				fl->mistakes++;
			j++;
		}
		i++;
	}
	if (fl->total_pairs == 0)
		fl->disorder = 0.0;
	else
		fl->disorder = (double)fl->mistakes / (double)fl->total_pairs;
}

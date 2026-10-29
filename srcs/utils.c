/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	i_sqrt(int n)
{
	int	r;

	r = 1;
	while (r <= n / r)
		r++;
	return (r - 1);
}

int	index_of_min(int *stack, int size)
{
	int	i;
	int	idx;

	idx = 0;
	i = 1;
	while (i < size)
	{
		if (stack[i] < stack[idx])
			idx = i;
		i++;
	}
	return (idx);
}

int	index_of_max(int *stack, int size)
{
	int	i;
	int	idx;

	idx = 0;
	i = 1;
	while (i < size)
	{
		if (stack[i] > stack[idx])
			idx = i;
		i++;
	}
	return (idx);
}

/*
** Bring the element at index idx of stack a (is_b = 0) or b (is_b = 1)
** to the top using the shortest rotation direction.
*/
void	rot_to_top(t_ctx *ctx, int idx, int is_b)
{
	int	size;

	size = ctx->size_a;
	if (is_b)
		size = ctx->size_b;
	if (idx <= size / 2)
	{
		while (idx-- > 0)
		{
			if (is_b)
				do_rb(ctx);
			else
				do_ra(ctx);
		}
	}
	else
	{
		while (idx++ < size)
		{
			if (is_b)
				do_rrb(ctx);
			else
				do_rra(ctx);
		}
	}
}

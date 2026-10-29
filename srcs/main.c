/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	error_exit(t_ctx *ctx)
{
	ctx_free(ctx);
	write(2, "Error\n", 6);
	return (1);
}

int	main(int argc, char **argv)
{
	t_ctx	ctx;
	t_flags	fl;
	t_strat	st;
	int		count;

	if (argc < 2)
		return (0);
	count = count_numbers(argc, argv);
	if (count < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (count == 0)
		return (0);
	if (!ctx_init(&ctx, count))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (!parse_args(argc, argv, &ctx, &fl))
		return (error_exit(&ctx));
	compute_disorder(&ctx, &fl);
	st.name = "None (already sorted)";
	st.class = "O(1)";
	if (!is_sorted(&ctx))
	{
		compress_ranks(&ctx);
		st = dispatch(&ctx, &fl);
	}
	write(1, ctx.ops, ctx.ops_len);
	if (fl.bench)
		print_bench(&ctx, &fl, st);
	ctx_free(&ctx);
	return (0);
}

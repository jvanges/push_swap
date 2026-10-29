/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_long_fd(long n, int fd)
{
	char	c;

	if (n >= 10)
		put_long_fd(n / 10, fd);
	c = '0' + (n % 10);
	write(fd, &c, 1);
}

static void	print_disorder(t_flags *fl)
{
	long	bps;

	if (fl->total_pairs == 0)
		bps = 0;
	else
		bps = (fl->mistakes * 10000 + fl->total_pairs / 2) / fl->total_pairs;
	ft_putstr_fd("[bench] Disorder: ", 2);
	put_long_fd(bps / 100, 2);
	ft_putstr_fd(".", 2);
	if (bps % 100 < 10)
		ft_putstr_fd("0", 2);
	put_long_fd(bps % 100, 2);
	ft_putstr_fd("%\n", 2);
}

static void	print_counts(t_ctx *ctx)
{
	static const char	*names[OP_COUNT] = {
		"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"
	};
	long				total;
	int					i;

	total = 0;
	i = 0;
	while (i < OP_COUNT)
	{
		total += ctx->counts[i];
		i++;
	}
	ft_putstr_fd("[bench] Total operations: ", 2);
	put_long_fd(total, 2);
	ft_putstr_fd("\n[bench] Ops:", 2);
	i = 0;
	while (i < OP_COUNT)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd((char *)names[i], 2);
		ft_putstr_fd("=", 2);
		put_long_fd(ctx->counts[i], 2);
		i++;
	}
	ft_putstr_fd("\n", 2);
}

void	print_bench(t_ctx *ctx, t_flags *fl, t_strat st)
{
	print_disorder(fl);
	ft_putstr_fd("[bench] Strategy: ", 2);
	ft_putstr_fd((char *)st.name, 2);
	ft_putstr_fd(" — ", 2);
	ft_putstr_fd((char *)st.class, 2);
	ft_putstr_fd("\n", 2);
	print_counts(ctx);
}

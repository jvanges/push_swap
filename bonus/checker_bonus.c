/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	fail(t_ctx *ctx, char *line)
{
	free(line);
	ctx_free(ctx);
	write(2, "Error\n", 6);
	exit(1);
}

static void	apply_idx(t_ctx *ctx, int i)
{
	if (i == 0 || i == 2)
		do_sa(ctx);
	if (i == 1 || i == 2)
		do_sb(ctx);
	if (i == 5 || i == 7)
		do_ra(ctx);
	if (i == 6 || i == 7)
		do_rb(ctx);
	if (i == 8 || i == 10)
		do_rra(ctx);
	if (i == 9 || i == 10)
		do_rrb(ctx);
	if (i == 3)
		do_pa(ctx);
	if (i == 4)
		do_pb(ctx);
}

static int	apply_op(t_ctx *ctx, const char *op)
{
	static const char	*names[OP_COUNT] = {
		"sa\n", "sb\n", "ss\n", "pa\n", "pb\n", "ra\n",
		"rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"
	};
	int					i;

	i = 0;
	while (i < OP_COUNT)
	{
		if (!ft_strncmp(op, names[i], ft_strlen(names[i]) + 1))
		{
			apply_idx(ctx, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	process_char(t_ctx *ctx, char *line, char c, int *len)
{
	if (c == '\n')
	{
		line[*len] = '\n';
		line[*len + 1] = '\0';
		if (*len == 0 || !apply_op(ctx, line))
			return (0);
		*len = 0;
		return (1);
	}
	if (*len < 4)
		line[(*len)++] = c;
	else
		(*len)++;
	return (1);
}

static void	read_ops(t_ctx *ctx, char *line)
{
	char	c;
	int		len;
	int		r;

	len = 0;
	r = read(0, &c, 1);
	while (r > 0)
	{
		if (!process_char(ctx, line, c, &len))
			fail(ctx, line);
		r = read(0, &c, 1);
	}
	if (len > 0)
		fail(ctx, line);
}

int	main(int argc, char **argv)
{
	t_ctx	ctx;
	t_flags	fl;
	char	*line;
	int		count;

	if (argc < 2)
		return (0);
	count = count_numbers(argc, argv);
	if (count <= 0 || !ctx_init(&ctx, count))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	ctx.record = 0;
	if (!parse_args(argc, argv, &ctx, &fl))
		fail(&ctx, NULL);
	line = malloc(6);
	if (!line)
		fail(&ctx, NULL);
	read_ops(&ctx, line);
	free(line);
	if (is_sorted(&ctx) && ctx.size_b == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ctx_free(&ctx);
	return (0);
}

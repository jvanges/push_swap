/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** 1: valid flag, 0: not a flag, -1: unknown flag.
** The length passed to ft_strncmp includes the trailing '\0',
** so matches are exact.
*/
static int	flag_kind(const char *arg)
{
	if (arg[0] != '-' || arg[1] != '-')
		return (0);
	if (!ft_strncmp(arg, "--bench", 8))
		return (1);
	if (!ft_strncmp(arg, "--simple", 9))
		return (1);
	if (!ft_strncmp(arg, "--medium", 9))
		return (1);
	if (!ft_strncmp(arg, "--complex", 10))
		return (1);
	if (!ft_strncmp(arg, "--adaptive", 11))
		return (1);
	return (-1);
}

static void	apply_flag(const char *arg, t_flags *fl)
{
	if (!ft_strncmp(arg, "--bench", 8))
		fl->bench = 1;
	else if (!ft_strncmp(arg, "--simple", 9))
		fl->strategy = 's';
	else if (!ft_strncmp(arg, "--medium", 9))
		fl->strategy = 'm';
	else if (!ft_strncmp(arg, "--complex", 10))
		fl->strategy = 'c';
	else
		fl->strategy = 'a';
}

/*
** Strict integer conversion: optional sign, digits only, must
** fit inside an int.
*/
long	ft_atol_check(const char *s, int *ok)
{
	long	val;
	int		sign;

	val = 0;
	sign = 1;
	*ok = 0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!ft_isdigit(*s))
		return (0);
	while (ft_isdigit(*s))
	{
		val = val * 10 + (*s - '0');
		if (val * sign > 2147483647 || val * sign < -2147483648L)
			return (0);
		s++;
	}
	if (*s != '\0')
		return (0);
	*ok = 1;
	return (val * sign);
}

static int	add_value(t_ctx *ctx, long val)
{
	int	i;

	i = 0;
	while (i < ctx->size_a)
	{
		if (ctx->a[i] == (int)val)
			return (0);
		i++;
	}
	ctx->a[ctx->size_a] = (int)val;
	ctx->size_a++;
	return (1);
}

/*
** First pass: how many numbers will be parsed (to allocate the
** stacks once). -1 on error (unknown flag or empty token list).
*/
int	count_numbers(int argc, char **argv)
{
	char	**tokens;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 1;
	while (i < argc)
	{
		if (flag_kind(argv[i]) != 0)
		{
			if (flag_kind(argv[i]) < 0)
				return (-1);
		}
		else
		{
			tokens = ft_split(argv[i], ' ');
			if (!tokens)
				return (-1);
			if (!tokens[0])
			{
				free_strs(tokens);
				return (-1);
			}
			j = 0;
			while (tokens[j++])
				count++;
			free_strs(tokens);
		}
		i++;
	}
	return (count);
}

/*
** Second pass: fill stack a. Returns 0 on error (bad integer,
** out of range value or duplicate).
*/
int	parse_args(int argc, char **argv, t_ctx *ctx, t_flags *fl)
{
	char	**tokens;
	long	val;
	int		ok;
	int		ij[2];

	fl->bench = 0;
	fl->strategy = 'a';
	ij[0] = 0;
	while (++ij[0] < argc)
	{
		if (flag_kind(argv[ij[0]]) == 1)
		{
			apply_flag(argv[ij[0]], fl);
			continue ;
		}
		tokens = ft_split(argv[ij[0]], ' ');
		ij[1] = -1;
		while (tokens[++ij[1]])
		{
			val = ft_atol_check(tokens[ij[1]], &ok);
			if (!ok || !add_value(ctx, val))
			{
				free_strs(tokens);
				return (0);
			}
		}
		free_strs(tokens);
	}
	return (1);
}

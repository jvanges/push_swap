NAME		= push_swap
BONUS_NAME	= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iincludes -Ilibft

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= srcs/main.c \
			  srcs/parse.c \
			  srcs/stack.c \
			  srcs/utils.c \
			  srcs/ops.c \
			  srcs/ops_rot.c \
			  srcs/ops_record.c \
			  srcs/disorder.c \
			  srcs/sort_small.c \
			  srcs/simple.c \
			  srcs/medium.c \
			  srcs/complex.c \
			  srcs/adaptive.c \
			  srcs/dispatch.c \
			  srcs/bench.c

SHARED		= srcs/parse.c \
			  srcs/stack.c \
			  srcs/utils.c \
			  srcs/ops.c \
			  srcs/ops_rot.c \
			  srcs/ops_record.c

BONUS_SRCS	= bonus/checker_bonus.c $(SHARED)

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c includes/push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re

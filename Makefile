NAME := minishell
LIBFT_DIR := Auxiliary/Libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g
LDFLAGS := -lreadline

OBJDIR := .objs

SRCS := $(shell find . -type f -name '*.c' -not -path './$(LIBFT_DIR)/*' -not -path './.git/*' -not -path './$(OBJDIR)/*')
OBJS := $(patsubst ./%.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: ./%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

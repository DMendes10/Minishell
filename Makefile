NAME := minishell
SRC_DIR := src

SRCS := built_ins2.c built_ins.c built_in_utils.c cd_utils.c cmdlist_utils.c env_utils.c error.c exec_utils2.c executor_utils.c expansion.c expansion_utils.c expansion_utils2.c export_node.c export_utils.c free_hub.c here_doc.c lexer.c lexer_utils.c list_utils.c minishell.c parse.c parser_utils.c redirections.c rem_quotes.c split_pipex.c split_shell.c utils.c env_handler.c error_alloc.c redirection_hub.c
OBJS := $(SRCS:.c=.o)
LIBFT_DIR := $(SRC_DIR)/Libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g
LDFLAGS := -lreadline

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
# Compile .c files to .o preserving directory structure
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

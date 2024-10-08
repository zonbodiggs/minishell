#-----------------------------------------------------------------#
CC			=	cc

CFLAGS		= -g -Wall -Wextra -Werror #-fsanitize=address

LIBFTFLAGS	= -Llibft -lft -L/usr/local/lib -I/usr/local/include -lreadline

NAME		= minishell
#-----------------------------------------------------------------#
SRCS		= parsing/tokenize/bool_lexer.c\
			  parsing/tokenize/init_lexer.c\
			  parsing/tokenize/lexer_tools.c\
			  parsing/tokenize/expand.c\
			  parsing/tokenize/expand_utils.c\
			  parsing/tokenize/expand_tools.c\
			  parsing/tokenize/operator.c\
			  parsing/pars_cmd/init_cmd.c\
			  parsing/pars_cmd/cmd_utils.c\
			  parsing/pars_cmd/tab_utils.c\
			  parsing/pars_cmd/files_utils.c\
			  parsing/pars_cmd/lst_cmd_utils.c\
			  parsing/pars_cmd/parsing_cmd.c\
			  parsing/pars_cmd/bool_cmd.c\
			  parsing/pars_utils.c\
			  exec/exec.c\
			  exec/exec_utils.c\
			  exec/redirect.c\
			  exec/pipe.c\
			  exec/pipe_utils.c\
			  exec/builtin.c\
			  exec/heredoc.c\
			  builtin/echo.c\
			  builtin/cd.c\
			  builtin/cd_utile.c\
			  builtin/pwd.c\
			  builtin/env.c\
			  builtin/export.c\
			  builtin/export_utile.c\
			  builtin/unset.c\
			  builtin/exit.c\
			  exit/exit_shell.c\
			  exit/exit_code.c\
			  env_utils.c\
			  signal.c\
			  free.c\
			  main.c

LIB_DIR		= ./libft/

LIB_NAME	= libft.a

LIB			= ${addprefix $(LIB_DIR), $(LIB_NAME)}

OBJ_DIR		= .obj

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

HEADERS		= minishell.h  ${addprefix $(LIB_DIR), libft.h}
#-----------------------------------------------------------------#
all : libs $(NAME)

$(NAME) : $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTFLAGS)

$(OBJ_DIR)/%.o : %.c $(HEADERS)
	@mkdir -p  $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

libs :	
	$(MAKE) -C $(LIB_DIR)

clean :
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)

fclean : clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)

re : fclean
	$(MAKE) all

.PHONY : all libs clean fclean re

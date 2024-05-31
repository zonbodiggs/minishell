#---------------------------------------------------#
CC 			= cc

CFLAGS 		= -g3 -Wall -Wextra -Werror

NAME 		= libft.a
#---------------------------------------------------#
SRCS		= \
	ft_printf_fd.c\
	ft_printf_fd_utils.c\
	ft_atoi.c\
	ft_calloc.c\
	ft_strnstr.c\
	ft_memcmp.c\
	ft_memchr.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strdup.c\
	ft_strlen.c\
	ft_bzero.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_memset.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_strncmp.c\
	ft_substr.c\
	ft_slash_strjoin.c\
	ft_strtrim.c\
	ft_itoa.c\
	ft_split.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_qsplit.c\
	ft_qstrdup.c\
	get_next_line.c\
	get_next_line_utils.c\
	ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstclear.c\
	ft_lstdelone.c\
	ft_swap.c

OBJ_DIR 	= .obj

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

HEADERS		= libft.h
#---------------------------------------------------#
all : $(NAME)
	
$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re:	fclean
	$(MAKE) all

.PHONY: all clean fclean re
#---------------------------------------------------#
 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:52:08 by endoliam          #+#    #+#             */
/*   Updated: 2023/11/16 11:11:15 by endoliam       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_stack
{
	void			*content;

	struct s_stack	*prev;
	struct s_stack	*next;
}	t_stack;

void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t num, size_t nsize);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_swap(char **a, char **b);

char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
char	*ft_qstrdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_slash_strjoin(const char *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	**ft_qsplit(char const *s, char c);

size_t	ft_strlcat(char *dest, char *src, size_t l);
size_t	ft_strlcpy(char *dest, const char *src, size_t l);
size_t	ft_strlen(const char *str);
size_t	ft_strlen(const char *str);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_toupper(int c);
int		ft_isalnum(int c);
int		ft_tolower(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);

// lst tools
t_stack	*ft_lstnew(void *content);
void	ft_lstadd_front(t_stack **lst, t_stack *new);
int		ft_lstsize(t_stack *lst);
t_stack	*ft_lstlast(t_stack *lst);
void	ft_lstadd_back(t_stack **lst, t_stack *new);
void	ft_lstadd_mid(t_stack **lst, t_stack *new);
void	ft_lstclear(t_stack **lst, void (*del)(void*));
void	ft_lstdelone(t_stack *lst, void (*del)(void*));
void	ft_lstiter(t_stack *lst, void (*f)(void *));
t_stack	*ft_lstmap(t_stack *lst, void *(*f)(void *), void (*del)(void *));

// get next line
char	*get_next_line(int fd);
char	*ft_read(int fd, char *next_line);
char	*ft_get_line(char *next_line, char *ptr);
char	*go_next_line(char *next_line, char *ptr);
char	*ft_strchrgnl(char *str, int c);
char	*ft_substrgnl(char const *s, unsigned int start, size_t len);
size_t	ft_strlengnl(const char *str);
char	*ft_strjoingnl(char *next_line, const char *buffer);
void	*ft_memmovegnl(void *dest, const void *src, size_t n);
void	*ft_free(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// printf fd
void	ft_putcharft(int fd, char c, int *addrcheck);
size_t	ft_strlenft(const char *str);
void	ft_putstrft(int fd, const char *str, int *addrcheck);
void	ft_putnbrft(int fd, long long n, int *addrcheck);
void	ft_putnbr_hexaft(int fd, unsigned long n, int *addrcheck, int c);
int		ft_check_error(va_list arg);
int		ft_printf_fd(int fd, const char *str, ...);

#endif

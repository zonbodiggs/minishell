/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:20:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/05/17 03:36:38 by endoliam         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

extern int			g_signal;

typedef enum e_enum
{
	HEREDOC = 1,
	APPEND,
	TRUNC,
	IN,
}		t_enum;

typedef enum e_lexer_type
{
	PIPES = 1,
	WORD,
	INPUT,
	OUTPUT,
	SINGLE_Q,
	DOUBLE_Q,
	ENV_VAR,
	DOUBLE_ENV,
	SINGLE_ENV,
}		t_lexer_type;

typedef struct s_lexer // for pars
{
	t_lexer_type		lex;		// enum of lex word ?? pipes ?? input ?? output ??
	char				*contain;	// part of prompt
	bool				spaces; 	// spaces after word ??
	struct s_lexer		*next;
	struct s_lexer		*prev;
}		t_lexer;

typedef struct s_cmd // for exec
{
	char				**cmd;			// cmd
	char				**t_env;		// env
	t_enum				redir;			// enum of fd
	struct s_input		*next;
}		t_cmd;

typedef struct s_minishell
{
	t_cmd		*input;				// cmd
	t_lexer		*lex;				// lex
	char		**path;				// path
}		t_minishell;

int			main(int ac, char **av, char **env);

// parsing

void		create_lexer(char *s);

#endif
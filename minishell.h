/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:20:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/04 12:49:03 by endoliam         ###   ########lyon.fr   */
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
# include <fcntl.h>
# include <sys/wait.h>

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
	char				**files;
	t_enum				redir;			// enum of fd
	struct s_cmd		*next;
}		t_cmd;

typedef struct s_minishell
{
	t_cmd		*input;				// cmd
	t_lexer		*lex;				// lex
	char		**path;				// path
}		t_minishell;

int			main(int ac, char **av, char **env);


/* 					parsing					*/ 

// tokenize

// init lexer
t_lexer		*create_lexer(char *s);
int			init_operator(t_lexer **lexer, char *s, int start);
void		init_lexer_type(t_lexer *data);
void		init_redirection(t_lexer **lexer, char c, int flag);

// tools lexer
int			lst_init_lexer(t_lexer **lexer, char *s, int start);
void		add_lexer(t_lexer **lexer, t_lexer *element);
int			word_len(char *s);

// bool lexer
bool		isword(char *s, int start);
bool		final_space(char *s);
bool		isoperator(char c);

// utils cmd
int			exit_failure(char *msg, char c);
int			zap_quote(char *s, char quote, int i);
void		free_array(char **array);
void		exit_cmd(char *msg);

// init cmd
t_cmd		*init_cmd(char **env, t_lexer *lex);
void		cpy_env(char **env, t_cmd *command);

//parsing cmd for execution

// init cmd
t_cmd		*init_cmd(char **env, t_lexer *lex);
char		**init_tab(t_lexer *lex);
char		*dup_cmd(t_lexer *lex);

// pars cmd
int			set_file(char **files, int flag);
void		pars_files(t_cmd *command);

// lst cmd
void		lst_init_cmd(char **env, t_cmd **command);
void		add_cmd(t_cmd **command, t_cmd *element);
void		pars_cmd(char **cmd);
void		pars_cmd_list(t_cmd	*command);
int			error_files(int flag, char *file);

// utils cmd
void		cpy_env(char **env, t_cmd *command);
int			size_tab_cmd(t_lexer *lex);
bool		isoperator_cmd(t_lexer_type lex_type);
bool		isredirection(t_lexer_type lex_type);
bool		isbuiltin(char *cmd);

// files utils 
void		set_input(t_cmd *command, t_lexer *lex);
int			isfilevalid_in(char *file);
int			isfilevalid_out(char *file);

/*					end parsing				*/


/* 					exec					*/
void		execute_pipeline(t_cmd *cmds);
int 		get_last_index(char **files);
void 		run_commands(t_cmd *cmds);

int			redirect_input(const char *file);
int			redirect_output(const char *file);
int			redirect_output_append(const char *file);
void		redirect_heredoc(const char *delimiter);

void 		sort_cmd(char **cmd);
int 		echo(char **cmd);
int 		pwd();

/* 					end exec				*/ 
#endif
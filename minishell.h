/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:20:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/06/10 22:57:44 by endoliam         ###   ########lyon.fr   */
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
# include <sys/types.h>

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
	char		**env;				// path
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
bool		is_env_var(char *s);

// utils cmd
int			exit_failure(char *msg, char c);
int			zap_quote(char *s, char quote, int i);
void		free_array(char **array);
void		exit_cmd(char *msg);
char		**cpy_env(char **env);

//parsing cmd for execution

// init cmd
t_cmd		*init_cmd(char **env, t_lexer **lex);
char		**init_tab(t_lexer *lex);
char		*dup_cmd(t_lexer *lex);

// pars cmd
int			set_file(char **files, int flag);
void		pars_files(t_cmd *command);

// lst cmd
void		lst_init_cmd(char **env, t_cmd **command);
void		add_cmd(t_cmd **command, t_cmd *element);
int			iscmd(char **cmd);
void		pars_cmd_list(t_cmd	*command);
int			error_files(int flag, char *file);

// utils cmd
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
int 		get_last_index(char **files);
void 		run_commands(t_minishell *mini);

void		redirect_input(const char *file);
void		redirect_output(const char *file);
void		redirect_output_append(const char *file);
void		redirect_heredoc(const char *delimiter);

void 		sort_cmd(char **cmd);
int 		echo(char **cmd);
int 		pwd();

/* 					end exec				*/ 

// free
t_lexer		*free_lexer(t_lexer **lex);
void		free_all(t_cmd **cmd);
void		kill_prompt(t_minishell *mini);


/*****************print*********************/

void	printfds(t_cmd *cmd, int *old,int *new);
void	print_cmd(t_cmd *cmd);
void	print_lexer(t_lexer *lex);
void	print_minishell(t_minishell *mini);
void	print_env(char **env);

#endif
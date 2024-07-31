/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:20:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/07/31 19:27:16 by endoliam         ###   ########lyon.fr   */
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
	char				*files;
	bool				pipe;
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

// 				init lexer
t_lexer		*create_lexer(char *s, t_minishell *mini);
int			init_operator(t_lexer **lexer, char *s, int start, t_minishell mini);
void		init_lexer_type(t_lexer *data);
void		init_redirection(t_lexer **lexer, char c, int flag, t_minishell mini);
int			find_redirection(t_lexer **lexer, char *s, int start, t_minishell mini);

// 				tools lexer
int			lst_init_lexer(t_lexer **lexer, char *s, int start, t_minishell mini);
void		add_lexer(t_lexer **lexer, t_lexer *element);
int			word_len(char *s);

// 				bool lexer
bool		isword(char *s, int start);
bool		final_space(char *s);
bool		isoperator(char c);
bool		is_env_var(char *s);
bool		isispace(char c);

//				expand
char		*init_env_var(char *s, t_minishell mini);
char 		*join_and_free(char *s1, char *s2);

// 				utils cmd
int			exit_failure(char *msg, char c);
int			zap_quote(char *s, char quote, int i);
void		free_array(char **array);
void		exit_cmd(char *msg);
char		**cpy_env(char **env);
char		*mygetenv(char *s, char **env);

//			parsing cmd for execution

// 				init cmd
t_cmd		*init_cmd(char **env, t_lexer **lex);
char		**init_tab(t_lexer *lex);
char		*dup_cmd(t_lexer *lex);

// 				pars cmd
int			set_file(char *files, int flag);
void		pars_files(t_cmd *command);

// 				lst cmd
void		lst_init_cmd(char **env, t_cmd **command);
void		add_cmd(t_cmd **command, t_cmd *element);
int			iscmd(char **cmd);
void		pars_cmd_list(t_cmd	*command);
int			error_files(int flag, char *file);

// 				utils cmd
int			size_tab_cmd(t_lexer *lex);
t_lexer		*zap_redirection(t_lexer *lex);
t_lexer		*go_next_cmd(t_lexer *lex);
char		*join_cmd(t_lexer *lex, char *cmd);
char		*dup_cmd(t_lexer *lex);

//				bool cmd
bool		isoperator_cmd(t_lexer_type lex_type);
bool		isredirection(t_lexer_type lex_type);
bool		isbuiltin(char *cmd);
bool		isthereredirection(t_lexer *lexer, t_cmd *command);

// 				files utils 
void		set_input(t_cmd *command, t_lexer *lex);
int			isfilevalid_in(char *file);
int			isfilevalid_out(char *file);
char		*init_files(t_lexer *lex);

/*					end parsing				*/

/* 					exec					*/
int 		get_last_index(char **files);
void 		run_commands(t_minishell *mini);

//					redirecion
void		redirect_input(t_minishell *mini);
void		redirect_output(t_minishell *mini);
void		redirect_output_append(t_minishell *mini);
void		redirect_heredoc(const char *delimiter);

//					builtins
int 		cd(char **cmd, char ***env);
int 		sort_cmd(char **cmd, char **env);
int 		echo(char **cmd);
int 		pwd();
int 		env_shell(char **env);
void 		exit_shell(t_minishell *shell, char **cmd);
int			export_variable(char **cmd, char ***env);
int 		unset_variable(char **cmd, char ***env);

/* 					end exec				*/ 

// 					free
void		free_lexer(t_lexer **lex);
void		free_all_input(t_cmd *cmd);
void		free_cmd(t_cmd **cmd);
void		free_one_input(t_cmd *cmd);
void		free_input(t_cmd **cmd);

//					exit
void		exit_error_exec(t_minishell *mini, t_cmd *cmd);
void		kill_shell(t_minishell *shell);

/*******************print*********************/

void	printfds(t_cmd *cmd, int *old,int *new);
void	print_cmd(t_cmd *cmd);
void	print_lexer(t_lexer *lex);
void	print_minishell(t_minishell *mini);
void	print_env(char **env);
t_lexer		*zap_redirection(t_lexer *lex);

#endif
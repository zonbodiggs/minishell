/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endoliam <endoliam@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:20:55 by endoliam          #+#    #+#             */
/*   Updated: 2024/09/09 13:08:11 by endoliam         ###   ########lyon.fr   */
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
# include <signal.h>
# include <sys/types.h>
# include <errno.h>
# include <limits.h>

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

typedef struct s_lexer
{
	t_lexer_type		lex;
	char				*contain;
	bool				spaces;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}		t_lexer;

typedef struct s_cmd
{
	char				**cmd;
	char				**t_env;
	char				*files;
	bool				pipe;
	t_enum				redir;
	struct s_cmd		*next;
}		t_cmd;

typedef struct s_minishell
{
	t_cmd		*input;
	t_lexer		*lex;
	char		**env;
	char		*exit_code;
}		t_minishell;

int			main(int ac, char **av, char **env);

/*						add_env				*/
void		add_pwd(t_minishell *minishell);
void		add_env(t_minishell *minishell);
void		update_shlvl(t_minishell *minishell);

/* 					parsing					*/

// 				init lexer
t_lexer		*create_lexer(char *s, t_minishell *mini);
int			init_operator(t_lexer **lexer,
				char *s, int start, t_minishell mini);
void		init_lexer_type(t_lexer *data);
void		init_redirection(t_lexer **lexer,
				char c, int flag, t_minishell mini);
int			find_redirection(t_lexer **lexer,
				char *s, int start, t_minishell mini);

// 				tools lexer
int			lst_init_lexer(t_lexer **lexer,
				char *s, int start, t_minishell mini);
void		add_lexer(t_lexer **lexer, t_lexer *element);
int			word_len(char *s);
void		free_one_lexer(t_lexer **lexer);

// 				bool lexer
bool		isword(char *s, int start);
bool		final_space(char *s);
bool		isoperator(char c);
bool		is_env_var(char *s);
bool		isispace(char c);
bool		is_quote(char c);

//				expand
char		*init_env_var(char *s, t_minishell mini);
char		*join_and_free(char *s1, char *s2);
t_lexer		*parsing_expand(t_lexer **lexer);
void		clean_expand(char *contain);
char		*add_contain(t_lexer **lexer);
void		clean_expand_quote(t_lexer *lexer);
void		expand_variable(t_lexer *data, t_lexer **lexer,
				t_minishell mini);
// 				utils cmd
int			exit_failure(char *msg, char c);
int			zap_quote(char *s, char quote, int i);
void		free_array(char **array);
char		**cpy_env(t_minishell *mini, char **env);
char		*mygetenv(char *s, t_minishell mini);

//			parsing cmd for execution

// 				init cmd
t_cmd		*init_cmd(t_minishell *mini, t_lexer **lex);
char		**init_tab(t_cmd *command, t_lexer *lex, t_minishell *mini);

// 				lst cmd
void		lst_init_cmd(t_minishell *mini, t_cmd **command);
void		add_cmd(t_cmd **command, t_cmd *element);
int			iscmd(char **cmd, t_minishell *mini);
int			error_files(int flag, char *file);

// 				utils cmd
int			size_tab_cmd(t_lexer *lex);
t_lexer		*zap_redirection(t_lexer *lex);
t_lexer		*go_next_cmd(t_lexer *lex);
char		*join_cmd(t_lexer *lex, char *cmd);
char		*dup_cmd(t_lexer *lex, t_minishell *mini);

//				bool cmd
bool		isoperator_cmd(t_lexer_type lex_type);
bool		isredirection(t_lexer_type lex_type);
bool		isbuiltin(char *cmd);
bool		isthereredirection(t_lexer *lexer, t_cmd *command);
bool		is_directory(char *cmd);

// 				files utils 
void		set_input(t_cmd *command, t_lexer *lex);
int			isfilevalid_in(char *file);
int			isfilevalid_out(char *file);
char		*init_files(t_cmd *command, t_lexer *lex, t_minishell *mini);

/*					end parsing				*/

/* 					exec					*/
int			my_execve(t_minishell *mini);
char		*run_commands(t_minishell *mini);

//					exec utils
t_cmd		*get_pipe_comd(t_cmd *cmd);
bool		is_last_cmd(t_cmd	*cmd);
int			number_of_command(t_cmd *cmd);
void		init_fds(int oldfd[2], int newfd[2]);

//					pipe
int			execute_pipeline(t_minishell *mini);
int			execute_simple_command(t_minishell *mini);
void		update_pipeline(int *oldfd, int *newfd);
void		close_all(int *newfd, int *oldfd);

//					redirecion
int			redirect_input(t_minishell *mini);
int			redirect_output(t_minishell *mini);
int			redirect_output_append(t_minishell *mini);
int			redirect(t_minishell *mini);

//					heredoc
int			redirect_heredoc(t_minishell *mini);
void		find_heredoc(t_cmd	*command, t_minishell *mini);
void		write_heredoc(int fd, char *line);

//					builtins
void		exec_builtin(t_minishell *mini, t_cmd *cmd);
int			sort_cmd(char **cmd, char **env);
int			echo(char **cmd);
int			pwd(char **cmd);
int			env_shell(char **env, char **cmd);
void		exit_shell(t_minishell *shell, char **cmd);
int			unset_variable(char **cmd, char ***env);
int			sort_builtin(t_minishell *mini);

//					cd
int			cd(char **cmd, char ***env);
int			check_env(char ***env, const char *var, char *new_var, int len);
int			update_pwd(char ***env);
int			update_oldpwd(char ***env);
int			cheking_cd(char ***env, char *path);
char		*get_env_value(char **env, const char *var);
int			set_env_var(char ***env, const char *var, const char *value);
int			print_error(char *arg);
char		*check_path(char *path, char ***env);

//					export
int			export_variable(char **cmd, char ***env);
int			update_existing_var(char *new_var, char ***env);
int			add_new_var(char *new_var, char ***env);
int			check_var(char *new_var, char **env);

/* 					end exec				*/

// 					free
void		free_lexer(t_lexer **lex);
void		free_all_input(t_cmd *cmd);
void		free_cmd(t_cmd **cmd);
void		free_one_input(t_cmd *cmd);
void		free_input(t_cmd **cmd);

//					exit
int			exit_error_exec(t_minishell *mini, int value);
void		kill_shell(t_minishell *shell);
void		exit_cmd(char *msg, t_minishell *mini, int value);
t_lexer		*lexer_error_exit(int i, t_lexer *lexer, t_minishell *mini);
int			get_exit_code(t_minishell *mini, int value);

//					signaux
void		set_exec_signal(void);
void		set_input_signal(void);
void		handle_sigint_input(int sig);
void		handle_sigint(int sig);


void	print_cmd(t_cmd *cmd);
void	printfds(t_cmd *cmd, int *old, int *new);
void	print_lexer(t_lexer *lex);
void	print_minishell(t_minishell *mini);

#endif

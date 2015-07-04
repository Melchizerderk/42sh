/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mngomane <mngomane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 16:50:24 by mngomane          #+#    #+#             */
/*   Updated: 2014/06/26 05:43:38 by mngomane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSH_H
# define FTSH_H

# include <termios.h>
# include <unistd.h>

# define IN			0
# define OUT		1
# define I			0
# define J			1
# define K			2
# define FALSE		0
# define TRUE		1
# define BSLASH		2
# define SQUOTE		3
# define DQUOTE		4
# define READ_MAX	100
# define PID_MAXLEN	256

typedef enum		e_pars
{
	NONE,
	PIPE,
	RIGHT,
	DRIGHT,
	LEFT,
	DLEFT,
	AND,
	OR,
	ESPERL,
}					t_pars;

typedef struct		s_sent
{
	char			*word;
	size_t			index;
	struct s_sent	*next;
}					t_sent;

typedef struct		s_bin
{
	char			*path;
	struct s_bin	*next;
}					t_bin;

typedef struct		s_job
{
	struct s_job	*next;
	char			**av;
	char			*command;
	int				active;
	int				number;
	int				pad;
	int				pid;
	int				status;
	int				stopped;
}					t_job;

typedef struct		s_entry
{
	char			**av;
	char			**ep;
	char			*save;
	char			*newpwd;
	char			*oldpwd;
	char			ano_buf[8];
	char			erase[4096];
	t_bin			*bin;
	t_bin			*bin_save;
	t_sent			*semicol;
	t_sent			*logic;
	t_sent			*par;
	t_sent			*sent;
	t_sent			*ano;
	t_sent			*red;
	t_sent			*red_save;
	t_job			*job;
	ssize_t			ano_read;
	int				fd;
	int				i;
	int				ret_pipe;
	int				ret_parse;
	int				pfd[2];
	int				ret_popen;
	pid_t			leaderpid;
	int				exit_status;
	pid_t			pid;
	pid_t			son_pid;
	char			end;
	char			cjmp;
	char			jpad;
	char			kpad;
}					t_entry;

typedef struct		s_env
{
	char			*ename;
	int				usr;
	int				home;
	struct s_env	*next;
}					t_env;

typedef struct		s_jmp
{
	char			*tmp;
	size_t			wrd;
	size_t			letter[2];
	size_t			i;
	size_t			save;
	size_t			len_word;
}					t_jmp;

char				*ft_strdup(char *str);
char				*ft_strjoin(char *str1, char *str2, char c);
char				*wjmp(char *s, size_t l[2], size_t (*w)(char));
char				*trim_entry(char *str, size_t (*wfct)(char));
int					arg_error(int ac, char **av);
int					ent_init(t_entry *ent, t_env **el, char **av, char **ep);
int					envl_init(t_env **el, char **ep);
int					ft_atoi(const char *s);
int					ft_env(t_env *envl);
int					ft_inhib(t_entry *ent);
int					ft_is_number(char *str);
int					ft_strncmp(char *s1, char *s2, size_t len);
int					no_job_stopped(t_job *job);
int					parse_error(char *s, char c, size_t max);
int					parse_tok_error(char *s);
int					path_init(t_entry *ent);
int					secu_malloc(char **str, size_t len);
int					sent_fill(t_entry *ent);
int					sub_main(t_entry *ent, t_env **envl);
size_t				in_env(char c);
size_t				in_word(char c);
size_t				ft_is_inhib(char c);
size_t				ft_is_left(char c);
size_t				ft_is_pipe(char c);
size_t				ft_is_redir(char c);
size_t				ft_is_right(char c);
size_t				ft_is_sep(char c);
size_t				ft_strlen(char *str);
size_t				nbr_words(char *str, size_t (*wfct)(char));
t_bin				*add_bin(t_bin **bin, char *path);
t_env				*add_envl(t_env **envl, char *ename);
t_job				*add_job(t_job *job, t_sent *sent, int pid);
t_pars				is_tok(char *str);
t_sent				**sent_split(t_sent *sent);
t_sent				*add_sent(t_sent **sent, char *word, size_t i);
t_sent				*and_or(char *str, char c);
t_sent				*sent_parse(char *str, size_t (*wfct)(char));
void				*ft_memset(void *s, int c, size_t len);
void				add_rev_sent(t_sent **sent, char *word);
void				and_tok(t_entry *ent, t_env **envl, t_sent **tab);
void				delet_job(t_job **job, int pid);
void				or_tok(t_entry *ent, t_env **envl, t_sent **tab);
void				arg_set(t_entry *ent, t_sent *sent);
void				clean_job(t_job **job);
void				cmdnf(t_sent *sent);
void				dash_cd(t_entry *ent);
void				env_set(t_entry *ent, t_env *envl);
void				exec_cmd(t_entry *ent, t_sent *sent, t_bin *b);
void				ft_bg(t_entry *ent, t_sent *sent);
void				ft_cd(t_entry *ent, t_env *envl, t_sent *sent);
void				ft_echo(t_sent **s);
void				ft_father(t_entry *ent, t_env **envl, t_sent **sent);
void				ft_fg(t_entry *ent, t_sent *sent);
void				ft_job(t_entry *ent, t_sent *sent);
void				ft_setenv(t_env **envl, t_sent *sent);
void				ft_sighand(int sig);
void				ft_son(t_entry *ent, t_env **el, t_sent **s, t_bin **b);
void				ft_putnbr_off_t(off_t n, pid_t pid);
void				ft_unsetenv(t_env **e, t_sent *s);
void				free_tab(t_sent ***tab);
void				free_envl(t_env **envl);
void				free_job(t_job **job);
void				free_sent(t_sent **sent);
void				jand(t_entry *ent, t_env **envl, t_sent **tab);
void				red_left(t_entry *ent, t_env **envl, t_sent **tab);
void				red_dright(t_entry *ent, t_env **envl, t_sent **tab);
void				red_right(t_entry *ent, t_env **envl, t_sent **tab);
void				sub_enti(t_entry **ent, char **av, char **ep);
void				sub_fathbg(t_entry *ent, t_sent **sent);
void				sub_fathcd(t_entry *ent, t_env **envl, t_sent **sent);
void				sub_fathfg(t_entry *ent, t_sent **sent);
void				sub_fathjob(t_entry *ent, t_sent **sent);
void				sub_fathset(t_env **envl, t_sent **sent);
void				sub_fathun(t_env **envl, t_sent **sent);
void				sub_main_body(t_entry *ent, t_env **envl);
void				sub_pipe_fork(t_entry *ent, t_env **envl, t_sent **tab);

#endif

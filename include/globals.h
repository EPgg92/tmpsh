#ifndef GLOBALS_H
# define GLOBALS_H

# include <termios.h>
# include "styles.h"

extern char		g_last_char[5];
extern t_caps		*g_caps;

extern char	**g_environ;
extern t_ht_table	*g_variables;
extern t_ht_table	*g_alias;
extern t_ht_table	*g_hash;

extern t_ht_table	*g_builtins;
extern char			*g_shell_dir;
extern t_background_job		*g_jobs;
extern int	g_last_status;
extern pid_t	g_last_pid;

extern t_grammar	*g_grammar;

extern t_pylst      *g_passed_alias;
extern t_pylst      *g_actual_alias;
extern int          g_aliasindepth;
extern t_pylst      *g_heredocs;

struct termios		g_tcsettings;

#endif

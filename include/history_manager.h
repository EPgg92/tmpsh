#ifndef HISTORY_MANAGER_H
# define HISTORY_MANAGER_H

# include "tmpsh.h"

int		history_manager(char *key, t_line *shell_repr, t_cursor *cursor);
int		history_store(int action, t_hist **history);
#endif
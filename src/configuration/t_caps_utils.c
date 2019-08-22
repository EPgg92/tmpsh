#include <ncurses.h>
#include <term.h>
#include "t_caps_utils.h"
#include "libft.h"
#include "environ_utils.h"

/*
** alloc_capabilities_struct:
**
** Allocate a t_caps * element, prepare all termcaps strings in different
** attribute of our structure.
*/

void		alloc_capabilities_struct(t_caps **capabilities)
{
	// if (tgetent(ft_getenv("TERM"), NULL) == -1)
	// 	exit(-1); // WHAT SHOULD I DO ?
	// *capabilities = (t_caps *)ft_memalloc(sizeof(t_caps));
	// (*capabilities)->clear = tgetstr("cl", NULL);
	// (*capabilities)->video = tgetstr("mr", NULL);
	// (*capabilities)->reset_video = tgetstr("me", NULL);
	// (*capabilities)->hide_cursor = tgetstr("vi", NULL);
	// (*capabilities)->reset_cursor = tgetstr("ve", NULL);
	// (*capabilities)->save_pos = tgetstr("sc", NULL);
	// (*capabilities)->reset_pos = tgetstr("rc", NULL);
	// (*capabilities)->del_line = tgetstr("dl", NULL);
	// (*capabilities)->start_line = tgetstr("cr", NULL);
	// (*capabilities)->move_up = tgetstr("up", NULL);
	// (*capabilities)->move_down = tgetstr("do", NULL);
}

int			free_capabilities_struct(t_caps **capabilities, int status)
{
	FREE(*capabilities);
	*capabilities = NULL;
	return (status);
}

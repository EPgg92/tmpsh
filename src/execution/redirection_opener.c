/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 15:37:20 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "tmpsh.h"
#include "fd_management.h"
#include "file_rights.h"
#include "redirection_opener.h"

/*
** convert_dest:
**
** Retrieve the int value of the string redirection->dest.
*/

static void		convert_dest(t_redirection_fd *redirection)
{
	void	*tmp;

	if (digitstr(redirection->dest))
	{
		tmp = int_copy(ft_atoi(redirection->dest));
		ft_strdel((char **)&redirection->dest);
		redirection->dest = tmp;
		redirection->close_dst = false;
		return ;
	}
	if (!ft_strequ(redirection->dest, "-"))
	{
		tmp = NULL;
		if (ft_strequ(redirection->type, "TRUNC_TO_FD"))
			tmp = "TRUNC";
		else if (ft_strequ(redirection->type, "READ_FROM_FD"))
			tmp = "READ_FROM";
		if (tmp)
		{
			redirection->type = tmp;
			open_redirection_file(redirection);
			return ;
		}
	}
	redirection->dest = NULL;
}

/*
** get_options:
**
** Retrieve the appropriate open's flags according to the
** redirection type.
** Retrieve also the expected rights on the file to use
** with check_rigths.
*/

static void		get_options(char *filename, char *type, int *flags, int *rights)
{
	*flags = 0;
	*rights = 0;
	if (ft_strequ(type, "TRUNC"))
	{
		*flags |= O_WRONLY | O_TRUNC;
		*rights = W;
	}
	else if (ft_strequ(type, "APPEND"))
	{
		*flags |= O_WRONLY | O_APPEND;
		*rights = W;
	}
	else if (ft_strequ(type, "READ_FROM"))
	{
		*flags |= O_RDONLY;
		*rights = R;
	}
	if (access(filename, F_OK) == -1)
	{
		*flags |= O_CREAT;
		*rights = -1;
	}
}

static t_bool	open_file(t_redirection_fd *redirection, int flags)
{
	int		fd;

	if ((fd = open(redirection->dest, flags, 0666)) != -1)
	{
		ft_strdel((char **)&redirection->dest);
		redirection->dest = int_copy(fd);
		return (true);
	}
	ft_dprintf(2, NAME_SH" Permission denied : %s\n", redirection->dest);
	return (false);
}

/*
** open_redirection_file:
**
** For a given redirection, open the destination file with
** the expected mode.
*/

void			open_redirection_file(t_redirection_fd *redirection)
{
	int		flags;
	int		rights;

	if (in(redirection->type, "TRUNC", "APPEND", "READ_FROM", NULL))
	{
		redirection->dest = join_pylst(redirection->tagstokens->tokens, "");
		get_options(redirection->dest, redirection->type, &flags, &rights);
		if (rights == -1 && ft_strequ(redirection->type, "READ_FROM"))
			ft_dprintf(2, NAME_SH" No such file or directory : %s\n", \
					redirection->dest);
		else if (rights == -1 || \
				check_rights(redirection->dest, rights | VERBOSE, true, true))
		{
			if (open_file(redirection, flags) == true)
				return ;
		}
		redirection->error = true;
		redirection->dest = NULL;
	}
	else
		convert_dest(redirection);
}

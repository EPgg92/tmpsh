/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 13:26:44 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FD_MANAGEMENT_H
# define FD_MANAGEMENT_H

enum	e_save_fd
{
	save,
	restore,
};

int		replace_fd(int expected_fd, int old_fd);
int		setup_pipe_fd(int pipes_fd[2]);
void	save_std_fd(enum e_save_fd mode);
void	replace_std_fd(int stdin, int stdout);

#endif

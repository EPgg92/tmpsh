/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/09 14:45:00 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** replace_pylst:
**
** Change a part of the given list with the given list
** WARNING : do not duplicate the new_pylst element.
**
** Don't do that :
** var = [1,2,3,4]
** var[0:0] = [9,7,8]
** You're not in Python ! And it seem stupid.
** Use different index please because it will have an UNDEFINED BEHAVIOR
** otherwise, like I don't know what.
** Or please implement this behavior by yourself, up to you.
*/

void	replace_pylst(t_pylst **old_pylst, t_pylst *new_pylst, int from, int to)
{
	t_pylst		*precedence_from;
	t_pylst		*precedence_to;
	t_pylst		*del_slice;

	precedence_from = precedence_pylst(*old_pylst, from);
	precedence_to = precedence_pylst(*old_pylst, to);
	del_slice = *old_pylst;
	if (precedence_from)
	{
		del_slice = precedence_from->next;
		precedence_from->next = new_pylst;
	}
	else
		*old_pylst = new_pylst;
	new_pylst = index_pylst(new_pylst, -1);
	if (precedence_to)
	{
		new_pylst->next = precedence_to->next;
		precedence_to->next = NULL;
	}
	else
		new_pylst->next = NULL;
	free_pylst(&del_slice, 0);
}

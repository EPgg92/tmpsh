/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_stmt_ttm.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 13:33:42 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 13:34:21 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ttm.h"

void	remove_escape_token_ttm(t_tags_tokens_monitor *self)
{
	if (self->token && self->token[0] == *g_grammar->escape)
		ft_strcpy(self->token, self->token + 1);
}

void	is_stmt_ttm(t_tags_tokens_monitor *self)
{
	self->begin_cmd = check_aliases_ttm(self);
	remove_escape_token_ttm(self);
}

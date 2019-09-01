#include "ttm.h"


/*
** is_dquotes_ttm:
**
** description:
** describe what you function do.
**
** parameter:
** - (type) name : what is this param?
**
** return value:
** - (type) value : descibe output.
*/

void	is_dquotes_ttm(t_tags_tokens_monitor *self)
{
	t_bool	indquote;
	char	*update_str;

	indquote = true;
	push_pylst(&self->opened, "DQUOTES", 0, _ptr);
	while (indquote && next_ttm(self, false))
	{
		if (ft_strequ(self->tag, "DQUOTES") && \
				ft_strequ(vindex_pylst(self->opened, -1), "DQUOTES"))
		{
			pop_pylst(&self->opened, -1);
			update_pylst(self->tt->tags, self->i, "END_DQUOTES", 0, _ptr);
			indquote = false;
		}
		else if (search_value(g_grammar->dquotes_opening_tags, self->tag))
			op_selector_ttm(self);
		else
		{
			if (!ft_strequ(vindex_pylst(self->tt->tags, self->i), "VAR"))
				update_str = "STMT";
			else
				update_str = "VAR";
			update_pylst(self->tt->tags, self->i, update_str, 0, _ptr);
		}
	}
}
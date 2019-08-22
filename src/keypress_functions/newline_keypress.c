#include "libft.h"
#include "tmpsh.h"
#include "char_concatenation.h"
#include "display.h"
#include "run_ast.h"
#include "shell_setup.h"
#include "history.h"
#include "line_extend.h"

t_ast		*ast_init(t_tagstokens *tagstok);
void		input_init_tagstokens(t_tagstokens **tagstok, char *shell_str);

/*
** register_command:
**
** Whenever a new command is send, store it to the current history and rewrite
** the history file.
*/

static void		register_command(char *shell_str)
{
	t_hist	*history;
	char	*shell_cpy;
	int		store_history;

	history_store(GET, &history);
	store_history = !history ? TRUE : FALSE;
	if (!(shell_cpy = ft_strdup(shell_str)))
		exit(-1);
	if (shell_cpy[0])
	{
		push_t_hist(&history, shell_cpy, FALSE);
		rewrite_history(history);
	}
	else
		ft_strdel(&shell_cpy);
	if (store_history)
		history_store(STORE, &history);
}

/*
** newline_check:
**
** Whenever a newline is found, check if the current shell is nested or not,
** a new line will be created according to the result.
*/

int			newline_check(t_line **shell_repr, t_cursor **cursor)
{
	t_tagstokens	*tagstoken;
	char			*shell_content;

	shell_content = render_shell_content(*shell_repr);
	input_init_tagstokens(&tagstoken, shell_content);
	if (tagstoken->incomplete)
	{
		add_new_line(*shell_repr, tagstoken, *cursor);
		return (true);
	}
	**cursor = (t_cursor){.row = -1, .column = -1};
	display_shell(*shell_repr, *cursor, false);
	ft_printf("\n");
	manage_shell_repr(GO_FREE, NULL, NULL);
	if (tagstoken->valid && !tagstoken->incomplete)
	{
		register_command(shell_content);
		run_ast(ast_init(tagstoken));
		shell_preconfig(shell_repr, cursor);
		//MUST FREE TAGSTOKEN
		return (false);
	}
	ft_dprintf(2, "tmpsh: sytax error near %s\n", tagstoken->token_error);
	shell_preconfig(shell_repr, cursor);
	//MUST FREE TAGSTOKEN
	return (false);
}

# include "tmpsh.h"
# include "libft.h"
# include "globals.h"
# include "tokenizer_utils.h"
# include "tagstokens.h"

static t_bool cond_check_forbidden_shiftreduce(char *key, size_t i,\
                                                t_pylst *instack,\
                                                t_pylst *tags)
{
    size_t index_forbidden;
    t_pylst *forbidden_node;

    if (ft_strequ("FORBIDDEN", search_value(g_grammar->reverse, key)))
    {
        index_forbidden = i - len_pylst(instack);
        forbidden_node = index_pylst(tags, index_forbidden);
        if (ft_strequ("SPACES", (char *)forbidden_node->value))
            forbidden_node = index_pylst(tags, --index_forbidden);
        forbidden_node->value = "FORBIDDEN";
        return (TRUE);
    }
    return (FALSE);
}

t_bool check_forbidden_shiftreduce(t_pylst *tags)
{
    size_t i;
    size_t len_tags;
    t_pylst *instack;
    char *key;

    i = -1;
    len_tags = len_pylst(tags);
    instack = NULL;
    while (++i < (len_tags + 1))
    {
        key = join_pylst(instack, " ");
        if (cond_check_forbidden_shiftreduce(key, i, instack, tags))
            return (free_pylst(&instack, ft_strdel_out(&key, FALSE)));
        else if (i < len_tags && !ft_strequ("SPACES", \
                                        (char *)get_value_pylst(tags, i)))
        {
             if (!(instack) || ops_begin_with(key, \
                            search_value(g_grammar->grammar, "FORBIDDEN")))
                push_pylst(&instack, get_value_pylst(tags, i), 0, _ptr);
            else
                free_pylst(&instack, 42);
        }
        ft_strdel(&key);
    }
    return (free_pylst(&instack, TRUE));
}

#include "file_management.h"
#include "t_hist_allocation.h"

/*
** history_store:
**
** Function to manage the memory of the t_hist chained list,
** from his creation to his deletion.
** Avaible action : CREATE, GET or FREE
**
** - CREATE : Store the current HISTORY_FILE into a chained list format,
**            giving also the pointer to history.
** - GET : Give the capacity to get the current allocated history.
** - GO_FREE : Free the space allocated to the t_hist chained list.
** - STORE : Register the new history in the store.
*/

int		history_store(int action, t_hist **history)
{
	static t_hist	*saved_history;

	if (action == CREATE)
	{
		if (store_history(history) == FAILURE)
			return (FAILURE);
		saved_history = *history;
	}
	else if (action == STORE)
		saved_history = *history;
	else if (action == GET)
		*history = saved_history;
	else if (action == GO_FREE)
		free_history(&saved_history, 0);
	return (SUCCESS);
}

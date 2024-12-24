/****************************************************************
*	Author:			Doron Battino								*
* 	Reviewer:		 											*
* 	Date: 			17/05/2023									*
* 	Title: 			pqueue										*
* 	Description:	Source file for priority queue.				*
* 	Group: 			HRD30										*
*****************************************************************/

#include <stddef.h>	/* NULL */
#include <assert.h>	/* assert */

#include "pqueue.h"
#include "sortlist.h"
/*****************************************************************/

pq_ty *PQCreate(int (*cmp)(const void *lhs, const void *rhs))
{
	pq_ty *pq = (pq_ty *)(SortListCreate(cmp));
	
	return (pq);
}

void PQDestroy(pq_ty *pq)
{
	assert(NULL != pq);
	
	SortListDestroy((sortlist_ty *)(pq));
}

int PQEnqueue(pq_ty *pq, void *data)
{
	assert(pq);
	assert(data);
	
	return (SortListInsert((sortlist_ty *)(pq), data));
}

void PQDequeue(pq_ty *pq)
{
	assert(NULL != pq);
	
	SortListPopFront((sortlist_ty *)(pq));
}

void *PQPeek(pq_ty *pq)
{
	assert(NULL != pq);
	
	return (SortListGetData(SortListBegin((sortlist_ty *)(pq))));
}

int PQIsEmpty(const pq_ty *pq)
{
	assert(NULL != pq);
	
	return (SortListIsEmpty((sortlist_ty *)(pq)));
}

size_t PQSize(const pq_ty *pq)
{
	assert(NULL != pq);
	
	return (SortListSize((sortlist_ty *)(pq)));
}

void PQClear(pq_ty *pq)
{
	assert(NULL != pq);
	
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

void *PQErase(pq_ty *pq, int (*is_match)(const void *, const void *),
		const void *match_param)
{
	sort_iter_ty to_erase = {NULL};
	sort_iter_ty end = {NULL};
	void *ret = NULL;

	assert(NULL != pq);
	assert(NULL != is_match);
	assert(NULL != match_param);
	
	to_erase = SortListBegin((sortlist_ty *)(pq));
	end = SortListEnd((sortlist_ty *)(pq));

	to_erase = SortListFindIf
		(
			to_erase,
			end,
			is_match,
			match_param
		);
		
	if (NULL != SortListGetData(to_erase) && 
		is_match(SortListGetData(to_erase), match_param))
	{
		ret = SortListGetData(to_erase);
		SortListRemove(to_erase);
		return (ret);
	}
	else
	{
		return (ret);
	}	
}

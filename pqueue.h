/****************************************************************
*	Author:		Doron Battino				*
* 	Reviewer:		 				*
* 	Date: 		17/05/2023				*
* 	Title: 		pqueue					*
* 	Description:	Header file for priority queue.		*
* 	Group: 		HRD30					*
*****************************************************************/

#ifndef __ILRD_PQUEUE_H
#define __ILRD_PQUEUE_H

#include <stddef.h>	/* size_t */
/*****************************************************************/

typedef struct pqueue pq_ty;

/*
*	Error: 		return BAD_PQUEUE
*	Complexity:	O(1). 
*/
pq_ty *PQCreate(int (*cmp)(const void *lhs, const void *rhs));

/*
*	Complexity:	O(size). 
*/
void PQDestroy(pq_ty *pq);

/*
*	Error: 		not 0
*	Complexity:	O(size). 
*/
int PQEnqueue(pq_ty *pq, void *data);

/*
*	Complexity:	O(1). 
*/
void PQDequeue(pq_ty *pq);

/*
*	Complexity:	O(1). 
*/
void *PQPeek(pq_ty *pq);


/*
*	Complexity:	O(1). 
*/
int PQIsEmpty(const pq_ty *pq);


/*
*	Complexity:	O(size). 
*/
size_t PQSize(const pq_ty *pq);


/*
*	Desc:		Empties the pqueue.
*	Complexity:	O(size). 
*/
void PQClear(pq_ty *pq);


/*
*	Desc:		Erase every element that meets a condition.		
*	Input: 		pqueue, matching func ptr, param for matching.
*	Complexity:	O(number of matches). 
*/
void *PQErase(pq_ty *pq, int (*is_match)(const void *, const void *param),
		const void *match_param);


#endif /* __ILRD_PQUEUE_H */

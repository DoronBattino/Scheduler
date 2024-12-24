/****************************************************************
*    Author:		Doron Battino                    	*
*    Date:         	22/05/2023.                  	  	*
*    Title:         	TASK Header file.    			*
*    Description:	Header file for task WS.      	 	*
*    Group:        	HRD30.                    		*
*    Reviewer:                        				*
*****************************************************************/
#ifndef __ILRD_TASK_H
#define __ILRD_TASK_H

#include <stddef.h>	/* size_t */

#include "uid.h"

typedef struct task task_ty;

task_ty *TaskCreate
	(
		size_t interval_seconds_,
		int (*action)(void *p),
		void *param_
	);

void TaskDestroy(task_ty *tsk_);

/*
*	Call the task function with the task param.
*/
int TaskDoNUpdate(task_ty *tsk_);

/*
*	Compare between two tasks next run. 
*/
int TaskCompare(const task_ty *lhs_, const task_ty *rhs_);

/*
*	Return the timr a task should run.
*/
size_t TaskWhen(const task_ty *tsk_);

/*
*	Check if a task has the uid accepted as argument.
*/
int TaskIsMatchID(const task_ty *tsk_, const uid_ty *uid_)/* is_match */;

uid_ty TaskGetID(task_ty *tsk_);



#endif /* __ILRD_TASK_H */

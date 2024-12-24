/************************************************************************
*    Author:    	Doron Battino.         				*            
*    Date:         	22/05/2023.                    			*
*    Title:         	TASK Source File.        			*
*    Description:	Source file for task WS.			*   
*    Group:        	HRD30. 						*
*    Reviewer: 		                                       		*
*************************************************************************/

#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc */
#include <stddef.h>	/* NULL */

#include "task.h"
#include "uid.h"

struct task
{
	uid_ty tid;
	size_t interval_seconds;
	size_t next_run;
	int (*action)(void *param);
	void *param;
	
};

task_ty *TaskCreate
	(
		size_t interval_seconds_,
		int (*action_)(void *param),
		void *param_
	)
{
	task_ty *tsk = NULL;

	assert(NULL != action_);
	assert(NULL != param_);
	
	/* allocate memo and check */
	tsk = (task_ty *)(malloc(sizeof(task_ty)));
	if (NULL == tsk)
	{
		return (NULL);
	}
	
	/* init fileds */
	tsk->tid = UIDCreate();
	if (UIDIsSame(&(tsk->tid), &BAD_UID))
	{
		free(tsk);
		return (NULL);
	}
	tsk->interval_seconds = interval_seconds_;
	tsk->next_run = interval_seconds_;
	tsk->action = action_;
	tsk->param = param_;
	
	/* return task */
	return (tsk);
}

void TaskDestroy(task_ty *tsk_)
{
	free(tsk_);
}

int TaskDoNUpdate(task_ty *tsk_)
{
	int ret = 1;

	assert(NULL != tsk_);
	
	ret = tsk_->action(tsk_->param);
	
	tsk_->next_run += tsk_->interval_seconds;
	
	return (ret);
}

int TaskCompare(const task_ty *lhs_, const task_ty *rhs_)
{
	assert(NULL != lhs_);
	assert(NULL != rhs_);

	return (UIDIsSame(&lhs_->tid, &rhs_->tid));
}

size_t TaskWhen(const task_ty *tsk_)
{
	assert(NULL != tsk_);

	return (tsk_->next_run);
}

int TaskIsMatchID(const task_ty *tsk_, const uid_ty *UID_)
{
	assert(NULL != tsk_);
	assert(1 != UIDIsSame(&BAD_UID, &tsk_->tid));
	
	return (UIDIsSame(&tsk_->tid, UID_));
}

uid_ty TaskGetID(task_ty *tsk_)
{
	assert(NULL != tsk_);

	return (tsk_->tid);
}























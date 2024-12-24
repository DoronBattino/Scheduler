/****************************************************************
*	Author: 	Doron 					*
*	Date: 		20/5					*
*	Title: 		Scheduler.				*
*	Description: 	Test file for scheduler WS		*
*	Group:		HRD30					*
*	Reviewer:	****					*
*****************************************************************/
#include <assert.h>	/* assert */
#include <stddef.h>	/* NULL, size_t */
#include <stdio.h>	/* puts, printf */

#include "scheduler.h"
#include "pqueue.h"
#include "uid.h"
#include "task.h"


#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"

void run_tests(void);
static int ActionPrint(void *p);
static int ActionStop(void *p);
static int ActionSize(void *p);
static int ActionIsEmpty(void *p);


int TestSchedCreate(void);
int TestSchedAdd(void);
int TestSchedRemove(void);
int TestSchedClear(void);
int TestSchedRun(void);
/*****************************************************************/

int main() 
{
    printf("Running tests...\n\n");
    run_tests();
    printf(ANSI_COLOR_GREEN "All tests passed.\n\n" ANSI_COLOR_RESET);
    return 0;
}

void run_tests() 
{
	do
	{
/*		if (0 != TestSchedCreate()) break;*/
/*		if (0 != TestSchedAdd()) break;*/
/*		if (0 != TestSchedRemove()) break;*/
/*		if (0 != TestSchedClear()) break;*/
		if (0 != TestSchedRun()) break;
		
	} while (0);	
}

int ActionSize(void *p)
{
	printf("Size of sched is: %ld\n", SchedSize((sched_ty *)(p)));
	return (0);
}

int ActionIsEmpty(void *p)
{
	(SchedIsEmpty((sched_ty *)(p)))?
		(puts("Empty")):
		(puts("Not Empty"));
	return (0);
}

int ActionPrint(void *p)
{
	printf("%s\n", (char *)(p));
	return (0);
}


int ActionStop(void *p)
{
	(void)(p);
	puts("Stopping scheduler...");
	SchedStop((sched_ty *)(p));
	return (0);
}

int TestSchedCreate()
{
	sched_ty *schd = SchedCreate();
	if (NULL == schd)
	{
		return (1);
	}
	
	puts("TestSchedCreate:\n");
	
	assert(NULL != schd);
	
	SchedDestroy(schd);
	
	puts("<SUCCESS>\n\n");
	
	return (0);
}

int TestSchedAdd()
{
	sched_ty *schd = SchedCreate();
	if (NULL == schd)
	{
		return (1);
	}
	
	puts("TestSchedAdd:\n");
	
	SchedAdd(schd, 5, &ActionPrint, "ActionPrint1 <TEST>");
	SchedAdd(schd, 10, &ActionPrint, "ActionPrint2 <TEST>");
	SchedAdd(schd, 15, &ActionPrint, "ActionPrint3 <TEST>");
	
	assert(3 == SchedSize(schd));
	
	SchedDestroy(schd);
	
	puts("<SUCCESS>\n\n");
	
	return (0);
}

int TestSchedRemove()
{
	uid_ty uid1 = {0};
	uid_ty uid2 = {0};
	uid_ty uid3 = {0};

	sched_ty *schd = SchedCreate();
	if (NULL == schd)
	{
		return (1);
	}
	
	puts("TestSchedRemove:\n");
	
	uid1 = SchedAdd(schd, 5, &ActionPrint, "ActionPrint1 <TEST>");
	uid2 = SchedAdd(schd, 10, &ActionPrint, "ActionPrint2 <TEST>");
	uid3 = SchedAdd(schd, 15, &ActionPrint, "ActionPrint3 <TEST>");
	assert(3 == SchedSize(schd));
	
	SchedRemove(schd, uid1);
	assert(2 == SchedSize(schd));
	SchedRemove(schd, uid2);
	SchedRemove(schd, uid3);
	assert(0 == SchedSize(schd));
	
	SchedDestroy(schd);
	
	puts("<SUCCESS>\n\n");
	
	return (0);
}

int TestSchedClear()
{
	sched_ty *schd = SchedCreate();
	if (NULL == schd)
	{
		return (1);
	}
	
	puts("TestSchedClear:\n");
	
	SchedAdd(schd, 5, &ActionPrint, "ActionPrint1 <TEST>");
	SchedAdd(schd, 10, &ActionPrint, "ActionPrint2 <TEST>");
	SchedAdd(schd, 15, &ActionPrint, "ActionPrint3 <TEST>");
	assert(3 == SchedSize(schd));
	SchedClear(schd);
	assert(0 == SchedSize(schd));
	
	SchedDestroy(schd);
	
	puts("<SUCCESS>\n\n");
	
	return (0);
}

int TestSchedRun(void)
{
	
	sched_ty *schd = SchedCreate();
	if (NULL == schd)
	{
		return (1);
	}
	
	puts("TestSchedRun:\n");
	
	SchedAdd(schd, 5, &ActionPrint, "\n\nHey, I'm the scheduler.\n\n");
	SchedAdd(schd, 10, &ActionPrint, "\n\nI can sched your tasks precisly!\n\n");
	SchedAdd(schd, 15, &ActionPrint, "\n\nGPT can't do that!\n\n");
	SchedAdd(schd, 20, &ActionPrint, "\n\nBye :)\n\n");
	SchedAdd(schd, 25, &ActionSize, schd);
	SchedAdd(schd, 26, &ActionIsEmpty, schd);
	SchedAdd(schd, 27, &ActionStop, schd);
	
	printf("There are %ld tasks in scheduler\n", SchedSize(schd));
	puts("Starting...\n");
	
	SchedRun(schd);
	
	printf("There are %ld tasks left in scheduler\n", SchedSize(schd));
	puts("Done.\n");
	SchedDestroy(schd);
	
	puts("<SUCCESS>\n\n");
	
	return (0);
}



































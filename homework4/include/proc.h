
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef _PROC_H_
#define _PROC_H_

#include "const.h"
#include "type.h"
#include "protect.h"

typedef struct s_stackframe
{					/* proc_ptr points here				↑ Low			*/
	u32 gs;			/* ┓						│			*/
	u32 fs;			/* ┃						│			*/
	u32 es;			/* ┃						│			*/
	u32 ds;			/* ┃						│			*/
	u32 edi;		/* ┃						│			*/
	u32 esi;		/* ┣ pushed by save()				│			*/
	u32 ebp;		/* ┃						│			*/
	u32 kernel_esp; /* <- 'popad' will ignore it			│			*/
	u32 ebx;		/* ┃						↑栈从高地址往低地址增长*/
	u32 edx;		/* ┃						│			*/
	u32 ecx;		/* ┃						│			*/
	u32 eax;		/* ┛						│			*/
	u32 retaddr;	/* return address for assembly code save()	│			*/
	u32 eip;		/*  ┓						│			*/
	u32 cs;			/*  ┃						│			*/
	u32 eflags;		/*  ┣ these are pushed by CPU during interrupt	│			*/
	u32 esp;		/*  ┃						│			*/
	u32 ss;			/*  ┛						┷High			*/
} STACK_FRAME;

typedef struct s_proc
{
	STACK_FRAME regs; /* process registers saved in stack frame */

	u16 ldt_sel;			   /* gdt selector giving ldt base and limit */
	DESCRIPTOR ldts[LDT_SIZE]; /* local descriptors for code and data */

	int ticks; /* remained ticks */
	int priority;
	int delay; /* 用作milli_seconds使用，为0时则不需要延迟 */
	int state; /* 进程的状态：等待态、非等待态 */
	struct s_proc *next;
	u32 pid;		 /* process id passed in from MM */
	char p_name[16]; /* name of the process */
} PROCESS;

typedef struct s_task
{
	task_f initial_eip;
	int stacksize;
	char name[32];
} TASK;

/* Number of tasks */
#define NR_TASKS 6

/* stacks of tasks */
#define STACK_SIZE_PROCESSA 0x8000
#define STACK_SIZE_PROCESSB 0x8000
#define STACK_SIZE_PROCESSC 0x8000
#define STACK_SIZE_PROCESSD 0x8000
#define STACK_SIZE_PROCESSE 0x8000
#define STACK_SIZE_PROCESSF 0x8000

#define STACK_SIZE_TOTAL (STACK_SIZE_PROCESSA + \
						  STACK_SIZE_PROCESSB + \
						  STACK_SIZE_PROCESSC + \
						  STACK_SIZE_PROCESSD + \
						  STACK_SIZE_PROCESSE + \
						  STACK_SIZE_PROCESSF)

#endif
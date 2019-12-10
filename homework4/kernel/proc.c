
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"

/*======================================================================*
                              schedule
 *======================================================================*/
PUBLIC void schedule()
{
	PROCESS *p;
	int greatest_ticks = 0;

	while (!greatest_ticks)
	{
		for (p = proc_table; p < proc_table + NR_TASKS; p++)
		{
			if (p->ticks > greatest_ticks)
			{
				greatest_ticks = p->ticks;
				p_proc_ready = p;
			}
		}

		if (!greatest_ticks)
		{
			for (p = proc_table; p < proc_table + NR_TASKS; p++)
			{
				if (p->delay <= ticks)
				{
					// 说明当前的进程p已经不在delay中了，为其分配ticks
					p->ticks = p->priority;
				}
				else
				{
					// 不为delay中的进程分配ticks
					p->ticks = 0;
				}
			}
		}
	}
}

/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}

/*======================================================================*
                           sys_sprint
 *======================================================================*/
PUBLIC void sys_sprint(char *buf)
{
	disp_str(buf);
	if (disp_pos >= 160 * 25)
	{
		disp_pos = 0;
	}
}

/*======================================================================*
                        sys_milli_seconds
 *======================================================================*/
PUBLIC void sys_milli_seconds(int ms)
{
	p_proc_ready->delay = ms + ticks;
	p_proc_ready->ticks = 0;
	// p_proc_ready++;
	// if (p_proc_ready >= proc_table + NR_TASKS)
	// {
	// 	p_proc_ready = proc_table;
	// }
	schedule();
}

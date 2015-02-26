/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 * 
 *  Copyright (C) 2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010-2012 by Meika Sugimoto
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 */
 
 /*
 *  TOPPERS/SSP�Υ���ץ�ץ����
 */

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "syssvc/serial.h"

#include "sample1.h"


/*
 *  �����ƥॵ���ӥ��Υ��顼�ϥ�ɥ��
 */
#define SVC(expression)											\
	if((expression) < 0)										\
	{															\
		syslog(LOG_NOTICE , "Error at %s : %s caused by %s." ,	\
			__FILE__ , __LINE__ , #expression);					\
	}

/*
 *  ����¹Ԥ���륿�����ؤΥ�å������ΰ�
 */
char_t message[3];

/*
 *  �롼�ײ��
 */
ulong_t	task_loop;		/* ��������ǤΥ롼�ײ�� */

void init_task(intptr_t exinf)
{
#ifndef TASK_LOOP
	volatile ulong_t	i;
	SYSTIM	stime1, stime2;
#endif /* TASK_LOOP */
	
	/* ���ꥢ��ݡ��ȤΥ����ץ� */
	SVC(serial_opn_por(SIO_PORTID));
	SVC(serial_ctl_por(SIO_PORTID , IOCTL_CRLF));
	
	/* ��ư��å������ν��� */
	syslog(LOG_INFO , "Sample program starts.");
	
	/* �����ϥ�ɥ�ε�ư */
	SVC(sta_cyc(MAIN_CYC));
	
	/*
 	 *  �롼�ײ��������
	 *
	 *  TASK_LOOP���ޥ����������Ƥ����硤¬�ꤻ���ˡ�TASK_LOOP����
	 *  �����줿�ͤ򡤥�������ǤΥ롼�ײ���Ȥ��롥
	 *
	 *  MEASURE_TWICE���ޥ����������Ƥ����硤1���ܤ�¬���̤�Τ�
	 *  �ơ�2���ܤ�¬���̤�Ȥ���1���ܤ�¬���Ĺ��λ��֤��Ф뤿�ᡥ
	 */
#ifdef TASK_LOOP
	task_loop = TASK_LOOP;
#else /* TASK_LOOP */

	task_loop = LOOP_REF;
	SVC(get_tim(&stime1));
	for (i = 0; i < task_loop; i++);
	SVC(get_tim(&stime2));
	task_loop = LOOP_REF * 400UL / (stime2 - stime1);

#endif /* TASK_LOOP */

}


void main_task(intptr_t exinf)
{
	static ID tskid = TASK1;
	static uint_t tskno = 1;
	char_t c;
	

	/* ���ꥢ��ݡ��Ȥ����ʸ������ */
	if(serial_rea_dat(SIO_PORTID , &c , 1) > 0)
	{
		switch(c)
		{
		case 'e':
		case 'z':
		case 'Z':
		case 'r':
			message[tskno] = c;
		    break;
		case '1':
			tskid = TASK1;
			tskno = 0;
			break;
		case '2':
			tskid = TASK2;
			tskno = 1;
			break;
		case '3':
			tskid = TASK3;
			tskno = 2;
			break;
		case 'a':
			syslog(LOG_INFO, "#act_tsk(%d)", tskno);
			SVC(act_tsk(tskid));
			break;
		case 'b':
			syslog(LOG_INFO, "#sta_alm(1, 5000)");
			SVC(sta_alm(ALM1 , 5000));
			break;
		case 'B':
			syslog(LOG_INFO, "#stp_alm(1)");
			SVC(stp_alm(ALM1));
			break;
		case 'c':
			syslog(LOG_INFO, "sta_cyc(1)");
			SVC(sta_cyc(CYC1));
			break;
		case 'C':
			syslog(LOG_INFO, "stp_cyc(1)");
			SVC(stp_cyc(CYC1));
			break;
		case 'Q':
			syslog(LOG_NOTICE, "Sample program ends.");
			SVC(ext_ker());
			break;
		default:
			/* ���顼ɽ�� */
			syslog(LOG_INFO , "Unknown command.");
			break;
		}
	}
}


void task(intptr_t exinf)
{
	/* exinf�ϥ������ֹ�  */
	uint_t tskno = (uint_t)exinf;
	static int_t		n = 0;
	char_t command;
	volatile ulong_t i;
	const char	*graph[] = { "|", "  +", "    *" };
	bool_t cont = true;
	
	do
	{
		for (i = 0; i < task_loop; i++)
			;
		
		/* �������ֹ��ɽ�� */
		syslog(LOG_NOTICE, "task%d is running (%03d).   %s",
										tskno, ++n, graph[tskno-1]);
		
		/* ���ޥ�ɼ�������å������ΰ�򥯥ꥢ */
		command = message[tskno - 1];
		message[tskno - 1] = 0;
		
		switch(command)
		{
		case 'e':
			cont = false;
			syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
			break;
		case 'z':
			syslog(LOG_NOTICE, "#%d#raise CPU exception", tskno);
			RAISE_CPU_EXCEPTION;
			break;
		default:
			break;
		}
	}while(cont == true);
}


void alarm_handler(intptr_t exinf)
{
	ID tskid = (ID)exinf;
	
	syslog(LOG_INFO , "Alarm handler is raised.");
	SVC(iact_tsk(tskid));
}

void main_task_cychdr(intptr_t exinf)
{
	ID tskid = (ID)exinf;
	
	(void)iact_tsk(tskid);
}

void cyclic_handler(intptr_t exinf)
{
	syslog(LOG_INFO , "Cyclic handler is raised.");
}

#ifdef TEST_EXC
void exc_handler(void *p_excinf)
{
	syslog(LOG_INFO , "CPU exception handler.");
	syslog(LOG_INFO , "Kernel exit.");
	
	(void)ext_ker();
}
#endif /* TEST_EXC */


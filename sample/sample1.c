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
 *
 *  SSP�����ͥ�δ���Ū��ư����ǧ���뤿��Υ���ץ�ץ���ࡥ
 *
 *  �ץ����γ���:
 *
 *  �桼�����󥿥ե�������������ĥᥤ�󥿥����ȡ�3�Ĥ��¹Լ¹Ԥ����
 *  �������Ȥǹ�������롥������ID�����ͥ��������ϰʲ����̤ꡥ
 *     (������ID)   (��ư��ͥ����)    (�¹Ի�ͥ����)
 *      MAIN_TASK    MAIN_PRIORITY     (����Ʊ��)
 *      TASK1        TASK1_PRIORITY    (����Ʊ��)
 *      TASK2        TASK2_PRIORITY    (����Ʊ��)
 *      TASK3        TASK3_PRIORITY    TASK3_EXEPRIORITY
 *
 *  �ޤ�����ư������2�äμ����ϥ�ɥ�ʼ����ϥ�ɥ�ID: CYC1�ˤ����
 *  �ᥤ�󥿥�����ư�Ѥμ����ϥ�ɥ�(�����ϥ�ɥ�ID: MAIN_CYC)���Ѥ��롥
 *
 *  �¹Լ¹Ԥ���륿�����ϡ�task_loop����롼�פ�¹Ԥ����٤ˡ���������
 *  �¹���Ǥ��뤳�Ȥ򤢤�魯��å�������ɽ�����롥���롼�פ�¹Ԥ���
 *  �Τϡ����롼�פʤ��ǥ�å���������Ϥ���ȡ�¿�̤Υ�å�����������
 *  ���졤�ץ�����ư���ǧ�����餯�ʤ뤿��Ǥ��롥�ޤ�����®�ʥ�
 *  �ꥢ��ݡ��Ȥ��Ѥ��ƥ�å���������Ϥ�����ˡ����٤ƤΥ�å�����
 *  �����ϤǤ���褦�ˡ���å��������̤����¤���Ȥ�����ͳ�⤢�롥
 *
 *  �����ϥ�ɥ�(CYC1)�ϡ���ư�������Ȥ򼨤���å�������ɽ�����롥
 *  �ץ����ε�ưľ��ϡ������ϥ�ɥ�(CYC1)����߾��֤ˤʤäƤ��롥
 *
 *  �ᥤ�󥿥����ϡ������ϥ�ɥ�(MAIN_CYC)����100�ߥ��ä��Ȥ˵�ư���졤
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ�����Ϥ�Ԥ������Ϥ��줿
 *  ʸ�����б�����������¹Ԥ��롥���Ϥ��줿ʸ���Ƚ����δط��ϼ����̤ꡥ
 *  'Q'�����Ϥ����ȡ��ץ�����λ���롥
 *
 *  '1' : �оݥ�������TASK1���ڤ괹����ʽ������ˡ�
 *  '2' : �оݥ�������TASK2���ڤ괹���롥
 *  '3' : �оݥ�������TASK3���ڤ괹���롥
 *  'a' : �оݥ�������act_tsk�ˤ�굯ư���롥
 *  'e' : �оݥ�������ؿ��Υ꥿����ˤ�꽪λ�����롥
 *  'c' : �����ϥ�ɥ��ư��Ϥ����롥
 *  'C' : �����ϥ�ɥ��ư����ߤ����롥
 *  'b' : ���顼��ϥ�ɥ��5�ø�˵�ư����褦ư��Ϥ����롥
 *  'B' : ���顼��ϥ�ɥ��ư����ߤ����롥
 *  'z' : �оݥ�������CPU�㳰��ȯ��������ʥ�������λ������ˡ�
 *  's' : ���٥�ȥե饰(ID:FLG1)�������������˴�Ϣ����ӥåȤ򥻥åȤ��롥
 *  'l' : ���٤ƤΥ�������Ϣ���륤�٥�ȥե饰(ID:FLG1)�ΥӥåȤ򥯥ꥢ���롥
 *  'p' : �ݡ���󥰤ǥ��٥�ȥե饰(FLG1)���Ԥġ�
 *  'd' : �ݡ���󥰤ǥǡ������塼(ID:DTQ1)�إǡ������������롥
 *  'r' : �ݡ���󥰤ǥǡ������塼(ID:DTQ1)����ǡ�����������롥
 */

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "syssvc/serial.h"

#ifdef TOPPERS_CQSTARM
#include "cq_starm.h"  /* �ܡ��ɤ�LED�˥����������뤿��ܡ��ɰ�¸��������ե�����򥤥󥯥롼�� */
#endif
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
	
#ifdef TOPPERS_CQSTARM
        /* LED��GPIOC��6��PIN���ޤ��Ϥ��������������� */
        sil_wrh_mem((void*)GPIO_ODR(GPIOC_BASE), (sil_reh_mem((void*)GPIO_ODR(GPIOC_BASE)) | 0x40));
#endif
	/* ���ꥢ��ݡ��ȤΥ����ץ� */
	SVC(serial_opn_por(TASK_PORTID));
	SVC(serial_ctl_por(TASK_PORTID , IOCTL_CRLF));
	
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
	if(serial_rea_dat(TASK_PORTID , &c , 1) > 0)
	{
		switch(c)
		{
		case 'e':
		case 's':
		case 'l':
		case 'p':
		case 'd':
		case 'r':
		case 'z':
			message[tskno-1] = c;
		    break;
		case '1':
			tskid = TASK1;
			tskno = 1;
			break;
		case '2':
			tskid = TASK2;
			tskno = 2;
			break;
		case '3':
			tskid = TASK3;
			tskno = 3;
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
	int_t		n = 0;
	char_t command;
	volatile ulong_t i;
	const char	*graph[] = { "|", "  +", "    *" };
	bool_t cont = true;
	FLGPTN pattern;
	const FLGPTN flgptn[] = { 0x00000001U, 0x00000002U, 0x00000004U };
	const FLGPTN allptn = 0x00000007U;
	intptr_t dtqdata;
	
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
			syslog(LOG_INFO, "#%d#terminate task", tskno);
			break;
		case 's':
			SVC(set_flg(FLG1 , flgptn[tskno - 1]));
			syslog(LOG_INFO, "#%d#set_flg(flgid=%d , mask=%d)",
									tskno , FLG1 , flgptn[tskno - 1]);
			break;
		case 'l':
			SVC(clr_flg(FLG1 , ~allptn));
			syslog(LOG_INFO, "#%d#clr_flg(flgid=%d)", tskno , FLG1);
			break;
		case 'p':
			SVC(pol_flg(FLG1 , allptn , TWF_ORW , &pattern));
			syslog(LOG_INFO, "#%d#pol_flg(flgid=%d , value=%u)", tskno , FLG1 , pattern);
			break;
		case 'd':
			SVC(psnd_dtq(DTQ1 , (intptr_t)tskno));
			syslog(LOG_INFO, "#%d#snd_dtq(dtqid=%d , value=%u)", tskno , DTQ1 , tskno);
			break;
		case 'r':
			SVC(prcv_dtq(DTQ1 , (intptr_t *)(&dtqdata)));
			syslog(LOG_INFO, "#%d#rcv_dtq(dtqid=%d , value=%u)", tskno , DTQ1 , dtqdata);
			break;
#ifdef CPUEXC1
		case 'z':
			syslog(LOG_NOTICE, "#%d#raise CPU exception", tskno);
			RAISE_CPU_EXCEPTION;
			break;
#endif /* CPUEXC1 */
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
#ifdef TOPPERS_CQSTARM
        /* LED�����ǽ��� */
        /* ���δؿ���100ms�����ϥ�ɥ�ؿ��ʤΤǡ�������10�󤴤Ȥ�LED���������֤�ȿž�����롣 */
        /* �Ĥޤꡢ1��������1�þ����򤳤��Ǽ¸����롣 */
        {
          static uint_t count = 0;
          if (++count >= 10) {
            sil_wrh_mem((void*)GPIO_ODR(GPIOC_BASE), (sil_reh_mem((void*)GPIO_ODR(GPIOC_BASE)) ^ 0x40));
            count = 0;
          }
        }
#endif
}

void cyclic_handler(intptr_t exinf)
{
	syslog(LOG_INFO , "Cyclic handler is raised.");
}

#ifdef CPUEXC1
void exc_handler(void *p_excinf)
{
	syslog(LOG_INFO , "CPU exception handler.");
	syslog(LOG_INFO , "Kernel exit.");
	
	(void)ext_ker();
}
#endif /* CPUEXC1 */


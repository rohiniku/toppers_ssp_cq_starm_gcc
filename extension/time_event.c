/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2011 by Meika Sugimoto
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�
 *  �����ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭�����
 *      ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ�����
 *      ��������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻���
 *      �Ǥ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ����Ѽԥ�
 *      �˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ�����̵��
 *      �ڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻���
 *      �Ǥ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ���
 *        �𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»��
 *      ����⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ��ޤ���
 *      �ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���ͳ�˴��
 *      �����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ���
 *  ��TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū���Ф�
 *  ��Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ�����������
 *  �ˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ����
 *  ��ʤ���
 * 
 */

#include "kernel_impl.h"

#include "time_event.h"


/*
 *  ���ߤΥ����ƥ�����ñ��: 1�ߥ��á�
 *
 *  ��̩�ˤϡ����Υ�����ƥ��å��Υ����ƥ���
 */
EVTTIM	current_time;

/*
 *  �����।�٥�ȥҡ������ͭ���ʺǾ��Υ����ƥ�����ñ��: 1�ߥ��á�
 */
EVTTIM	min_time;


/*
 *  �����।�٥�ȥ��塼�Υ��塼�إå�
 *
 *  �����।�٥�ȥ��塼�֥�å��ν�ü�˳��ݤ��롥
 */
#define TMEVT_HEAD()	(tmevt_queue[tnum_tmevt_queue])
#define TMEVT_NULL		((QUEIDX)tnum_tmevt_queue)

/*
 *  ���٥��ȯ��������ӥޥ���
 *
 *  ���٥��ȯ������ϡ�min_time����������ͤ���Ӥ��롥���ʤ����
 *  min_time��Ǿ��͡ʺǤ�ᤤ����ˡ�mit_time-1�������͡ʺǤ�󤤻����
 *  �Ȥߤʤ�����Ӥ��롥
 */
#define	EVTTIM_LT(t1, t2) (((t1) - min_time) < ((t2) - min_time))
#define	EVTTIM_LE(t1, t2) (((t1) - min_time) <= ((t2) - min_time))

/*
 *  �����।�٥�Ȥν����
 */

#ifdef TOPPERS_tmevtini

void
initialize_time_event(void)
{
	/* �ѿ��ν���� */
	current_time = 0U;
	min_time = 0U;
	
	/* �����।�٥�ȥ��塼�ν���� */
	queue_initialize(&TMEVT_HEAD() , (QUEIDX)tnum_tmevt_queue);
}

#endif /* TOPPERS_tmevtini */

/*
 *  �����।�٥�Ȥ���Ͽ
 */

#ifdef TOPPERS_tmevtenq

void
time_event_enqueue(ID tmevtid , EVTTIM evttim , CBACK callback , uintptr_t arg)
{
	QUEIDX pos = TMEVT_HEAD().next;
	
	/* �������֤򸡺� */
	while((pos != TMEVT_NULL)
			&& (EVTTIM_LE(tmevt_time[pos] , evttim))) {
		pos = tmevt_queue[pos].next;
	}
	
	/* ���塼������ */
	queue_insert_prev(&(tmevt_queue[0]) , pos , (QUEIDX)tmevtid);
	tmevt_callback[tmevtid] = (CBACK)callback;
	tmevt_arg[tmevtid] = arg;
	tmevt_time[tmevtid] = evttim;
}

#endif /* TOPPERS_tmevtenq */

/*
 *  �����।�٥�Ȥκ��
 */

#ifdef TOPPERS_tmevtdeq

void
time_event_dequeue(ID tmevtid)
{
	/* ���塼������ */
	(void)queue_delete_next(&(tmevt_queue[0]) , (QUEIDX)tmevtid);
}

#endif /* TOPPERS_tmevtdeq */

/*
 *  �����ƥ���������
 */

#ifdef TOPPERS_sig_tim

void
signal_time(void)
{
	QUEIDX pos = TMEVT_HEAD().next , evtid;
	
	i_lock_cpu();
	
	/* ���߻���ι��� */
	current_time += (EVTTIM)TIC_NUME;
	
	/* ������Хå��μ¹� */
	while((pos != TMEVT_NULL)
			&& EVTTIM_LT(tmevt_time[pos] , current_time)) {
		(void)queue_delete_next(&(tmevt_queue[0]) , pos);
		evtid = pos;
		pos = tmevt_queue[pos].next;
		(*tmevt_callback[evtid])(tmevt_arg[evtid]);
	}

	/* min_time�ι��� */
	min_time = current_time;
	
	i_unlock_cpu();
}

#endif /* TOPPERS_sig_tim */

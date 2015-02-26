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

/*
 *  ���顼��ϥ�ɥ鵡ǽ
 */

#include "alarm.h"
#include "check.h"
#include "time_event.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */

#ifndef LOG_ALM_ENTER
#define LOG_ALM_ENTER(almidx)
#endif /* LOG_ALM_ENTER */

#ifndef LOG_ALM_LEAVE
#define LOG_ALM_LEAVE(almidx)
#endif /* LOG_ALM_LEAVE */

#ifndef LOG_STA_ALM_ENTER
#define LOG_STA_ALM_ENTER(almid, almtim)
#endif /* LOG_STA_ALM_ENTER */

#ifndef LOG_STA_ALM_LEAVE
#define LOG_STA_ALM_LEAVE(ercd)
#endif /* LOG_STA_ALM_LEAVE */

#ifndef LOG_STP_ALM_ENTER
#define LOG_STP_ALM_ENTER(almid)
#endif /* LOG_STP_ALM_ENTER */

#ifndef LOG_STP_ALM_LEAVE
#define LOG_STP_ALM_LEAVE(ercd)
#endif /* LOG_STP_ALM_LEAVE */


/* �����ϥ�ɥ�ID�򥿥��।�٥��ID���Ѵ� */
#define ALM_EVTID(almid)	((ID)(INDEX_ALM(almid) + almevtid_offset))
#define INDEX_ALM(almid)	((uint_t)((almid) - TMIN_ALMID))

/* ���顼��ϥ�ɥ�θĿ� */
#define tnum_alm			((uint_t)(tmax_almid - TMIN_ALMID + 1))

/* ���顼���ư����֤�ɽ���ӥåȥޥå� */
#define ALMACT_BIT(index)	(1U << (index))


/* ���顼��ϥ�ɥ�¹ԥ����।�٥�� */
void call_almhdr(uint_t almidx);


/*
 *  ���顼��ϥ�ɥ鵡ǽ�ν����
 */

#ifdef TOPPERS_almcal

void
initialize_alarm(void)
{
	/* ���ƤΥ��顼�����߾��֤ˤ��� */
	almcb_almact = 0U;
}

#endif /* TOPPERS_almcal */

/*
 *  ���顼��γ���
 */

#ifdef TOPPERS_sta_alm

ER
sta_alm(ID almid , RELTIM almtim)
{
	ER ercd;
	uint_t index = INDEX_ALM(almid);
	
	LOG_STA_ALM_ENTER(almid, almtim);
	CHECK_TSKCTX_UNL();
	CHECK_ALMID(almid);
	
	t_lock_cpu();
	
	if((almcb_almact & ALMACT_BIT(index)) != 0U) {
		time_event_dequeue(ALM_EVTID(almid));
	}
	else {
		almcb_almact |= ALMACT_BIT(index);
	}
	
	time_event_enqueue(ALM_EVTID(almid) ,
		current_time + (EVTTIM)almtim , (CBACK)call_almhdr , index);
	
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_STA_ALM_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_sta_alm */

/*
 *  ���顼������
 */

#ifdef TOPPERS_stp_alm

ER
stp_alm(ID almid)
{
	ER ercd;
	uint_t index = INDEX_ALM(almid);
	
	LOG_STP_ALM_ENTER(almid);
	CHECK_TSKCTX_UNL();
	CHECK_ALMID(almid);
	
	t_lock_cpu();
	
	if((almcb_almact & ALMACT_BIT(index)) != 0U) {
		almcb_almact &= ~ALMACT_BIT(index);
		time_event_dequeue(ALM_EVTID(almid));
	}
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_STP_ALM_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_stp_alm */

/*
 *  ���顼��ϥ�ɥ鵯ư�롼����
 */

#ifdef TOPPERS_almcal

void
call_almhdr(uint_t almidx)
{
	/* ���顼��ϥ�ɥ����߾��֤ˤ��� */
	almcb_almact &= ~ALMACT_BIT(almidx);
	
	i_unlock_cpu();
	
	/* ���顼��ϥ�ɥ�μ¹� */
	LOG_ALM_ENTER(almidx);
	(*alminib_almhdr[almidx])(alminib_exinf[almidx]);
	LOG_ALM_LEAVE(almidx);
	
	if (!i_sense_lock()) {
		i_lock_cpu();
	}
}

#endif /* TOPPERS_almcal */


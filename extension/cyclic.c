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
 *  �����ϥ�ɥ鵡ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "time_event.h"
#include "cyclic.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_CYC_ENTER
#define LOG_CYC_ENTER(cycidx)
#endif /* LOG_CYC_ENTER */

#ifndef LOG_CYC_LEAVE
#define LOG_CYC_LEAVE(cycidx)
#endif /* LOG_CYC_LEAVE */

#ifndef LOG_STA_CYC_ENTER
#define LOG_STA_CYC_ENTER(cycid)
#endif /* LOG_STA_CYC_ENTER */

#ifndef LOG_STA_CYC_LEAVE
#define LOG_STA_CYC_LEAVE(ercd)
#endif /* LOG_STA_CYC_LEAVE */

#ifndef LOG_STP_CYC_ENTER
#define LOG_STP_CYC_ENTER(cycid)
#endif /* LOG_STP_CYC_ENTER */

#ifndef LOG_STP_CYC_LEAVE
#define LOG_STP_CYC_LEAVE(ercd)
#endif /* LOG_STP_CYC_LEAVE */


/* �����ϥ�ɥ�ID�򥿥��।�٥��ID���Ѵ� */
#define CYC_EVTID(cycidx)	((ID)((cycidx) + cycevtid_offset))
#define INDEX_CYC(cycid)	((uint_t)((cycid) - TMIN_CYCID))


/* �����ϥ�ɥ��ư����֤�ɽ���ӥåȥޥå� */
#define CYCACT_BIT(index)	(1U << (index))

/*
 *  �����ϥ�ɥ鵯ư�롼����
 */
void call_cychdr(uintptr_t cycidx);

/*
 *  �����ϥ�ɥ鵡ǽ�ν����
 */

#ifdef TOPPERS_cycini

void
initialize_cyclic(void)
{
	uint_t i;
	
	/* �����ϥ�ɥ�ξ������� */
	cyccb_cycact = cycinib_cycact;
	
	for(i = 0U ; i < tnum_cyc ; i++) {
		cyccb_evttim[i] = 0U;
		
		/* �����ϥ�ɥ�ν����ư */
		if((cycinib_cycact & CYCACT_BIT(i)) != 0U) {
			time_event_enqueue(CYC_EVTID(i) ,
				(EVTTIM)cycinib_cycphs[i] , call_cychdr , i);
			cyccb_evttim[i] = cycinib_cycphs[i];
		}
	}
}

#endif /* TOPPERS_cycini */

#ifdef TOPPERS_sta_cyc

ER
sta_cyc(ID cycid)
{
	ER ercd;
	uint_t index = INDEX_CYC(cycid);
	EVTTIM evttim;
	
	LOG_STA_CYC_ENTER(cycid);
	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	
	t_lock_cpu();
	
	if((cyccb_cycact & CYCACT_BIT(index)) != 0U) {
		time_event_dequeue(CYC_EVTID(index));
	}
	else {
		cyccb_cycact |= CYCACT_BIT(index);
	}

	evttim = current_time + cycinib_cycphs[index];
	time_event_enqueue(CYC_EVTID(index) ,
		 evttim , call_cychdr , index);
	cyccb_evttim[index] = evttim;
	
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_STA_CYC_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_sta_cyc */


#ifdef TOPPERS_stp_cyc

ER
stp_cyc(ID cycid)
{
	ER ercd;
	uint_t index = INDEX_CYC(cycid);
	
	LOG_STP_CYC_ENTER(cycid);
	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	
	t_lock_cpu();
	
	if((cyccb_cycact & CYCACT_BIT(index)) != 0U) {
		cyccb_cycact &= ~CYCACT_BIT(index);
		time_event_dequeue(CYC_EVTID(index));
	}
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_STA_CYC_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_stp_cyc */

#ifdef TOPPERS_cyccal

void
call_cychdr(uintptr_t cycidx)
{
	cyccb_evttim[cycidx] += cycinib_cyctim[cycidx];

	/* �������Υ����।�٥�Ȥ���Ͽ */
	time_event_enqueue((ID)cycidx ,
		cyccb_evttim[cycidx] , call_cychdr , cycidx);
	
	i_unlock_cpu();
	
	/* �����ϥ�ɥ��¹� */
	LOG_CYC_ENTER(cycidx);
	(*cycinib_cychdr[cycidx])(cycinib_exinf[cycidx]);
	LOG_CYC_LEAVE(cycidx);
	
	if (!i_sense_lock()) {
		i_lock_cpu();
	}
}

#endif /* TOPPERS_cyccal */

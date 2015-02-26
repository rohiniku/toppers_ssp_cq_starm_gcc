/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *		�ǡ������塼��ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "dataqueue.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_PSND_DTQ_ENTER
#define LOG_PSND_DTQ_ENTER(dtqid, data)
#endif /* LOG_PSND_DTQ_ENTER */

#ifndef LOG_PSND_DTQ_LEAVE
#define LOG_PSND_DTQ_LEAVE(ercd)
#endif /* LOG_PSND_DTQ_LEAVE */

#ifndef LOG_IPSND_DTQ_ENTER
#define LOG_IPSND_DTQ_ENTER(dtqid, data)
#endif /* LOG_IPSND_DTQ_ENTER */

#ifndef LOG_IPSND_DTQ_LEAVE
#define LOG_IPSND_DTQ_LEAVE(ercd)
#endif /* LOG_IPSND_DTQ_LEAVE */

#ifndef LOG_PRCV_DTQ_ENTER
#define LOG_PRCV_DTQ_ENTER(dtqid, p_data)
#endif /* LOG_PRCV_DTQ_ENTER */

#ifndef LOG_PRCV_DTQ_LEAVE
#define LOG_PRCV_DTQ_LEAVE(ercd, data)
#endif /* LOG_PRCV_DTQ_LEAVE */

/*
 *  �ǡ������塼�ؤΥǡ�������
 */
void
enqueue_data(intptr_t* const data , uint8_t* const tail , const uint8_t size , const intptr_t sdata);

/*
 *  �ǡ������塼����Υǡ�������
 */
void
dequeue_data(intptr_t* const data , uint8_t* const head , const uint8_t size , intptr_t* rdata);


/*
 *  �ǡ������塼�ο�
 */
#define tnum_dtq	((uint_t)(tmax_dtqid - TMIN_DTQID + 1))

/*
 *  �ǡ������塼ID����ǡ������塼�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_DTQ(dtqid)	((uint_t)((dtqid) - TMIN_DTQID))

/*
 *  �ǡ������塼��ǽ�ν����
 */
#ifdef TOPPERS_dtqini

void
initialize_dataqueue(void)
{
	uint_t	i;

	for (i = 0U ; i < tnum_dtq ; i++) {
		dtqcb_count[i] = 0U;
		dtqcb_head[i] = 0U;
		dtqcb_tail[i] = 0U;
	}
}

#endif /* TOPPERS_dtqini */


/*
 *  �ǡ������塼�����դ��Υ����å�
 */

Inline bool_t
data_full(uint8_t count , uint8_t size)
{
	return (count >= size)? true : false;
}

/*
 *  �ǡ������塼�������Υ����å�
 */

Inline bool_t
data_empty(uint8_t count)
{
	return (count == 0)? true : false;
}


/*
 *  �ǡ������塼�ؤΥǡ�������
 */


#ifdef TOPPERS_dtqenq

void
enqueue_data(intptr_t* const data , uint8_t* const tail , const uint8_t size , const intptr_t sdata)
{
	data[*tail] = sdata;
	(*tail)++;
	if (*tail >= size) {
		*tail = 0U;
	}
}

#endif /* TOPPERS_dtqenq */

/*
 *  �����Ԥ����塼����Ƭ����������Υǡ�������
 */
#ifdef TOPPERS_dtqdeq

void
dequeue_data(intptr_t* const data , uint8_t* const head , const uint8_t size , intptr_t* rdata)
{
	*rdata = data[*head];
	(*head)++;
	if (*head >= size) {
		*head = 0U;
	}
	
}

#endif /* TOPPERS_dtqdeq */

/*
 *  �ǡ������塼�ؤ������ʥݡ���󥰡�
 */
#ifdef TOPPERS_psnd_dtq

ER
psnd_dtq(ID dtqid, intptr_t data)
{
	ER		ercd;
	int_t	index;
	
	LOG_PSND_DTQ_ENTER(dtqid, data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	
	t_lock_cpu();
	index = INDEX_DTQ(dtqid);
	
	if (!data_full(dtqcb_count[index] , dtqinib_size[index]))
	{
		enqueue_data(dtqinib_data[index] , &(dtqcb_tail[index]) , 
					dtqinib_size[index] , data);
		dtqcb_count[index]++;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();
	
  error_exit:
	LOG_PSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_psnd_dtq */

/*
 *  �ǡ������塼�ؤ������ʥݡ���󥰡��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_ipsnd_dtq

ER
ipsnd_dtq(ID dtqid, intptr_t data)
{
	ER		ercd;
	int_t	index;

	LOG_IPSND_DTQ_ENTER(dtqid, data);
	CHECK_INTCTX_UNL();
	CHECK_DTQID(dtqid);

	i_lock_cpu();
	index = INDEX_DTQ(dtqid);
	
	if (!data_full(dtqcb_count[index] , dtqinib_size[index]))
	{
		enqueue_data(dtqinib_data[index] , &(dtqcb_tail[index]) , 
					dtqinib_size[index] , data);
		dtqcb_count[index]++;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	i_unlock_cpu();

  error_exit:
	LOG_IPSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ipsnd_dtq */

/*
 *  �ǡ������塼����μ����ʥݡ���󥰡�
 */
#ifdef TOPPERS_prcv_dtq

ER
prcv_dtq(ID dtqid, intptr_t *p_data)
{
	ER		ercd;
	int_t	index;

	LOG_PRCV_DTQ_ENTER(dtqid, p_data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);

	t_lock_cpu();
	index = INDEX_DTQ(dtqid);
	
	if (!data_empty(dtqcb_count[index]))
	{
		dequeue_data(dtqinib_data[index] , &(dtqcb_head[index]) , 
					dtqinib_size[index] , p_data);
		dtqcb_count[index]--;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

  error_exit:
	LOG_PRCV_DTQ_LEAVE(ercd, *p_data);
	return(ercd);
}

#endif /* TOPPERS_prcv_dtq */

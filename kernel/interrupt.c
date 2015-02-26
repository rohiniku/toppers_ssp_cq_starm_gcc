/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2010-2011 by Meika Sugimoto
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
 *		����ߴ�����ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "interrupt.h"


/* 
 *  ����ߴ�����ǽ�ν����
 */
#ifdef TOPPERS_intini
#ifndef OMIT_INITIALIZE_INTERRUPT

void
initialize_interrupt(void)
{
	uint_t			i;
	
	for (i = 0U; i < tnum_inhno; i++) {
		x_define_inh(inhinib_inhno[i], (FP)(inhinib_entry[i]));
	}
	for (i = 0U; i < tnum_intno; i++) {
		x_config_int(intinib_intno[i], intinib_intatr[i], intinib_intpri[i]);
	}
}

#endif /* OMIT_INITIALIZE_INTERRUPT */
#endif /* TOPPERS_intini */

/*
 *  ����ߤζػ�
 */
#ifdef TOPPERS_dis_int
#ifdef TOPPERS_TARGET_SUPPORT_DIS_INT

ER
dis_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;
	
	CHECK_TSKCTX();
	CHECK_INTNO_DISINT(intno);
	
	locked = t_sense_lock();
	
	if (!locked) {
		t_lock_cpu();
	}
	
	if (t_disable_int(intno)) {
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;
	}
	
	if (!locked) {
		t_unlock_cpu();
	}

  error_exit:
	return(ercd);
}

#endif /* TOPPERS_SUPPORT_DIS_INT */
#endif /* TOPPERS_dis_int */


/*
 *  ����ߤε���
 */
#ifdef TOPPERS_ena_int
#ifdef TOPPERS_TARGET_SUPPORT_ENA_INT

ER
ena_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	CHECK_TSKCTX();
	CHECK_INTNO_DISINT(intno);

	locked = t_sense_lock();
	if (!locked) {
		t_lock_cpu();
	}
	
	if (t_enable_int(intno)) {
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;
	}
	
	if (!locked) {
		t_unlock_cpu();
	}

  error_exit:
	return(ercd);
}

#endif /* TOPPERS_SUPPORT_ENA_INT */
#endif /* TOPPERS_ena_int */

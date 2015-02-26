/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2011-2012 by Meika Sugimoto
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
 *		���٤Ƥδؿ��򥳥�ѥ��뤹�뤿������
 */

#ifndef TOPPERS_ALLFUNC_H
#define TOPPERS_ALLFUNC_H

/* startup.c */
#define TOPPERS_sta_ker
#define TOPPERS_ext_ker

/* task.c */
#define TOPPERS_get_ipriself
#define TOPPERS_get_ipri
#define TOPPERS_tskini
#define TOPPERS_tsksched
#define TOPPERS_tskrun
#define TOPPERS_tskdsp
#define TOPPERS_tskact
#define TOPPERS_tskdmt


/* task_manage.c */
#define TOPPERS_act_tsk
#define TOPPERS_iact_tsk

/* sys_manage.c */
#define TOPPERS_loc_cpu
#define TOPPERS_iloc_cpu
#define TOPPERS_unl_cpu
#define TOPPERS_iunl_cpu
#define TOPPERS_dis_dsp
#define TOPPERS_ena_dsp
#define TOPPERS_sns_ctx
#define TOPPERS_sns_loc
#define TOPPERS_sns_dsp
#define TOPPERS_sns_dpn
#define TOPPERS_sns_ker

/* interrupt.c */
#define TOPPERS_intini
#define TOPPERS_dis_int
#define TOPPERS_ena_int

/* exception.c */
#define TOPPERS_excini

/* time_event.c */
#define TOPPERS_tmevtini
#define TOPPERS_tmevtenq
#define TOPPERS_tmevtdeq
#define TOPPERS_sig_tim

/* cyclic.c */
#define TOPPERS_cycini
#define TOPPERS_sta_cyc
#define TOPPERS_stp_cyc
#define TOPPERS_cyccal

/* alarm.c */
#define TOPPERS_almini
#define TOPPERS_sta_alm
#define TOPPERS_stp_alm
#define TOPPERS_almcal

/* time_manage.c */
#define TOPPERS_get_tim

#endif /* TOPPERS_ALLFUNC_H */

/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�CQ-STARM�ѡ�
 */

#ifndef TOPPERS_TARGET_SERIAL_H
#define TOPPERS_TARGET_SERIAL_H

#include "cq_starm.h"
#include "target_syssvc.h"

/*
 *  SIO�γ���ߥ٥����ֹ�
 */
#if (SIO_PORTID == 1)
#define INHNO_SIO		IRQ_VECTOR_USART1
#define INTNO_SIO		IRQ_VECTOR_USART1
#elif (SIO_PORID == 2)
#define INHNO_SIO		IRQ_VECTOR_USART2
#define INTNO_SIO		IRQ_VECTOR_USART2
#endif
#define INTPRI_SIO		-3				/* �����ͥ���� */
#define INTATR_SIO		0				/* �����°�� */

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_RDY_SND    1U        /* ������ǽ������Хå� */
#define SIO_RDY_RCV    2U        /* �������Υ�����Хå� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ���ꥢ��ݡ��Ȥδ����֥�å�
 */
typedef struct sio_port_control_block {
	ID port;
	uint32_t reg;
	intptr_t exinf;
} SIOPCB;

/*
 *  SIO�����
 */
extern void sio_initialize(intptr_t exinf);

/*
 *  ���ꥢ�륪���ץ�
 */
extern SIOPCB *sio_opn_por(ID siopid, intptr_t exinf);

/*
 *  ���ꥢ�륯����
 */
extern void sio_cls_por(SIOPCB *p_siopcb);

/*
 *  ����ߥϥ�ɥ�
 */
extern void sio_isr(intptr_t exinf);

/*
 *  1ʸ������
 */
extern bool_t sio_snd_chr(SIOPCB *siopcb, char_t c);

/*
 *  1ʸ������
 */
extern int_t sio_rcv_chr(SIOPCB *siopcb);

/*
 *  ������Хå��ε���
 */
extern void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn);

/* 
 *  ������Хå��ζػ�
 */
extern void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  ������ǽ������Хå�
 */
extern void sio_irdy_snd(intptr_t exinf);

/*
 *  �������Υ�����Хå�
 */
extern void sio_irdy_rcv(intptr_t exinf);

/*
 *  1ʸ�������ʥݡ���󥰤Ǥν��ϡ�
 */
extern void sio_pol_snd_chr(char_t c, ID siopid);

/*
 *  �������åȤΥ��ꥢ������
 */
extern void target_usart_init(ID siopid);

/*
 *  ���٥���Ͻ����
 */
extern void target_low_output_init(ID siopid);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_SERIAL_H */

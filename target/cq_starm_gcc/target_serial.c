/*
 *  TOPPERS/SSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by Meika Sugimoto
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
 * ���ꥢ��ɥ饤�С�CQ-STARM�ѡ�
 */

#include <kernel.h>
#include <sil.h>
#include "target_serial.h"
#include "target_syssvc.h"

/*
 * �쥸����������
 */
#define PORT2SIOPID(x)	((x) + 1)
#define INDEX_PORT(x)	((x) - 1)
#define GET_SIOPCB(x)	(&siopcb_table[INDEX_PORT(x)])

/*
 * USART�쥸�������
 */
#define USART_SR(x)		(x)
#define USART_DR(x)		(x + 0x04)
#define USART_BRR(x)	(x + 0x08)
#define USART_CR1(x)	(x + 0x0C)
#define USART_CR2(x)	(x + 0x10)
#define USART_CR3(x)	(x + 0x14)
#define USART_GTPR(x)	(x + 0x18)

#define SR_TXE			(0x0080)
#define SR_TC			(0x0040)
#define SR_RXNE			(0x0020)
#define SR_ORE			(0x0008)
#define SR_FE			(0x0002)
#define SR_PE			(0x0001)
#define CR1_UE			(0x2000)
#define CR1_TXEIE		(0x0080)
#define CR1_RXNEIE		(0x0020)
#define CR1_TE			(0x0008)
#define CR1_RE			(0x0004)
#define CR3_EIE			(0x0001)

/*
 * ���ꥢ��I/O�ݡ��ȴ����֥�å����ꥢ
 */
SIOPCB siopcb_table[TNUM_PORT];

static const uint32_t sioreg_table[TNUM_PORT] = {
	USART1_BASE,
#if (TNUM_PORT >= 2)
	USART2_BASE
#endif
};

Inline bool_t  sio_putready(SIOPCB* siopcb)
{
	return (sil_rew_mem((void*)USART_SR(siopcb->reg)) & SR_TXE) != 0;
}

Inline bool_t sio_getready(SIOPCB* siopcb)
{
	return (sil_rew_mem((void*)USART_SR(siopcb->reg)) & SR_RXNE) != 0;
}

/*
 *  ���٥���Ϥν����
 */

void target_low_output_init(ID siopid)
{
	uint32_t tmp, usartdiv, fraction;
	uint32_t reg = sioreg_table[INDEX_PORT(siopid)];
	uint32_t src_clock;
	
	/* ������Ѥߤξ��Ϥ����˥꥿���� */
	if((sil_rew_mem((void*)USART_CR1(reg)) & (CR1_RE | CR1_TE | CR1_UE))
		== (CR1_RE | CR1_TE | CR1_UE))
	{
		return ;
	}
	
	/* USART��̵���� */
	sil_andw((void*)USART_CR1(reg), ~CR1_UE);

	/* 1STOP BIT */
	sil_wrw_mem((void*)USART_CR2(reg), 0);

	/* 1START BIT, 8DATA bits, Parity�ʤ� */
	sil_wrw_mem((void*)USART_CR1(reg), 0);

	/* CR3����� */
	sil_wrw_mem((void*)USART_CR3(reg), 0);

	/* �̿�®������ */
	if (siopid == 1) {
		/* fck=72MHz */
		src_clock = PCLK2_CLOCK;
	} else {
		/* fck=36MHz */
		src_clock = PCLK1_CLOCK;
	}
	tmp = (1000 * (src_clock / 100)) / ((BPS_SETTING / 100) * 16);
	usartdiv = (tmp / 1000) << 4;
	fraction = tmp - ((usartdiv >> 4) * 1000);
	fraction = ((16 * fraction) + 500) / 1000;
	usartdiv |= (fraction & 0x0F);
	sil_wrw_mem((void*)USART_BRR(reg), usartdiv);
	
	/* USART��ͭ���� */
	sil_orw((void*)USART_CR1(reg), CR1_RE | CR1_TE);
	sil_orw((void*)USART_CR1(reg), CR1_UE);
}

/*
 *  �������åȤΥ��ꥢ������
 */
void target_usart_init(ID siopid)
{
	uint32_t reg = sioreg_table[INDEX_PORT(siopid)];
	
	target_low_output_init(siopid);
	
	/* ���顼����ߤ�ͭ���� */
	sil_orw((void*)USART_CR3(reg), CR3_EIE);
	
	/* ����ߵ��� */
	(void)ena_int(INTNO_SIO);
}

/*
 *  �������åȤΥ��ꥢ�뽪λ
 */
void target_usart_term(ID siopid)
{
	uint32_t reg = sioreg_table[INDEX_PORT(siopid)];
	
	/* USART��̵���� */
	sil_andw((void*)USART_CR1(reg),  ~CR1_UE);
}

/*
 *  SIO�����
 */
void sio_initialize(intptr_t exinf)
{
	int i;

	for (i = 0; i < TNUM_PORT; i++) {
		siopcb_table[i].port = i;
		siopcb_table[i].reg = sioreg_table[i];
		siopcb_table[i].exinf = 0;
	}
}

/*
 *  ���ꥢ�륪���ץ�
 */
SIOPCB *sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB* siopcb;

	if (siopid > TNUM_PORT) {
		return NULL;
	}
	
	siopcb = GET_SIOPCB(siopid);
	siopcb->exinf = exinf;

	target_usart_init(siopid);

	return siopcb;
}

/*
 *  ���ꥢ�륯����
 */
void sio_cls_por(SIOPCB *p_siopcb)
{
	target_usart_term(PORT2SIOPID(p_siopcb->port));
}

/*
 *  ����ߥϥ�ɥ�
 */
void sio_isr(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);

	if (sio_putready(siopcb)) {
		sio_irdy_snd(siopcb->exinf);
	}
	if (sio_getready(siopcb)) {
		sio_irdy_rcv(siopcb->exinf);
	}
}

/*
 *  1ʸ������
 */
bool_t sio_snd_chr(SIOPCB *siopcb, char_t c)
{
	if (sio_putready(siopcb)) {
		sil_wrw_mem((void*)USART_DR(siopcb->reg), c);

		return true;
	}

	return false;
}

/*
 *  1ʸ������
 */
int_t sio_rcv_chr(SIOPCB *siopcb)
{
	int_t c = -1;

	if (sio_getready(siopcb)) {
		c = sil_rew_mem((void*)USART_DR(siopcb->reg)) & 0xFF;
	}

	return c;
}

/*
 *  ������Хå��ε���
 */
void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		sil_orw((void*)USART_CR1(siopcb->reg), CR1_TXEIE);
		break;
	case SIO_RDY_RCV:
		sil_orw((void*)USART_CR1(siopcb->reg), CR1_RXNEIE);
		break;
	default:
		break;
	}
}

/* 
 *  ������Хå��ζػ�
 */
void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		sil_andw((void*)USART_CR1(siopcb->reg), ~CR1_TXEIE);
		break;
	case SIO_RDY_RCV:
		sil_andw((void*)USART_CR1(siopcb->reg), ~CR1_RXNEIE);
		break;
	default:
		break;
	}
}

/*
 *  1ʸ�����ϡʥݡ���󥰤Ǥν��ϡ�
 */
void sio_pol_snd_chr(char_t c, ID siopid)
{
	uint32_t reg = sioreg_table[INDEX_PORT(siopid)];

	sil_wrw_mem((void*)USART_DR(reg), c);

	while ((sil_rew_mem((void*)USART_SR(reg)) & SR_TXE) == 0)
		;
}

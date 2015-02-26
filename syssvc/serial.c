/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2008 by Embedded and Real-Time Systems Laboratory
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
 */

/*
 *		���ꥢ�륤�󥿥ե������ɥ饤��
 */

#include <kernel.h>
#include "target_syssvc.h"
#include "target_serial.h"
#include "serial.h"
#include "kernel_cfg.h"

/*
 *  �Хåե��������Υǥե�����ͤȥХåե������
 */
#ifndef SERIAL_RCV_BUFSZ1
#define	SERIAL_RCV_BUFSZ1	64			/* �ݡ���1�μ����Хåե������� */
#endif /* SERIAL_RCV_BUFSZ1 */

#ifndef SERIAL_SND_BUFSZ1
#define	SERIAL_SND_BUFSZ1	64			/* �ݡ���1�������Хåե������� */
#endif /* SERIAL_SND_BUFSZ1 */

static char_t	rcv_buffer1[SERIAL_RCV_BUFSZ1];
static char_t	snd_buffer1[SERIAL_SND_BUFSZ1];

#if TNUM_PORT >= 2						/* �ݡ���2�˴ؤ������ */

#ifndef SERIAL_RCV_BUFSZ2
#define	SERIAL_RCV_BUFSZ2	64			/* �ݡ���2�μ����Хåե������� */
#endif /* SERIAL_RCV_BUFSZ2 */

#ifndef SERIAL_SND_BUFSZ2
#define	SERIAL_SND_BUFSZ2	64			/* �ݡ���2�������Хåե������� */
#endif /* SERIAL_SND_BUFSZ2 */

static char_t	rcv_buffer2[SERIAL_RCV_BUFSZ2];
static char_t	snd_buffer2[SERIAL_SND_BUFSZ2];

#endif /* TNUM_PORT >= 2 */

#if TNUM_PORT >= 3						/* �ݡ���3�˴ؤ������ */

#ifndef SERIAL_RCV_BUFSZ3
#define	SERIAL_RCV_BUFSZ3	64			/* �ݡ���3�μ����Хåե������� */
#endif /* SERIAL_RCV_BUFSZ3 */

#ifndef SERIAL_SND_BUFSZ3
#define	SERIAL_SND_BUFSZ3	64			/* �ݡ���3�������Хåե������� */
#endif /* SERIAL_SND_BUFSZ3 */

static char_t	rcv_buffer3[SERIAL_RCV_BUFSZ3];
static char_t	snd_buffer3[SERIAL_SND_BUFSZ3];

#endif /* TNUM_PORT >= 3 */

/*
 *  ���ꥢ��ݡ��Ƚ�����֥�å�
 */
typedef struct serial_port_initialization_block {
	uint_t	rcv_bufsz;		/* �����Хåե������� */
	char_t	*rcv_buffer;	/* �����Хåե� */
	uint_t	snd_bufsz;		/* �����Хåե������� */
	char_t	*snd_buffer;	/* �����Хåե� */
} SPINIB;

static const SPINIB spinib_table[TNUM_PORT] = {
	{ SERIAL_RCV_BUFSZ1, rcv_buffer1,
	  SERIAL_SND_BUFSZ1, snd_buffer1 },
#if TNUM_PORT >= 2
	{ SERIAL_RCV_BUFSZ2, rcv_buffer2,
	  SERIAL_SND_BUFSZ2, snd_buffer2 },
#endif /* TNUM_PORT >= 2 */
#if TNUM_PORT >= 3
	{ SERIAL_RCV_BUFSZ3, rcv_buffer3,
	  SERIAL_SND_BUFSZ3, snd_buffer3 },
#endif /* TNUM_PORT >= 3 */
};

/*
 *  ���ꥢ��ݡ��ȴ����֥�å�
 */
typedef struct serial_port_control_block {
	const SPINIB *p_spinib;		/* ���ꥢ��ݡ��Ƚ�����֥�å� */
	SIOPCB	*p_siopcb;			/* ���ꥢ��I/O�ݡ��ȴ����֥�å� */
	bool_t	openflag;			/* �����ץ�Ѥߥե饰 */
	bool_t	errorflag;			/* ���顼�ե饰 */
	uint_t	ioctl;				/* ư������������� */

	uint_t	rcv_read_ptr;		/* �����Хåե��ɽФ��ݥ��� */
	uint_t	rcv_write_ptr;		/* �����Хåե�����ߥݥ��� */
	uint_t	rcv_count;			/* �����Хåե����ʸ���� */

	uint_t	snd_read_ptr;		/* �����Хåե��ɽФ��ݥ��� */
	uint_t	snd_write_ptr;		/* �����Хåե�����ߥݥ��� */
	uint_t	snd_count;			/* �����Хåե����ʸ���� */
} SPCB;

static SPCB	spcb_table[TNUM_PORT];

/*
 *  ���ꥢ��ݡ���ID���饷�ꥢ��ݡ��ȴ����֥�å�����Ф�����Υޥ���
 */
#define INDEX_PORT(portid)	((uint_t)((portid) - 1))
#define get_spcb(portid)	(&(spcb_table[INDEX_PORT(portid)]))

/*
 *  �ݥ��󥿤Υ��󥯥����
 */
#define INC_PTR(ptr, bufsz)		{ if (++(ptr) == (bufsz)) { (ptr) = 0; }}

/*
 *  �����ӥ�������ƽФ��ޥ���
 *
 *  �����ӥ�������ƽФ���ޤ༰exp��ɾ���������ͤ����顼������͡ˤξ�
 *  ��ˤϡ�erc��ercd_exp��ɾ�������ͤ���������error_exit��goto���롥
 */
#define SVC(exp, ercd_exp) \
				{ if ((exp) < 0) { ercd = (ercd_exp); goto error_exit; }}

/*
 *  E_SYS���顼������
 */
static ER
gen_ercd_sys(SPCB *p_spcb)
{
	p_spcb->errorflag = true;
	return(E_SYS);
}


/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фν�����롼����
 */
void
serial_initialize(intptr_t exinf)
{
	uint_t	i;
	SPCB	*p_spcb;

	for (p_spcb = spcb_table, i = 0; i < TNUM_PORT; p_spcb++, i++) {
		p_spcb->p_spinib = &(spinib_table[i]);
		p_spcb->openflag = false;
	}
}

/*
 *  ���ꥢ�륤�󥿡��ե������ɥ饤�Фν�λ�롼����
 */

void
serial_terminate(intptr_t exinf)
{
	uint_t	i;
	SPCB	*p_spcb;
	
	/* �Хåե��˻ĤäƤ������Ƥ�ʸ������Ϥ��� */
	for (p_spcb = spcb_table, i = 0; i < TNUM_PORT; p_spcb++, i++) {
		while(p_spcb->snd_count != 0)
		{
			if(sio_snd_chr(p_spcb->p_siopcb,
					p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr]) == true)
			{
				INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
				p_spcb->snd_count--;
			}
		}
	}

}

/*
 *  ���ꥢ��ݡ��ȤΥ����ץ�ʥ����ӥ��������
 */
ER
serial_opn_por(ID portid)
{
	SPCB	*p_spcb;
	ER		ercd;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}
	p_spcb = get_spcb(portid);

	SVC(dis_dsp(), gen_ercd_sys(p_spcb));
	if (p_spcb->openflag) {			/* �����ץ�Ѥߤ��Υ����å� */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  �ѿ��ν����
		 */
		p_spcb->ioctl = (IOCTL_ECHO | IOCTL_CRLF);

		p_spcb->rcv_read_ptr = p_spcb->rcv_write_ptr = 0U;
		p_spcb->rcv_count = 0U;

		p_spcb->snd_read_ptr = p_spcb->snd_write_ptr = 0U;
		p_spcb->snd_count = 0U;

		/*
		 *  ����ʹߡ�����ߤ�ػߤ��롥
		 */
		if (loc_cpu() < 0) {
			ercd = E_SYS;
			goto error_exit_enadsp;
		}

		/*
		 *  �ϡ��ɥ�������¸�Υ����ץ����
		 */
		p_spcb->p_siopcb = sio_opn_por(portid, (intptr_t) p_spcb);

		/*
		 *  �������Υ�����Хå�����Ĥ��롥
		 */
		sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_RCV);
		p_spcb->openflag = true;
		p_spcb->errorflag = false;

		if (unl_cpu() < 0) {
			p_spcb->errorflag = true;
			ercd = E_SYS;
			goto error_exit_enadsp;
		}
		ercd = E_OK;
	}

  error_exit_enadsp:
	SVC(ena_dsp(), gen_ercd_sys(p_spcb));

  error_exit:
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��ȤΥ������ʥ����ӥ��������
 */
ER
serial_cls_por(ID portid)
{
	SPCB	*p_spcb;
	ER		ercd;
	bool_t	eflag = false;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}
	p_spcb = get_spcb(portid);

	SVC(dis_dsp(), gen_ercd_sys(p_spcb));
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  �ϡ��ɥ�������¸�Υ���������
		 */
		if (loc_cpu() < 0) {
			eflag = true;
		}
		sio_cls_por(p_spcb->p_siopcb);
		p_spcb->openflag = false;
		if (unl_cpu() < 0) {
			eflag = true;
		}
		
		/*
		 *  ���顼�����ɤ�����
		 */
		if (eflag) {
			ercd = gen_ercd_sys(p_spcb);
		}
		else {
			ercd = E_OK;
		}
	}
	SVC(ena_dsp(), gen_ercd_sys(p_spcb));

  error_exit:
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�ʸ������
 *
 *  p_spcb�ǻ��ꤵ��륷�ꥢ��I/O�ݡ��Ȥ��Ф��ơ�ʸ��c���������롥ʸ��
 *  �������쥸�����ˤ��줿���ˤ�true���֤��������Ǥʤ����ˤϡ�����
 *  �쥸���������������Ȥ����Τ��륳����Хå��ؿ�����Ĥ���false���֤���
 *  ���δؿ��ϡ�CPU��å����֤ǸƤӽФ���롥
 */
Inline bool_t
serial_snd_chr(SPCB *p_spcb, char_t c)
{
	if (sio_snd_chr(p_spcb->p_siopcb, c)) {
		return(true);
	}
	else {
		sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
		return(false);
	}
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�1ʸ������
 */
static ER_BOOL
serial_wri_chr(SPCB *p_spcb, char_t c)
{
	bool_t	buffer_full;
	ER		ercd, rercd;

	/*
	 *  LF������CR���������롥
	 */
	if (c == '\n' && (p_spcb->ioctl & IOCTL_CRLF) != 0U) {
		SVC(rercd = serial_wri_chr(p_spcb, '\r'), rercd);
	}

	SVC(loc_cpu(), gen_ercd_sys(p_spcb));
	if ((p_spcb->snd_count == 0U) && serial_snd_chr(p_spcb, c)) {
		/*
		 *  ���ꥢ��I/O�ǥХ����������쥸������ʸ��������뤳�Ȥ�������
		 *  ����硥
		 */
		buffer_full = false;
	}
	else {
		/*
		 *  �����Хåե���ʸ��������롥
		 */
		p_spcb->p_spinib->snd_buffer[p_spcb->snd_write_ptr] = c;
		INC_PTR(p_spcb->snd_write_ptr, p_spcb->p_spinib->snd_bufsz);
		p_spcb->snd_count++;
		buffer_full = (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz);
	}

	SVC(unl_cpu(), gen_ercd_sys(p_spcb));
	ercd = (ER_BOOL) buffer_full;

  error_exit:
	return(ercd);
}

bool_t
serial_sndbuf_full(SPCB *p_spcb)
{
	return (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz);
}

bool_t
serial_rcvbuf_empty(SPCB *p_spcb)
{
	return (p_spcb->rcv_count == 0u);
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�ʸ���������ʥ����ӥ��������
 */
ER_UINT
serial_wri_dat(ID portid, const char_t *buf, uint_t len)
{
	SPCB	*p_spcb;
	uint_t	wricnt = 0U;
	ER		ercd, rercd;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* ���顼���֤��Υ����å� */
		return(E_SYS);
	}
	
	SVC((rercd = loc_cpu()) , rercd);
	if(!serial_sndbuf_full(p_spcb))
	{
		while(wricnt < len)
		{
			SVC(rercd = serial_wri_chr(p_spcb, *buf++), rercd);
			wricnt++;
		}
	}
	SVC((rercd = unl_cpu()) , rercd);
	
  error_exit:
	return(wricnt > 0U ? (ER_UINT) wricnt : rercd);
}

/*
 *  ���ꥢ��ݡ��Ȥ����1ʸ������
 */
static bool_t
serial_rea_chr(SPCB *p_spcb, char_t *p_c)
{
	bool_t	buffer_empty;
	ER		ercd;

	SVC(loc_cpu(), gen_ercd_sys(p_spcb));

	/*
	 *  �����Хåե�����ʸ������Ф���
	 */
	*p_c = p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_read_ptr];
	INC_PTR(p_spcb->rcv_read_ptr, p_spcb->p_spinib->rcv_bufsz);
	p_spcb->rcv_count--;
	buffer_empty = (p_spcb->rcv_count == 0U);
	
	SVC(unl_cpu(), gen_ercd_sys(p_spcb));
	ercd = (ER_BOOL) buffer_empty;

  error_exit:
	return(ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥ����ʸ��������ʥ����ӥ��������
 */
ER_UINT
serial_rea_dat(ID portid, char_t *buf, uint_t len)
{
	SPCB	*p_spcb;
	uint_t	reacnt = 0U;
	char_t	c = '\0';		/* ����ѥ���ηٹ���޻ߤ��뤿��˽�������� */
	ER		ercd, rercd;
	bool_t	buffer_empty;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* ���顼���֤��Υ����å� */
		return(E_SYS);
	}
	
	buffer_empty = false;
	if(p_spcb->rcv_count >= len) {
		
		while(reacnt < len)
		{
			(void)serial_rea_chr(p_spcb, &c);
			/*
			 *  �������Хå�������
			 */
			if ((p_spcb->ioctl & IOCTL_ECHO) != 0U) {
				SVC(rercd = serial_wri_chr(p_spcb, c), rercd);
			}
			*buf++ = c;
			reacnt++;
		}
	}
	
	ercd = reacnt;
  error_exit:
	return(reacnt > 0U ? (ER_UINT) reacnt : ercd);
}

/*
 *  ���ꥢ��ݡ��Ȥ�����ʥ����ӥ��������
 */
ER
serial_ctl_por(ID portid, uint_t ioctl)
{
	SPCB	*p_spcb;

	if (sns_dpn()) {				/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �ݡ����ֹ�Υ����å� */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �����ץ�Ѥߤ��Υ����å� */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* ���顼���֤��Υ����å� */
		return(E_SYS);
	}

	p_spcb->ioctl = ioctl;
	return(E_OK);
}

/*
 *  ���ꥢ��ݡ��Ȥ����������ǽ������Хå�
 */
void
sio_irdy_snd(intptr_t exinf)
{
	SPCB	*p_spcb;

	p_spcb = (SPCB *) exinf;

	if (p_spcb->snd_count > 0U) {
		/*
		 *  �����Хåե��椫��ʸ������Ф����������롥
		 */
		(void) sio_snd_chr(p_spcb->p_siopcb,
					p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr]);
		INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
		p_spcb->snd_count--;
	}
	else {
		/*
		 *  �������٤�ʸ�����ʤ����ϡ�������ǽ������Хå���ػߤ��롥
		 */
		sio_dis_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
	}
}

/*
 *  ���ꥢ��ݡ��Ȥ���μ������Υ�����Хå�
 */
void
sio_irdy_rcv(intptr_t exinf)
{
	SPCB	*p_spcb;
	char_t	c;
	
	p_spcb = (SPCB *) exinf;
	c = (char_t) sio_rcv_chr(p_spcb->p_siopcb);
	
	if (p_spcb->rcv_count != p_spcb->p_spinib->rcv_bufsz) {
		/*
		 *  ��������ʸ��������Хåե�������롥
		 *  �Хåե��ե�ξ�硤��������ʸ����ΤƤ롥
		 */
		p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_write_ptr] = c;
		INC_PTR(p_spcb->rcv_write_ptr, p_spcb->p_spinib->rcv_bufsz);
		p_spcb->rcv_count++;
	}
}

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф����̤����ʸ���μ�Ф�
 */
bool_t
serial_get_chr(ID portid, char_t *p_c)
{
	SPCB	*p_spcb;

	if (1 <= portid && portid <= TNUM_PORT) {	/* �ݡ����ֹ�Υ����å� */
		p_spcb = get_spcb(portid);
		if (p_spcb->openflag) {					/* �����ץ�Ѥߤ��Υ����å� */
			if (p_spcb->snd_count > 0U) {
				*p_c = p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr];
				INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
				p_spcb->snd_count--;
				return(true);
			}
		}
	}
	return(false);
}

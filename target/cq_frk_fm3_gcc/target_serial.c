/*
 *  TOPPERS/SSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2012 by Meika Sugimoto
 * 
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 * �V���A���h���C�o�iCQ-FRM-FM3�p�j
 */

#include <sil.h>
#include "kernel_int.h"
#include "target_serial.h"
#include "target_syssvc.h"

/*
 * ���W�X�^�ݒ�l
 */
#define PORT2SIOPID(x)	((x) + 1)
#define INDEX_PORT(x)	((x) - 1)
#define GET_SIOPCB(x)	(&siopcb_table[INDEX_PORT(x)])

/*
 * USART���W�X�^��`
 *  #define MFS_SMR(ch)				(MFS_BASEADDR((ch)) + 0x00)
 *  #define MFS_SCR(ch)				(MFS_BASEADDR((ch)) + 0x01)
 *  #define MFS_ESCR(ch)			(MFS_BASEADDR((ch)) + 0x04)
 *  #define MFS_SSR(ch)				(MFS_BASEADDR((ch)) + 0x05)
 *  #define MFS_RDRTDR(ch)			(MFS_BASEADDR((ch)) + 0x08)
 *  #define MFS_BGR0(ch)			(MFS_BASEADDR((ch)) + 0x0B)
 *  #define MFS_BGR1(ch)			(MFS_BASEADDR((ch)) + 0x0C)
 *
 */

/*
 *  �r�b�g���蓖�Ă̓o�C�g�A�N�Z�X�p�ɋL�q���Ă���
 */

/* SCR */
#define SCR_UPCL					(1U << 7)
#define SCR_RIE						(1U << 4)
#define SCR_TIE						(1U << 3)
#define SCR_TEIE					(1U << 2)
#define SCR_RXE						(1U << 1)
#define SCR_TXE						(1U << 0)

/* SMR */
#define SMR_MODE_ASYNC_NORMAL		(0U << 5)
#define SMR_MODE_ASYNC_MULTI		(1U << 5)
#define SMR_MODE_CLKSYNC			(2U << 5)
#define SMR_MODE_LIN				(3U << 5)
#define SMR_MODE_I2C				(4U << 5)

#define SMR_WAKEUP					(1U << 4)

#define SMR_SBL_1OR3				(0U << 3)	/* ESCR.ESBL = 0��1 */
#define SMR_SBL_2OR4				(1U << 3)	/* ESCR.ESBL = 0��2 */

#define SMR_BDS_LSBFIRST			(0U << 2)
#define SMR_BDS_MSBFIRST			(1U << 2)

#define SMR_SOE_DISABLE				(0U << 0)
#define SMR_SOE_ENABLE				(1U << 0)

/* SSR */
#define SSR_REC						(1U << 7)
#define SSR_PE						(1U << 5)
#define SSR_FRE						(1U << 4)
#define SSR_ORE						(1U << 3)
#define SSR_RDRF					(1U << 2)
#define SSR_TDRE					(1U << 1)
#define SSR_TBI						(1U << 0)

/* ESCR */
#define ESCR_FLWEN_ENABLE			(1U << 7)
#define ESCR_FLWEN_DISABLE			(0U << 7)
#define ESCR_ESBL					(1U << 6)
#define ESCR_INV_NRZ				(0U << 5)
#define ESCR_INV_INVNRZ				(1U << 5)
#define ESCR_PEN					(1U << 4)
#define ESCR_PEN_DISABLE			(0U << 4)
#define ESCR_PEN_ENABLE				(1U << 4)
#define ESCR_P_EVEN					(0U << 3)
#define ESCR_P_ODD					(1U << 3)
#define ESCR_DATALEN_8				(0U << 0)
#define ESCR_DATALEN_5				(1U << 0)
#define ESCR_DATALEN_6				(2U << 0)
#define ESCR_DATALEN_7				(3U << 0)
#define ESCR_DATALEN_9				(4U << 0)


/*
 * �V���A��I/O�|�[�g�Ǘ��u���b�N�G���A
 */
SIOPCB siopcb_table[TNUM_PORT];

static const uint32_t sioreg_table[TNUM_PORT] = {
	MFS_BASEADDR(0),
#if (TNUM_PORT >= 2)
	MFS_BASEADDR(4)
#endif
};

Inline bool_t  sio_putready(SIOPCB* siopcb)
{
	return ((sil_reb_mem((void*)MFS_SSR(siopcb->port)) & SSR_TDRE) != 0);
}

Inline bool_t sio_getready(SIOPCB* siopcb)
{
	return ((sil_reb_mem((void*)MFS_SSR(siopcb->port)) & SSR_RDRF) != 0);
}

/*
 *  �჌�x���o�͂̏�����
 */

void target_low_output_init(ID siopid)
{
	uint32_t ch = INDEX_PORT(siopid);
	
	/* �������ς݂̏ꍇ�͂����Ƀ��^�[�� */
	if((sil_reb_mem((void*)MFS_SCR(ch)) & (SCR_TXE | SCR_RXE)) != 0)
	{
		return ;
	}
	
	/* USART�̖������C���Z�b�g */
	sil_wrb_mem((void *)MFS_SCR(ch) , SCR_UPCL);
	sil_wrb_mem((void *)MFS_SCR(ch) , 0x0);
	
	/* �ʐM���[�h�ݒ� */
	sil_wrb_mem((void *)MFS_SMR(ch) , 
			(SMR_MODE_ASYNC_NORMAL | SMR_SBL_1OR3 | SMR_BDS_LSBFIRST | SMR_SOE_DISABLE));
	sil_wrb_mem((void *)MFS_ESCR(ch) ,
			(ESCR_FLWEN_DISABLE | ESCR_INV_NRZ | ESCR_PEN_DISABLE | ESCR_DATALEN_8));
	/* �ʐM���x�ݒ� */
	sil_wrh_mem((void *)MFS_BGR0(ch) , BPS_SETTING);	/* �n�[�t���[�h�A�N�Z�X���� */
	/* FIFO������ */
	sil_wrb_mem((void *)MFS_FCR0(ch) , 0x00);
	sil_wrb_mem((void *)MFS_FCR1(ch) , 0x00);
	
	/* USART�̗L���� */
	sil_orb((void *)MFS_SMR(ch) , SMR_SOE_ENABLE);
	sil_orb((void*)MFS_SCR(ch) , (SCR_TXE | SCR_RXE));
}

/*
 *  �^�[�Q�b�g�̃V���A��������
 */
void target_usart_init(ID siopid)
{
	target_low_output_init(siopid);
	
	/* �����݋��� */
	x_clear_int(INTNO_SIO_TX);
	x_clear_int(INTNO_SIO_RX);
	/* �����݋֎~ */
	(void)ena_int(INTNO_SIO_TX);
	(void)ena_int(INTNO_SIO_RX);
}

/*
 *  �^�[�Q�b�g�̃V���A���I��
 */
void target_usart_term(ID siopid)
{
	/* �����݋֎~ */
	(void)dis_int(INTNO_SIO_TX);
	(void)dis_int(INTNO_SIO_RX);
	
	/* USART�̖����� */
	sil_andb((void*)MFS_SCR(INDEX_PORT(siopid)) , (SCR_TXE | SCR_RIE));
}

/*
 *  SIO������
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
 *  �V���A���I�[�v��
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
 *  �V���A���N���[�Y
 */
void sio_cls_por(SIOPCB *p_siopcb)
{
	target_usart_term(p_siopcb->port);
}

/*
 *  �����݃n���h��
 */
void sio_isr_tx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);

	if (sio_putready(siopcb)) {
		sio_irdy_snd(siopcb->exinf);
	}
}

void sio_isr_rx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);

	if (sio_getready(siopcb)) {
		sio_irdy_rcv(siopcb->exinf);
	}
}

/*
 *  1�������M
 */
bool_t sio_snd_chr(SIOPCB *siopcb, char_t c)
{
	bool_t ret = false;
	
	if (sio_putready(siopcb)) {
		sil_wrb_mem((void*)MFS_RDRTDR(siopcb->port), c);
		
		ret = true;
	}

	return ret;
}

/*
 *  1������M
 */
int_t sio_rcv_chr(SIOPCB *siopcb)
{
	int_t c = -1;

	if (sio_getready(siopcb)) {
		c = (int)sil_reb_mem((void*)MFS_RDRTDR(siopcb->port));
	}

	return c;
}

/*
 *  �R�[���o�b�N�̋���
 */
void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		sil_orb((void*)MFS_SCR(siopcb->port), SCR_TIE);
		break;
	case SIO_RDY_RCV:
		sil_orb((void*)MFS_SCR(siopcb->port), SCR_RIE);
		break;
	default:
		break;
	}
}

/* 
 *  �R�[���o�b�N�̋֎~
 */
void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		sil_andb((void*)MFS_SCR(siopcb->port), ~SCR_TIE);
		break;
	case SIO_RDY_RCV:
		sil_andb((void*)MFS_SCR(siopcb->port), ~SCR_RIE);
		break;
	default:
		break;
	}
}

/*
 *  1�����o�́i�|�[�����O�ł̏o�́j
 */
void sio_pol_snd_chr(char_t c, ID siopid)
{
	sil_wrb_mem((void*)MFS_RDRTDR(INDEX_PORT(siopid)), (int)c);
	
	while ((sil_reb_mem((void*)MFS_SSR(INDEX_PORT(siopid))) & SSR_TDRE) == 0U)
		;
}

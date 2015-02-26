/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 * �^�[�Q�b�g�ˑ����@�A�Z���u������iCQ-FRM-FM3�p�j
 */

#define TOPPERS_MACRO_ONLY
#define UINT_C(val)			(val)
#define ULONG_C(val)		(val)
#include "kernel_impl.h"
#include "cq_frm_fm3.h"

/*
 * �჌�x���̃^�[�Q�b�g�ˑ��̏�����
 *
 * �������������̑O�ɌĂяo�����
 */

	.globl	hardware_init_hook

	.text
	.align 2
	.syntax unified
	.code 16
	.thumb
	
hardware_init_hook:
	/* �e�o�X�N���b�N�̃v���X�P�[���ݒ� */
	ldr	r0 , =#BSC_PSR					/* �x�[�X�N���b�N(1����) */
	mov	r1 , #BSC_CLK_DIV_1
	str	r1 , [r0]
	
	ldr	r0 , =#APBC0_PSR				/* APB0(8����) */
	mov	r1 , #APB_CLK_DIV_8
	str	r1 , [r0]
	
	ldr	r0 , =#APBC1_PSR				/* APB1(8����) */
	mov	r1 , #(APB_CLK_DIV_8 | APBC_EN | APBC_RESET)
	str	r1 , [r0]
	mov	r1 , #(APB_CLK_DIV_8 | APBC_EN)
	str	r1 , [r0]
	
	ldr	r0 , =#APBC2_PSR				/* APB2(8����) */
	mov	r1 , #(APB_CLK_DIV_8 | APBC_EN | APBC_RESET)
	str	r1 , [r0]
	mov	r1 , #(APB_CLK_DIV_8 | APBC_EN)
	str	r1 , [r0]
	
	ldr	r0 , =#INT_CLR		/* INT_CLR�̃N���A */
	mov	r1 , #(INT_CLL_MCS | INT_CLL_SCS | INT_CLL_PCS | INT_CLL_FCS)
	str	r1 , [r0]
	
	/* ���C���N���b�N���M����҂������݂̐ݒ� */
	ldr	r0 , =#CSW_PSR
	mov	r1 , #PSW_TMR_MOWT_CONF12
	str	r1 , [r0]
	
	/* ���C���N���b�N���͈���҂������ݗL���� */
	ldr	r0 , =#INT_ENR
	mov	r1 , #INT_CLL_MCS
	str	r1 , [r0]
	
	/* ���C���N���b�N�N�� */
	ldr	r0 , =#SCM_CTL
	ldr	r1 , [r0]
	and r1 , #SCM_CTL_MOSCE
	str	r1 , [r0]
	
	/* ���C���N���b�N����҂� */
	ldr	r0 , =#SCM_STR
  wait_main_clock_stable:
	ldr	r1 , [r0]
	orr	r1 , #SCM_STR_MORDY
	beq wait_main_clock_stable
	
	/* PLL���̓N���b�N�Ɣ��M����҂������݂̐ݒ� */
	ldr	r0 , =#PSW_TMR
	mov	r1 , #(PSW_TMR_PINC_MO | PSW_TMR_POWT_CONF7)	/* �҂����Ԃ͍ő�l��� */
	str	r1 , [r0]
	
	/* PLL���͈���҂������ݗL���� */
	ldr	r0 , =#INT_ENR
	mov	r1 , #INT_CLL_PCS
	str	r1 , [r0]
	
	/* PLL�̕������ݒ� */
	ldr	r0 , =#PLL_CTL1		/* PLLK , PLLM */
	mov	r1 , #(PLL_CTL1_PLLK(PLLK_VALUE) | PLL_CTL1_PLLM(PLLM_VALUE))
	str	r1 , [r0]
	ldr	r0 , =#PLL_CTL2		/* PLLN */
	mov	r1 , #PLL_CTL2_PLLN(PLLN_VALUE)
	str	r1 , [r0]
	
	/* PLL�N�� */
	ldr	r0 , =#SCM_CTL
	ldr	r1 , [r0]
	orr r1 , #SCM_CTL_PLLE
	str	r1 , [r0]
	
	/* PLL����҂� */
	ldr	r0 , =#SCM_STR		/* APB2(8����) */
  wait_pll_stable:
	ldr	r1 , [r0]
	and	r1 , #SCM_STR_PLRDY
	beq wait_pll_stable

	/* �}�X�^�N���b�N�؂�ւ� */
	ldr	r0 , =#SCM_CTL
	ldr	r1 , [r0]
	and r1 , #~SCM_CTL_RCS_MASK
	orr r1 , #SCM_CTL_RCS_PLLCLK
	str	r1 , [r0]
	
	isb
	
	/* �g���[�X�N���b�N�̐ݒ� */
	ldr	r0 , =#TTC_PSR				/* TTC(8����) */
	mov	r1 , #(APB_CLK_DIV_8)
	str	r1 , [r0]
	
	/* �g���[�X�|�[�g�̐ݒ� */
	ldr	r0 , =#PFR0
	ldr	r1 , [r0]
	orr r1 , #(0x01F << 5)
	str	r1 , [r0]
	
	ldr	r0 , =#EPFR0
	ldr	r1 , [r0]
	orr r1 , #(0x03 << 24)
	str	r1 , [r0]
	
	bx	lr

/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2012 Meika Sugimoto
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
 * �^�[�Q�b�g�ˑ����W���[��(CQ-FRM-FM3�p)
 */
#include "kernel_impl.h"
#include <sil.h>
#include "target_serial.h"
#include "target_syssvc.h"

/*
 * �^�[�Q�b�g�V�X�e���̃n�[�h�E�F�A�����̒�`
 */
#include "cq_frm_fm3.h"


/*
 * �^�[�Q�b�g�ˑ����@����������
 */
void target_initialize(void)
{
	/*
	 *  �v���Z�b�T�ˑ����̏�����
	 */
	prc_initialize();

	/*
	 *  �y���t�F�����̐ݒ�
	 */
	
	/*
	 *  �n�[�h�E�F�AWDT������
	 */
	sil_wrw_mem((void *)WDG_LCK , WDG_UNLOCK_VAL);
	sil_wrw_mem((void *)WDG_LCK , ~WDG_UNLOCK_VAL);
	sil_wrw_mem((void *)WDG_CTL , (WDG_RESDIS | WDG_RESINTDIS));
	
	/*
	 *  I/O�|�[�g�̏�����
	 */
#if (SIO_PORTID == 1)
	/* PFR�̐ݒ� */
	
	/* MFS(RX,TX) CH0 */
	sil_andw((void *)EPFR7 , ~(0x03 << 2));	/* SIN0_0 , SOT0_0���g�p */
	sil_orw((void *)EPFR7 , (0x01 << 6));	/* SIN0_0 , SOT0_0���g�p */
	
	/* P21(SIN),P22(SOT) */
	sil_orw((void *)PFR2 , (1 << 1) | (1 << 2));
	sil_andw((void *)ADE , ~(1 << 31));

#elif (SIO_PORTID == 2)
	/* USART2(RX,TX) CH2 */
	sil_andw((void *)EPFR8 , ~(0x03 << 6));	/* SIN4_2���g�p */
	sil_orw((void *)EPFR8 , (0x03 << 6));	/* SIN4_2 , SOT4_2���g�p */
	
	/* PD2(SIN),PD3(SOT) */
	sil_orw((void *)PFR0 , (1 << 5) | (1 << 6));
	
#endif

	/*
	 *  �o�i�[�o�͗p�̃V���A��������
	 */
	
	target_low_output_init(SIO_PORTID);
	sil_dly_nse(10 * 1000 * 1000);
	
	/* LED�|�[�g */
	sil_andw((void *)PFRF , ~BITMAP_3);
	sil_orw((void *)PDDRF , BITMAP_3);
	sil_andw((void *)PDORF , ~BITMAP_3);
	
}

/*
 * �^�[�Q�b�g�ˑ��� �I������
 */
void target_exit(void)
{
	/* �v���Z�b�T�ˑ����̏I������ */
	prc_terminate();
}

/*
 * �V�X�e�����O�̒჌�x���o�͂̂��߂̕����o��
 */
void target_fput_log(char_t c)
{
	if (c == '\n') {
		sio_pol_snd_chr('\r', SIO_PORTID);
	}
	sio_pol_snd_chr(c, SIO_PORTID);
}



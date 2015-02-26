/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2012 Meika Sugimoto
 * 
 *  ��L���쌠�҂́CFree Software Foundation �ɂ���Č��\����Ă��� 
 *  GNU General Public License �� Version 2 �ɋL�q����Ă���������C��
 *  ����(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F
 *  �A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���ė��p�\�ȃo�C�i���R�[�h�i�����P�[�^�u���I�u
 *      �W�F�N�g�t�@�C���⃉�C�u�����Ȃǁj�̌`�ŗ��p����ꍇ�ɂ́C���p
 *      �ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C
 *      ���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���ė��p�s�\�ȃo�C�i���R�[�h�̌`�܂��͋@��ɑg
 *      �ݍ��񂾌`�ŗ��p����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂������ƁD
 *    (a) ���p�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒���
 *        ���\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) ���p�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āC��L���쌠�҂ɕ񍐂���
 *        ���ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂�Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂́C
 *  �{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\�����܂߂āC�����Ȃ�ۏ؂��s��
 *  �Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ�������
 *  ���Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *  �^�[�Q�b�g�{�[�h�Ɋւ����`(CQ-FRM-FM3�p)
 */

#ifndef TOPPERS_CQ_FRM_FM3_H
#define TOPPERS_CQ_FRM_FM3_H

#include <sil.h>

#include "MB9BF618T.h"

/*
 *  �O���I�V���[�^�N���b�N�̒�`
 */

#define OSC_CLOCK		(4 * 1000 * 1000)	/* 4MHz */

/*
 *  �O���I�V���[�^�����ɐ�������V�X�e���N���b�N�֘A�̒�`
 */

/* PLL�N���b�N */
#define PLLK_VALUE	(1)
#define PLLN_VALUE	(36)
#define PLLM_VALUE	(2)

/* (((OSC_CLOCK / PLLK) * PLLN) * PLLM) / PLLM = OSC_CLOCK / PLLK * PLLN */
#define PLL_CLOCK		(144 * 1000 * 1000)

#define BASE_CLOCK		(PLL_CLOCK)
#define PCLK0_CLOCK		(PLL_CLOCK / 8)	/* 18MHz */
#define PCLK1_CLOCK		(PLL_CLOCK / 8)	/* 18MHz */
#define PCLK2_CLOCK		(PLL_CLOCK / 8)	/* 18MHz */

#define SYSTIC_CLOCK	(PLL_CLOCK)	/* 18MHz */

/* �V���A���ʐM�{�[���[�g�ݒ�(�o�X�N���b�N18MHz�̏ꍇ�̐ݒ�) */
#define BGR_VALUE_115200BPS		(155)
#define BGR_VALUE_57600BPS		(311)
#define BGR_VALUE_38400BPS		(467)
#define BGR_VALUE_9600BPS		(1874)


#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_CQ_FRM_FM3_H */

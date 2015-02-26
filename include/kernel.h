/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2010-2012 by Meika Sugimoto
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
 *		TOPPERS/SSP�����ͥ� ɸ��إå��ե�����
 *
 *  TOPPERS/SSP�����ͥ뤬���ݡ��Ȥ��륵���ӥ������������ȡ�ɬ�פʥǡ�
 *  ������������ޥ���������ޤ�إå��ե����롥
 *
 *  ������֥����Υ������ե����뤫�餳�Υե�����򥤥󥯥롼�ɤ����
 *  �ϡ�TOPPERS_MACRO_ONLY��������Ƥ���������ˤ�ꡤ�ޥ�������ʳ���
 *  �����褦�ˤʤäƤ��롥
 *
 *  ���Υե�����򥤥󥯥롼�ɤ������˥��󥯥롼�ɤ��Ƥ����٤��ե�����
 *  �Ϥʤ���
 */

#ifndef TOPPERS_KERNEL_H
#define TOPPERS_KERNEL_H

/*
 *	TOPPERS���̤Υǡ�������������ޥ���
 */
#include <t_stddef.h>

/*
 *  �������åȰ�¸��
 */
#include "target_kernel.h"
#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ǡ����������
 */

/*
 *  �ӥåȥѥ�����䥪�֥��������ֹ�η����
 */
typedef	uint_t			INTNO;		/* ������ֹ� */
typedef	uint_t			INHNO;		/* ����ߥϥ�ɥ��ֹ� */
typedef	uint_t			EXCNO;		/* CPU�㳰�ϥ�ɥ��ֹ� */


/*
 *  ����ñ�̤η����
 */
typedef void	(*TASK)(intptr_t exinf);
typedef void	(*ISR)(intptr_t exinf);
typedef void	(*INTHDR)(void);
typedef void	(*EXCHDR)(void *p_excinf);
typedef void	(*INIRTN)(intptr_t exinf);
typedef void	(*TERRTN)(intptr_t exinf);
typedef void	(*CYCHDR)(intptr_t exinf);
typedef void	(*ALMHDR)(intptr_t exinf);

/*
 *  �����ΰ���ݤΤ���η����
 */
#ifndef TOPPERS_STK_T
#define TOPPERS_STK_T	intptr_t
#endif /* TOPPERS_STK_T */
typedef	TOPPERS_STK_T	STK_T;	/* �����å��ΰ����ݤ��뤿��η� */


/*
 *  �����ӥ�����������
 */

/*
 *  ������������ǽ
 */
extern ER		act_tsk(ID tskid);
extern ER		iact_tsk(ID tskid);

/*
 *  �����ƥ���ִ�����ǽ
 */
extern ER		loc_cpu(void);
extern ER		iloc_cpu(void);
extern ER		unl_cpu(void);
extern ER		iunl_cpu(void);
extern ER		dis_dsp(void);
extern ER		ena_dsp(void);
extern bool_t	sns_ctx(void);
extern bool_t	sns_loc(void);
extern bool_t	sns_dsp(void);
extern bool_t	sns_dpn(void);
extern bool_t	sns_ker(void);
extern ER		ext_ker(void);

/*
 *  ����ߴ�����ǽ
 */
extern ER		dis_int(INTNO intno);
extern ER		ena_int(INTNO intno);

/*
 *  �����ϥ�ɥ鵡ǽ
 */
extern ER		sta_cyc(ID cycid);
extern ER		stp_cyc(ID cycid);

/*
 *  ���顼��ϥ�ɥ鵡ǽ
 */
extern ER		sta_alm(ID almid , RELTIM almtim);
extern ER		stp_alm(ID almid);

/*
 *  �����ƥ���������ǽ
 */
extern ER		get_tim(SYSTIM *p_systim);

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ���֥�������°�������
 */
#define TA_RSTR			UINT_C(0x04)	/* ���󥿥��� */

#define TA_ACT			UINT_C(0x02)	/* ��������ư���줿���֤����� */

#define TA_STA			UINT_C(0x02)	/* �����ϥ�ɥ��ư����֤����� */

#define TA_NONKERNEL	UINT_C(0x02)	/* �����ͥ�������γ���� */

#define TA_ENAINT		UINT_C(0x01)	/* ������׵�ػߥե饰�򥯥ꥢ */
#define TA_EDGE			UINT_C(0x02)	/* ���å��ȥꥬ */

/*
 *  ����¾����������
 */
#define TSK_SELF		0			/* ������������ */
#define TSK_NONE		0			/* �������륿�������ʤ� */

#define TPRI_INI		0			/* �������ε�ư��ͥ���� */

#define TIPM_ENAALL		0			/* �����ͥ���٥ޥ�������� */

/*
 *  ��������ȥޥ���
 */

/*
 *  ͥ���٤��ϰ�
 */
#define TMIN_TPRI		1			/* ������ͥ���٤κǾ��͡ʺǹ��͡�*/
#ifndef TMAX_TPRI
	#define TMAX_TPRI		16			/* ������ͥ���٤κ����͡ʺ����͡�*/
#elif (TMAX_TPRI != 8) && (TMAX_TPRI != 16)
	#error "TMAX_TPRI must defined 8 or 16."
#endif	/* TMAX_TPRI */

#define TMIN_ISRPRI		1			/* ����ߥ����ӥ��롼����ͥ���٤κǾ��� */
#define TMAX_ISRPRI		16			/* ����ߥ����ӥ��롼����ͥ���٤κ����� */

/*
 *  �С���������
 */
#define TKERNEL_MAKER	UINT_C(0x0118)	/* �����ͥ�Υ᡼���������� */
#define TKERNEL_PRID	UINT_C(0x0007)	/* �����ͥ�μ����ֹ� */
#define TKERNEL_SPVER	UINT_C(0xf511)	/* �����ͥ���ͤΥС�������ֹ� */
#define TKERNEL_PRVER	UINT_C(0x1011)	/* �����ͥ�ΥС�������ֹ� */

/*
 *  �����ΰ���ݤΤ���Υޥ���
 *
 *  �ʲ���TOPPERS_COUNT_SZ��TOPPERS_ROUND_SZ������ϡ�unit��2�ζҾ�Ǥ�
 *  �뤳�Ȥ��ꤷ�Ƥ��롥
 */
#ifndef TOPPERS_COUNT_SZ
#define TOPPERS_COUNT_SZ(sz, unit)	(((sz) + (unit) - 1) / (unit))
#endif /* TOPPERS_COUNT_SZ */
#ifndef TOPPERS_ROUND_SZ
#define TOPPERS_ROUND_SZ(sz, unit)	(((sz) + (unit) - 1) & ~((unit) - 1))
#endif /* TOPPERS_ROUND_SZ */

#define COUNT_STK_T(sz)		TOPPERS_COUNT_SZ((sz), sizeof(STK_T))
#define ROUND_STK_T(sz)		TOPPERS_ROUND_SZ((sz), sizeof(STK_T))


#endif /* TOPPERS_KERNEL_H */

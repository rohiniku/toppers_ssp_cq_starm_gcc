/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2009 by Embedded and Real-Time Systems Laboratory
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
 *		�����ͥ�ν�����Ƚ�λ����
 */

#include "task.h"
#include "t_stddef.h"
#include "kernel_impl.h"
#include <sil.h>

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_KER_ENTER
#define LOG_KER_ENTER()
#endif /* LOG_KER_ENTER */

#ifndef LOG_KER_LEAVE
#define LOG_KER_LEAVE()
#endif /* LOG_KER_LEAVE */

#ifndef LOG_EXT_KER_ENTER
#define LOG_EXT_KER_ENTER()
#endif /* LOG_EXT_KER_ENTER */

#ifndef LOG_EXT_KER_LEAVE
#define LOG_EXT_KER_LEAVE(ercd)
#endif /* LOG_EXT_KER_LEAVE */


#ifdef TOPPERS_sta_ker

/*
 *  �����ͥ�ư����֥ե饰
 *
 *  �������ȥ��åץ롼����ǡ�false�ʡ�0�ˤ˽��������뤳�Ȥ���Ԥ���
 *  ���롥
 */
bool_t	kerflg = false;

/*
 *  �����ͥ�ε�ư
 *    NMI��������Ƥγ���ߤ��ޥ������줿����(������ߥ�å����֤�����)�ǸƤӽФ���롥
 */
void
sta_ker(void)
{
	target_initialize();
	
	initialize_object();
	
	call_inirtn();
	
	/*
	 *  �����ͥ��ư��򳫻Ϥ��롥
	 */	
	kerflg = true;
	
	/* �ǥ����ѥå����ư������������ư��򳫻Ϥ��� */
	LOG_KER_ENTER();
	start_dispatch();
	assert(false);
}

#endif /* TOPPERS_sta_ker */

#ifdef TOPPERS_ext_ker

/*
 *  �����ͥ�ν�λ
 */
ER
ext_ker(void)
{
	SIL_PRE_LOC;
	
	LOG_EXT_KER_ENTER();
	
	/*
	 *  ����ߥ�å����֤˰ܹ�
	 */
	SIL_LOC_INT();
	
	/*
	 *  �����ͥ�ư��ν�λ
	 */
	LOG_KER_LEAVE();
	kerflg = false;
	
	/*
	 *  �����ͥ�ν�λ�����θƽФ�
	 *
	 *  �󥿥�������ƥ����Ȥ��ڤ괹���ơ�exit_kernel��ƤӽФ���
	 */
	call_exit_kernel();
	
	/*
	 *  SIL_UNL_INT��ƤӽФ�������������ã���뤳�ȤϤʤ���
	 *  ���Ҥ���Τ�SIL_PRE_LOC�����������ѿ���������ˡ�
	 *  ����ѥ��餬���Ϥ���ٹ���������뤿��Ǥ��롥
	 */
	SIL_UNL_INT();
	LOG_EXT_KER_LEAVE(E_SYS)
	
	return E_SYS;
}


/*
 *  �����ͥ�ν�λ����
 */
void
exit_kernel(void)
{
	/*
	 *  ��λ�����롼����μ¹�
	 */
	call_terrtn();
	
	/*
	 *  �������åȰ�¸�ν�λ����
	 */
	target_exit();
	assert(false);
}

#endif /* TOPPERS_ext_ker */

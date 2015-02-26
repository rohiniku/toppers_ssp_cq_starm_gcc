/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011 by Meika Sugimoto
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
 *  ���٥�ȥե饰��ǽ
 */


#include "kernel_impl.h"
#include "check.h"
#include "eventflag.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_SET_FLG_ENTER
#define LOG_SET_FLG_ENTER(flgid, setptn)
#endif /* LOG_SET_FLG_ENTER */

#ifndef LOG_SET_FLG_LEAVE
#define LOG_SET_FLG_LEAVE(ercd)
#endif /* LOG_SET_FLG_LEAVE */

#ifndef LOG_ISET_FLG_ENTER
#define LOG_ISET_FLG_ENTER(flgid, setptn)
#endif /* LOG_ISET_FLG_ENTER */

#ifndef LOG_ISET_FLG_LEAVE
#define LOG_ISET_FLG_LEAVE(ercd)
#endif /* LOG_ISET_FLG_LEAVE */

#ifndef LOG_CLR_FLG_ENTER
#define LOG_CLR_FLG_ENTER(flgid, clrptn)
#endif /* LOG_CLR_FLG_ENTER */

#ifndef LOG_CLR_FLG_LEAVE
#define LOG_CLR_FLG_LEAVE(ercd)
#endif /* LOG_CLR_FLG_LEAVE */

#ifndef LOG_POL_FLG_ENTER
#define LOG_POL_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn)
#endif /* LOG_POL_FLG_ENTER */

#ifndef LOG_POL_FLG_LEAVE
#define LOG_POL_FLG_LEAVE(ercd, flgptn)
#endif /* LOG_POL_FLG_LEAVE */



/* ���٥�ȥե饰IDID��������󥪥ե��åȤؤ��Ѵ��ޥ��� */
#define INDEX_FLG(flgid)	((uint_t)((flgid) - TMIN_FLGID))

#ifdef TOPPERS_iniflg

void initialize_eventflag(void)
{
	uint_t i;
	
	for(i = 0U ; i < tmax_flgid ; i++)
	{
		/* �ӥåȥѥ�����ν���� */
		flgcb_flgptn[i] = flginib_iflgptn[i];
	}
}

#endif /* TOPPERS_iniflg */

/*
 *  ���٥�ȥե饰��郎��Ω���Ƥ��뤫�Υ����å�
 */
Inline bool_t
check_flg_cond(FLGPTN curptn , FLGPTN waiptn, MODE wfmode)
{
	bool_t flgset = false;
	
	if ((wfmode & TWF_ORW) != 0U)
	{
		if((curptn & waiptn) != 0U)
		{
			flgset = true;
		}
	}
	else	/* (wfmode & TWF_ANDW) != 0U  */
	{
		if((curptn & waiptn) == waiptn)
		{
			flgset = true;
		}
	}
	
	return (flgset);
}

/*
 *  ���٥�ȥե饰�Υ��å�
 */
#ifdef TOPPERS_set_flg

ER
set_flg(ID flgid, FLGPTN setptn)
{
	ER		ercd;
	
	LOG_SET_FLG_ENTER(flgid, setptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	
	t_lock_cpu();
	flgcb_flgptn[INDEX_FLG(flgid)] |= setptn;
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_SET_FLG_LEAVE(ercd);
	return(ercd);
}


#endif /* TOPPERS_set_flg */

/*
 *  ���٥�ȥե饰�Υ��åȡ��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_iset_flg

ER
iset_flg(ID flgid, FLGPTN setptn)
{
	ER		ercd;
	
	LOG_ISET_FLG_ENTER(flgid, setptn);
	CHECK_INTCTX_UNL();
	CHECK_FLGID(flgid);
	
	i_lock_cpu();
	flgcb_flgptn[INDEX_FLG(flgid)] |= setptn;
	ercd = E_OK;
	i_unlock_cpu();
	
  error_exit:
	LOG_ISET_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iset_flg */

/*
 *  ���٥�ȥե饰�Υ��ꥢ
 */
#ifdef TOPPERS_clr_flg

ER
clr_flg(ID flgid, FLGPTN clrptn)
{
	ER		ercd;
	
	LOG_CLR_FLG_ENTER(flgid, clrptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	
	t_lock_cpu();
	flgcb_flgptn[INDEX_FLG(flgid)] &= clrptn; 
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_CLR_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_clr_flg */


/*
 *  ���٥�ȥե饰�Ԥ��ʥݡ���󥰡�
 */
#ifdef TOPPERS_pol_flg

ER
pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	ER		ercd;
	int_t	index;
	
	LOG_POL_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0U);
	CHECK_PAR(wfmode == TWF_ORW || wfmode == TWF_ANDW);
	
	t_lock_cpu();
	
	index = INDEX_FLG(flgid);
	
	if (check_flg_cond(flgcb_flgptn[index], waiptn, wfmode)) {
		ercd = E_OK;
		*p_flgptn = flgcb_flgptn[index];

		if((flginib_atr[index] & TA_CLR) != 0U)
		{
			flgcb_flgptn[index] = 0U;
		}
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

  error_exit:
	LOG_POL_FLG_LEAVE(ercd, *p_flgptn);
	return(ercd);
}

#endif /* TOPPERS_pol_flg */



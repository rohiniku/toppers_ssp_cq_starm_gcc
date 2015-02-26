$ ======================================================================
$ 
$  TOPPERS/SSP Kernel
$      Smallest Set Profile Kernel
$ 
$   Copyright (C) 2007 by TAKAGI Nobuhisa
$   Copyright (C) 2007-2009 by Embedded and Real-Time Systems Laboratory
$               Graduate School of Information Science, Nagoya Univ., JAPAN
$   Copyright (C) 2010-2012 by Naoki Saito
$               Nagoya Municipal Industrial Research Institute, JAPAN
$ 
$  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ������������˸¤ꡤ�ܥ��եȥ���
$  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�
$  �����ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
$  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭�����
$      ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ�����
$      ��������˴ޤޤ�Ƥ��뤳�ȡ�
$  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻���
$      �Ǥ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ����Ѽԥ�
$      �˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ�����̵��
$      �ڵ����Ǻܤ��뤳�ȡ�
$  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻���
$      �Ǥ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ������������ȡ�
$    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
$        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
$    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ���
$        �𤹤뤳�ȡ�
$  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»��
$      ����⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ��ޤ���
$      �ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���ͳ�˴��
$      �����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
$ 
$  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ���
$  ��TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū���Ф�
$  ��Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ�����������
$  �ˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ����
$  ��ʤ���
$ 
$ ======================================================================

$ ������
$   ���ꤷ����������Ƭ�˥��֤�Ĥ���ɽ�����롥
$   �����ɵڤӽ��Ϥβ�������󤲤뤿��˻Ȥ���
$     ���� : ARGV[1] : ��Ƭ���������륿�֤ο�
$     ���� : ��ʸ����
$     ��� : RESULT�����Ƥ��뤿�ᡤ¾�δؿ��ν��Ϥ���¸�������˸ƤӽФ��Ⱦ�񤭤���롥
$ 
$FUNCTION LOG$
	$FOREACH i RANGE(1,ARGV[1])$$TAB$$END$
	$RESULT = {}$
$END$

$ =====================================================================
$ �������Υ����å�
$ =====================================================================

$ ��������1�İʾ�¸�ߤ��뤳�ȤΥ����å�
$IF !LENGTH(TSK.ID_LIST)$
	$ERROR$$FORMAT("no task is registered")$$END$
$END$

$ =====================================================================
$ kernel_cfg.h ������
$ =====================================================================

$FILE "kernel_cfg.h"$

/* kernel_cfg.h */$NL$
#ifndef TOPPERS_KERNEL_CFG_H$NL$
#define TOPPERS_KERNEL_CFG_H$NL$
$NL$
#define TNUM_TSKID	$LENGTH(TSK.ID_LIST)$$NL$
#define TNUM_CYCID	$LENGTH(CYC.ORDER_LIST)$$NL$
#define TNUM_ALMID	$LENGTH(ALM.ORDER_LIST)$$NL$
$NL$

$ // ������ID��ưͥ����(tskapri)�ι⤤��� reallocate_tskapri �س�����ơ�
$ // ����� kernel_cfg.h �ؽ��Ϥ��롥
$tsk_apriorder_list={}$
$tsk_epri_list={}$
$tsk_index = 1$
$FOREACH id SORT(TSK.ORDER_LIST, "TSK.ATSKPRI")$
	$tsk_apriorder_list = APPEND(tsk_apriorder_list, TSK.TSKID[id])$
	$reallocate_tskapri[TSK.TSKID[id]] = tsk_index$
	#define $TSK.TSKID[id]$	$tsk_index$$NL$

$	DEF_EPRI ���������Ƥ��ʤ��������μ¹Ի�ͥ���٤�����ưͥ���٤�Ʊ���ˤʤ�褦�ˤ��롥
	$tsk_epri_list = APPEND(tsk_epri_list, ALT(TSK.ETSKPRI[TSK.TSKID[id]], TSK.ATSKPRI[TSK.TSKID[id]]))$
	$tsk_index = tsk_index + 1$
$END$
$FOREACH id CYC.ID_LIST$
	#define $id$	$+id$$NL$
$END$
$FOREACH id ALM.ID_LIST$
	#define $id$	$+id$$NL$
$END$

#endif /* TOPPERS_KERNEL_CFG_H */$NL$

$ =====================================================================
$ kernel_cfg.c������
$ =====================================================================

$FILE "kernel_cfg.c"$

/* kernel_cfg.c */$NL$
#include "kernel/kernel_int.h"$NL$
#include "kernel_cfg.h"$NL$
$NL$
#ifndef TOPPERS_EMPTY_LABEL$NL$
#define TOPPERS_EMPTY_LABEL(x,y) x y[0]$NL$
#endif$NL$
$NL$

$ ---------------------------------------------------------------------
$  ���󥯥롼�ɥǥ��쥯�ƥ��֡�#include��
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  Include Directives (#include)$NL$
$SPC$*/$NL$
$NL$
$INCLUDES$
$NL$

$ ---------------------------------------------------------------------
$  ���֥������Ȥ�ID�ֹ���ݻ������ѿ�
$ ---------------------------------------------------------------------
$IF USE_EXTERNAL_ID$
	/*$NL$
	$SPC$*  Variables for Object ID$NL$
	$SPC$*/$NL$
	$NL$
	$FOREACH id TSK.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id CYC.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
	$FOREACH id ALM.ID_LIST$
		const ID $id$_id$SPC$=$SPC$$+id$;$NL$
	$END$
$END$

$ ---------------------------------------------------------------------
$  �ȥ졼�����ޥ���Υǥե�������
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  Default Definitions of Trace Log Macros$NL$
$SPC$*/$NL$
$NL$
#ifndef LOG_ISR_ENTER$NL$
#define LOG_ISR_ENTER(intno)$NL$
#endif /* LOG_ISR_ENTER */$NL$
$NL$
#ifndef LOG_ISR_LEAVE$NL$
#define LOG_ISR_LEAVE(intno)$NL$
#endif /* LOG_ISR_LEAVE */$NL$
$NL$


$ ---------------------------------------------------------------------
$  �������˴ؤ������
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  Task Management Functions$NL$
$SPC$*/$NL$
$NL$

$ ������ID�ֹ�κ�����
const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);$NL$
$NL$

$ ready_primap �ν����
$init_rdypmap = 0$
$tsk_index = 1$

$ ������°����
const ATR     	_kernel_tinib_tskatr[TNUM_TSKID]    = {
$JOINEACH tskid tsk_apriorder_list ","$
$	// TA_ACT , TA_RSTR �ޤ��� TA_NULL �Ǥ����E_RSATR��
	$IF (TSK.TSKATR[tskid] & ~(TA_ACT | TA_RSTR | ALT(TARGET_TSKATR,0))) != 0$
		$ERROR TSK.TEXT_LINE[tskid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "tskatr", TSK.TSKATR[tskid], tskid, "CRE_TSK")$$END$
	$END$

	($TSK.TSKATR[tskid]$)
	
	$IF TSK.TSKATR[tskid] & TA_ACT$
		$init_rdypmap = init_rdypmap + tsk_index$
	$END$
	$tsk_index = tsk_index << 1$
$END$
};$NL$

const uint_t$TAB$_kernel_init_rdypmap = $init_rdypmap$U;$NL$

$ ��ĥ����(exinf)�� ���顼�ϥ���ѥ�����ޤ��ϥ��ץ�Υƥ��ȤǸ��Ф��뤿�ᡤ�����ǤϤ��ʤ���
const intptr_t	_kernel_tinib_exinf[TNUM_TSKID]     = {
$JOINEACH tskid tsk_apriorder_list ","$
	(intptr_t)($TSK.EXINF[tskid]$)
$END$
};$NL$

$ ��ư����(task)�����顼�ϥ���ѥ�����ޤ��ϥ��ץ�Υƥ��ȤǸ��Ф��뤿�ᡤ�����ǤϤ��ʤ���
const TASK    	_kernel_tinib_task[TNUM_TSKID]      = {
$JOINEACH tskid tsk_apriorder_list ","$
	($TSK.TASK[tskid]$)
$END$
};$NL$

$ ��ưͥ����(atskpri)��
$FOREACH tskid tsk_apriorder_list$
$	// atskpri �� TMIN_TPRI �ʾ塤TMAX_TPRI �ʲ��Ǥ��롥��E_PAR��
 	$IF !(TMIN_TPRI <= TSK.ATSKPRI[tskid] && TSK.ATSKPRI[tskid] <= TMAX_TPRI)$
 		$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "atskpri", TSK.ATSKPRI[tskid], tskid, "CRE_TSK")$$END$
 	$END$

$	// atskpri �Ͻ�ʣ���ʤ�����E_PAR��
	$FOREACH tskid2 tsk_apriorder_list$
		$IF tskid != tskid2 && TSK.ATSKPRI[tskid] == TSK.ATSKPRI[tskid2] $
			$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% of %2% (%3%) in %4% is duplicated"), "atskpri", tskid, TSK.ATSKPRI[tskid], "CRE_TSK")$$END$
		$END$
	$END$
$END$

$ �¹Ի�ͥ����(etskpri)��
const uint_t  	_kernel_tinib_epriority[TNUM_TSKID] = {
$epri_allocated = 0$
$tsk_index = 0$
$JOINEACH tskid tsk_apriorder_list ","$
	$epri = AT(tsk_epri_list, tsk_index)$

$	// etskpri �� TMIN_TPRI �ʾ�Ǥ��롥(E_PAR)
	$IF TMIN_TPRI > epri$
		$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "etskpri", epri, tskid, "CRE_TSK")$$END$
	$END$

$	// etskpri �� atskpri �ʲ����ͤ���(ͥ���٤Ȥ��Ƥ�Ʊ����������⤤)��(E_PAR)
	$IF epri > TSK.ATSKPRI[tskid]$
		$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "etskpri", epri, tskid, "CRE_TSK")$$END$
	$END$

$	// etskpri ������ɽ������ꤷ reallocate_tskepri �˳�Ǽ��
	$FOREACH tskid2 tsk_apriorder_list $
	 	$IF epri_allocated != 1 && epri <= TSK.ATSKPRI[tskid2]$
			INT_PRIORITY($reallocate_tskapri[TSK.TSKID[tskid2]]$)
				$reallocate_tskepri[tskid] = reallocate_tskapri[TSK.TSKID[tskid2]]$
			$epri_allocated = 1$
		$END$
	$END$
	$epri_allocated = 0$
	$tsk_index = tsk_index + 1$
$END$
};$NL$$NL$

$ 
$ // ͥ���ٳ�����Ƥ˴ؤ����̤�ɸ����Ϥ�ɽ��
$ 
$FILE "stdout"$
=====================================$NL$
Task priority configuration result:$NL$
$FOREACH tskid SORT(TSK.ORDER_LIST, "TSK.ATSKPRI")$
	$TAB$$TSK.TSKID[tskid]$:$TAB$ IPRI = $reallocate_tskapri[TSK.TSKID[tskid]]$, EXEPRI = $reallocate_tskepri[tskid]$$NL$
$END$
=====================================$NL$
$ 
$ // �������ե�������ᤷ��ͥ���ٳ�����Ʒ�̤����
$ 
$FILE "kernel_cfg.c"$
/*$NL$
$SPC$* Task priority configuration result:$NL$
$FOREACH tskid SORT(TSK.ORDER_LIST, "TSK.ATSKPRI")$
$SPC$*  $TAB$$TSK.TSKID[tskid]$:$TAB$ IPRI = $reallocate_tskapri[TSK.TSKID[tskid]]$, EXEPRI = $reallocate_tskepri[tskid]$$NL$
$END$
$SPC$*/$NL$$NL$

$ 
$  �������κ��祹���å������̤η׻�
$ 

$ �����å��������˴ؤ��륨�顼�����å�
$FOREACH tskid TSK.ID_LIST$
$	// stksz��0�����������å�����κǾ��͡�TARGET_MIN_STKSZ�ˤ��⾮��������E_PAR��
	$IF TSK.STKSZ[tskid] == 0 || (LENGTH(TARGET_MIN_STKSZ) && 
										TSK.STKSZ[tskid] < TARGET_MIN_STKSZ)$
		$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(_("%1% `%2%\' of `%3%\' in %4% is too small"), "stksz", TSK.STKSZ[tskid], tskid, "CRE_TSK")$$END$
	$END$
$END$

$  
$ �ؿ����
$ 
$ 
$ �ؿ�1: ��ư��ͥ���٤��㤤��˥����ƥ��󥰤��뤿�����Ӵؿ�
$ 
$FUNCTION compare_tskapri_rev$
	$RESULT = reallocate_tskapri[ARGV[2]] - reallocate_tskapri[ARGV[1]]$
$END$

$ 
$ �ؿ�2: ���ꤷ�����������Ф��륹���å������̤κ����׻�����ؿ�
$    ���� : ARGV[1] : ������ID(����ɽ��, ��ư��ͥ���٤�����ɽ����������)
$    ���� : RESULT  : �������������Ф��륹���å������̤κ����͡�
$                     �����ͤϡ������������μ¹Գ��Ϥ��齪λ�ޤǤδ֤�
$                     ���Υ��������Ф���ץꥨ��ץȤ��θ���ƥ����å������̤�
$                     �׻��������ˡ���ǽ���Τ����Ȥ߹�碌����Ǻ���Ȥʤ��ͤ��֤���
$ 
$nest_level = 0$
$ 
$FUNCTION calc_stksz$
$	// �ѿ��ꥹ��
	$nest_level = nest_level + 1$
	$arg[nest_level] = ARGV[1]$
	$calculated_stack_size = 0$

$	// ��������
$SPC$* $LOG(nest_level-1)$Calculation start (Task ID = $arg[nest_level]$, StackSize[$arg[nest_level]$]=$TSK.STKSZ[arg[nest_level]]$)$NL$

$	// ���ꤷ��������ID �Υ����å��׻�����λ���Ƥ��뤫
	$IF	LENGTH(done[arg[nest_level]]) == 0$

$SPC$* $LOG(nest_level)$Task list with higher priority than $arg[nest_level]$ = $higher_pri_tsklist[arg[nest_level]]$$NL$

$		// (1) ��λ���Ƥ��ʤ����
$		// �ѿ��ν����
		$max_stksz[arg[nest_level]] = 0$
		$higher_pri_maxstksz[arg[nest_level]] = 0$

$		// ����������ID �μ¹Ի�ͥ���٤��⤤��ưͥ���٤���ĥ�������¸�ߤ�����
		$IF LENGTH(higher_pri_tsklist[arg[nest_level]]) > 0$
$			// ���줾��ι�ͥ���٥��������Ф�
			$FOREACH id higher_pri_tsklist[arg[nest_level]]$
$				// �Ƶ��ƽФ�����ѿ�����񤭤���뤿�ᡤ��¸���Ƥ���
				$id_saved[nest_level] = id$
$				// �����å��׻���¹Ԥ���
				$calculated_stack_size = calc_stksz(id_saved[nest_level])$
$				// ��¸�����ѿ�������
				$id = id_saved[nest_level]$

				$IF higher_pri_maxstksz[arg[nest_level]] < calculated_stack_size$
$					// �������Ƥ���
					$higher_pri_maxstksz[arg[nest_level]] = calculated_stack_size$
				$END$
			$END$
		$END$

$SPC$* $LOG(nest_level)$higher_pri_maxstksz[$arg[nest_level]$] = $higher_pri_maxstksz[arg[nest_level]]$$NL$

$		// ��ͥ���٥������Υ����å������̤ˡ������������λ����̤�û�����
		$max_stksz[arg[nest_level]] = higher_pri_maxstksz[arg[nest_level]] + TSK.STKSZ[arg[nest_level]]$

$SPC$* $LOG(nest_level)$DONE(max_stksz[$arg[nest_level]$] = $max_stksz[arg[nest_level]]$)$NL$

$		// ����������ID���Ф��ƤϷ׻���Ѥޤ����Ȥ�����Ͽ��Ĥ��Ƥ���
		$done[arg[nest_level]] = 1$

	$ELSE$
$		// (2) �׻������˴�λ���Ƥ����硤�׻��򥹥��åפ��롥

$SPC$* $LOG(nest_level)$SKIP(max_stksz[$arg[nest_level]$] = $max_stksz[arg[nest_level]]$)$NL$
	$END$

$	// ���Ѥ��κ����ͤ��֤�
	$RESULT = max_stksz[arg[nest_level]]$
	$nest_level = nest_level - 1$
$END$

$ 
$ �ؿ���������ޤǡ��������饹���å��׻������γ���
$ 

$ 
$ �ޤ����ڹ�¤�Υǡ�����¤����
$ 
$FOREACH id LSORT(tsk_apriorder_list, "compare_tskapri_rev")$

$	// �ƥ�������ˡ����μ¹Ի�ͥ���٤���⤤��ư��ͥ���٤���ĥ������Υꥹ�Ȥ��롥
$	// ����ϥץꥨ��ץȤ�����ǽ���Τ��륿�����ΰ����Ȥʤ롥
	$FOREACH id2 LSORT(tsk_apriorder_list, "compare_tskapri_rev")$
		$IF reallocate_tskepri[id] > reallocate_tskapri[id2]$
			$higher_pri_tsklist[id] = APPEND(higher_pri_tsklist[id], id2)$
		$END$
	$END$

$	// �ץꥨ��ץȤ��롦�����ط��򼨤��ڹ�¤�κ�(root)�Ȥʤ륿������õ����
$	//   �оݥ�����(id)�ε�ư��ͥ����(reallocate_tskapri[id])����㤤
$	//   (�ͤȤ��Ƥ��礭��)��ư��ͥ���٤��ĥ������� higher_pri_tsklist �ˡ�
$	//   �оݥ�����(id) ���ޤޤ�ʤ���С����Ȥʤ롥
	$is_root = 1$
	$FOREACH id2 LSORT(tsk_apriorder_list, "compare_tskapri_rev")$
		$IF (is_root == 1) && (reallocate_tskapri[id] < reallocate_tskapri[id2])$
			$IF LENGTH(FIND(higher_pri_tsklist[id2], id)) > 0$
				$is_root = 0$
			$END$
		$END$
	$END$
$	// ��(root)�Ȥʤ륿�����ʤ�С��ꥹ�Ȥ��ɲ�
	$IF is_root == 1$
		$root_apri = APPEND(root_apri, id)$
	$END$
$END$

$ 
$ ���ϳ���
$ 

/* $NL$
$SPC$* Task Stack Size Estimation: $NL$
$SPC$* $NL$

$ // ���Ȥʤ�ƥ��������Ф��ơ����κ��祿���������̤�׻������ꥹ�Ȥ��ɲä��롥
$FOREACH root_id root_apri$
	$stksz_estimated = APPEND(stksz_estimated, calc_stksz(root_id))$
$END$

$ // �������Υ����å������̤κ����ͤ����
$ // �ꥹ��������Ǥκ����ͤ��������κ��祹���å������̤Ȥʤ롥
$max_tsk_stksz = 0$
$FOREACH size stksz_estimated$
	$IF size > max_tsk_stksz$
		$max_tsk_stksz = size$
	$END$
$END$

$ // ��ǧ
$SPC$* List of Estimated Total Stack Sizes of Tasks = $stksz_estimated$$NL$
$SPC$* Estimated Maximum Total Stack Size of Tasks = $max_tsk_stksz$$NL$
$SPC$*/ $NL$$NL$


$ ���Ƥν���ñ�̤Υ����å��϶�ͭ����롥
$ ���Τ��ᡤ�����å��������˴ؤ�������å���
$ ��ͭ�����å�����ΤȤ���ǤޤȤ�ƹԤ���

$ �����å�����Ƭ����(stk)��
$FOREACH tskid tsk_apriorder_list$
$	// ��� NULL �Ǥ��롥(E_PAR)
	$IF !EQ(TSK.STK[tskid], "NULL")$
		$ERROR TSK.TEXT_LINE[tskid]$E_PAR: $FORMAT(("'%1%' of %2% must be NULL."), "stk", "CRE_TSK")$$END$
	$END$
$END$



$ ---------------------------------------------------------------------
$  ����ߴ�����ǽ
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  Interrupt Management Functions$NL$
$SPC$*/$NL$
$NL$

$ // INTNO_ATTISR_VALID �����Ǥ���ʣ���Ƥ��ʤ����ɤ����Υ����å�
$i = 0$
$FOREACH intno INTNO_ATTISR_VALID$
	$j = 0$
	$FOREACH intno2 INTNO_ATTISR_VALID$
		$IF i < j && intno == intno2$
			$ERROR$ $FORMAT(_("intno (%1%) of INTNO_ATTISR_VALID is duplicated"), intno)$$END$
		$END$
		$j = j + 1$
	$END$
	$i = i + 1$
$END$

$ // INHNO_ATTISR_VALID �����Ǥ���ʣ���Ƥ��ʤ����ɤ����Υ����å�
$i = 0$
$FOREACH intno INHNO_ATTISR_VALID$
	$j = 0$
	$FOREACH intno2 INHNO_ATTISR_VALID$
		$IF i < j && intno == intno2$
			$ERROR$ $FORMAT(_("intno (%1%) of INHNO_ATTISR_VALID is duplicated"), intno)$$END$
		$END$
		$j = j + 1$
	$END$
	$i = i + 1$
$END$


$ // ATT_ISR �ǻ��Ѳ�ǽ�ʳ�����ֹ�ȡ�������б��������ߥϥ�ɥ��ֹ�ο���Ʊ�����ɤ���
$ // �ƥꥹ�Ȥ����ǤϽ�ʣ���Ƥ��ʤ����Ȥ�����Ȥ��Ƥ��롥
$IF LENGTH(INTNO_ATTISR_VALID) != LENGTH(INHNO_ATTISR_VALID)$
	$ERROR$length of `INTNO_ATTISR_VALID' is different from length of `INHNO_ATTISR_VALID'$END$
$END$


$ // ������ֹ�ȳ���ߥϥ�ɥ��ֹ���Ѵ��ơ��֥�κ���
$ //  ������ֹ�Υꥹ�Ȥȳ���ߥϥ�ɥ��ֹ�Υꥹ�Ȥ��б��������Ǥ�Ʊ�����֤�
$ //  �����褦���¤٤��Ƥ��뤳�Ȥ�����Ȥ��롥
$i = 0$
$FOREACH intno INTNO_ATTISR_VALID$

$	// INTNO_ATTISR_VALID �˴ޤޤ���ͤ� INTNO_CFGINT_VALID �ˤ�ޤޤ��٤��Ǥ��롥
$	// INTNO_ATTISR_VALID �� INTNO_CFGINT_VALID ����ʬ����ˤʤ�Ϥ���
	$IF LENGTH(FIND(INTNO_CFGINT_VALID, intno)) == 0$
		$ERROR$all elements of `INTNO_ATTISR_VALID' must be included in `INTNO_CFGINT_VALID'$END$
	$END$

	$inhno = AT(INHNO_ATTISR_VALID, i)$
	$INHNO[intno] = inhno$
	$INTNO[inhno] = intno$
	$i = i + 1$
$END$


$ // INTNO_CFGINT_VALID �����Ǥ� INTNO_VALID �˴ޤޤ�뤫�ɤ����Υ����å�
$ // INTNO_CFGINT_VALID �� INTNO_VALID ����ʬ����ˤʤ�Ϥ���
$FOREACH intno INTNO_CFGINT_VALID$
	$IF LENGTH(FIND(INTNO_VALID, intno)) == 0$
		$ERROR$all elements of `INTNO_CFGINT_VALID' must be included in `INTNO_VALID'$END$
	$END$
$END$


$ // INHNO_ATTISR_VALID �����Ǥ� INHNO_VALID �˴ޤޤ�뤫�ɤ����Υ����å�
$ // INHNO_ATTISR_VALID �� INHNO_VALID ����ʬ����ˤʤ�Ϥ���
$FOREACH inhno INHNO_ATTISR_VALID$
	$IF LENGTH(FIND(INHNO_VALID, inhno)) == 0$
		$ERROR$all elements of `INHNO_ATTISR_VALID' must be included in `INHNO_VALID'$END$
	$END$
$END$


$ // ������׵�饤��˴ؤ��륨�顼�����å�
$i = 0$
$FOREACH intno INT.ORDER_LIST$
$	// intno��CFG_INT���Ф��������ֹ�Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(INTNO_CFGINT_VALID, INT.INTNO[intno]))$
		$ERROR INT.TEXT_LINE[intno]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "intno", INT.INTNO[intno], "CFG_INT")$$END$
	$END$

$	// intno��CFG_INT�ˤ�ä�����Ѥߤξ���E_OBJ��
	$j = 0$
	$FOREACH intno2 INT.ORDER_LIST$
 		$IF INT.INTNO[intno] == INT.INTNO[intno2] && j < i$
			$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "intno", INT.INTNO[intno], "CFG_INT")$$END$
		$END$
		$j = j + 1$
	$END$

$	// intatr�� TA_ENAINT, TA_EDGE, �ޤ��Ϥ���¾�������åȤ����Ѳ�ǽ��°���Τ�����Ǥ�ʤ�����E_RSATR��
	$IF (INT.INTATR[intno] & ~(TA_ENAINT|TA_EDGE|ALT(TARGET_INTATR,0))) != 0$
		$ERROR INT.TEXT_LINE[intno]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "intatr", INT.INTATR[intno], "intno", INT.INTNO[intno], "CFG_INT")$$END$
	$END$

$	// intpri��CFG_INT���Ф�������ͥ���٤Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(INTPRI_CFGINT_VALID, INT.INTPRI[intno]))$
		$ERROR INT.TEXT_LINE[intno]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "intpri", INT.INTPRI[intno], "CFG_INT")$$END$
	$END$

$	// �����ͥ�����γ���ߤȤ��Ƹ��ꤵ��Ƥ������ߤˡ�TMIN_INTPRI ���⾮�����ͤ����ꤵ�줿����E_OBJ��
	$IF LENGTH(FIND(INTNO_FIX_KERNEL, intno))$
		$IF INT.INTPRI[intno] < TMIN_INTPRI$
			$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' must not have higher priority than %3%"), "intno", INT.INTNO[intno], "TMIN_INTPRI")$$END$
		$END$
	$END$

$	// �����ͥ�������γ���ߤȤ��Ƹ��ꤵ��Ƥ������ߤˡ�TMIN_INTPRI ���⾮�����ͤ����ꤵ��ʤ��ä�����E_OBJ��
	$IF LENGTH(FIND(INTNO_FIX_NONKERNEL, intno))$
		$IF INT.INTPRI[intno] >= TMIN_INTPRI$
			$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' must have higher priority than %3%"), "intno", INT.INTNO[intno], "TMIN_INTPRI")$$END$
		$END$
	$END$
	$i = i + 1$
$END$


$ ����ߥϥ�ɥ�˴ؤ��륨�顼�����å�
$i = 0$
$FOREACH inhno INH.ORDER_LIST$
$	// ����ߥϥ�ɥ��ֹ�(inhno)���������ʤ�����E_PAR��
	$IF !LENGTH(FIND(INHNO_DEFINH_VALID, INH.INHNO[inhno]))$
		$ERROR INH.TEXT_LINE[inhno]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "inhno", INH.INHNO[inhno], "DEF_INH")$$END$
	$END$

$	// Ʊ������ߥϥ�ɥ��ֹ���Ф���DEF_INH��ʣ��¸�ߤ������E_OBJ��
	$j = 0$
	$FOREACH inhno2 INH.ORDER_LIST$
		$IF INH.INHNO[inhno] == INH.INHNO[inhno2] && j < i$
			$ERROR INH.TEXT_LINE[inhno]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "inhno", INH.INHNO[inhno], "DEF_INH")$$END$
		$END$
		$j = j + 1$
	$END$

$	// ����ߥϥ�ɥ�°��(inhatr) �� TA_NULL, TA_NONKERNEL, �ڤӤ���¾�������åȰ�¸�����Ѳ�ǽ��°���Τ�����Ǥ�ʤ���E_RSATR��
	$IF (INH.INHATR[inhno] & ~(TA_NONKERNEL|ALT(TARGET_INHATR,0))) != 0$
		$ERROR INH.TEXT_LINE[inhno]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "inhatr", INH.INHATR[inhno], "inhno", INH.INHNO[inhno], "DEF_INH")$$END$
	$END$

$	// �����ͥ�����˸��ꤵ��Ƥ������ߥϥ�ɥ�ˡ�TA_NONKERNEL °�������ꤵ��Ƥ����E_RSATR��
	$IF LENGTH(FIND(INHNO_FIX_KERNEL, inhno))$
		$IF (INH.INHATR[inhno] & TA_NONKERNEL) != 0$
			$ERROR INH.TEXT_LINE[inhno]$E_RSATR: $FORMAT(_("%1% `%2%\' must not be non-kernel interrupt"), "inhno", INH.INHNO[inhno])$$END$
		$END$
	$END$

$	// �����ͥ�������˸��ꤵ��Ƥ������ߥϥ�ɥ�ˡ�TA_NONKERNEL °�������ꤵ��Ƥ��ʤ���E_RSATR��
	$IF LENGTH(FIND(INHNO_FIX_NONKERNEL, inhno))$
		$IF (INH.INHATR[inhno] & TA_NONKERNEL) == 0$
			$ERROR INH.TEXT_LINE[inhno]$E_RSATR: $FORMAT(_("%1% `%2%\' must be non-kernel interrupt"), "inhno", INH.INHNO[inhno])$$END$
		$END$
	$END$


$	// ������ֹ��1��1�б��������ߥϥ�ɥ��ֹ�(ATT_ISR�ǻ����ǽ�ʳ���ߥϥ�ɥ��ֹ�)�ϡ��ʲ��Υ����å���Ԥ���
$	// INHNO_ATTISR_VALID �˴ޤޤ�ʤ�����ߥϥ�ɥ��ֹ�ϥ����å�����ʤ����Ȥˤʤ롥
	$IF LENGTH(INTNO[INH.INHNO[inhno]]) > 0$
		$intno = INTNO[INH.INHNO[inhno]]$

$		// ����ߥϥ�ɥ���Ͽ��γ�����׵�饤��°�����ꤵ��Ƥ��ʤ�(CFG_INT���ʤ�)��E_OBJ��
		$IF !LENGTH(INT.INTNO[intno])$
			$ERROR INH.TEXT_LINE[inhno]$E_OBJ: $FORMAT(_("%1% `%2%\' corresponding to %3% `%4%\' is not configured with %5%"), "intno", INT.INTNO[intno], "inhno", INH.INHNO[inhno], "CFG_INT")$$END$
		$ELSE$
			$IF (INH.INHATR[inhno] & TA_NONKERNEL) == 0$
$				// inhatr��TA_NONKERNEL�����ꤵ��Ƥ��餺��inhno���б�
$				// ����intno���Ф���CFG_INT�����ꤵ�줿�����ͥ���٤�
$				// TMIN_INTPRI���⾮��������E_OBJ��
				$IF INT.INTPRI[intno] < TMIN_INTPRI$
					$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' configured for %3% `%4%\' is higher than %5%"), "intpri", INT.INTPRI[intno], "inhno", INH.INHNO[inhno], "TMIN_INTPRI")$$END$
				$END$
			$ELSE$
$				// inhatr��TA_NONKERNEL�����ꤵ��Ƥ��ꡤinhno���б�
$				// ����intno���Ф���CFG_INT�����ꤵ�줿�����ͥ���٤�
$				// TMIN_INTPRI�ʾ�Ǥ������E_OBJ��
				$IF INT.INTPRI[intno] >= TMIN_INTPRI$
					$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' configured for %3% `%4%\' is lower than or equal to %5%"), "intpri", INT.INTPRI[intno], "inhno", INH.INHNO[inhno], "TMIN_INTPRI")$$END$
				$END$
			$END$
		$END$
	$END$
	$i = i + 1$
$END$

$ ����ߥ����ӥ��롼�����ISR�ˤ˴ؤ��륨�顼�����å��ȳ���ߥϥ�ɥ������
$FOREACH order ISR.ORDER_LIST$
$	// isratr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF (ISR.ISRATR[order] & ~ALT(TARGET_ISRATR,0)) != 0$
		$ERROR ISR.TEXT_LINE[order]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "isratr", ISR.ISRATR[order], "isr", ISR.ISR[order], "ATT_ISR")$$END$
	$END$

$	// intno��ATT_ISR���Ф��������ֹ�Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(INTNO_ATTISR_VALID, ISR.INTNO[order]))$
		$ERROR ISR.TEXT_LINE[order]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "intno", ISR.INTNO[order], "ATT_ISR")$$END$
	$END$

$	// (TMIN_ISRPRI <= isrpri && isrpri <= TMAX_ISRPRI)�Ǥʤ�����E_PAR��
	$IF !(TMIN_ISRPRI <= ISR.ISRPRI[order] && ISR.ISRPRI[order] <= TMAX_ISRPRI)$
		$ERROR ISR.TEXT_LINE[order]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "isrpri", ISR.ISRPRI[order], "ATT_ISR")$$END$
	$END$
$END$


$FOREACH intno INTNO_ATTISR_VALID$
	$inhno = INHNO[intno]$

$	// ������ֹ�intno���Ф�����Ͽ���줿ISR�Υꥹ�Ȥκ���
	$isr_order_list = {}$
	$FOREACH order ISR.ORDER_LIST$
		$IF ISR.INTNO[order] == intno$
			$isr_order_list = APPEND(isr_order_list, order)$
			$order_for_error = order$
		$END$
	$END$

$	// ������ֹ�intno���Ф�����Ͽ���줿ISR��¸�ߤ�����
	$IF LENGTH(isr_order_list) > 0$
$		// intno���б�����inhno���Ф���DEF_INH���������E_OBJ��
		$IF LENGTH(INH.INHNO[inhno])$
			$ERROR ISR.TEXT_LINE[order_for_error]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated with %4% `%5%\'"), "intno", ISR.INTNO[order_for_error], "ATT_ISR", "inhno", INH.INHNO[inhno])$$END$
		$END$

$		// intno���Ф���CFG_INT���ʤ�����E_OBJ��
		$IF !LENGTH(INT.INTNO[intno])$
			$ERROR ISR.TEXT_LINE[order_for_error]$E_OBJ: $FORMAT(_("%1% `%2%\' is not configured with %3%"), "intno", ISR.INTNO[order_for_error], "CFG_INT")$$END$
		$ELSE$
$			// intno���Ф���CFG_INT�����ꤵ�줿�����ͥ���٤�TMIN_INTPRI
$			// ���⾮��������E_OBJ��
			$IF INT.INTPRI[intno] < TMIN_INTPRI$
				$ERROR INT.TEXT_LINE[intno]$E_OBJ: $FORMAT(_("%1% `%2%\' configured for %3% `%4%\' is higher than %5%"), "intpri", INT.INTPRI[intno], "intno", ISR.INTNO[order_for_error], "TMIN_INTPRI")$$END$
			$END$
		$END$

$		// DEF_INH(inhno, { TA_NULL, _kernel_inthdr_<intno> } );
		$INH.INHNO[inhno] = inhno$
		$INH.INHATR[inhno] = VALUE("TA_NULL", 0)$
		$INH.INTHDR[inhno] = CONCAT("_kernel_inthdr_", intno)$
		$INH.ORDER_LIST = APPEND(INH.ORDER_LIST, inhno)$

$		// ISR�Ѥγ���ߥϥ�ɥ�
		void$NL$
		_kernel_inthdr_$intno$(void)$NL$
		{$NL$
		$IF LENGTH(isr_order_list) > 1$
			$TAB$PRI	saved_ipm;$NL$
			$NL$
			$TAB$i_begin_int($intno$);$NL$
			$TAB$saved_ipm = i_get_ipm();$NL$
		$ELSE$
			$TAB$i_begin_int($intno$);$NL$
		$END$
$		// ISR��ͥ���ٽ�˸ƤӽФ�
		$JOINEACH order SORT(isr_order_list, "ISR.ISRPRI") "\tif (i_sense_lock()) {\n\t\ti_unlock_cpu();\n\t}\n\ti_set_ipm(saved_ipm);\n"$
			$TAB$LOG_ISR_ENTER($intno$);$NL$
			$TAB$((ISR)($ISR.ISR[order]$))((intptr_t)($ISR.EXINF[order]$));$NL$
			$TAB$LOG_ISR_LEAVE($intno$);$NL$
		$END$
		$TAB$i_end_int($intno$);$NL$
		}$NL$
	$END$
$END$
$NL$

$ ����ߴ�����ǽ�Τ����ɸ��Ū�ʽ�������������
$IF !ALT(OMIT_INITIALIZE_INTERRUPT,0)$

$ ����ߥϥ�ɥ��
#define TNUM_INHNO	$LENGTH(INH.ORDER_LIST)$$NL$
const uint_t _kernel_tnum_inhno = TNUM_INHNO;$NL$
$NL$
$FOREACH inhno INH.ORDER_LIST$
	INTHDR_ENTRY($INH.INHNO[inhno]$, $+INH.INHNO[inhno]$, $INH.INTHDR[inhno]$)$NL$$NL$
$END$

$ ����ߥϥ�ɥ������ơ��֥�
$IF LENGTH(INH.ORDER_LIST)$
	const INHNO _kernel_inhinib_inhno[TNUM_INHNO] = {
	$JOINEACH inhno INH.ORDER_LIST ","$
		($INH.INHNO[inhno]$)
	$END$
	};$NL$

	const ATR _kernel_inhinib_inhatr[TNUM_INHNO] = {
	$JOINEACH inhno INH.ORDER_LIST ","$
		($INH.INHATR[inhno]$)
	$END$
	};$NL$

	const FP _kernel_inhinib_entry[TNUM_INHNO] = {
	$JOINEACH inhno INH.ORDER_LIST ","$
		(FP)(INT_ENTRY($INH.INHNO[inhno]$, $INH.INTHDR[inhno]$))
	$END$
	};$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const INHNO, _kernel_inhinib_inhno);$NL$
	TOPPERS_EMPTY_LABEL(const ATR, _kernel_inhinib_inhatr);$NL$
	TOPPERS_EMPTY_LABEL(const FP, _kernel_inhinib_entry);$NL$
$END$
$NL$

$ ������׵�饤���
#define TNUM_INTNO	$LENGTH(INT.ORDER_LIST)$$NL$
const uint_t _kernel_tnum_intno = TNUM_INTNO;$NL$
$NL$

$ ������׵�饤�������ơ��֥�
$IF LENGTH(INT.ORDER_LIST)$
	const INTNO _kernel_intinib_intno[TNUM_INTNO] = {
	$JOINEACH intno INT.ORDER_LIST ","$
		($INT.INTNO[intno]$)
	$END$
	};$NL$

	const ATR _kernel_intinib_intatr[TNUM_INTNO] = {
	$JOINEACH intno INT.ORDER_LIST ","$
		($INT.INTATR[intno]$)
	$END$
	};$NL$

	const PRI _kernel_intinib_intpri[TNUM_INTNO] = {
	$JOINEACH intno INT.ORDER_LIST ","$
		($INT.INTPRI[intno]$)
	$END$
	};$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const INTNO, _kernel_intinib_intno);$NL$
	TOPPERS_EMPTY_LABEL(const ATR, _kernel_intinib_intatr);$NL$
	TOPPERS_EMPTY_LABEL(const PRI, _kernel_intinib_intpri);$NL$
$END$
$NL$
$END$

$ ---------------------------------------------------------------------
$  CPU�㳰�ϥ�ɥ�
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  CPU Exception Handler$NL$
$SPC$*/$NL$
$NL$

$ // EXCNO_DEFEXC_VALID �����Ǥ� EXCNO_VALID �˴ޤޤ�뤫�ɤ����Υ����å�
$ // EXCNO_DEFEXC_VALID �� EXCNO_VALID ����ʬ����ˤʤ�Ϥ���
$FOREACH excno EXCNO_DEFEXC_VALID$
	$IF LENGTH(FIND(EXCNO_VALID, excno)) == 0$
		$ERROR$all elements of `EXCNO_DEFEXC_VALID' must be included in `EXCNO_VALID'$END$
	$END$
$END$


$ CPU�㳰�ϥ�ɥ�˴ؤ��륨�顼�����å�
$i = 0$
$FOREACH excno EXC.ORDER_LIST$
$	// excno��DEF_EXC���Ф���CPU�㳰�ϥ�ɥ��ֹ�Ȥ����������ʤ�����E_PAR��
	$IF !LENGTH(FIND(EXCNO_DEFEXC_VALID, EXC.EXCNO[excno]))$
		$ERROR EXC.TEXT_LINE[excno]$E_PAR: $FORMAT(_("illegal %1% `%2%\' in %3%"), "excno", EXC.EXCNO[excno], "DEF_EXC")$$END$
	$END$

$	// excno��DEF_EXC�ˤ�ä�����Ѥߤξ���E_OBJ��
	$j = 0$
	$FOREACH excno2 EXC.ORDER_LIST$
		$IF EXC.EXCNO[excno] == EXC.EXCNO[excno2] && j < i$
			$ERROR EXC.TEXT_LINE[excno]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated"), "excno", EXC.EXCNO[excno], "DEF_EXC")$$END$
		$END$
		$j = j + 1$
	$END$

$	// excatr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF (EXC.EXCATR[excno] & ~ALT(TARGET_EXCATR,0)) != 0$
		$ERROR EXC.TEXT_LINE[excno]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "excatr", EXC.EXCATR[excno], "excno", EXC.EXCNO[excno], "DEF_EXC")$$END$
	$END$
	$i = i + 1$
$END$

$ CPU�㳰�ϥ�ɥ�Τ����ɸ��Ū�ʽ�������������
$IF !ALT(OMIT_INITIALIZE_EXCEPTION,0)$

$ CPU�㳰�ϥ�ɥ��
#define TNUM_EXCNO	$LENGTH(EXC.ORDER_LIST)$$NL$
const uint_t _kernel_tnum_excno = TNUM_EXCNO;$NL$
$NL$
$FOREACH excno EXC.ORDER_LIST$
	EXCHDR_ENTRY($EXC.EXCNO[excno]$, $+EXC.EXCNO[excno]$, $EXC.EXCHDR[excno]$)$NL$$NL$
$END$

$ CPU�㳰�ϥ�ɥ������ơ��֥�
$IF LENGTH(EXC.ORDER_LIST)$
	const EXCNO _kernel_excinib_excno[TNUM_EXCNO] = {
	$JOINEACH excno EXC.ORDER_LIST ","$
		($EXC.EXCNO[excno]$)
	$END$
	};$NL$

	const ATR _kernel_excinib_excatr[TNUM_EXCNO] = {
	$JOINEACH excno EXC.ORDER_LIST ","$
		($EXC.EXCATR[excno]$)
	$END$
	};$NL$

	const FP _kernel_excinib_entry[TNUM_EXCNO] = {
	$JOINEACH excno EXC.ORDER_LIST ","$
		(FP)(EXC_ENTRY($EXC.EXCNO[excno]$, $EXC.EXCHDR[excno]$))
	$END$
	};$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const EXCNO, _kernel_excinib_excno);$NL$
	TOPPERS_EMPTY_LABEL(const ATR, _kernel_excinib_excatr);$NL$
	TOPPERS_EMPTY_LABEL(const FP, _kernel_excinib_entry);$NL$
$END$
$NL$
$END$


$ ---------------------------------------------------------------------
$  �����ϥ�ɥ�
$ ---------------------------------------------------------------------

/*$NL$
$SPC$*  Cyclic Handler Functions$NL$
$SPC$*/$NL$
$NL$

$ �����ϥ�ɥ�ID�ֹ�κ�����
const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);$NL$

$ �����ϥ�ɥ�Υ����।�٥��ID���ե��å�
$ �����ϥ�ɥ�Υ����।�٥��ID��0���鳫��
const uint_t _kernel_cycevtid_offset = 0;$NL$
$NL$

$ ����ȥ꤬16�Ĥ��¿�����ϡ����顼�Ȥ���
$IF LENGTH(CYC.ORDER_LIST) > 16$
	$ERROR$$FORMAT("The number of CRE_CYC must be equal to or less than 16.")$$END$
$END$

$IF LENGTH(CYC.ORDER_LIST)$
$	�����ϥ�ɥ�°��
	$CYCACT = 0$
	$FOREACH cycid CYC.ORDER_LIST$
$		// �����ϥ�ɥ�°��(cycatr) �� TA_NULL, TA_STA �Τ�����Ǥ�ʤ���E_RSATR��
		$IF (CYC.CYCATR[cycid] & ~TA_STA) != 0$
			$ERROR CYC.TEXT_LINE[cycid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "cycatr", CYC.CYCATR[cycid], cycid, "CRE_CYC")$$END$
		$END$

		$IF(CYC.CYCATR[cycid] & TA_STA)$
			$CYCACT = CYCACT | (1 << (cycid-1))$
		$END$
	$END$
	const uint16_t _kernel_cycinib_cycact = $CYCACT$;$NL$

$	�����ϥ�ɥ��ĥ����
	const intptr_t _kernel_cycinib_exinf[TNUM_CYCID] = {
	$JOINEACH cycid CYC.ORDER_LIST ","$
		(intptr_t)($CYC.EXINF[cycid]$)
	$END$
	};$NL$

$	�����ϥ�ɥ饢�ɥ쥹
	const CYCHDR _kernel_cycinib_cychdr[TNUM_CYCID] = {
	$JOINEACH cycid CYC.ORDER_LIST ","$
		($CYC.CYCHDR[cycid]$)
	$END$
	};$NL$

$	�����ϥ�ɥ����
	const RELTIM _kernel_cycinib_cyctim[TNUM_CYCID] = {
	$JOINEACH cycid CYC.ORDER_LIST ","$
$		// cyctim �� 0 ����礭����TMAX_RELTIM �ʲ��Ǥ��롥(E_PAR)
		$IF CYC.CYCTIM[cycid] <= 0 || TMAX_RELTIM < CYC.CYCTIM[cycid] $
			$ERROR CYC.TEXT_LINE[cycid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "cyctim", CYC.CYCTIM[cycid], cycid, "CRE_CYC")$$END$
		$END$

		($CYC.CYCTIM[cycid]$)
	$END$
	};$NL$

$	�����ϥ�ɥ����
	const RELTIM _kernel_cycinib_cycphs[TNUM_CYCID] = {
	$JOINEACH cycid CYC.ORDER_LIST ","$
$		// cycphs �� 0 �ʾ塤TMAX_RELTIM �ʲ��Ǥ��롥(E_PAR)
		$IF CYC.CYCPHS[cycid] < 0 || TMAX_RELTIM < CYC.CYCPHS[cycid] $
			$ERROR CYC.TEXT_LINE[cycid]$E_PAR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "cycphs", CYC.CYCPHS[cycid], cycid, "CRE_CYC")$$END$
		$END$

$		// ���꤬0���ġ�°���� TA_STA �ξ��Ϸٹ�
		$IF CYC.CYCPHS[cycid] == 0 && (CYC.CYCATR[cycid] & TA_STA) != 0$
			$WARNING CYC.TEXT_LINE[cycid]$$FORMAT(_("%1% is not recommended when %2% is set to %3% in %4%"), "cycphs==0", "TA_STA", "cycatr", "CRE_CYC")$$END$
		$END$

		($CYC.CYCPHS[cycid]$)
	$END$
	};$NL$
	$NL$

$	�����ϥ�ɥ�μ���ư����
EVTTIM _kernel_cyccb_evttim[TNUM_CYCID];$NL$

$ELSE$
	const uint16_t _kernel_cycinib_cycact = 0;$NL$
	TOPPERS_EMPTY_LABEL(const intptr_t, _kernel_cycinib_exinf);$NL$
	TOPPERS_EMPTY_LABEL(const CYCHDR, _kernel_cycinib_cychdr);$NL$
	TOPPERS_EMPTY_LABEL(const RELTIM, _kernel_cycinib_cyctim);$NL$
	TOPPERS_EMPTY_LABEL(const RELTIM, _kernel_cycinib_cycphs);$NL$
	TOPPERS_EMPTY_LABEL(EVTTIM, _kernel_cyccb_evttim);$NL$
$END$

$	�����ϥ�ɥ�ư�����
uint16_t _kernel_cyccb_cycact;$NL$

$NL$
$NL$

$ ---------------------------------------------------------------------
$  ���顼��ϥ�ɥ�
$ ---------------------------------------------------------------------

/*$NL$
$SPC$*  Alarm Handler Functions$NL$
$SPC$*/$NL$
$NL$

$ ����ȥ꤬16�Ĥ��¿�����ϡ����顼�Ȥ���
$IF LENGTH(ALM.ORDER_LIST) > 16$
	$ERROR$$FORMAT("The number of CRE_ALM must be equal to or less than 16.")$$END$
$END$

$ ���顼��ϥ�ɥ�κ���ID��
const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);$NL$

$ ���顼��ϥ�ɥ�Υ����।�٥��ID���ե��å�
const uint_t _kernel_almevtid_offset = $LENGTH(CYC.ORDER_LIST)$;$NL$
$NL$

$FOREACH almid ALM.ORDER_LIST$
$	// almatr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF ALM.ALMATR[almid] != 0$
		$ERROR ALM.TEXT_LINE[almid]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "almatr", ALM.ALMATR[almid], almid, "CRE_ALM")$$END$
	$END$
$END$

$IF LENGTH(ALM.ORDER_LIST)$
$	���顼��ϥ�ɥ���Ƭ����
	const ALMHDR _kernel_alminib_almhdr[TNUM_ALMID] = {
	$JOINEACH almid ALM.ORDER_LIST ","$
		($ALM.ALMHDR[almid]$)
	$END$
	};$NL$

$	���顼��ϥ�ɥ��ĥ����
	const intptr_t _kernel_alminib_exinf[TNUM_ALMID] = {
	$JOINEACH almid ALM.ORDER_LIST ","$
		(intptr_t)($ALM.EXINF[almid]$)
	$END$
	};$NL$
$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const ALMHDR, _kernel_alminib_almhdr);$NL$
	TOPPERS_EMPTY_LABEL(const intptr_t, _kernel_alminib_exinf);$NL$
$NL$
$END$

$ ���顼��ϥ�ɥ����
uint16_t _kernel_almcb_almact;$NL$
$NL$


$ ---------------------------------------------------------------------
$  �����।�٥�ȴ���
$ ---------------------------------------------------------------------

/*$NL$
$SPC$*  Time Event Management$NL$
$SPC$*/$NL$
$NL$

$TNUM_TMEVT = LENGTH(CYC.ORDER_LIST) + LENGTH(ALM.ORDER_LIST)$

#define TNUM_TMEVT $TNUM_TMEVT$$NL$
$NL$

$ �����।�٥�ȥ֥�å��Υ�����
const uint_t _kernel_tnum_tmevt_queue = TNUM_TMEVT;$NL$$NL$

$IF TNUM_TMEVT != 0$
$	�����।�٥�ȥ��塼
	QUEUE _kernel_tmevt_queue[TNUM_TMEVT+1];$NL$
$	�����।�٥�Ȼ���
	EVTTIM _kernel_tmevt_time[TNUM_TMEVT];$NL$
$	�����।�٥�ȤΥ�����Хå�
	CBACK _kernel_tmevt_callback[TNUM_TMEVT];$NL$
$	�����।�٥�ȥ�����Хå��ΰ���
	uintptr_t _kernel_tmevt_arg[TNUM_TMEVT];$NL$
	$NL$$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(QUEUE, _kernel_tmevt_queue);$NL$
	TOPPERS_EMPTY_LABEL(EVTTIM, _kernel_tmevt_time);$NL$
	TOPPERS_EMPTY_LABEL(CBACK, _kernel_tmevt_callback);$NL$
	TOPPERS_EMPTY_LABEL(uintptr_t, _kernel_tmevt_arg);$NL$
	$NL$$NL$
$END$

$ ---------------------------------------------------------------------
$  ��ͭ�����å��ΰ�
$      SSP�ǤϤ��٤Ƥν���ñ�̤Υ����å���ͭ���뤿�ᡤ
$      �����ǥ����ƥ����ΤΥ����å��ΰ����ݤ��롥
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  Stack Area for System$NL$
$SPC$*/$NL$
$NL$

$ // �ѿ����
$ // ������Ƥ�줿��ͭ�����å��ΰ�Υ�����
$allocated_stack_size = 0$

$ // DEF_ICS �Υ���ȥ꤬¸�ߤ��뤫?
$IF !LENGTH(ICS.ORDER_LIST)$
$	// �ʤ���硥�������ϴ����� (DEFAULT_ISTKSZ) ��Ȥ�
$	// �ΰ����Ƭ���Ϥδ����� (DEFALT_ISTK) �ϻȤ�ʤ����ˤȤ��롥
$	// �����å��ΰ����Ƭ���Ϥ���ꤹ����ϡ�DEF_ICS ��Ȥ����ȡ�
	#define TOPPERS_ISTKSZ		DEFAULT_ISTKSZ$NL$
	static STK_T          		_kernel_stack[COUNT_STK_T(TOPPERS_ISTKSZ)];$NL$
	#define TOPPERS_STK   		_kernel_stack$NL$
	#define TOPPERS_STKSZ		ROUND_STK_T(TOPPERS_ISTKSZ)$NL$
	$NL$

	$allocated_stack_size = DEFAULT_ISTKSZ$
$ELSE$
$	// DEF_ICS �Υ���ȥ꤬������

$ 
$	// ���顼�����å�
$ 
$	// ��ŪAPI��DEF_ICS�פ�ʣ�������E_OBJ��
	$IF LENGTH(ICS.ORDER_LIST) > 1$
		$ERROR$E_OBJ: $FORMAT(_("too many %1%"), "DEF_ICS")$$END$
	$END$
$	// DEF_ICS ��0����ꤷ�����(E_PAR)
	$IF ICS.ISTKSZ[1] == 0$
		$ERROR ICS.TEXT_LINE[1]$E_PAR: $FORMAT(_("%1% in %2% is 0"), "istksz", "DEF_ICS")$$END$
	$ELSE$
		$allocated_stack_size = ICS.ISTKSZ[1]$
	$END$

	$IF EQ(ICS.ISTK[1], "NULL")$
$		// �����å��ΰ�μ�ư���դ�
		#define TOPPERS_ISTKSZ		($ICS.ISTKSZ[1]$)$NL$
		static STK_T				_kernel_stack[COUNT_STK_T(TOPPERS_ISTKSZ)];$NL$
		#define TOPPERS_STK   		_kernel_stack$NL$
		#define TOPPERS_STKSZ		ROUND_STK_T(TOPPERS_ISTKSZ)$NL$
	$ELSE$
$ 		// istksz���������å������ޤ륢�饤���ȥ��������ܿ��˥��饤���Ȥ���Ƥ��ʤ�����E_PAR��
		$IF LENGTH(CHECK_STKSZ_ALIGN) && (ICS.ISTKSZ[1] & (CHECK_STKSZ_ALIGN - 1))$
			$ERROR ICS.TEXT_LINE[1]$E_PAR: $FORMAT(_("%1% `%2%\' in %3% is not aligned"), "istksz", ICS.ISTKSZ[1], "DEF_ICS")$$END$
		$END$

		#define TOPPERS_ISTKSZ		($ICS.ISTKSZ[1]$)$NL$
		#define TOPPERS_STK   		($ICS.ISTK[1]$)$NL$
		#define TOPPERS_STKSZ		ROUND_STK_T(TOPPERS_ISTKSZ)$NL$
	$END$
$END$
$NL$

$ ��ͭ�����å��ѤΥ����å��ΰ�
const SIZE		_kernel_stksz = TOPPERS_STKSZ;$NL$
STK_T *const	_kernel_stk = TOPPERS_STK;$NL$
$NL$
#ifdef TOPPERS_ISTKPT$NL$
STK_T *const	_kernel_istkpt = TOPPERS_ISTKPT(TOPPERS_STK, TOPPERS_STKSZ);$NL$
#endif /* TOPPERS_ISTKPT */$NL$
$NL$

$ 
$ // �����å�����˴ؤ����̤�ɸ����Ϥ�ɽ��
$ 
$FILE "stdout"$
=====================================$NL$
Stack size configuration result:$NL$
$TAB$Estimated task stack size = $max_tsk_stksz$$NL$
$TAB$Allocated total stack size = $allocated_stack_size$(value=$FORMAT("%d",+allocated_stack_size)$)$NL$
$ // �������Υ����å����������ο�����祵�������ºݤ˳����Ƥ�줿��ͭ�����å��ΰ�Υ���������礭����硤�ٹ𤹤롥
$IF max_tsk_stksz > allocated_stack_size$
	$TAB$!!!WARNING!!!: Estimated task stack size is more than the allocated stack size.$NL$
	$WARNING ICS.TEXT_LINE[1]$ $FORMAT("The estimated task stack size is more than the allocated stack size.")$$END$
$END$
=====================================$NL$
$ 
$ // ������򸵤��ᤷ�Ƥ���
$ 
$FILE "kernel_cfg.c"$


$ ---------------------------------------------------------------------
$  �ƥ⥸�塼��ν�����ؿ�
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  Module Initialization Function$NL$
$SPC$*/$NL$
$NL$
void$NL$
_kernel_initialize_object(void)$NL$
{$NL$
$IF TNUM_TMEVT > 0$
$TAB$_kernel_initialize_time_event();$NL$
$END$
$TAB$_kernel_initialize_task();$NL$
$TAB$_kernel_initialize_interrupt();$NL$
$TAB$_kernel_initialize_exception();$NL$
$IF LENGTH(CYC.ID_LIST)$
	$TAB$_kernel_initialize_cyclic();$NL$
$END$
$IF LENGTH(ALM.ID_LIST)$
	$TAB$_kernel_initialize_alarm();$NL$
$END$
}$NL$
$NL$

$ ---------------------------------------------------------------------
$  ������롼����μ¹Դؿ�
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  Initialization Routine$NL$
$SPC$*/$NL$
$NL$
void$NL$
_kernel_call_inirtn(void)$NL$
{$NL$
$FOREACH order INI.ORDER_LIST$
$ 	// iniatr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF INI.INIATR[order] != 0$
		$ERROR INI.TEXT_LINE[order]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "iniatr", INI.INIATR[order], "inirtn", INI.INIRTN[order], "ATT_INI")$$END$
	$END$
	$TAB$((INIRTN)($INI.INIRTN[order]$))((intptr_t)($INI.EXINF[order]$));$NL$
$END$
}$NL$
$NL$

$ ---------------------------------------------------------------------
$  ��λ�����롼����μ¹Դؿ�
$ ---------------------------------------------------------------------
/*$NL$
$SPC$*  Termination Routine$NL$
$SPC$*/$NL$
$NL$
void$NL$
_kernel_call_terrtn(void)$NL$
{$NL$
$FOREACH rorder TER.RORDER_LIST$
$ 	// teratr����TA_NULL�ˤǤʤ�����E_RSATR��
	$IF TER.TERATR[rorder] != 0$
		$ERROR TER.TEXT_LINE[rorder]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of %3% `%4%\' in %5%"), "teratr", TER.TERATR[rorder], "terrtn", TER.TERRTN[rorder], "ATT_TER")$$END$
	$END$
	$TAB$((TERRTN)($TER.TERRTN[rorder]$))((intptr_t)($TER.EXINF[rorder]$));$NL$
$END$
}$NL$
$NL$



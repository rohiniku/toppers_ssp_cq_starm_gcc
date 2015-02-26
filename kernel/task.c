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
 *  Copyright (C) 2010 by Meika Sugimoto
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

#include "kernel_impl.h"
#include "task.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */

#ifndef LOG_DSP_ENTER
	#define LOG_DSP_ENTER(tskidx)
#endif /* LOG_DSP_ENTER */

#ifndef LOG_DSP_LEAVE
	#define LOG_DSP_LEAVE(tskidx)
#endif /* LOG_DSP_ENTER */


extern const intptr_t	tinib_exinf[];			/* �������γ�ĥ���� */
extern const TASK    	tinib_task[];			/* �������ε�ư���� */
extern const uint_t  	tinib_epriority[];		/* �������μ¹Ի�ͥ���١�����ɽ���� */

/* �����ؿ��Υץ�ȥ�������� */
Inline bool_t primap_empty(void);
Inline bool_t primap_test(uint_t pri);
Inline uint_t primap_search(void);
Inline void primap_set(uint_t pri);
Inline void primap_set(uint_t pri);
Inline void primap_clear(uint_t pri);
Inline uint_t bitmap_search(uint_t bitmap);


#ifdef TOPPERS_tskini

/*
 *  �¹Ծ��֥������θ���ͥ����
 */
uint_t runtsk_curpri;

/*
 *  �¹Ծ��֥������ε�ư��ͥ����
 */
uint_t runtsk_ipri;

/*
 *  ��ǥ����塼�������Τ���Υӥåȥޥå�
 */
volatile uint_t	ready_primap;

/*
 *  �������ǥ����ѥå���ư�׵�ե饰
 */
bool_t	reqflg;

/*
 *  �ǥ����ѥå��ػ߾���
 */
bool_t	disdsp;

/*
 *  read_primap�ν����
 */
extern const uint_t init_rdypmap;

#endif /* TOPPERS_tskini */

#ifdef TOPPERS_get_ipriself

/*
 *  ������ID����ε�ư��ͥ���ټ���(����������ƥ�������)
 */
uint_t
get_ipri_self(ID tskid)
{
	uint_t ipri;
	
	if(tskid != TSK_SELF)
	{
		ipri = (uint_t)((tskid) - TMIN_TSKID);
	}
	else
	{
		ipri = runtsk_ipri;
	}
	return ipri;
}

#endif /* TOPPERS_get_ipriself */

/*
 *  ������ID����ε�ư��ͥ���ټ���(�󥿥�������ƥ�������)
 */
#ifdef TOPPERS_get_ipri

uint_t
get_ipri(ID tskid)
{
	return (uint_t)(tskid - TMIN_TSKID);
}

#endif /* TOPPERS_get_ipri */

/*
 *  �ӥåȥޥåץ������ؿ�
 *
 *  bitmap���1�ΥӥåȤ��⡤�ǤⲼ�̡ʱ��ˤΤ�Τ򥵡����������Υӥ�
 *  ���ֹ���֤����ӥå��ֹ�ϡ��ǲ��̥ӥåȤ�0�Ȥ��롥bitmap��0�����
 *  ���ƤϤʤ�ʤ������δؿ��Ǥϡ�bitmap��8�ӥåȤǤ��뤳�Ȥ��ꤷ��
 *  uint8_t���Ȥ��Ƥ��롥
 *
 *  �ӥåȥ�����̿�����ĥץ��å��Ǥϡ��ӥåȥ�����̿���Ȥ��褦��
 *  ��ľ����������Ψ���ɤ���礬���롥���Τ褦�ʾ��ˤϡ��������å�
 *  ��¸���ǥӥåȥ�����̿���Ȥä�bitmap_search���������
 *  OMIT_BITMAP_SEARCH��ޥ����������Ф褤���ޤ����ӥåȥ�����̿���
 *  �������������դʤɤ���ͳ��ͥ���٤ȥӥåȤȤ��б����ѹ�����������
 *  �ϡ�PRIMAP_BIT��ޥ����������Ф褤��
 *
 *  �ޤ���ɸ��饤�֥���ffs������ʤ顤���Τ褦���������ɸ��饤��
 *  ����Ȥä�������Ψ���ɤ���ǽ���⤢�롥
 *		#define	bitmap_search(bitmap) (ffs(bitmap) - 1)
 */
#ifndef PRIMAP_BIT
#define	PRIMAP_BIT(pri)		(1U << (pri))
#endif /* PRIMAP_BIT */

#ifndef OMIT_BITMAP_SEARCH

static const uint8_t bitmap_search_table[] = { 0U, 1U, 0U, 2U, 0U, 1U, 0U,
												3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U };

Inline uint_t
bitmap_search(uint_t bitmap)
{
	uint_t	n = 0U;

#if TMAX_TPRI != 8
	if ((bitmap & 0x00ffU) == 0U) {
		bitmap >>= 8U;
		n += 8U;
	}
#endif
	
	if ((bitmap & 0x0fU) == 0U) {
		bitmap >>= 4U;
		n += 4U;
	}
	return (n + bitmap_search_table[(bitmap & 0x0fU) - 1U]);
}

#endif /* OMIT_BITMAP_SEARCH */


/*
 *  ��ư��ͥ���٥ӥåȥޥåפ������Υ����å�
 */
Inline bool_t
primap_empty(void)
{
	return (ready_primap == 0U);
}

/*
 *  ���ꤷ����ư��ͥ���٤ε�ư��ͥ���٥ӥåȥޥåפ����åȤ���Ƥ��뤫�ɤ����Υ����å�
 */
Inline bool_t
primap_test(uint_t pri)
{
	return ((ready_primap & PRIMAP_BIT(pri)) != 0U);
}

/*
 *  ��ư��ͥ���٥ӥåȥޥåפΥ�����
 */
Inline uint_t
primap_search(void)
{
	return bitmap_search(ready_primap);
}

/*
 *  ��ư��ͥ���٥ӥåȥޥåפΥ��å�
 */
Inline void
primap_set(uint_t pri)
{
	ready_primap |= PRIMAP_BIT(pri);
}

/*
 *  ��ư��ͥ���٥ӥåȥޥåפΥ��ꥢ
 */
Inline void
primap_clear(uint_t pri)
{
	ready_primap &= ~PRIMAP_BIT(pri);
}

/*
 *  �ǹ�ͥ���̥������Υ�����
 */

#ifdef TOPPERS_tsksched

uint_t
search_schedtsk(void)
{
	return primap_search();
}

#endif /* TOPPERS_tsksched */

#ifdef TOPPERS_tskdmt
/*
 *  ���ꤷ����ư��ͥ���٤Υ��������¹ԤǤ�����֤��ɤ����Υƥ���
 *
 */
bool_t
test_dormant(uint_t ipri)
{
	return !primap_test(ipri);
}

#endif /* TOPPERS_tskdmt */

/*
 *  �����������⥸�塼��ν����
 */


#ifdef TOPPERS_tskini

void
initialize_task(void)
{
	/* ��ư��ͥ���٥ӥåȥޥåפν���� */
	ready_primap = init_rdypmap;
	
	/* ������ͥ���٤ν���� */
	runtsk_curpri = TSKPRI_NULL;
	runtsk_ipri = TSKPRI_NULL;
	
	/* ����߶ػߥե饰�ν���� */
	disdsp = false;
}

#endif /* TOPPERS_tskini */

/*
 *  �������ε�ư
 */

#ifdef TOPPERS_tskact

bool_t
make_active(uint_t ipri)
{
	bool_t dsp;
	
	primap_set(ipri);
	
	/* 
	 *  �¹Ծ��֥������θ���ͥ���٤Ȱ����ǻ��ꤵ�줿
	 *  ��ư�оݥ������ν��ͥ���٤���Ӥ����¹Ծ��֥�������
	 *  �ѹ����뤫Ƚ�ꤹ�롥
	 *
	 *  �������¹Ծ��֥��������ѹ�������ϥǥ����ѥå��ػ߾��֤⻲�Ȥ��롥
	 */
	if(ipri < runtsk_curpri) {
		dsp = !disdsp;
	}
	else {
		dsp = false;
	}
	
	return dsp;
}

#endif /* TOPPERS_tskact */


/*
 *  �������μ¹�
 */

#ifdef TOPPERS_tskrun

void
run_task(uint_t ipri)
{
	uint_t next_pri;		/* ���˼¹Գ��Ϥ��륿�����ε�ư��ͥ���� */
	uint_t saved_ipri;		/* �ƤӽФ����������ν��ͥ���� */
	uint_t saved_curpri;	/* �ƤӽФ����������θ���ͥ���� */
	bool_t cont;
	
	/* �ǹ�ͥ���̥�������¹Ԥ������ˡ����߼¹���Υ������θ���ͥ���٤Ƚ��ͥ���٤���¸���� */
	next_pri = ipri;
	saved_ipri = runtsk_ipri;
	saved_curpri = runtsk_curpri;
	
	do {
		/* �¹Ԥ��륿�����θ���ͥ���٤�¹Ի�ͥ���٤����ꤹ�� */
		runtsk_curpri = tinib_epriority[next_pri];
		runtsk_ipri = next_pri;
		
		/* CPU��å���� */
		t_unlock_cpu();
		
		/* �������¹Գ��� */
		(*((TASK)(tinib_task[next_pri])))(tinib_exinf[next_pri]);
		
		if (t_sense_lock()) {
			/*
			 *  CPU��å����֤�ext_tsk���ƤФ줿���ϡ�CPU��å�������
			 *  �Ƥ��饿������λ���롥������ϡ������ӥ���������Ǥ�CPU
			 *  ��å����ά����Ф褤������
			 */
		}
		else {
			/*
			 *  ����t_lock_cpu�򤳤β���disdsp������Τ褦�ˤ��ʤ��Τϡ�
			 *  CPU��å���˺���t_lock_cpu��ƤФʤ�����Ǥ��롥
			 */
			t_lock_cpu();
		}
		
		/* �����ͥ���٥ޥ�������������֤ΤϤ��ʤΤǡ����⤷�ʤ� */
		
		/*
		 *  �ǥ����ѥå��ػ߾��֤�ext_tsk���ƤФ줿���ϡ��ǥ����ѥ�
		 *  �����ľ��֤ˤ��Ƥ��饿������λ���롥
		 *
		 *	����ϰʲ��Τ褦�˵��Ҥ��٤��Ǥ��뤬��������ˤ���disdsp��
		 *	false�ˤ���Ф������ᡤñ��false�����ꤹ�롥
		 *
		 *		if (disdsp) {
		 *			disdsp = false;
		 *		}
		 */
		disdsp = false;
		
		/* �ӥåȥޥåץ��ꥢ�� */
		primap_clear(next_pri);
		
		cont = false;
		/* �����줫�Υ��������¹Բ�ǽ���֤ˤʤäƤ��뤫 */
		if(!primap_empty())
		{
			/* ����西�����θ���ͥ���٤��⤤��ư��ͥ���٤��ĥ���������ư���줿�� */
			next_pri = search_schedtsk();
			if(saved_curpri > next_pri)
			{
				cont = true;
			}
		}
	} while(cont);
	
	runtsk_curpri = saved_curpri;
	runtsk_ipri = saved_ipri;
}

#endif /* TOPPERS_tskrun */

/*
 *  �������ǥ����ѥå���
 */

#ifdef TOPPERS_tskdsp

void
dispatcher(void)
{
	do {
		if(!primap_empty()) {
			/* �������γ��� */
			run_task(search_schedtsk());
		}
		else {
			idle_loop();
		}
	} while(true);
}

#endif /* TOPPERS_tsk_dsp */

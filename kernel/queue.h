/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
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
 *  ���塼���إå�
 *
 *  SSP�����ͥ�Ǥϥ�������Τ���˥���ǥå�������Ѥ������塼���Ѥ���
 */

#ifndef TOPPERS_QUEUE_H
#define TOPPERS_QUEUE_H

/* ���塼�Υ���ǥå��� */
typedef uint8_t QUEIDX;

/* ���塼��¤�� */
typedef struct
{
	QUEIDX	next;
	QUEIDX	prev;
} QUEUE;


/* ���塼�إå��ν���� */
Inline void
queue_initialize(QUEUE *queue , QUEIDX queue_null)
{
	queue->next = queue->prev = queue_null;
}

/* ���ꤷ�����Ǥ����˿��������Ǥ��ɲ� */
Inline void
queue_insert_prev(QUEUE *top , QUEIDX queue , QUEIDX entry)
{
	top[entry].prev = top[queue].prev;
	top[entry].next = queue;
	top[top[queue].prev].next = entry;
	top[queue].prev = entry;
}


/* ���ꤷ�����塼�μ������Ǥ����������Υ���ǥå������֤� */
Inline QUEIDX
queue_delete_next(QUEUE *top , QUEIDX queue)
{
	top[top[queue].next].prev = top[queue].prev;
	top[top[queue].prev].next = top[queue].next;
	
	return top[queue].next;
}


/*
 *  ���塼�������ɤ����Υƥ���
 *
 *  queue�ˤϥ��塼�إå�����ꤹ�뤳��
 */
Inline bool_t
queue_empty(QUEUE *queue , QUEIDX queue_null)
{
	bool_t empty;
	
	if(queue->next == queue_null)
	{
		empty = true;
	}
	else
	{
		empty = false;
	}
	
	return empty;
}

#endif /* TOPPERS_QUEUE_H */

/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
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
 *		kernel_cfg.c�ʤ����cfg1_out.c���ѥإå��ե�����
 */

#ifndef TOPPERS_KERNEL_INT_H
#define TOPPERS_KERNEL_INT_H

/*
 *  �����ͥ�ɸ��إå��ե�����
 */
#include "kernel_impl.h"

/*
 *  �����ͥ�γƥإå��ե�����
 */
#include "task.h"
#include "interrupt.h"
#include "exception.h"

/*
 *  ��ĥ�ѥå������Υإå��ե�����
 */
#include "time_event.h"
#include "cyclic.h"
#include "alarm.h"
#include "eventflag.h"
#include "dataqueue.h"

/*
 *  ��͡��ष������ܥ�򸵤��᤹����Υإå��ե�����
 */
#include "kernel_unrename.h"


#endif /* TOPPERS_KERNEL_INT_H */

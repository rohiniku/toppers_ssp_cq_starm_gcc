/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2010 by Meika Sugimoto
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 */

#include <string>
#include <iostream>

#include "toppers/oil/oil_parser.hpp"
#include "toppers/diagnostics.hpp"

using namespace std;
using namespace boost::spirit::classic;
using namespace toppers::oil;
using namespace toppers::oil::oil_implementation;
using namespace toppers::oil::oil_definition;


int oil_parser::do_parse(oil_impl **impl , oil_def **def)
{
	oil_grammer grammer(this);
	parse_info<> info;
	
	info = parse(description->c_str() , grammer , space_p);
	if(info.hit)
	{
		*impl = &impl_list;
		*def = &def_list;
		return 0;
	}
	else
	{
		return -1;
	}
}

void eval_tree(tree_match<char const *>::tree_iterator const &iter, int nest) {
	int size; // �Ρ��ɤλҤθĿ�
	
	size = iter->children.size(); // �Ρ��ɤλҤθĿ�����Ф�
	for(int i=0; i<nest; i++)
	{
		cout << "  "; // ���ڡ�������ʬ����ǥ��
	}
	cout << "Node = '" << string(iter->value.begin(), iter->value.end()) << "'";
	if (size > 0)
	{
		cout << " Child Size = " << size << endl; // �ҤθĿ���ɽ��
	} else
	{
		cout << endl;                             // �Ҥ�̵����иĿ�ɽ�����ʤ�
	}
	for(int j=0; j<size; j++)
	{
		eval_tree(iter->children.begin()+j, nest+1); // �ҤθĿ�ʬ�Ƶ��ƤӽФ�
	}
}

int oil_parser::start_objimpl_analysis(std::string object_name)
{
	int result = 0;

	try
	{
		// ������Υ��֥������ȼ���������¸
		current_impl = new oil_object_impl(object_name);
	}
	catch( ... )
	{
		result = -1;
	}
	
	return result;
}

int oil_parser::set_nextparam_name(std::string name)
{
	if(param_addable == true)
	{
		next_param_name = name;
	}

	return 0;
}

int oil_parser::add_parameter_objimpl(std::string parameter)
{
	// �ѥ�᡼�����ϡ��ɲ�
	if(param_addable)
	{
		current_impl->add_parameter(next_param_name , parameter);
	}

	return 0;
}

int oil_parser::start_objdef_analysis(std::string object_name_type)
{
	int result = 0;

	try
	{
		// ������Υ��֥������ȼ���������¸
		current_def = new object_definition(object_name_type);
	}
	catch( ... )
	{
		result = -1;
	}
	return result;
}

int oil_parser::end_objimpl_analysis(void)
{
	// ������λ����Ͽ
	impl_list.push_back(current_impl);
	
	return 0;
}

void oil_parser::enable_addparam(bool enabled)
{
	param_addable = enabled;
}

int oil_parser::end_objdef_analysis(void)
{
	static std::vector<std::string> defined_object_name;
	std::string obj_name = current_def->get_name();

	// ����Ʊ�����֥������Ȥ��ʤ��������å�
	if(find(defined_object_name.begin() , defined_object_name.end() , obj_name)
			== defined_object_name.end())
	{
		// ������λ����Ͽ
		def_list.push_back(current_def);
		// ���֥�������̾���ɲá���Ͽ�Ѥߤˤ���
		defined_object_name.push_back(obj_name);
	}
	else
	{
		// Ʊ̾�Υ��֥�������̾��¸�ߤ��뤿�ᡤ���顼
		toppers::error("Object %1% redefined." , obj_name);
	}
	
	return 0;
}

int oil_parser::add_attr_value(string str)
{
	attr_description = str;

	if(param_addable == true)
	{
		current_def->add_parameter(next_param_name , attr_description);
	}

	return 0;
}

void oil_parser::set_error(int position , std::string message)
{
	error_position = position;
	error_message = message;
}

void oil_parser::get_error(int *position , std::string *message)
{
	*position = error_position;
	*message = error_message;
}

void oil_parser::dump_implementation(void)
{
	std::vector<oil_object_impl*>::iterator p;

	for(p = impl_list.begin(); p != impl_list.end() ; p++)
	{
		(*p)->display_implementation();
	}
}

void oil_parser::dump_definition(void)
{
	std::vector<object_definition*>::iterator p;
	
	cout << "************** Object Defition **************" << endl;
	for(p = def_list.begin(); p != def_list.end() ; p++)
	{
		(*p)->display_definition();
	}
	cout << "************** Object Defition End **************" << endl;
}

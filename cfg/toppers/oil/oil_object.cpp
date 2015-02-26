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

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/cast.hpp>
#include <algorithm>
#include <functional>

#include "toppers/oil/oil_object.hpp"
#include "toppers/diagnostics.hpp"

namespace toppers
{
	namespace oil
	{
		// �ǥХå��Ѵؿ�
		void dump(boost::smatch *r)
		{
			unsigned int i;

			for(i = 0 ; i < r->size() ; i++)
			{
				cout << "Match[" << i << "] : " << r->str(i) << endl;
			}
		}
		
		namespace oil_implementation
		{
			int oil_object_impl::add_parameter(string param_name , string parameter_description)
			{
				if((parameter_description.find("UINT32") == 0)
					|| (parameter_description.find("UINT64") == 0))
				{
					this->params.push_back(
						(object_parameter_impl *)(new parameter_uint_impl(param_name , parameter_description)));
				}
				else if((parameter_description.find("INT32") == 0)
						|| (parameter_description.find("INT64") == 0))
				{
					this->params.push_back(
						(object_parameter_impl *)(new parameter_int_impl(param_name , parameter_description)));
				}
				else if(parameter_description.find("ENUM") == 0)
				{
					this->params.push_back(
						(object_parameter_impl *)(new parameter_enum_impl(param_name , parameter_description)));
				}
				else if(parameter_description.find("BOOLEAN") == 0)
				{
					boost::regex bool_with_option("\\[\\s*TRUE");
					string::const_iterator start = parameter_description.begin();
					string::const_iterator end = parameter_description.end();

					// [ TRUE , FALSE ]���������ENUM��Ʊ���������ʤ�����STRING��Ʊ�������Ȥ���
					if(regex_search(start , end , bool_with_option))
					{
						this->params.push_back(
							(object_parameter_impl *)(new parameter_enum_impl(param_name , parameter_description)));
					}
					else
					{
						this->params.push_back(
							(object_parameter_impl *)(new parameter_boolean_impl(param_name , parameter_description)));
					}
				}
				else if(parameter_description.find("STRING") == 0)
				{
					this->params.push_back(
						(object_parameter_impl *)(new parameter_string_impl(param_name , parameter_description)));
				}
				else if(parameter_description.find("FLOAT") == 0)
				{
					this->params.push_back(
						(object_parameter_impl *)(new parameter_float_impl(param_name , parameter_description)));
				}
				else if(parameter_description.find("_TYPE") != string::npos)
				{
					this->params.push_back(
						(object_parameter_impl *)(new parameter_object_ref_impl(param_name , parameter_description)));
				}
				else
				{
					// ���ꤨ�ʤ�
				}

				return 0;
			}

			oil_object_impl::~oil_object_impl()
			{
				std::vector<object_parameter_impl*>::iterator p;

				for(p = params.begin() ; p != params.end() ; p++)
				{
					delete (*p);
				}
			}

			bool oil_object_impl::validate_object_parameter
				(oil_definition::object_parameter_def *obj_param , bool *multiple ,
						std::vector<object_ref> *references)
			{
				std::vector<object_parameter_impl*>::iterator match;
				bool result = false;

				// Ʊ��̾������ĥѥ�᡼�������뤫����
				// ��find_if���ȥ����󥭥㥹�Ȥ˼��Ԥ���
				for(match = params.begin() ; match != params.end() ; match++)
				{
					if((*match)->validate_parameter_name(obj_param->get_parameter_name())
						== true)
					{
						break;
					}
				}
				
				// �ѥ�᡼����°�������å�
				if(match != params.end())
				{
					parameter_object_ref_impl *ref_param;
					parameter_enum_impl *enum_param;

					ref_param = dynamic_cast<parameter_object_ref_impl*>(*match);
					if(ref_param != NULL)
					{
						if(ref_param->validate_object_parameter(obj_param , references) == true)
						{
							*multiple = (*match)->get_multiple();
							result = true;
						}
					}
					else 
					{
						// enum�ξ�硢�����Ǥǻ��Ȥ��ФƤ����ǽ��������
						enum_param = dynamic_cast<parameter_enum_impl*>(*match);
						if(enum_param != NULL)
						{
							if(enum_param->validate_object_parameter(obj_param , references) == true)
							{
								*multiple = (*match)->get_multiple();
								result = true;
							}
							else
							{
								// ���顼���Ϥ�validate_object_parameter�ǹԤäƤ��뤿�����ס�
								//toppers::error("Object %1%'s parameter %2% can't set %3%." , 
								//	obj_param->get_parent_name() , obj_param->get_parameter_name() , obj_param->get_value());
							}
						}
						else
						{
							if((*match)->validate_object_parameter(obj_param) == true)
							{
								*multiple = (*match)->get_multiple();
								result = true;
							}
							else
							{
								// ���顼���Ϥ�validate_object_parameter�ǹԤäƤ��뤿�����ס�
								//toppers::error("Object %1%'s parameter %2% can't set %3%." , 
								//	obj_param->get_parent_name() , obj_param->get_parameter_name() , obj_param->get_value());
							}
						}
					}
				}
				else
				{
					// ���顼����
					toppers::error("Object %1% can't define parameter %2%." , 
						obj_param->get_parent_name() , obj_param->get_parameter_name());
				}

				return result;
			}

			// ���ܥѥ�᡼���Υ����å�
			bool object_parameter_impl::validate_object_parameter
					(oil_definition::object_parameter_def *obj , bool *auto_param)
			{
				// ʣ������ϥ��֥������Ȳ���¦�Ǥ����Ԥ��ʤ�
				// �ǥե����������ɤ����⥪�֥������ȤǤ����Ԥ��ʤ�
				set_parameter_type(obj);
								
				// AUTO°���Υ����å�
				if(obj->get_value() == "AUTO")
				{
					if(assign_auto == false)
					{
						toppers::error("Object %1% : %2% can't use \"AUTO\"" ,
							obj->get_parent_name().c_str() , obj->get_parameter_name().c_str());
						return false;
					}
					else
					{
						*auto_param = true;
					}
				}
				else
				{
					*auto_param = false;
				}

				return true;
			}
			
			template<typename T>
			bool validate_number_paremeter
			(VALUE_LIMIT_TYPE type ,T value , T min , T max , vector<T> *value_list)
			{
				bool result = true;
				
				if(type == LIMIT_RANGE)
				{
					if((value < min) || (value > max))
					{
						result = false;
					}
				}
				else if(type == LIMIT_LIST)
				{
                    // modified by takuya
					//std::vector<T>::iterator p;
					typename std::vector<T>::iterator p;

					// �ͤΥꥹ�Ȥ�¸�ߤ��뤫�򸡺�
					p = find(value_list->begin() , value_list->end() , value);
					if(p >= value_list->end())
					{
						result = false;
					}
				}
				else
				{
					// �����å���ɬ�פʤ�
				}

				return result;
			}

			template<typename T>
			void val2string(std::vector<T> *list , std::string *str)
			{
                // modified by takuya 110823
				//std::vector<T>::iterator p;
				typename std::vector<T>::iterator p;

				for(p = list->begin() ; p != list->end() ; p++)
				{
					try
					{
						*str += boost::lexical_cast<string>(*p) + " , ";
					}
					catch( ... )
					{
						toppers::error("cast error");
					}
				}
			}

			bool parameter_int_impl::validate_object_parameter
					(oil_definition::object_parameter_def *obj)
			{
				bool result = false , assign_auto;
				int64_t value;
				
				// ����°���Υ����å�
				if(object_parameter_impl::validate_object_parameter(obj , &assign_auto)
					== false)
				{
					return false;
				}

				// AUTO�ѥ�᡼���ʤ餹����ȴ����
				if(assign_auto == true)
				{
					return true;
				}

				// �ͤ��Ѵ�
				if(obj->get_value().find("0x") != string::npos)
				{
                    // modified by takuya 110823
					//(void)sscanf_s(obj->get_value().c_str() , "0x%I64x" , &value);
					(void)sscanf(obj->get_value().c_str() , "0x%llx" , &value);
				}
				else if(obj->get_value().find("0X") != string::npos)
				{
                    // modified by takuya 110823
					//(void)sscanf_s(obj->get_value().c_str() , "0X%I64x" , &value);
					(void)sscanf(obj->get_value().c_str() , "0X%llx" , &value);
				}
				else
				{
					try
					{
						value = boost::lexical_cast<int64_t>(obj->get_value());
					}
					catch(std::exception& exception)
					{
						toppers::error("%1%'s %2% is not INT16/INT32." , 
							obj->get_parent_name() , obj->get_parameter_name());

						return false;
					}
				}

				if(validate_number_paremeter
							(limit_type , value , min , max , &value_list) == false)
				{
					if(limit_type == LIMIT_RANGE)
					{
						toppers::error("Object %1%'s %2% is \"%3%\" not in range [%4% - %5%]" ,
							obj->get_parent_name().c_str() , obj->get_parameter_name().c_str() ,
							obj->get_value() , min , max);
					}
					else // if(limit_type == LIMIT_LIST)
					{
						std::string str;
						val2string(&value_list , &str);
						
						toppers::error("Object %1%'s %2% is \"%3%\" not in range [%4% - %5%]" ,
							obj->get_parent_name().c_str() , obj->get_parameter_name().c_str() ,
							obj->get_value() , min , max);
					}
				}
				else
				{
					result = true;
				}

				return result;
			}

			void parameter_int_impl::set_parameter_type(oil_definition::object_parameter_def *obj)
			{
				obj->set_type(TYPE_INT);
			}

			bool parameter_uint_impl::validate_object_parameter
				(oil_definition::object_parameter_def *obj)
			{
				bool result = false , assign_auto;
				uint64_t value;
				
				// ����°���Υ����å�
				if(object_parameter_impl::validate_object_parameter(obj , &assign_auto)
					== false)
				{
					return false;
				}

				// AUTO�ѥ�᡼���ʤ餹����ȴ����
				if(assign_auto == true)
				{
					return true;
				}

				// �ͤ��Ѵ�
				if(obj->get_value().find("0x") != string::npos)
				{
                    // modified by takuya 110823
					//(void)sscanf_s(obj->get_value().c_str() , "0x%I64x" , &value);
					(void)sscanf(obj->get_value().c_str() , "0x%llx" , &value);
				}
				else if(obj->get_value().find("0X") != string::npos)
				{
                    // modified by takuya 110823
					//(void)sscanf_s(obj->get_value().c_str() , "0X%I64x" , &value);
					(void)sscanf(obj->get_value().c_str() , "0X%llx" , &value);
				}
				else
				{
					try
					{
						value = boost::lexical_cast<uint64_t>(obj->get_value());
					}
					catch(std::exception& exception)
					{
						toppers::error("%1% : %2% is not UINT16/UINT32." , 
							obj->get_parent_name() , obj->get_parameter_name());
						return false;
					}
				}

				if(validate_number_paremeter
							(limit_type , value , min , max , &value_list) == false)
				{
					if(limit_type ==LIMIT_RANGE)
					{
						toppers::error("Object %1%'s %2% : %3% is not in range [%4% - %5%]" ,
							obj->get_parent_name().c_str() , obj->get_parameter_name().c_str() ,
							obj->get_value() , min , max);
					}
					else // if(limit_type == LIMIT_LIST)
					{
						std::string str;
						val2string(&value_list , &str);

						toppers::error("Object %1%'s %2% : %3% is not in range value list [%4%]" ,
							obj->get_parent_name().c_str() , obj->get_parameter_name().c_str() ,
							obj->get_value() , str);
					}
				}
				else
				{
					result = true;
				}

				return result;
			}

			void parameter_uint_impl::set_parameter_type(oil_definition::object_parameter_def *obj)
			{
				obj->set_type(TYPE_UINT);
			}

			bool parameter_float_impl::validate_object_parameter
				(oil_definition::object_parameter_def *obj)
			{
				bool result = false , assign_auto;
				double value;
				
				// ����°���Υ����å�
				if(object_parameter_impl::validate_object_parameter(obj , &assign_auto)
					== false)
				{
					return false;
				}

				// AUTO�ѥ�᡼���ʤ餹����ȴ����
				if(assign_auto == true)
				{
					return true;
				}

				// �ͤ��Ѵ�
				try
				{
					value = boost::lexical_cast<double>(obj->get_value().c_str());
				}
				catch(std::exception& exception)
				{
					toppers::error("%1% : %2% is not FLOAT." , 
						obj->get_parent_name() , obj->get_parameter_name());

					return false;
				}

				if(validate_number_paremeter
							(limit_type , value , min , max , &value_list) == false)
				{
					if(limit_type ==LIMIT_RANGE)
					{
						toppers::error("Object %1%'s %2%  : %3% is not in range [%4% - %5%]" ,
							obj->get_parent_name().c_str() , obj->get_parameter_name().c_str() ,
							obj->get_value().c_str() , min , max);
					}
					else // if(limit_type == LIMIT_LIST)
					{
						std::string str;
						val2string(&value_list , &str);

						toppers::error("Object %1%' %2% : %3% is not in range value list [%4%]" ,
							obj->get_parent_name().c_str() , obj->get_parameter_name().c_str() ,
							obj->get_value().c_str() , str.c_str());
					}
				}
				else
				{
					result = true;
				}

				return result;
			}

			void parameter_float_impl::set_parameter_type(oil_definition::object_parameter_def *obj)
			{
				obj->set_type(TYPE_FLOAT);
			}

			bool parameter_enum_impl::validate_object_parameter
					(oil_definition::object_parameter_def *obj , std::vector<toppers::oil::object_ref> *object_refs)
			{
				std::map<std::string , oil_object_impl*>::iterator p;
				bool result = true , assign_auto;

				// ����°���Υ����å�
				if(object_parameter_impl::validate_object_parameter(obj , &assign_auto)
					== false)
				{
					return false;
				}

				// AUTO�ѥ�᡼���ʤ餹����ȴ����
				if(assign_auto == true)
				{
					return true;
				}

				// �ѥ�᡼����ENUM�Υꥹ�Ȥˤ��뤫����(���������
				std::vector<oil_definition::object_definition*>::iterator s;
				std::string str;
				bool hit = false;

				for(p = sub_params.begin() ; p != sub_params.end(); p++)
				{
					// ���顼�����ѤΥꥹ��
					str += (*p).first + " , ";
					// �ѥ�᡼��̾�����פ��Ƥ��ʤ������ν����ϹԤ�ʤ�
					if(obj->get_value() == (*p).first)
					{
						hit = true;
					}
				}
				// �ꥹ�Ȥˤʤ��ä����ν���
				if(hit == false)
				{
					toppers::error("Object %1%'s %2% : %3% is not in range [%4%]" ,
						obj->get_parent_name().c_str() , obj->get_parameter_name().c_str() , 
						obj->get_value().c_str() , str);

					return false;
				}
				
				// ���֥ѥ�᡼���ˤĤ��Ƥ�����å�
				for(s = obj->get_subparams()->begin() ; s != obj->get_subparams()->end() ; s++)
				{
					for(p = sub_params.begin() ; p != sub_params.end(); p++)
					{
						/* Ʊ̾�������������򸫤Ĥ�����Ƶ��Ǹ��� */
						if((*s)->get_parent()->get_value() == (*p).first)
						{
							if((*p).second->validate_object_configuration((*s) , object_refs) == true)
							{
								result = true;
							}
						}
					}
					if(result == true)
					{
						break;
					}
				}
				// ���Ĥ���ʤ���Х��顼
				if((obj->get_subparams()->empty() == false)
					&& (s == obj->get_subparams()->end()))
				{
					result = false;
				}

				return result;
			}

			bool parameter_object_ref_impl::validate_object_parameter
					(oil_definition::object_parameter_def *obj , std::vector<toppers::oil::object_ref> *object_refs)
			{
				// ����°���Υ����å�
				// ��ե������Υ����å��⤳���ǹԤ��٤�������
				// ��ե������Υ��֥������ȼ��������Ǥ��ʤ������ǹԤ�
				if(object_parameter_impl::validate_object_parameter(obj , &assign_auto)
					== false)
				{
					return false;
				}

				// �����å�����٤���ե���󥹤�����
				object_ref ref = { reftype_name , obj->get_value() };
				object_refs->push_back(ref);

				return true;
			}

			void parameter_string_impl::set_parameter_type
					(oil_definition::object_parameter_def *obj)
			{
				obj->set_type(TYPE_STRING);
			}

			void parameter_boolean_impl::set_parameter_type
					(oil_definition::object_parameter_def *obj)
			{
				obj->set_type(TYPE_BOOLEAN);
			}
		
			void parameter_enum_impl::set_parameter_type(oil_definition::object_parameter_def *obj)
			{
				obj->set_type(TYPE_ENUM);
			}

			void parameter_object_ref_impl::set_parameter_type(oil_definition::object_parameter_def *obj)
			{
				obj->set_type(TYPE_REF);
			}

			bool oil_object_impl::validate_object_configuration
					(oil_definition::object_definition * obj_def , std::vector<object_ref> *references)
			{
				std::vector<oil_definition::object_parameter_def*>::iterator p;
				std::vector<oil_definition::object_parameter_def*> *obj_params;
				std::vector<object_parameter_impl*>::iterator q;
				std::vector<string> defined_parameter;
				std::vector<object_parameter_impl*> undefined_parameter;
				std::vector<string>::iterator found , s;
				bool result = true;
				bool multiple;

				// ���֥�������̾����äƤ��뤫�����å�
				if(name != obj_def->get_object_type())
				{
					return false;
				}

				// �ѥ�᡼���������������å�
				obj_params = obj_def->get_params();
				for(p = obj_params->begin() ; p != obj_params->end() ; p++)
				{
					if(validate_object_parameter(*p , &multiple , references) == false)
					{
						result = false;
					}

					// ʣ�������ǽ���Υ����å�
					if(((found = find(defined_parameter.begin() , defined_parameter.end() , 
						(*p)->get_parameter_name())) != defined_parameter.end())
							&& (multiple == false))
					{
						toppers::error("Object %1% : %2% can define once." ,
							obj_def->get_name().c_str() , (*p)->get_parameter_name().c_str());

						result = false;
					}
					else
					{
						defined_parameter.push_back((*p)->get_parameter_name());
					}
				}

				if(result == true)
				{
					//
					// �ǥե���ȥѥ�᡼�����䴰
					//

					// ���֥�����������˵��ܤ���Ƥ��ʤ��ѥ�᡼����õ��
					for(q = params.begin() ; q != params.end() ; q++)
					{
						s = find(defined_parameter.begin() , 
							defined_parameter.end() , (*q)->get_name());

						if(s == defined_parameter.end())
						{
							undefined_parameter.push_back((*q));
						}
					}

					// õ�������ѥ�᡼�����Ф��ƤΥǥե���ȥѥ�᡼�����䴰
					for(q = undefined_parameter.begin() ; q != undefined_parameter.end() ; q++)
					{
						string default_value;
						DEFAULT_TYPE deftype = (*q)->get_default(&default_value);

						if((deftype == HAVE_DEFAULT)
							|| (deftype == AUTO))
						{
							obj_def->add_parameter((*q)->get_name() , default_value);
						}
						else if(deftype == NO_DEFAULT)
						{
							toppers::error("Object %1% : Parmeter %2% is not defined. %2% doesn't have default value." ,
								obj_def->get_name().c_str() , (*q)->get_name().c_str());

							result = false;
						}
						else	/* deftype == HAVE_NOT_DEFINE */
						{
						}

					}
				}

				return result;
			}

			bool parameter_string_impl::validate_object_parameter
					(oil_definition::object_parameter_def *obj)
			{
				// ʸ��°�����ä����󤬤ʤ�������true
				return true;
			}
			
			bool parameter_boolean_impl::validate_object_parameter
					(oil_definition::object_parameter_def *obj)
			{
				// TRUE��FALSE�Ǥʤ��Ȥʤ�ʤ�
				if((obj->get_value() == "TRUE")
					|| (obj->get_value() == "FALSE"))
				{
					return true;
				}

				toppers::error("Object %1%'s %2% is \"%3%\" , but can not set [TRUE , FALSE , ]." ,
					obj->get_parent_name() , obj->get_parameter_name() , obj->get_value());

				return false;
			}

			void oil_object_impl::display_implementation(void)
			{
				std::vector<object_parameter_impl*>::iterator p;
				
				cout << "=========== Object Name : " << name << "===========" << endl << endl;
				for(p = params.begin() ; p != params.end() ; p++)
				{
					(*p)->display_implementation();
				}
				cout << endl << "==================================" << endl;
				
			}

			void object_parameter_impl::set_parameter_type
					(oil_definition::object_parameter_def *obj)
			{
				obj->set_type(TYPE_UNKNOWN);
			}
		}

		namespace oil_definition
		{
			object_definition* find_object(string name)
			{
				return NULL;
			}
			
			int object_definition::add_parameter(string param_name , string param_value)
			{
				try
				{
					object_parameter_def* param_def =
						new object_parameter_def(param_name , param_value , name);
					params.push_back(param_def);
				}
				catch(...)
				{
					// ���顼����
				}

				return 0;
			}

			object_definition::~object_definition()
			{
				std::vector<object_parameter_def*>::iterator p;

				for(p = params.begin() ; p != params.end() ; p++)
				{
					delete (*p);
				}
			}

			void object_definition::display_definition(void)
			{
				std::vector<object_parameter_def*>::iterator p;
				
				for(p = params.begin() ; p != params.end() ; p++)
				{
					(*p)->display_definition();
				}
				cout << endl << endl;
			}

			
		/*!
		 *  \brief  ���֥�������ID�ֹ�γ��դ�
		 *  \param[in]  api_map   �������˵��Ҥ��줿��ŪAPI����Ͽ��������ƥ�
		 */
		void assign_id( cfg_obj_map obj_def_map , long fixed_id)
		{
		  using namespace toppers;
		  using namespace toppers::oil::oil_definition;

          // modified by takuya 110823
		  //std::map<std::string, std::vector< object_definition* >>::iterator p;
		  std::map<std::string, std::vector< object_definition* > >::iterator p;
		  std::vector<object_definition*>::iterator q;
		  int serial;

		  for(p = obj_def_map.begin() ; p != obj_def_map.end() ; p++)
		  {
			  serial = 0;
			  // ���֥������Ȥ��Ȥ�ID������
			  for(q = (*p).second.begin() ; q != (*p).second.end() ; q++)
			  {
				  if(fixed_id == UINT_MAX)
				  {
					(*q)->set_id(serial++);
				  }
				  else
				  {
					(*q)->set_id(fixed_id);
				  }
			  }
		  }

		}

		cfg_obj_map merge(std::vector<object_definition*> *obj_defs , 
				cfg_obj_map& out , string prefix , string suffix , long fixed_id)
		{
		  std::vector<object_definition*>::iterator p , q;
		  std::vector<object_definition*> *sub_objects;
		  std::vector<object_parameter_def*>::iterator r;
		  std::vector<object_parameter_def*> *subparams;   
		  
		  for(p = obj_defs->begin() ; p != obj_defs->end() ; p++)
		  {
			  string s(prefix + (*p)->get_object_type() + suffix);
			  out[ s ].push_back(*p);
		  }

		  // ID����ٳ��դ���
		  assign_id(out , fixed_id);

		  for(p = obj_defs->begin() ; p != obj_defs->end() ; p++)
		  {
			  long id;
			  subparams = (*p)->get_params();
			  // ���֥ѥ�᡼������Ͽ
			  for(r = subparams->begin() ; r != subparams->end() ; r++)
			  {
				  sub_objects = (*r)->get_subparams();
	   			  id = (*p)->get_id();

				  string s = "." + (*r)->get_value();

				  // ���֥ѥ�᡼���λ���°���ϺƵ�����Ͽ����
				  if(sub_objects->empty() == false)
				  {
					  cfg_obj_map temp;
					  std::string subparam_name = 
						  (*p)->get_object_type() + ".";
					  temp = merge(sub_objects , temp , subparam_name , s , id);

					  // ��̤򥳥ԡ�(���礦�ɤ����᥽�åɤ�̵��)
                      // modified by takuya 110823
					  // std::map< std::string, std::vector< object_definition* >>::iterator x;
					  std::map< std::string, std::vector< object_definition* > >::iterator x;
					  for(x = temp.begin() ; x != temp.end() ; x++ )
					  {
						  std::vector< object_definition* >::iterator y;
						  for(y = (*x).second.begin() ; y != (*x).second.end() ; y++)
						  {
							  out[(*x).first].push_back((*y));
						  }
						  //out[(*x).first] = (*x).second;
						  //out[(*x).first].push_back((*x).second);
					  }
				  }
			  }
		  }

		  return out;
		}
		}
	}	/* oil */

}

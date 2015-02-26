/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2007-2009 by TAKAGI Nobuhisa
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


#ifndef OIL_PARSER_H
#define OIL_PARSER_H

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_error_handling.hpp>
#include <boost/spirit/include/classic_ast.hpp>
#include <boost/spirit/include/classic_functor_parser.hpp>
#include <boost/spirit/include/classic_regex.hpp>
#include <vector>
#include <map>
#include <algorithm>

#include "toppers/text.hpp"
#include "toppers/oil/oil_object.hpp"



using namespace boost::spirit::classic;

namespace toppers
{
	namespace oil
	{
		typedef std::vector<toppers::oil::oil_implementation::oil_object_impl*> oil_impl;
		typedef std::vector<toppers::oil::oil_definition::object_definition*> oil_def;
		
		class oil_parser
		{
			public:
				oil_parser(std::string* txt , std::vector<std::string> const& objlist)
				{
					description = txt;
					param_addable = true;
					m_object_list = objlist;
				}
				~oil_parser()
				{
					std::vector<toppers::oil::oil_implementation::oil_object_impl*>::iterator p;

					for(p = impl_list.begin() ; p != impl_list.end() ; p++)
					{
						delete *p;
					}

					std::vector<toppers::oil::oil_definition::object_definition*>::iterator q;

					for(q = def_list.begin() ; q != def_list.end() ; q++)
					{
						delete *q;
					}
				}
				int do_parse(oil_impl **impl , oil_def **def);
				int start_objimpl_analysis(std::string object_name);
				int start_objdef_analysis(std::string object_name_type);
				int add_parameter_objimpl(std::string parameter);
				int set_nextparam_name(std::string name);
				int add_attr_value(std::string str);
				int end_objimpl_analysis(void);
				int end_objdef_analysis(void);
				void enable_addparam(bool enabled);
				void dump_implementation(void);
				void dump_definition(void);
				void set_error(int position , std::string message);
				void get_error(int *position , std::string *message);

				std::string* get_description(void)
				{
					return description;
				}
				std::vector<std::string> m_object_list;
			protected:
				std::string *description;
				oil_impl impl_list;
				oil_def def_list;
			private:
				toppers::oil::oil_implementation::oil_object_impl* current_impl;
				std::string next_param_name;
				std::string attr_description;
				bool param_addable;
				toppers::oil::oil_definition::object_definition* current_def;
				std::string error_message;
				int error_position;
		};

		// ʸˡ���顼����
		enum oil_grammer_error
		{
			open_brace , close_brace , semicolon , equal , keyword , comma
		};
		// ʸˡ���顼�����
		typedef assertion<oil_grammer_error> oil_assertion;
		typedef boost::spirit::classic::guard<oil_grammer_error> oil_error_guard;
		
		// ���顼�����ϥ�ɥ�
		struct error_handler
		{
			oil_parser* container;
			error_handler(oil_parser* _container) : container(_container)
			{
			}
			template < class Scanner, class oil_grammer_error >
			boost::spirit::classic::error_status<> operator()( Scanner const& scan, oil_grammer_error const& error ) const
			{
				std::string message;
				int pos;
				boost::spirit::classic::error_status<> result =
					boost::spirit::classic::error_status<>( boost::spirit::classic::error_status<>::fail );

				// ���顼�и����֤λ���
				pos = error.where - &((container->get_description()->c_str())[0]);
				
				// ��å���������Ͽ
				switch ( error.descriptor )
				{
				case open_brace:
					message = "missing '{'";
					break;
				case close_brace:
					message = "missing '}'";
					break;
				case semicolon:
					message = "missing ';'";
					break;
				case equal:
					message = "missing '='";
					break;
				case keyword:
					message = "can't use keyword";
					break;
				case comma:
					message = "missing ','";
					break;
				}

				container->set_error(pos , message);
				return result;
			}
		};

		// �ե��󥯥�
		struct match_objimpl_name
		{
			oil_parser* container;
			match_objimpl_name(oil_parser* _container) : container(_container)
			{
			}
			void operator()(char const *first, char const *last) const
			{
				std::string str(first , last);
				std::vector<std::string>::iterator p;
				bool hit = false;

				for(p = container->m_object_list.begin() ; p != container->m_object_list.end() ; p++)
				{
					if(*p == str)
					{
						hit = true;
						break;
					}
				}
				container->start_objimpl_analysis(str);
			}
		};

		struct find_implparam_name
		{
			oil_parser* container;
			find_implparam_name(oil_parser* _container) : container(_container)
			{
			}

			void operator()(char const *first, char const *last) const
			{
				string str(first , last);
				container->set_nextparam_name(str);
			}
		};

		struct match_impl_parameter
		{
			oil_parser* container;
			match_impl_parameter(oil_parser* _container) : container(_container)
			{
			}

			void operator()(char const *first, char const *last) const
			{
				string str(first , last);
				container->add_parameter_objimpl(str);
			}
		};
		
		// ���������Ĥ���̤򸡽Ф���ե��󥯥�
		struct match_objimpl_end
		{
			oil_parser* container;
			match_objimpl_end(oil_parser* _container) : container(_container)
			{
			}

			void operator()(char val) const
			{
				container->end_objimpl_analysis();
			}
		};
		
		// ���֥������������Ƭ�򸡽Ф���ե��󥯥�
		struct match_objdef_name
		{
			oil_parser* container;
			match_objdef_name(oil_parser* _container) : container(_container)
			{
			}
			void operator()(char const *first, char const *last) const
			{
				string str(first , last);
				container->start_objdef_analysis(str);
			}
		};

		// �ѥ�᡼��������ɲä���ե��󥯥�
		struct find_attrname
		{
			oil_parser* container;
			find_attrname(oil_parser* _container) : container(_container)
			{
			}
			void operator()(char const *first, char const *last) const
			{
				string str(first , last);
				container->set_nextparam_name(str);
			}
		};

		// ���֥������������ü�򸡽Ф���ե��󥯥�
		struct match_objdef_end
		{
			oil_parser* container;
			match_objdef_end(oil_parser* _container) : container(_container){}

			void operator()(char val) const
			{
				container->end_objdef_analysis();
			}
		};
		
		// ������Υѥ�᡼�������פ��̤���ե��󥯥�
		struct find_attribute
		{
			oil_parser* container;
			find_attribute(oil_parser* _container) : container(_container)
			{
			}
			void operator()(char const *first, char const *last) const
			{
				string str(first , last);
				container->add_attr_value(str);
			}
		};

		// ������Υѥ�᡼�������פ��̤���(��ư��������)
		struct find_attribute_float
		{
			oil_parser* container;
			find_attribute_float(oil_parser* _container) : container(_container)
			{
			}
			void operator()(double val) const
			{
				char buf[256];
                // modified by takuya 110823
				//sprintf_s(buf , "%lf" , val);
				sprintf(buf , "%lf" , val);
				string str(buf);
				
				container->add_attr_value(str);
			}
		};


		
		// ENUM��Υѥ�᡼��̵�뤹�뤿��Υե��󥯥�
		struct enum_start
		{
			oil_parser* container;
			enum_start(oil_parser* _container) : container(_container){}

			void operator()(char val) const
			{
				container->enable_addparam(false);
			}
		};

		// ENUM��Υѥ�᡼��̵��������뤿��Υե��󥯥�
		struct enum_end
		{
			oil_parser* container;
			enum_end(oil_parser* _container) : container(_container){}

			void operator()(char val) const
			{
				container->enable_addparam(true);
			}
		};
		
		// OIL�ѡ������饹
		struct oil_grammer :  public grammar<oil_grammer>
		{
			oil_parser* m_container;
			oil_grammer(oil_parser* container)
			{
				m_container = container;
			}
			template <typename T> struct definition
			{
				// ʸˡ���顼�������
				oil_assertion assertion_open_brace , assertion_close_brace , assertion_semicolon;
				oil_assertion assertion_equal , assertion_keyword , assertion_comma;
				// ���顼�ϥ�ɥ�����
				oil_error_guard guard_implementation , guard_object , guard_object_def;

				// BNF
				rule<T> file;
				rule<T> oil_version , implementation_definition , application_definition;
				rule<T> implementation_spec_list , implementation_spec , implementation_def;
				rule<T> object , object_ref_type , object_name , object_temp;
				
				rule<T> name , null_str , boolean , string_literal;
				rule<T> multiple_specifier , auto_specifier;
				rule<T> number_range , number_list , number , float_range , default_number , default_float;
				rule<T> attribute_name;
				rule<T> default_string , default_bool , default_name;
				rule<T> bool_values;
				rule<T> enumerator , enumeration , enumerator_list;
				
				rule<T> impl_parameter_list;
				
				rule<T> uint32_impl_attr_def , int32_impl_attr_def , uint64_impl_attr_def , int64_impl_attr_def;
				rule<T> float_impl_attr_def , string_impl_attr_def , bool_impl_attr_def , enum_impl_attr_def;
				rule<T> reference_name;
				rule<T> impl_attr_def , impl_ref_def;
				
				rule<T> object_definition;
				rule<T> parameter , attribute_value;

				definition(oil_grammer const& self) :
					assertion_open_brace(open_brace) ,
					assertion_close_brace(close_brace) ,
					assertion_semicolon(semicolon) ,
					assertion_equal(equal) ,
					assertion_keyword(keyword) ,
					assertion_comma(comma)
				{
					// ����ط�
					null_str = str_p("");
					name = (alpha_p | ch_p('_')) >> +(alnum_p | ch_p('_'));
					string_literal = ch_p('"') >> name >> ch_p('"');
					multiple_specifier = !(ch_p('[') >> ch_p(']'));
					auto_specifier = !str_p("WITH_AUTO");
					number = (str_p("0x") >> +xdigit_p) | (str_p("0X") >> xdigit_p) | int_p | uint_p;
					boolean = str_p("TRUE") | str_p("FALSE");
					
					// ��󥸡��ǥե������
					number_list = ch_p('[') >> number >> *(ch_p(',') >> number) >> ch_p(']');
					number_range = !((ch_p('[') >> number >> str_p("..") >> number >> ch_p(']'))
									| number_list);
					default_number = !((ch_p('=') >> number)
										| (ch_p('=') >> str_p("NO_DEFAULT"))
										| (ch_p('=') >> str_p("AUTO")));
					float_range = !(ch_p('[') >> real_p >> str_p("..") >> real_p >> ch_p(']'));
					default_float = !((ch_p('=') >> real_p)
										| (ch_p('=') >> str_p("NO_DEFAULT"))
										| (ch_p('=') >> str_p("AUTO")));
					
					enumerator = name >> !(ch_p('{') >> implementation_def >> ch_p('}'));
					enumerator_list = enumerator >> *(ch_p(',') >> enumerator);
					enumeration = ch_p('[')[enum_start(self.m_container)] >> 
										enumerator_list >> ch_p(']')[enum_end(self.m_container)];

					default_name = !((ch_p('=') >> name)
										| (ch_p('=') >> str_p("NO_DEFAULT"))
										| (ch_p('=') >> str_p("AUTO")));
					
					attribute_name = name | object;
					attribute_value = (boolean >> !(ch_p('{')[enum_start(self.m_container)] >>
											*parameter >> (ch_p('}')[enum_end(self.m_container)])))
											[find_attribute(self.m_container)]
										| number[find_attribute(self.m_container)]
										| real_p[find_attribute_float(self.m_container)]
										| string_literal[find_attribute(self.m_container)]
										/* 
                                         * modified by takuya 110823
                                         * AUTO�ϲ�����������Ѳ�ǽ
                                         */
										| (name >> !(ch_p('{')[enum_start(self.m_container)] >>
											*parameter >> ch_p('}')[enum_end(self.m_container)]))
											[find_attribute(self.m_container)];

					default_string = !((ch_p('=') >> ch_p('"') >> name >> ch_p('"'))
										| (ch_p('=') >> str_p("NO_DEFAULT"))
										| (ch_p('=') >> str_p("AUTO")));
					default_bool = !((ch_p('=') >> boolean)
										| (ch_p('=') >> str_p("NO_DEFAULT"))
										| (ch_p('=') >> str_p("AUTO")));
					bool_values = !(ch_p('[')[enum_start(self.m_container)] >>
											str_p("TRUE") >> !(ch_p('{') >> implementation_def >> ch_p('}')) >>
									ch_p(',') >>
											str_p("FALSE") >> !(ch_p('{') >> implementation_def >> ch_p('}')) >>
									ch_p(']')[enum_end(self.m_container)]);

					std::vector<std::string>::iterator p;
					std::string objtype = "(" , objref = "(";
					
					// ����ɽ���Υꥹ�Ȥ����
					for(p = self.m_container->m_object_list.begin() ; p != self.m_container->m_object_list.end() ; p++)
					{
						objtype += (*p) + "|";
						objref += (*p) + "_TYPE" + "|";
					}
					
					objtype[objtype.size() - 1] = ')';
					objref[objref.size() - 1] = ')';

					object = regex_p(objtype.c_str());
					object_ref_type = regex_p(objref.c_str());
					
					// ���֥����������
					parameter = attribute_name[find_attrname(self.m_container)] >>
								assertion_equal(ch_p("=")) >> attribute_value >>
								assertion_semicolon(ch_p(";"));
					object_name = (object >> name)[match_objdef_name(self.m_container)];
					object_definition = guard_object(
											object_name >> assertion_open_brace(ch_p('{')) >> 
											*parameter >> assertion_close_brace(ch_p('}')) >> 
											assertion_semicolon(ch_p(';'))[match_objdef_end(self.m_container)])
											[error_handler(self.m_container)];

					// ���̤Υѥ�᡼�������
					uint32_impl_attr_def = str_p("UINT32") >> auto_specifier >> number_range >>
										attribute_name[find_implparam_name(self.m_container)] >> 
										multiple_specifier >> default_number >> 
										assertion_semicolon(ch_p(';'));
					int32_impl_attr_def = str_p("INT32") >> auto_specifier  >> number_range >> 
										attribute_name[find_implparam_name(self.m_container)] >>
										multiple_specifier >> default_number >>
										assertion_semicolon(ch_p(';'));
					uint64_impl_attr_def = str_p("UINT64") >> auto_specifier  >> number_range >> 
										attribute_name[find_implparam_name(self.m_container)] >>
										multiple_specifier >> default_number >>
										assertion_semicolon(ch_p(';'));
					int64_impl_attr_def = str_p("INT64") >> auto_specifier  >> number_range >> 
										attribute_name[find_implparam_name(self.m_container)] >>
										multiple_specifier >> default_number >>
										assertion_semicolon(ch_p(';'));
					float_impl_attr_def = str_p("FLOAT") >> auto_specifier  >> float_range >> 
										attribute_name[find_implparam_name(self.m_container)] >>
										multiple_specifier >> default_float >>
										assertion_semicolon(ch_p(';'));
					string_impl_attr_def = str_p("STRING") >> auto_specifier >> 
										attribute_name[find_implparam_name(self.m_container)] >>
										multiple_specifier >> default_string >>
										assertion_semicolon(ch_p(';'));
					bool_impl_attr_def = str_p("BOOLEAN") >>
										auto_specifier >> bool_values >>
										attribute_name[find_implparam_name(self.m_container)] >>
										multiple_specifier >> default_bool >>
										assertion_semicolon(ch_p(';'));
					enum_impl_attr_def = str_p("ENUM") >>
										auto_specifier >> enumeration >>
										attribute_name[find_implparam_name(self.m_container)] >>
										multiple_specifier >> default_name >>
										assertion_semicolon(ch_p(';'));

					// °����
					impl_attr_def = uint32_impl_attr_def | int32_impl_attr_def
									| uint64_impl_attr_def | int64_impl_attr_def
									| float_impl_attr_def | string_impl_attr_def
									| bool_impl_attr_def | enum_impl_attr_def;
					
					reference_name = name | object;
					impl_ref_def = object_ref_type >> reference_name[find_implparam_name(self.m_container)] >>
									multiple_specifier >> assertion_semicolon(ch_p(';'));
					
					// �ѥ�᡼���η���
					implementation_def = *((impl_attr_def | impl_ref_def)
												[match_impl_parameter(self.m_container)]);

					// �������
					application_definition = 
							str_p("CPU") >> name >> ch_p('{') >> 
							*object_definition >> ch_p('}') >> ch_p(';');

					// �礭��ñ�̤�ʸˡ
					implementation_spec = 
						guard_object(object[match_objimpl_name(self.m_container)] >>
										assertion_open_brace(ch_p('{')) >>
										implementation_def >>
										assertion_close_brace(ch_p('}')) >>
										assertion_semicolon(ch_p(';')[match_objimpl_end(self.m_container)]))
										[error_handler(self.m_container)];
					implementation_spec_list = *implementation_spec;
					
					implementation_definition = "IMPLEMENTATION" >> name >> ch_p('{')
						>> implementation_spec_list >> ch_p('}') >> ch_p(';');

					oil_version = str_p("OIL_VERSION") 
								>> ch_p('=') >> ch_p('\"') >> real_p >> ch_p('\"') >> ch_p(';');	//
					file = oil_version >> implementation_definition >> application_definition >> *space_p;
				};
				rule<T> const& start() const
				{
					return file;                    // ��������롼����֤�
				}
			};
			
		};


	}
}

#endif	/* OIL_PARSER_H */

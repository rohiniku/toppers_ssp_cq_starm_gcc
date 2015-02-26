/* 
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *  
 *  Copyright (C) 2007-2012 by TAKAGI Nobuhisa
 *  Copyright (C) 2011-2014 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2014 by FUJISOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by Spansion LLC, USA
 *  Copyright (C) 2011-2013 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2014 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2014 by TOSHIBA CORPOTATION, JAPAN
 *  Copyright (C) 2011-2014 by Witz Corporation, JAPAN
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
 *  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
 *  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
 *  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
 *  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  $Id: cfg1_out.hpp 179 2014-03-17 05:01:16Z nces-mtakada $
 */

/*!
 *  \file   toppers/xml/cfg1_out.hpp
 *  \brief  cfg1_out.c/.srec �ե�����򰷤������������
 *
 *  ���Υե�������������륯�饹
 *  \code
 *  class cfg1_out;
 *  \endcode
 */
#ifndef TOPPERS_XML_CFG1_OUT_HPP_
#define TOPPERS_XML_CFG1_OUT_HPP_

#include <string>
#include <vector>
#include <map>
#include "toppers/workaround.hpp"
#include "toppers/codeset.hpp"
#include "toppers/xml/xml_object.hpp"

namespace toppers
{

  class macro_processor;
  class s_record;
  class nm_symbol;

  namespace xml
  {

    /*!
     *  \class  cfg1_out  cfg1_out.hpp  "toppers/xml/cfg1_out.hpp"
     *  \brief  cfg1_out.c/.srec �ե�����������饹
     */
    class cfg1_out
    {
    public:
      struct cfg1_def_t
      {
        bool is_signed;
        std::string name;
        std::string expression;
        std::string value1;
        std::string value2;
      };
      typedef std::map< std::string, std::vector< toppers::xml::container::object* > > xml_obj_map; //Ϣ��������Ϥ���������󤷤�����
      typedef xml_obj_map cfg_element_map;
      typedef std::vector< cfg1_def_t > cfg1_def_table;

      struct multi_info
      {
        unsigned int multiplicity;
        std::vector< std::string > shortname;
      };
      typedef std::map< std::string, multi_info > t_multi_info_map;

      //std::vector< toppers::xml::container::object* > container_array; /*  xml����ѡ����������ǡ��� only xml */
      void del_containers();

      explicit cfg1_out( std::string const& filename, cfg1_def_table const* def_table = 0 );
      cfg1_out( cfg1_out const& other );
      virtual ~cfg1_out();
      cfg1_out& operator = ( cfg1_out const& other )
      {
        cfg1_out t( other );
        swap( t );
        return *this;
      }

      void load_cfg( std::string const& input_file, codeset_t codeset, std::map<std::string, toppers::xml::info> const& info_map );
      void generate( char const* type = 0 ) const;
      std::string const& get_includes() const;

      void load_srec();
      std::tr1::shared_ptr< s_record > get_srec() const;
      std::tr1::shared_ptr< nm_symbol > get_syms() const;
      cfg1_def_table const* get_def_table() const;
      xml_obj_map merge(std::map<std::string, toppers::xml::info> const& info_map ) const;
      void do_sub_siblings(std::vector< toppers::xml::container::object* > objects, int siblings) const;
      xml_obj_map do_merge(std::vector< toppers::xml::container::object* >, std::map<std::string, toppers::xml::info> const& info_map ) const;
      void do_sub_merge(std::vector< toppers::xml::container::object* > objects, xml_obj_map & xml_map, std::map<std::string, toppers::xml::info> const& info_map ) const;
      string replase_xml_pathname(std::vector< toppers::xml::container::object* >::iterator pObj, std::map<std::string, toppers::xml::info> const& info_map ) const;
      string search_info_pathname(string shortname) const;

      bool is_little_endian() const;

      void swap( cfg1_out& other )
      {
        implementation* t = pimpl_;
        pimpl_ = other.pimpl_;
        other.pimpl_ = t;
      }
      void swap(xml_obj_map& other)
      {
      }

      static std::tr1::int32_t make_signed( std::tr1::uint32_t value )
      {
        std::tr1::int32_t result;
        if ( ( value >> 31 ) != 0 )
        {
          result = -static_cast< std::tr1::int32_t >( ( value ^ 0xffffffff ) + 1 ); // 2�����ɽ���ˤ����б����ʤ�
        }
        else
        {
          result = static_cast< std::tr1::int32_t >( value );
        }
        return result;
      }

      static std::vector< toppers::xml::container::object* > xml_parser_init(std::string input_file);

    protected:
      struct implementation;
      explicit cfg1_out( implementation* pimpl ) : pimpl_( pimpl ) {}
    private:
      implementation* pimpl_;
    };

  }
}

#endif  /* TOPPERS_XML_CFG1_OUT_HPP_ */

/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2007-2012 by TAKAGI Nobuhisa
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
/*!
 *  \file   toppers/oil/cfg1_out.hpp
 *  \brief  cfg1_out.c/.srec �ե�����򰷤������������
 *
 *  ���Υե�������������륯�饹
 *  \code
 *  class cfg1_out;
 *  \endcode
 */
#ifndef TOPPERS_OIL_CFG1_OUT_HPP_
#define TOPPERS_OIL_CFG1_OUT_HPP_

#include <string>
#include <vector>
#include <map>
#include "toppers/workaround.hpp"
#include "toppers/codeset.hpp"
#include "toppers/oil/oil_object.hpp"

namespace toppers
{

  class macro_processor;
  class s_record;
  class nm_symbol;

  namespace oil
  {
	  using namespace toppers::oil::oil_definition;

    /*!
     *  \class  cfg1_out  cfg1_out.hpp  "toppers/oil/cfg1_out.hpp"
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
      typedef std::map< std::string, std::vector< object_definition* > > cfg_obj_map;
      typedef cfg_obj_map cfg_element_map;
      typedef std::vector< cfg1_def_t > cfg1_def_table;

      explicit cfg1_out( std::string const& filename, cfg1_def_table const* def_table = 0 );
      cfg1_out( cfg1_out const& other );
      virtual ~cfg1_out();
      cfg1_out& operator = ( cfg1_out const& other )
      {
        cfg1_out t( other );
        swap( t );
        return *this;
      }

      void load_cfg( std::string const& input_file, codeset_t codeset, std::vector<std::string> const& obj_info );
      void generate( char const* type = 0 ) const;
      std::string const& get_includes() const;

      void load_srec();
      std::tr1::shared_ptr< s_record > get_srec() const;
      std::tr1::shared_ptr< nm_symbol > get_syms() const;
      cfg1_def_table const* get_def_table() const;
      cfg_obj_map merge(void) const;
      bool is_little_endian() const;

      void swap( cfg1_out& other )
      {
        implementation* t = pimpl_;
        pimpl_ = other.pimpl_;
        other.pimpl_ = t;
      }
      void swap(cfg_obj_map& other)
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

      static void load_id_input_file( std::map< std::string, std::pair< long, bool > >& id_map );

    protected:
      struct implementation;
      explicit cfg1_out( implementation* pimpl ) : pimpl_( pimpl ) {}
    private:
      implementation* pimpl_;
    };

  }
}

#endif  // ! TOPPERS_OIL_CFG1_OUT_HPP_

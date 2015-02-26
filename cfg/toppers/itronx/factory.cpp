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
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "toppers/misc.hpp"
#include "toppers/global.hpp"
#include "toppers/csv.hpp"
#include "toppers/nm_symbol.hpp"
#include "toppers/s_record.hpp"
#include "toppers/diagnostics.hpp"
#include "toppers/macro_processor.hpp"
#include "toppers/io.hpp"
#include "toppers/cpp.hpp"
#include "toppers/itronx/factory.hpp"
#include "toppers/itronx/cfg1_out.hpp"

namespace toppers
{
  namespace itronx
  {
    namespace
    {
      /*!
       *  \brief  ���֥�������ID�ֹ�γ��դ�
       *  \param[in]  api_map   �������˵��Ҥ��줿��ŪAPI����Ͽ��������ƥ�
       */
      void assign_id( toppers::itronx::cfg1_out::static_api_map& api_map )
      {
        using namespace toppers;
        using namespace toppers::itronx;

        std::string id_input_file( get_global_string( "id-input-file" ) );
        if ( id_input_file.empty() )  // --id-input-file ���ץ���󤬻��ꤵ��Ƥ��ʤ����...
        {
          for ( cfg1_out::static_api_map::iterator iter( api_map.begin() ), last( api_map.end() );
                iter != last;
                ++iter )
          {
            static_api::assign_id( iter->second.begin(), iter->second.end() );
          }
        }
        else  // --id-input-file ���ץ���󤬻��ꤵ��Ƥ�����...
        {
          typedef std::map< std::string, std::pair< long, bool > > id_map_t;
          id_map_t id_map;
          std::ifstream ifs( id_input_file.c_str() );
          while ( ifs )
          {
            std::string linebuf;
            std::getline( ifs, linebuf );
            if ( ifs.bad() )
            {
              fatal( _( "I/O error" ) );
            }
            if ( linebuf.empty() || linebuf == "\r" )
            {
              break;
            }

            std::istringstream iss( linebuf );
            std::string name;
            iss >> name;
            if ( iss.fail() )
            {
              fatal( _( "id file `%1%\' is invalid" ), id_input_file );
            }

            long value;
            iss >> value;
            if ( iss.fail() )
            {
              fatal( _( "id file `%1%\' is invalid" ), id_input_file );
            }

            if ( id_map.find( name ) != id_map.end() )
            {
              fatal( _( "E_OBJ: `%1%\' is duplicated" ), name );
            }
            else
            {
              id_map[ name ] = std::make_pair( value, false );
            }
          }

          for ( cfg1_out::static_api_map::iterator iter( api_map.begin() ), last( api_map.end() );
                iter != last;
                ++iter )
          {
            for ( std::vector< static_api >::iterator iter2( iter->second.begin() ), last2( iter->second.end() );
                  iter2 != last2;
                  ++iter2 )
            {
              static_api::info const* info = iter2->get_info();
              if ( info->id_pos >= 0 )
              {
                std::string name( iter2->at( info->id_pos ).text );
                std::string symbol( iter2->at( info->id_pos ).symbol );
                if ( !info->slave && symbol[0] == '#' )
                {
                  id_map_t::iterator hit( id_map.find( name ) );
                  if ( hit != id_map.end() )
                  {
                    long id_value = hit->second.first;
                    if ( id_value > 0 )
                    {
                      iter2->at( info->id_pos ).value = id_value;
                      hit->second.second = true;
                    }
                  }
                }
              }
            }
            static_api::assign_id( iter->second.begin(), iter->second.end() );
          }

          for ( id_map_t::const_iterator iter( id_map.begin() ), last( id_map.end() ); iter != last; ++iter )  // �Ĥ�ʪ�������...
          {
            if ( !iter->second.second )
            {
              warning( _( "object identifier `%1%\' is not used" ), iter->first );
            }
          }
        }

        // --id-output-file ���ץ���󤬻��ꤵ��Ƥ�����
        std::string id_output_file( get_global_string ( "id-output-file" ) );
        if ( !id_output_file.empty() )
        {
          std::ofstream ofs( id_output_file.c_str() );
          for ( cfg1_out::static_api_map::iterator iter( api_map.begin() ), last( api_map.end() );
            iter != last;
            ++iter )
          {
            for ( std::vector< static_api >::const_iterator iter2( iter->second.begin() ), last2( iter->second.end() );
                  iter2 != last2;
                  ++iter2 )
            {
              static_api::info const* info = iter2->get_info();
              if ( info->id_pos >= 0 )
              {
                std::string name( iter2->at( info->id_pos ).text );
                std::string symbol( iter2->at( info->id_pos ).symbol );
                if ( !info->slave && symbol[0] == '#' )
                {
                  ofs << name << '\t' << iter2->at( info->id_pos ).value.get() << std::endl;
                }
              }
            }
          }
        }
      }

      // �����ͥ륪�֥��������������������ŪAPI�γƥѥ�᡼����ޥ���ץ��å����ѿ��Ȥ������ꤹ�롣
      void set_object_vars( cfg1_out::static_api_map const& api_map, macro_processor& mproc )
      {
        typedef macro_processor::element element;
        typedef macro_processor::var_t var_t;
        std::map< std::string, var_t > order_list_map;
        std::map< std::string, long > id_map;

        for ( cfg1_out::static_api_map::const_iterator m_iter( api_map.begin() ), m_last( api_map.end() );
              m_iter != m_last;
              ++m_iter )
        {
          int order = 1;

          for ( std::vector< static_api >::const_iterator v_iter( m_iter->second.begin() ), v_last( m_iter->second.end() );
                v_iter != v_last;
                ++v_iter )
          {
            static_api::info const* info = v_iter->get_info();

            long id = -1;
            if ( !info->slave )
            {
              // �и��� $OBJ.ORDER$
              if ( v_iter->id().value )
              {
                id = static_cast< long >( v_iter->id().value.get() );
              }
              else
              {
                id = order;
              }
              id_map[ v_iter->id().text ] = id;
              element e;
              e.i = order;
              mproc.set_var( toppers::toupper( ( boost::format( "%s.order" ) % info->type ).str() ), id, var_t( 1, e ) );

              e.i = id;
              e.s = v_iter->id().text;
              order_list_map[ info->type ].push_back( e );
              ++order;
            }
            else
            {
              std::map< std::string, long >::iterator iter( id_map.find( v_iter->id().text ) );
              if ( iter == id_map.end() )
              {
                error( v_iter->line(), _( "E_NOEXS: `%1%\' is undefined" ), v_iter->id().text );
              }
              else
              {
                id = iter->second;
              }
            }

            // �ƥѥ�᡼��
            var_t var;
            std::string prev_name;
            for ( static_api::const_iterator api_iter( v_iter->begin() ), api_last( v_iter->end() );
                  api_iter != api_last;
                  ++api_iter )
            {
              bool is_param_list = false;

              char const* type_name = ( api_iter->symbol[0] == '*'  && info->slave ) ? info->api_name : info->type;
              std::string name( toppers::toupper( ( boost::format( "%s.%s" ) % type_name % ( api_iter->symbol.c_str() + 1 ) ).str() ) );
              // ������ ? �����
              if ( *name.rbegin() == '\?' ) 
              {
                name.resize( name.size() - 1 );
              }
              // ������ ... �����
              if ( name.size() > 3 && name.substr( name.size() - 3 ) == "..." )
              {
                name.resize( name.size() - 3 );
                is_param_list = true;
              }

              if (!var.empty())
              {
                if (prev_name != name)
                {
                  var.clear();
                }
              }

              element e;
              e.s = api_iter->text; // �������λ���
              if ( api_iter->symbol[0] != '&' )   // ����������ѥ�᡼�����ͤ�����Ǥ��ʤ�
              {
                if ( api_iter->symbol[0] == '$' )  // ʸ����������ѥ�᡼��
                {
                  e.v = api_iter->string; // Ÿ�����ʸ����
                }
                else
                {
                  e.i = api_iter->value;
                }
                if ( api_iter->symbol[0] == '%' )
                {
                  continue;
                }
              }
              var.push_back(e);
              mproc.set_var( name, id, var );

              prev_name = name;

              // ���̸ߴ����Τ��ᡢsymbol + order ̾���ѿ�����Ͽ
              if (is_param_list)
              {
                mproc.set_var( name + boost::lexical_cast< std::string >( api_iter->order ), id, var_t( 1, e ) );
              }
            }

            // ��ŪAPI��̾��
            if ( !info->slave ) {
              element e;
              e.s = info->api_name;
              std::string type( toppers::toupper( info->type ) );
              mproc.set_var( type + ".APINAME", id, var_t( 1, e ) );
            }

            // ��ŪAPI���и��������ֹ�
            {
              element e;
              e.s = v_iter->line().file;
              e.i = v_iter->line().line;
              std::string type( toppers::toupper( info->slave ? info->api_name : info->type ) );
              mproc.set_var( type + ".TEXT_LINE", id, var_t( 1, e ) );
            }
          }
        }

        std::map< std::string, var_t > id_list_map;

        for ( std::map< std::string, var_t >::const_iterator iter( order_list_map.begin() ), last( order_list_map.end() );
              iter != last;
              ++iter )
        {
          // �и���ꥹ�� $OBJ.ORDER_LIST$ -- ID�ֹ���¤�
          mproc.set_var( toppers::toupper( iter->first + ".order_list" ), iter->second );
          var_t rorder_list( iter->second );

          // �ս�ꥹ�� $OBJ.RORDER_LIST$ -- ID�ֹ���¤�
          std::reverse( rorder_list.begin(), rorder_list.end() );
          mproc.set_var( toppers::toupper( iter->first + ".rorder_list" ), rorder_list );

          // ID�ֹ�ꥹ�� $OBJ.ID_LIST$ -- ID�ֹ���¤�
          var_t id_list( iter->second );
          std::sort( id_list.begin(), id_list.end() );
          mproc.set_var( toppers::toupper( iter->first + ".id_list" ), id_list );
        }

        element external_id;
        external_id.i = get_global< bool >( "external-id" );
        mproc.set_var( "USE_EXTERNAL_ID", var_t( 1, external_id ) );
      }

      // �����ͥ륪�֥��������������������ŪAPI�γƥѥ�᡼����ޥ���ץ��å����ѿ��Ȥ������ꤹ�롣
      void set_object_vars( std::vector< static_api > const& api_array, macro_processor& mproc )
      {
        typedef macro_processor::element element;
        typedef macro_processor::var_t var_t;
        long order = 1;
        var_t order_list;

        for ( std::vector< static_api >::const_iterator v_iter( api_array.begin() ), v_last( api_array.end() );
              v_iter != v_last;
              ++v_iter )
        {
          static_api::info const* info = v_iter->get_info();
          var_t params;
          var_t args;

          // ��ŪAPI���и��������ֹ�
          element e;
          e.s = v_iter->line().file;
          e.i = v_iter->line().line;
          mproc.set_var( "API.TEXT_LINE", order, var_t( 1, e ) );

          // ��ŪAPI̾
          e.s = info->api_name;
          e.i = boost::none;
          mproc.set_var( "API.NAME", order, var_t( 1, e ) );

          // ���֥������ȥ����ס�"TSK", "SEM", ...��
          e.s = toppers::toupper( info->type );
          mproc.set_var( "API.TYPE", order, var_t( 1 , e ) );

          // �ƥѥ�᡼��
          for ( static_api::const_iterator api_iter( v_iter->begin() ), api_last( v_iter->end() );
                api_iter != api_last;
                ++api_iter )
          {
            std::string name( toppers::toupper( ( boost::format( "%s.%s" ) % info->type % ( api_iter->symbol.c_str() + 1 ) ).str() ) );
            // ������ ? �����
            if ( *name.rbegin() == '\?' ) 
            {
              name.resize( name.size() - 1 );
            }
            // ������ ... ����� & order ���ղ�
            if ( name.size() > 3 && name.substr( name.size() - 3 ) == "..." )
            {
              name.resize( name.size() - 3 );
              name += boost::lexical_cast< std::string >( api_iter->order );
            }

            element e;
            e.s = api_iter->text; // �������λ���
            if ( api_iter->symbol[0] != '&' )   // ����������ѥ�᡼�����ͤ�����Ǥ��ʤ�
            {
              if ( api_iter->symbol[0] == '$' )  // ʸ����������ѥ�᡼��
              {
                e.v = api_iter->string; // Ÿ�����ʸ����
              }
              else
              {
                e.i = api_iter->value;
              }
            }
            args.push_back( e );

            e.s = name;
            e.i = boost::none;
            params.push_back( e );

            if ( api_iter->symbol[0] == '%' )
            {
              continue;
            }
          }
          mproc.set_var( "API.ARGS", order, args );
          mproc.set_var( "API.PARAMS", order, params );
          e.s.clear();
          e.i = order;
          order_list.push_back( e );
          ++order;
        }
        mproc.set_var( "API.ORDER_LIST", order_list );

        element external_id;
        external_id.i = get_global< bool >( "external-id" );
        mproc.set_var( "USE_EXTERNAL_ID", var_t( 1, external_id ) );
      }

      // ���饹ID�ꥹ�Ȥ�ޥ���ץ��å����ѿ��Ȥ������ꤹ�롣
      void set_clsid_vars( std::vector< std::pair< std::string, long > > const& table, cfg1_out const& cfg1out, macro_processor& mproc )
      {
        if ( cfg1out.get_def_table() == 0 )
        {
          return;
        }

        typedef macro_processor::element element;
        macro_processor::var_t var;

        bool little_endian = cfg1out.is_little_endian();
        nm_symbol::entry nm_entry = cfg1out.get_syms()->find( "TOPPERS_cfg_sizeof_signed_t" );
        std::size_t sizeof_signed_t = static_cast< std::size_t >( cfg1out.get_srec()->get_value( nm_entry.address, 4, little_endian ) );

        for ( std::vector< std::pair< std::string, long > >::const_iterator iter( table.begin() ), last( table.end() );
              iter != last;
              ++iter )
        {
          if ( !iter->first.empty() )
          {
            element e;
            e.s = iter->first;

            std::string symbol = "TOPPERS_cfg_valueof_" + iter->first;
            nm_symbol::entry nm_entry = cfg1out.get_syms()->find( symbol );
            if ( nm_entry.type == -1 )
            {
              continue;
            }
            const std::size_t size = sizeof_signed_t;
            std::tr1::intmax_t value = cfg1out.get_srec()->get_value( nm_entry.address, size, little_endian );

            e.i = value;

            var.push_back( e );
          }
        }
        // ���饹ID���ͤǥ����Ȥ��Ƥ��ʤ�
        mproc.set_var( "CLS.ID_LIST", var );
      }

      // �ɥᥤ��ID�ꥹ�Ȥ�ޥ���ץ��å����ѿ��Ȥ������ꤹ�롣
      void set_domid_vars( std::vector< std::pair< std::string, long > > const& table, macro_processor& mproc )
      {
        typedef macro_processor::element element;
        macro_processor::var_t var;

        for ( std::vector< std::pair< std::string, long > >::const_iterator iter( table.begin() ), last( table.end() );
              iter != last;
              ++iter )
        {
          if ( !iter->first.empty() )
          {
            element e;
            e.s = iter->first;
            e.i = iter->second;
            var.push_back( e );
          }
        }
        mproc.set_var( "DOM.ID_LIST", var );
      }

      // �ץ�åȥե����ࡦ����ѥ����¸���ͤ�ޥ���ץ��å����ѿ��Ȥ������ꤹ�롣
      void set_platform_vars( cfg1_out const& cfg1out, macro_processor& mproc )
      {
        typedef macro_processor::element element;
        typedef macro_processor::var_t var_t;

        cfg1_out::cfg1_def_table const* def_table = cfg1out.get_def_table();
        if ( def_table == 0 )
        {
          return;
        }
        std::size_t sizeof_signed_t;
        std::size_t sizeof_pointer;

        static cfg1_out::cfg1_def_t const limit_defs[] =
        {
          { false, "TOPPERS_cfg_CHAR_BIT",  "CHAR_BIT" },
          { false, "TOPPERS_cfg_CHAR_MAX",  "CHAR_MAX" },
          { true, "TOPPERS_cfg_CHAR_MIN",  "CHAR_MIN" },
          { false, "TOPPERS_cfg_SCHAR_MAX", "SCHAR_MAX" },  // ���������դ���������ˤʤ뤳�ȤϤʤ�
          { false, "TOPPERS_cfg_SHRT_MAX",  "SHRT_MAX" },   // ���������դ���������ˤʤ뤳�ȤϤʤ�
          { false, "TOPPERS_cfg_INT_MAX",   "INT_MAX" },    // ���������դ���������ˤʤ뤳�ȤϤʤ�
          { false, "TOPPERS_cfg_LONG_MAX",  "LONG_MAX" },   // ���������դ���������ˤʤ뤳�ȤϤʤ�
        };

        nm_symbol::entry nm_entry = cfg1out.get_syms()->find( "TOPPERS_cfg_sizeof_signed_t" );
        sizeof_signed_t = static_cast< std::size_t >( cfg1out.get_srec()->get_value( nm_entry.address, 4, cfg1out.is_little_endian() ) );

        nm_entry = cfg1out.get_syms()->find( "TOPPERS_cfg_sizeof_pointer" );
        sizeof_pointer = static_cast< std::size_t >( cfg1out.get_srec()->get_value( nm_entry.address, 4, cfg1out.is_little_endian() ) );

        for ( std::size_t i = 0; i < sizeof limit_defs / sizeof limit_defs[ 0 ]; ++i )
        {
          element e;
          e.s = limit_defs[ i ].expression;
          nm_entry = cfg1out.get_syms()->find( limit_defs[ i ].name );
          std::tr1::int64_t value = cfg1out.get_srec()->get_value( nm_entry.address, sizeof_signed_t, cfg1out.is_little_endian() );
          if ( sizeof_signed_t < 8 && limit_defs[ i ].is_signed )
          {
            value = cfg1_out::make_signed( static_cast< std::tr1::uint32_t >( value ) );
          }
          mproc.set_var( e.s, var_t( 1, e ) );
        }

        for ( cfg1_out::cfg1_def_table::const_iterator iter( def_table->begin() ), last( def_table->end() );
              iter != last;
              ++iter )
        {
          element e;
          std::tr1::int64_t value;

          nm_entry = cfg1out.get_syms()->find( "TOPPERS_cfg_" + iter->name );
          if ( nm_entry.type >= 0 )
          {
            if ( !iter->expression.empty() && iter->expression[ 0 ] == '@' )  // ����'@'�ǻϤޤ���ϥ��ɥ쥹�����
            {
              value = cfg1out.get_srec()->get_value( nm_entry.address, sizeof_pointer, cfg1out.is_little_endian() );
              if ( sizeof_signed_t < 8 && iter->is_signed )
              {
                value = cfg1_out::make_signed( static_cast< std::tr1::uint32_t >( value ) );
              }

              // ��ۤɼ��Ф������ɥ쥹��Ȥäƴ��ܻ���
              value = cfg1out.get_srec()->get_value( value, 8, cfg1out.is_little_endian() );  // ���Ф��ͤϷ��˴ط��ʤ����8�Х���
              if ( sizeof_signed_t < 8 && iter->is_signed )
              {
                value = cfg1_out::make_signed( static_cast< std::tr1::uint32_t >( value ) );
              }
              e.s = iter->expression.c_str() + 1; // ��Ƭ��'@'�����
            }
            else  // ���ɥ쥹�ǤϤʤ��̾�����������
            {
              value = cfg1out.get_srec()->get_value( nm_entry.address, sizeof_signed_t, cfg1out.is_little_endian() );
              if ( sizeof_signed_t < 8 && iter->is_signed )
              {
                value = cfg1_out::make_signed( static_cast< std::tr1::uint32_t >( value ) );
              }
              e.s = iter->expression;
            }
            e.i = value;
            mproc.set_var( iter->name, var_t( 1, e ) );
          }
        }

        // �Х��ȥ�������
        {
          bool little_endian = cfg1out.is_little_endian();
          element e;
          e.i = little_endian;
          mproc.set_var( "LITTLE_ENDIAN", var_t( 1, e ) );

          e.i = !little_endian;
          mproc.set_var( "BIG_ENDIAN", var_t( 1, e ) );
        }
      }

    }

    //! ���󥹥ȥ饯��
    factory::factory( std::string const& kernel )
      : kernel_( tolower( kernel ) )
    {
    }

    //! �ǥ��ȥ饯��
    factory::~factory()
    {
    }

    std::auto_ptr< macro_processor > factory::create_macro_processor( cfg1_out const& cfg1out ) const
    {
      cfg1_out::static_api_map api_map( cfg1out.merge() );
      assign_id( api_map );
      return do_create_macro_processor( cfg1out, api_map );
    }

    //! ���ݡ��Ȥ��Ƥ�����ŪAPI����μ���
    std::map< std::string, static_api::info > const* factory::get_static_api_info_map() const
    {
      // CSV������ŪAPI������ɤ߼�ꡢ��Ͽ���뤿��Υ����륯�饹
      struct init_t
      {
        init_t()
        {
          boost::any t = global( "api-table" );
          if ( !t.empty() )
          {
            std::vector< std::string > api_tables( boost::any_cast< std::vector< std::string >& >( t ) );
            for ( std::vector< std::string >::const_iterator iter( api_tables.begin() ), last( api_tables.end() );
                  iter != last;
                  ++iter )
            {
              std::string buf;
              std::string api_table_filename = *iter;
              read( api_table_filename.c_str(), buf );
              csv data( buf.begin(), buf.end() );
              for ( csv::const_iterator d_iter( data.begin() ), d_last( data.end() );
                    d_iter != d_last;
                    ++d_iter )
              {
                csv::size_type len = d_iter->size();
                if ( len < 3 )  // type, api_name, params ��ɬ������
                {
                  toppers::fatal( _( "too little fields in `%1%\'" ), *iter );
                }
                static_api::info api_info = { 0 };
                try
                {
                    char* s;
                    s = new char[ ( *d_iter )[ 0 ].size() + 1 ];
                    std::strcpy( s, ( *d_iter )[ 0 ].c_str() );
                    api_info.type = s;

                    s = new char[ ( *d_iter )[ 1 ].size() + 1 ];
                    std::strcpy( s, ( *d_iter )[ 1 ].c_str() );
                    api_info.api_name = s;

                    s = new char[ ( *d_iter )[ 2 ].size() + 1 ];
                    std::strcpy( s, ( *d_iter )[ 2 ].c_str() );
                    api_info.params = s;
                    if ( len >= 4 && !( *d_iter )[ 3 ].empty() )
                    {
                      api_info.id_pos = std::strtol( ( *d_iter )[ 3 ].c_str(), 0, 0 );
                    }
                    if ( len >= 5 && !( *d_iter )[ 4 ].empty() )
                    {
                      api_info.slave = !!std::strtol( ( *d_iter )[ 4 ].c_str(), 0, 0 );
                    }
                    static_api_table_[ api_info.api_name ] = api_info;
                }
                catch ( ... )
                {
                  delete[] api_info.type;
                  delete[] api_info.api_name;
                  delete[] api_info.params;
                  throw;
                }
              }
            }
          }
        }

        ~init_t()
        {
          for ( std::map< std::string, static_api::info >::const_iterator iter( static_api_table_.begin() ), last( static_api_table_.end() );
                iter != last;
                ++iter )
          {
            delete[] iter->second.type;
            delete[] iter->second.api_name;
            delete[] iter->second.params;
          }
        }

        std::map< std::string, static_api::info > static_api_table_;
      };
      static init_t init;
      std::map< std::string, static_api::info > const* result = &init.static_api_table_;
      return result;
    }

    /*!
     * \brief   cfg1_out.c �ؤν��Ͼ���ơ��֥������
     * \return  �������� cfg1_out::cfg1_def_table ���֥������ȤؤΥݥ���
     * \note    ���δؿ����֤��ݥ��󥿤� delete ���ƤϤʤ�ʤ�
     *
     * --cfg1-def-table ���ץ����ǻ��ꤷ���ե����뤫�顢cfg1_out.c �ؽ��Ϥ��������ɤ߼�ꡢ
     * cfg1_out::cfg1_def_table ���֥������Ȥ��������롣
     *
     * CSV �η����ϰʲ����̤�
     *
     *    ����ܥ�̾,��[,s|signed]
     *
     * ������ s �ޤ��� signed �Ͼ�ά��ǽ����ά�������̵�������Ȥߤʤ���s �ޤ��� signed �������
     * ����դ������Ȥߤʤ���\n
     * �ּ��פκǽ�� # ����������������Ȥߤʤ���
     */
    cfg1_out::cfg1_def_table const* factory::get_cfg1_def_table() const
    {
      struct init_t
      {
        init_t()
        {
          boost::any t = global( "cfg1-def-table" );
          if ( t.empty() )
          {
            without_def_table_ = true;
          }
          else
          {
            without_def_table_ = false;

            std::vector< std::string > cfg1_def_table = boost::any_cast< std::vector< std::string >& >( t );
            for ( std::vector< std::string >::const_iterator iter( cfg1_def_table.begin() ), last( cfg1_def_table.end() );
                  iter != last;
                  ++iter )
            {
              std::string buf;
              read( iter->c_str(), buf );
              csv data( buf.begin(), buf.end() );
              for ( csv::const_iterator d_iter( data.begin() ), d_last( data.end() );
                    d_iter != d_last;
                    ++d_iter )
              {
                csv::size_type len = d_iter->size();
                if ( len < 2 )
                {
                  toppers::fatal( _( "too little fields in `%1%\'" ), *iter );
                }
                cfg1_out::cfg1_def_t def = { 0 };
                def.name = ( *d_iter )[ 0 ];
                def.expression = ( *d_iter )[ 1 ];
                if ( len >= 3 )
                {
                  std::string is_signed( ( *d_iter )[ 2 ] );
                  def.is_signed = ( is_signed == "s" || is_signed == "signed" );
                }
                if ( len >= 4)
                {
                  def.value1 = ( *d_iter )[ 3 ];
                }
                if ( len >= 5)
                {
                  def.value2 = ( *d_iter )[ 4 ];
                }
                cfg1_def_table_.push_back( def );
              }
            }
          }
        }
        cfg1_out::cfg1_def_table cfg1_def_table_;
        bool without_def_table_;
      };
      static init_t init;
      cfg1_out::cfg1_def_table const* result = init.without_def_table_ ? 0 : &init.cfg1_def_table_;
      return result;
    }

    //! ���֥������Ȥθ�
    void factory::do_swap( factory& other )
    {
      kernel_.swap( other.kernel_ );
    }

    /*!
     *  \brief  �ޥ���ץ��å�������
     *  \param[in]  cfg1out cfg1_out ���֥�������
     *  \param[in]  api_map .cfg �ե�����˵��Ҥ��줿��ŪAPI����
     *  \return     �ޥ���ץ��å��ؤΥݥ���
     *  \note   ���Υ��дؿ��Ͻ�����͡ʥ��եȥ������������б��ǡˤβ�¸�Τ���ˤ��Τޤ޻Ĥ���
     */
    std::auto_ptr< macro_processor > factory::do_create_macro_processor( cfg1_out const& cfg1out, cfg1_out::static_api_map const& api_map ) const
    {
      typedef macro_processor::element element;
      typedef macro_processor::var_t var_t;
      std::auto_ptr< macro_processor > mproc( new macro_processor );
      element e;

      e.s = " ";    mproc->set_var( "SPC", var_t( 1, e ) );  // $SPC$
      e.s = "\t";   mproc->set_var( "TAB", var_t( 1, e ) );  // $TAB$
      e.s = "\n";   mproc->set_var( "NL",  var_t( 1, e ) );  // $NL$

      // �С���������
      e.s = toppers::get_global_string( "version" );
      e.i = toppers::get_global< std::tr1::int64_t >( "timestamp" );
      mproc->set_var( "CFG_VERSION", var_t( 1, e ) );   // $CFG_VERSION$

      // ����¾���Ȥ߹����ѿ�������
      set_object_vars( api_map, *mproc );
      set_object_vars( cfg1out.get_static_api_array(), *mproc );
      set_clsid_vars( cfg1out.get_clsid_table(), cfg1out, *mproc );
      set_domid_vars( cfg1out.get_domid_table(), *mproc );
      set_platform_vars( cfg1out, *mproc );
      e.s = cfg1out.get_includes();
      e.i = boost::none;
      mproc->set_var( "INCLUDES", var_t( 1, e ) );

      // �ѥ�����
      e.s = boost::lexical_cast< std::string >(toppers::get_global< int >( "pass" ));
      e.i = toppers::get_global< int >( "pass" );
      mproc->set_var( "CFG_PASS", var_t( 1, e ) );

      return mproc;
    }

    /*!
     *  \brief  �ޥ���ץ��å�������
     *  \param[in]  cfg1out cfg1_out ���֥�������
     *  \param[in]  api_array .cfg �ե�����˵��Ҥ��줿��ŪAPI����
     *  \return     �ޥ���ץ��å��ؤΥݥ���
     */
    std::auto_ptr< macro_processor > factory::do_create_macro_processor( cfg1_out const& cfg1out, std::vector< static_api > const& api_array ) const
    {
      typedef macro_processor::element element;
      typedef macro_processor::var_t var_t;
      std::auto_ptr< macro_processor > mproc( new macro_processor );
      element e;

      e.s = " ";    mproc->set_var( "SPC", var_t( 1, e ) );  // $SPC$
      e.s = "\t";   mproc->set_var( "TAB", var_t( 1, e ) );  // $TAB$
      e.s = "\n";   mproc->set_var( "NL",  var_t( 1, e ) );  // $NL$

      // �С���������
      e.s = toppers::get_global_string( "version" );
      e.i = toppers::get_global< std::tr1::int64_t >( "timestamp" );
      mproc->set_var( "CFG_VERSION", var_t( 1, e ) );   // $CFG_VERSION$

      // ����¾���Ȥ߹����ѿ�������
      set_object_vars( api_array, *mproc );
      set_clsid_vars( cfg1out.get_clsid_table(), cfg1out, *mproc );
      set_domid_vars( cfg1out.get_domid_table(), *mproc );
      set_platform_vars( cfg1out, *mproc );
      e.s = cfg1out.get_includes();
      e.i = boost::none;
      mproc->set_var( "INCLUDES", var_t( 1, e ) );

      // �ѥ�����
      e.s = boost::lexical_cast< std::string >( toppers::get_global< int >( "pass" ) );
      e.i = toppers::get_global< int >( "pass" );
      mproc->set_var( "CFG_PASS", var_t( 1, e ) );

      return mproc;
    }

    std::auto_ptr< cfg1_out > factory::do_create_cfg1_out( std::string const& filename ) const
    {
      return std::auto_ptr< itronx::cfg1_out >( new cfg1_out( filename, get_cfg1_def_table() ) );
    }

    std::auto_ptr< checker > factory::do_create_checker() const
    {
      return std::auto_ptr< itronx::checker >( new checker );
    }

  }
}

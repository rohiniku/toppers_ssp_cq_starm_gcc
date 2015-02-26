/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2010 by TAKAGI Nobuhisa
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
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include "toppers/macro_processor.hpp"
#include "toppers/diagnostics.hpp"
#include "toppers/gettext.hpp"
#include "toppers/cpp.hpp"
#include "toppers/global.hpp"
#include "toppers/misc.hpp"
#include "toppers/itronx/static_api.hpp"
#include "toppers/itronx/factory.hpp"
#include "toppers/itronx/component.hpp"
#include <boost/format.hpp>
#include <boost/utility.hpp>
#include <boost/lexical_cast.hpp>

namespace toppers
{
  namespace
  {
    typedef macro_processor::element element;
    typedef macro_processor::var_t var_t;
    typedef macro_processor::context context;

    inline std::tr1::int64_t get_i( var_t const& var, context const* p_ctx )
    {
      return macro_processor::to_integer( var, p_ctx );
    }
    inline std::string get_s( var_t const& var, context const* p_ctx )
    {
      return macro_processor::to_string( var, p_ctx );
    }

    inline bool less_element( const element& lhs, const element& rhs )
    {
      return *lhs.i < *rhs.i;
    }

    /*!
     *  \brief  ID�ֹ����դ���
     *  \param[in]  line      ���ֹ�
     *  \param[in]  arg_list  �ޥ���°����ꥹ��
     *  \param[in]  p_ctx     �ޥ�����ƥ�����
     *  \retval     �ޥ����ֵ���
     *  �������ǻ��ꤷ�����̤Υ��֥������Ȥ��Ф���ID�ֹ����դ����ġ��Υѥ�᡼����ɽ���ѿ���
     *  TEXT_LINE��ID_LIST��ORDER_LIST�������RORDER_LIST�����ꤹ�롣��������ID�ֹ������ʤ�
     *  ���֥������Ȥξ�硢ID_LIST�����ꤷ�ʤ���
     */
    var_t bf_assignid( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
    {
      if ( macro_processor::check_arity( line, arg_list.size(), 1, "ASSIGNID" ) )
      {
        itronx::factory* factory = get_global< itronx::factory* >( "factory" );
        std::map< std::string, itronx::static_api::info > const* info_map = factory->get_static_api_info_map();

        std::string type = get_s( arg_list[ 0 ], p_ctx );    // ������ꥹ�Ȥμ���̾
        std::string TYPE = toppers::toupper( type );
        typedef std::map< std::string, long > id_map_t;
        typedef std::map< long, std::string > id_rmap_t;
        id_map_t id_map;
        id_rmap_t id_rmap;
        var_t id_list, order_list, rorder_list;
        bool has_id = false;

        std::string id_input_file( get_global< std::string >( "id-input-file" ) );
        if ( !id_input_file.empty() )  // --id-input-file ���ץ���󤬻��ꤵ��Ƥ�����...
        {
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
              id_map[ name ] = value;
              id_rmap[ value ] = name;
            }
          }
        }
        long order = 1;
        for ( int i = 1; ; i++ )
        {
          std::string str_i = boost::lexical_cast< std::string >( i );
          if ( p_ctx->var_map.find( "API.TYPE[" + str_i + "]" ) == p_ctx->var_map.end() )
          {
            break;
          }
          std::string api_name = p_ctx->var_map[ "API.NAME[" + str_i + "]" ].at( 0 ).s;
          std::map< std::string, itronx::static_api::info >::const_iterator it = info_map->find( api_name );
          if ( it == info_map->end() )
          {
            break;
          }
          itronx::static_api::info info = it->second;
          if ( info.type != type )
          {
            continue;
          }

          var_t params = p_ctx->var_map[ "API.PARAMS[" + str_i + "]" ];
          var_t args = p_ctx->var_map[ "API.ARGS[" + str_i + "]" ];
          long id = -1;

          if ( info.id_pos >= 0 )  // ID�ֹ�Τ�����...
          {
            if ( !info.slave )
            {
              if ( std::strchr( info.params, '#' ) != 0 ) // ���֥������ȼ���̾����ľ��...
              {
                for ( id = 1; id_rmap.find( id ) != id_rmap.end(); id++ ) // ̤���Ѥ�ID�ֹ�򸡺�
                  ;
                args.at( info.id_pos ).i = id; // ID�ֹ������
              }
              else
              {
                id = static_cast< long >( *args.at( info.id_pos ).i );
              }
              std::string idname = args[ info.id_pos ].s; // ID�λ���
              id_map[ idname ] = id;
              id_rmap[ id ] = idname;
              order_list.push_back( args[ info.id_pos ] );
            }
            else
            {
              id_map_t::iterator it = id_map.find( args.at( info.id_pos ).s );
              if ( it == id_map.end() )
              {
                fatal( line, _( "E_NOEXS: `%1%\' is undefined" ), args[ info.id_pos ].s );
              }
              args.at( info.id_pos ).i = it->second;
            }
            has_id = true;
          }
          else  // ID�ֹ��̵�����...
          {
            element e;
            e.i = order;
            order_list.push_back( e );
          }
          std::string str_id = boost::lexical_cast< std::string >( id > 0 ? id : order );

          // �ƥѥ�᡼�����ѿ�������
          for ( var_t::size_type i = 0, n = params.size(); i < n; i++ )
          {
            std::string var_name = params[ i ].s + "[" + str_id + "]";
            p_ctx->var_map[ var_name ] = var_t( 1, args.at( i ) );
          }
          p_ctx->var_map[ TYPE + ".TEXT_LINE[" + str_id + "]" ] = p_ctx->var_map[ "API.TEXT_LINE[" + str_i + "]" ];
          ++order;
        }

        id_list = order_list;
        std::sort( id_list.begin(), id_list.end(), less_element );
        rorder_list = order_list;
        std::reverse( rorder_list.begin(), rorder_list.end() );
        p_ctx->var_map[ TYPE + ".ID_LIST" ] = id_list;
        p_ctx->var_map[ TYPE + ".ORDER_LIST" ] = order_list;
        p_ctx->var_map[ TYPE + ".RORDER_LIST" ] = rorder_list;
      }
      return var_t();
    }

    /*!
     *  \brief  ���ꤷ��Ϣ�����󷲤���ŪAPI���ɲä���
     *  \param[in]  line      ���ֹ�
     *  \param[in]  arg_list  �ޥ���°����ꥹ��
     *  \param[in]  p_ctx     �ޥ�����ƥ�����
     *  \retval     �ޥ����ֵ���
     *  API.�ǻϤޤ�Ϣ�����󷲤�ɬ�פ˱�����Ŭ�ڤ��Ѵ���Ԥä���ǡ��̤Υץ�ե��å����ǻϤޤ�
     *  Ϣ�����󷲤��ɲä��롣���ꤹ�������ˡ�Ȥ��Ƥϡ�����Υ��եȥ��������ʤ������ǽ����ŪAPI
     *  �˴ؤ��Ƥϡ��ɲä�Ԥ�ʤ�����¾����ŪAPI���֤��������ɲä�Ԥ�������Ǥ��ʤ���ŪAPI�˴ؤ���
     *  �Ϥ��Τޤ��ɲä�Ԥ���
     *  ���δؿ����������ˤ�API.�ǻϤޤ�Ϣ�������Ϣ�֤���������ˤ��ɲ����Ϣ�����󷲤�
     *  �ץ�ե��å������軰�����ˤ��оݤȤ�����ŪAPI̾����Ͱ����ˤ��ɲä���ѥ�᡼������ܥ��
     *  �¤Ӥ���ް����ˤϥѥ�᡼�����¤Ӥ���ꤹ�롣     
     */
    var_t bf_addapi( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
    {
      element e;
      if ( macro_processor::check_arity( line, arg_list.size(), 5, "ADDAPI" ) )
      {
        itronx::factory* factory = get_global< itronx::factory* >( "factory" );
        std::map< std::string, itronx::static_api::info > const* info_map = factory->get_static_api_info_map();

        std::tr1::int64_t order = get_i( arg_list[ 0 ], p_ctx );  // ������ŪAPI��Ϣ��
        std::string list_name = get_s( arg_list[ 1 ], p_ctx );    // ������ꥹ�Ȥμ���̾
        std::string api_name = get_s( arg_list[ 2 ], p_ctx );     // ��ŪAPI̾
        var_t params = arg_list[ 3 ]; // �ѥ�᡼������ܥ���¤�
        var_t args = arg_list[ 4 ];   // �ѥ�᡼�����¤�

        std::map< std::string, itronx::static_api::info >::const_iterator it = info_map->find( api_name );
        if ( it != info_map->end() )
        {
          itronx::static_api::info info = it->second;
          std::string str_order = boost::lexical_cast< std::string >( order );
          p_ctx->var_map[ list_name + ".TEXT_LINE[" + str_order + "]" ] = p_ctx->var_map[ "API.TEXT_LINE[" + str_order + "]" ]; 
          e.s = api_name;
          p_ctx->var_map[ list_name + ".NAME[" + str_order + "]" ] = var_t( 1, e );
          e.s = info.type;
          p_ctx->var_map[ list_name + ".TYPE[" + str_order + "]" ] = var_t( 1, e );
          p_ctx->var_map[ list_name + ".PARAMS[" + str_order + "]" ] = params;
          p_ctx->var_map[ list_name + ".ARGS[" + str_order + "]" ] = args;

          e.s.clear();
          if ( !p_ctx->var_map[ list_name + ".ORDER_LIST" ].empty() )
          {
            e.i = *p_ctx->var_map[ list_name + ".ORDER_LIST" ].back().i + 1;
          }
          else
          {
            e.i = 1;
          }
          p_ctx->var_map[ list_name + ".ORDER_LIST" ].push_back( e );

          e.s.clear();
          e.i = 1;
        }
      }
      return var_t( 1, e );
    }

    /*!
     *  \brief  �ѿ����θ�
     *  \param[in]  line      ���ֹ�
     *  \param[in]  arg_list  �ޥ���°����ꥹ��
     *  \param[in]  p_ctx     �ޥ�����ƥ�����
     *  \retval     �ޥ����ֵ���
     *  �������������������ǻ��ꤷ���ץ�ե��å���������ѿ����������ؤ��롣
     *  ��ADDAPI�Ǵؿ��ǡ��̤Υץ�ե��å��������Ϣ��������Ȥ�Ω�Ƥ����Ȥϡ����δؿ����Ѥ��뤳�Ȥǡ�
     *  API.��ץ�ե��å����˻���Ϣ������ȸ򴹤��뤳�Ȥ��Ǥ��롣
     */
    var_t bf_swapprefix( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
    {
      if ( macro_processor::check_arity( line, arg_list.size(), 2, "SWAPPREFIX" ) )
      {
        std::string list1_name = get_s( arg_list[ 0 ], p_ctx ) + ".";    // ������API�ꥹ�Ȥμ���̾.
        std::string list2_name = get_s( arg_list[ 1 ], p_ctx ) + ".";    // ¾����API�ꥹ�Ȥμ���̾.
        std::string::size_type list1_size = list1_name.size();
        std::string::size_type list2_size = list2_name.size();

        std::map< std::string, var_t > temp;
        for ( std::map< std::string, var_t >::const_iterator iter = p_ctx->var_map.begin(), last = p_ctx->var_map.end();
              iter != last;
              ++iter )
        {
          std::pair< std::string, var_t > element = *iter;
          if ( std::strncmp( iter->first.c_str(), list1_name.c_str(), list1_size ) == 0 )
          {
            element.first = list2_name + ( iter->first.c_str() + list1_size );
          }
          else if ( std::strncmp( iter->first.c_str(), list2_name.c_str(), list2_size ) == 0 )
          {
            element.first = list1_name + ( iter->first.c_str() + list2_size );
          }
          temp.insert( element );
        }
        p_ctx->var_map.swap( temp );
      }
      return var_t();
    }

    /*!
     *  \brief  �ѿ����θ�
     *  \param[in]  line      ���ֹ�
     *  \param[in]  arg_list  �ޥ���°����ꥹ��
     *  \param[in]  p_ctx     �ޥ�����ƥ�����
     *  \retval     �ޥ����ֵ���
     *  �������ǻ��ꤷ���ץ�ե��å����ǻϤޤ��ѿ����������롣��SWAPPREFIX�Ǵؿ��Ǹ򴹤������ȡ�
     *  ���פˤʤä��ѿ����Ϥ��δؿ��Ǻ�����Ƥ������Ȥ�˾�ޤ�����
     */
    var_t bf_cleanvars( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
    {
      if ( macro_processor::check_arity( line, arg_list.size(), 1, "CLEANVARS" ) )
      {
        std::string prefix = get_s( arg_list[ 0 ], p_ctx ) + ".";    // �ѿ�����Ƭ��
        std::size_t n = prefix.size();
        std::map< std::string, var_t > temp_map;

        for ( std::map< std::string, var_t >::const_iterator iter = p_ctx->var_map.begin(), last =p_ctx->var_map.end();
              iter != last;
              ++iter )
        {
          if ( std::strncmp( iter->first.c_str(), prefix.c_str(), n ) != 0 )
          {
            temp_map.insert( *iter );
          }
        }
        p_ctx->var_map.swap( temp_map );
      }
      return var_t();
    }

    macro_processor::func_t const function_table[] =
    {
      { "ASSIGNID",   &bf_assignid },
      { "ADDAPI",     &bf_addapi },
      { "SWAPPREFIX", &bf_swapprefix },
      { "CLEANVARS",  &bf_cleanvars },
    };

  }

  namespace itronx
  {

    component::component( macro_processor* mproc )
      : mproc_( mproc )
    {
      for ( std::size_t i = 0; i < sizeof( function_table ) / sizeof( function_table[ 0 ] ); i++ )
      {
        mproc_->add_builtin_function( function_table[ i ] );
      }
    }

  }
}

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
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include "toppers/macro_processor.hpp"
#include "toppers/diagnostics.hpp"
#include "toppers/gettext.hpp"
#include "toppers/cpp.hpp"
#include <boost/format.hpp>
#include <boost/utility.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string.hpp> 

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

  }

  /*!
    *  \brief  �����θĿ������å�
    *  \param[in]  line    ���ֹ����
    *  \param[in]  arity   �����θĿ�
    *  \param[in]  valid   ���Ԥ��Ƥ�������θĿ�
    *  \param[in]  function_name �Ȥ߹��ߴؿ�̾
    */
  bool macro_processor::check_arity( text_line const& line, std::size_t arity, std::size_t valid, char const* function_name )
  {
    bool result = false;
    if ( arity < valid )
    {
      error( line, _( "too few arguments for `%1%\'" ), function_name );
    }
    else if ( arity > valid )
    {
      error( line, _( "too many arguments for `%1%\'" ), function_name );
    }
    else
    {
      result = true;
    }
    return result;
  }

  /*!
   *  \brief  �ѿ�����פΤ����<<�黻��
   *  \param[in,out]  ostr  ���ϥ��ȥ꡼��
   *  \param[in]      arg   �ѿ��򻲾Ȥ��뤿��Υڥ�
   *  \return         ostr���֤�
   *  \note ���ߤμ����Ǥϡ�arg.second �ϻ��Ѥ��Ƥ��ʤ���
   */
  std::ostream& operator<<( std::ostream& ostr, std::pair< var_t const*, context const* > const& arg )
  {
    for ( var_t::const_iterator iter( arg.first->begin() ), last( arg.first->end() ); iter != last; ++iter )
    {
      if ( !iter->s.empty() )
      {
        ostr << iter->s;
      }
      else if ( iter->i )
      {
        ostr << iter->i.get();
      }
      if ( boost::next( iter ) != last )
      {
        ostr << ",";
      }
    }
    return ostr;
  }

  /*!
   *  \brief  ����ꥹ�Ȥ�Ĺ��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����Ȥ��ƻ��ꤷ������դ��ꥹ�Ȥ����ǿ����֤���
   *  ��1�ޥ���°���������դ��ꥹ�ȤǤʤ�����1���֤����ޤ�����1�ޥ���°�����̵�����ѿ��ξ���0���֤���
   */
  var_t bf_length( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "LENGTH" ) )
    {
      std::tr1::int64_t size = arg_list.front().size();
      e.i = size;
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ʸ����ΰ���Ƚ��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°�������2�ޥ���°�����ʸ����Ȥ�����Ӥ������פ�����Ͽ��򡢤����Ǥʤ���е����֤���
   */
  var_t bf_eq( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "EQ" ) )
    {
      e.i = get_s( arg_list[ 0 ], p_ctx ) == get_s( arg_list[ 1 ], p_ctx );
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ������
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°�����̵�����ѿ��ξ�����2�°������֤�������¾����1�°������֤���
   */
  var_t bf_alt( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "ALT" ) )
    {
      if ( !arg_list[0].empty() )
      {
        return arg_list[ 0 ];
      }
      else
      {
        return arg_list[ 1 ];                
      }
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ����ꥹ�Ȥ�����
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����Ȥ���Ϳ��������դ��ꥹ�Ȥγ����Ǥ���2�ޥ���°�����ź�����Ȥ��������ѿ���ɾ������
   *  ����ɾ����̤˴�Ť���������󤹤롣
   *
   *  \example
   *  $FOO[1] = 20$
   *  $FOO[2] = 10$
   *  $FOO[3] = 30$
   *  $SORT({ 1,2,3 }, "FOO")$
   *  �� { 2,1,3 }
   *  \endexample
   */
  var_t bf_sort( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    var_t result;
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "SORT" ) )
    {
      var_t list( arg_list[ 0 ] );
      std::string field( get_s( arg_list[ 1 ], p_ctx ) );
      std::vector< std::pair< element, std::tr1::int64_t > > temp;

      for ( var_t::const_iterator iter( list.begin() ), last( list.end() ); iter != last; ++iter )
      {
        std::tr1::int64_t order = iter->i.get();
        std::string name( ( boost::format( "%s[%d]" ) % field % order ).str() );
        std::map< std::string, var_t >::const_iterator m_iter( p_ctx->var_map.find( name ) );
        if ( m_iter == p_ctx->var_map.end() )
        {
          return var_t();
        }
        if ( !m_iter->second.empty() )
        {
          temp.push_back( std::make_pair( m_iter->second.front(), order ) );
        }
      }

      std::stable_sort( temp.begin(), temp.end() );

      for ( std::vector< std::pair< element, std::tr1::int64_t > >::const_iterator iter( temp.begin() ), last( temp.end() );
            iter != last;
            ++iter )
      {
        element e;
        e.i = iter->second;
        result.push_back( e );
      }
    }
    return result;
  }

  /*!
   *  \brief  �Ķ��ѿ��μ���
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ���Ķ��ѿ����ͤ��֤���
   */
  var_t bf_environ( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "ENVIRON" ) )
    {
      std::string name = get_s( arg_list[ 0 ], p_ctx );
      char const* env = std::getenv( name.c_str() );
      if ( env == 0 )
      {
        return var_t();
      }
      e.s = env;
      errno = 0;
      char* endptr;
      if ( std::tr1::int64_t value = std::strtol( env, &endptr, 0 ) )
      {
        if ( *endptr == '\0' && errno == 0 )
        {
          e.i = value;
        }
      }
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  �ͤ�����
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°�����ƥ����ȡ���2�ޥ���°�������ͤȤ��ơ��ͤ��������롣
   */
  var_t bf_value( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "VALUE" ) )
    {
      if ( !arg_list[0].empty() )
      {
        e.s = get_s( arg_list[ 0 ], p_ctx );
      }
      if ( !arg_list[1].empty() )
      {
        e.i = get_i( arg_list[ 1 ], p_ctx );
      }
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ʸ�����Ϣ��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°�������2�ޥ���°�����Ϣ�뤷�ƿ�����ʸ������������롣
   */
  var_t bf_concat( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "CONCAT" ) )
    {
      e.s = get_s( arg_list[ 0 ], p_ctx ) + get_s( arg_list[ 1 ], p_ctx );
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ����ꥹ�Ȥν�ü�����Ǥ��ɲ�
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°�������2�ޥ���°����ʹߤ�Ϣ�뤷�ƿ���������դ��ꥹ�Ȥ��������롣
   */
  var_t bf_append( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    var_t result;
    var_t::size_type const n = arg_list.size();
    if ( n < 2 )
    {
      error( line, _( "too few arguments for `%1%\'" ), "APPEND" );
        }
        else
        {
          result = arg_list[ 0 ];
      for ( var_t::size_type i = 1; i < n; i++)
            {
              result.insert( result.end(), arg_list[ i ].begin(), arg_list[ i ].end() );
            }
        }
    return result;
  }

  /*!
   *  \brief  ����ꥹ�Ȥλ������Ǥλ���
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ������ꥹ�ȤΡ���2�ޥ���°����ǻ��ꤷ�����Ǥ��֤���
   */
  var_t bf_at( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "AT" ) )
    {
      try
      {
        e = arg_list[ 0 ].at( static_cast< std::vector< var_t >::size_type >( get_i( arg_list[1], p_ctx ) ) );
      }
      catch ( std::out_of_range& )
      {
        // ź����������
        // �ä˲��⤷�ʤ� �� ���λ����� e �����ͤǤ��뤳�Ȥ����
      }
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  �ƥ����Ȥ�����
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ��ʸ������������롣
   */
  var_t bf_gettext( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "GETTEXT" ) )
    {
      std::string message = get_s( arg_list[ 0 ], p_ctx );
      e.s = gettext( message );
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  �ޥ���°����ν񼰲�
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ�������ʸ����ˤ�äơ���2�ޥ���°����ʹߤ�񼰲����롣
   *  �񼰲�ʸ����ϡ�%n���Ȥ��ʤ����Ȥ������printf�ؿ��Υ����ѡ����åȤǤ��롣
   *  ���Τʻ��ͤϡ�boost::format�򻲾ȤΤ��ȡ�
   */
  var_t bf_format( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    std::size_t arity = arg_list.size();
    if ( arity < 1 )
    {
      error( line, _( "too few arguments for `%1%\'" ), "FORMAT" );
    }
    std::string format_str = get_s( arg_list[ 0 ], p_ctx );
#if 0
    std::string debug_str = format_str;
    if ( debug_str == "0x%08x" )
      toppers::trace("%s", debug_str.c_str() );
#endif
    boost::format fmt( format_str );
    try
    {
      for ( std::size_t i = 1; i < arity; i++ )
      {
        std::pair< var_t const*, context const* > arg( &arg_list[i], p_ctx );
        fmt % arg;
      }
      e.s = fmt.str();
    }
    catch ( ... )
    {
      error( line, _( "illegal argument value in `%1%\'" ), "FORMAT" );
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ����դ��ꥹ�����õ��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ������դ��ꥹ�Ȥ˴ޤޤ����2�ޥ���°����ǻ��ꤷ���ͤ����������Ǥ�
   *  ��Ƭ������õ�����롣
   *  ���������Ǥ����Ĥ���Ф������ǤؤΥ���ǥå����򡢤����Ǥʤ���ж��ͤ��֤���
   */
  var_t bf_find( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "FIND" ) )
    {
      var_t list( arg_list[ 0 ] );

      if ( !arg_list[ 1 ].empty() )
      {
        element key( arg_list[ 1 ].front() );

        if ( !key.i )   // �����ͤ����ꤵ��Ƥ��ʤ����...
        {
          std::string value( key.s );

          for ( var_t::const_iterator iter( list.begin() ), last( list.end() ); iter != last; ++iter )
          {
            if ( iter->s == value ) // ȯ����
            {
              e.i = iter - list.begin();  // iter �� RandomAccessIterator
              return var_t( 1, e );
            }
          }
        }
        else
        {
          std::tr1::int64_t value( key.i.get() );

          for ( var_t::const_iterator iter( list.begin() ), last( list.end() ); iter != last; ++iter )
          {
            if ( iter->i && iter->i.get() == value ) // ȯ����
            {
              e.i = iter - list.begin();  // iter �� RandomAccessIterator
              return var_t( 1, e );
            }
          }
        }
      }
    }
    return var_t();
  }

  /*!
   *  \brief  �ϰϻ���ˤ�����դ��ꥹ��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����Ǻǽ���ͤ���2�ޥ���°����ǺǸ���ͤ���ꤹ�롣
   *  { �ǽ����, �ǽ���� + 1, ... �Ǹ���� }
   *  �Ȥʤ����դ��ꥹ�Ȥ��������롣
   *  �������������ʤ����϶��ͤ��֤���
   */
  var_t bf_range( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    var_t result;
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "RANGE" ) )
    {
      std::tr1::int64_t arg1( get_i( arg_list[ 0 ], p_ctx ) );
      std::tr1::int64_t arg2( get_i( arg_list[ 1 ], p_ctx ) );

      for ( ; arg1 <= arg2; ++arg1 )
      {
        element e;
        e.i = arg1;
        result.push_back( e );
      }
    }
    return result;
  }

  /*!
   *  \brief  ���ѿ��Υ����
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  �ޥ���°�������ꤷ����硢����ʸ����°���ǻ��ꤷ���ե�����˥���פ���ʸ������ɵ����롣
   *  �ե�����̾�Ȥ��ơ�"stdout"����ꤷ������ɸ����ϡ�"stderr"����ꤷ������ɸ�२�顼�˽��Ϥ��롣
   *  �ե�����̾���ά��������"stderr"����ꤷ����ΤȤ��ƿ��񤦡�
   */
  var_t bf_dump( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    std::size_t arity = arg_list.size();

    if ( arity > 1 )
    {
      error( line, _( "too many arguments for `%1%\'" ), "DUMP" );
    }

    std::string dump_str;

    // ���ѿ���ʤ��
    for ( std::map< std::string, var_t >::const_iterator iter( p_ctx->var_map.begin() ), last( p_ctx->var_map.end() );
          iter != last;
          ++iter )
    {
      dump_str += "$" + iter->first + "$ = { ";
      if ( !iter->second.empty() )
      {
        // ���ѿ���������
        for ( var_t::const_iterator iter2( iter->second.begin() ), last2( iter->second.end() );
              iter2 != last2;
              ++iter2 )
        {
          dump_str += "\"" + iter2->s + "\"(";
          if ( iter2->i ) // ��°���������...
          {
            dump_str += boost::lexical_cast< std::string >( *iter2->i );
          }
          dump_str += "), ";
        }
      }
      dump_str += " }\n";
    }

    std::string filename( "stderr" );
    if ( arity == 1 )
    {
      filename = get_s( arg_list[ 0 ], p_ctx );
    }
    if ( filename == "stdout" )
    {
      std::fputs( dump_str.c_str(), stdout );
      std::fflush( stdout );
    }
    else if ( filename == "stderr" )
    {
      std::fputs( dump_str.c_str(), stderr );
      std::fflush( stderr );
    }
    else
    {
      std::FILE* stream = std::fopen( filename.c_str(), "a" );
      if ( stream != 0 )
      {
        std::fputs( dump_str.c_str(), stream );
        std::fclose( stream );
      }
    }
    element e;
    return var_t( 1, e );
  }

  /*!
   *  \brief  �ѿ��Υȥ졼��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ���ѿ������Ƥ�ȥ졼�����롣
   *  ��2�ޥ���°�������ꤷ����硢����ʸ����°���ǻ��ꤷ���ե�����˥ȥ졼�����Ƥ��ɵ����롣
   *  �ե�����̾�Ȥ��ơ�"stdout"����ꤷ������ɸ����ϡ�"stderr"����ꤷ������ɸ�२�顼�˽��Ϥ��롣
   *  �ե�����̾���ά��������"stderr"����ꤷ����ΤȤ��ƿ��񤦡�
   */
  var_t bf_trace( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    std::size_t arity = arg_list.size();

    if ( arity < 1 )
    {
      error( line, _( "too few arguments for `%1%\'" ), "TRACE" );
    }
    else if ( arity > 2 )
    {
      error( line, _( "too many arguments for `%1%\'" ), "TRACE" );
    }

    var_t value( arg_list[ 0 ] );

    std::string trace_str = "{ ";
    for ( var_t::const_iterator iter( value.begin() ), last( value.end() );
          iter != last;
          ++iter )
    {
      trace_str += "\"" + iter->s + "\"(";
      if ( iter->i ) // ��°���������...
      {
        trace_str += boost::lexical_cast< std::string >( *iter->i ) + " as integer";
      }
      else if ( !iter->v.empty() )
      {
        trace_str += "\"" + boost::lexical_cast< std::string >( iter->v ) + "\" as string";
      }
      trace_str += "), ";
    }
    trace_str += " }\n";

    std::string filename( "stderr" );
    if ( arity == 2 )
    {
      filename = get_s( arg_list[ 1 ], p_ctx );
    }
    if ( filename == "stdout" )
    {
      std::fputs( trace_str.c_str(), stdout );
      std::fflush( stdout );
    }
    else if ( filename == "stderr" )
    {
      std::fputs( trace_str.c_str(), stderr );
      std::fflush( stderr );
    }
    else
    {
      std::FILE* stream = std::fopen( filename.c_str(), "a" );
      if ( stream != 0 )
      {
        std::fputs( trace_str.c_str(), stream );
        std::fclose( stream );
      }
    }

    element e;
    return var_t( 1, e );
  }

  /*!
   *  \brief  ʸ����Υ���������
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   */
  var_t bf_escstr( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "ESCSTR" ) )
    {
      std::string str( get_s( arg_list[ 0 ], p_ctx ) );
      e.s = quote_string( str );
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ʸ����Υ��������ײ��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   */
  var_t bf_unescstr( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "UNESCSTR" ) )
    {
      std::string str( get_s( arg_list[ 0 ], p_ctx ) );
      if ( !str.empty() )
      {
        e.s = expand_quote( str );
      }
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  �ؿ��θƤӽФ�
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   */
  var_t bf_call( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    return macro_processor::call_user_function( line, arg_list, p_ctx );
  }

  namespace
  {
    struct bf_functor : std::binary_function< element const&, element const&, bool >
    {
    public:
      bf_functor( text_line const& line, std::string const& func_name, context* p_ctx )
        : line_( line ), func_name_( func_name ), p_ctx_( p_ctx )
      {
      }
      bool operator()( element const& lhs, element const& rhs )
      {
        std::vector< var_t > arg_list;
        arg_list.reserve( 3 );

        element e;
        e.s = func_name_;
        arg_list.push_back( var_t( 1, e ) );
        arg_list.push_back( var_t( 1, lhs ) );
        arg_list.push_back( var_t( 1, rhs ) );
        int arg1 = static_cast< int >( *lhs.i );
        int arg2 = static_cast< int >( *rhs.i );

        var_t r = bf_call( line_, arg_list, p_ctx_ );
        bool result = 0;
        if ( !r.empty() )
        {
          int retval = static_cast< int >( *r.front().i );
          result = ( *r.front().i < 0 );
        }
        return result;
      }
    private:
      std::string func_name_;
      context* p_ctx_;
      text_line line_;
    };
  }

  /*!
   *  \brief  ������
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   */
  var_t bf_lsort( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "LSORT" ) )
    {
      var_t temp( arg_list[ 0 ] );
      std::string compare( arg_list[ 1 ].front().s );
      std::stable_sort( temp.begin(), temp.end(), bf_functor( line, compare, p_ctx ) );
      return temp;
    }
    element e;
    return var_t( 1, e );
  }

  /*!
   *  \brief  �ؿ����ɤ�����Ƚ��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   */
  var_t bf_isfunction( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "ISFUNCTION" ) )
    {
      std::string func_name( get_s( arg_list[ 0 ], p_ctx ) );
      if ( p_ctx->func_map.find( func_name ) != p_ctx->func_map.end() )
      {
        e.i = 1;
      }
      else
      {
        e.i = 0;
      }
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ����դ��ꥹ�Ȥ��¤Ӥ�դˤ���
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   */
  var_t bf_reverse( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    var_t result;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "REVERSE" ) )
    {
      result = arg_list[ 0 ];
      std::reverse(result.begin(), result.end());
    }
    return result;
  }

  /*! 
   *  \brief  ����ɽ�����Ѥ����ִ� 
   *  \param[in]  line      ���ֹ� 
   *  \param[in]  arg_list  �ޥ���°����ꥹ�� 
   *  \param[in]  p_ctx     �ޥ�����ƥ����� 
   *  \retval     �ޥ����ֵ��� 
   *  ��1�ޥ���°����ǻ��ꤷ��ʸ����Τ�������2�ޥ���°����ǻ��ꤷ������ɽ���˥ޥå�����ս����3�ޥ���°��������Ƥ��ִ����롣
   *  ����ɽ����ECMAScript�ߴ��Ȥ��롣
   */ 
   var_t bf_regex_replace( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx ) 
   { 
     element e; 
     if ( macro_processor::check_arity( line, arg_list.size(), 3, "REGEX_REPLACE" ) ) 
     {
       e.s = boost::xpressive::regex_replace( get_s( arg_list[ 0 ], p_ctx ), 
                                              boost::xpressive::sregex::compile( get_s( arg_list[ 1 ], p_ctx ) ), 
                                              get_s( arg_list[ 2 ], p_ctx ));
     } 
     return var_t( 1, e ); 
   }

  /*!
   *  \brief  ʸ���󤫤������ؤ��Ѵ�
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ��ʸ����������ͤ��Ѵ����롣
   *  ��2�ޥ���°�������ꤷ����硢��������Ȥߤʤ����Ѵ���Ԥ���
   *  ��2�ޥ���°�����0����ꤷ����硢��Ƭ���˱����ơ�8�ʡ�10�ʡ�16�ʤ�Ƚ�̤��롣
   *  ��2�ޥ���°�����1����ꤷ����硢��Ƭ���˱����ơ�8�ʡ�10�ʡ�16�ʤ�Ƚ�̤��롣
   */
  var_t bf_atoi( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    std::size_t arity = arg_list.size();

    if ( arity < 1 )
    {
      error( line, _( "too few arguments for `%1%\'" ), "ATOI" );
    }
    else if ( arity > 2 )
    {
      error( line, _( "too many arguments for `%1%\'" ), "ATOI" );
    }

    std::string str( get_s( arg_list[ 0 ], p_ctx ) );
    int radix = 10;

    if ( arity == 2 )
    {
      std::tr1::int64_t t = get_i( arg_list[ 1 ], p_ctx );
      if ( t < 0 || 36 < t )
      {
        error( line, _( "illegal_radix `%1%\' in function `%2%\'" ), radix, "ATOI" );
      }
      radix = static_cast< int >( t );
    }
    if ( radix == 1 )
    {
      std::string::size_type const pos = str.find_first_of( "0123456789" );
      if ( pos != std::string::npos && str[ pos ] == '0' )
      {
        char c = str[ pos + 1 ];
        if ( c != 'x' && c != 'X' )
        {
          radix = 10;
        }
      }
    }

    element e;
    char* endptr;
    errno = 0;
    using namespace std;
    e.i = strtoll( str.c_str(), &endptr, static_cast< int >( radix ) );
    if ( errno != 0 || *endptr != '\0')
    {
      error( line, _( "conversion error in function `%1%\'" ), "ATOI" );
    }

    return var_t( 1, e ); 
  }

  /*!
   *  \brief  ��ʸ���ؤ��Ѵ�
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ��ʸ������ξ�ʸ������ʸ�����Ѵ����ޤ���
   */
  var_t bf_toupper( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "TOUPPER" ) ) 
    {
      std::string str = get_s( arg_list[ 0 ], p_ctx );
      for ( std::string::iterator first( str.begin() ), last( str.end() ); first != last; ++first )
      {
        char c = *first;
        *first = std::toupper( c );
      }
      e.s = str;
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ��ʸ���ؤ��Ѵ�
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ��ʸ���������ʸ����ʸ�����Ѵ����ޤ���
   */
  var_t bf_tolower( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "TOLOWER" ) ) 
    {
      std::string str = get_s( arg_list[ 0 ], p_ctx );
      for ( std::string::iterator first( str.begin() ), last( str.end() ); first != last; ++first )
      {
        char c = *first;
        *first = std::tolower( c );
      }
      e.s = str;
    }
    return var_t( 1, e );
  }

  /*!  
   *  \brief  ʸ�����ʬ�� 
   *  \param[in]  line      ���ֹ�  
   *  \param[in]  arg_list  �ޥ���°����ꥹ��  
   *  \param[in]  p_ctx     �ޥ�����ƥ�����  
   *  \retval     �ޥ����ֵ���  
   *  ��1�ޥ���°����ǻ��ꤷ��ʸ����Τ�������2�ޥ���°����ǻ��ꤷ��ʸ����separator��ʸ����ʬ�䤷������������դ��ꥹ�Ȥ��������롣 
   */  
  var_t bf_split( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx ) 
  { 
    var_t result; 
    if ( macro_processor::check_arity( line, arg_list.size(), 2, "SPLIT" ) ) 
    { 
      std::list<std::string> split_results; 
      std::string heystack = get_s( arg_list[ 0 ], p_ctx ); 
      boost::split(split_results, heystack, boost::is_any_of( get_s( arg_list[ 1 ], p_ctx ) ) );  

      std::list<std::string>::iterator it = split_results.begin(); 
      while ( it != split_results.end() ) 
      { 
        element e; 
        e.s = *it; 
        result.push_back( e ); 
        ++it; 
      } 
    } 
    return result; 
  } 

  /*!
   *  \brief  ����������
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  ��1�ޥ���°����ǻ��ꤷ��̾�����������������롣
   */
  var_t bf_clean( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 1, "CLEAN" ) ) 
    {
      std::string name = get_s( arg_list[ 0 ], p_ctx ) + "[";
      for ( std::map< std::string, var_t >::iterator it = p_ctx->var_map.lower_bound( name );
            it != p_ctx->var_map.end();
            ++it )
      {
        if ( std::strncmp( it->first.c_str(), name.c_str(), name.size() ) != 0 )
          break;
        it->second = var_t();
      }
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  �ޥ���ץ��å��ν�λ
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  �ޥ���ץ��å���λ���롣
   */
  var_t bf_die( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    if ( macro_processor::check_arity( line, arg_list.size(), 0, "DIE" ) ) 
    {
      throw macro_processor::die_terminate();
    }
    return var_t( 1, e );
  }

  /*!
   *  \brief  ���⤷�ʤ��Ȥ߹��ߴؿ�
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *  �����Ȥ߹��ߴؿ��ϲ���Ԥ�ʤ����ޤ����ޥ���°����Υ����å���Ԥ�ʤ���
   *  NOOP�ؿ��Ͼ�� "" ���֤���
   *  \note       ���ͤ��֤��ʤ��Τϡ�$NOOP()$�Τ褦�ʻȤ����򤷤��Ȥ��Ǥ������ʻ��Ȥ�������ʤ��褦�ˤ��뤿�ᡣ
   */
  var_t bf_noop( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    element e;
    return var_t( 1, e );
  }

  macro_processor::func_t const macro_processor::builtin_function_table[] =
  {
    { "LENGTH", bf_length },
    { "EQ", bf_eq },
    { "ALT", bf_alt },
    { "SORT", bf_sort },
    { "ENVIRON", bf_environ },
    { "VALUE", bf_value },
    { "CONCAT", bf_concat },
    { "APPEND", bf_append },
    { "AT", bf_at },
    { "GETTEXT", bf_gettext },
    { "_", bf_gettext },  // GETTEXT�Υ��Υ˥�
    { "FORMAT", bf_format },
    { "FIND", bf_find },
    { "RANGE", bf_range },
    { "DUMP", bf_dump },
    { "TRACE", bf_trace },
    { "ESCSTR", bf_escstr },
    { "UNESCSTR", bf_unescstr },
    { "CALL", bf_call },
    { "LSORT", bf_lsort },
    { "ISFUNCTION", bf_isfunction },
    { "REVERSE", bf_reverse },
    { "REGEX_REPLACE", bf_regex_replace }, 
    { "ATOI", bf_atoi },
    { "TOLOWER", bf_tolower },
    { "TOUPPER", bf_toupper },
    { "SPLIT", bf_split },
    { "CLEAN", bf_clean },
    { "DIE", bf_die },
    { "NOOP", bf_noop },
    { "", 0 },
  };

}

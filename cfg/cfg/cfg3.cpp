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
#include <fstream>
#include <sstream>
#include "toppers/diagnostics.hpp"
#include "toppers/s_record.hpp"
#include "toppers/macro_processor.hpp"
#include "toppers/itronx/component.hpp"
#include "toppers/itronx/component.hpp"
#include "cfg.hpp"
#include <boost/spirit/include/classic.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace
{
  using toppers::text_line;
  typedef toppers::macro_processor::element element;
  typedef toppers::macro_processor::var_t var_t;
  typedef toppers::macro_processor::context context;

  /*!
   *  \brief  ����ܥ���б����륢�ɥ쥹�μ���
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   */
  template < class Checker >
  var_t bf_symbol( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    using namespace toppers;
    using namespace toppers::itronx;

    if ( macro_processor::check_arity( line, arg_list.size(), 1, "SYMBOL" ) )
    {
      std::string symbol( macro_processor::to_string( arg_list[0], p_ctx ) );
      std::tr1::shared_ptr< Checker > chk = get_global< std::tr1::shared_ptr< Checker > >( "checker" );
      nm_symbol::entry entry = chk->find( symbol );
      if ( entry.type >= 0 )
      {
        element e;
        e.i = entry.address;
        return var_t( 1, e );
      }
    }
    return var_t();
  }

  // VMA ���ɥ쥹����ѥơ��֥�
  std::vector< std::pair< std::tr1::int64_t, std::vector< unsigned char > > > vma_table;

  /*!
   *  \brief  ���ꤷ�����ɥ쥹�˳�Ǽ����Ƥ����ͤμ���
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *
   *  ��1�����˥��ɥ쥹����2�������ɤ߹���Х��ȿ�����ꤷ�ޤ���
   */
  template < class Checker >
  var_t bf_peek( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    using namespace toppers;
    using namespace toppers::itronx;

    if ( macro_processor::check_arity( line, arg_list.size(), 2, "PEEK" ) )
    {
      std::size_t address = static_cast< std::size_t >( macro_processor::to_integer( arg_list[0], p_ctx ) );
      std::size_t size = static_cast< std::size_t >( macro_processor::to_integer( arg_list[1], p_ctx ) );
      std::tr1::shared_ptr< Checker > chk = get_global< std::tr1::shared_ptr< Checker > >( "checker" );

      std::map< std::string, var_t >::const_iterator le_iter( p_ctx->var_map.find( "LITTLE_ENDIAN" ) );
      if ( le_iter != p_ctx->var_map.end() )
      {
        bool little_endian = !!( *le_iter->second.front().i );
        long pos = -1;
        long base = 0;
        element e;

        for ( std::size_t i = 0, n = vma_table.size(); i < n; i++ )
        {
          if ( vma_table[i].first <= address && address < vma_table[i].first + vma_table[i].second.size() )
          {
            pos = i;
            base = static_cast< long >( address - vma_table[i].first );
          }
        }
        if ( pos >= 0 )  // VMA �����ɤ߼��
        {
          std::tr1::uint64_t value = 0;
          if ( little_endian )
          {
            for ( long j = static_cast< long >( size-1 ); j >= 0; j-- )
            {
              int t = vma_table[ pos ].second[ base + j ];
              if ( t < 0 )
              {
                return var_t();
              }
              value = ( value << 8 ) | ( t & 0xff );
            }
          }
          else
          {
            for ( std::size_t j = 0; j < size; j++ )
            {
              int t = vma_table[ pos ].second[ base + j ];
              if ( t < 0 )
              {
                return var_t();
              }
              value = ( value << 8 ) | ( t & 0xff );
            }
          }
          e.i = value;
        }
        else  // VMA �ǤϤʤ��Τǡ�S�쥳���ɤ����ɤ߼��
        {
          e.i = chk->get( address, size, !!little_endian );
        }
        return var_t( 1, e );
      }
    }
    return var_t();
  }

  /*!
   *  \brief  ����֥�å���ž��
   *  \param[in]  line      ���ֹ�
   *  \param[in]  arg_list  �ޥ���°����ꥹ��
   *  \param[in]  p_ctx     �ޥ�����ƥ�����
   *  \retval     �ޥ����ֵ���
   *
   *  ��1������ž�������ɥ쥹����2������ž���襢�ɥ쥹����3������ž������Х��ȿ�����ꤷ�ޤ���
   *  ���ꤷ�����ԡ������ɥ쥹���饳�ԡ��襢�ɥ쥹�ء�����Х��ȿ��Υ���֥�å���ž�����ޤ���
   *  ���δؿ��ϡ�LMA����VMA�ؤΥ��ɥ쥹�Ѵ�����Ū�Ȥ��ƻ��Ѥ��뤳�Ȥ����ꤷ�Ƥ��ޤ���
   *
   *  \attention  �����Ȥ߹��ߴؿ��ϡ�LMA����VMA�ؤΥ��ɥ쥹�Ѵ������ꤷ�Ƥ��뤿�ᡢ���ˤ�ž����
   *              �����֤��褦�ʾ����ˤ��б����Ƥ��ޤ���ʥ�����­��ȯ�����ޤ��ˡ�
   */
  template < class Checker >
  var_t bf_bcopy( text_line const& line, std::vector< var_t > const& arg_list, context* p_ctx )
  {
    using namespace toppers;
    using namespace toppers::itronx;

    if ( macro_processor::check_arity( line, arg_list.size(), 3, "BCOPY" ) )
    {
      std::size_t src = static_cast< std::size_t >( macro_processor::to_integer( arg_list[0], p_ctx ) );
      std::size_t dst = static_cast< std::size_t >( macro_processor::to_integer( arg_list[1], p_ctx ) );
      std::size_t size = static_cast< std::size_t >( macro_processor::to_integer( arg_list[2], p_ctx ) );
      std::tr1::shared_ptr< Checker > chk = get_global< std::tr1::shared_ptr< Checker > >( "checker" );

      std::pair< std::tr1::int64_t, std::vector< unsigned char > > block;
      block.first = dst;
      block.second.reserve( size );
      for ( std::tr1::int64_t i = 0; i < size; i++ )
      {
        block.second.push_back( static_cast< unsigned char >( chk->get( static_cast< std::size_t >( src + i ), 1, true ) ) );
      }
      vma_table.push_back( block );
    }
    return var_t();
  }

}

namespace
{
  template < class Factory>
  inline bool cfg3_main_implementation( std::string const& kernel )
  {
    using namespace toppers;
    typedef typename Factory::cfg1_out Cfg1_out;

    Factory factory( kernel );
    global( "factory" ) = &factory;

    // *.cfg��cfg1_out.srec���ɤ߹���
    std::string input_file;
    try
    {
      get_global( "input-file", input_file );
    }
    catch ( boost::bad_any_cast& )
    {
      fatal( _( "no input files" ) );
    }
    std::string cfg1_out_name;
    get_global( "cfg1_out", cfg1_out_name );
    std::auto_ptr< Cfg1_out > cfg1_out( factory.create_cfg1_out( cfg1_out_name ) );

    codeset_t codeset = get_global< codeset_t >( "codeset" );
    cfg1_out->load_cfg( input_file, codeset, factory.get_cfg_info() );
    cfg1_out->load_srec();

    std::auto_ptr< typename Factory::checker > p_checker( factory.create_checker() );
    std::tr1::shared_ptr< typename Factory::checker > chk( p_checker );
    global( "checker" ) = chk;
    std::string rom_image( get_global_string( "rom-image" ) );
    std::string symbol_table( get_global_string( "symbol-table" ) );
    chk->load_rom_image( rom_image, symbol_table );

    // �ƥ�ץ졼�ȥե�����
    boost::any template_file( global( "template-file" ) );
    if ( template_file.empty() )
    {
      // �ƥ�ץ졼�ȥե����뤬���ꤵ��Ƥ��ʤ���к���¤Υ����å��Τߡʸ����ߴ����Τ����
      // �ѥ�᡼�������å�
      if ( !chk->check( *cfg1_out ) )
      {
        return false;
      }
    }
    else
    {
      namespace fs = boost::filesystem;

      // �ƥ�ץ졼�Ƚ���
      std::auto_ptr< macro_processor > mproc;
      std::auto_ptr< typename Factory::component > component_ptr;

      if ( get_global_bool( "with-software-components" ) )
      {
        mproc = factory.create_macro_processor( *cfg1_out, component_ptr );
      }
      else
      {
        mproc = factory.create_macro_processor( *cfg1_out );
      }

      // �� �ɲ��Ȥ߹��ߴؿ�����Ͽ
      toppers::macro_processor::func_t func_info = {};
      func_info.name = "SYMBOL";
      func_info.f = &bf_symbol< typename Factory::checker >;
      mproc->add_builtin_function( func_info );

      func_info.name = "PEEK";
      func_info.f = &bf_peek< typename Factory::checker >;
      mproc->add_builtin_function( func_info );

      func_info.name = "BCOPY";
      func_info.f = &bf_bcopy< typename Factory::checker >;
      mproc->add_builtin_function( func_info );
      // �� �ɲ��Ȥ߹��ߴؿ�����Ͽ

      fs::path cfg_dir( get_global_string( "cfg-directory" ) );  // filesystem3�б�
      std::vector< std::string > include_paths = get_global< std::vector< std::string > >( "include-path" );
      include_paths.push_back( cfg_dir.empty() ? "." : cfg_dir.string() );  // filesystem3�б�

      toppers::text in_text;
      toppers::text pp_text;
      std::string file_name( boost::any_cast< std::string& >( template_file ) );

      in_text.set_line( file_name, 1 );
      std::ifstream ifs( file_name.c_str() );
      if ( !ifs.is_open() )
      {
        fatal( _( "`%1%` can not be found." ), file_name );
      }

      in_text.append( ifs );
      macro_processor::preprocess( in_text, pp_text );
      mproc->evaluate( pp_text );

      if ( get_error_count() > 0 )
      {
        return false;
      }
      // ���ϥե����뤬���뤫�ɤ���ʬ����ʤ�������������֤��롣
      output_file::save();
    }

    // �ѥ�4�ʹߤ����ή�Ѥ���뤿�ᡢ���߽�����Υѥ���Ĵ�٤롣
    int pass = get_global< int >( "pass" );
    int max_pass = get_global< int >( "max-pass" );
    if ( max_pass == pass ) // �ǽ��ʳ��Υѥ������������Ȥ���"check complete"��å�������Ф���
    {
      std::cerr << _( "check complete" ) << std::endl;
    }

    return true;
  }
}

bool cfg3_main()
{
  std::string kernel;
  toppers::get_global( "kernel", kernel );

  if ( toppers::get_global_bool( "oil" ) )
  {
    return cfg3_main_implementation< toppers::oil::factory >( kernel );
  }
#ifdef  HAS_CFG_XML
  else if ( toppers::get_global_bool( "xml" ) )
  {
    return cfg3_main_implementation< toppers::xml::factory >( kernel );
  }
#endif
  else
  {
    return cfg3_main_implementation< toppers::itronx::factory >( kernel );
  }
}

/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2007-2011 by TAKAGI Nobuhisa
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
#include "cfg.hpp"
#include <boost/spirit/include/classic.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace
{
  template < class Factory >
  inline bool cfg2_main_implementation( std::string const& kernel )
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
    std::string cfg1_out_name( get_global_string( "cfg1_out" ) );
    std::auto_ptr< Cfg1_out > cfg1_out( factory.create_cfg1_out( cfg1_out_name ) );

    codeset_t codeset = get_global< codeset_t >( "codeset" );
    cfg1_out->load_cfg( input_file, codeset, factory.get_cfg_info() );
    if ( !get_global_bool( "omit-symbol" ) )
    {
      cfg1_out->load_srec();
    }

    std::auto_ptr< macro_processor > mproc;
    std::auto_ptr< typename Factory::component > component_ptr;

    if ( get_global_bool( "with-software-components" ) )
    {
      mproc = factory.create_macro_processor( *cfg1_out, component_ptr );
    }
    else  // ������͡ʥ��եȥ������������б���
    {
      mproc = factory.create_macro_processor( *cfg1_out );
    }

    // �ƥ�ץ졼�Ƚ���
    boost::any template_file( global( "template-file" ) );
    namespace fs = boost::filesystem;
    fs::path cfg_dir( get_global_string( "cfg-directory" ) );  // filesystem3�б�
    std::vector< std::string > include_paths = get_global< std::vector< std::string > >( "include-path" );
    include_paths.push_back( cfg_dir.empty() ? "." : cfg_dir.string() );  // filesystem3�б�
    if ( !template_file.empty() )
    {
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
    }
    else  // �ƥ�ץ졼�ȥե����뤬���ꤵ��Ƥ��ʤ��Τǡ�������ʬ��kernel.tf�ˤΤߤ����
    {
      fs::path kernel_cfg_template_file( cfg_dir/fs::path( "../../kernel/kernel.tf" ) );
      if ( !fs::exists( kernel_cfg_template_file ) )
      {
        error( _( "cannot open file `%1%\'" ), kernel_cfg_template_file.string() );  // filesystem3�б�
      }
      else
      {
        toppers::text in_text;
        toppers::text pp_text;

        in_text.set_line( kernel_cfg_template_file.string(), 1 );  // filesystem3�б�
        std::ifstream ifs( kernel_cfg_template_file.string().c_str() );  // filesystem3�б�
        in_text.append( ifs );
        macro_processor::preprocess( in_text, pp_text );
        mproc->evaluate( pp_text );
      }
    }

    if ( get_error_count() > 0 )
    {
      return false;
    }
    output_file::save();
    return true;
  }
}

/*!
 *  \brief  �ѥ�������
 *  \retval true  ����
 *  \retval false ����
 */
bool cfg2_main()
{
  std::string kernel;
  toppers::get_global( "kernel", kernel );
  if ( toppers::get_global_bool( "oil" ) )
  {
    return cfg2_main_implementation< toppers::oil::factory >( kernel );
  }
#ifdef  HAS_CFG_XML
  else if ( toppers::get_global_bool( "xml" ) )
  {
    return cfg2_main_implementation< toppers::xml::factory >( kernel );
  }
#endif
  else
  {
    return cfg2_main_implementation< toppers::itronx::factory >( kernel );
  }
}


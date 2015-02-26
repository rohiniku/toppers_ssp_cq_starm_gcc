/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2007-2012 by TAKAGI Nobuhisa
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
#include <cstdlib>
#include <cerrno>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stack>
#include "toppers/text.hpp"
#include "toppers/diagnostics.hpp"
#include "toppers/c_expr.hpp"
#include "toppers/global.hpp"
#include "toppers/macro_processor.hpp"
#include "toppers/s_record.hpp"
#include "toppers/nm_symbol.hpp"
#include "toppers/oil/cfg1_out.hpp"
#include "toppers/oil/preprocess.hpp"
#include "toppers/oil/configuration_manager.hpp"
#include <boost/spirit/include/classic_spirit.hpp>
#include <boost/filesystem/path.hpp>

using namespace toppers::oil::oil_definition;
using namespace toppers::configuration_manager;

namespace toppers
{
  namespace oil
  {
    namespace
    {
      struct block_t
      {
        std::string type;
        std::string id;
        text_line line;
      };
    }

    //! cfg_out ���饹�μ����ܺ�
    struct cfg1_out::implementation
    {
    protected:
      output_file ofile_;
      oil_def *oil_def_array;
      std::string cfg1_out_list_;
      std::string includes_;
      std::vector< block_t > block_table_;

      std::tr1::shared_ptr< s_record > srec_;
      std::tr1::shared_ptr< nm_symbol > syms_;
      bool little_endian_;
      std::size_t base_;
      cfg1_def_table const* def_table_;
      config_manage oil_configuration;

      implementation( std::string const& filename, std::ios_base::openmode omode, cfg1_def_table const* def_table = 0 )
        : ofile_( filename, omode ), little_endian_( true ), base_( 1 ), def_table_( def_table )
      {
      }
      virtual ~implementation()
      {
      }
      virtual void do_load_cfg( std::string const& input_file, codeset_t codeset,  std::vector<std::string> const& obj_info );
      virtual void do_generate_includes() const
      {
      }
      virtual void do_generate_cfg1_def() const
      {
        ofile_ << "const uint32_t TOPPERS_cfg_magic_number = 0x12345678;\n"
                  "const uint32_t TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);\n"
                  "const uint32_t TOPPERS_cfg_sizeof_pointer = sizeof(const volatile void*);\n"
                  "const unsigned_t TOPPERS_cfg_CHAR_BIT = ((unsigned char)~0u == 0xff ? 8 : 16);\n"  // CHAR_BIT��8�ޤ���16�ӥåȤǤ��뤳�Ȥ���
                  "const unsigned_t TOPPERS_cfg_CHAR_MAX = ((char)-1 < 0 ? (char)((unsigned char)~0u >> 1) : (unsigned char)~0u);\n"
                  "const unsigned_t TOPPERS_cfg_CHAR_MIN = ((char)-1 < 0 ? -((unsigned char)~0u >> 1) - 1 : 0);\n"
                  "const unsigned_t TOPPERS_cfg_SCHAR_MAX = (signed char)((unsigned char)~0u >> 1);\n"
                  "const unsigned_t TOPPERS_cfg_SHRT_MAX = (short)((unsigned short)~0u >> 1);\n"
                  "const unsigned_t TOPPERS_cfg_INT_MAX = (int)(~0u >> 1);\n"
                  "const unsigned_t TOPPERS_cfg_LONG_MAX = (long)(~0ul >> 1);\n"
                  "\n";

        if ( def_table_ != 0 )	// ���ͼ�������ܥ�ơ��֥��
        {
          for ( cfg1_def_table::const_iterator iter( def_table_->begin() ), last( def_table_->end() );
                iter != last;
                ++iter )
          {
            // ���κǽ�� # ������С�����ϥޥ��������Ƚ��
            // ����ա� #@ �ǻϤޤ�񼰤��ѻ� 2010/07/23
            bool is_pp = ( iter->expression[ 0 ] == '#' );
            if ( !iter->value1.empty() || !iter->value2.empty() ) // ��CSV�Ρ�4���ܤޤ���5���ܤ��ͤ������...
            {
              is_pp = true;
            }

            std::string type = ( iter->is_signed ? "signed_t" : "unsigned_t" );
            std::string definition = "const " + type + " ";
            definition += "TOPPERS_cfg_" + iter->name;
            if ( is_pp )
            {
              std::string expression = iter->expression.substr( iter->expression[ 0 ] == '#' ? 1 : 0 );
              std::string value1 = ( !iter->value1.empty() ? iter->value1 : "1" );
              std::string value2 = ( !iter->value2.empty() ? iter->value2 : "0" );
              definition +=
                          " = \n"
                          "#if " + expression + "\n"
                          "(" + value1 + ");\n"
                          "#else\n"
                          "(" + value2 + ");\n"
                          "#endif\n";
            }
            else if ( iter->expression[ 0 ] == '@' )  // '@'�ǻϤޤ�Х��ɥ쥹
            {
              definition = "const volatile void* const TOPPERS_cfg_" + iter->name + " = (" + ( iter->expression.c_str() + 1 ) + ");\n";
            }
            else
            {
              definition +=
                          " = ( " + type + " )" + iter->expression + ";\n";
            }
            ofile_ << definition;
          }
        }
      }
      virtual void do_assign_params();
      virtual implementation* do_clone() const
      {
        return new implementation( *this );
      }

      void preprocess( std::string const& input_file, codeset_t codeset, text& txt );

      friend class cfg1_out;
    };


    /*!
     *  \brief  ���󥹥ȥ饯��
     *  \param[in]  filename    cfg1_out.c �ޤ��� cfg1_out.srec �㤷���Ϥ���������̾
     *  \param[in]  def_table   cfg1_out.c �����Ѥ�����ơ��֥�
     */
    cfg1_out::cfg1_out( std::string const& filename, cfg1_def_table const* def_table )
      : pimpl_( new implementation( filename, std::ios_base::out, def_table ) )
    {
    }

    /*!
     *  \brief  ���ԡ����󥹥ȥ饯��
     *  \param[in]  other   ���ԡ���
     */
    cfg1_out::cfg1_out( cfg1_out const& other )
      : pimpl_( other.pimpl_->do_clone() )
    {
    }

    //! �ǥ��ȥ饯��
    cfg1_out::~cfg1_out()
    {
      delete pimpl_;
      pimpl_ = 0;
    }

    /*!
     *  \brief  �����ƥॳ��ե�����졼�����ե�����Υ���
     *  \param[in]  input_file  ���ϥե�����̾
     *  \param[in]  codeset     ʸ��������
     *  \param[in]  obj_info    ���֥������Ⱦ����Ϣ������
     */
    void cfg1_out::load_cfg( std::string const& input_file, codeset_t codeset, 
        std::vector<std::string> const& obj_info )
    {
      return pimpl_->do_load_cfg( input_file, codeset, obj_info );
    }

    //! ������
    void cfg1_out::implementation::preprocess( std::string const& input_file, codeset_t codeset, text& txt )
    {
      boost::any print_depend = global( "print-dependencies" );
      if ( !print_depend.empty() )
      {
        std::set< std::string > depend, onces;
        oil::preprocess( input_file, txt, codeset, &depend, &onces );

        // ��¸�ط��ν��ϡ�GNU make��Ŭ����������
        std::string target_file = boost::any_cast< std::string& >( print_depend );
        std::cout << target_file << ": " << input_file << ' ';
        std::copy( depend.begin(), depend.end(), std::ostream_iterator< std::string >( std::cout, " " ) );
        std::cout << std::endl;
        exit();
      }
      else
      {
        std::set< std::string > onces;
        oil::preprocess( input_file, txt, codeset, 0, &onces );
      }
    }

    /*!
     *  \brief  �����ƥॳ��ե�����졼�����ե�����Υ��ɽ����μ���
     *  \param[in]  input_file  ���ϥե�����̾
     *  \param[in]  codeset     ʸ��������
     *  \param[in]  obj_info    ���֥������Ⱦ����Ϣ������
     */
    void cfg1_out::implementation::do_load_cfg( std::string const& input_file, 
                codeset_t codeset, std::vector<std::string> const& obj_info )
    {

      text txt;
      // �����ƥॳ��ե�����졼�����ե�����β���
      std::ostringstream oss, includes_oss;

      preprocess( input_file, codeset, txt );

      // OIL������ɤ߽Ф�
      if(oil_configuration.read_configuration(&txt , obj_info) == true)
      {
        oil_def_array = oil_configuration.get_obj_def();
        oil_configuration.validate_and_assign_default_configuration();
      }

      // �ǡ������Фؤ�ȿ��
      std::string cfg1_list_temp( oss.str() );
      std::string includes_temp( includes_oss.str() );

      cfg1_out_list_.swap( cfg1_list_temp );
      includes_.swap( includes_temp );
    }

    /*!
     *  \brief  cfg1_out.c ����������
     *  \param[in]  type  ���� cfg1_out[] �����Ƿ������ݥ��󥿤ξ��� uint32_t �Ȥ��ư����롣
     */
    void cfg1_out::generate( char const* type ) const
    {
      if ( type == 0 )
      {
        type = "uint32_t";
      }
      pimpl_->ofile_ << "/* cfg1_out.c */\n"
                        "#define TOPPERS_CFG1_OUT  1\n" 
                        "#include \"osek_kernel.h\"\n"
                        "#include \"target_cfg1_out.h\"\n";
      pimpl_->do_generate_includes();
      pimpl_->ofile_ << pimpl_->includes_ << '\n';

      // int128_t�ϸΰդ�̵��
      // int128_t��·����Ƚ������Ť��ʤꤹ���뤿��
      if ( get_global< int >( "atk" ) < 2 )
      {
        pimpl_->ofile_ << "\n#ifdef INT64_MAX\n"
                          "  typedef int64_t signed_t;\n"
                          "  typedef uint64_t unsigned_t;\n"
                          "#else\n"
                          "  typedef int32_t signed_t;\n"
                          "  typedef uint32_t unsigned_t;\n"
                          "#endif\n";
      }
      else
      {
        pimpl_->ofile_ << "\n#ifdef INT64_MAX\n"
                          "  typedef sint64 signed_t;\n"
                          "  typedef uint64 unsigned_t;\n"
                          "#else\n"
                          "  typedef sint32 signed_t;\n"
                          "  typedef uint32 unsigned_t;\n"
                          "#endif\n";
      }

      pimpl_->ofile_ << "\n#include \"target_cfg1_out.h\"\n\n";

      pimpl_->do_generate_cfg1_def();
      pimpl_->ofile_ << pimpl_->cfg1_out_list_ << '\n';
    }

    /*!
     *  \brief  #include������¤Ӥ��������
     *  \return #include������¤�
     *
     *  ���Υ��дؿ��ϡ�
     *  \code
     *  #include <...>
     *  #include "..."
     *  \endcode
     *  �Ȥ��ä�#include������¤Ӥ�ʸ����Ȥ����֤���
     */
    std::string const& cfg1_out::get_includes() const
    {
      return pimpl_->includes_;
    }

    /*!
     *  \brief  S�쥳���ɤΥ���
     */
    void cfg1_out::load_srec()
    {
      std::ifstream srec_ifs( ( pimpl_->ofile_.file_name() + ".srec" ).c_str() );
      if ( !srec_ifs.is_open() )
      {
        fatal( _( "cannot open file `%1%\'" ), pimpl_->ofile_.file_name() + ".srec" );
      }
      pimpl_->srec_ = std::tr1::shared_ptr< s_record >( new s_record( srec_ifs ) );

      std::ifstream syms_ifs( ( pimpl_->ofile_.file_name() + ".syms" ).c_str() );
      if ( !syms_ifs.is_open() )
      {
        fatal( _( "cannot open file `%1%\'" ), pimpl_->ofile_.file_name() + ".syms" );
      }
      pimpl_->syms_ = std::tr1::shared_ptr< nm_symbol >( new nm_symbol( syms_ifs ) );

      nm_symbol::entry nm_entry = pimpl_->syms_->find( "TOPPERS_cfg_magic_number" );
      if ( nm_entry.type < 0 )
      {
        fatal( _( "magic number is not found in `%1%\'" ), ( pimpl_->ofile_.file_name() + ".srec/.syms" ) );
      }
      unsigned long magic[ 4 ];
      magic[ 0 ] = ( *pimpl_->srec_ )[ nm_entry.address + 0 ];
      magic[ 1 ] = ( *pimpl_->srec_ )[ nm_entry.address + 1 ];
      magic[ 2 ] = ( *pimpl_->srec_ )[ nm_entry.address + 2 ];
      magic[ 3 ] = ( *pimpl_->srec_ )[ nm_entry.address + 3 ];
      unsigned long magic_number = ( magic[ 0 ] << 24 ) | ( magic[ 1 ] << 16 ) | ( magic[ 2 ] << 8 ) | magic[ 3 ];
      if ( magic_number == 0x12345678 )
      {
        pimpl_->little_endian_ = false;
      }
      else if ( magic_number == 0x78563412 )
      {
        pimpl_->little_endian_ = true;
      }
      else
      {
        fatal( _( "magic number is not found in `%1%\'" ), ( pimpl_->ofile_.file_name() + ".srec/.syms" ) );
      }
      pimpl_->do_assign_params();
    }

    /*!
     *  \brief  "cfg1_out.srec" �����ɤ߼�ä�����λ���
     */
    std::tr1::shared_ptr< s_record > cfg1_out::get_srec() const
    {
      return pimpl_->srec_;
    }

    /*!
     *  \brief  "cfg1_out.syms" �����ɤ߼�ä�����λ���
     */
    std::tr1::shared_ptr< nm_symbol > cfg1_out::get_syms() const
    {
      return pimpl_->syms_;
    }

    cfg1_out::cfg1_def_table const* cfg1_out::get_def_table() const
    {
      return pimpl_->def_table_;
    }

    /*!
     *  \brief  ���֥������Ȥ��Ȥ�OIL���֥������Ⱦ����ޤȤ��
     *  \return ��ŪAPI����
     *
     *  ���δؿ��ϡ�"tsk"��"sem"�Ȥ��ä����̤򥭡��Ȥ��ơ����μ��̤�ʬ�व�����ŪAPI�����Ϣ��������������롣
     */
    cfg1_out::cfg_obj_map cfg1_out::merge() const
    {
      cfg_obj_map result;
      result = oil_definition::merge(pimpl_->oil_def_array , result);
      return result;
    }

    /*!
     *  \brief  ��ȥ륨��ǥ����󤫤ɤ�����Ƚ��
     *  \retval     true  ��ȥ륨��ǥ�����
     *  \retval     false �ӥå�����ǥ�����
     *  \attention  load_srec �ƤӽФ�������������̤������ʤ���
     */
    bool cfg1_out::is_little_endian() const
    {
      return pimpl_->little_endian_;
    }

    /*!
     *  \brief  ��ŪAPI�Υѥ�᡼����S�쥳���ɤ�����������ͤ���������
     */
    void cfg1_out::implementation::do_assign_params()
    {
    }

    /*!
     *  \brief  --id-input-file���ץ����ǻ��ꤷ���ե�������ɤ߹���
     *  \id_map �ɤ߹�����ǡ����γ�Ǽ��
     */
    void cfg1_out::load_id_input_file( std::map< std::string, std::pair< long, bool > >& id_map )
    {
      std::string id_input_file( get_global_string( "id-input-file" ) );
      if ( id_input_file.empty() )
      {
        return;
      }

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
          fatal( _( "`%1%\' is duplicated" ), name );
        }
        else
        {
          id_map[ name ] = std::make_pair( value, false );
        }
      }
    }
  }
}

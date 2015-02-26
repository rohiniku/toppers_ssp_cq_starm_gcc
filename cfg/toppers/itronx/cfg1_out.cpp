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
#include "toppers/misc.hpp"
#include "toppers/itronx/cfg1_out.hpp"
#include "toppers/itronx/preprocess.hpp"
#include <boost/spirit/include/classic.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>

namespace toppers
{
  namespace itronx
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
      std::vector< static_api > static_api_array_;
      std::string cfg1_out_list_;
      std::string includes_;
      std::string domid_defs_;
      std::vector< block_t > block_table_;
      std::vector< std::pair< std::string, long > > clsid_table_;
      std::vector< std::pair< std::string, long > > domid_table_;

      std::tr1::shared_ptr< s_record > srec_;
      std::tr1::shared_ptr< nm_symbol > syms_;
      bool little_endian_;
      std::size_t base_;
      cfg1_def_table const* def_table_;

      implementation( std::string const& filename, std::ios_base::openmode omode, cfg1_def_table const* def_table = 0 )
        : ofile_( filename, omode ), little_endian_( true ), base_( 1 ), def_table_( def_table )
      {
      }
      virtual ~implementation()
      {
      }
      virtual void do_load_cfg( std::string const& input_file, codeset_t codeset, std::map< std::string, static_api::info > const& info_map );
      virtual void do_generate_includes() const
      {
      }
      virtual void do_generate_cfg1_def() const
      {
        std::string kernel( get_global_string( "kernel" ) );
        if ( kernel == "atk2_osap" || kernel == "atk2_no_osap" )
        {
          ofile_ << "const uint32 TOPPERS_cfg_magic_number = 0x12345678;\n"
                    "const uint32 TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);\n"
                    "const uint32 TOPPERS_cfg_sizeof_pointer = sizeof(const volatile void*);\n";
        }
        else
        {
          ofile_ << "const uint32_t TOPPERS_cfg_magic_number = 0x12345678;\n"
                    "const uint32_t TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);\n"
                    "const uint32_t TOPPERS_cfg_sizeof_pointer = sizeof(const volatile void*);\n";
        }
        ofile_ << "const unsigned_t TOPPERS_cfg_CHAR_BIT = ((unsigned char)~0u == 0xff ? 8 : 16);\n"  // CHAR_BIT��8�ޤ���16�ӥåȤǤ��뤳�Ȥ���
                  "const unsigned_t TOPPERS_cfg_CHAR_MAX = ((char)-1 < 0 ? (char)((unsigned char)~0u >> 1) : (unsigned char)~0u);\n"
                  "const unsigned_t TOPPERS_cfg_CHAR_MIN = (unsigned_t)((char)-1 < 0 ? -((unsigned char)~0u >> 1) - 1 : 0);\n"
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
     *  \param[in]  info_map    ��ŪAPI�����Ϣ������
     */
    void cfg1_out::load_cfg( std::string const& input_file, codeset_t codeset, std::map< std::string, static_api::info > const& info_map )
    {
      return pimpl_->do_load_cfg( input_file, codeset, info_map );
    }

    //! ������
    void cfg1_out::implementation::preprocess( std::string const& input_file, codeset_t codeset, text& txt )
    {
      boost::any print_depend = global( "print-dependencies" );
      if ( !print_depend.empty() )
      {
        std::set< std::string > depend, onces;
        itronx::preprocess( input_file, txt, codeset, &depend, &onces );

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
        itronx::preprocess( input_file, txt, codeset, 0, &onces );
      }
    }

    /*!
     *  \brief  �����ƥॳ��ե�����졼�����ե�����Υ��ɽ����μ���
     *  \param[in]  input_file  ���ϥե�����̾
     *  \param[in]  codeset     ʸ��������
     *  \param[in]  info_map    ��ŪAPI�����Ϣ������
     */
    void cfg1_out::implementation::do_load_cfg( std::string const& input_file, codeset_t codeset, std::map< std::string, static_api::info > const& info_map )
    {
      text txt;
      preprocess( input_file, codeset, txt );

      // �����ƥॳ��ե�����졼�����ե�����β���
      std::ostringstream oss, includes_oss;
      std::vector< static_api > api_array;
      long serial = 0;
      std::stack< block_t > block_stack;
      std::vector< block_t > block_table;
      std::string current_class, current_domain;
      long domain_serial = 1;
      std::map< std::string, std::pair< long, bool > > id_map;
      std::vector< std::pair< std::string, long > > clsid_table;
      std::vector< std::pair< std::string, long > > domid_table;

      for ( text::const_iterator iter( txt.begin() ), last( txt.end() ); iter != last; ++iter )
      {
        using namespace boost::spirit::classic;
        parse_info< text::const_iterator > info;

        info = parse( iter, last, ( ch_p( '#' ) >> *( anychar_p - eol_p ) >> eol_p ) ); // ����������θ���
        if ( info.hit ) // ����������ʤ��...
        {
          if ( std::size_t col = info.stop.get_col() )
          {
            if ( info.stop.get_row()->buf.find_first_not_of( " \t" ) < col )
            {
              error( _( "illegal character `%1%\' is found" ), '#' );
            }
          }
          text::const_iterator stop = info.stop;
          std::string directive;
          info = parse( iter, last, ( ch_p( '#' ) >> ( +alnum_p )[ assign_a( directive ) ] >> *( anychar_p - eol_p ) >> eol_p ) );
          if ( info.hit )
          {
            if ( directive == "include" )
            {
              std::string directive_line_str( iter, info.stop );
              if ( *directive_line_str.rbegin() == '\n' )
              {
                directive_line_str.erase( directive_line_str.size() - 1 );
              }
              includes_oss << directive_line_str << '\n';
              oss << "/* " << directive_line_str << " */\n";
            }
            else if ( directive == "if" || directive == "ifdef" || directive == "ifndef"
                   || directive == "else" || directive == "elif" || directive == "endif" )
            {
              oss << '\n' << std::string( iter, stop );
            }
            else if ( directive != "pragma" ) // ����ե�����졼�����������٤�#pragma����Ϥ��λ����ǤϽ����Ƥ���
            {
              error( iter.line(), _( "`#%1%\' is not supported" ), directive );
            }
          }
          else
          {
            oss << std::string( iter, stop );
          }
          iter = boost::prior( stop );
        }
        else // ����������ǤϤʤ�...
          if ( !std::isspace( static_cast< unsigned char >( *iter ) ) )
        {
          while ( iter != last )
          {
            int ch = static_cast< unsigned char >( *iter );
            if ( !std::isspace( ch ) )
            {
              break;
            }
          }

          std::string block_type;
          std::string id;
          std::string idexp;
          c_const_expr_parser const c_const_expr_p;
          info = parse( iter, last,
                        (
                          str_p( "DOMAIN" )[ assign_a( block_type ) ]
                          >> '(' >> c_ident_p[ assign_a( id ) ] >> ')' >> '{'
                        )
                      | (
                          str_p( "CLASS" )[ assign_a( block_type ) ]
                          >> '(' >> c_const_expr_p[ assign_a( id ) ] >> ')' >> '{'
                        )
                      | (
                          str_p( "KERNEL_DOMAIN" )[ assign_a( block_type ) ] >> '{'
                        ),
                        space_p );
          if ( info.hit )               // CLASS or DOMAIN�֥�å����Ϥʤ��...
          {
            block_t b;
            b.type = block_type;
            b.id = id;
            b.line = iter.line();
            idexp = id; // ���̤Ȥ��Ƥ�ID����¸

            if ( block_type == "CLASS" )
            {
              if ( !get_global_bool( "has-class" ) )
              {
                error( "cannot use `%1%'", "CLASS" );
              }
            }
            if ( block_type == "DOMAIN" || block_type == "KERNEL_DOMAIN"  )
            {
              if ( !get_global_bool( "has-domain" ) )
              {
                error( "cannot use `%1%'", block_type );
              }
            }
            // �����ͥ�ɥᥤ����̾�Υɥᥤ���Ʊ���褦�˰�����褦���ѷ�
            if ( block_type == "KERNEL_DOMAIN" )
            {
              block_type = "DOMAIN";
              id = "TDOM_KERNEL";
              b.type = block_type;
              b.id = id;
            }
            else if ( block_type == "DOMAIN" ) // �ɥᥤ��ID�β���Ͽ
            {
              bool hit = false;
              for ( std::vector< std::pair< std::string, long > >::const_iterator iter( domid_table.begin() ), last( domid_table.end() );
                    iter != last;
                    ++iter )
              {
                if ( iter->first == id )
                {
                  hit = true;
                  break;
                }
              }
              if ( !hit )
              {
                domid_table.push_back( std::make_pair( id, 0L ) );
              }
            }
            else if ( block_type == "CLASS" ) // ���饹ID����Ͽ
            {
              // ���饹ID�˼���Ȥ���褦�ˤ������ᡢ���̻Ҥ˻Ȥ���������Ѵ�����ɬ�פ�����
              std::tr1::uint64_t hash = 0;
              for ( const char* s = id.c_str(); *s != '\0'; ++s )
              {
                hash = ( ( hash << 1 ) | ( hash >> 63 ) ) ^ static_cast< unsigned char >( *s );
              }
              id = boost::str( boost::format( "%02x_%016x_%u" ) % *id.c_str() % hash % id.size() );
              b.id = id;

              bool hit = false;
              for ( std::vector< std::pair< std::string, long > >::const_iterator iter( clsid_table.begin() ), last( clsid_table.end() );
                    iter != last;
                    ++iter )
              {
                if ( iter->first == id )
                {
                  hit = true;
                  break;
                }
              }
              if ( !hit )
              {
                clsid_table.push_back( std::make_pair( id, 0L ) );
              }
            }

            // �����Ƚ��
            if ( block_type == "CLASS" && !current_class.empty()
              || block_type == "DOMAIN" && !current_domain.empty() )
            {
              fatal( iter.line(), _( "`%1%\' is nested" ), block_type );
            }

            block_stack.push( b );
            block_table.push_back( b );

            if ( block_type == "CLASS" )
            {
              oss << "\n#ifndef TOPPERS_cfg_valueof_" << id << "_DEFINED\n"
                    "#define TOPPERS_cfg_valueof_" << id << "_DEFINED 1\n";
              oss << boost::format( "\n#line %1% \"%2%\"\n" ) % ( iter.line().line ) % dir_delimiter_to_slash( iter.line().file );

              current_class = idexp;
              oss << "const unsigned_t TOPPERS_cfg_valueof_" << id << " = " << idexp << ";\n";
            }
            if ( block_type == "DOMAIN" )
            {
              oss << "\n#ifndef TOPPERS_cfg_valueof_" << id << "_DEFINED\n"
                    "#define TOPPERS_cfg_valueof_" << id << "_DEFINED 1\n";
              oss << boost::format( "\n#line %1% \"%2%\"\n" ) % ( iter.line().line ) % dir_delimiter_to_slash( iter.line().file );

              current_domain = id;
              oss << "const unsigned_t TOPPERS_cfg_valueof_" << id << " = ";
              if ( id == "TDOM_KERNEL" )
              {
                oss << "( unsigned_t ) (-1)" << ";\n";
              }
              else
              {
                oss << id << ";\n";
              }
            }
            oss << "\n#endif\n";

            oss << "#define TOPPERS_cfg_inside_of_" << id << "\n";

            iter = boost::prior( info.stop );
          }
          else if ( *info.stop == '}' ) // �֥�å������ʤ��...
          {
            if ( block_stack.empty() )
            {
              fatal( iter.line(), _( "syntax error" ) );
            }
            block_t b = block_stack.top();
            block_stack.pop();

            oss << "\n#ifndef TOPPERS_cfg_inside_of_" << b.id << "\n";
            oss << boost::format( "\n#line %1% \"%2%\"\n" ) % ( iter.line().line ) % dir_delimiter_to_slash( iter.line().file );
            oss << "#error syntax error\n"
                    "#endif\n";
            oss << "#undef TOPPERS_cfg_inside_of_" << b.id << "\n"
                    "\n";

            if ( b.type == "CLASS" )
            {
              current_class.clear();
            }
            if ( b.type == "DOMAIN" )
            {
              current_domain.clear();
            }
            iter = info.stop;
          }
          else
          {
            static_api api;
            if ( api.parse( iter, last, info_map, false, codeset ) )  // ��ŪAPI�ʤ��...
            {
              if ( !current_class.empty() )
              {
                api.set_class( current_class );
                oss << "const unsigned_t TOPPERS_cfg_valueof_CLASS_" << serial << " = " << current_class << ";";
              }
              if ( !current_domain.empty() )
              {
                api.set_domain( current_domain );
                oss << "const unsigned_t TOPPERS_cfg_valueof_DOMAIN_" << serial << " = ( unsigned_t ) ( " << current_domain << " );";
              }

              api_array.push_back( api );

              oss << boost::format( "\n#line %1% \"%2%\"\n" ) % api.line().line % dir_delimiter_to_slash( api.line().file );
              oss << "const unsigned_t TOPPERS_cfg_static_api_" << serial << " = " << serial << ";\n";

              if ( !api.params().empty() && api.begin()->symbol[0] == '#' )   // ���֥������ȼ���̾
              {
                std::string object_id( api.begin()->text );
                bool valid_object_id = true;
                if ( !object_id.empty() && ( std::isalpha( static_cast< unsigned char >( object_id[ 0 ] ) ) || object_id[ 0 ] == '_' ) )
                {
                  for ( std::string::const_iterator id_iter( object_id.begin() + 1 ), id_last( object_id.end() );
                        id_iter != id_last;
                        ++id_iter )
                  {
                    if ( !( std::isalnum( static_cast< unsigned char >( *id_iter ) ) || *id_iter == '_' ) )
                    {
                      valid_object_id = false;
                    }
                  }
                }
                else
                {
                  valid_object_id = false;
                }
                if ( !valid_object_id )
                {
                  error( _( "`%1%\' is illegal object identifier" ), object_id );
                }
                else
                {
                  oss << "#define " << object_id << "\t(<>)\n";   // �Ǥ����ʻ���ʴ��ܥ�����ʸ������Τߤǹ����ˤ�������뤳�Ȥǡ�����Ѥ򸡽Ф���
                  oss << boost::format( "\n#line %1% \"%2%\"\n" ) % ( api.line().line ) % dir_delimiter_to_slash( api.line().file );
                }
              }
              for ( static_api::iterator api_iter( api.begin() ), api_last( api.end() );
                    api_iter != api_last;
                    ++api_iter )
              {
                if ( ( api_iter->symbol[0] == '.' ) || ( api_iter->symbol[0] == '+' ) )
                    // ����������ѥ�᡼���Τ߽���
                {
                  char const* type;
                  if ( api_iter->symbol[0] == '.' )
                  {
                    type = "unsigned_t";
                  }
                  else
                  {
                    type = "signed_t";
                  }
                  oss << "const " << type << " ";

                  // ��ά��ǽ�ѥ�᡼������������ˤ��� ? �����
                  std::string parameter_name( api_iter->symbol.c_str() + 1 );
                  if ( *parameter_name.rbegin() == '\?' )
                  {
                    parameter_name.resize( parameter_name.size() - 1 );
                  }
                  // ������ ... ����� & order ���ղ�
                  if ( parameter_name.size() > 3 && parameter_name.substr( parameter_name.size() - 3 ) == "..." )
                  {
                    parameter_name.resize( parameter_name.size() - 3 );
                    parameter_name += boost::lexical_cast< std::string >( api_iter->order );
                  }

                  oss << "TOPPERS_cfg_valueof_" << parameter_name << "_" << serial << " = ( " << type << " )( " << api_iter->text << " ); ";

                  // �����ͤ�����
                  char* endptr;
                  errno = 0;
                  unsigned long value = std::strtoul( api_iter->text.c_str(), &endptr, 0 );
                  if ( errno == 0 && *endptr == '\0' )
                  {
                    api_iter->value = value;
                  }
                }
                else if ( api_iter->symbol[0] == '$' )  // ʸ����������ѥ�᡼��
                {
                  // ��ά��ǽ�ѥ�᡼������������ˤ��� ? �����
                  std::string parameter_name( api_iter->symbol.c_str() + 1 );
                  if ( *parameter_name.rbegin() == '\?' )
                  {
                    parameter_name.resize( parameter_name.size() - 1 );
                  }
                  // ������ ... ����� & order ���ղ�
                  if ( parameter_name.size() > 3 && parameter_name.substr( parameter_name.size() - 3 ) == "..." )
                  {
                    parameter_name.resize( parameter_name.size() - 3 );
                    parameter_name += boost::lexical_cast< std::string >( api_iter->order );
                  }

                  oss << "const char TOPPERS_cfg_valueof_" << parameter_name << "_" << serial << "[] = " << api_iter->text << "; ";
                }
              }
            }
            else
            {
              fatal( iter.line(), _( "syntax error" ) );
            }

            ++serial;
            iter = boost::prior( iter );
          }
        }
      }

      for ( std::vector< block_t >::const_iterator iter( block_table.begin() ), last( block_table.end() );
            iter != last;
            ++iter )
      {
        oss << "\n#ifdef TOPPERS_cfg_inside_of_" << iter->id << "\n";
        oss << "#error missing \'}\'\n"
               "#endif\n";
      }

      // ������ͽ�1.1.0�ˤ�����2.14.2 TOPPERS���̥ǡ������ε���ˤ�ꡢACPTN��32�ӥå����̵���������Ǥ��롣
      // ����ˤ�ꡢ�ɥᥤ��κ������32�ĤǤʤ���Фʤ�ʤ���
      const std::size_t domain_max = 32;
      if ( domid_table.size() > domain_max )
      {
        fatal( _( "there are too many %1% ids" ), "domain" );
      }

      std::string domid_defs_temp;

      if ( get_global_bool( "has-domain" ) )
      {
        load_id_input_file( id_map ); // --id-input-file�ˤ��ɥᥤ��ID���ɤ߹���

        std::string domids[ domain_max ];

        // ����ܤϡ�--id-input-file���ץ�����ȿ��
        for ( std::vector< std::pair< std::string, long > >::iterator iter( domid_table.begin() ), last( domid_table.end() );
              iter != last;
              ++iter )
        {
          std::map< std::string, std::pair< long, bool > >::iterator hit = id_map.find( iter->first );
          if ( hit != id_map.end() )
          {
            long domid = hit->second.first; // --id-input-file���ץ����ǻ��ꤵ�줿��
            if ( domid > 32 )
            {
              fatal( _( "%1% id `%2%' is too large" ), "domain", hit->first );
            }
            domids[ domid - 1 ] = hit->first;
          }
        }
        // ����ܤϡ��Ĥ�Υɥᥤ��ID�����դ���
        for ( std::vector< std::pair< std::string, long > >::iterator iter( domid_table.begin() ), last( domid_table.end() );
              iter != last;
              ++iter )
        {
          if ( id_map.find( iter->first ) == id_map.end() )
          {
            for ( int i = 0; i < sizeof( domids ) / sizeof( domids[ 0 ] ); i++ )
            {
              if ( domids[ i ].empty() )
              {
                domids[ i ] = iter->first;
                break;
              }
            }
          }
        }
        domid_table.clear();
        for ( std::size_t i = 0; i < sizeof( domids ) / sizeof( domids[ 0 ] ); i++ )
        {
          domid_table.push_back( std::make_pair( domids[ i ], long( i + 1 ) ) );
        }

        // cfg1_out.c�����ѤΥ����ɤ�����
        for ( std::vector< std::pair< std::string, long > >::iterator iter( domid_table.begin() ), last( domid_table.end() );
              iter != last;
              ++iter )
        {
          if ( !iter->first.empty() )
          {
            domid_defs_temp += ( boost::format( "#define %1%\t%2%\n" ) % iter->first % iter->second ).str();
          }
        }
      }

      // �ǡ������Фؤ�ȿ��
      std::string cfg1_list_temp( oss.str() );
      std::string includes_temp( includes_oss.str() );

      clsid_table_.swap( clsid_table );
      domid_table_.swap( domid_table );
      domid_defs_.swap( domid_defs_temp );
      cfg1_out_list_.swap( cfg1_list_temp );
      includes_.swap( includes_temp );
      static_api_array_.swap( api_array );
      block_table_.swap( block_table );
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
                        "#include \"kernel/kernel_int.h\"\n";
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
      pimpl_->ofile_ << '\n' << pimpl_->domid_defs_ << '\n';
      pimpl_->ofile_ << pimpl_->cfg1_out_list_ << '\n';
    }

    /*!
     *  \brief  ��ŪAPI����λ���
     *  \return �������ݻ����Ƥ�����ŪAPI����ؤλ���
     */
    std::vector< static_api > const& cfg1_out::get_static_api_array() const
    {
      return pimpl_->static_api_array_;
    }

    /*!
     *  \brief  �ɥᥤ��ID�ơ��֥�λ���
     *  \return �������ݻ����Ƥ���ɥᥤ��ID�ơ��֥�ؤλ���
     */
    std::vector< std::pair< std::string, long > > const& cfg1_out::get_domid_table() const
    {
      return pimpl_->domid_table_;
    }

    /*!
     *  \brief  ���饹ID�ơ��֥�λ���
     *  \return �������ݻ����Ƥ��륯�饹ID�ơ��֥�ؤλ���
     */
    std::vector< std::pair< std::string, long > > const& cfg1_out::get_clsid_table() const
    {
      return pimpl_->clsid_table_;
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
      if ( pimpl_->def_table_ == 0 )
      {
        pimpl_->little_endian_ = false; // �ͤ�����ˤʤ뤳�Ȥ����
        return;
      }

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
     *  \brief  �����ͥ륪�֥������Ȥ��Ȥ���ŪAPI�����ޤȤ��
     *  \return ��ŪAPI����
     *
     *  ���δؿ��ϡ�"tsk"��"sem"�Ȥ��ä����̤򥭡��Ȥ��ơ����μ��̤�ʬ�व�����ŪAPI�����Ϣ��������������롣
     */
    cfg1_out::static_api_map cfg1_out::merge() const
    {
      static_api_map result;
      for ( std::vector< static_api >::const_iterator iter( pimpl_->static_api_array_.begin() ), last( pimpl_->static_api_array_.end() );
            iter != last;
            ++iter )
      {
        static_api::info const* info = iter->get_info();
        if ( info != 0 )
        {
          result[ info->type ].push_back( *iter );
        }
      }
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
      std::vector< toppers::itronx::static_api > temp_array;

      for ( std::vector< static_api >::size_type serial = 0, n = static_api_array_.size(); serial < n; ++serial )
      {
        toppers::itronx::static_api api( static_api_array_.at( serial ) );

        nm_symbol::entry nm_entry = syms_->find( boost::str( boost::format( "TOPPERS_cfg_static_api_%d" ) % serial ) );
        if ( nm_entry.type == -1 )
        {
          continue;
        }

        // sizeof( signed_t )
        std::size_t const sizeof_signed_t = static_cast< std::size_t >( srec_->get_value( syms_->find( "TOPPERS_cfg_sizeof_signed_t" ).address, 4, little_endian_ ) );

        for ( toppers::itronx::static_api::iterator api_iter( api.begin() ),
                                                    api_last( api.end() );
              api_iter != api_last;
              ++api_iter )
        {
          if ( ( api_iter->symbol[0] == '.' ) || ( api_iter->symbol[0] == '+' ) || ( api_iter->symbol[0] == '*' ) )
            // ����������ѥ�᡼���Τ��ͤ����
          {
            std::string parameter_name( api_iter->symbol.c_str() + 1 );

            // ��ά��ǽ�ѥ�᡼������������ˤ��� ? �����
            if ( *parameter_name.rbegin() == '\?' )
            {
              parameter_name.resize( parameter_name.size() - 1 );
            }

            // ������ ... ����� & order ���ղ�
            if ( parameter_name.size() > 3 && parameter_name.substr( parameter_name.size() - 3 ) == "..." )
            {
              parameter_name.resize( parameter_name.size() - 3 );
              parameter_name += boost::lexical_cast< std::string >( api_iter->order );
            }

            std::string symbol = boost::str( boost::format( "TOPPERS_cfg_valueof_%s_%d" ) % parameter_name % serial );
            nm_symbol::entry nm_entry = syms_->find( symbol );
            if ( nm_entry.type == -1 )
            {
              continue;
            }
            const std::size_t size = sizeof_signed_t;
            std::tr1::intmax_t value = srec_->get_value( nm_entry.address, size, little_endian_ );

            if ( api_iter->symbol[0] == '+' )
            {
              value = make_signed( static_cast< std::tr1::uint32_t >( value ) );
            }
            api_iter->value = value;
          }
          else if ( api_iter->symbol[0] == '$' )  // ʸ����������ѥ�᡼��
          {
            std::string parameter_name( api_iter->symbol.c_str() + 1 );

            // ��ά��ǽ�ѥ�᡼������������ˤ��� ? �����
            if ( *parameter_name.rbegin() == '\?' )
            {
              parameter_name.resize( parameter_name.size() - 1 );
            }

            // ������ ... ����� & order ���ղ�
            if ( parameter_name.size() > 3 && parameter_name.substr( parameter_name.size() - 3 ) == "..." )
            {
              parameter_name.resize( parameter_name.size() - 3 );
              parameter_name += boost::lexical_cast< std::string >( api_iter->order );
            }

            std::string symbol = boost::str( boost::format( "TOPPERS_cfg_valueof_%s_%d" ) % parameter_name % serial );
            nm_symbol::entry nm_entry = syms_->find( symbol );
            if ( nm_entry.type == -1 )
            {
              continue;
            }
            std::string string;
            string.reserve( 256 );
            char c;
            for ( long i = 0; ( c = static_cast< char >( srec_->get_value( nm_entry.address + i, 1, little_endian_ ) ) ) != '\0'; i++ )
            {
              string.push_back( c );
            }

            api_iter->string = string;
          }
        }
        temp_array.push_back( api );
      }
      static_api_array_.swap( temp_array );
    }

    /*!
     *  \brief  --id-input-file���ץ����ǻ��ꤷ���ե�������ɤ߹���
     *  \id_map �ɤ߹�����ǡ����γ�Ǽ��
     */
    void cfg1_out::load_id_input_file( std::map< std::string, std::pair< long, bool > >& id_map )
    {
      std::string id_input_file( get_global< std::string >( "id-input-file" ) );
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
          fatal( _( "E_OBJ: `%1%\' is duplicated" ), name );
        }
        else
        {
          id_map[ name ] = std::make_pair( value, false );
        }
      }
    }

  }
}

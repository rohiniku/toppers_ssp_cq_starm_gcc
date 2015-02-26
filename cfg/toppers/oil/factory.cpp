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
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/spirit/include/classic_spirit.hpp>
#include "toppers/misc.hpp"
#include "toppers/global.hpp"
#include "toppers/csv.hpp"
#include "toppers/nm_symbol.hpp"
#include "toppers/s_record.hpp"
#include "toppers/diagnostics.hpp"
#include "toppers/macro_processor.hpp"
#include "toppers/io.hpp"
#include "toppers/cpp.hpp"
#include "toppers/oil/factory.hpp"
#include "toppers/oil/cfg1_out.hpp"

namespace toppers
{
  namespace oil
  {
    namespace
    {

    object_definition* find_object(string name , cfg1_out::cfg_obj_map const& obj_def_map)
    {
          // modified by takuya 110823
      //std::map< std::string, std::vector<object_definition*>>::const_iterator p;
      std::map< std::string, std::vector<object_definition*> >::const_iterator p;
      std::vector<object_definition*>::const_iterator q;
    
      // ̾�������פ��륪�֥������Ȥ򸡺�
      for(p = obj_def_map.begin() ; p != obj_def_map.end() ; p++)
      {
        for(q = (*p).second.begin() ; q != (*p).second.end() ; q++)
        {
          if((*q)->get_name() == name)
          {
            return (*q);
          }
        }
      }    
      return NULL;
    }

      // �����ͥ륪�֥��������������������ŪAPI�γƥѥ�᡼����ޥ���ץ��å����ѿ��Ȥ������ꤹ�롣
      void set_object_vars( cfg1_out::cfg_obj_map const& obj_def_map, macro_processor& mproc )
      {
        typedef macro_processor::element element;
        typedef macro_processor::var_t var_t;
        std::map< std::string, var_t > order_list_map , obj_parameter;
        std::map< std::string, long > id_map;

    using namespace toppers::oil::oil_definition;
        // modified by takuya 110823
    //std::map< std::string, std::vector<object_definition*>>::const_iterator p;
    std::map< std::string, std::vector<object_definition*> >::const_iterator p;
    std::vector<object_definition*>::const_iterator q;
    std::vector<object_parameter_def*>::const_iterator r;

        for ( p = obj_def_map.begin() ; p != obj_def_map.end() ; p++)
        {
      element e;
      var_t t;
      string name;
      long obj_id;
      long param_id;
      
      // �ѥ�᡼����������
      for(q = (*p).second.begin() ; q != (*p).second.end() ; q++)
      {
        std::map< std::string, var_t > obj_parameter;
        std::map< std::string, var_t >::iterator s;
        obj_id = (*q)->get_id();
        name = (*p).first;
        std::map<std::string , long> id_count;
        std::map<std::string , long>::iterator id_iter;

        // �ͤμ��Ф�
        e.i = (*q)->get_id();
        e.s = (*q)->get_name();
        // �и���ꥹ���Ѥξ������
        order_list_map[ name ].push_back(e);
        // ���֥������ȼ��Ȥ�������
              mproc.set_var( toppers::toupper(name), obj_id, var_t( 1, e ) );
        
        // ���֥������ȥ��Ф�������
        for(r = (*q)->get_params()->begin() ; r != (*q)->get_params()->end() ; r++)
        {
          name = (*p).first+ string(".") + (*r)->get_parameter_name();
          e.s = (*r)->get_value();

          if(e.s == string(""))
          {
            continue;
          }

          // ���Ф�ID�򸡺�
          id_iter = id_count.find(name);
          if(id_iter == id_count.end())
          {
            id_count[name] = 0;
            param_id = 0;
          }
          else
          {
            param_id = (*id_iter).second + 1;
            id_count[name] = (*id_iter).second + 1;
          }

          if((*r)->get_type() == oil::TYPE_UINT)
          {
            string value_str(((*r)->get_value()));
            try
            {
              e.i = boost::lexical_cast<uint64_t>((*r)->get_value());
            }
            catch( std::exception& exception)
            {
              uint64_t temp;
              // 16�ʤξ�礬����Τ��Ѵ�
              /// ���줤����ʤ��ΤǤʤ�Ȥ�������
              if(value_str.find("0x") == 0)
              {
                                // modified by takuya 110823
                //sscanf_s(value_str.c_str() , "0x%I64x" , &temp);
                sscanf(value_str.c_str() , "0x%llx" , &temp);
                e.i = temp;
              }
              else if(value_str.find("0X") == 0)
              {
                                // modified by takuya 110823
                //sscanf_s(value_str.c_str() , "0X%I64x" , &temp);
                sscanf(value_str.c_str() , "0X%llx" , &temp);
                e.i = temp;
              }
              else
              {
                // ���㥹�Ȥ˼��Ԥ�����0�ˤ��Ƥ���
                e.i = 0;
              }

            }
          }
          else if((*r)->get_type() == oil::TYPE_INT)
          {
            string value_str(((*r)->get_value()));
            try
            {
              e.i = boost::lexical_cast<int64_t>(value_str);
            }
            catch(std::exception& exception)
            {
              int64_t temp;
              // 16�ʤξ�礬����Τ��Ѵ�
              /// ���줤����ʤ��ΤǤʤ�Ȥ�������
              if(value_str.find("0x") == 0)
              {
                                // modified by takuya 110823
                //sscanf_s(value_str.c_str() , "0x%I64x" , &temp);
                sscanf(value_str.c_str() , "0x%llx" , &temp);
                e.i = temp;
              }
              else if(value_str.find("0X") == 0)
              {
                                // modified by takuya 110823
                //sscanf_s(value_str.c_str() , "0X%I64x" , &temp);
                sscanf(value_str.c_str() , "0X%llx" , &temp);
                e.i = temp;
              }
              else
              {
                // ���㥹�Ȥ˼��Ԥ�����0�ˤ��Ƥ���
                e.i = 0;
              }
            }
          }
          else if((*r)->get_type() == oil::TYPE_REF)
          {
            object_definition *obj;
            string refefence_obj_type;

            // ���֥�������ID��õ��
            e.i = 0;
            obj = find_object((*r)->get_value() , obj_def_map);
            if(obj != NULL)
            {
              e.i = obj->get_id();
            }
          }
          else
          {
            e.i = 0;
          }
          obj_parameter[name].push_back(e);
        }

        for(s = obj_parameter.begin() ; s != obj_parameter.end() ; s++)
        {
          mproc.set_var((*s).first , obj_id , (*s).second );
        }
      }

    }
    // ����ꥹ�Ȥκ���
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
    }

      // �����ͥ륪�֥��������������������ŪAPI�γƥѥ�᡼����ޥ���ץ��å����ѿ��Ȥ������ꤹ�롣
      void set_object_vars( std::vector< object_definition* > const& obj_array, macro_processor& mproc )
      {
        typedef macro_processor::element element;
        typedef macro_processor::var_t var_t;
        long order = 1;
        var_t order_list;

        for ( std::vector< object_definition* >::const_iterator v_iter( obj_array.begin() ), v_last( obj_array.end() );
              v_iter != v_last;
              ++v_iter )
        {
          var_t params;
          var_t args;

#if 0
          // ��ŪAPI���и��������ֹ�
          element e;
          // e.s = v_iter->line().file;
          // e.i = v_iter->line().line;
          // mproc.set_var( "API.TEXT_LINE", order, var_t( 1, e ) );

          // ��ŪAPI̾
          e.s = v_iter->get_name();
          e.i = boost::none;
          mproc.set_var( "OBJ.NAME", order, var_t( 1, e ) );

          // ���֥������ȥ����ס�"TSK", "SEM", ...��
          e.s = toppers::toupper( v_iter->object_type );
          mproc.set_var( "OBJ.TYPE", order, var_t( 1 , e ) );

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
#endif
          ++order;
        }
        mproc.set_var( "API.ORDER_LIST", order_list );

        element external_id;
        external_id.i = get_global_bool( "external-id" );
        mproc.set_var( "USE_EXTERNAL_ID", var_t( 1, external_id ) );
      }

      // �ץ�åȥե����ࡦ����ѥ����¸���ͤ�ޥ���ץ��å����ѿ��Ȥ������ꤹ�롣
      void set_platform_vars( cfg1_out const& cfg1out, macro_processor& mproc )
      {
        typedef macro_processor::element element;
        typedef macro_processor::var_t var_t;

        cfg1_out::cfg1_def_table const* def_table = cfg1out.get_def_table();
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

    //! ���ݡ��Ȥ��Ƥ��륪�֥������Ⱦ���μ���
  std::vector<std::string> const* factory::get_object_definition_info() const
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
                  unsigned int i;
                  for(i = 0 ; i < d_iter->size() ; i++)
                  {
                      volatile int x = 1;
                      object_definition_table.push_back((*d_iter)[i].c_str());
                  }
              }

            }
          }
        }

        ~init_t()
        {

        
        }

    std::vector<std::string> object_definition_table;
      };
      static init_t init;
    std::vector<std::string> const* result = &init.object_definition_table;
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
          if ( !t.empty() )
          {
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
      };
      static init_t init;
      cfg1_out::cfg1_def_table const* result = &init.cfg1_def_table_;
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
     */
    std::auto_ptr< macro_processor > factory::do_create_macro_processor( cfg1_out const& cfg1out, cfg1_out::cfg_obj_map const& obj_def_map ) const
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
      set_object_vars( obj_def_map, *mproc );
      set_platform_vars( cfg1out, *mproc );
      e.s = cfg1out.get_includes();
      mproc->set_var( "INCLUDES", var_t( 1, e ) );

      // �ѥ�����
      e.s = boost::lexical_cast< std::string >( toppers::get_global< int >( "pass" ) );
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
    std::auto_ptr< macro_processor > factory::do_create_macro_processor( cfg1_out const& cfg1out, std::vector< object_definition* > const& obj_array ) const
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
      set_object_vars( obj_array, *mproc );
      set_platform_vars( cfg1out, *mproc );
      e.s = cfg1out.get_includes();
      mproc->set_var( "INCLUDES", var_t( 1, e ) );

      // �ѥ�����
      e.s = boost::lexical_cast< std::string >( toppers::get_global< int >( "pass" ));
      e.i = toppers::get_global< int >( "pass" );
      mproc->set_var( "CFG_PASS", var_t( 1, e ) );

      return mproc;
    }

    std::auto_ptr< cfg1_out > factory::do_create_cfg1_out( std::string const& filename ) const
    {
      return std::auto_ptr< oil::cfg1_out >( new cfg1_out( filename, get_cfg1_def_table() ) );
    }
    std::auto_ptr< checker > factory::do_create_checker() const
    {
      return std::auto_ptr< oil::checker >( new checker );
    }

  }
}

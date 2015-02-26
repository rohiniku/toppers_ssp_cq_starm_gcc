/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2010 by Meika Sugimoto
 *  Copyright (C) 2012 by TAKAGI Nonbuhisa
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

#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#include "toppers/global.hpp"
#include "toppers/oil/configuration_manager.hpp"

using namespace std;
using namespace toppers::oil;
using namespace toppers::oil::oil_implementation;
using namespace toppers::oil::oil_definition;

namespace toppers
{
  namespace configuration_manager
  {
    // APPMODE��õ���ե��󥯥�
    bool find_appmode_object(object_definition *p)
    {
      if(p->get_object_type() == "APPMODE")
      {
        return true;
      }
      return false;
    }

    bool config_manage::read_configuration
      (toppers::text *txt , std::vector<std::string> const& objlist)
    {
        description = txt;

        // ���ȥ�󥰤���
        description_str = new string();
        typedef text::container::const_iterator const_row_iterator;
        typedef std::string::size_type size_type;
        const_row_iterator first( txt->begin().get_row() ), last( txt->end().get_row() );

        for ( const_row_iterator iter( first ); iter != last; ++iter )
        {
          *description_str += iter->buf;
        }

        // �ѡ���������
        try
        {
          parser = new ::oil_parser(description_str , objlist);
        }
        catch( ... )
        {
          toppers::fatal("Memory allocation error.");
        }

      if(parser->do_parse(&oil_impl , &oil_def) == 0)
      {
        std::string kernel_type;
        // APPMODE���������Ƥ��ʤ�����OSDEFAULTAPPMODE������
        toppers::get_global( "kernel", kernel_type );
        if((kernel_type == "atk1")
          && (oil_def->end() == 
            (find_if(oil_def->begin() , oil_def->end() , find_appmode_object))))
        {
          oil_def->push_back(new object_definition("APPMODE OSDEFAULTAPPMODE"));
        }

        return true;
      }
      else
      {
        std::string message;
        int position;
        text::const_iterator iter;

        // ���顼���֤μ���
        parser->get_error(&position , &message);
        // �����Ԥμ���
        iter = description->line_at(position);
        text::line_type error_occur = iter.line();
        
        // ʸˡ���顼�Ϥ����˽�λ
        toppers::fatal(iter.line() , "%1%" , message);
        
        return false;
      }
    }

    bool object_matching(object_definition* obj , oil_object_impl* impl)
    {
      return impl->validate_object_configuration(obj , NULL);
    }

    bool config_manage::validate_and_assign_default_configuration(void)
    {
      bool result = true;
      std::vector<oil_definition::object_definition*>::iterator p;
      std::vector<oil_implementation::oil_object_impl*>::iterator q , found;
      
      // ���ƤΥ��֥��������������������礷�Ƥ��뤫�����å�����
      // �ǥե���ȥѥ�᡼�����䴰��Ԥ�
      for(p = oil_def->begin() ; p != oil_def->end() ; p++)
      {
        std::vector<toppers::oil::object_ref> object_refs;
        for(q = oil_impl->begin() ; q != oil_impl->end() ; q++)
        {
          if((*q)->validate_object_configuration(*p , &object_refs) == true)
          {
            break;
          }
        }
        
        if(q >= oil_impl->end())
        {
          // �ѥ�᡼���������������å�
          result = false;
          break;
        }
        
        // ��ե�����褬���������Υ����å�
        result = validate_object_reference((*p)->get_name() , &object_refs);
      }

      return result;
    }
    bool config_manage::validate_object_reference
        (std::string obj_name , std::vector<object_ref> *obj_refs)
    {
      std::vector<oil_definition::object_definition*>::iterator q;
      std::vector<object_ref>::iterator p;
      bool result = true;
      
      for(p = obj_refs->begin() ; p != obj_refs->end() ; p++)
      {
        std::vector<oil_definition::object_definition*> name_match;
        // ̾����Ʊ����Τ�õ��
        for(q = oil_def->begin() ; q != oil_def->end() ; q++)
        {
          if((*p).obj_name == (*q)->get_name())
          {
            name_match.push_back(*q);
          }
        }
        // ̾�������פ��ʤ���Ф��λ����ǥ��顼
        if(name_match.empty() == true)
        {
          toppers::error("Object %1%'s parameter %2% reference %3% , but not found." ,
                    obj_name , (*p).obj_type , (*p).obj_name);
          result = false;
          continue;
        }

        // ������Υ����פ�Ʊ����õ��
        for(q = name_match.begin() ; q != name_match.end() ; q++)
        {
          if((*p).obj_type == (*q)->get_object_type())
          {
            break;
          }
        }
        // �����פ�Ʊ����Τ��ʤ���Х��顼
        if(q == name_match.end())
        {
          toppers::error("Object %1%'s parameter %2% reference %3% , but referenced object is not %4%_TYPE" , 
                  obj_name , (*p).obj_type , (*p).obj_name , (*p).obj_type);
          result = false;
        }
      }

      return result;
    }

  } /* namespace oil */

} /* namespace toppers */


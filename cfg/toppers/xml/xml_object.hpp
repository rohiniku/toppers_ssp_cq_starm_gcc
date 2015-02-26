/* 
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *  
 *  Copyright (C) 2011-2014 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2014 by FUJISOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by Spansion LLC, USA
 *  Copyright (C) 2011-2013 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2014 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2014 by TOSHIBA CORPOTATION, JAPAN
 *  Copyright (C) 2011-2014 by Witz Corporation, JAPAN
 *  Copyright (C) 2012 by TAKAGI Nobuhisa
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
 *  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
 *  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
 *  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
 *  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  $Id: xml_object.hpp 179 2014-03-17 05:01:16Z nces-mtakada $
 */

#ifndef TOPPERS_XML_OBJECT_HPP_
#define TOPPERS_XML_OBJECT_HPP_

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax/Locator.hpp>

XERCES_CPP_NAMESPACE_USE
using namespace std;

typedef std::basic_string<XMLCh> XercesString;

inline XercesString fromNative(const char* str)
{
  boost::scoped_array<XMLCh> ptr(xercesc::XMLString::transcode(str));
  return XercesString(ptr.get());
}

inline XercesString fromNative(const std::string& str)
{
  return fromNative(str.c_str());
}

inline std::string toNative(const XMLCh* str)
{
  boost::scoped_array<char> ptr(xercesc::XMLString::transcode(str));
  return std::string(ptr.get());
}

inline std::string toNative(const XercesString& str)
{
  return toNative(str.c_str());
}

namespace toppers
{
  namespace xml
  {
    /*
     * \class
     * ARXML�ե�����˵��Ҥ��줿XML�ξ����������뤿��Υ��饹
     */
    namespace container
    {
      /* ���饹��������� */
      class object;
      class parameter;
    }

    namespace container
    {
      /* �ѥ�᡼�������� */
      enum PARAMETER_TYPE
      {
        TYPE_UNKNOWN = 0,
        TYPE_INT ,
        TYPE_FLOAT ,
        TYPE_STRING ,
        TYPE_BOOLEAN ,
        TYPE_ENUM , 
        TYPE_REF ,
        TYPE_FUNCTION,
        TYPE_INCLUDE,
      };

      /* ���֥�����������Υ��饹 */
      class object
      {
      public:
        static const int undefined = -1;  /*  ���֥������Ȥ�̤������  */
        object()
        {
          id = undefined;
          line = undefined;
          parent = NULL;
          siblings = undefined;
        }
        ~object()
        {
        }

        int getId() { return id; }
        int getLine() { return line; }
        std::string getFileName() { return file_name; }
        std::string getDefName()  { return define_name; }
        std::string getObjName() { return object_name; }
        std::vector<parameter*>* getParams() { return &params; }
        std::vector<object*>* getSubcontainers() { return &subcontainers; }
        object* getParent() { return parent; }
        int getSiblings() { return siblings; }

        void setId( int id_ )
        {
          id = id_;
        }
        void setLine( int line_ )
        {
          line = line_;
        }
        void setFileName( std::string str )
        {
          file_name = str;
        }
        void setDefName( std::string str )
        {
          define_name = str;
        }
        void setObjName( std::string str )
        {
          object_name = str;
        }
        void setParams( std::vector<parameter*> p )
        {
          params = p;
        }
        void setSubcontainers( std::vector<object*> p )
        {
          subcontainers = p;
        }
        void setParent( object* p )
        {
          parent = p;
        }
        void setSiblings( int siblings_ )
        {
          siblings = siblings_;
        }
      protected:
        int id;                 /* ����ƥʥ��֥������Ȥ�ID */
        string define_name;     /* ����ƥ�̾ */
        string object_name;     /* ����ƥʤμ���̾ */
        std::vector<parameter*> params;     /* ����ƥʥѥ�᡼���ؤΥݥ��� */
        std::vector<object*> subcontainers; /* ���֥���ƥʤؤΥݥ��� */
        object* parent;         /* �ƥ���ƥʤؤΥݥ��� */
        string file_name;       /* �ѡ����ե�����̾ */
        int line;               /* �ѡ������ֹ� */
        int siblings;           /* ���拾��ƥʤο� */
      };

      // ����ƥʥѥ�᡼���˴ؤ������
      class parameter
      {
      public:
        ~parameter() {}

        int getLine() { return line; }
        std::string getFileName() { return file_name; }
        std::string getDefName()  { return define_name; }
        object* getParent() { return parent; }
        string getValue() { return value; }
        PARAMETER_TYPE getType() { return type; }

        void setLine( int line_ )
        {
          line = line_;
        }
        void setFileName( std::string str )
        {
          file_name = str;
        }
        void setDefName( std::string str )
        {
          define_name = str;
        }
        void setParent( object* p )
        {
          parent = p;
        }
        void setType( PARAMETER_TYPE param_type )
        {
          type = param_type;
        }
        void setValue( string val_ )
        {
          value = val_;
        }

      protected:
        string define_name;   /* �ѥ�᡼��̾ */
        PARAMETER_TYPE type;  /* �� */
        string value;         /* �� */
        object* parent;       /* ����ƥʤؤΥݥ��� */
        string file_name;     /* �ѡ����ե�����̾ */
        int line;             /* �ѡ������ֹ� */
      };
    } /* container */

    struct info
    {
      char const* tfname;      /* tf�ǻ��Ѥ���Ȥ����֤�������̾�� */
      char const* type;        /* ������ */
      container::PARAMETER_TYPE type_enum;  /* ������(enum) */
      unsigned int multimin;   /* ¿���ٺǾ��� */
      unsigned int multimax;   /* ¿���ٺ����� */
    };
  } /* xml */
} /* toppers */

class SAX2Handlers : public DefaultHandler
{
public:

  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  SAX2Handlers();
  ~SAX2Handlers();

  toppers::xml::container::object *obj_temp;
  toppers::xml::container::parameter *para_temp;

  std::vector<toppers::xml::container::object*> object_array; 

  // -----------------------------------------------------------------------
  //  Handlers for the SAX ContentHandler interface
  // -----------------------------------------------------------------------
  void ignorableWhitespace(const XMLCh* const chars, const XMLSize_t length);
  void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
  void characters(const XMLCh* const chars, const XMLSize_t length);
  void endElement( const XMLCh* const uri, const XMLCh *const localname, const XMLCh *const qname);
  void setDocumentLocator (const Locator *const locator);
  int get_line();
  static void obj_delete(toppers::xml::container::object *pObj);

  // -----------------------------------------------------------------------
  //  Handlers for the SAX ErrorHandler interface
  // -----------------------------------------------------------------------
  void warning(const SAXParseException& exc);
  void error(const SAXParseException& exc);
  void fatalError(const SAXParseException& exc);
  void resetErrors();

  string filename;

private:
  int fEcuModuleConfigurationValues_;
  int fEcucContainerValue_;
  int fSubcontainers_;
  int fSubcontainers_old_;
  int fParameterValues_;
  int fReferenceValues_;
  XercesString currentText_;
  const Locator* locator_; 

  // PaserStrings
  XercesString ecucmodule;
  XercesString ecuccontainer;
  XercesString subcontainer;

  XercesString parameter;
  XercesString ecucnumerical;
  XercesString ecucreference;

  XercesString reference;
  XercesString ecuctextual;
  XercesString ecucboolean;     /* R3.1 only */
  XercesString ecucenum;        /* R3.1 only */
  XercesString ecucfloat;       /* R3.1 only */
  XercesString ecucfunction;    /* R3.1 only */

  XercesString definitionref;
  XercesString defqname;
  XercesString defBool;
  XercesString defEnum;
  XercesString defFloat;
  XercesString defFunction;
  XercesString defInteger;
  XercesString defReference;
  XercesString defString;

  XercesString shortname;
  XercesString value;
  XercesString valueref;

  // xml:space attribute is trim off(default(=TRUE)).
  bool fAttrXmlSpace_;
};

#endif /* TOPPERS_XML_OBJECT_HPP_ */

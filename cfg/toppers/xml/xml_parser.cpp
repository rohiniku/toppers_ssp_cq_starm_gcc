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
 *  $Id: xml_parser.cpp 179 2014-03-17 05:01:16Z nces-mtakada $
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax/SAXException.hpp>
#include "toppers/global.hpp"
#include "toppers/diagnostics.hpp"
#include "xml_object.hpp"

using namespace std;
using namespace toppers;
using namespace toppers::xml::container;

#define XML_DEBUG_P 0 /* xml debug print (0:silent 1:verbose) */

// ---------------------------------------------------------------------------
//  SAX2Handlers: Constructors and Destructor
// ---------------------------------------------------------------------------
SAX2Handlers::SAX2Handlers() :

fEcuModuleConfigurationValues_(0)
, fEcucContainerValue_(0)
, fParameterValues_(0)
, fReferenceValues_(0)
, fSubcontainers_(0)
, fSubcontainers_old_(0)
, fAttrXmlSpace_(true)
/*
, fEcucReferenceValue_(0)
, fEcucNumericalParamValue_(0)
, fEcucTextualParamValue_(0)
*/
{
  std::string version( get_global_string( "XML_AUTOSARVersion" ) );
  if ( version.at(0) == '3' )
  {
    ecucmodule    = fromNative("MODULE-CONFIGURATION");
    ecuccontainer = fromNative("CONTAINER");
    subcontainer  = fromNative("SUB-CONTAINERS");

    parameter     = fromNative("PARAMETER-VALUES");
    ecucboolean   = fromNative("BOOLEAN-VALUE");
    ecucenum      = fromNative("ENUMERATION-VALUE");
    ecucfloat     = fromNative("FLOAT-VALUE");
    ecucfunction  = fromNative("FUNCTION-NAME-VALUE");
    ecucnumerical = fromNative("INTEGER-VALUE");
    ecuctextual   = fromNative("STRING-VALUE");

    reference     = fromNative("REFERENCE-VALUES");
    ecucreference = fromNative("REFERENCE-VALUE");

    definitionref = fromNative("DEFINITION-REF");
    defqname      = fromNative("DEST");
    defBool       = fromNative("BOOLEAN-PARAM-DEF");
    defEnum       = fromNative("ENUMERATION-PARAM-DEF");
    defFloat      = fromNative("FLOAT-PARAM-DEF");
    defFunction   = fromNative("FUNCTION-NAME-DEF");
    defInteger    = fromNative("INTEGER-PARAM-DEF");
    defReference  = fromNative("REFERENCE-PARAM-DEF");
    defString     = fromNative("STRING-PARAM-DEF");

    shortname     = fromNative("SHORT-NAME");
    value         = fromNative("VALUE");
    valueref      = fromNative("VALUE-REF");
  }
  else if ( version.at(0) == '4' )
  {
    ecucmodule    = fromNative("ECUC-MODULE-CONFIGURATION-VALUES");
    ecuccontainer = fromNative("ECUC-CONTAINER-VALUE");
    subcontainer  = fromNative("SUB-CONTAINERS");

    parameter     = fromNative("PARAMETER-VALUES");
    ecuctextual   = fromNative("ECUC-TEXTUAL-PARAM-VALUE");
    ecucnumerical = fromNative("ECUC-NUMERICAL-PARAM-VALUE");

    reference     = fromNative("REFERENCE-VALUES");
    ecucreference = fromNative("ECUC-REFERENCE-VALUE");

    definitionref = fromNative("DEFINITION-REF");
    defqname      = fromNative("DEST");
    defBool       = fromNative("ECUC-BOOLEAN-PARAM-DEF");
    defEnum       = fromNative("ECUC-ENUMERATION-PARAM-DEF");
    defFloat      = fromNative("ECUC-FLOAT-PARAM-DEF");
    defFunction   = fromNative("ECUC-FUNCTION-NAME-DEF");
    defInteger    = fromNative("ECUC-INTEGER-PARAM-DEF");
    defReference  = fromNative("ECUC-REFERENCE-DEF");
    defString     = fromNative("ECUC-STRING-PARAM-DEF");

    shortname     = fromNative("SHORT-NAME");
    value         = fromNative("VALUE");
    valueref      = fromNative("VALUE-REF");
  }
  else
  {
    fatal( _( "Illegal \"AUTOSARVersion\" parameter(%s) in AUTOSAR ini-file." ), version );
  }
}

SAX2Handlers::~SAX2Handlers()
{
}

// ---------------------------------------------------------------------------
//  SAX2CountHandlers: Implementation of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void SAX2Handlers::startElement(const XMLCh* const uri
                   , const XMLCh* const localname
                   , const XMLCh* const qname
                   , const Attributes& attrs)
{
#if XML_DEBUG_P
  XERCES_STD_QUALIFIER cerr << "element : " << toNative(localname) << "(" << get_line() << ")" << XERCES_STD_QUALIFIER endl;
#endif
  int attlen = attrs.getLength();
  for(int i=0 ; i < attlen ; i++)
  {
    const XMLCh* qname = attrs.getQName(i);
    string name = toNative(attrs.getValue(qname));
#if XML_DEBUG_P
    XERCES_STD_QUALIFIER cerr << "        ATTR("<< i <<":"<< attlen <<") : name : " << toNative(qname) << "[" << name << "]" << XERCES_STD_QUALIFIER endl;
#endif
    if( toNative(qname) == "xml:space" && name == "preserve" )
    {
      fAttrXmlSpace_ = false;
    }
  }

  if(localname == ecucmodule) {
    fEcuModuleConfigurationValues_++;

    obj_temp = new toppers::xml::container::object();
    object_array.push_back(obj_temp);
    obj_temp->setParent( obj_temp );
    obj_temp->setLine( get_line() );
    obj_temp->setId( 1 );

  } else if(localname == ecuccontainer) {
    fEcucContainerValue_++;

    toppers::xml::container::object *old_obj = obj_temp;
    obj_temp = new toppers::xml::container::object();
    obj_temp->setLine( get_line() );

    if(fSubcontainers_ > fSubcontainers_old_) // old_obj�Υ��֥���ƥʤξ��
    {
      old_obj->getSubcontainers()->push_back(obj_temp);
      obj_temp->setParent( old_obj );
    }
    else
    {
      while(fSubcontainers_ < fSubcontainers_old_)
      {
        old_obj = old_obj->getParent();
        fSubcontainers_old_--;
      }
      old_obj->getParent()->getSubcontainers()->push_back(obj_temp);
      obj_temp->setParent( old_obj->getParent() );
    }

    fSubcontainers_old_ = fSubcontainers_;
  }

  // ����ƥ���Υ��������ѡ�������
  if(fEcuModuleConfigurationValues_ || fEcucContainerValue_)
  {
    
    if(localname == subcontainer)
    {
      fSubcontainers_++;
    }
    else if(localname == parameter)
    {
      fParameterValues_++;
    }
    else if(localname == reference)
    {
      fReferenceValues_++;
    }
    else if(localname == ecuctextual || localname == ecucnumerical || localname == ecucreference 
        || localname == ecucboolean || localname == ecucenum || localname == ecucfloat || localname == ecucfunction )
    {
      para_temp = new toppers::xml::container::parameter();
      para_temp->setLine( get_line() );
      para_temp->setFileName( filename );
      para_temp->setParent( obj_temp );
      obj_temp->getParams()->push_back(para_temp);

      if(localname == ecuctextual)
      {
        //fEcucTextualParamValue_++;
        para_temp->setType( TYPE_STRING );
      }
      else if(localname == ecucnumerical)
      {
        //fEcucNumericalParamValue_++;
        para_temp->setType( TYPE_INT );
      }
      else if (localname == ecucreference)
      {
        //fEcucReferenceValue_++;
        para_temp->setType( TYPE_REF );
      }
    }
    else if(localname == definitionref)
    {
      int attlen = attrs.getLength();
      for(int i=0 ; i < attlen ; i++)
      {
        const XMLCh* qname = attrs.getQName(i);
        const XMLCh* value = attrs.getValue(qname);
#if defined( _MSC_VER ) && _DEBUG && XML_DEBUG
        XERCES_STD_QUALIFIER cerr << "        ATTR : name : " << toNative(qname) << "[" << toNative(value) << "]" << XERCES_STD_QUALIFIER endl;
#endif
        if(defqname== qname && para_temp != NULL)
        {
          if(value == defInteger)
          {
            para_temp->setType( TYPE_INT );
          }
          else if(value == defFloat)
          {
            para_temp->setType( TYPE_FLOAT );
          }
          else if(value == defString)
          {
            para_temp->setType( TYPE_STRING );
          }
          else if(value == defBool)
          {
            para_temp->setType( TYPE_BOOLEAN );
          }
          else if(value == defEnum)
          {
            para_temp->setType( TYPE_ENUM );
          }
          else if(value == defReference)
          {
            para_temp->setType( TYPE_REF );
          }
          else if(value == defFunction)
          {
            para_temp->setType( TYPE_FUNCTION );
          }
        }
      }
    }
  }
}

void SAX2Handlers::characters(  const   XMLCh* const   chars
                   , const XMLSize_t length)
{
  string slen = boost::lexical_cast<string>(length);
#if XML_DEBUG_P
  XERCES_STD_QUALIFIER cerr << "contents : " << toNative(chars) << "(" << get_line() << ")" << XERCES_STD_QUALIFIER endl;
#endif

  if(fEcuModuleConfigurationValues_)
  {
    currentText_.append(chars, length);
  }
}

void SAX2Handlers::endElement( const XMLCh* const uri, const XMLCh *const localname, const XMLCh *const qname)
{

#if XML_DEBUG_P
  XERCES_STD_QUALIFIER cerr << "end element : " << toNative(localname) << XERCES_STD_QUALIFIER endl;
#endif
  // �ѡ�����Υ����ν���
  if(fEcuModuleConfigurationValues_ || fEcucContainerValue_)
  {
    std::string strAttr;
    // xml:space���Ǥϥǥե���Ȥǥ��ڡ�����������
    if(fAttrXmlSpace_ == true)
    {
#if XML_DEBUG_P
      XERCES_STD_QUALIFIER cerr << "attr(before) : [" << toNative(currentText_) << "]" <<XERCES_STD_QUALIFIER endl;
#endif
      strAttr = ( toNative(currentText_) );
      boost::trim(strAttr);
#if XML_DEBUG_P
      XERCES_STD_QUALIFIER cerr << "attr(after) : [" << strAttr << "]" <<XERCES_STD_QUALIFIER endl;
#endif
    }
    if(localname == shortname)
    {
      obj_temp->setObjName( strAttr );
      obj_temp->setFileName( filename );
    }
    else if(localname == definitionref)
    {
      if(fParameterValues_ || fReferenceValues_)
      {
        para_temp->setDefName( strAttr );
      }
      else
      {
        obj_temp->setDefName( strAttr );
      }
    }
    else if(localname == value || localname == valueref)
    {
      // VALUE���ͤ����ξ��ϥ��顼
      if ( strAttr.empty() == true )
      {
        currentText_.clear();
        fatal( _( "Empty string value in %1%. (%2%:%3%)" ), para_temp->getFileName(), para_temp->getDefName(), para_temp->getLine() );
      }
      else
      {
        para_temp->setValue( strAttr );
      }
    }


    else if(localname == ecucmodule)
    {
      fEcuModuleConfigurationValues_--;
    }
    else if(localname == ecuccontainer)
    {
      fEcucContainerValue_--;
    }
    else if(localname == subcontainer)
    {
      fSubcontainers_--;
    }
    else if (localname == parameter)
    {
      fParameterValues_--;
    }
    else if (localname == reference)
    {
      fReferenceValues_--;
    }
    /* �ʲ��ν����ϥե饰����Ӥ�Ȥ�ʤ��ΤǤ�����פ�ʤ��Ȼפ��� */
/*    else if (localname == ecuctextual)
    {
      fEcucTextualParamValue_--;
    }
    else if (localname == ecucnumerical)
    {
      fEcucNumericalParamValue_--;
    }
    else if (localname == ecucreference)
    {
      fEcucReferenceValue_--;
    }
*/
  }
  currentText_.clear();
  fAttrXmlSpace_ = true;
}

void SAX2Handlers::setDocumentLocator (const Locator *const locator)
{
  locator_ = locator;
}

int SAX2Handlers::get_line()
{
  return (int)locator_->getLineNumber();
}

// ���ǥ���ƥ�Ĥ�̵��Ǥ���������Խ���
void SAX2Handlers::ignorableWhitespace( const   XMLCh* const chars
                      , const XMLSize_t length)
{
}

/*
void SAX2Handlers::startDocument()
{
}

void SAX2Handlers::endDocument()
{
}
*/

// object_array�β��
void SAX2Handlers::obj_delete(toppers::xml::container::object *pObj)
{
  while( !pObj->getSubcontainers()->empty() )
  {
    obj_delete( pObj->getSubcontainers()->back() );
    delete pObj->getSubcontainers()->back();
    pObj->getSubcontainers()->pop_back();
  }
  
  for(std::vector<toppers::xml::container::parameter*>::iterator pPara = pObj->getParams()->begin() ;
    pPara != pObj->getParams()->end(); ++pPara)
  {
    delete *pPara;
  }
  pObj->getParams()->clear();
}

// ---------------------------------------------------------------------------
//  SAX2CountHandlers: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void SAX2Handlers::error(const SAXParseException& e)
{
   cerr << "\nError at file " << toNative(e.getSystemId())
    << ", line " << e.getLineNumber()
    << ", char " << e.getColumnNumber()
    << "\n  Message: " << toNative(e.getMessage()) << endl;

}

void SAX2Handlers::fatalError(const SAXParseException& e)
{
   cerr << "\nFatal Error at file " << toNative(e.getSystemId())
    << ", line " << e.getLineNumber()
    << ", char " << e.getColumnNumber()
    << "\n  Message: " << toNative(e.getMessage()) << endl;

}

void SAX2Handlers::warning(const SAXParseException& e)
{
  cerr << "\nWarning at file " << toNative(e.getSystemId())
    << ", line " << e.getLineNumber()
    << ", char " << e.getColumnNumber()
    << "\n  Message: " << toNative(e.getMessage()) << endl;
}

void SAX2Handlers::resetErrors()
{
}

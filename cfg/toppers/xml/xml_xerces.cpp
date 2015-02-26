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
 *  $Id: xml_xerces.cpp 179 2014-03-17 05:01:16Z nces-mtakada $
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#if defined(XERCES_NEW_IOSTREAMS)
#include <fstream>
#else
#include <fstream.h>
#endif
#include <xercesc/util/OutOfMemoryException.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "toppers/io.hpp"
#include "toppers/global.hpp"
#include "toppers/diagnostics.hpp"
#include "cfg1_out.hpp"
#include "xml_object.hpp"

#if defined( _MSC_VER ) && _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

using namespace toppers;

namespace toppers
{
  namespace xml
  {
    std::vector< toppers::xml::container::object* > cfg1_out::xml_parser_init( std::string input_file )
    {
      SAX2XMLReader::ValSchemes    valScheme    = SAX2XMLReader::Val_Auto;
      bool                         doNamespaces = true;
      bool                         doSchema = true;
      bool                         schemaFullChecking = false;
      bool                         identityConstraintChecking = true;
      bool                         namespacePrefixes = true;
      bool                         recognizeNEL = false;

      // Initialize the XML4C2 system
      try
      {
        XMLPlatformUtils::Initialize();
      }
      catch (const XMLException& toCatch)
      {
        std::vector<toppers::xml::container::object*> object_array;
        fatal( _("Error during initialization! Message:\n%" ), toNative(toCatch.getMessage()));
        return object_array;
      }

      //
      //  Create a SAX parser object. Then, according to what we were told on
      //  the command line, set it to validate or not.
      //
      SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
      parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, doNamespaces);
      parser->setFeature(XMLUni::fgXercesSchema, doSchema);
      parser->setFeature(XMLUni::fgXercesHandleMultipleImports, true);
      parser->setFeature(XMLUni::fgXercesSchemaFullChecking, schemaFullChecking);
      parser->setFeature(XMLUni::fgXercesIdentityConstraintChecking, identityConstraintChecking);
      parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, namespacePrefixes);

      if (valScheme == SAX2XMLReader::Val_Auto)
      {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(XMLUni::fgXercesDynamic, true);
      }
      if (valScheme == SAX2XMLReader::Val_Never)
      {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, false);
      }
      if (valScheme == SAX2XMLReader::Val_Always)
      {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(XMLUni::fgXercesDynamic, false);
      }

      /* External Schema file */
      // XML�ե�����Υ����å�
      namespace fs = boost::filesystem;

      if( !fs::exists( input_file ) )
      {
        fatal( _("'%1%` is not exist."), input_file );
      }
      /* ����ե����뤬������ϥѥ�᡼��̾�Υ����å���Ԥ� */
      std::string paraname( get_global_string( "ini-file" ) );
      std::string strAUTOSARVersion;
      std::string strSchema;
      std::string strSchemaLocation;
      std::string strContainerPath;
      std::string strModuleName;
      //std::cout << "AUTOSAR ini-file (ini file name):[" << paraname << "]" << std::endl;
      if( !paraname.empty() )
      {
        strAUTOSARVersion = get_global_string( "XML_AUTOSARVersion" );
        if( strAUTOSARVersion.empty() )
        {
          strAUTOSARVersion = "4";
          warning( _( " \"AUTOSARVersion\" parameter is not found in AUTOSAR ini-file. Use default value." ) );
        }
        strSchema = get_global_string( "XML_Schema" );
        if( strSchema.empty() )
        {
          strSchema = "AUTOSAR_4-0-3_STRICT.xsd";
          warning( _( " \"Schema\" parameter is not found in AUTOSAR ini-file. Use default value." ) );
        }
        strSchemaLocation = get_global_string( "XML_SchemaLocation" );
        if( strSchemaLocation.empty() )
        {
          strSchemaLocation = "http://autosar.org/schema/r4.0";
          warning( _( " \"SchemaLocation\" parameter is not found in AUTOSAR ini-file. Use default value." ) );
        }
        strContainerPath = get_global_string( "XML_ContainerPath" );
        if( strContainerPath.empty() )
        {
          strContainerPath = "/AUTOSAR/EcucDefs";
          warning( _( " \"ContainerPath\" parameter is not found in AUTOSAR ini-file. Use default value." ) );
        }
      }
      toppers::global( "XML_AUTOSARVersion" ) = strAUTOSARVersion;
      toppers::global( "XML_Schema" )         = strSchema;
      toppers::global( "XML_SchemaLocation" ) = strSchemaLocation;
      toppers::global( "XML_ContainerPath" )  = strContainerPath;

      // XML�ե���������xsi:schemaLocation°��������Ф������Ǥ����
      std::string sstr( "xsi:schemaLocation" );
      std::string buf;
      toppers::read( input_file, buf );

      std::list<std::string> results;
      string::size_type index( buf.find( sstr ) );
      if( index != string::npos )
      {
        string::size_type index2( buf.substr( index ).find( "\"" ) );
        string::size_type index3( buf.substr( index+index2+1 ).find( "\"" ) );
        sstr = buf.substr( index+index2+1, index3 );
        split( results, sstr, boost::is_space() );
      }

      // �������ޥե�����Υ����å�
      std::ostringstream ostream;
      if( results.size() == 2 && fs::exists( results.back() ) )
      {
        ostream << sstr;
      }
      else
      {
        ostream << get_global_string( "XML_SchemaLocation" ) << " " << fs::absolute( get_global_string( "cfg-directory" ).c_str() ).string() 
         << "/" << get_global_string( "XML_Schema" );
      }
      XMLCh* str (XMLString::transcode (ostream.str().c_str()));

      parser->setProperty(XMLUni::fgXercesSchemaExternalSchemaLocation, str);

      //
      //  Create our SAX handler object and install it on the parser, as the
      //  document and error handler.
      //
      SAX2Handlers handler;
      parser->setContentHandler(&handler);
      parser->setErrorHandler(&handler);

      //reset error count first
      handler.resetErrors();

      handler.filename = input_file;

      try
      {
        parser->parse(input_file.c_str());
      }
      catch (const OutOfMemoryException&)
      {
        warning("OutOfMemoryException");
      }
      catch (const XMLException& e)
      {
        warning( _("\nError during parsing: '%'\nException message is:  \n%\n"), input_file, toNative(e.getMessage()));
      }
      catch (...)
      {
        warning( _("\nUnexpected exception during parsing: '%'\n"), input_file);
      }

      delete parser;

      XMLPlatformUtils::Terminate();

      return handler.object_array;
    }
  }
}

#include <VtdCore/XMLConfigReader.h>
#include <VtdCore/Logging/Log.h>
#include <boost/cast.hpp>
#include <iostream>

namespace 
{
    const unsigned int NUM_INDENTS_PER_SPACE = 2;
    static const char* pINDENT="                                      + ";
    static const unsigned int LENGTH= boost::numeric_cast<unsigned int>( strlen(pINDENT) );
    static const char* pINDENTALT="                                        ";
    static const unsigned int LENGTHALT = boost::numeric_cast<unsigned int>( strlen(pINDENTALT) );
}

namespace VTD {
namespace Internal {

XMLConfigReader::XMLConfigReader() : verbose_(false)
{
    xmlConfig = boost::shared_ptr<TiXmlDocument>(new TiXmlDocument);
}

XMLConfigReader::XMLConfigReader(bool verbose)
    : verbose_(verbose)
{
    xmlConfig = boost::shared_ptr<TiXmlDocument>(new TiXmlDocument);
}

XMLConfigReader::~XMLConfigReader()
{
}

bool XMLConfigReader::readAttribute(const char* attribute, TiXmlElement* pElem, std::string& str)
{
    if (TIXML_NO_ATTRIBUTE == pElem->QueryStringAttribute(attribute, &str))
    {
        VTD_LOG("VtdCore: No XML attribute " << attribute);
        return false;
    }
    else if (TIXML_WRONG_TYPE == pElem->QueryStringAttribute(attribute, &str))
    {
        VTD_LOG("VtdCore: Wrong XML attribute %s \n " << attribute);
        return false;
    }

    return true;
}

bool XMLConfigReader::readAttribute(const char* attribute, TiXmlElement* pElem, float& variable)
{
    if (TIXML_NO_ATTRIBUTE == pElem->QueryFloatAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: No XML attribute " << attribute);
        return false;
    }
    else if (TIXML_WRONG_TYPE == pElem->QueryFloatAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: Wrong XML attribute %s \n " << attribute);
        return false;
    }

    return true;
}

bool XMLConfigReader::readAttribute(const char* attribute, TiXmlElement* pElem, unsigned int& variable)
{
    if (TIXML_NO_ATTRIBUTE == pElem->QueryUnsignedAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: No XML attribute " << attribute);
        return false;
    }
    else if (TIXML_WRONG_TYPE == pElem->QueryUnsignedAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: Wrong XML attribute " << attribute);
        return false;
    }

    return true;
}

bool XMLConfigReader::readAttribute(const char* attribute, TiXmlElement* pElem, int& variable)
{
    if (TIXML_NO_ATTRIBUTE == pElem->QueryIntAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: No XML attribute " << attribute);
        return false;
    }
    else if (TIXML_WRONG_TYPE == pElem->QueryIntAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: Wrong XML attribute " << attribute);
        return false;
    }

    return true;
}

bool XMLConfigReader::readAttribute(const char* attribute, TiXmlElement* pElem, double& variable)
{
    if (TIXML_NO_ATTRIBUTE == pElem->QueryDoubleAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: No XML attribute " << attribute);
        return false;
    }
    else if (TIXML_WRONG_TYPE == pElem->QueryDoubleAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: Wrong XML attribute " << attribute);
        return false;
    }

    return true;
}

bool XMLConfigReader::readAttribute(const char* attribute, TiXmlElement* pElem, bool& variable)
{
    if (TIXML_NO_ATTRIBUTE == pElem->QueryBoolAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: No XML attribute " << attribute);
        return false;
    }
    else if (TIXML_WRONG_TYPE == pElem->QueryBoolAttribute(attribute, &variable))
    {
        VTD_LOG("VtdCore: Wrong XML attribute " << attribute);
        return false;
    }

    return true;
}

const char* XMLConfigReader::getIndent(unsigned int numIndents)
{
    unsigned int n = numIndents * NUM_INDENTS_PER_SPACE;
    if (n > LENGTH)
        n = LENGTH;

    return &pINDENT[LENGTH-n];
}

// same as getIndent but no "+" at the end
const char* XMLConfigReader::getIndentAlt( unsigned int numIndents )
{
    unsigned int n = numIndents * NUM_INDENTS_PER_SPACE;
    if (n > LENGTHALT)
        n = LENGTHALT;

    return &pINDENTALT[LENGTHALT - n];
}

int XMLConfigReader::dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
    if ( !pElement )
        return 0;

    TiXmlAttribute* pAttrib=pElement->FirstAttribute();
    int i=0;
    int ival;
    double dval;
    const char* pIndent=getIndent(indent);
    printf("\n");
    while (pAttrib)
    {
        printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

        if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)
            printf( " int=%d", ival);

        if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS)
            printf( " d=%1.1f", dval);

        printf( "\n" );
        i++;
        pAttrib=pAttrib->Next();
    }

    return i;
}

void XMLConfigReader::dump_to_stdout (TiXmlNode* pParent, unsigned int indent)
{
    if (!pParent)
        return;

    TiXmlNode* pChild;
    TiXmlText* pText;
    int t = pParent->Type();
    printf( "%s", getIndent(indent));
    int num;

    switch (t)
    {
        case TiXmlNode::TINYXML_DOCUMENT:
            printf( "Document" );
            break;

        case TiXmlNode::TINYXML_ELEMENT:
            printf( "Element [%s]", pParent->Value() );
            num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
            switch(num)
            {
                case 0:  printf( " (No attributes)"); break;
                case 1:  printf( "%s1 attribute", getIndentAlt(indent)); break;
                default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
            }
            configFileElements_.push_back(pParent->Value());
            break;

        case TiXmlNode::TINYXML_COMMENT:
            printf( "Comment: [%s]", pParent->Value());
            break;

        case TiXmlNode::TINYXML_UNKNOWN:
            printf( "Unknown" );
            break;

        case TiXmlNode::TINYXML_TEXT:
            pText = pParent->ToText();
            printf( "Text: [%s]", pText->Value() );
            break;

        case TiXmlNode::TINYXML_DECLARATION:
            printf( "Declaration" );
            break;
        default:
            break;
    }

    printf( "\n" );
    for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
    {
        dump_to_stdout( pChild, indent+1 );
    }
}

bool XMLConfigReader::openXMLFile(const std::string& fileName)
{
    bool loadOkay = xmlConfig->LoadFile(fileName.c_str());

    if (!loadOkay)
    {
        printf( "Could not load config file %s. Error='%s'. Exiting.\n", fileName.c_str(), xmlConfig->ErrorDesc());
        return false;
    }

    return true;
}

void XMLConfigReader::printXMLFile()
{
    xmlConfig->Print(stdout);
}

bool XMLConfigReader::saveXMLFile(const std::string& fileName)
{
    bool saveOkay = xmlConfig->SaveFile(fileName.c_str());

    if (!saveOkay)
    {
        printf( "Could not load config file %s. Error='%s'. Exiting.\n", fileName.c_str(), xmlConfig->ErrorDesc());
        return false;
    }

    return true;
}

}

}

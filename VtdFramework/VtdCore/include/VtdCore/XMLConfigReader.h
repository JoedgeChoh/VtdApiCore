#ifndef  _XML_CONFIG_READER_H
#define  _XML_CONFIG_READER_H

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <tinyxml.h>

namespace VTD {
namespace Internal {

/**
 * @brief The XMLConfigReader class - read xml data
 */
class XMLConfigReader
{

public:

    /**
     * @brief XMLConfigReader - constructor
     */
	XMLConfigReader();

    /**
     * @brief XMLConfigReader - constructor
     * @param verbose - write data to log file
     */
    explicit XMLConfigReader(bool verbose);

    /**
      * @brief XMLConfigReader - destructor
      */
    virtual ~XMLConfigReader();

    /**
     * @brief openXMLFile
     * @param fileName
     * @return
     */
    bool openXMLFile(const std::string& fileName);

    /**
     * @brief printXMLFile
     * @return
     */
    void printXMLFile();

    /**
     * @brief getIndent
     * @param numIndents
     * @return
     */
    const char* getIndent(unsigned int numIndents);

    /**
     * @brief getIndentAlt
     * @param numIndents
     * @return
     * @details same as getIndent but no "+" at the end
     */
    const char* getIndentAlt(unsigned int numIndents);

    /**
     * @brief dump_attribs_to_stdout
     * @param pElement
     * @param indent
     * @return
     */
    int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent);

    /**
     * @brief dump_to_stdout
     * @param pParent
     * @param indent
     */
    void dump_to_stdout(TiXmlNode* pParent, unsigned int indent = 0 );

    /**
     * @brief hex2int
     * @param x
     * @param str
     */
    void hex2int(unsigned int& x, const char* str);

    /**
     * @brief saveXMLFile
     * @param fileName
     * @return
     */
    bool saveXMLFile(const std::string& fileName);

    /**
     * @brief readAttribute
     * @param attribute
     * @param pElem
     * @param variable
     * @return
     */
    static bool readAttribute(const char* attribute, TiXmlElement* pElem, float& variable);

    /**
     * @brief readAttribute
     * @param attribute
     * @param pElem
     * @param variable
     * @return
     */
    static bool readAttribute(const char* attribute, TiXmlElement* pElem, unsigned int& variable);

    /**
     * @brief readAttribute
     * @param attribute
     * @param pElem
     * @param variable
     * @return
     */
    static bool readAttribute(const char* attribute, TiXmlElement* pElem, int& variable);

    /**
     * @brief readAttribute
     * @param attribute
     * @param pElem
     * @param variable
     * @return
     */
    static bool readAttribute(const char* attribute, TiXmlElement* pElem, double& variable);

    /**
     * @brief readAttribute
     * @param attribute
     * @param pElem
     * @param variable
     * @return
     */
    static bool readAttribute(const char* attribute, TiXmlElement* pElem, bool& variable);

    /**
     * @brief readAttribute
     * @param attName
     * @param outPut
     * @param pElem
     * @return
     */
    static bool readAttribute(const char* attribute, TiXmlElement* pElem, std::string& str);

    /**
     * @brief getXmlDocument
     * @return
     */
    inline TiXmlDocument* getXmlDocument() {return xmlConfig.get();}

private:

    // xmlConfig
    boost::shared_ptr<TiXmlDocument> xmlConfig;
    // configFileElements_
    std::vector<std::string> configFileElements_;
    // m_name
    std::string m_name;
    // verbose - write data to log file or not
    bool verbose_;
};
}
}
#endif //_XML_CONFIG_READER_H


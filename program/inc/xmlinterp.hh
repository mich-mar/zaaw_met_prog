#ifndef XMLINTERP4ACTIONS_HH
#define XMLINTERP4ACTIONS_HH

#include <string>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include "Configuration.hh"

XERCES_CPP_NAMESPACE_USE

/**
 * @brief Główna funkcja uruchamiająca parser XML (nasz "silnik")
 */
bool ReadXML(const std::string& sFileName, Configuration& rConfig);

/*!
 * \brief Implementuje reakcje na napotkane elementu opisu akcji
 */
class XMLInterp4Config : public xercesc::DefaultHandler {
private:
  /**
   * @brief Referencja do obiektu konfiguracji, który wypełniamy.
   */
  Configuration& _Config;

public:
   /*!
    * \brief Inicjalizuje obiekt
    */
  XMLInterp4Config(Configuration &rConfig);
   /*!
    * \brief Wywoływana jest na początku dokumentu
    */
    virtual void startDocument() override;

   /*!
    * \brief Wywoływana jest na końcu dokumentu
    */
    virtual void endDocument() override;

   /*!
    * \brief Wywoływana jest po napotkaniu nowego elementu XML
    */
    virtual void startElement(
                    const XMLCh *const               pURI, 
                    const XMLCh *const               pLocalName, 
                    const XMLCh *const               pQNname,
                    const   xercesc::Attributes&     rAttrs
                  ) override;

   /*!
    * \brief Wywoływana jest po dojściu do końca elementu XML
    */
    virtual  void endElement(
                    const XMLCh *const pURI, 
                    const XMLCh *const pLocalName, 
                    const XMLCh *const pQNname
                   ) override;

   /*!
    * \brief Wywoływana jest gdy napotkany zostanie błąd fatalny
    */
    void fatalError(const xercesc::SAXParseException&);

   /*!
    * \brief Wywoływana jest gdy napotkany zostanie błąd
    */
    void error(const xercesc::SAXParseException &);

   /*!
    * \brief Wywoływana jest gdy parser sygnalizuje ostrzeżenie
    */
    void warning(const xercesc::SAXParseException &);

    /*!
     * \brief Wykonuje operacje związane z danym elementem XML
     */
    void WhenStartElement( const std::string&             rElemName,
               const xercesc::Attributes&     rAttrs
                         );

    /*!
     * \brief Analizuje atrybuty i  odpwiednio je interpretuje
     */
    void ProcessLibAttrs(const xercesc::Attributes&   rAttrs);

    /*!
     * \brief Analizuje atrybuty i odpwiednio je interpretuje
     */
    void ProcessCubeAttrs(const xercesc::Attributes&   rAttrs); 
};

#endif
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>     
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/XMLString.hpp>    
#include <xercesc/sax2/Attributes.hpp>    
#include "xmlinterp.hh"
#include <cassert>
#include <sstream>  
#include <cstdlib> 
#include <iostream>
#include <cstring>  
#include <stdexcept>
#include "Cuboid.hh"

// Użycie przestrzeni nazw Xerces jest dozwolone
XERCES_CPP_NAMESPACE_USE 

Vector3D ParseXMLVector(const char* sValue) {
    std::istringstream IStrm(sValue);
    Vector3D Vec;
    IStrm >> Vec[0] >> Vec[1] >> Vec[2];
    return Vec;
}

/**
 * @brief Główna funkcja uruchamiająca parser XML (silnik).
 *
 * Inicjalizuje parser Xerces-C, konfiguruje go, przypisuje handlery
 * (w tym 'XMLInterp4Config') i rozpoczyna parsowanie pliku.
 *
 * @param sFileName Nazwa pliku XML do wczytania.
 * @param rConfig Referencja do obiektu konfiguracji, który zostanie wypełniony.
 * @return true jeśli parsowanie zakończyło się sukcesem, false w przeciwnym razie.
 */
bool ReadXML(const std::string& sFileName, Configuration& rConfig) {
  try {
    XMLPlatformUtils::Initialize();
  } catch (const XMLException& e) {
    char* sMessage = XMLString::transcode(e.getMessage());
    std::cerr << "Błąd podczas inicjalizacji Xerces-C! :\n"
              << sMessage << std::endl;
    XMLString::release(&sMessage);
    return false;
  }

  SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();
  
  pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true); 

  // Utworzenie instancji handlera zdarzeń SAX
  XMLInterp4Config Handler(rConfig);
  pParser->setContentHandler(&Handler);
  pParser->setErrorHandler(&Handler);

  try {
    pParser->parse(sFileName.c_str());
  }
  catch (const XMLException& e) {
    char* sMessage = XMLString::transcode(e.getMessage());
    std::cerr << "!!! Wyjątek XML: " << sMessage << std::endl;
    XMLString::release(&sMessage);
    delete pParser;
    XMLPlatformUtils::Terminate();
    return false;
  }
  catch (const SAXParseException& e) {
    char* sMessage = XMLString::transcode(e.getMessage());
    std::cerr << "!!! Wyjątek parsowania SAX: " << sMessage << std::endl;
    XMLString::release(&sMessage);
    delete pParser;
    XMLPlatformUtils::Terminate();
    return false;
  }
  catch (const std::runtime_error& e) {
    std::cerr << "!!! Błąd wykonania: " << e.what() << std::endl;
    delete pParser;
    XMLPlatformUtils::Terminate();
    return false;
  }

  // Poprawne zwolnienie zasobów
  delete pParser;
  XMLPlatformUtils::Terminate();
  return true;
}

/**
 * @brief Konstruktor klasy.
 *
 * Inicjalizuje referencję do obiektu konfiguracji, który będzie
 * wypełniany podczas parsowania.
 *
 * @param rConfig Referencja do obiektu konfiguracji.
 */
XMLInterp4Config::XMLInterp4Config(Configuration &rConfig)
 : _Config(rConfig) // Inicjalizacja referencji do obiektu konfiguracji
{
}

/**
 * @brief Metoda wywoływana bezpośrednio przed rozpoczęciem
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::startDocument()
{
  std::cout << "--- Rozpoczęcie przetwarzania dokumentu XML." << std::endl;
}


/**
 * @brief Metoda wywoływana bezpośrednio po zakończeniu
 * przetwarzana dokumentu XML.
 */
void XMLInterp4Config::endDocument()
{
  std::cout << "--- Koniec przetwarzania dokumentu XML." << std::endl;
}

/**
 * @brief Analizuje atrybuty elementu XML "Lib".
 *
 * Oczekuje dokładnie jednego atrybutu "Name" i dodaje jego
 * wartość do obiektu konfiguracji.
 *
 * @param rAttrs Atrybuty przekazane przez parser dla elementu "Lib".
 */
void XMLInterp4Config::ProcessLibAttrs(const xercesc::Attributes  &rAttrs)
{
 if (rAttrs.getLength() != 1) {
      std::cerr << "Zła ilość atrybutów dla \"Lib\"" << std::endl;
      std::exit(1); // Użycie std::exit
 }

 char* sParamName = xercesc::XMLString::transcode(rAttrs.getQName(0));

 if (std::strcmp(sParamName,"Name")) { // Użycie std::strcmp
      std::cerr << "Zła nazwa atrybutu dla Lib" << std::endl;
      std::exit(1);
 }         

 XMLSize_t  Size = 0;
 char* sLibName = xercesc::XMLString::transcode(rAttrs.getValue(Size));

 std::cout << "  Nazwa biblioteki: " << sLibName << std::endl;

 // Dodanie odczytanej nazwy biblioteki do konfiguracji
 _Config.AddLibrary(sLibName);

 xercesc::XMLString::release(&sParamName);
 xercesc::XMLString::release(&sLibName);
}


/**
 * @brief Analizuje atrybuty elementu XML "Cube".
 *
 * Wczytuje atrybuty obiektu 'Cube', takie jak nazwa, skala i kolor.
 *
 * @param rAttrs Atrybuty przekazane przez parser dla elementu "Cube".
 */
void XMLInterp4Config::ProcessCubeAttrs(const xercesc::Attributes &rAttrs)
{
    if (rAttrs.getLength() < 1) {
        std::cerr << "Zła ilość atrybutów dla \"Cube\"" << std::endl;
        return; // lub exit
    }

    Cuboid *pObj = new Cuboid(); // Tworzymy nowy prostopadłościan

    // Pętla po wszystkich atrybutach elementu <Cube ...>
    for (XMLSize_t i = 0; i < rAttrs.getLength(); i++) {
        char* sAttrName = xercesc::XMLString::transcode(rAttrs.getQName(i));
        char* sAttrValue = xercesc::XMLString::transcode(rAttrs.getValue(i));
        
        std::string strName = sAttrName; // Konwersja na string dla łatwiejszego porównania

        if (strName == "Name") {
            pObj->SetName(sAttrValue);
        } 
        else if (strName == "Shift") {
            pObj->SetShift(ParseXMLVector(sAttrValue));
        } 
        else if (strName == "Scale") {
            pObj->SetScale(ParseXMLVector(sAttrValue));
        } 
        else if (strName == "RotXYZ_deg") {
            Vector3D Ang = ParseXMLVector(sAttrValue);
            pObj->SetAng_Roll_deg(Ang[0]);
            pObj->SetAng_Pitch_deg(Ang[1]);
            pObj->SetAng_Yaw_deg(Ang[2]);
        } 
        else if (strName == "Trans_m") {
            pObj->SetPosition_m(ParseXMLVector(sAttrValue));
        } 
        else if (strName == "RGB") {
            pObj->SetColor(ParseXMLVector(sAttrValue));
        }

        // Pamiętaj o zwolnieniu pamięci po transcode!
        xercesc::XMLString::release(&sAttrName);
        xercesc::XMLString::release(&sAttrValue);
    }

    // Dodajemy wypełniony obiekt do sceny znajdującej się w konfiguracji
    _Config.GetScene().AddMobileObj(pObj);
    
    std::cout << "  Dodano obiekt do sceny: " << pObj->GetName() << std::endl;
}

/**
 * @brief Wykonuje operacje związane z wystąpieniem danego elementu XML.
 *
 * Działa jak dyspozytor, kierując przetwarzanie do odpowiedniej
 * metody (np. `ProcessLibAttrs`) na podstawie nazwy elementu.
 *
 * @param rElemName Nazwa napotkanego elementu.
 * @param rAttrs Lista atrybutów tego elementu.
 */
void XMLInterp4Config::WhenStartElement( const std::string           &rElemName,
                             const xercesc::Attributes   &rAttrs
                                       )
{
  if (rElemName == "Lib") {
    ProcessLibAttrs(rAttrs);   return;   
  }

  if (rElemName == "Cube") {
    ProcessCubeAttrs(rAttrs);  return;
  }
}


/**
 * @brief Metoda wywoływana po napotkaniu nowego elementu XML.
 *
 * Handler zdarzeń SAX dla rozpoczęcia elementu.
 */
void XMLInterp4Config::startElement(  const   XMLCh* const            pURI,
                                      const   XMLCh* const            pLocalName,
                                      const   XMLCh* const            pQName,
              const   xercesc::Attributes&    rAttrs
                                    )
{
  char* sElemName = xercesc::XMLString::transcode(pLocalName);
  std::cout << "--- Początek elementu: "<< sElemName << std::endl;

  WhenStartElement(sElemName, rAttrs);

  xercesc::XMLString::release(&sElemName);
}


/**
 * @brief Metoda wywoływana w momencie zakończenia danego elementu XML.
 *
 * Handler zdarzeń SAX dla zakończenia elementu.
 */
void XMLInterp4Config::endElement(  const   XMLCh* const    pURI,
                                    const   XMLCh* const    pLocalName,
                                    const   XMLCh* const    pQName
                                 )
{
   char* sElemName = xercesc::XMLString::transcode(pLocalName);
   std::cout << "----- Koniec elementu: "<< sElemName << std::endl;
   xercesc::XMLString::release(&sElemName);
}


/**
 * @brief Metoda wywoływana, gdy napotkany zostanie błąd fatalny.
 *
 * Przerywa dalsze przetwarzanie.
 */
void XMLInterp4Config::fatalError(const xercesc::SAXParseException&  rException)
{
   char* sMessage = xercesc::XMLString::transcode(rException.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(rException.getSystemId());

   std::cerr << "Błąd fatalny! " << std::endl
        << "    Plik:  " << sSystemId << std::endl
        << "   Linia: " << rException.getLineNumber() << std::endl
        << " Kolumna: " << rException.getColumnNumber() << std::endl
        << " Informacja: " << sMessage 
        << std::endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}

/**
 * @brief Metoda wywoływana, gdy napotkany zostanie błąd (nie fatalny).
 */
void XMLInterp4Config::error(const xercesc::SAXParseException&  rException)
{
  // std::cerr << "Błąd parsowania..." << std::endl;
  // TODO: Dodać implementację obsługi błędów (np. logowanie).
}


/**
 * @brief Metoda wywoływana w przypadku ostrzeżeń.
 */
void XMLInterp4Config::warning(const xercesc::SAXParseException&  rException)  
{
  std::cerr << "Ostrzeżenie parsowania..." << std::endl;
  // TODO: Dodać implementację obsługi ostrzeżeń (np. logowanie).
}
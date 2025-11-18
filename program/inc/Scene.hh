#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include "AbstractScene.hh"
#include "AbstractMobileObj.hh"

/*!
 * \brief Klasa przechowująca kolekcję obiektów na scenie.
 * * Pozwala na dodawanie obiektów i wyszukiwanie ich po nazwie.
 * Implementuje interfejs AbstractScene.
 */
class Scene : public AbstractScene {
    /*!
     * \brief Mapa obiektów mobilnych.
     * Kluczem jest nazwa obiektu (std::string), wartością inteligentny wskaźnik.
     */
    std::map<std::string, std::shared_ptr<AbstractMobileObj>> _ObjMap;

public:
    Scene() {}
    
    /*!
     * \brief Wyszukuje obiekt o podanej nazwie.
     * \param sName - nazwa szukanego obiektu.
     * \return Wskaźnik do obiektu lub nullptr, jeśli nie znaleziono.
     */
    virtual AbstractMobileObj* FindMobileObj(const char *sName) override {
        auto it = _ObjMap.find(sName);
        if (it == _ObjMap.end()) {
            return nullptr;
        }
        return it->second.get();
    }

    /*!
     * \brief Dodaje nowy obiekt do sceny.
     * \param pMobObj - wskaźnik do dodawanego obiektu.
     */
    virtual void AddMobileObj(AbstractMobileObj *pMobObj) override {
        if (!pMobObj) return;
        
        // Tworzymy shared_ptr przejmując wskaźnik (zakładamy, że Scena zarządza pamięcią)
        std::shared_ptr<AbstractMobileObj> ptr(pMobObj);
        _ObjMap.insert({pMobObj->GetName(), ptr});
    }

    // ====================================================================
    // METODY DODATKOWE
    // ====================================================================

    /*!
     * \brief Zwraca mapę wszystkich obiektów (przydatne do iterowania przy wysyłaniu do serwera).
     */
    const std::map<std::string, std::shared_ptr<AbstractMobileObj>> & GetObjects() const {
        return _ObjMap;
    }
};

#endif
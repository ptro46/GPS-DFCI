//
//  DFCICacheManager.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 26/11/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef DFCICacheManager_hpp
#define DFCICacheManager_hpp

#include <stdio.h>
#include <string>
#include <map>
using namespace std;

#include "Carre100Km.hpp"
#include "Carre20Km.hpp"
#include "Carre2Km.hpp"

class DFCICacheManager {
private:
    map<string,Carre100Km*>     mapCache100Km;
    map<string,Carre20Km*>      mapCache20Km;
    map<string,Carre2Km*>       mapCache2Km;

    DFCICacheManager();
    
    static  DFCICacheManager    *       instance;

public:
    ~DFCICacheManager();
    
    static  DFCICacheManager*   getInstance();
    static  void                reset();
    
    void    addCarre100Km(string dfciName, Carre100Km* pCarre100Km);
    void    addCarre20Km(string dfciName, Carre20Km* pCarre20Km);
    void    addCarre2Km(string dfciName, Carre2Km* pCarre2Km);
    
    Carre100Km* carre100KmFromDFCI(string dfciName);
    Carre20Km*  carre20KmFromDFCI(string dfciName);
    Carre2Km*   carre2KmFromDFCI(string dfciName);
};

inline
void
DFCICacheManager::addCarre100Km(string dfciName, Carre100Km *pCarre100Km) {
    mapCache100Km[dfciName] = pCarre100Km ;
}

inline
void
DFCICacheManager::addCarre20Km(string dfciName, Carre20Km *pCarre20Km) {
    mapCache20Km[dfciName] = pCarre20Km ;
}

inline
void
DFCICacheManager::addCarre2Km(string dfciName, Carre2Km *pCarre2Km) {
    mapCache2Km[dfciName] = pCarre2Km ;
}

inline
Carre100Km*
DFCICacheManager::carre100KmFromDFCI(string dfciName) {
    return mapCache100Km[dfciName];
}

inline
Carre20Km*
DFCICacheManager::carre20KmFromDFCI(string dfciName) {
    return mapCache20Km[dfciName];
}

inline
Carre2Km*
DFCICacheManager::carre2KmFromDFCI(string dfciName) {
    return mapCache2Km[dfciName];
}

#endif /* DFCICacheManager_hpp */

//
//  DFCICacheManager.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 26/11/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "DFCICacheManager.hpp"

DFCICacheManager* DFCICacheManager::instance  =   nullptr ;

DFCICacheManager::DFCICacheManager() {
    
}

DFCICacheManager::~DFCICacheManager() {
    
}

DFCICacheManager*
DFCICacheManager::getInstance() {
    if ( instance == nullptr ) {
        instance = new DFCICacheManager();
    }
    return instance;
}

void
DFCICacheManager::reset() {
    if ( instance != nullptr ) {
        delete instance;
        instance = nullptr ;
    }
}
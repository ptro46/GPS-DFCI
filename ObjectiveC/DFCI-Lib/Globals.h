//
//  Globals.h
//  DFCI-Lib-ObjC
//
//  Created by Patrice Trognon on 18/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef Globals_h
#define Globals_h


#define CustomLog(FORMAT, ...) fprintf(stderr,"%s", [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);

#endif /* Globals_h */

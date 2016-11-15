//
//  support.hpp
//  project3
//
//  Created by Ning Wang on 5/18/16.
//  Copyright © 2016 Ning Wang. All rights reserved.
//

#ifndef support_h
#define support_h

#include "provided.h"


bool winHorizontally(Scaffold &s, int N, int &color);
bool winVertically(Scaffold &s, int N, int &color);
bool winDiagonally(Scaffold &s, int N, int &color);
bool win(Scaffold &ss, int g, int &wcolor);

#endif /* support_h */

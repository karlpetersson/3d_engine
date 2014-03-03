//
//  OFFParser.h
//  Excercise 1
//
//  Created by Karl Petersson on 2014-01-21.
//  Copyright (c) 2014 Karl Petersson. All rights reserved.
//

#ifndef __Excercise_1__OFFParser__
#define __Excercise_1__OFFParser__

#include <iostream>
#include <map>
#include "Mesh.h"
#include "VertexBuffer.h"

namespace OFFParser {
    Mesh parse(std::string filename);
}

#endif /* defined(__Excercise_1__OFFParser__) */

//
//  main.cpp
//  UnderwaterTest
//
//  Created by Patryk Cieslak on 02/03/2014.
//  Copyright (c) 2014 Patryk Cieslak. All rights reserved.
//

#include "UnderwaterTestApp.h"
#include "UnderwaterTestManager.h"

int main(int argc, const char * argv[])
{
    UnderwaterTestManager* simulationManager = new UnderwaterTestManager(100.0);
    UnderwaterTestApp app(1000, 700, simulationManager);
    app.Init("Data", "Shaders");
    app.EventLoop();
    app.CleanUp();
    
    return 0;
}

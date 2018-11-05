//
//  UnderwaterTestApp.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 03/03/2014.
//  Copyright (c) 2014-2017 Patryk Cieslak. All rights reserved.
//

#include "UnderwaterTestApp.h"

#include <graphics/OpenGLTrackball.h>
#include <entities/systems/Manipulator.h>
#include <entities/systems/UnderwaterVehicle.h>
#include <entities/forcefields/Ocean.h>
#include <sensors/FakeRotaryEncoder.h>
#include <sensors/Accelerometer.h>
#include <sensors/ForceTorque.h>
#include <entities/forcefields/Trigger.h>

UnderwaterTestApp::UnderwaterTestApp(std::string dataDirPath, int width, int height, UnderwaterTestManager* sim) 
    : GraphicalSimulationApp("Underwater Test", dataDirPath, width, height, sim)
{
    decimalTime = 12.0;
}

void UnderwaterTestApp::DoHUD()
{
    GraphicalSimulationApp::DoHUD();
    
    ui_id slider;
    slider.owner = 0;
    slider.item = 0;
    slider.index = 0;
    getSimulationManager()->setStepsPerSecond(IMGUI::getInstance()->DoSlider(slider, 5.f, 5.f, 120.f, 100.0, 2000.0, getSimulationManager()->getStepsPerSecond(), "Steps/s"));
    
#ifdef USE_IAUV_CLASSES
    Manipulator* manip = (Manipulator*)getSimulationManager()->getEntity("Arm");
    slider.item = 1;
    manip->SetDesiredJointPosition(0 , IMGUI::getInstance()->DoSlider(slider, 5.f, 100.f, 200.f, -1.0, 1.0, manip->getDesiredJointPosition(0), "Joint1"));
    
    slider.item = 2;
    manip->SetDesiredJointPosition(1 , IMGUI::getInstance()->DoSlider(slider, 5.f, 155.f, 200.f, -1.0, 1.0, manip->getDesiredJointPosition(1), "Joint2"));
    
    slider.item = 3;
    manip->SetDesiredJointPosition(2, IMGUI::getInstance()->DoSlider(slider, 5.f, 210.f, 200.f, -1.0, 1.0, manip->getDesiredJointPosition(2), "Joint3"));
    
    slider.item = 4;
    manip->SetDesiredJointPosition(3, IMGUI::getInstance()->DoSlider(slider, 5.f, 265.f, 200.f, -1.0, 1.0, manip->getDesiredJointPosition(3), "Joint4"));
    
    UnderwaterVehicle* vehicle = (UnderwaterVehicle*)getSimulationManager()->getEntity("AUV");
    slider.item = 5;
    vehicle->SetThrusterSetpoint(0, IMGUI::getInstance()->DoSlider(slider, 5.f, 350.f, 200.f, -1.0, 1.0, vehicle->GetThrusterSetpoint(0), "Sway"));
    
    slider.item = 6;
    vehicle->SetThrusterSetpoint(1, IMGUI::getInstance()->DoSlider(slider, 5.f, 405.f, 200.f, -1.0, 1.0, vehicle->GetThrusterSetpoint(1), "Surge port"));
    
    slider.item = 7;    
    vehicle->SetThrusterSetpoint(2, IMGUI::getInstance()->DoSlider(slider, 5.f, 460.f, 200.f, -1.0, 1.0, vehicle->GetThrusterSetpoint(2), "Surge starboard"));
    
    slider.item = 8;
    vehicle->SetThrusterSetpoint(3, IMGUI::getInstance()->DoSlider(slider, 5.f, 515.f, 200.f, -1.0, 1.0, vehicle->GetThrusterSetpoint(3), "Heave stern"));
    
    slider.item = 9;
    vehicle->SetThrusterSetpoint(4, IMGUI::getInstance()->DoSlider(slider, 5.f, 570.f, 200.f, -1.0, 1.0, vehicle->GetThrusterSetpoint(4), "Heave bow"));
#else
    slider.item = 5;
    Thruster* thSway = (Thruster*)getSimulationManager()->getActuator("ThrusterSway");
    thSway->setSetpoint(IMGUI::getInstance()->DoSlider(slider, 5.f, 350.f, 200.f, -1.0, 1.0, thSway->getSetpoint(), "Sway"));
    
    slider.item = 6;
    Thruster* thSurgeP = (Thruster*)getSimulationManager()->getActuator("ThrusterSurgePort");
    thSurgeP->setSetpoint(IMGUI::getInstance()->DoSlider(slider, 5.f, 405.f, 200.f, -1.0, 1.0, thSurgeP->getSetpoint(), "Surge port"));
    
    slider.item = 7;
    Thruster* thSurgeS = (Thruster*)getSimulationManager()->getActuator("ThrusterSurgeStarboard");
    thSurgeS->setSetpoint(IMGUI::getInstance()->DoSlider(slider, 5.f, 460.f, 200.f, -1.0, 1.0, thSurgeS->getSetpoint(), "Surge starboard"));
    
    slider.item = 8;
    Thruster* thHeaveS = (Thruster*)getSimulationManager()->getActuator("ThrusterHeaveStern");
    thHeaveS->setSetpoint(IMGUI::getInstance()->DoSlider(slider, 5.f, 515.f, 200.f, -1.0, 1.0, thHeaveS->getSetpoint(), "Heave stern"));
    
    slider.item = 9;
    Thruster* thHeaveB = (Thruster*)getSimulationManager()->getActuator("ThrusterHeaveBow");
    thHeaveB->setSetpoint(IMGUI::getInstance()->DoSlider(slider, 5.f, 570.f, 200.f, -1.0, 1.0, thHeaveB->getSetpoint(), "Heave bow"));
    
    
    ForceTorque* ft = (ForceTorque*)getSimulationManager()->getSensor("FT");
    std::cout << "Force/torque" << ft->getLastSample().data[0] << ", " << ft->getLastSample().data[1] << ", " << ft->getLastSample().data[2] << ", "
                                << ft->getLastSample().data[3] << ", " << ft->getLastSample().data[4] << ", " << ft->getLastSample().data[5] << std::endl;
    
#endif
    
    Ocean* ocean = getSimulationManager()->getOcean();
    
    slider.item = 10;
    ocean->setAlgeaBloomFactor(IMGUI::getInstance()->DoSlider(slider, 5.f, 625.f, 200.f, 0.0, 1.0, ocean->getAlgeaBloomFactor(), "Algea bloom"));
    
    slider.item = 11;
    ocean->setTurbidity(IMGUI::getInstance()->DoSlider(slider, 5.f, 680.f, 200.f, 0.0, 1000.0, ocean->getTurbidity(), "Turbidity"));
    
    slider.item = 13;
    double newTime = IMGUI::getInstance()->DoSlider(slider, 5.f, 735.f, 200.f, 0.0, 24.0, decimalTime, "Time");
	if(newTime != decimalTime)
	{
		decimalTime = newTime;
		std::time_t rawTime;
		std::time(&rawTime);
		std::tm* hUtc;
		hUtc = std::gmtime(&rawTime);
		hUtc->tm_hour = trunc(decimalTime);
		hUtc->tm_min = ((int)trunc(decimalTime*60.0)) % 60;
		hUtc->tm_sec = 0;
    	OpenGLAtmosphere::getInstance()->SetSunPosition(3, 40.0, *hUtc);
	}
    
#ifdef USE_IAUV_CLASS
    //FakeRotaryEncoder* enc = (FakeRotaryEncoder*)getSimulationManager()->getSensor("Encoder");
    Accelerometer* acc = (Accelerometer*)getSimulationManager()->getSensor("Acc");
    
    slider.item = 12;
    std::vector<unsigned short> dims;
    dims.push_back(2);
    IMGUI::getInstance()->DoTimePlot(slider, getWindowWidth()-310, 10, 300, 200, acc, dims, "Test", new btScalar[2]{-20.f,20.f});
#endif
    /*
    ui_id plot;
    plot.owner = 1;
    plot.item = 0;
    plot.index = 0;
    getHUD()->DoTimePlot(plot, getWindowWidth()-310, 10, 300, 200, getSimulationManager()->getSensor(0), "Acceleration");
    */
	//Trigger* trig = (Trigger*)getSimulationManager()->getEntity("BoxTrigger");
	//std::cout << "Trigger: " << (int)trig->isActive() << std::endl;
}

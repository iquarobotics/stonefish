//
//  IMU.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 06/05/2014.
//  Copyright (c) 2014-2017 Patryk Cieslak. All rights reserved.
//

#include "sensors/IMU.h"

IMU::IMU(std::string uniqueName, SolidEntity* attachment, const btTransform& geomToSensor, btScalar frequency, int historyLength) : SimpleSensor(uniqueName, geomToSensor, frequency, historyLength)
{
    attach = attachment;
    channels.push_back(SensorChannel("Roll", QUANTITY_ANGLE));
    channels.push_back(SensorChannel("Pitch", QUANTITY_ANGLE));
    channels.push_back(SensorChannel("Yaw", QUANTITY_ANGLE));
    channels.push_back(SensorChannel("Angular velocity X", QUANTITY_ANGULAR_VELOCITY));
    channels.push_back(SensorChannel("Angular velocity Y", QUANTITY_ANGULAR_VELOCITY));
    channels.push_back(SensorChannel("Angular velocity Z", QUANTITY_ANGULAR_VELOCITY));
}

void IMU::InternalUpdate(btScalar dt)
{
    //Calculate transformation from global to imu frame
    btTransform imuTrans = attach->getTransform() * attach->getGeomToCOGTransform().inverse() * g2s;
    
    //Get angular velocity
    btVector3 av = imuTrans.getBasis().inverse() * attach->getAngularVelocity();
    
    //Get angles
    btScalar yaw, pitch, roll;
    imuTrans.getBasis().getEulerYPR(yaw, pitch, roll);
    
    //Save sample
    btScalar values[6] = {roll, pitch, yaw, av.x(), av.y(), av.z()};
    Sample s(6, values);
    AddSampleToHistory(s);
}

void IMU::SetRange(btScalar angularVelocityMax)
{
    channels[3].rangeMin = -angularVelocityMax;
    channels[4].rangeMin = -angularVelocityMax;
    channels[5].rangeMin = -angularVelocityMax;
    channels[3].rangeMax = angularVelocityMax;
    channels[4].rangeMax = angularVelocityMax;
    channels[5].rangeMax = angularVelocityMax;
}
    
void IMU::SetNoise(btScalar angleStdDev, btScalar angularVelocityStdDev)
{
    channels[0].setStdDev(angleStdDev);
    channels[1].setStdDev(angleStdDev);
    channels[2].setStdDev(angleStdDev);
    channels[3].setStdDev(angularVelocityStdDev);
    channels[4].setStdDev(angularVelocityStdDev);
    channels[5].setStdDev(angularVelocityStdDev);
}

btTransform IMU::getSensorFrame()
{
    return attach->getTransform() * attach->getGeomToCOGTransform().inverse() * g2s;
}
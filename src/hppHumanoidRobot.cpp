/*
 *  Copyright (c) 2007 LAAS-CNRS
 *
 *  Author: Florent Lamiraux
 */

#include "hppModel/hppHumanoidRobot.h"

// ==========================================================================

ChppHumanoidRobot::ChppHumanoidRobot
(CjrlRobotDynamicsObjectFactory *inObjFactory) :
  CimplDynamicRobot(), CimplHumanoidDynamicRobot(inObjFactory),
  ChppDevice()
{
  std::cout << "Constructor ChppHumanoidRobot with OF" << std::endl;
}

// ==========================================================================

ChppHumanoidRobotShPtr ChppHumanoidRobot::create(std::string inName)
{
  CimplObjectFactory* objFactory = new CimplObjectFactory();
  ChppHumanoidRobot *hppDevice = new ChppHumanoidRobot(objFactory);
  ChppHumanoidRobotShPtr hppDeviceShPtr(hppDevice);

  if (hppDevice->init(hppDeviceShPtr, inName) != KD_OK) {
    hppDeviceShPtr.reset();
  }
  return hppDeviceShPtr;
}

// ==========================================================================

ChppHumanoidRobotShPtr
ChppHumanoidRobot::createCopy(const ChppHumanoidRobotShPtr& inDevice)
{
  ChppHumanoidRobot* ptr = new ChppHumanoidRobot(*inDevice);
  ChppHumanoidRobotShPtr deviceShPtr(ptr);

  if(KD_OK != ptr->init(deviceShPtr, inDevice))	{
    deviceShPtr.reset();
  }

  return deviceShPtr;
}

// ==========================================================================

CkwsDeviceShPtr ChppHumanoidRobot::clone() const
{
  return ChppHumanoidRobot::createCopy(attWeakPtr.lock());
}

// ==========================================================================

CkppComponentShPtr ChppHumanoidRobot::cloneComponent() const
{
  return ChppHumanoidRobot::createCopy(attWeakPtr.lock());
}

// ==========================================================================

bool ChppHumanoidRobot::isComponentClonable() const
{
  return true;
}

// ==========================================================================

ChppJoint* ChppHumanoidRobot::hppWaist()
{
  return jrlToHppJoint(waist());
}

// ==========================================================================

ChppJoint* ChppHumanoidRobot::hppLeftWrist()
{
  return jrlToHppJoint(leftWrist());
}

// ==========================================================================

ChppJoint* ChppHumanoidRobot::hppRightWrist()
{
  return jrlToHppJoint(rightWrist());
}

// ==========================================================================

ChppJoint* ChppHumanoidRobot::hppLeftFoot()
{
  return jrlToHppJoint(leftAnkle());
}

// ==========================================================================

ChppJoint* ChppHumanoidRobot::hppRightFoot()
{
  return jrlToHppJoint(rightAnkle());
}

// ==========================================================================

ChppJoint* ChppHumanoidRobot::hppGazeJoint()
{
  return jrlToHppJoint(gazeJoint());
}

// ==========================================================================

ktStatus ChppHumanoidRobot::init(const ChppHumanoidRobotWkPtr& inDevWkPtr,
				 const std::string &inName)
{
  ktStatus success = ChppDevice::init(inDevWkPtr, inName);

  if(KD_OK == success) {
    attWeakPtr = inDevWkPtr;
  }
  return success;
}

// ==========================================================================

ktStatus ChppHumanoidRobot::init(const ChppHumanoidRobotWkPtr& inWeakPtr,
				 const ChppHumanoidRobotShPtr& inDevice)
{
  ktStatus  success = ChppDevice::init(inWeakPtr, inDevice);

  if(KD_OK == success) {
    attWeakPtr = inWeakPtr;
  }

  return success;
}

/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>
#include <frc/WPILib.h>

#define CAMERA_RES_W  320
#define CAMERA_RES_H  240
#define CAMERA_FPS    15

void Robot::RobotInit()
{
  // initialize camera
  cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
  camera.SetResolution(CAMERA_RES_W, CAMERA_RES_H);
  camera.SetFPS(CAMERA_FPS);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif

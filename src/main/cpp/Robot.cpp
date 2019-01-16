/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

void Robot::RobotInit()
{
    // initialize camera
    camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(CAMERA_RES_W, CAMERA_RES_H);
    camera.SetFPS(CAMERA_FPS);
    // inititalize intake motor
    m_intakeMotor.EnableDeadbandElimination(true);
}

void Robot::RobotPeriodic()
{
    ArcadeDrive();
    IntakeSuccAndPuke();
}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}

void Robot::ArcadeDrive()
{
    m_robotDrive.ArcadeDrive(-m_stick.GetY(), m_stick.GetX());
}

void Robot::IntakeSuccAndPuke()
{
    if (m_stick.GetRawButton(INTAKE_SUCC_BUTTON))
    {
        m_intakeMotor.SetSpeed(-INTAKE_SPEED);
    }
    else if (m_stick.GetRawButton(INTAKE_PUKE_BUTTON))
    {
        m_intakeMotor.SetSpeed(INTAKE_SPEED);
    }
    else
    {
        m_intakeMotor.SetSpeed(0.0);
    }
}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif

/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

void Robot::RobotInit()
{
    // camera settings
    camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(CAMERA_RES_W, CAMERA_RES_H);
    camera.SetFPS(CAMERA_FPS);
    // intake motor settings
    m_intakeMotor.EnableDeadbandElimination(true);
}

void Robot::RobotPeriodic()
{
    // drive with joystick
    ArcadeDrive();
    // control intake
    ControlIntake();
}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}

void Robot::ArcadeDrive()
{
    // acrade drive
    m_robotDrive.ArcadeDrive(-m_stick.GetY() * DRIVE_Y_SPEED, m_stick.GetX() * DRIVE_X_SPEED);
}

void Robot::ControlIntake()
{
    // succ
    if (m_stick.GetRawButton(INTAKE_SUCC_BUTTON)) {
        m_intakeMotor.SetSpeed(-INTAKE_SPEED);
    }
    // puke
    else if (m_stick.GetRawButton(INTAKE_PUKE_BUTTON)) {
        m_intakeMotor.SetSpeed(INTAKE_SPEED);
    }
    // stop (intake motor)
    else {
        m_intakeMotor.SetSpeed(0.0);
    }
}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif

/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/WPILib.h>
#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/spark.h>
#include <frc/drive/DifferentialDrive.h>

class Robot : public frc::TimedRobot
{
  public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;

  private:
    // pin constants
    const int LEFT_MOTOR_PIN = 0;
    const int RIGHT_MOTOR_PIN = 1;
    const int INTAKE_MOTOR_PIN = 2;

    // camera constants
    const int CAMERA_RES_W = 320;
    const int CAMERA_RES_H = 240;
    const int CAMERA_FPS = 15;

    // buttons constants
    const int INTAKE_SUCC_BUTTON = 7;
    const int INTAKE_PUKE_BUTTON = 8;

    // speed constants
    const float INTAKE_SPEED = 1.0;

    cs::UsbCamera camera;

    frc::PWMVictorSPX m_leftMotor{LEFT_MOTOR_PIN};
    frc::PWMVictorSPX m_rightMotor{RIGHT_MOTOR_PIN};
    frc::DifferentialDrive m_robotDrive{m_leftMotor, m_rightMotor};

    frc::Joystick m_stick{0};

    frc::Spark m_intakeMotor{INTAKE_MOTOR_PIN};

    void ArcadeDrive();
    void IntakeSuccAndPuke();
};

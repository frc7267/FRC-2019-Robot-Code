/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <ctre/Phoenix.h>
#include <frc/WPILib.h>
#include <iostream>
#include <string>

class Robot : public frc::TimedRobot {

public:
    // default functions
    void RobotInit() override;
    void RobotPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;

private:
    // RIO pin constants
    const int LEFT_MOTOR_PIN = 2;
    const int RIGHT_MOTOR_PIN = 1;
    const int INTAKE_MOTOR_PIN = 0;
    // PCM pin constants
    const int INTAKE_SOLONOID_PIN_1 = 0;
    const int INTAKE_SOLONOID_PIN_2 = 1;
    const int HATCH_SOLONOID_PIN_1 = 2;
    const int HATCH_SOLONOID_PIN_2 = 3;
    // camera constants
    const int CAMERA_RES_W = 320;
    const int CAMERA_RES_H = 240;
    const int CAMERA_FPS = 15;
    // buttons constants
    const int COMPRESSOR_ON_BUTTON = 11;
    const int COMPRESSOR_OFF_BUTTON = 12;
    const int ARM_UP_BUTTON = 4;
    const int ARM_DOWN_BUTTON = 1;
    // speed constants
    const float INTAKE_SPEED = 1.0; // succ is negative, puke is positive
    const float ARM_SPEED = 1.0;
    const float DRIVE_X_SPEED = 1.0;
    const float DRIVE_Y_SPEED = -1.0; // y axis is inverted

    //encoder angle constants
    const int ARM_COUNTS_PER_DEGREE = 71 * 7 / 360;
    const int ARM_MAX_ANGLE = 400;
    int ARM_TARGET_ANGLE = 0;

    // joystick
    frc::Joystick m_stick{ 0 };
    frc::Joystick m_secondarystick{ 1 };
    // camera
    cs::UsbCamera m_camera;

    //frc::PIDController pid(0, 0, 0, frc::PIDSource::GetPIDSourceType(m_liftEncoder.Get()), );

    // drive
    frc::PWMVictorSPX m_leftMotor{ LEFT_MOTOR_PIN };
    frc::PWMVictorSPX m_rightMotor{ RIGHT_MOTOR_PIN };
    frc::DifferentialDrive m_robotDrive{ m_leftMotor, m_rightMotor };
    // intake
    frc::Spark m_intakeMotor{ INTAKE_MOTOR_PIN };
    WPI_VictorSPX m_armMotor{ 0 };
    WPI_VictorSPX m_armMotor2{ 1 };
    frc::Encoder m_liftEncoder{ 0, 1, false, frc::Encoder::EncodingType::k2X };
    // pneumatics
    frc::Compressor* m_compressor = new frc::Compressor(0);
    frc::DoubleSolenoid m_intakeSolenoid{ INTAKE_SOLONOID_PIN_1, INTAKE_SOLONOID_PIN_2 };
    frc::DoubleSolenoid m_hatchSolenoid{ HATCH_SOLONOID_PIN_1, HATCH_SOLONOID_PIN_2 };

    // periodic functions
    void DriveWithJoystick();
    void ControlIntakeMotor();

    void ControlCompressorEnabledState();
    void ControlIntakePiston();
    void ControlHatchPiston();
    void ControlArmMotor();

    void DisplayShuffleBoardInformation();
};

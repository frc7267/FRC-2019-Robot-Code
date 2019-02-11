/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

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
    const int LEFT_MOTOR_PIN = 0;
    const int RIGHT_MOTOR_PIN = 1;
    const int INTAKE_MOTOR_PIN = 2;
    const int CAMERA_SERVO_PIN = 6;
    // PCM pin constants
    const int SWINGY_LIFT_SOLONOID_PIN_1 = 0;
    const int SWINGY_LIFT_SOLONOID_PIN_2 = 1;
    const int HATCH_SOLONOID_PIN_1 = 2;
    const int HATCH_SOLONOID_PIN_2 = 3;
    // camera constants
    const int CAMERA_RES_W = 320;
    const int CAMERA_RES_H = 240;
    const int CAMERA_FPS = 15;
    // buttons constants
    const int INTAKE_SUCC_BUTTON = 7;
    const int INTAKE_PUKE_BUTTON = 8;
    const int COMPRESSOR_ON_BUTTON = 11;
    const int COMPRESSOR_OFF_BUTTON = 12;
    const int SWINGY_LIFT_OUT_BUTTON = 3;
    const int SWINGY_LIFT_IN_BUTTON = 4;
    const int HATCH_IN_BUTTON = 9;
    const int HATCH_OUT_BUTTON = 10;
    // speed constants
    const float INTAKE_SPEED = 1.0; // succ is negative, puke is positive
    const float DRIVE_X_SPEED = 1.0;
    const float DRIVE_Y_SPEED = -1.0; // y axis is inverted

    // joystick
    frc::Joystick m_stick{ 0 };
    // camera
    cs::UsbCamera m_camera;
    frc::Servo* m_cameraServo = new frc::Servo(CAMERA_SERVO_PIN);
    // drive
    frc::PWMVictorSPX m_leftMotor{ LEFT_MOTOR_PIN };
    frc::PWMVictorSPX m_rightMotor{ RIGHT_MOTOR_PIN };
    frc::DifferentialDrive m_robotDrive{ m_leftMotor, m_rightMotor };
    // intake
    frc::Spark m_intakeMotor{ INTAKE_MOTOR_PIN };
    // pneumatics
    frc::Compressor* m_compressor = new frc::Compressor(0);
    frc::DoubleSolenoid m_swingyLiftSolenoid{ SWINGY_LIFT_SOLONOID_PIN_1, SWINGY_LIFT_SOLONOID_PIN_2 };
    frc::DoubleSolenoid m_hatchSolenoid{ HATCH_SOLONOID_PIN_1, HATCH_SOLONOID_PIN_2 };

    // periodic functions
    void DriveWithJoystick();
    void ControlCameraServo();
    void ControlIntake();
    void ControlCompressorEnabledState();
    void ControlSwingyLiftPiston();
    void ControlHatchPiston();
    void DisplayShuffleBoardInformation();
};

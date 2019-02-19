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
    m_camera = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
    m_camera.SetResolution(CAMERA_RES_W, CAMERA_RES_H);
    m_camera.SetFPS(CAMERA_FPS);
    // intake motor settings
    m_intakeMotor.EnableDeadbandElimination(true);
    // compressor settings
    m_compressor->SetClosedLoopControl(false);

    //testMotor.ConfigPeakCurrentLimit(35, 10); /* 35 A */
    //testMotor.ConfigPeakCurrentDuration(200, 10); /* 200ms */
    //testMotor.ConfigContinuousCurrentLimit(30, 10);   /* 30A */
    //testMotor.EnableCurrentLimit(true);
}

void Robot::RobotPeriodic()
{
    DriveWithJoystick();
    ControlIntakeMotor();

    ControlCompressorEnabledState();
    ControlIntakePiston();
    ControlHatchPiston();

    DisplayShuffleBoardInformation();
}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
    //testMotor.Set(ControlMode::Velocity, 1);
}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}

void Robot::DriveWithJoystick()
{
    // acrade drive
    float xDrive = m_stick.GetX() * DRIVE_X_SPEED;
    float yDrive = m_stick.GetY() * DRIVE_Y_SPEED;
    m_robotDrive.ArcadeDrive(yDrive, xDrive);
}

void Robot::ControlIntakeMotor()
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

void Robot::ControlCompressorEnabledState()
{
    // turn on compressor
    if (m_stick.GetRawButton(COMPRESSOR_ON_BUTTON)) {
        m_compressor->SetClosedLoopControl(true);
    }
    // turn off compressor
    else if (m_stick.GetRawButton(COMPRESSOR_OFF_BUTTON)) {
        m_compressor->SetClosedLoopControl(false);
    }
}

void Robot::ControlIntakePiston()
{
    // extend piston
    if (m_stick.GetRawButton(INTAKE_OUT_BUTTON)) {
        m_intakeSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
    }
    // retract piston
    else if (m_stick.GetRawButton(INTAKE_IN_BUTTON)) {
        m_intakeSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    // do nothing with piston
    else {
        m_intakeSolenoid.Set(frc::DoubleSolenoid::Value::kOff);
    }
}

void Robot::ControlHatchPiston()
{
    // extend piston
    if (m_stick.GetRawButton(HATCH_IN_BUTTON)) {
        m_hatchSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
    }
    // retract piston
    else if (m_stick.GetRawButton(HATCH_OUT_BUTTON)) {
        m_hatchSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    // do nothing with piston
    else {
        m_hatchSolenoid.Set(frc::DoubleSolenoid::Value::kOff);
    }
}

void Robot::DisplayShuffleBoardInformation()
{
    frc::SmartDashboard::PutBoolean("Compressor Enabled?", m_compressor->Enabled());
}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif

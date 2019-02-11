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
}

void Robot::RobotPeriodic()
{
    DriveWithJoystick();
    ControlCameraServo();
    ControlIntake();
    ControlCompressorEnabledState();
    ControlSwingyLiftPiston();
    DisplayShuffleBoardInformation();
}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {}

void Robot::DriveWithJoystick()
{
    // acrade drive
    float xDrive = m_stick.GetX() * DRIVE_X_SPEED;
    float yDrive = m_stick.GetY() * DRIVE_Y_SPEED;
    m_robotDrive.ArcadeDrive(yDrive, xDrive);
}

void Robot::ControlCameraServo()
{
    // control camera servo with throttle
    double servoVal = 0.5 * (m_stick.GetThrottle() + 1); // convert from -1 to 1 to 0 to 1
    m_cameraServo->Set(servoVal);
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

void Robot::ControlSwingyLiftPiston()
{
    // extend piston
    if (m_stick.GetRawButton(SWINGY_LIFT_OUT_BUTTON)) {
        m_swingyLiftSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
    }
    // retract piston
    else if (m_stick.GetRawButton(SWINGY_LIFT_IN_BUTTON)) {
        m_swingyLiftSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    // do nothing with piston
    else {
        m_swingyLiftSolenoid.Set(frc::DoubleSolenoid::Value::kOff);
    }
}

void Robot::DisplayShuffleBoardInformation()
{
    frc::SmartDashboard::PutBoolean("Compressor Enabled?", m_compressor->Enabled());
    frc::SmartDashboard::PutNumber("Camera Angle", m_cameraServo->GetAngle());
}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif

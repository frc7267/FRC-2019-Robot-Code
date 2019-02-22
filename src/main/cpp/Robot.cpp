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
    m_intakeMotor.EnableDeadbandElimination(false);
    // compressor settings
    m_compressor->SetClosedLoopControl(false);


    //lift encoder settings
    m_liftEncoder.Reset();
    m_liftEncoder.SetMaxPeriod(0.1);
    m_liftEncoder.SetMinRate(10);
    m_liftEncoder.SetDistancePerPulse(5);
    m_liftEncoder.SetReverseDirection(false);
    m_liftEncoder.SetSamplesToAverage(10);
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
    ControlArmMotor();

    DisplayShuffleBoardInformation();
    //manual override
    if (m_secondarystick.GetRawAxis(MANUAL_OVERRIDE_BUTTON) > 0.7) {
        manual = true;
    }
    else if (manual)
    {
        //reset encoder the first loop after manual override is released;
        m_liftEncoder.Reset();
        ARM_TARGET_ANGLE = 0;
        manual = false;
    }
    else
    {
        manual = false;
    }
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

void Robot::ControlIntakeMotor()
{
    if(!m_cargoSwitch.Get() && !manual)
    {
        m_intakeMotor.SetSpeed(std::fmax(-m_secondarystick.GetRawAxis(INTAKE_AXIS), 0));
        if(m_secondarystick.GetRawAxis(INTAKE_AXIS) > 0.4)
        {
            std::cout << "rumble" << std::endl;
            m_secondarystick.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 1.0);
            m_secondarystick.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 1.0);
        }
    }
    else
    {
        m_intakeMotor.SetSpeed(-m_secondarystick.GetRawAxis(INTAKE_AXIS));
    }
}

void Robot::ControlArmMotor()
{
    // up
    /*if (m_stick.GetRawButton(ARM_UP_BUTTON)) {
        m_armMotor.Set(ControlMode::PercentOutput, ARM_SPEED);
    }
    // down
    else if (m_stick.GetRawButton(ARM_DOWN_BUTTON)) {
        m_armMotor.Set(ControlMode::PercentOutput, -ARM_SPEED);
    }
    // stop
    else {
        m_armMotor.Set(ControlMode::PercentOutput, 0);
    }*/
    if (m_secondarystick.GetRawButton(ARM_UP_BUTTON)) {
        ARM_TARGET_ANGLE = 100;
    }
    // down
    else if (m_secondarystick.GetRawButton(ARM_DOWN_BUTTON)) {
        ARM_TARGET_ANGLE = 0;
    }
    else if (m_secondarystick.GetRawButton(7)) {
        DEADZONE--;
    }
    else if (m_secondarystick.GetRawButton(8)) {
        DEADZONE++;
    }
    else if (m_secondarystick.GetRawButton(3)) {
        ARM_TARGET_ANGLE = 200;
    }
    else if (m_secondarystick.GetRawButton(2)) {
        ARM_TARGET_ANGLE = 400;
    }
    float error = m_liftEncoder.Get() / ARM_COUNTS_PER_DEGREE - ARM_TARGET_ANGLE;
    float currspeed;
    if(abs(error) < ERROR_SLOWDOWN_MAX)
    {
        currspeed = (abs(error) - DEADZONE) / ERROR_SLOWDOWN_MAX;
    }
    else
    {
        currspeed = 1;
    }
    if(!manual)
    {
        if(error < DEADZONE)
        {
            m_armMotor.Set(ControlMode::PercentOutput, ARM_SPEED * currspeed);
            m_armMotor2.Set(ControlMode::PercentOutput, -ARM_SPEED * currspeed);
        }
        else if(error > DEADZONE)
        {
            m_armMotor.Set(ControlMode::PercentOutput, -ARM_SPEED * currspeed);
            m_armMotor2.Set(ControlMode::PercentOutput, ARM_SPEED * currspeed);
        }
        else
        {
            m_armMotor.Set(ControlMode::PercentOutput, 0);
            m_armMotor2.Set(ControlMode::PercentOutput, 0);
        }
    }
    else
    {
        m_armMotor.Set(ControlMode::PercentOutput, -ARM_SPEED * m_secondarystick.GetRawAxis(MANUAL_LIFT_AXIS));
        m_armMotor2.Set(ControlMode::PercentOutput, ARM_SPEED * m_secondarystick.GetRawAxis(MANUAL_LIFT_AXIS));
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
    if (m_secondarystick.GetPOV(0) == 315 || m_secondarystick.GetPOV(0) == 45 || m_secondarystick.GetPOV(0) == 0) {
        m_intakeSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
    }
    // retract piston
    else if (m_secondarystick.GetPOV(0) >= 135 && m_secondarystick.GetPOV(0) <= 225) {
        m_intakeSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    // do nothing with piston
    else {
        m_intakeSolenoid.Set(frc::DoubleSolenoid::Value::kOff);
    }
}

void Robot::ControlHatchPiston()
{
    if (m_secondarystick.GetPOV(0) >= 15 && m_secondarystick.GetPOV(0) <= 135) {
        m_hatchSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
    }
    // retract piston
    else if (m_secondarystick.GetPOV(0) >= 225 && m_secondarystick.GetPOV(0) <= 315) {
        m_hatchSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    // do nothing with piston
    else {
        m_hatchSolenoid.Set(frc::DoubleSolenoid::Value::kOff);
    }
}

void Robot::DisplayShuffleBoardInformation()
{
    //frc::ShuffleboardTab tab = 
    //frc::Shuffleboard::GetTab("SmartDashboard");
    //double p = frc::Shuffleboard::GetTab("SmartDashboard").add("P value", 1).getEntry();
    frc::SmartDashboard::PutBoolean("Compressor Enabled?", m_compressor->Enabled());
    //std::cout << p << std::endl;
    //std::cout << frc::SmartDashboard::GetNumber("Porportional Coefficient", -1) << std::endl;
}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif

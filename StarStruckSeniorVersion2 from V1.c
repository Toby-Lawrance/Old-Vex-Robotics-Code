#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in6,    LeftForkPot,    sensorPotentiometer)
#pragma config(Sensor, in7,    RightForkPot,   sensorPotentiometer)
#pragma config(Motor,  port1,           LeftBack,      tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           RightBack,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RightLauncher, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LeftLauncher,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           LeftFront,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          RightFront,    tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#include "UsefulFunctions.c"


int LPotDebug = SensorValue[LeftForkPot];




/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Functions
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
void SetLauncherPower(int Power)
{
	motor[LeftLauncher] = Power;
	motor[RightLauncher] = Power;
}

int DesiredHeight;
int PowerToMotor;
bool AdjustingHeight = false;
task BringToHeight()
{
	AdjustingHeight = true;
	PowerToMotor = motor[LeftLauncher];
	while(!InRange(SensorValue[LeftForkPot],DesiredHeight,100))
{
	if(SensorValue[LeftForkPot] < DesiredHeight)
	{
		PowerToMotor += 1;
	} else if (SensorValue[LeftForkPot] < DesiredHeight)
	{
		PowerToMotor -= 1;
	}

	PowerToMotor = ClampValue(PowerToMotor,127,-127);

	SetLauncherPower(PowerToMotor);
	wait1Msec(Responsiveness);
}
AdjustingHeight = false;
}

void DoButtons()
{
	if (L1) {}
	if (L2) {}
	if (R1) {SetLauncherPower(127);}
	if (R2) {SetLauncherPower(-127);}
	if(!R2 && !R1) {SetLauncherPower(0);}
	if (DUp) {}//DesiredHeight = 2000; if(!AdjustingHeight){startTask(BringToHeight);}}
	if (DDown) {}//DesiredHeight = 1200; if(!AdjustingHeight){startTask(BringToHeight);}}
	if (DLeft) {}
	if (DRight) {}
	if (Triangle) {}
	if (X) {}
	if (Square) {}
	if (Circle) {}
}
/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	motor[LeftBack] =-127;
	motor[RightBack] =-127;
	motor[LeftFront] =-127;
	motor[RightFront] =-127;
	SetLauncherPower(-127); //Set to positive if Unhook is upwards
	wait1Msec(250);
	SetLauncherPower(127);
	wait1Msec(250);

	SetLauncherPower(-127);
	wait1Msec(1000);
	motor[LeftBack] =0;
	motor[RightBack] =0;
	motor[LeftFront] =0;
	motor[RightFront] =0;
	SetLauncherPower(127);
	wait1Msec(1000);
	SetLauncherPower(0);


	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop
	startTask(CheckInput);
	while (true)
	{
		XDrive(LeftFront,LeftBack,RightFront,RightBack);
		DoButtons();

		LPotDebug = SensorValue[LeftForkPot];
	}
}
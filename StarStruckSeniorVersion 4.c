#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    ClawPot,           sensorPotentiometer)
#pragma config(Sensor, in2,    ArmPot,            sensorPotentiometer)
#pragma config(Sensor, I2C_1,  LeftEnc,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  RightEnc,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           RightRearDrive, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           RightFrontDrive, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           RightArmOutside, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           RightArmInside, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LeftArmInside, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LeftArmOutside, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           Claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LeftFrontDrive, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port10,          LeftRearDrive, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
#include "UsefulFunctions.c"


int ClawPower = 0;
int ArmPower = 0;

///////////////////////////////////////////////////////////////////////
int ClawPotValue;
int ArmPotValue;
task SensorInput()
{
	while(true)
	{
		ClawPotValue = SensorValue[ClawPot];
		ArmPotValue = SensorValue[ArmPot];
		wait1Msec(Responsiveness);
	}
}
///////////////////////////////////////////////////////////////////////
int HoldClawValue;
bool Holding = false;
///////////////////////////////////////////////////////////////////////
const int MinClaw = 3470;
const int MaxClaw = 250;
const int MaxArm = 3084;
const int MinArm = 1010;
const int IdealArm = 2500;
const int FlatClaw = 1800;
const int JustOutClaw = 3000;
///////////////////////////////////////////////////////////////////////
void SetArmPower(int Power)
{
	Power = ClampValue(Power,127,-127);
	motor[LeftArmInside] = Power;
	motor[LeftArmOutside] = Power;
	motor[RightArmInside] = Power;
	motor[RightArmOutside] = Power;
}

void SetClawPower(int Power)
{
	Power = ClampValue(Power,127,-127);
	motor[Claw] = Power;
}

task Update()
{
	while(true)
	{
		SetArmPower(ArmPower);
		SetClawPower(ClawPower);
		wait1Msec(Responsiveness);
	}
}

bool RaiseArm()
{
	if(ClawPotValue > JustOutClaw)
	{
		ClawPower = 127;
		return true;
	} else
	{
		if(ArmPotValue < MaxArm)
		{
			ArmPower = 127;
			return true;
		}
		else
		{
			ArmPower = 10;
			return false;
		}
	}
}

bool RaiseArm(int Value)
{
	if(ClawPotValue > JustOutClaw)
	{
		ClawPower = 127;
	} else
	{
		if(ArmPotValue < Value)
		{
			ArmPower = 127;
			return true;
		}
		else
		{
			ArmPower = 10;
			return false;
		}
	}
}

void TurnBy(float Degrees)
{
	
}

void TurnBy(float Degrees, unsigned int Power)
{
	
}

bool LowerArm()
{
	if(ArmPotValue  > MinArm)
	{
		ArmPower = -63;
		return true;
	}
	else
	{
		ArmPower = -10;
		return false;
	}

}

bool LowerArm(int Value)
{
	if(ArmPotValue  > Value)
	{
		ArmPower = -63;
		return true;
	}
	else
	{
		ArmPower = -10;
		return false;
	}

}

task HoldObject()
{
	while(Holding)
	{
		if(ClawPotValue > HoldClawValue)
		{
			ClawPower = 127;
		}
	}
}


bool CloseClaw()
{
	HoldClawValue = ClawPotValue;
	Holding = true;

	if(ClawPotValue  > MaxClaw)
	{
		ClawPower = 127;
		startTask(HoldObject);
		return true;
	}
	else
	{
		Holding = false;
		ClawPower = 0;
		return false;
	}

}

bool CloseClaw(int Value)
{

	if(ClawPotValue  > Value)
	{
		ClawPower = 127;
		return true;
	}
	else
	{
		ClawPower = 0;
		return false;
	}

}

bool OpenClaw()
{
	Holding = false;
	if(ClawPotValue  < JustOutClaw)
	{
		ClawPower = -127;
		return true;
	}
	else
	{
		ClawPower = -10;
		return false;
	}

}

bool OpenClaw(int Value)
{
	if(ClawPotValue  < Value)
	{
		ClawPower = -127;
		return true;
	}
	else
	{
		ClawPower = -10;
		return false;
	}

}


enum Direction
{
	Forwards,
	Backwards
};

void DriveFor(int MS, Direction D)
{
	MS = abs(MS);
	int Power = 127;
	if(D == Backwards)
	{
		Power *= -1;
	}
	motor[LeftFrontDrive] = Power;
	motor[LeftRearDrive] = Power;
	motor[RightFrontDrive] = Power;
	motor[RightRearDrive] = Power;
	if(MS == 0)
	{
		return;
	} else
	{
		wait1Msec(MS);
		motor[LeftFrontDrive] = 0;
		motor[LeftRearDrive] = 0;
		motor[RightFrontDrive] = 0;
		motor[RightRearDrive] = 0;
	}
}
bool BringToHang()
{
	OpenClaw();
	Ljoy_y = 127;

	if(LowerArm() == false)
	{
		return OpenClaw(MinClaw);
	} else
	{
		return false;
	}

}

void DoButtons()
{
	if (!R1 && !R2) {ClawPower = 0;}
	if (!L1 && !L2) {ArmPower = 0;}
	if (R1) {CloseClaw();}
	if (R2) {OpenClaw();}
	if (L1) {RaiseArm();}
	if (L2) {LowerArm();}
	if (DUp) {}
	if (DDown) {}
	if (DLeft) {}
	if (DRight) {}
	if (Triangle) {}
	if (X) {}
	if (Square) {BringToHang();}
	if (Circle) {OpenClaw();}
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



task autonomous()
{
	startTask(SensorInput);
	startTask(Update);
	clearTimer(T1);
	DriveFor(400,Forwards);
	while(CloseClaw(FlatClaw) == true) {if(time1[T1] > 500) {RaiseArm(IdealArm);} wait1Msec(Responsiveness);}
	while(RaiseArm(IdealArm) == true) {wait1Msec(Responsiveness);}
	DriveFor(1300,Forwards);
	//while(OpenClaw(MaxClaw + 250) == true) {wait1Msec(Responsiveness);}
	//while(CloseClaw() == true) {wait1Msec(Responsiveness);}
	//DriveFor(500,Backwards);
	//while(OpenClaw(FlatClaw) == true) {wait1Msec(Responsiveness);}
	//DriveFor(500,Forwards);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop
	startTask(CheckInput);
	startTask(SensorInput);
	startTask(Update);
	while (true)
	{
		ArcadeDrive(LeftFrontDrive,LeftRearDrive,RightFrontDrive, RightRearDrive);
		DoButtons();
	}
}

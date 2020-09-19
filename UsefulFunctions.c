int Ljoy_x;  //Joystick Begin
int Ljoy_y;
int Rjoy_x;
int Rjoy_y;  //Joystick End

bool L1;    //Buttons Begin
bool L2;

bool R1;
bool R2;

bool DUp;
bool DDown;
bool DLeft;
bool DRight;

bool Triangle;
bool X;
bool Square;
bool Circle;   // Buttons End

int BtnDelay = 500;
int Responsiveness = 20;
float ZeroTolerance = 10;


int ClampValue(int Value, int Max, int Min)
{
	if(Value > Max)
	{
		return Max;
	} else if (Value < Min)
	{
		return Min;
	} else
	{
		return Value;
	}
}

bool InRange(float Actual,float Desired,float Lenience) // tolerances
{
	if(Actual < (Desired + Lenience) && Actual > (Desired - Lenience))
	{return true;}
	else
	{return false;}
}

bool ButtonDelay()
{
	if(time1[T4] > BtnDelay)
	{clearTimer(T4); return true;} else {return false;}
}


bool IsNearlyZero(int Value)
{
	if(Value > ZeroTolerance *-1 && Value < ZeroTolerance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsNearlyZero(float Value)
{
	if(Value > ZeroTolerance *-1 && Value < ZeroTolerance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

task CheckInput() {
	while(true) {
		Ljoy_x = vexRT[Ch4];
		Ljoy_y = vexRT[Ch3];

		Rjoy_x = vexRT[Ch1];
		Rjoy_y = vexRT[Ch2];

		if(vexRT[Btn5U]) {			//Trigger Buttons Begin
			L1 = true;
			} else {
			L1 = false;
		}

		if(vexRT[Btn5D]) {
			L2 = true;
			} else {
			L2 = false;
		}

		if(vexRT[Btn6U]) {
			R1 = true;
			} else {
			R1 = false;
		}

		if(vexRT[Btn6D]) {
			R2 = true;
			} else {
			R2 = false;
		}													// Trigger Buttons End



		if(vexRT[Btn7U]) {			//D-Pad Begin
			DUp = true;
			} else {
			DUp = false;
		}

		if(vexRT[Btn7D]) {
			DDown = true;
			} else {
			DDown = false;
		}

		if(vexRT[Btn7L]) {
			DLeft = true;
			} else {
			DLeft = false;
		}

		if(vexRT[Btn7R]) {
			DRight = true;
			} else {
			DRight = false;
		}											//D-Pad End

		if(vexRT[Btn8U]) {			//Right Pad Begin
			Triangle = true;
			} else {
			Triangle = false;
		}

		if(vexRT[Btn8D]) {
			X = true;
			} else {
			X = false;
		}

		if(vexRT[Btn8L]) {
			Square = true;
			} else {
			Square = false;
		}

		if(vexRT[Btn8R]) {
			Circle = true;
			} else {
			Circle = false;
		}											//Right Pad End


		wait1Msec(Responsiveness);
	}
}

void XDrive(tMotor M1, tMotor M2, tMotor M3, tMotor M4)
{
	int LeftFrontPower = Ljoy_y + Ljoy_x;
		int LeftBackPower = Ljoy_y - Ljoy_x;
		int RightFrontPower = Ljoy_y - Ljoy_x;
		int RightBackPower = Ljoy_y + Ljoy_x;

		if(Rjoy_x > 40 || Rjoy_x < -40)
		{
			LeftFrontPower = Rjoy_x/2;
			RightFrontPower = -Rjoy_x/2;
			LeftBackPower = Rjoy_x/2;
			RightBackPower = -Rjoy_x/2;
		}


		LeftFrontPower = ClampValue(LeftFrontPower, 127,-127);
		RightFrontPower = ClampValue(RightFrontPower, 127,-127);
		LeftBackPower = ClampValue(LeftBackPower, 127,-127);
		RightBackPower = ClampValue(RightBackPower, 127,-127);

		motor[M1] = LeftFrontPower;
		motor[M2] = LeftBackPower;
		motor[M3] = RightFrontPower;
		motor[M4] = RightBackPower;
}

void ArcadeDrive(tMotor M1, tMotor M2, tMotor M3, tMotor M4)
{

		int LeftFrontPower = 0;
		int LeftBackPower = 0;
		int RightFrontPower = 0;
		int RightBackPower = 0;

	if(!IsNearlyZero(Rjoy_x) || !IsNearlyZero(Ljoy_y))
	{
		LeftFrontPower = Ljoy_y + (Rjoy_x * 2);
		LeftBackPower = Ljoy_y + (Rjoy_x * 2);
		RightFrontPower = Ljoy_y - (Rjoy_x * 2);
		RightBackPower = Ljoy_y - (Rjoy_x * 2);
	}
		LeftFrontPower = ClampValue(LeftFrontPower, 127,-127);
		RightFrontPower = ClampValue(RightFrontPower, 127,-127);
		LeftBackPower = ClampValue(LeftBackPower, 127,-127);
		RightBackPower = ClampValue(RightBackPower, 127,-127);

		motor[M1] = LeftFrontPower;
		motor[M2] = LeftBackPower;
		motor[M3] = RightFrontPower;
		motor[M4] = RightBackPower;
}

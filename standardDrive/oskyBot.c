#pragma config(Motor,  port2,           rightClaw,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontRightDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backRightDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightTower,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftTower,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           backLeftDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           frontLeftDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftClaw,      tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int MAX_SPD = 127;

void drive(int fl,int fr,int bl,int br)
{
    motor[frontLeftDrive]  =    -fl;
    motor[frontRightDrive] =     fr;
    motor[backLeftDrive]   =    -bl;
    motor[backRightDrive]  =     br;
}

void liftCtrl(int rt, int lt)
{
	  motor[rightTower] =     -rt;
	  motor[leftTower]  =     lt;
}

void clawCtrl(int rc, int lc)
{
		motor[rightClaw] =     -rc;
	  motor[leftClaw]  =     lc;

}

joyStickDrive()
{
		int fw  = VexRT[Ch3] >  10 ? VexRT[Ch3] : 0; //Forward
		int bk  = VexRT[Ch3] < -10 ? VexRT[Ch3] : 0; //Back
		int le  = VexRT[Ch4] < -10 ? VexRT[Ch4] : 0; //Left
		int ri  = VexRT[Ch4] >  10 ? VexRT[Ch4] : 0; //Right

		int nsDir = fw == 0 ? bk : fw; //Decide North or South Direction
		int ewDir = ri == 0 ? le : ri; //Decide East or West Direction

		int fl = nsDir == 0 ? nsDir : ewDir; //front left wheel
    int fr = nsDir == 0 ? nsDir : ewDir; //front right wheel


		//drive(fl,fr,

}

void driveFlow()
{
    drive(VexRT[

		if (VexRT[Btn7U]) //DriveForward
	  {				//frontLeft,frontRight,backLeft,backRight
		    drive(MAX_SPD, MAX_SPD, MAX_SPD, MAX_SPD);
    }
    else if (VexRT[Btn7D]) //DriveBack
	  {
		    drive(-MAX_SPD,-MAX_SPD,-MAX_SPD,-MAX_SPD);
    }
    else if (VexRT[Btn7L]) //Turn Left
	  {
		    drive(-MAX_SPD,MAX_SPD,-MAX_SPD,MAX_SPD);
    }
    else if (VexRT[Btn7R]) //Turn Right
	  {
		    drive(MAX_SPD,-MAX_SPD,MAX_SPD,-MAX_SPD);
    }
    else
  	{
				drive(0,0,0,0);
		}
}

void liftFlow()
{
		if (VexRT[Btn5U]) //Raise Lift
	  {
		    liftCtrl(MAX_SPD,MAX_SPD)
    }
    else if (VexRT[Btn5D]) //Lower Lift
	  {
		    liftCtrl(-MAX_SPD,-MAX_SPD)
    }
    else
  	{
				liftCtrl(0,0);
		}

}

void clawFlow()
{
		if (VexRT[Btn6U]) //Open Claw
	  {
		    clawCtrl(MAX_SPD,MAX_SPD)
    }
    else if (VexRT[Btn6D]) //Open Claw
	  {
		    clawCtrl(-MAX_SPD,-MAX_SPD)
    }
    else
  	{
  			clawCtrl(0,0);
		}
}

task main()
{

		while(true)
		{
				driveFlow();
				liftFlow();
				clawFlow();
		}
}

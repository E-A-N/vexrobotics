#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  upLeftShaft,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  upperLeftSonar, sensorSONAR_mm)
#pragma config(Sensor, dgtl7,  lowerLeftSonar, sensorSONAR_mm)
#pragma config(Sensor, dgtl9,  lowerRightSonar, sensorSONAR_mm)
#pragma config(Sensor, dgtl11, upperRightSonar, sensorSONAR_mm)
#pragma config(Motor,  port1,           rightBackDrive, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           leftBackDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           flail,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           pushMech,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightFrontDrive, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int WALL_DISTANCE = 200;

void initGyro()
{
		SensorType(in1) = sensorNone;
		wait1Msec(1000);
		SensorType(in1) = sensorGyro;
		wait1Msec(2000);
}


void drive(int speed, int turn, int strafe)
{
	  speed  = -speed;    //reverse speed until ports are rearranged
		strafe = -strafe;   //reverse strafe until ports are rearranged
		motor(leftFrontDrive) = speed + turn + strafe;
		motor(leftBackDrive) = speed + turn - strafe;
		motor(rightFrontDrive) = speed - turn - strafe;
		motor(rightBackDrive) = speed - turn + strafe;
}


bool wallCheck()
{
			bool checkResult = false;
    	if (sensorValue(upperLeftSonar) < WALL_DISTANCE && sensorVAlue(upperRightSonar) < WALL_DISTANCE)
     	{		//Uppers Sensors detect Walls
   				checkResult = True;
    	}
    	else if (sensorValue(lowerLeftSonar) < WALL_DISTANCE && sensorVAlue(lowerRightSonar) < WALL_DISTANCE)
     	{		//Lower Sensors detect Walss
   				checkResult = True;
    	}
    	return checkResult;
}

void pushControl(int dir = 1)
{
		motor(pushMech) = 127 * dir;
}

void sonarDrive(int speed, int turn, int strafe, int distance)
{
		SensorValue(gyro) = 0;
		while(abs(SensorValue(upLeftShaft)) < distance && wallCheck())
		{
				drive(speed, SensorValue(gyro), strafe);
		}
		while(wallCheck())
		{
				drive(speed, SensorValue(gyro), strafe);
		}
		//break
		drive(-speed,0,-strafe);
		wait1Msec(112);
		drive(0,0,0);
}

void clearEncoders()
{
		SensorValue(upLeftShaft) = 0;
}

void autoFence(int dir = 1)
{
	/*
		This function will automously run along the
	*/
	int dist = 2000;
	//drive along the fence


}

void userDrive()
{
	while(true)
	{
		int speed = (abs(vexRT(Ch3))<20)?0: vexRT(Ch3);
		int turn = (abs(vexRT(Ch1))<20)?0: vexRT(Ch1);
		int strafe = (abs(vexRT(Ch4))<20)?0: vexRT(Ch4);

		drive(speed,turn,strafe);

		if(vexRT(Btn6U))
		{
			motor(flail) = 100;
		}
		else if(vexRT(Btn6D))
		{
			motor(flail) = -100;
		}
		else
		{
			motor(flail) = 0;
		}
	}
}

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
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  initGyro();
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
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  clearEncoders();
	//strafe distancet to the fence
	int distance1 = 760;
	sonarDrive(0, 0, 100, distance1);

	wait1Msec(100);

	//turn motor wipper on
	motor(flail) = -100;

	//drive along the fence
	clearEncoders();
	int distance2 = 2000;
	sonarDrive(70,0,0,distance2);
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

  while (true)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    userDrive();
  }
}
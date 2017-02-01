#pragma config(Sensor, in7,    rightLine,      sensorLineFollower)
#pragma config(Sensor, in8,    leftLine,       sensorLineFollower)
#pragma config(Sensor, dgtl1,  blShaftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  brShaftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl10, tlShaftEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl12, trShaftEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           bottomRight,   tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           bottomLeft,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           topLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          topRight,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int U_TURN = 1800;
const int RIGHT_ANGLE = 900;

void manualDrive()
{
	 			motor[topLeft]    = VexRT[ch2] + VexRT[ch1] + VexRT[ch4]; //Speed + Strage + turn
				motor[topRight]   = VexRT[ch2] - VexRT[ch1] - VexRT[ch4];
				motor[bottomLeft] = -(VexRT[ch2] + VexRT[ch1] - VexRT[ch4]);
				motor[bottomRight]= VexRT[ch2] - VexRT[ch1] + VexRT[ch4];
}

/*
void quickTurn(int angle, int speed)
{
	  SensorValue[gyro] = 0;
    switch(angle)
    {
    		case RIGHT_ANGLE:
				case U_TURN:
				//abs make any number positive ie abs(-1000 = 100
		    		while( abs(SensorValue[gyro]) < angle )
		    		{
				    		motor[topLeft]     = speed;
				    		motor[topRight]    = -speed;
				    		motor[bottomLeft]  = speed;
				    		motor[bottomRight] = -speed;
		    	  }
		    	  break;

				//Reverse Angles
				case -RIGHT_ANGLE:
				case -U_TURN:
						while (SensorValue[gyro] < abs(angle))
						{
								motor[topLeft]     = speed;
								motor[topRight]    = -speed;
								motor[bottomLeft]  = speed;
								motor[bottomRight] = -speed;
						}
						break;
    }
    //stop the motors and cool down
    motor[topLeft]     = 0;
		motor[topRight]    = 0;
		motor[bottomLeft]  = 0;
		motor[bottomRight] = 0;
		wait1Msec(250);
}
*/

task main()
{
	  //Calibrate the gyro sensor
	//	SensorType[gyro] = sensorNone;
		wait1Msec(1000);
	//	SensorType[gyro] = sensorGyro;
		wait1Msec(2000);

    while(true)
  	{
  			//Drive Robot With Controller

				manualDrive(); //<---Remote Control
				/*
				if (VexRT[Btn6U]) //90 Degree turn right
			  {
				    quickTurn(RIGHT_ANGLE,127);
		    }
		    if (VexRT[Btn5U]) //90 Degree turn left
			  {
				    quickTurn(-RIGHT_ANGLE,-127);
		    }
		    if (VexRT[Btn6D]) //180 Degree turn right
			  {
				    quickTurn(U_TURN,127);
		    }
		    if (VexRT[Btn5D]) //180 Degree turn left
			  {
				    quickTurn(-U_TURN,-127);
		    }
				*/
		}
}

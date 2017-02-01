#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  sonar1,         sensorSONAR_inch)
#pragma config(Sensor, dgtl3,  sonar2,         sensorSONAR_inch)
#pragma config(Sensor, dgtl5,  sonar3,         sensorSONAR_inch)
#pragma config(Sensor, dgtl7,  sonar4,         sensorSONAR_inch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           driveRightBack, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port3,           driveLeftBack, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           driveRightFront, tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port5,           driveLeftFront, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_4)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/***************************************
* Function will reset the gyro
* helps prevent drift
****************************************/
void initGyro()
{
	SensorType(in1) = sensorNone;
	wait1Msec(1000);
	SensorType(in1) = sensorGyro;
	wait1Msec(2000);
}

/***************************************
* Function will clear all drive encoders
****************************************/
void clearEncoders()
{
	resetMotorEncoder(driveLeftBack);
	resetMotorEncoder(driveLeftFront);
	resetMotorEncoder(driveRightBack);
	resetMotorEncoder(driveRightFront);
}

/***************************************
* Function is compact drive function
* negative is left while positive is right
****************************************/
void drive(int speed, int turn, int strafe)
{
	motor(driveLeftFront) = speed + turn +strafe;
	motor(driveLeftBack) = speed + turn - strafe;

	motor(driveRightFront) = speed - turn -strafe;
	motor(driveRightBack) = speed - turn + strafe;
}

/***************************************
* User drive function
* dead zone checks for small errors in remote
* shuts off remote
* kind of life calibraiation of remote
****************************************/
int const DEAD_ZONE = 10;
void userDrive()
{
	while(true)
	{
		int speed = (abs(vexRT(Ch3)) > DEAD_ZONE)?vexRT(Ch3):0;
		int turn = (abs(vexRT(Ch1)) > DEAD_ZONE)?vexRT(Ch1):0;
		int strafe = (abs(vexRT(Ch4)) > DEAD_ZONE)?vexRT(Ch4):0;

		drive(speed, turn, strafe);

		//set arm, lift, spinner, ect code here for user drive


	}
}

/***************************************
* Overloaded drive function which will
* operate on encoder distance
****************************************/
void drive(int speed, int turn, int strafe, int distanceEncoder)
{
	clearEncoders();
	bool useGyro = (turn == 0)? true: false;
	if(useGyro)SensorValue(gyro) = 0;

	while(abs(nMotorEncoder(driveLeftBack)) < distanceEncoder &&
		abs(nMotorEncoder(driveLeftFront)) < distanceEncoder &&
	abs(nMotorEncoder(driveRightBack)) < distanceEncoder &&
	abs(nMotorEncoder(driveRightFront)) < distanceEncoder)
	{
		if(useGyro)
		{
			drive(speed, SensorValue(gyro), strafe);
		}
		else
		{
			drive(speed, turn, strafe);
		}
	}

	drive(0,0,0);
}


/***************************************
* Function will check for lowest reading of
* sonars -1 is error and should be checked for
****************************************/
int sonarFront()
{
	int value1 = SensorValue(sonar1);
	int value2 = SensorValue(sonar2);

	if(value1 == -1)return value2;
	if(value2 == -1)return value1;

	if(value1 < value2) return value1;

	return value2;

}
/***************************************
* Function will check for lowest reading of
* sonars -1 is error and should be checked for
****************************************/
int sonarBack()
{
	int value3 = SensorValue(sonar3);
	int value4 = SensorValue(sonar4);

	if(value3 == -1)return value4;
	if(value4 == -1)return value3;

	if(value3 < value4) return value3;
	return value4;
}

/***************************************
* Overload function will call drive
* check if encoder distance as been passed
* or if sonar is lower or
* equal to distance sonar
****************************************/
void drive(int speed, int turn, int strafe, int distanceEncoder, int distanceSonar)
{
	clearEncoders();
	bool useGyro = (turn == 0)? true: false;
	if(useGyro)SensorValue(gyro) = 0;


	while(abs(nMotorEncoder(driveLeftBack)) < distanceEncoder &&
		abs(nMotorEncoder(driveLeftFront)) < distanceEncoder &&
	abs(nMotorEncoder(driveRightBack)) < distanceEncoder &&
	abs(nMotorEncoder(driveRightFront)) < distanceEncoder)
	{

		//check if sonar is error
		//if not error check if less than desired sonar distance
		//if so shut of drive and reutrn
		int frontSonar = sonarFront();
		int backSonar = sonarBack();
		if(frontSonar != -1)
		{
			if(frontSonar <= distanceSonar)
			{
				drive(0,0,0);
				return;
			}
		}

		if(backSonar != -1)
		{
			if(backSonar <= distanceSonar)
			{
				drive(0,0,0);
				return;
			}
		}
		//end sonar check lets drive
		if(useGyro)
		{
			drive(speed,2* SensorValue(gyro), strafe);
		}
		else
		{
			drive(speed, turn, strafe);
		}
	}


	drive(0,0,0);
}

//this is flawed strafe causes encoder count to change
//some reason cant manually set encoder count on integrated encoders any more
//needs button to hit wall or just smash wall
void driveFenceCling(int speed, int distanceEncoder, int distanceSonar)
{
	clearEncoders();
	SensorValue(gyro) = 0;

	while(abs(nMotorEncoder(driveLeftBack)) < distanceEncoder &&
				abs(nMotorEncoder(driveLeftFront)) < distanceEncoder &&
				abs(nMotorEncoder(driveRightBack)) < distanceEncoder &&
				abs(nMotorEncoder(driveRightFront)) < distanceEncoder)
	{
		int error1 = abs(sonarFront() - distanceSonar);
		int error2 = abs(sonarBack() - distanceSonar);
		int errorThreshHold = 1;

		//get one sonar back on trach
		if(error1 > errorThreshHold && error2 > errorThreshHold)
		{

			int frontSonar = sonarFront();
			int backSonar = sonarBack();

			if(frontSonar < distanceSonar && backSonar < distanceSonar)
			{
				//strafe left
				while(frontSonar < distanceSonar && backSonar < distanceSonar)
				{
					drive(0,SensorValue(gyro),-30);
					frontSonar = sonarFront();
					backSonar = sonarBack();
				}
			}
			else
			{
				//srafe right
				while(frontSonar > distanceSonar && backSonar > distanceSonar)
				{
					drive(0,SensorValue(gyro),30);
					frontSonar = sonarFront();
					backSonar = sonarBack();
				}

			}
		}
		drive(speed, 2*SensorValue(gyro), 0);
	}

	drive(0,0,0);





}

task main()
{
	clearEncoders();
	initGyro();


	//strafe left into fence
	drive(0,0, 100, 7000, 10);

	wait1Msec(100);

	clearEncoders();
	driveFenceCling(100,6000, 3);


	userDrive();
}

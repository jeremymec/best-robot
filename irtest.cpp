#include <stdio.h>
#include <unistd.h>

int init(int d_lev);
int read_analog(int ch_adc);
int set_motor(int motor, int speed);
int Sleep(int sec, int usec);
void check_wall();

int check_front();
int check_left();
int check_right();

int default_speed = 30;

int sensor1_reading;
int sensor2_reading;
int sensor3_reading;

void forwards();
void turn_around();
void turn_left();
void turn_right();
void stop();

int main()
{
	//This sets up the hardware

	init(0);

	// Calling the function to check the wall
	check_wall();
}

// The function that contains the loop which constantly runs while the robot is moving
void check_wall()
{

	while (true){
		
		front_sensor = read_analog(5);
		left_sensor = read_analog(0);
		right_sensor = read_analog(1);

		if (check_left() == 0) // if able to turn left
		{
		  stop();
		  turn_left(); // then turn left
		}

		else if (check_front() == 0 && check_right() == 0) // if walls on left, but front and right is clear
		{
		  forwards(); // then go straight ahead
		  // then continue to follow the wall follower method
		}
		
		else if (check_front() == 0) // if walls on left and right, but front is clear
		{
		  //wall follow method
		}

		else if (check_right() == 0) // if walls in front and left
		{
		  stop();
		  turn_right(); // turn right
		}
		
		else  // if stuck
		{
		  stop();
		  turn_around(); // stop and turn around
		  // then continue to follow the wall follower method
		}

		

		

	}
}

// The below code assums motor_1 is left and motor_2 is right

void stop() // sets both wheels to stop
{
    set_motor(2, 0);
    set_motor(1, 0);
	sleep(1000);
}

void forwards(){ // sets both wheels forwards at speed 30
    set_motor(2, default_speed);
    set_motor(1, default_speed);
}

void turn_around(){ // sets left wheel at speed 30
    set_motor(1, default_speed); // wants speed 30 to turn robot around 180 degrees
    set_motor(2, 0); // sets right wheel to stop
	sleep(2000);
}

void turn_right(int factor){ // sets left wheel to speed 30

    int motor_1 = default_speed;
    int motor_2 = 0;

    set_motor(1, motor_1); // wants speed 30 to turn robot right 90 degrees
    set_motor(2, motor_2); // sets right wheel to stop
	sleep(1000);
}

void turn_left(int factor){ // sets right wheel to speed 30
    int motor_1 = 0;
    int motor_2 = default_speed;

    set_motor(1, motor_1); // sets left wheel to stop
    set_motor(2, motor_2); // wants speed 30 to turn robot left 90 degrees
	sleep(1000);
}

// 1 is true, 0 is false

int check_front()
{
	// Reads the value from the front IR sensor
	int sensor1_reading = read_analog(0);

	// If the IR sensor returns below 200, it is deemed to be too close to the wall.
	int max_distance_1 = 200;

	if (sensor1_reading < max_distance_1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_left()
{
	// Reads the value from the left IR sensor
	int sensor2_reading = read_analog(1);

	// If the IR sensor returns below 200, it is deemed to be too close to the wall.
	int max_distance_2 = 200;

	if (sensor2_reading < max_distance_2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_right()
{
	// Reads the value from the right IR sensor
	int sensor3_reading = read_analog(2);

	// If the IR sensor returns below 200, it is deemed to be too close to the wall.
	int max_distance_3 = 200;

	if (sensor3_reading < max_distance_3)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

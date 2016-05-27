#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep (int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int read_analog(int ch_adc);
void wall_turn_left();
void wall_turn_right();
void wall_dead_end();
void wall_straight();

int main()
{
    init(0);

    int current_error; //keeps error of one image process

    float kp = 0.015; //proportional constant
    int proportional_signal = 0; //used with kp and set_motor

    int default_speed = 35;

    int left_max_value = 680;
    int right_max_value= 680;

    int previous_left = read_analog(0);
    int previous_middle = read_analog(1);
    int previous_right = read_analog(2);

    int previous_left1 = read_analog(0);
    int previous_middle1 = read_analog(1);
    int previous_right1 = read_analog(2);

    int previous_left2 = read_analog(0);
    int previous_middle2 = read_analog(1);
    int previous_right2 = read_analog(2);

    int left_sensor = read_analog(0);
    int middle_sensor = read_analog(1);
    int right_sensor = read_analog(2);

    int difference = 50;

    while(true){

        left_sensor = read_analog(0);
        middle_sensor = read_analog(1);
        right_sensor = read_analog(2);

        printf("Left sensor: %d Middle sensor: %d Right sensor: %d\n", left_sensor, middle_sensor, right_sensor);
        printf("Pre Left: %d Pre mid: %d Pre right: %d\n", previous_left2, previous_middle2, previous_right2);


        if (left_sensor < previous_left2-difference){//if left open
            wall_turn_left();
            printf("Left\n");
set_motor(1, 0);//right_motor); //right
            set_motor(2, 0);
break;
            continue;
        }
        else if (middle_sensor < 496 && right_sensor < previous_right2-difference){//if middle open and right open
            printf("Straight\n");
            set_motor(1,default_speed);
            set_motor(2,2+default_speed);
            while (true){
                left_sensor = read_analog(0);
                middle_sensor = read_analog(1);
                right_sensor = read_analog(2);
                if (left_sensor < previous_left2-difference){
                    wall_turn_left();
                    printf("left");
                    break;
                }
                else if (middle_sensor > 496){
                    break;
                }
                else if (right_sensor > previous_right2+difference){
                    break;
                }
                previous_left = left_sensor;
                previous_middle = middle_sensor;
                previous_right = right_sensor;
                previous_left1 = previous_left;
                previous_middle1 = previous_middle;
                previous_right1 = previous_right;
                previous_left2 = previous_left1;
                previous_middle2 = previous_middle1;
                previous_right2 = previous_right1;
            }
set_motor(1, 0);//right_motor); //right
            set_motor(2, 0);
break;
            continue;
        }
        else if (middle_sensor < 496){//if wall either side, do PID stuff
            printf("Yay\n");
            current_error = right_sensor - left_sensor;
            proportional_signal = current_error*kp;

            printf("Proportional: %d\n", proportional_signal);

            int right_motor = default_speed + proportional_signal;
            int left_motor = default_speed - proportional_signal;
            printf("Left motor: %d Right motor: %d\n\n", left_motor, right_motor);
            set_motor(1, right_motor); //right
            set_motor(2, 2+left_motor); //left
            previous_left = left_sensor;
            previous_middle = middle_sensor;
            previous_right = right_sensor;
            previous_left1 = previous_left;
            previous_middle1 = previous_middle;
            previous_right1 = previous_right;
            previous_left2 = previous_left1;
            previous_middle2 = previous_middle1;
            previous_right2 = previous_right1;

        }
        else if (left_sensor < right_sensor + 100 || left_sensor > right_sensor - 100)
        {
            wall_dead_end();
            printf("Dead end\n");
            set_motor(1,0);
            set_motor(2,0);
            break;
        }
        else {
            wall_turn_right();
            printf("Right\n");
set_motor(1, 0);//right_motor); //right
            set_motor(2, 0);
break;
            continue;
        }
        
        //printf("Right Max value: %d Left Max Value: %d\n", right_max_value, left_max_value);

    }
}

void wall_turn_left()
{

}

void wall_turn_right()
{

}

void wall_dead_end()
{

}

void wall_straight()
{

}

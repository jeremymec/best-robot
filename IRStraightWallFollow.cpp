#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep (int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int read_analog(int ch_adc);

int main()
{
    init(0);
    
    int current_error; //keeps error of one image process

    float kp = 0.015; //proportional constant
    int proportional_signal = 0; //used with kp and set_motor

    int default_speed = 37;

    int left_max_value = 680;
    int right_max_value= 680;
    int right_count = 0;
    int left_count = 0;

    bool left_at_max = false;
    bool right_at_max = false;

    while(true){
        left_count++;
        right_count++;
        int left_sensor = read_analog(1);
        int right_sensor = read_analog(0);

        if (left_sensor > left_max_value && left_count > 20){
            left_at_max = !left_at_max;
            left_count = 0;
        }

        if (right_sensor > right_max_value && right_count > 20){
            right_at_max = !right_at_max;
            right_count = 0;
        }
        
        if (right_at_max){
            right_sensor = 2*right_max_value - right_sensor;
        }

        if (left_at_max){
            left_sensor = 2*left_max_value - left_sensor;
        }

        printf("Right Max value: %d Left Max Value: %d\n", right_max_value, left_max_value);
        printf("Left sensor: %d. Right sensor: %d\n", left_sensor, right_sensor);

        current_error = right_sensor - left_sensor;
        proportional_signal = current_error*kp;

        printf("Proportional: %d", proportional_signal);

        int right_motor = default_speed - proportional_signal;
        int left_motor = default_speed + proportional_signal;
        printf("left motor: %d. right motor: %d\n\n", left_motor, right_motor);
        set_motor(1, 0);//left_motor); //right
        set_motor(2, 0);//right_motor); //left
    }
}

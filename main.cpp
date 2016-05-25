#include <stdio.h>
#include <time.h>

//loads specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int Sleep (int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int write_digital(int chan, char level);
extern "C" int read_digital(int chan, int direct);
extern "C" int select_IO(int chan, int direct);
extern "C" int read_analog(int ch_adc);
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
void gate_opening();



int main()
{
    //This sets up the RPi hardware and ensures
    //everything is working correctly
    init(0);

    gate_opening();

    return 0;
}

void gate_opening()
{
    //gate closed
    connect_to_server("130.195.6.196", 1024); //connects to gate server
    send_to_server("Please");//requests password
    char message[6];//initialises variable to store password
    receive_from_server(message);//sets variable to password
    send_to_server(message);//sends password to server
    //gate opens
}


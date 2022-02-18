#include <kipr/wombat.h>


void servos_up() // arm up
{
    enable_servos(); //turn servos on
    set_servo_position (0, 300); // arm down
    set_servo_position (2, 830); // arm down
    msleep (1500);
    disable_servos (); // turn servos off
}
void servos_down() // arm down
{	
    enable_servos(); //turn servos on
    set_servo_position (0, 1150); // arm down
    set_servo_position (2, 0); // arm down
    msleep (500);
    disable_servos (); // turn servos off
}

void Find_Approach(int num) // Function keep the selected color block in middel and robot move until color block area of camear is 18000
{
    printf("Find_Approach Start \n");
    servos_up(); // arm up
    int area = 0;
    int channel = num;
    printf("Channel is %d. \n", num);
    //while(camera_open() == 1)
    //while(get_object_count(channel) > 0) 
    //camera_open();
    if(camera_open() == 1) // Opens camera and checks for success   
    {
        printf("Camera open successful. \n");
        msleep(1000); //Waiting for camera to load
        while(area <= 18000)
        {
            camera_update();
            msleep(10);
            if(get_object_count(channel) > 0)
            {
                area = get_object_area(channel, 0);
                if (get_object_count(channel) > 0) // is the object count greater than 0
                {
                    if (get_object_center_column(channel, 0) < 69) // is the object on the left
                    {
                        motor(0,-20); // turn left
                        motor(1,20);
                    }
                    if (get_object_center_column(channel, 0) > 89) // is the object on the right
                    {
                        motor(0,20); // turn right
                        motor(1,-20);
                    }
                    if ((get_object_center_column(channel, 0) >= 69) && (get_object_center_column(channel,0) <= 89)) // object centered?
                    {
                        motor(0,20); // drive forward
                        motor(1,20);
                    }
                    area = get_object_area(channel, 0); 
                }
            }    
            else
            {
                ao();
            }
        }
    }


    printf("The final area of the object is %d. \n", area);

    camera_close(); // Camera closed

    servos_down(); //arm down
    servos_up();// arm up

    printf("Find_Approach End \n");
}

void Find(int num) // Function spin the robot to right until camera find selected color
{
    printf("Find Start \n");
    int area = 0;
    int channel = num;
    camera_open();
    printf("Camera open.\n");
    msleep(500);

    while(get_object_count(channel) == 0) // run motor until camera find selected color
    { 
        motor(0, 25);
        motor(1, -25);
        camera_update();
    }
    ao();
    area = get_object_area(channel, 0);
    printf("The area of the new object is %d.\n" ,area);

    camera_close();
    printf("Find Finish \n");
}


int main()
{
    printf("Start.\n");

    int x=0;
    while(1) // It keep running the program
    {

        if(digital(0) == 1) // If Red button pressed
        {
            for(x=0; x<1; x++)
            {
                printf("Red 0 \n");
                Find(0); 
                Find_Approach(0);
            }       
            printf("Red 0 IF END.\n");
            x=0;
            ao(); // stop the all motors
        }
        else if(digital(1) == 1) // If Blue button pressed
        {
            for(x=0; x<1; x++)
            {
                printf("Blue 1 \n");
                Find(1);
                Find_Approach(1);
            }       
            printf("Blue 1 IF END.\n");
            x=0;
            ao();
        }
        else if(digital(2) == 1)// If Yellow button pressed 
        {
            for(x=0; x<1; x++)
            {
                printf("Yellow 2 \n");
                Find(2);
                Find_Approach(2);
            }       
            printf("Yellow 2 IF END.\n");
            x=0;
            ao();
        }
        else if(digital(4) == 1) // If Orange button pressed 
        {        
            for(x=0; x<1; x++)
            {
                printf("Orange 3 \n");
                Find(3);
                Find_Approach(3);
            }       
            printf("Orange 3 IF END.\n");
            x=0;
            ao();             
        }         
    }
    return 0;
}

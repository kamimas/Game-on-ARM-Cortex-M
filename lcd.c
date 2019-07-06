#include "lcd_driver.h"
#include "lcd_graphic.h"
#include "address_map_arm.h"
#include "GSInterface.h"

/*******************************************************************************
 * The program performs the following:
 * 1. Writes INTEL FPGA COMPUTER SYSTEMS to the top of the LCD.
 * 2. Bounces a filled in rectangle around the display and off the displayed
 * text.
 ******************************************************************************/



volatile int * LED_ptr       = (int *)LED_BASE; // LED address
unsigned char array[6];
unsigned char array1[6];
int xh,yh,lngh;
volatile int lookUpTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0X79, 0x71}; //look up table for the 7 segment display
volatile int * Segment_ptr = (int *)HEX3_HEX0_BASE; // lower order 7 segment display
volatile int * Segment_ptr1 = (int *)HEX5_HEX4_BASE; // lower order 7 segment display

int hp = 6;


void health(){
    if(hp>0)
        hp--;
    
}
void GSInit(void)
{	

	
	WriteGSRegister( 	0x31 , 8);
	WriteGSRegister( 	0x2C ,11);
	WriteGSRegister(	0x2D , 8);
	
}

void crossHair(){
    LCD_line(60,28,1,1,1);
    LCD_line(68,28,1,1,1);
    LCD_line(61,29,1,1,1);
    LCD_line(67,29,1,1,1);
    LCD_line(62,30,1,1,1);
    LCD_line(66,30,1,1,1);
    LCD_line(63,31,1,1,1);
    LCD_line(65,31,1,1,1);
    LCD_line(63,32,1,1,1);
    LCD_line(65,32,1,1,1);
    LCD_line(62,33,1,1,1);
    LCD_line(66,33,1,1,1);
    LCD_line(61,34,1,1,1);
    LCD_line(67,34,1,1,1);
    LCD_line(60,35,1,1,1);
    LCD_line(68,35,1,1,1);
}

void drawChar(j,z,length){
    yh = z;
    clear_screen();
    LCD_line(0,0,hp*5,1,0);
    LCD_line(0,1,hp*5,1,0);
    int i=1;
    while(i<=12){
        LCD_line(j,z,length,1,0);
        

        if(i<=6){
            j--;
            length+=2;
        }
        else{
            j++;
            length-=2;
            }
        
        z++;
        i++;
    }
    LCD_line(j,z,15,1,1);
    LCD_line(j-1,z,15,1,1);
    LCD_line(j+1,z,15,1,1);
    LCD_line(j-7,z+7,15,1,0);
    z+=15;
    LCD_line(j-3,z,7,1,0);
    LCD_line(j-3,z,10,1,1);
    LCD_line(j-4,z,10,1,1);
    LCD_line(j+3,z,10,1,1);
    LCD_line(j+4,z,10,1,1);
    crossHair();
    refresh_buffer();
    
    xh = j;
    lngh = z;       
    
}



int GSensY(){
    int length = 1;
    MultiReadGS(0x32, array , 4);
		
    printf("DATA: %d \t", array[2]);
        
    
    if(array[3] == 0){
        
        if(array[2]>=0 && array[2] <= 75)
            {
                return 8;
            }
        
        if(array[2]>=76 && array[2] <=125)
            {
                return 6;
                }
        
        if(array[2]>=126 && array[2] <=200)
            {
                return 4;
                }
        
    }
    else if(array[3] == 255){
        
        if(array[2]>=0 && array[2] <=75)
            {
                return 20;
            }
        
        if(array[2]>=76 && array[2] <=125)
            {
                return 17;
                }
        
        if(array[2]>=126 && array[2] <=200)
            {
                return 12;
                }
        
    }

   


}
//do larger then 5


void GSensX(){
    int length = 1;
    int y;
    MultiReadGS(0x32, array , 4);
	y = GSensY();
    // x = GSensX();

    printf("DATA: %d \t", array[2]);
        
    // printf("DATA: %d \t", array[1]);
    
    // if (detect_movement) {
    //     clear_screen();
    // }


    

    if(array[1] == 0){
        
        if(array[0]>=0 && array[0] <=25)
            {
    
                
                drawChar(70,y,length);

            }
        
        if(array[0]>=26 && array[0] <=50)
            {
                
                drawChar(75,y,length);
                }
        
        if(array[0]>=51 && array[0] <=75)
            {
               
                drawChar(80,y,length);
                }
        if(array[0]>=76 && array[0] <=100)
            {
                
                drawChar(85,y,length);
                }
        if(array[0]>=101 && array[0] <=125)
            {
               
                drawChar(90,y,length);
                }
        
        if(array[0]>=126 && array[0] <=150)
            {
                
                drawChar(95,y,length);
                }
        
        if(array[0]>=151 && array[0] <=175)
            {
               
                drawChar(100,y,length);
                }
        if(array[0]>=176 && array[0] <=200)
            {
                
                drawChar(105,y,length);
                }
        if(array[0]>=201 && array[0] <=225)
            {
                
                drawChar(110,y,length);
                }
        if(array[0]>=226 && array[0] <=254)
            {
                
                drawChar(115,y,length);
                }
    }
    else if(array[1] == 255){
        
        if(array[0]>=0 && array[0] <=25)
            {
              
                drawChar(15,y,length);
                }
        
        if(array[0]>=26 && array[0] <=50)
            {
               
                drawChar(20,y,length);
                }
        
        if(array[0]>=51 && array[0] <=75)
            {

                drawChar(25,y,length);
                }
        if(array[0]>=76 && array[0] <=100)
            {
                
                drawChar(30,y,length);
                }
        if(array[0]>=101 && array[0] <=125)
            {
                
                drawChar(35,y,length);
                }
        
        if(array[0]>=126 && array[0] <=150)
            {
                
                drawChar(40,y,length);
                }
        
        if(array[0]>=151 && array[0] <=175)
            {
                
                drawChar(45,y,length);
                }
        if(array[0]>=176 && array[0] <=200)
            {
                
                drawChar(50,10,length);
                }
        if(array[0]>=201 && array[0] <=225)
            {
                
                drawChar(55,y,length);
                }
        if(array[0]>=226 && array[0] <=254)
            {
                
                drawChar(60,y,length);
                }
    }
    if(array[1]==255||array[1]==0){
        if(array[0]==255 || array[0]==0){
            
            drawChar(64,y,length);
        }
    }

}






int check(){
    printf("xh: %d\n",xh);
    if(xh>=49&&xh<=65)    
       {   health();
           return 1;}
    else
        return 0;
}





int main(void) {


    //GSensor codes
    
	I2C0Init();
	
	unsigned int delay = 0;

    GSInit();


    //random code idk wtf this is
    int          x, y, length, dir_x, dir_y;
    volatile int delay_count; // volatile so C compiler doesn't remove the loop
    volatile int *pushBtn = KEY_BASE;
    volatile int * LED_ptr       = (int *)LED_BASE; // LED address 
	int win;
    /* create a message to be displayed on the VGA display */
    


    //The declerations below corresponds to the logic of the gun
    int ammoCount = 6;


    init_spim0();
    init_lcd();

    clear_screen();

    int rlz=0;
    x      = 0;
    y      = 16;
    length = 1;
    dir_x  = 1;
    dir_y  = 1;
    //LCD_rect(x, y, length, length, 1, 1);
    
    int i=1,j=64,z=1;
    int t=1;
    
    
    while(t)
	{	
        
		GSensX();
        //for(delay_count;delay_count<=20000;delay_count++);
        if(ammoCount == 0)
            {
                *Segment_ptr1 = 0x50*256 + 0x79;
                *Segment_ptr = 0x38*16777216 + 0x5C*65536 + 0x77*256 + 0x5E;
                
            }
        else 
            {   *Segment_ptr1 = 0x00;
                *Segment_ptr = lookUpTable[ammoCount];}  
        if(*pushBtn == 1&&ammoCount>0&&rlz==0){
            rlz=1;
            ammoCount--;
            win = check();
            printf("win: %d\t",win);
            if( win == 1){
                *(LED_ptr) = 1023;
                    
            }
            else if( win == 0){
                *(LED_ptr) = 512+256+1+2;
                * Segment_ptr = 0x00;
                win = 0;
            }
        }
        if(*pushBtn == 0)
            rlz = 0;
        if(*pushBtn == 2)
            ammoCount = 6;

        if(hp == 0){
            clear_screen();
            char text_top_lcd[17]    = "   Do you want \0";
            char text_bottom_lcd[17] = " to play again? \0";
            LCD_text(text_top_lcd, 1);
            LCD_text(text_bottom_lcd,2);
            refresh_buffer();
            int status = 0,DELAY_LENGTH;
            int x = 1;
            DELAY_LENGTH = 700000;
            while(x){
                if(*pushBtn == 4)
                    {
                        x=0;
                        hp = 6;
                    }
                else if(*pushBtn == 8)
                    {
                        x=0;
                        t=0;    
                    }
                if (status == 0){
                    status = 1;
                    // Display the hex based on the input of the switches
                    *LED_ptr = 1023;
                } else {
                    status = 0;
                    *LED_ptr = 0;
                }
                // delay loop
                for (delay_count = DELAY_LENGTH; delay_count != 0; --delay_count);
            }
        }

        
        
    }

    clear_screen();
    char text_top_lcd[17]    = "   Good Luck  \0";
    LCD_text(text_top_lcd, 1);
    refresh_buffer();
    int status = 0,DELAY_LENGTH;

    DELAY_LENGTH = 700000;
    while(1){
        if (status == 0){
            status = 1;
            // Display the hex based on the input of the switches
            *LED_ptr = 1023;
        } else {
            status = 0;
            *LED_ptr = 0;
        }
        // delay loop
        for (delay_count = DELAY_LENGTH; delay_count != 0; --delay_count);
    }
    
}





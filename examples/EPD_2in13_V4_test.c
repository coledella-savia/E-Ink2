/*****************************************************************************
* | File      	:   EPD_2in13_V4_test.c
* | Author      :   Waveshare team
* | Function    :   2.13inch e-paper V4 test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2023-6-25
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_2in13_V4.h"
#include <time.h> 

int EPD_2in13_V4_test(void)
{

    Debug("EPD_2in13_V4_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    Debug("e-Paper Init and Clear...\r\n");
	EPD_2in13_V4_Init();


	struct timespec start={0,0}, finish={0,0}; 
    clock_gettime(CLOCK_REALTIME,&start);
    EPD_2in13_V4_Clear();
	clock_gettime(CLOCK_REALTIME,&finish);
    Debug("%ld S\r\n",finish.tv_sec-start.tv_sec);	

    //Create a new image cache
    UBYTE *BlackImage;
    UWORD Imagesize = ((EPD_2in13_V4_WIDTH % 8 == 0)? (EPD_2in13_V4_WIDTH / 8 ): (EPD_2in13_V4_WIDTH / 8 + 1)) * EPD_2in13_V4_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        Debug("Failed to apply for black memory...\r\n");
        return -1;
    }
    Debug("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 90, WHITE);
	Paint_Clear(WHITE);

    while(1) {
        Paint_NewImage(BlackImage, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 90, WHITE);
        Debug("Slide 1\r\n");
        Paint_SelectImage(BlackImage);
        GUI_ReadBmp("./pic/where_you_are_1bit.bmp", 0, 0);
        EPD_2in13_V4_Display(BlackImage);
        DEV_Delay_ms(30000);

        Debug("Slide 2\r\n");
        Paint_SelectImage(BlackImage);
        GUI_ReadBmp("./pic/summit.bmp", 0, 0);
        EPD_2in13_V4_Display(BlackImage);
        DEV_Delay_ms(30000);

        Paint_NewImage(BlackImage, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 90, WHITE);
        Debug("Slide 3\r\n");
        Paint_SelectImage(BlackImage);
        GUI_ReadBmp("./pic/tweet_250x122.bmp", 0, 0);
        EPD_2in13_V4_Display(BlackImage);
        DEV_Delay_ms(30000);

        Paint_NewImage(BlackImage, EPD_2in13_V4_WIDTH, EPD_2in13_V4_HEIGHT, 90, WHITE);
        Debug("Slide 4\r\n");
        Paint_SelectImage(BlackImage);
        GUI_ReadBmp("./pic/sky_window_250x122_1bit.bmp", 0, 0);
        EPD_2in13_V4_Display(BlackImage);
        DEV_Delay_ms(30000);
    }

	Debug("Clear...\r\n");
	EPD_2in13_V4_Init();
    EPD_2in13_V4_Clear();
	
    Debug("Goto Sleep...\r\n");
    EPD_2in13_V4_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    Debug("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    return 0;
}


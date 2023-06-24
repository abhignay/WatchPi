#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include <time.h>
#include <math.h>

// rp2040 libs
#include "pico/stdlib.h"
#include "pico/util/datetime.h"
#include "hardware/adc.h"
#include "hardware/rtc.h"

// external libs
#include "LCD_1in28.h"
#include "GUI_Paint.h"
#include "QMI8658.h"
#include "Debug.h"

#define BUTTON1 22 // Sponsored by Supreme

char* getMonth(int mont){
    char* realMonth;
    if (mont == 1){
        realMonth = "JAN";
    }
    else if (mont == 2){
        realMonth = "FEB";
    }
    else if (mont == 3){
        realMonth = "MAR";
    }
    else if (mont == 4){
        realMonth = "APR";
    }
    else if (mont == 5){
        realMonth = "MAY";
    }
    else if (mont == 6){
        realMonth = "JUN";
    }
    else if (mont == 7){
        realMonth = "JUL";
    }
    else if (mont == 8){
        realMonth = "AUG";
    }
    else if (mont == 9){
        realMonth = "SEP";
    }
    else if (mont == 10){
        realMonth = "OCT";
    }
    else if (mont == 11){
        realMonth = "NOV";
    }
    else if (mont == 12){
        realMonth = "DEC";
    }

    return realMonth; // probably not the best way to do this lol
}

char* getDay(int day){
    char* realDay;
    if (day == 1){
        realDay = "MON";
    }
    else if (day == 2){
        realDay = "TUE";
    }
    else if (day == 3){
        realDay = "WED";
    }
    else if (day == 4){
        realDay = "THU";
    }
    else if (day == 5){
        realDay = "FRI";
    }
    else if (day == 6){
        realDay = "SAT";
    }
    else if (day == 0){
        realDay = "SUN";
    }
    

    return realDay; // probably not the best way to do this lol
}

int batPercent(){
    // get bat voltage
    const float conversion_factor = 3.3f / (1 << 12) * 2;
    uint16_t result = adc_read();
    float batVol = result * conversion_factor;
    int batpercent = (batVol/4.2) * 100;
    return batpercent;
}

void WatchFace1(int rtcHour, int rtcMin, int rtcSec, int rtcDay, int rtcMonth, int rtcDotw){
    // get time
    char time_str[6];
    char tme_sec[2];
    sprintf(time_str, "%02d:%02d", rtcHour, rtcMin);
    sprintf(tme_sec, "%02d", rtcSec);

    // get date
    char datee[6];
    sprintf(datee, "%s-%02d", getMonth(rtcMonth), rtcDay);

    // bat percent
    char realBatPercent[3];
    sprintf(realBatPercent, "%02d", batPercent());

    char temp[3];
    sprintf(temp, "%02dC", ((int)QMI8658_readTemp() - 3));

    Paint_DrawString_EN(5, 78, ("%s", time_str), &FontRobotoMono63, WHITE, BLACK);
    Paint_DrawString_EN(197, 108, ("%s", tme_sec), &FontRobotoMono30, WHITE, BLACK);

    Paint_DrawString_EN(25, 41, ("%s", getDay(rtcDotw)), &FontRobotoMono24, GRAY, BLACK);
    Paint_DrawString_EN(125, 41, ("%s", datee), &FontRobotoMono24, GRAY, BLACK);
    Paint_DrawString_EN(22, 165, ("%s", temp), &FontRobotoMono24, GRAY, BLACK);
    Paint_DrawString_EN(164, 165, ("%s", realBatPercent), &FontRobotoMono24, GRAY, BLACK);
    Paint_DrawString_EN(206, 165, "%", &FontRobotoMono24, GRAY, BLACK);

    Paint_DrawString_EN(53, 195, ("%s", "Not-a-bomb"), &FontRobotoMono18, WHITE, RED);


    Paint_DrawLine(0, 157, 240, 157, GRAY, 1, LINE_STYLE_SOLID);
    Paint_DrawLine(0, 78, 240, 78, GRAY, 1, LINE_STYLE_SOLID);
    Paint_DrawLine(107, 78, 125, 78, BLACK, 1, LINE_STYLE_SOLID);
    Paint_DrawLine(107, 157, 125, 157, BLACK, 1, LINE_STYLE_SOLID);

}

void WatchFace2(int rtcHour, int rtcMin, int rtcSec, int rtcDay, int rtcMonth, int rtcDotw){

    // time
    char strHour[2];
    sprintf (strHour, "%02d", rtcHour);

    char strMin[2];
    sprintf (strMin, "%02d", rtcMin);

    char strSec[2];
    sprintf (strSec, "%02d", rtcSec);

    // date
    char Date[5];
    sprintf (Date, "%s-%02d", getMonth(rtcMonth), rtcDay);

    // bat
    char realBatPercent[3];
    sprintf(realBatPercent, "%02d", batPercent());

    //temp
    char temp[3];
    sprintf(temp, "%02dC", ((int)QMI8658_readTemp() - 3));

    Paint_DrawString_EN(60, 80, ("%s", strMin), &FontRobotoMono98, WBROWN, BLACK);
    Paint_DrawString_EN(52, 30, ("%s", strHour), &FontRobotoMono69, WHITE, BLACK);
    Paint_DrawString_EN(180, 106, ("%s", strSec), &FontRobotoMono33, WHITE, BLACK);

    Paint_DrawString_EN(137, 75, ("%s", Date), &FontRobotoMono22, WHITE, BLACK);
    Paint_DrawString_EN(157, 50, ("%s", getDay(rtcDotw)), &FontRobotoMono22, WBROWN, BLACK);

    Paint_DrawString_EN(110, 200, ("%s", realBatPercent), &FontRobotoMono24, WHITE, BLACK);
    Paint_DrawString_EN(139, 200, "%", &FontRobotoMono24, WHITE, BLACK);
    Paint_DrawString_EN(180, 145, ("%s", temp), &FontRobotoMono22, WBROWN, BLACK);

    Paint_DrawLine(183, 146, 220, 146, WBROWN, 1, LINE_STYLE_SOLID);
    Paint_DrawLine(142, 75, 215, 75, WBROWN, 1, LINE_STYLE_SOLID);
}

void WatchFace3(int rtcHour, int rtcMin, int rtcSec, int rtcDay, int rtcMonth, int rtcDotw){
    char strHour[3];
    sprintf (strHour, "%02d", rtcHour);

    char strMin[2];
    sprintf (strMin, "%02d", rtcMin);

    char strSec[2];
    sprintf (strSec, "%02d", rtcSec);

    // date
    char Date[5];
    sprintf (Date, "%s-%02d", getMonth(rtcMonth), rtcDay);

    // bat
    char realBatPercent[3];
    sprintf(realBatPercent, "%02d", batPercent());

    //temp
    char temp[3];
    sprintf(temp, "%02dC", ((int)QMI8658_readTemp()));

    Paint_DrawString_EN(8, 65, ("%s", strHour), &FontRobotoMono83, WHITE, GRAY);
    Paint_DrawString_EN(104, 65, ("%s", strMin), &FontRobotoMono83, ABLUE, GRAY);
    Paint_DrawString_EN(202, 86, ("%s", strSec), &FontRobotoMono27, WHITE, GRAY);

    // Paint_DrawString_EN(137, 75, ("%s", Date), &FontRobotoMono22, WHITE, BLACK);
    // Paint_DrawString_EN(157, 50, ("%s", getDay(rtcDotw)), &FontRobotoMono22, WBROWN, BLACK);

    // Paint_DrawString_EN(95, 200, ("%s", realBatPercent), &FontRobotoMono24, WHITE, BLACK);
    // Paint_DrawString_EN(139, 200, "%", &FontRobotoMono24, WHITE, BLACK);
    // Paint_DrawString_EN(180, 145, ("%s", temp), &FontRobotoMono22, WBROWN, BLACK);

    // Paint_DrawLine(183, 146, 220, 146, WBROWN, 1, LINE_STYLE_SOLID);
    // Paint_DrawLine(142, 75, 215, 75, WBROWN, 1, LINE_STYLE_SOLID);

}

void IMUFace(float accX, float accY, float accZ, float gyroX, float gyroY, float gyroZ){
    accX = accX/9.807;
    accY = accY/9.807;
    accZ = accZ/9.807;

    // accelerations
    char accx[20];
    sprintf(accx, "AccX: %0.1f ", accX);

    char acy[20];
    sprintf(acy, "AccY: %0.1f  ", accY);

    char acz[20];
    sprintf(acz, "AccZ: %0.1f  ", accZ);

    // gyros
    char gyX[20];
    sprintf(gyX, "GyX: %0.1f   ", gyroX);
    
    char gyY[20];
    sprintf(gyY, "GyY: %0.1f   ", gyroY);

    char gyZ[20];
    sprintf(gyZ, "GyZ: %0.1f   ", gyroZ);

    Paint_DrawString_EN(35, 30, ("%s", accx), &FontRobotoMono22, WHITE, BLACK);
    Paint_DrawString_EN(35, 62, ("%s", acy), &FontRobotoMono22, WHITE, BLACK);
    Paint_DrawString_EN(35, 94, ("%s", acz), &FontRobotoMono22, WHITE, BLACK);

    Paint_DrawString_EN(35, 126, ("%s", gyX), &FontRobotoMono22, WHITE, BLACK);
    Paint_DrawString_EN(35, 158, ("%s", gyY), &FontRobotoMono22, WHITE, BLACK);
    Paint_DrawString_EN(38, 192, ("%s", gyZ), &FontRobotoMono22, WHITE, BLACK);

}

void refreshDisp(int donnyJ){
    // donnyJ = 0; // DJT 2024 
    if (donnyJ == 0){
        Paint_Clear(BLACK); // idk if this is the best way to do something once lol
        donnyJ += 1;
    }
}

int main(){

    // rp2040 low level inits
    stdio_init_all();
    gpio_init(BUTTON1);
    gpio_set_dir(BUTTON1, GPIO_IN);
    gpio_pull_up(BUTTON1);

    // lcd init
    DEV_Module_Init();
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);
    DEV_SET_PWM(60);

    // adc init
    adc_init();
    adc_gpio_init(29);
    adc_select_input(3);

    // set lcd refresh param
    UDOUBLE Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }

    // setting other lcd param
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, BLACK);
    Paint_SetScale(65);
    Paint_Clear(BLACK);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(BLACK);  


    // starting rtc and setting default time and date
    datetime_t t = {
        .year  = 2023,
        .month = 01,
        .day   = 01,
        .dotw  = 0, // 0 is Sunday, so 5 is Friday
        .hour  = 00,
        .min   = 00,
        .sec   = 00
    };

    rtc_init();
    rtc_set_datetime(&t);
    sleep_us(64);

    // imu init
    QMI8658_init();
    float acc[3], gyro[3];
    unsigned int tim_count = 0;
    int faceFlag = 0;

    //misc
    int faceNum = 0; 
    int face1Flag = 0;
    int face0Flag = 0;
    int face2Flag = 0;
    uint32_t milliSec;

    while (true) {
        rtc_get_datetime(&t);
        QMI8658_read_xyz(acc, gyro, &tim_count);

        if (!gpio_get(BUTTON1)){
            faceNum += 1;
        }
        if (faceNum == 3){
            faceNum = 0;
        }

        if (faceNum == 0){
            if (face0Flag == 0){
                Paint_DrawCircle(130, 130, 133, BLACK, 1, DRAW_FILL_FULL);
                face0Flag = 1;
            }
            else{
                WatchFace2(t.hour, t.min, t.sec, t.day, t.month, t.dotw);
                face1Flag = 0;
                face2Flag = 0;
            }
            milliSec = 1000;
        }
        else if (faceNum == 1){
            if (face1Flag == 0){
                Paint_DrawCircle(130, 130, 133, BLACK, 1, DRAW_FILL_FULL);
                face1Flag = 1;
            }
            else{
                WatchFace1(t.hour, t.min, t.sec, t.day, t.month, t.dotw);
                face0Flag = 0;
                face2Flag = 0;
            }
            milliSec = 1000;
        }
        else if (faceNum == 2){
            if (face2Flag == 0){
                Paint_DrawCircle(130, 130, 133, BLACK, 1, DRAW_FILL_FULL);
                face2Flag = 1;
            }
            else{
                IMUFace(acc[0], acc[1], acc[2], gyro[0], gyro[1], gyro[2]);
            }
            milliSec = 100;
        }
        
        LCD_1IN28_Display(BlackImage);
        sleep_ms(milliSec);

    }

    return 0;
}
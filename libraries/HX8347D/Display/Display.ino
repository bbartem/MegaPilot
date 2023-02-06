#include <stdint.h>
#include <LCD.h>
#include <SPI.h>
#include <XPT2046.h>
#include <Touch.h>
#include <EEPROM.h>
 

 
void setup()
{  
  Serial.begin(9600);

    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV4);
    SPI.begin();
    
    Tft.lcd_init();                                      // init TFT library
 //   Tft.lcd_display_string(60, 120, (const uint8_t *)"Hello, world !", FONT_1608, RED);
 //   Tft.lcd_display_string(30, 152, (const uint8_t *)"2.8' TFT Touch Shield", FONT_1608, RED);

 //   Tft.lcd_draw_rect(30, 40, 150, 100, RED);
 //   Tft.lcd_draw_circle(120, 160, 50, BLUE);
 //   Tft.lcd_draw_line(30, 40, 180, 140, RED);
 //   
 //   Tft.lcd_draw_line(30, 220, 210, 240, RED);
 //   Tft.lcd_draw_line(30, 220, 120, 280, RED);
 //   Tft.lcd_draw_line(120, 280, 210, 240, RED);


    Tp.tp_init();
    Tp.tp_adjust();
   // Tp.tp_dialog();


 
}

void loop()
{

  Tp.tp_draw_board(); 
 

  int hwXpos = EEPROM.read(250);
  int hwYpos = EEPROM.read(251);
  Serial.print(hwXpos);
  Serial.print(" - ");
  Serial.println(hwYpos);
  
 if(hwXpos > 20 && hwXpos < 70 && hwYpos > 20 && hwYpos < 70){
 Tft.lcd_display_string(60, 120, (const uint8_t *)"ArduBlock", FONT_1608, RED);
  }

  if(hwXpos > 20 && hwXpos < 70 && hwYpos > 90 && hwYpos < 100){
 Tft.lcd_display_string(60, 120, (const uint8_t *)"ArduBlock", FONT_1608, WHITE);
  }
 
//Tft.lcd_display_num(50, 50, hwXpos, 4, 16, RED);
//Tft.lcd_draw_point(1, 1, RED);
  //Tft.lcd_clear_screen(WHITE);
  //delay(300);


/*
#define WHITE          0xFFFF
#define BLACK          0x0000   
#define BLUE           0x001F  
#define BRED           0XF81F
#define GRED       0XFFE0
#define GBLUE      0X07FF
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0
#define BROWN        0XBC40 
#define BRRED        0XFC07 
#define GRAY         0X8430
void lcd_draw_point(uint16_t hwXpos, uint16_t hwYpos, uint16_t hwColor);
  void lcd_display_char(uint16_t hwXpos, //specify x position.
                         uint16_t hwYpos, //specify y position.
                         uint8_t chChr,   //a char is display.
                         uint8_t chSize,  //specify the size of the char
                         uint16_t hwColor); //specify the color of the char
  //display a number at the specified position on lcd.
  void lcd_display_num(uint16_t hwXpos,  //specify x position.
                            uint16_t hwYpos, //specify y position.
                            uint32_t chNum,  //a number is display.
                            uint8_t chLen,   //length ot the number
                            uint8_t chSize,  //specify the size of the number
                            uint16_t hwColor); //specify the color of the number
  //display a string at the specified position on lcd.
  void lcd_display_string(uint16_t hwXpos, //specify x position.
                           uint16_t hwYpos,   //specify y position.
                           const uint8_t *pchString,  //a pointer to string
                           uint8_t chSize,    // the size of the string 
                           uint16_t hwColor);  // specify the color of the string
    void lcd_draw_line(uint16_t hwXpos0, //specify x0 position.
                      uint16_t hwYpos0, //specify y0 position.
                      uint16_t hwXpos1, //specify x1 position.
                      uint16_t hwYpos1, //specify y1 position.
                      uint16_t hwColor); //specify the color of the line
    void lcd_draw_circle(uint16_t hwXpos,  //specify x position.
                        uint16_t hwYpos,  //specify y position.
                        uint16_t hwRadius, //specify the radius of the circle.
                        uint16_t hwColor);  //specify the color of the circle.
    void lcd_fill_rect(uint16_t hwXpos,  //specify x position.
                   uint16_t hwYpos,  //specify y position.
                   uint16_t hwWidth, //specify the width of the rectangle.
                   uint16_t hwHeight, //specify the height of the rectangle.
                   uint16_t hwColor);  //specify the color of rectangle.
    void lcd_draw_v_line(uint16_t hwXpos, //specify x position.
                        uint16_t hwYpos, //specify y position. 
                        uint16_t hwHeight, //specify the height of the vertical line.
                        uint16_t hwColor);  //specify the color of the vertical line.
    void lcd_draw_h_line(uint16_t hwXpos, //specify x position.
                        uint16_t hwYpos,  //specify y position. 
                        uint16_t hwWidth, //specify the width of the horizonal line.
                        uint16_t hwColor); //specify the color of the horizonal line.
  void lcd_draw_rect(uint16_t hwXpos,  //specify x position.
                      uint16_t hwYpos,  //specify y position.
                      uint16_t hwWidth, //specify the width of the rectangle.
                      uint16_t hwHeight, //specify the height of the rectangle.
                      uint16_t hwColor);  //specify the color of rectangle.
 */ 
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
 


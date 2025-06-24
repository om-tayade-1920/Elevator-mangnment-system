#include <REG51.H>

// LCD Pins
sbit RS = P2^5;   // Register Select
sbit RW = P2^6;   // Read/Write
sbit E  = P2^7;   // Enable

#define LCD_DATA P1
sbit Overload = P3^4;  // Overload input

int p, q, r;

void delay_lcd()
{
    unsigned int i;
    for (i = 0; i < 1000; i++);
}

void LCD_Delay(unsigned int t)
{
    unsigned int i, j;
    for (i = 0; i < t; i++)
    {
        for (j = 0; j < 1275; j++);
    }
}

void LCD_Command(unsigned char cmd)
{
    LCD_DATA = cmd;
    RS = 0;
    RW = 0;
    E = 1;
    delay_lcd();
    E = 0;
}

void LCD_Char(unsigned char dat)
{
    LCD_DATA = dat;
    RS = 1;
    RW = 0;
    E = 1;
    delay_lcd();
    E = 0;
}

void LCD_Init()
{
    LCD_Command(0x38);  // 8-bit, 2 line mode
    LCD_Command(0x0C);  // Display ON, Cursor OFF
    LCD_Command(0x06);  // Auto Increment cursor
    LCD_Command(0x01);  // Clear Display
}

void LCD_String(char *str)
{
    while (*str)
    {
        LCD_Char(*str++);
    }
}

void delay(int c)
{
    int i, j;
    if (c == 0)
    {
        for (i = 0; i < 500; i++)
        {
            for (j = 0; j < r; j++);
        }
    }
}

void display_closed()
{
    LCD_Command(0x01);      // Clear LCD
    LCD_Command(0x80);
    LCD_String("Door Closed");
}

void up(int b)
{
    int i, j;
    LCD_Command(0x01);
    LCD_Command(0x80);
    LCD_String("Moving Up");

    for (i = 1; i <= b; i++)
    {
        for (j = 0; j <= 10; j++)
        {
            P3 = 1; delay(0);
            P3 = 2; delay(0);
            P3 = 4; delay(0);
            P3 = 8; delay(0);
            P3 = 16; delay(0);
        }
        P2 = p + i;
    }
    p = p + b;
}

void down(int b)
{
    int i, j;
    LCD_Command(0x01);
    LCD_Command(0x80);
    LCD_String("Moving Down");

    for (i = 1; i <= b; i++)
    {
        for (j = 0; j <= q; j++)
        {
            P3 = 16; delay(0);
            P3 = 8; delay(0);
            P3 = 4; delay(0);
            P3 = 2; delay(0);
            P3 = 1; delay(0);
        }
        P2 = p - i;
    }
    p = p - b;
}

void display_floor(int floor)
{
    LCD_Command(0x01);
    LCD_Command(0x80);      // First line
    LCD_String("Floor: ");
    LCD_Char(floor + '0');  // Display floor number
    LCD_Command(0xC0);      // Second line
    LCD_String("Door Open");

    LCD_Delay(500);         // 5 seconds delay

    display_closed();
}

void control(int a)
{
    int difference;
    if (a > p)
    {
        difference = a - p;
        up(difference);
    }
    else if (a < p)
    {
        difference = p - a;
        down(difference);
    }
}

void overload_alarm()
{
    LCD_Command(0x01);      // Clear LCD
    LCD_Command(0x80);
    LCD_String("Overload!");
    LCD_Command(0xC0);
    LCD_String("Remove Weight");
}

void main()
{
    int p1;
    p = 0;
    q = 10;   // Freeze count
    r = 10;   // Motor speed
    LCD_Init();
    LCD_String("Elevator Ready");
    P2 = p;

    while (1)
    {
        if (Overload == 0)   // ?? Overload NOT detected
        {
            if (P0 == 2)
            {
                p1 = 1;
                control(1);
                display_floor(1);
            }
            else if (P0 == 4)
            {
                p1 = 2;
                control(2);
                display_floor(2);
            }
            else if (P0 == 8)
            {
                p1 = 3;
                control(3);
                display_floor(3);
            }
            else if (P0 == 16)
            {
                p1 = 4;
                control(4);
                display_floor(4);
            }
            else if (P0 == 32)
            {
                p1 = 5;
                control(5);
                display_floor(5);
            }
            else if (P0 == 1)
            {
                p1 = 0;
                control(0);
                display_floor(0);
            }
        }
        else    // ?? Overload detected
        {
            overload_alarm();         // Show overload once

            while (Overload == 1);     // Wait here until overload is cleared
            LCD_Command(0x01);         // Clear LCD after overload is removed
            LCD_Command(0x80);
            LCD_String("Elevator Ready");
        }
    }
}

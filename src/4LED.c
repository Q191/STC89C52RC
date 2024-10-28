#include <8052.h>
#include <mcs51reg.h>

/*
1 A F  2 3 B
===========
E D DP C G 4


P1.0 P0.0 P0.1 P1.1 P1.2 P0.2
P0.3 P0.4 P0.5 P0.6 P0.7 P1.3

 a
f b
 g
e c
 d dp
*/

// 1 - 4 选择
int select[] = {0b0001, 0b0010, 0b0100, 0b1000};
// 0 - 9 数码管显示
int all[] = {0b10100000, 0b10111011, 0b01100010, 0b00101010, 0b00111001, 0b00101100, 0b00100100, 0b10111010, 0b00100000, 0b00101000};

void sleep(float s)
{
    int i = (int)(s * 120000000);
    while (i--)
        ;
}

void main()
{
    for (;;)
    {
        for (int i = 0; i < sizeof(all) / sizeof(int); i++)
        {
            sleep(1);
            P0 = all[i];
            // P2.7 - P2.4此时都亮
            //P2 = 0b11110000;
            P1 = 0b0000;
            sleep(1);
            P1 = 0b0001;
            sleep(1);
            P1 = 0b0011;
            sleep(1);
            P1 = 0b0111;
            sleep(1);
            P1 = 0b1111;
            sleep(1);
        }
    }
}

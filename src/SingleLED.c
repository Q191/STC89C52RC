#include <8052.h>
#include <mcs51reg.h>

// 10-17 RST // 0-7 EA ALE PSE
// 30-37     // 27-20
// P0 // dp d c e b a f g

/*
 a
f b
 g
e c
 d dp
*/

// 0-9
int all[] = {0b10000001, 0b11010111, 0b10100010, 0b10010010, 0b11010100, 0b10011000, 0b10001000, 0b111010011, 0b10000000, 0b10010000};

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
            sleep(1);
            P0 = 0b01111111;
        }
    }
}

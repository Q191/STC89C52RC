#include "8052.h"
#include "mcs51reg.h"

#define RS P2_7
#define RW P2_6
#define E P2_5
#define DATA P0
#define BUSY 0x80

#define MAX_WIDTH 0xf

void delay(unsigned char z)

{

       unsigned char x,y;

       for(x=z;x>0;x--)

              for(y=122;y>0;y--);     

}

int sleep(float s)
{
    int i = (int)(s * 12000000000);
    while (i--) {

    }
    return i;
}

unsigned char wait(void)
{
    DATA = 0xff;
    RS = 0;
    RW = 1;
    E = 0;
    E = 0;
    E = 1;
    while (DATA & BUSY)
        ;
    return DATA;
}

void writeCmd(unsigned char ch, int checkBusy)
{
    if (checkBusy)
        wait();
    DATA = ch;
    RS = 0;
    RW = 0;
    E = 0;
    E = 0;
    E = 1;
}

unsigned char readData(void)
{
    RS = 1;
    RW = 1;
    E = 0;
    E = 0;
    E = 1;
    return DATA;
}

void writeData(unsigned char ch)
{
    wait();
    DATA = ch;
    RS = 1;
    RW = 0;
    E = 0;
    E = 0;
    E = 1;
}

void writeChar(unsigned char x, unsigned y, unsigned char ch)
{
    y &= 0x1;
    x &= MAX_WIDTH;
    if (y)
    {
        x += 0x40;
    }
    x += 0x80;
    writeCmd(x, 0);
    writeData(ch);
}

void writeStr(unsigned char x, unsigned char y, unsigned char *str)
{
    y &= 0x1;
    x &= MAX_WIDTH;
    int len = 0;
    while (str[len] != '\0')
    {
        if (x <= MAX_WIDTH)
        {
            writeChar(x, y, str[len]);
            len++;
            x++;
        }
    }
}

int pow(int x, unsigned int y)
{
    if (y == 0)
    {
        return 1;
    }
    if (y == 1)
    {
        return x;
    }
    return pow(x * x, y - 1);
}

unsigned char writeNum(unsigned char x, unsigned char y, unsigned long num)
{
    unsigned char maxLen = MAX_WIDTH - x;
    if (y == 0)
    {
        maxLen += MAX_WIDTH;
    }
    unsigned char width = 1;
    unsigned long checkNum = num;
    while ((checkNum = checkNum / 10) != 0)
    {
        width++;
    }
    if (width > maxLen)
    {
        width = maxLen;
    }

    for (unsigned char i = 0; i < width; i++)
    {
        char ch = num % 10;
        num /= 10;
        writeChar((x + width - i - 1) % MAX_WIDTH, y + (x + width - i - 1) / MAX_WIDTH, ch + '0');
    }
    return width;
}

void init(void)
{
    DATA = 0;
    writeCmd(0x38, 0);
    writeCmd(0x38, 1);
    writeCmd(0x08, 1);
    writeCmd(0x01, 1);
    writeCmd(0x06, 1);
    writeCmd(0x0c, 1);
}

void main(void)
{
    init();
    char *str = "Mutability\nPercy Bysshe Shelley\nThe flower that smiles to-day\nTo-morrow dies;\nAll that we wish to stay\nTempts and then flies.\nWhat is this world’s delight?\nLightning that mocks the night,\nBrief even as bright.\nVirtue, how frail it is!\nFriendship how rare!\nLove, how it sells poor bliss\nFor proud despair!\nBut we, though soon they fall,\nSurvive their joy, and all\nWhich ours we call.\nWhilst skies are blue and bright,\nWhilst flowers are gay,\nWhilst eyes that change ere night\nMake glad the day;\nWhilst yet the calm hours creep,\nDream thou–and from thy sleep\nThen wake to weep.\n";
    int len = 581;
    for (int i = 0; i < len; i += MAX_WIDTH)
    {
        for (int j = 0; j < MAX_WIDTH; j++)
        {
            writeChar(j, 0, str[i + j]);
        }
        unsigned char pos = writeNum(0, 1, i);
        writeChar(pos, 1, '-');
        writeNum(pos + 1, 1, i + MAX_WIDTH);
        sleep(3);
    }
}

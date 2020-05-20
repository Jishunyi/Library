#include <stdio.h>
#include <stdlib.h>

const int Lenth = 8;

void ShortToChar(const unsigned short *ShortData)
{
    int i;
    unsigned char CharData[8];
    for (i = 0; i < Lenth; i += 2) //i+2是错误的
    {
        CharData[i] = ShortData[i / 2] & 0xff;            //低八位 00
        CharData[i + 1] = (ShortData[i / 2] >> 8) & 0xff; //高八位 01
    }

    //拆解成功
    //CharData[7-0]
    for (i = Lenth - 1; i >= 0; i--)
    {
        printf("%02x ", CharData[i]);
    }
}

int main(void)
{
    int i;
    unsigned short *ShortData;
    unsigned char *CharData;

    //存储八个字节数据:0x00-0x07
    //CharData[0-7]
    CharData = malloc(Lenth * sizeof(char));
    printf("接收到的数据,CharData[0-%d]\n", Lenth - 1);
    for (i = 0; i < Lenth; i++)
    {
        CharData[i] = i;
        printf("%02x ", CharData[i]);
    }

    //实际数据排列
    //CharData[7-0]
    printf("\n高位至低位,CharData[%d-0]:\n", Lenth - 1);
    for (i = Lenth - 1; i >= 0; i--)
    {
        printf("%02x ", CharData[i]);
    }

    //产生误解的操作
    //char转化为short
    ShortData = (unsigned short *)CharData;

    //数据很奇怪，但没有错
    //ShortData[0-3]
    printf("\n奇怪的形式，ShortData[0-%d]:\n", (Lenth - 1) / 2);
    for (i = 0; i < Lenth / 2; i++)
    {
        printf("%04x ", ShortData[i]);
    }

    //实际数据排列并没有发生改变
    //ShortData[3-0]
    printf("\n高位至低位，ShortData[%d-0]:\n", (Lenth - 1) / 2);
    for (i = (Lenth - 1) / 2; i >= 0; i--)
    {
        printf("%04x ", ShortData[i]);
    }

    //short转化为char
    printf("\nCharData[%d-0]:\n", Lenth - 1);
    ShortToChar(ShortData);

    return 0;
}
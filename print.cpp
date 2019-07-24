#pragma once

#include "print.h"

/*

struct packetData
{
    // Ethernet

    uint8_t dMac[5]; // 0
    uint8_t sMac[5]; // 6

    uint16_t type; // 12 // Ethernet Header -> IP Header

    // IP

    uint8_t headerLength; // 14
    uint16_t packetTotalLength; //16
    uint8_t protocol; // 23

    uint8_t sIP[3];             // 26
    uint8_t dIP[3];             // 30

    // TCP

    uint16_t sPort;             // 34
    uint16_t dPort;             // 36

    uint8_t data[9];            // 54
};

*/

void packetDataConstruct(packetData * packetdata,const u_char* packet)
{
    for (int i=0;i<6;i++)
    {
        packetdata->dMac[i] = packet[i];
    }

    for (int i=0;i<6;i++)
    {
        packetdata->sMac[i] = packet[i+6];
    }

    packetdata->type=(uint16_t)((packet[12] << 8) | packet[13]);

    packetdata->ipHeaderLength = (uint8_t)(((packet[14]<<4)>>4)*4);

    packetdata->packetTotalLength = (uint16_t)((packet[16] << 8) | packet[17]);

    packetdata->protocol = packet[23];


    for (int i=0;i<4;i++)
    {
        packetdata->sIP[i] = packet[i+26];
    }

    for (int i=0;i<4;i++)
    {
        packetdata->dIP[i] = packet[i+30];
    }

    packetdata->sPort = (uint16_t)((packet[34] << 8) | (packet[35]));
    packetdata->dPort = (uint16_t)((packet[36] << 8) | (packet[37]));

    packetdata->tcpHeaderLength = (uint8_t)((packet[52]>>4)*4);

    for (int i=0;i<10;i++)
    {
        if( (packetdata->packetTotalLength - (packetdata->ipHeaderLength + packetdata->tcpHeaderLength + 18)) < i)break;
        packetdata->data[i] = packet[i];
    }






}

void printMac(packetData * packetdata)
{
    printf("DMAC : ");
    for (int i=0;i<6;i++)
    {
        printf("%02X:", packetdata->dMac[i]);
    }
    printf("\n");

    printf("SMAC : ");
    for (int i=0;i<6;i++)
    {
        printf("%02X:", packetdata->sMac[i]);
    }
    printf("\n");
}

void printPort(packetData * packetdata)
{
    printf("DPORT : %d\n", packetdata->dPort);
    printf("SPORT : %d\n", packetdata->sPort);
}


void printIP(packetData * packetdata)
{
    printf("DIP : ");
    for (int i=0;i<4;i++)
    {
        printf("%d.", packetdata->dIP[i]);
    }
    printf("\n");

    printf("SIP : ");
    for (int i=0;i<4;i++)
    {
        printf("%d.", packetdata->dIP[i]);
    }
    printf("\n");
}

void printData(packetData * packetdata)
{
    printf("DATA : ");
    for (int i=0;i<10;i++)
    {
      if( (packetdata->packetTotalLength - (packetdata->ipHeaderLength + packetdata->tcpHeaderLength + 18)) < i)break;
       printf("%02X ",packetdata->data[i]);
    }
    printf("\n");
}

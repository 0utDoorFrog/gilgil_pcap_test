#pragma once

#include <stdint.h>
#include <pcap.h>
#include <memory.h>

struct mac
{
        uint8_t mac1;
        uint8_t mac2;
        uint8_t mac3;
        uint8_t mac4;
        uint8_t mac5;
        uint8_t mac6;
};

struct ip
{
    uint8_t ip1;
    uint8_t ip2;
    uint8_t ip3;
    uint8_t ip4;

};

struct httpPacket
{


    struct mac sMac;
    struct mac dMac;

    struct ip sIP;
    struct ip dIP;

    uint16_t sPort;
    uint16_t dPort;

    u_char data[10];
};

void httpPacketStructConstructor(httpPacket * httppacket, const u_char * packet);
void printIP(httpPacket httppacket);
void printMac(httpPacket httppacket);
void printPort(httpPacket httppacket);
void printData(httpPacket httppacket);

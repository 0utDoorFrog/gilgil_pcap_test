#pragma once

#include <pcap.h>
#include <stdio.h>
#include <stdint.h>

struct packetData
{
    // Ethernet

    uint8_t dMac[5]; // 0
    uint8_t sMac[5]; // 6

    uint16_t type; // 12 // Ethernet Header -> IP Header

    // IP

    uint8_t ipHeaderLength; // 14
    uint16_t packetTotalLength; //16
    uint8_t protocol; // 23

    uint8_t sIP[3];             // 26
    uint8_t dIP[3];             // 30

    // TCP

    uint16_t sPort;             // 34
    uint16_t dPort;             // 36
    uint8_t tcpHeaderLength;    // 52

    uint8_t data[9];            // 54
};

void packetDataConstruct(packetData * packetdata,const u_char* packet);

void printMac(packetData * packetdata);

void printPort(packetData * packetdata);

void printIP(packetData * packetdata);

void printData(packetData * packetdata);

#include <pcap.h>
#include <stdio.h>
#include <stdint.h>
#include "print.h"
#include <stdlib.h>

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

void usage() {
  printf("syntax: pcap_test <interface>\n");
  printf("sample: pcap_test wlan0\n");
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    usage();
    return -1;
  }

  char* dev = argv[1];
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
  if (handle == nullptr) {
    fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    return -1;
  }

  while (true)
  {
    struct pcap_pkthdr* header;
    const u_char* packet;
    int res = pcap_next_ex(handle, &header, &packet);
    if (res == 0) continue;
    if (res == -1 || res == -2) break;

    packetData  * packetdata = (packetData *)malloc(sizeof(packetData));
    packetDataConstruct(packetdata,packet);

    if((packetdata->sPort == 80) | (packetdata->dPort == 80)) // HTTP
    {
        printf("HTTP DETECTED : \n");

        printMac(packetdata);

        if(packetdata->type == 0x800) // IP
        {
            printf("IP DETECTED : \n");

            printIP(packetdata);

            if(packetdata->protocol == 6) // TCP
            {
                printf("TCP DETECTED : \n");

                printPort(packetdata);

                printf("DATA : ");
                for (int i=0;i<10;i++)
                {
                    if( (packetdata->packetTotalLength - (packetdata->ipHeaderLength + packetdata->tcpHeaderLength + 18)) < i)
                    {
                        break;
                    }
                    printf("%02X ",packetdata->data[i]);
                }
                printf("\n");
            }
        }
        else
        {
            printf("Other Protocol ....\n");
        }
    }
    else
    {
        printf("HTTP NOT DETECTED : \n");

        printMac(packetdata);

        if(packetdata->type == 0x800) // IP
        {
            printf("IP DETECTED : \n");

            printIP(packetdata);

            if(packetdata->protocol == 6) // TCP
            {
                printf("TCP DETECTED : \n");

                printPort(packetdata);

                printf("DATA : ");
                for (int i=0;i<10;i++)
                {
                    if( (packetdata->packetTotalLength - (packetdata->ipHeaderLength + packetdata->tcpHeaderLength + 18)) < i)
                    {
                        break;
                    }
                    printf("%02X ",packetdata->data[i]);
                }
                printf("\n");
            }
        }


    }
  }
}

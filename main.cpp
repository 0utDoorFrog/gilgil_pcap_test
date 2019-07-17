#include <stdint.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include "print.h"


void usage()
{
  printf("syntax: pcap_test <interface>\n");
  printf("sample: pcap_test wlan0\n");
}

int main(int argc, char* argv[]) // argc != 2 -> exit
{
  if (argc != 2)
  {
    usage();
    return -1;
  }

  char* dev = argv[1];
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf); // PROMISCUOUS == 1

  if (handle == nullptr) // ERROR Handeling
  {
    fprintf(stderr, "couldn't open device %s: %s\n", dev, errbuf);
    return -1;
  }

  while (true)
  {
    struct pcap_pkthdr* header;
    const u_char* packet;
    int res = pcap_next_ex(handle, &header, &packet); // get data

    if (res == 0) // SUCCESS
        continue;

    if (res == -1 || res == -2) // ERROR
        break;

    struct httpPacket httppacket;

    httpPacketStructConstructor(&httppacket,packet);

    if((httppacket.sPort == 80) || (httppacket.dPort == 80))
    {
      printf("HTTP Packet : \n");

      printMac(httppacket);

      printIP(httppacket);

      printPort(httppacket);

      printData(httppacket);
    }
    else
    {
        printf("NO HTTP Packet : \n");

        printMac(httppacket);

        printIP(httppacket);

        printPort(httppacket);
    }
  }

  pcap_close(handle);
  return 0;
}

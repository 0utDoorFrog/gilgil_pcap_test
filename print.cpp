#include "print.h"

void httpPacketStructConstructor(httpPacket * httppacket, const u_char * packet)
{
    u_char * mac = (u_char *)&packet[0];
    u_char * ip = (u_char *)&packet[26];
    u_char * port = (u_char *)&packet[34];
    u_char * data = (u_char *)&packet[38];

    httppacket->dMac.mac1 = mac[0];
    httppacket->dMac.mac2 = mac[1];
    httppacket->dMac.mac3 = mac[2];
    httppacket->dMac.mac4 = mac[3];
    httppacket->dMac.mac5 = mac[4];
    httppacket->dMac.mac6 = mac[5];
    httppacket->sMac.mac1 = mac[6];
    httppacket->sMac.mac2 = mac[7];
    httppacket->sMac.mac3 = mac[8];
    httppacket->sMac.mac4 = mac[9];
    httppacket->sMac.mac5 = mac[10];
    httppacket->sMac.mac6 = mac[11];

    httppacket->sIP.ip1 = ip[0];
    httppacket->sIP.ip2 = ip[1];
    httppacket->sIP.ip3 = ip[2];
    httppacket->sIP.ip4 = ip[3];
    httppacket->dIP.ip1 = ip[4];
    httppacket->dIP.ip2 = ip[5];
    httppacket->dIP.ip3 = ip[6];
    httppacket->dIP.ip4 = ip[7];

    httppacket->sPort = (uint16_t)((port[0] << 8 | port[1]));
    httppacket->dPort = (uint16_t)((port[2] << 8 | port[3]));

    u_char dataMiddler[10] = {data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]};
    memcpy(httppacket->data,dataMiddler,sizeof(dataMiddler));
}

void printMac(httpPacket httppacket)
{
    printf("SMAC : %02x:%02x:%02x:%02x:%02x:%02x\n", httppacket.sMac.mac1, httppacket.sMac.mac2, httppacket.sMac.mac3, httppacket.sMac.mac4, httppacket.sMac.mac5, httppacket.sMac.mac6 );
    printf("DMAC : %02x:%02x:%02x:%02x:%02x:%02x\n", httppacket.dMac.mac1, httppacket.dMac.mac2, httppacket.dMac.mac3, httppacket.dMac.mac4, httppacket.dMac.mac5, httppacket.dMac.mac6 );
}

void printIP(httpPacket httppacket)
{
    printf("SIP : %d.%d.%d.%d\n", httppacket.sIP.ip1, httppacket.sIP.ip2, httppacket.sIP.ip3, httppacket.sIP.ip4);
    printf("DIP : %d.%d.%d.%d\n", httppacket.dIP.ip1, httppacket.dIP.ip2, httppacket.dIP.ip3, httppacket.dIP.ip4);

}

void printPort(httpPacket httppacket)
{
    printf("SPORT : %d\n", httppacket.sPort);
    printf("DPORT : %d\n", httppacket.dPort);
}

void printData(httpPacket httppacket)
{
    printf("DATA : %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", httppacket.data[0], httppacket.data[1], httppacket.data[2], httppacket.data[3], httppacket.data[4], httppacket.data[5], httppacket.data[6], httppacket.data[7], httppacket.data[8], httppacket.data[9]);
}


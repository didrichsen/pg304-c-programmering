//
// Created by Simen Didrichsen on 11/03/2024.
//

#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#pragma pack(1)
typedef struct _PCAPHEADER{

    uint32_t magic_number;
    uint16_t version_major;
    uint16_t version_minor;
    uint32_t timezone;
    uint32_t timestamp_accuracy;
    uint32_t snap_length;
    uint32_t link_layer_type;

}PCAPHEADER;
#pragma pack()

#pragma pack(1)
typedef struct _PACKETHEADER{

    uint32_t timestamp_second;
    uint32_t timestamp_microseconds;
    uint32_t captured_length;
    uint32_t original_length;


}PACKETHEADER;
#pragma pack()

#pragma pack(1) // Ensure that the compiler does not add padding between the members
typedef struct _ETHERNETHEADER {
    uint8_t  dest_mac[6];   // Destination MAC address (6 bytes)
    uint8_t  src_mac[6];    // Source MAC address (6 bytes)
    uint16_t ether_type;    // EtherType field (2 bytes)
} ETHERNETHEADER;
#pragma pack()

#pragma pack(1)
typedef struct _IPV6HEADER {
    uint32_t version_traffic_class_flow_label; // Version, Traffic Class, and Flow Label
    uint16_t payload_length;                   // Payload length
    uint8_t  next_header;                      // Next Header
    uint8_t  hop_limit;                        // Hop Limit
    uint8_t  src_addr[16];                     // Source IPv6 address
    uint8_t  dest_addr[16];                    // Destination IPv6 address
} IPV6HEADER;
#pragma pack()

#pragma pack(1)
typedef struct _UDPHEADER {
    uint16_t source_port_number;                // Version, Traffic Class, and Flow Label
    uint16_t destination_port_number;           // Payload length
    uint16_t length;                            // Length of UDP header AND UDP data
    uint16_t checksum;                          // Used for error checking. Optional in IPV4, mandatory IPV6.
} UDPHEADER;
#pragma pack()

int main(void) {

    FILE *fHandler = NULL;
    PCAPHEADER pcapheader;
    PACKETHEADER packetheader;

    fHandler = fopen("file/test.pcap","rb");

    if(fHandler == NULL){
        printf("Failed to open file.");
        return 1;
    }

    fread(&pcapheader,sizeof (pcapheader),1,fHandler);

    printf("Magic Number: %2X\n",pcapheader.magic_number);
    printf("Version Major: %2X\n", pcapheader.version_major);
    printf("Version Minor: %2X\n", pcapheader.version_minor);
    printf("Timezone: %2X\n", pcapheader.timezone);
    printf("Timestamp Accuracy: %2X\n", pcapheader.timestamp_accuracy);
    printf("Snap Length: %2X\n", pcapheader.snap_length);
    printf("Link Layer Type: %2X\n", pcapheader.link_layer_type);

        while (1) {
            // Read the packet header
            if (fread(&packetheader, sizeof(packetheader), 1, fHandler) != 1) {
                if (!feof(fHandler)) {
                    perror("Failed to read packet header");
                }
                break; // Break the loop on error or end of file
            }

            // Print packet header information
            printf("\n|PACKET HEADER|\n");
            printf("Timestamp Seconds: %u\n", packetheader.timestamp_second);
            printf("Timestamp Microseconds: %u\n", packetheader.timestamp_microseconds);
            printf("Captured Length: %u\n", packetheader.captured_length);
            uint8_t *packet_data = (uint8_t *) malloc(packetheader.captured_length);
            if (packet_data == NULL) {
                perror("Failed to allocate memory for packet data");
                break;
            }

            // Read the packet data
            if (fread(packet_data, packetheader.captured_length, 1, fHandler) != 1) {
                perror("Failed to read packet data");
                free(packet_data);
                break;
            }

            ETHERNETHEADER *eth_header = (ETHERNETHEADER *)packet_data;

            // Now you can access the Ethernet header fields, for example:
            printf("\n|ETHERNET HEADER|\n");
            printf("\nDestination MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                   eth_header->dest_mac[0], eth_header->dest_mac[1], eth_header->dest_mac[2],
                   eth_header->dest_mac[3], eth_header->dest_mac[4], eth_header->dest_mac[5]);
            printf("Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                   eth_header->src_mac[0], eth_header->src_mac[1], eth_header->src_mac[2],
                   eth_header->src_mac[3], eth_header->src_mac[4], eth_header->src_mac[5]);
            printf("EtherType: %04X\n", ntohs(eth_header->ether_type));

            if(ntohs (eth_header->ether_type) == 0x86DD){
                printf("\n|IPV6 HEADER|\n");
                IPV6HEADER *ipv6Header = (IPV6HEADER*) (packet_data + sizeof (ETHERNETHEADER));
                printf("\nSource Address: %02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X\n",
                       ipv6Header->src_addr[0], ipv6Header->src_addr[1], ipv6Header->src_addr[2], ipv6Header->src_addr[3],
                       ipv6Header->src_addr[4], ipv6Header->src_addr[5], ipv6Header->src_addr[6], ipv6Header->src_addr[7],
                       ipv6Header->src_addr[8], ipv6Header->src_addr[9], ipv6Header->src_addr[10], ipv6Header->src_addr[11],
                       ipv6Header->src_addr[12], ipv6Header->src_addr[13], ipv6Header->src_addr[14], ipv6Header->src_addr[15]);

                printf("Destination Address: %02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X\n",
                       ipv6Header->dest_addr[0], ipv6Header->dest_addr[1], ipv6Header->dest_addr[2], ipv6Header->dest_addr[3],
                       ipv6Header->dest_addr[4], ipv6Header->dest_addr[5], ipv6Header->dest_addr[6], ipv6Header->dest_addr[7],
                       ipv6Header->dest_addr[8], ipv6Header->dest_addr[9], ipv6Header->dest_addr[10], ipv6Header->dest_addr[11],
                       ipv6Header->dest_addr[12], ipv6Header->dest_addr[13], ipv6Header->dest_addr[14], ipv6Header->dest_addr[15]);
                printf("Next Header: %02X\n",ipv6Header->next_header);

                if(ipv6Header->next_header == 0x11){
                    printf("\n|UDP Header|\n");
                    UDPHEADER *udpheader = (UDPHEADER*) (packet_data + sizeof (ETHERNETHEADER) + sizeof (IPV6HEADER));
                    printf("\nSource Port Number: %u\n", ntohs(udpheader->source_port_number));
                    printf("Destination Port Number: %u\n", ntohs(udpheader->destination_port_number));
                    printf("Length of UDP header and UDP Data: %u\n", ntohs(udpheader->length));
                    printf("Checksum: %u\n", ntohs(udpheader->checksum));

                    int payloadLength = ntohs(udpheader->length) - 8;

                    //Lets move the pointer to where the data is starting
                    uint8_t *pPayload = (uint8_t*) (packet_data + sizeof (ETHERNETHEADER) + sizeof (IPV6HEADER) + sizeof (udpheader));

                    printf("\n|Payload Start|\n");
                    for(int i = 0; i < payloadLength; i++){
                        printf("%02X ", *pPayload);
                        pPayload++;
                    }
                    printf("\n |Payload Ended| \n");

                }
            }


            // Free the packet data
            free(packet_data);

            // At this point, you are at the beginning of the next packet header
        }



}
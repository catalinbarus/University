#include <queue.h>
#include "skel.h"

//Structura folosita pentru tabela de rutare
struct route_table_entry {
    uint32_t prefix;
    uint32_t next_hop;
    uint32_t mask;
    int interface;
} __attribute__((packed));

//Strcutura folosita pentru tabela ARP
struct arp_entry {
    __u32 ip;
    uint8_t mac[6];
};

struct route_table_entry *rtable;
int rtable_size = 0;

struct arp_entry *arp_table;
int arp_table_len = 0;

struct route_table_entry *get_best_route(__u32 dest_ip) {
    
    /* Compar mastile din tabela de rutare pentru a obtine drumul cel mai bun*/
    uint32_t maxMASK = 0;
    int ok = 0;
    struct route_table_entry *match;

    for (int i = 0; i < rtable_size; i++) {

        if ((rtable[i].mask & dest_ip) == rtable[i].prefix) {

            /* Masca cea mai mare reprezinta cel mai bun drum*/
            if (rtable[i].mask > maxMASK) {

                maxMASK = rtable[i].mask;
                match = &rtable[i];
                ok = 1;
            }
        }
    }

    /* Daca gasim o masca maxima, returnam intrarea din tabela de 
    rutare corespunzatoare */
    if (ok == 1) {

        return match;
    }

    /*Altfel returnam NULL */
    return NULL;
}

struct arp_entry *get_arp_entry(__u32 ip) {

    /* Verificam daca ip-ul furnizat corespunde cu cel din tabela ARP si 
    returnam intrarea corespunzatoare din tabela */
    for (int i = 0; i < arp_table_len; i++) {

        if (arp_table[i].ip == ip) {

            return &arp_table[i];
        }
    }

    return NULL;
}


/* Functie de parsare a tabelei ARP, preluata din laboratorul 4. */
void parse_arp_table() 
{
    FILE *f;
    fprintf(stderr, "Parsing ARP table\n");
    f = fopen("arp_table.txt", "r");
    DIE(f == NULL, "Failed to open arp_table.txt");
    char line[100];
    int i = 0;
    for(i = 0; fgets(line, sizeof(line), f); i++) {
        char ip_str[50], mac_str[50];
        sscanf(line, "%s %s", ip_str, mac_str);
        fprintf(stderr, "IP: %s MAC: %s\n", ip_str, mac_str);
        arp_table[i].ip = inet_addr(ip_str);
        int rc = hwaddr_aton(mac_str, arp_table[i].mac);
        DIE(rc < 0, "invalid MAC");
    }
    arp_table_len = i;
    fclose(f);
    fprintf(stderr, "Done parsing ARP table.\n");
}

/* Functie de parsare a tabelei de rutare, adaptata dupa functia de 
parse_arp_table din laboratorul 4. */
void parse_rtable(char* rtable_file)
{

    FILE *f;
    fprintf(stderr, "Parsing rtable\n");
    f = fopen(rtable_file, "r");
    DIE(f == NULL, "Failed to open rtable");
    char line[100];
    int i = 0;
    for(i = 0; fgets(line, sizeof(line), f); i++) {
        
        char prefix[100], next_hop[100], mask[100];
        int interface = 0;

        sscanf(line, "%s %s %s %d", prefix, next_hop, mask, &interface);
        rtable[i].prefix = inet_addr(prefix);
        rtable[i].next_hop = inet_addr(next_hop);
        rtable[i].mask = inet_addr(mask);
        rtable[i].interface = interface;
    }
    rtable_size = i;
    fclose(f);
    fprintf(stderr, "Done parsing rtable.\n");

}

int main(int argc, char *argv[])
{
    packet m;
    int rc;

    init(argc - 2, argv + 2);
    rtable = malloc(sizeof(struct route_table_entry) * 200000);
    arp_table = malloc(sizeof(struct  arp_entry) * 200000);
    parse_rtable(argv[1]);
    parse_arp_table();

    while (1) {
        rc = get_packet(&m);
        DIE(rc < 0, "get_message");
        /* Students will write code here */

        //Header-ul meu de ethernet
        struct ether_header *eth_hdr = (struct ether_header *)m.payload;

        //Header-ul meu de IPV4
        struct iphdr *ip_hdr = (struct iphdr *)(m.payload 
        	+ sizeof(struct ether_header));

        //Header-ul meu de ICMP
        struct icmphdr *icmp_hdr = parse_icmp(m.payload);
        
        //Task 2

        //Verific daca pachetul IP este adresat routerului
        if (ip_hdr -> daddr == inet_addr(get_interface_ip(m.interface))) {

        	//Raspund doar daca pachetul este de tip ICMP ECHO 
            if ((icmp_hdr != NULL) && (icmp_hdr -> type == ICMP_ECHO)) {

                send_icmp(ip_hdr -> saddr, ip_hdr -> daddr, 
                	eth_hdr -> ether_dhost, eth_hdr -> ether_shost, 0, 0, 
                	m.interface, icmp_hdr->un.echo.id, 
                	icmp_hdr->un.echo.sequence);
            }

            //Altfel, arunc pachetul
            continue;   
        }

        //Task 5

        //Daca ttl ajunge sa fie mai mic sau egal cu 1, trimit mesajul de
        //time exceeded
        if(ip_hdr->ttl <=1) {

            uint8_t mac[6];
            get_interface_mac(m.interface, mac);
            send_icmp_error(ip_hdr->saddr, 
            	inet_addr(get_interface_ip(m.interface)), 
            	mac, eth_hdr->ether_shost, 11, 0, m.interface);
            
            continue;
        }

        //Task 6

        //Daca checksum-ul nou nu este identic cu cel initial, arunc pachetul
        int initialChecksum = ip_hdr->check;
        ip_hdr->check = 0;
        ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

        if (ip_hdr->check != initialChecksum) {
            continue;
        }

        //Task 7

        //Decrementez tt-ul
        ip_hdr->ttl--;

        //Updatez checksum-ul
        ip_hdr->check = 0;

        ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

        
        //Task 8

        //Gasesc cea mai buna cale din tabela de rutare
        struct route_table_entry *bestRoute = get_best_route(ip_hdr->daddr);


        /* Aruncam pachetul daca nu avem o ruta potrivita */
        if (bestRoute == NULL) {

            uint8_t mac[6];
            get_interface_mac(m.interface, mac);
            send_icmp_error(ip_hdr -> saddr, 
            	inet_addr(get_interface_ip(m.interface)), mac, 
            	eth_hdr -> ether_shost, 3, 0, m.interface);

            continue;
        }


        //Task 9

        /* Convertesc adresa ip pt next hop intr-una MAC */
        struct arp_entry *matchARP = get_arp_entry(bestRoute->next_hop);

        if (matchARP == NULL) {
            continue;
        }

        /* Updatez adresa Ethernet cu noua adresa MAC gasita */
        memcpy(eth_hdr->ether_dhost, matchARP->mac, sizeof(matchARP->mac));

        /* Obtin interfata potrivita pentru destinatia pachetului, folosind 
        sursa protocolului Ethernet */
        get_interface_mac(bestRoute->interface, eth_hdr->ether_shost);


        //Task 10
        
        /* Trimit mesajul pe interfata corespunzatoare */
        send_packet(bestRoute->interface, &m);
    }
}

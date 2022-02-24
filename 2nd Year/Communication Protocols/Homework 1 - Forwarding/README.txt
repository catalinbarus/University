Student: Barus Catalin-Stefan
Grupa: 321CD

*** Tema 1 - PC ***
*** Forwarding ***

** Disclaimer **

Daca exista probleme legate de spatiere sau README ul se vede ciudat, atunci
documentul trebuie deschis cu Sublime Text sau alt editor text exhivalent.

** Setup & Problems **

In cadrul acestei teme, o buna parte din functionalitate si implementare se
aseamana cu ideea de baza din cadrul laboratorului 4, prin urmare multe functii
si structuri au fost preluate direct de acolo (vor fi mentionate pe parcurs).

Mai mult, aceasta tema depinde de fisierul arp_table.txt, deci este
o implementare cu tabela arp statica, fara protocolul arp implementat.

** Implementarea efectiva **

(Task-urile sunt numerotate dupa cerintele din enuntul temei)

* Task 1 *

Pentru inceput, parsez tabelele de rutare si ARP folosind functia de 
"parse_arp_table", preluata direct din laboratorul 4 si o versiune modificata a 
acestei functii pentru tabela de rutare. De asemenea, structurile pentru tabela 
ARP si cea de rutare sunt preluate din laboratorul 4. Mai departe, imi definesc 
header-ele de Ethernet, IPv4 si ICMP.

* Task 2 *

Ma asigur ca pachetul este de tip ICMP. In acest caz, daca este un pachet
destinat router-ului si este de tipul ICMP ECHO request, voi raspunde apeland
functia "send_icmp". Altfel, arunc pachetul.

* Task 5 *

Verific daca ttl-ul este mai mic sau egal cu 1, pentru a vedea daca este necesar
sa trimit un mesaj de tipul icmp time exceeded. Daca este cazul, apelez functia
"send_icmp_error", cu valoarea 11 (time exceeded) pentru tipul de eroare, pentru
a trimite un mesaj de eroare catre sursa corecta.

* Task 6 *

Recalculez checksum-ul si daca nu este egal cu cel initial inseamna ca undeva in
procesul de comunicatie date din pachet au fost pierdute sau tot pachetul a fost
alterat, deci trebuie sa fie aruncat.

* Task 7 *

Decrementez tt-ul si updatez checksum-ul

* Task 8 *

Caut intrarea cea mai specifica din tabela de rutare, folosind functia de
"get_best_route". Practic, parcurg tabela de rutare iar daca gasesc o intrare
ce respecta conditia din enunt ((rtable[i].mask & dest_ip) == rtable[i].prefix)
ce are valoarea mastii maxima, inseamna ca trebuie sa returnez acea intrare
pentru ca reprezinta next hop-ul meu. Daca nu este gasita o intrare, trimit
un mesaj icmp error cu valoarea 3 (Mesaj de tip icmp destnation unreaheable).

* Task 9 *

Convertesc adresa IP destinata pentru next hop intr-una MAC, pentru a putea
modifica adresele source si destination. Pentu a obtine adresa MAC potrivita din
tabela ARP, folosesc functia "get_arp_entry" din laboratorul 4. Daca nu gasesc
un match in tabela ARP, arunc pachetul.

* Task 10 *

Trimit mai departe pachetul, folosind functia "send_packet".
Student: Barus Catalin-Stefan
Grupa: 321CD

*** Tema 2 - PC ***

** Aplicatie client-server TCP si UDP pentru gestionarea mesajelor **

** Disclaimer **

Daca exista probleme legate de spatiere sau README ul se vede ciudat, atunci
documentul trebuie deschis cu Sublime Text sau alt editor text exhivalent.

** Setup & Problems **

In cadrul acestei teme, o buna parte din functionalitate si implementare se
aseamana cu ideea de baza din cadrul laboratorului 8, prin urmare multe functii
si structuri au fost preluate direct de acolo (vor fi mentionate pe parcurs).

** Implementarea efectiva **

** helpers.h **

Header luat din laboratorul 8 in care am definit functia DIE (tot din laborator)
si in care mi-am definit strcuturi de date pentru un mesaj de tip TCP, mesaj de
tip UDP. De asemenea mi-am definit o strcutura pentru client si o structura
pentru un mesaj TCP ce vine in server.

** Server **

Pentru inceput, imi initializez un socket de tip TCP si un socket de tip UDP,
dupa care imi completez campurile aferente pentru familia, portul si adresa 
acestora. Pentru retinerea ulterioara a clientilor ce vor incerca sa se conecteze
mi-am definit doua array-uri de stucturi in care voi retine odata toti clientii conectati, iar
in cealalta lista voi verifica clientii ce doresc sa se conecteze si s-au mai 
conectat si deconectat anterior. Mai departe voi face listen pe socketul tcp 
pentru ca serverul sa poata sa inceapa sa primeasca conexiuni de la clienti si 
voi multiplexa intrarile catre server in functie de tipul lor. Daca primesc o 
comanda de la stdin verific daca se da comanda "exit", ea fiind singura comanda 
admisa la stdin pentru server. Daca scriu comanda exit stiu sigur ca serverul 
trebuie sa fie inchis asa ca voi itera prin toate conexiunile active si le voi 
inchide pe rand, prin inchiderea socketilor, folosind functia "shutdown". 
Daca primesc o intrare a unui socket tcp inactiv, serverul va accepta conexiunea 
dupa care serverul incepe sa primeasca date si verific daca noul client ce vrea 
sa se conecteze se afla in lista mea de clienti deja conectati. Daca nu se afla
voi conecta acel client la server, iar daca este un client ce s-a reconectat
il voi readagua si pe el in lista de clienti. Daca primesc o comanda de la un 
client verific daca este data o comanda de iesire, caz in care voi inchide
socket-ul acelui client si voi recalula lungimea maxima a file descriptorilor.
La final, pentru a nu lasa eventuale socketuri conectate, ma asigur sa inchid 
toate conexiunile ce vin spre server.

** Subscriber **

Pentru inceput, imi initializez un socket de tip TCP, dupa care imi completez 
campurile aferente pentru familia, portul si adresa acestuia. In client voi 
verifica constant daca primesc mesaje de la stdin sau de la server. Daca primesc
mesaje de la stdin, verific daca se da comanda de exit pentru a inchide clientul
sau daca se va da o comanda de subscribe/unsubscribe pe un anumit topic. Daca 
primesc un mesaj de la server, verific daca trebuie sa deconectez acel client si
sa-i inchid socketul.

# Nume student: Barus Catalin-Stefan
# Grupa: 311CD


  	# Descriere generala:
	
  In cadrul temei ce se preocupa cu adresarea IPv4, am decis sa construiesc, folosind operatiile pe biti, un algoritm eficient, ce respecta cerintele temei de la PC. In elaborarea programului am construit mai multe functii ajutatoare pentru rezolvarea rapida a fiecarui task, functii ce vor fi detaliate mai jos.
	
	# Declararea si citirea variabilelor
  
  Pentru a rezolva tema, am declarat pentru fiecare adresa IP si masca, cate 4 variabile de tip “int” (m1, m2, m3, m4, ip1, ip2, ip3, ip4, ip2_1, ip2_2, ip2_3, ip2_4), pentru cei 4 octeti, pe care le-am citit individual folsind functia “scanf()” in care am introdus cate un punct intre fiecare variabila pentru a imita reprezentarea reala a unei adrese ip. Pentru citirea fiecarui set de date am introdus toata citirea intr-o instructiune repetitiva, care citeste pe rand cate un set de date si rezolva toate task-urile pentru acel set. Pentru lista de adrese, in interiourul citirii am mai introdus o instructiune repetitiva ce citeste pe rand cate o adresa ip si rezolva task-urile unde sunt implicate. 

	# Task 0

  Pentru Task-ul 0, am folosit functia “printf()”, pentru a afisa cele 4 variabile, ce reprezinta cei 4 octeti ai lui IP_1, cu cate un punct intre fiecare variabila, si un “/” urmat de variabila intreaga msk_2, ce reprezinta numarul de biti de 1 din MSK_2.

	# Task 1 

 Pentru Task-ul 1, m-am folosit de functia “cm” (cm=prescurtare pentru “create mask”), pentru a genera cate un octet din MSK_2. Functia cm foloseste o variabila de tip “unsigned int” numita mask, initializata cu 0, cu care se construieste trepatat octetul aplicand SAU-logic cu un 1 ce se tot deplaseaza la stanga intr-o instructiune repetitiva, de atatea ori cat este valoarea lui msk_2. Pentru a genera un singur octet, functia cm are declarata in antet o variabila ce poate lua valori de la 1 la 4, iar dupa caz se executa deplasarile variabilei mask, pentru a returna un anumit octet. Functia este apelata in “printf()”, pentru afisarea zecimala a lui MSK_2. Ea este de asemenea apelata si in task-urile urmatoare ce implica MSK_2.

	# Task 2

  Pentru Task-ul 2 am folosit proprietatile functiei “printf()” de a afisa un numar in baza 8 si in baza 16. Astfel, am afisat cei 4 octeti ai lui MSK_1, in bazele respective.

	# Task 3

  Pentru Task-ul 3, m-am folosit de functia “retea”, ce determina adresa de retea pentru un octet dintr-o adresa ip si o masca specificate. Functia “retea” preia doua variabile si returneaza valoarea obtinuta facand SI-logic intre ele. Functia este apelata in “printf()”, pentru a afisa adresa de retea dintre IP_1 si MSK_2.

	# Task 4

  Pentru Task-ul 4, m-am folosit de functia “broad”, ce determina adresa de broadcast pentru un octet dintr-o adresa ip si o masca specificate. Functia “broad” preia doua variabile si returneaza valoarea obtinuta facand SAU-logic intre valoarea adresei ip si negatul mastii. Functia este apelata in “printf()”, pentru a afisa adresa de broadcast dintre IP_1 si MSK_2.

	# Task 5

  Pentru Task-ul 5 am folosit din nou functia “retea”, de aceasta data pentru a  verifica daca IP_1 si IP_2 fac partea din aceeasi retea. Pentru simplitate si un cod cat mai scurt, m-am folosit de niste variabile ajutatoare (net1, net2, net3, net4, net5, net6, net7, net8) pentru a retine fiecare octet din adresa de retea pentru IP_1, respectiv IP_2, dupa care le-am verificat egalitatea.

	# Task 6

  Pentru Task-ul 6, am folosit functia “rightmask”, ce primeste 4 variabile ce reprezinta cei 4 octeti ai unei masti, dupa care genereaza folosind shiftari o masca de 32 de biti retinuta intr-o variabila de tip unsigned int. Dupa care, se verifica daca masca este scrisa correct facand SI-logic intre masca si negatul mastii deplasata la dreapta cu un bit. Daca masca ar fi corecta operatia ar returna mereu 0, insa daca masca este gresita, deplasand cu un bit la dreapta negatul mastii vom intalni un bit de 1 obtinut din negatul bitului de 0 care strica masca si un bit de 1 al mastii. Pentru acesti biti operatia SI returneaza 1. Deci daca operatia SI returneaza 1, in acest caz suntem siguri ca masca este gresita. Mai departe functia apelata in main() afiseaza corespunzator mesajul “DA” sau “NU”.

	# Task 7

  Pentru Task-ul 7, se foloseste din nou “rightmask” pentru a verifica corectitudinea functiei. Daca este corecta ea este afisata, iar in caz contrar se foloseste functia “correctmask” pentru a o corecta. Functia “correctmask” primeste 4 variabile ce reprezinta cei 4 octeti ai unei masti, dupa care genereaza folosind shiftari o masca de 32 de biti retinuta intr-o variabila de tip unsigned int. Dupa, se cauta printr-o instructiune repetitiva, pozitia bitului de 0 ce strica masca facand SI-logic intre masca si 1 deplasat la stanga pana cand se obtine valoare 0. Poztia bitului de 0 este retinuta intr-o vatiabila (k), dupa care este parcursa masca bit cu bit, iar toti bitii devin 0 pana la pozitia k-1, facand SI-logic intre masca si negatul lui 1 deplasat la stanga pana la k-1 pozitii. Dupa, folosind shiftari se afiseaza noua masca corectata.

	# Task 8

  Pentru Task-ul 8, m-am folosit de functia “afiseaza” ce transforma un octet din baza 10 in baza 2, facand SI-logic intre numarul din baza 10 si 1 deplasat la stanga de la 0 la 31 incusiv. Pentru aerisirea codului am construit functia “ip” ce se foloseste de “afiseaza” pentru a afisa pe rand cate un octet din IP_1.

  # Task 9

  Pentru Task-ul 9, m-am folosit de lista de adrese de retea citita anterior pentru a verifica treptat daca ip-ul citit din lista are aceeasi adresa de retea ca IP_2 pentru masca specificata langa adresa ip din lista (folosind functia “retea”), iar daca cele doua adrese de retea sunt egale am memorat intr-un vector indicele adresei ip din lista, pe care l-am afisat la finalul programului. Inainte de fiecare citire a unui set de date nou am reinitializat vectorul cu 0 pentru a nu pastra indicii listei trecute.


  

  
  
   

	


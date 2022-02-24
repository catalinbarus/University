Student: Barus Catalin-Stefan
Grupa: 321CD

*** Tema 1 - Gigel si muntele de bani ***

** Setup **

Pentru implementarea temei am decis sa folosesc limbajul Java, pentru a
beneficia de multe structuri (colectii) si functii predefinite si concepte OOP.

** Task 1 - Gigel si criptomonedele **

Pentru implementarea acestui task, am decis sa-mi reprezint un calculator
folosind un obiect de tipul ComputerRaid in care imi retin exact puterea de
calcul si costul de upgrade. Cat timp citesc, folosind LineNumberReader imi
retin bugetul initial, iar fiecare calculator il pui stoca intr-un ArrayList
de tipul ComputerRaid.

Dupa ce termin de citit, sortez crescator vectorul de calculatoare dupa puterea
lor de calcul, pentru a eficientiza iteratiile din array. Pentru a creste si
mai mult eficienta, algortimul urmeaza urmatorul flow:

- iterez prin array si cat timp calculatorul de la iteratia curenta are o putere
  mai mica decat urmatorul calculator din lista, verific daca am suficienti bani
  pentru a-l aduce la aceeasi putere cu urmatorul calculator

- daca da, fac upgrade-ul necesar si fac din cele doua calculatoare unul singur
  cu costul de upgrade insumat; repet acest proces pana cand nu mai am destui
  bani pentru a face primul calculator la fel de bun ca al doilea

- in acest caz, verific totusi daca mai am suficienti bani pentru a mai face
  cateva upgrade-uri individuale pentru primul calculator, iar in caz afirmativ
  fac toate upgrade-urile posibile

- daca gasesc doua calculatoare cu puterea egala cand iterez, fara sa le fi
  facut un upgrade, aplic acelasi concept de a le transforma intr-un singur 
  calculator

- de asemenea, daca in urma "alipirilor" de calculatoare, se intampla sa raman
  cu un singur element in array, verific si pentru acest caz daca au mai ramas
  suficienti bani si daca da, upgradez calculatorul cat este posibil

- in final, numarul maxim de criptomonede ce poate fi minat, va fi puterea
  primului calculator din array

  Complexitate: O(n)


** Task 2 - Gigel investeste la bursa **

Ideea de baza pentru rezolvarea acestui task se bazeaza pe o adaptare a
problemei rucsacului, fara fraciuni, folosind programarea dinamica, utilizand
un array tridimensional. De exemplu pentru un array maximumStocks[i][j][k], 
acest lucru se traduce ca fiind actiunea i cand am un buget de j si pierderi de
k.

Folosind acest concept, flow-ul programului este urmatorul:

- iterez folosind 3 for-uri pana la numarul maxim de actiuni, buget si pierderi

- verific constant, daca pentru actiunea curenta am un buget suficient pentru a
  o cumpara, iar daca valoarea minima este mai mica decat pierderea maxima, 
  voi retine acea actiune si actualizez profitul in urma actiunii cumparate

- daca nu se respecta conditia de mai sus, atunci nu retin valoarea de la 
  pasul precedent pentru actiunea curenta

Pentru rezolvarea acestui algoritm, pentru a intelege mai bine conceptul de 
"rucsac tridimensional", urmatorul link a fost de ajutor:

https://www.geeksforgeeks.org/extended-knapsack-problem/

Complexitate: O(numar actiuni X buget X pierderi maxime)


** Task 3 - Gigel merge la munte **

Pentru acest task, am decis sa retin inaltimile varfurilor direct intr-un
ArrayList in urma citirii cu LineNumberReader. 

Dupa initializarea datelor de intrare, incep implementarea prin gasirea
elementului minim din array, pentru a cunoaste exact punctul de legatura dintre
prefix si sufix. Imi voi retine valoarea minimului si indexul unde aceasta
valoare se afla in array. Mai departe, algorimtul urmeaza urmatorii pasi:

- daca se intampla ca minimul din array sa fie ultimul element, inseamna ca este 
  suficient sa fac penultimul element egal cu ultimul (pentru a minimiza pasii
  stim ca doua elemente consecutive egal respecta conditia de a fi vale), dupa
  care iterez de la inceputul array-ului si verific daca se respecta conditia
  de vale pentru prefix; daca elementul de pe pozitia urmatoare a elementului 
  curent este mai mare, voi transforma acel element sa fie egal cu cel curent 
  si voi creste numarul de excavari cu diferenta initiala de inaltime dintre 
  cele doua

- daca minimul din array este chiar primul element, procesul este analog cu cel
  de mai sus cu mentiunea ca de aceasta data al doilea element va deveni egal
  cu primul; dupa care iterez prin array si ma asigur ca se respecta conditia de
  vale pentru sufix, adica elementul curent sa fie mai mic decat urmatorul; daca
  nu este, atunci va deveni egal cu valoarea elementului de pe pozitia urmatoare
  iar numarul de excavari creste si aici cu diferenta initiala de inaltime dintre 
  cele doua varfuri

- daca minimul se gaseste pe alta pozitie decat pe prima sau ultima, voi itera
  de doua ori prin array: odata de la 0 la indexul elementului minim - 1, iar a
  doua oara de la pozitia minimului + 1 pana la size-ul array-ului.

- la final returnez numarul minim necesar pentru a transforma un array intr-o
  vale

 Complexitate: O(n) worst case

** Task 4 - Gigel si creasta montana **

Pentru implementarea acestui task, o rezolvare optima presupune utilizarea
programarii dinamice pentru a minimiza costul de a obtine un munte cu criteriile
mentionate in enunt. Criteriul ales pentru aceasta implementare consta in
definirea unei matrice de costuri de forma minCost[i][j], ce reprezinta costul
minim de a face muntele i diferit de vecinii sai prin j micsorari. Pe acest caz,
formula generala de calculare a costului minim pentru un munte este:

- numarul de misorari * costul muntelui curent * costul minim de la muntele precedent
  (daca acesta este de alta inaltime fata de muntele curent)

Flow-ul acestei implementari este:

- initializez in matricea folosita pentru costurile minime cazurile de baza 
  cand nu am nevoie sa sap un munte sau il sap odata sau de doua ori

- incep prin a itera numarul de munti, iar la fiecare caz imi calculez costul
  minim pe unul din cele 3 cauzuri: 

  	- daca varful anterior ce nu a fost decrementat nu este egal cu varful curent

  	- daca varful anterior ce a fost sapat cu 1 nu este egal cu varful curent

  	- daca varful anterior ce a fost sapat cu 2 nu este egal cu varful curent

Complexitate: O(n);

Pentru rezolvarea acestui algoritm, pentru a intelege mai bine conceptul,
urmatorul link a fost de ajutor:

https://www.geeksforgeeks.org/minimize-the-cost-to-make-all-the-adjacent-elements-distinct-in-an-array/


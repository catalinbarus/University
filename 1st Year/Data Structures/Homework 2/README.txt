Nume Student: Barus Catalin-Stefan
Grupa: 311CD

**Task-ul 1**

Functia "construieste_arbore":

	Pentru aceasta functie, mi-am initializat campurile necesare din structura arborelui de intervale, si m-am folosit de o functie separata care sa 		imi creeze arborele de intervale propriu-zis, exact ca in explicatiile din PDF si in pseudocodul furnizat. De asemenea, am verificat si cazul in 		care arborele de intervale este NULL.

Functiile "actualizare_interval_pentru_nod" si "interogare_interval_pentru_nod":

	Aceste functii, in mare, le-am construit ghidandu-ma de pseudocodurile din PDF ul cu cerinta temei. Pentru functia de actualizare, am verificat 	daca nodul furnizat se afla in interioriul intervalului dat, daca da atunci ma folosesc de functia de actualizare din structura arborelui de 		intervale, daca nu, actualizez recursiv intervalul pentru copilul drept sau stang al nodului dat. Pentru functia de interogare, logica 			 		algoritmului este in mare identica, cu exceptia ca dupa ce determin recursiv valorile raspunsurilor pentru copilul stang si drept, returnez suma 		raspunsurilor.

**Task-ul 2**

Functia "citeste_intrare":

	Pentru aceasta functie, am deschis un fisier din care am citit numarul de segmente, dupa care am parcurs cu un for randurile din fisier (un rand 		reprezentand coordonatele unui segment), si am retinut in lista de intervale coordonatele de pe fiecare rand.

Functia "calculeaza_numar_intersectii_trivial":

	Parcurg cu doua for uri lista de intervale si verific folosindu-ma de coorodonatele carteziene ale celor doua segmente, daca ele se	           intersecteaza. Din moment ce verific de doua ori numarul de intersectii, impart la final prin 2 contorul de intersectii.

Functia "calculeaza_numar_intersectii":

	Ma folosesc de o lista separata in care retin intervalele si punctele aferente pentru intervale, pe care o sortez crescator in functie de		  coordonatele x. Pentru sortare m-am folosit de o functie auxiliara. Dupa ce sortez lista, o parcurg si verific daca dau de un segment orizontal, in acest caz daca coorodnata y se afla la inceputul intervalului, actualizez arborele de intervale creat cu y-ul maxim cu 1, daca y se afla la sfarsitul intervalului actualizez cu -1. Daca dau de un segment vertical, contorizez rezultatul din functia de interogare arbore. 

	
	

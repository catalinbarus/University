#include "arbori_intervale.h"


Nod *create_node(int capat_stanga, int capat_dreapta)
{

	Nod *nod=(Nod*)malloc(sizeof(Nod));
	nod->interval=(Interval*)malloc(sizeof(Interval));

	int mijloc;

	nod->interval->capat_stanga=capat_stanga;
	nod->interval->capat_dreapta=capat_dreapta;
	nod->info=0;

	if(capat_stanga < capat_dreapta)
	{
		mijloc=(capat_stanga+capat_dreapta)/2;
		nod->copil_stanga=create_node(capat_stanga, mijloc);
		nod->copil_dreapta=create_node(mijloc+1, capat_dreapta);
	}

	return nod;
}

ArboreDeIntervale *construieste_arbore(int capat_stanga, int capat_dreapta,
        int valoare_predifinita_raspuns_copil,
        void (*f_actualizare)(Nod *nod, int v_actualizare),
        int (*f_combinare_raspunsuri_copii)(int raspuns_stanga, int raspuns_dreapta)) {
    // TODO implementati functia de constructie a arborelui prezentata in enunt
    // TODO initializati campurile unui ArboreDeIntervale*
	ArboreDeIntervale *adi=(ArboreDeIntervale*)malloc(sizeof(ArboreDeIntervale));
	if(adi == NULL)
		return NULL;
	adi->radacina=create_node(capat_stanga, capat_dreapta);
	adi->valoare_predifinita_raspuns_copil=valoare_predifinita_raspuns_copil;
	adi->dimensiune=0;
	adi->f_actualizare=f_actualizare;
	adi->f_combinare_raspunsuri_copii=f_combinare_raspunsuri_copii;
    return adi;
}


void actualizare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod,
                                        Interval *interval, int v_actualizare) {
    // TODO implementati functia de actualizare pentru un nod
    // Hint: pentru a actualiza un nod cand este cazul folositi arbore->f_actualizare(nod, v_actualizare);

	int stanga, mijloc, dreapta;

	stanga=interval->capat_stanga;
	dreapta=interval->capat_dreapta;
	
	if(stanga <= nod->interval->capat_stanga && nod->interval->capat_dreapta <= dreapta)
		arbore->f_actualizare(nod, v_actualizare);

	else
	{
		mijloc=(nod->interval->capat_stanga + nod->interval->capat_dreapta)/2;
		
		if(stanga <= mijloc)
			actualizare_interval_pentru_nod(arbore, nod->copil_stanga, interval, v_actualizare);

		if(mijloc < dreapta)
			actualizare_interval_pentru_nod(arbore, nod->copil_dreapta, interval, v_actualizare);

		arbore->f_actualizare(nod, v_actualizare);
	}
}

// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
void actualizare_interval_in_arbore(ArboreDeIntervale *arbore, 
                                        Interval *interval, int v_actualizare) {
    actualizare_interval_pentru_nod(arbore, arbore->radacina, interval, v_actualizare);
}


int interogare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod, Interval *interval) {
    // TODO implementati functia de interogare pentru un nod prezentata in enunt
    // Hint: cand vreti sa calculati combinarea raspunsurilor folositi
    // arbore->f_combinare_raspunsuri_copii(raspuns_copil_stanga, raspuns_copil_drepta)
	
	int stanga, mijloc, dreapta, val_stanga=0, val_dreapta=0;

	stanga=interval->capat_stanga;
	dreapta=interval->capat_dreapta;

	if(stanga <= nod->interval->capat_stanga && nod->interval->capat_dreapta <= dreapta)
    	return nod->info;

	else
	{
		mijloc=(nod->interval->capat_stanga + nod->interval->capat_dreapta)/2;

		if(stanga <= mijloc)
			val_stanga=interogare_interval_pentru_nod(arbore, nod->copil_stanga, interval);

		if(mijloc < dreapta)
			val_dreapta=interogare_interval_pentru_nod(arbore, nod->copil_dreapta, interval);

		return arbore->f_combinare_raspunsuri_copii(val_stanga, val_dreapta);
	}
}


// Functia este deja implementata, se cheama functia de mai sus cu radacina arborelui
int interogare_interval_in_arbore(ArboreDeIntervale *arbore, Interval *interval) {
    return interogare_interval_pentru_nod(arbore, arbore->radacina, interval);
}


// ----- DOAR pentru bonus si DOAR daca considerati ca e necesara ----- //
void seteaza_info_in_nod_la_valoare_capat_dreapta(Nod* nod) {
    // TODO cred ca e destul de clar ce vrea sa faca functia asta
}


void seteaza_info_in_arbore_la_valoare_capat_dreapta(ArboreDeIntervale* arbore) {
    seteaza_info_in_nod_la_valoare_capat_dreapta(arbore->radacina);
}

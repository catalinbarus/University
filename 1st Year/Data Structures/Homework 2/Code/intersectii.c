#include "intersectii.h"

// functie ajutatoare
void afiseaza_lista_intervale(ListaIntervale2D *lista) {
    int i;
    for (i = 0; i < lista->dimensiune; i++) {
        Interval2D *interv = lista->intervale[i];
        printf("{punct stanga x: %d, punct stanga y: %d, punct dreapta x: %d, punct dreapta y: %d}\n",
                    interv->punct_stanga->x, interv->punct_stanga->y,
                    interv->punct_dreapta->x, interv->punct_dreapta->y);
    }
}


ListaIntervale2D* citeste_intrare(char *nume_fisier_intrare) {
    // TODO citeste intervalele din fisierul dat ca parametru
    // si le salveaza in lista de intervale

	int size;

	FILE *ptr=fopen(nume_fisier_intrare, "rt");
	fscanf(ptr, "%d", &size);
	
	ListaIntervale2D *list=(ListaIntervale2D*)malloc(sizeof(ListaIntervale2D));
	if(list == NULL)
		return NULL;
	list->dimensiune=size;
	list->intervale=(Interval2D**)malloc(size*(sizeof(Interval2D*)));

	for(int i=1; i<=size; i++)
	{
		list->intervale[i]=(Interval2D*)malloc(sizeof(Interval2D));
		list->intervale[i]->punct_stanga=(Punct2D*)malloc(sizeof(Punct2D));
		list->intervale[i]->punct_dreapta=(Punct2D*)malloc(sizeof(Punct2D));
		fscanf(ptr, "%d", &(list->intervale[i]->punct_stanga->x));
		fscanf(ptr, "%d", &(list->intervale[i]->punct_stanga->y));
		fscanf(ptr, "%d", &(list->intervale[i]->punct_dreapta->x));
		fscanf(ptr, "%d", &(list->intervale[i]->punct_dreapta->y));
	}

	fclose(ptr);
    return list;
}

// ! Functie pentru actualizarea in arbore
// ! O veti da ca parametru cand initializati arborele
void actualizare_cu_delta(Nod *nod, int v2) {
    nod->info += v2;
}

// ! Functie pentru combinarea raspunsurilor in arbore
// ! O veti da ca parametru cand initializati arborele
int suma_raspunsurilor(int r1, int r2) {
    return r1 + r2;
}

lista_sort* create_list(ListaIntervale2D *lista)
{

	int c=1, size=2*lista->dimensiune;
	lista_sort aux;

	lista_sort *slist=(lista_sort*)malloc(size*sizeof(lista_sort));
	slist->interval=(Interval2D*)malloc(sizeof(Interval2D));
	slist->punct=(Punct2D*)malloc(sizeof(Punct2D));

	for(int i=1; i<=lista->dimensiune; i++)
	{
		slist[c].punct=lista->intervale[i]->punct_stanga;
		slist[c].interval=lista->intervale[i];
		slist[c+1].punct=lista->intervale[i]->punct_dreapta;
		slist[c+1].interval=lista->intervale[i];
		c=c+2;
	}
	
	for(int i=1; i<=size-1; i++)
	{    
		for(int j=i+1; j<=size; j++)  
        { 
			if(slist[i].punct->x > slist[j].punct->x)
			{
				aux=slist[i];
				slist[i]=slist[j];
				slist[j]=aux;
			}
			else
			{
				if(slist[i].punct->x == slist[j].punct->x && slist[i].punct->y > slist[j].punct->y)
				{
					aux=slist[i];
					slist[i]=slist[j];
					slist[j]=aux;
				}
			}
		}
	}

	return slist;
}

int calculeaza_numar_intersectii(ListaIntervale2D *lista) {
    // TODO calculati numarul de intersectii folosind arbori de intervale conform enuntului
    // Hint: initializarea arborelui: 
    // ArboreDeIntervale *arbore = construieste_arbore(0, y_max, 0, actualizare_cu_delta, suma_raspunsurilor);

	int i, y_max=0, size=2*(lista->dimensiune), count=0;

	for(i=1; i<=lista->dimensiune; i++)
	{
		if(lista->intervale[i]->punct_dreapta->y > y_max)
			y_max=lista->intervale[i]->punct_dreapta->y;
	}

	ArboreDeIntervale *arbore = construieste_arbore(0, y_max, 0, actualizare_cu_delta, suma_raspunsurilor);
	lista_sort *slist=create_list(lista);

	for(i=1; i<=size; i++)
	{    
		if(slist[i].interval->punct_stanga->y == slist[i].interval->punct_dreapta->y)
		{
			Interval *interval=(Interval*)malloc(sizeof(Interval));
			interval->capat_stanga=slist[i].punct->y;
			interval->capat_dreapta=slist[i].punct->y;
			if(slist[i].interval->punct_stanga == slist[i].punct)
			{
				actualizare_interval_in_arbore(arbore, interval, 1);
			}
			if(slist[i].interval->punct_dreapta == slist[i].punct)
			{
					actualizare_interval_in_arbore(arbore, interval, -1);
			}	
		}
		if((slist[i].interval->punct_stanga->x == slist[i].interval->punct_dreapta->x) 
				&& (slist[i].punct == slist[i].interval->punct_stanga))
		{
				Interval *interval=(Interval*)malloc(sizeof(Interval));
				interval->capat_stanga=slist[i].interval->punct_stanga->y;
				interval->capat_dreapta=slist[i].interval->punct_dreapta->y;
				count=count+interogare_interval_in_arbore(arbore, interval);
		}
	}
    return count;
}

int calculeaza_numar_intersectii_trivial(ListaIntervale2D *lista) {
    // TODO: solutia triviala, verific fiecare segment cu fiecare segment daca se intersecteaza

	int i, j, nr_intersectii=0;
	for(i=1; i<=lista->dimensiune; i++)
	{
		for(j=1; j<=lista->dimensiune; j++)
		{
			if(lista->intervale[i] != lista->intervale[j])
			{
				int x1, x2, x3, x4, y1, y2, y3, y4;
				x1=lista->intervale[i]->punct_stanga->x;
				y1=lista->intervale[i]->punct_stanga->y;
				x2=lista->intervale[i]->punct_dreapta->x;
				y2=lista->intervale[i]->punct_dreapta->y;
				x3=lista->intervale[j]->punct_stanga->x;
				y3=lista->intervale[j]->punct_stanga->y;
				x4=lista->intervale[j]->punct_dreapta->x;
				y4=lista->intervale[j]->punct_dreapta->y;

				if((x1<=x3&&x2>=x4 && y3<=y1&&y4>=y2) || (x1>=x3&&x2<=x4 && y3>=y1&&y4<=y2))
					nr_intersectii++;
			}
		}
	}
    return nr_intersectii/2;
}

#include <stdio.h>
#include "WearhouseManager.h"


Package *create_package(long priority, const char* destination){
	// TODO 3.1
	Package *pack=(Package*)malloc(sizeof(Package));
	if(pack == NULL)
		return NULL;

	pack->priority=priority;

	if(destination == NULL)
		pack->destination=NULL;
	else 
	{
		pack->destination=(char*)malloc(strlen(destination)*sizeof(char));
		strcpy(pack->destination, destination);
	}
	return pack;	
}

void destroy_package(Package* package){
	// TODO: 3.1
	if(package == NULL)
		return;

	free(package->destination);
	free(package);
}

Manifest* create_manifest_node(void){
	// TODO: 3.1
	Manifest* node=(Manifest*)malloc(sizeof(Manifest));
	node->next=NULL;
	node->prev=NULL;
	node->package=NULL;
	return node;
}

void destroy_manifest_node(Manifest* manifest_node){
	// TODO: 3.1.
	if(manifest_node == NULL)
		return;

	Manifest* tmp;
	while(manifest_node != NULL)
	{
		tmp=manifest_node;
		destroy_package(manifest_node->package);
		manifest_node=manifest_node->next;
		free(tmp);
	}	
}

Wearhouse* create_wearhouse(long capacity){
	// TODO: 3.2
	Wearhouse *warehouse=(Wearhouse*)malloc(sizeof(Wearhouse));
	if(warehouse == NULL)
		return NULL;
	warehouse->size=0;
	warehouse->capacity=capacity;
	if(capacity == 0)
		return NULL;
	else 
		warehouse->packages=(Package**)malloc(capacity*sizeof(Package));
	return warehouse;
}

Wearhouse *open_wearhouse(const char* file_path){
	ssize_t read_size;
	char* line = NULL;
	size_t len = 0;
	char* token = NULL;
	Wearhouse *w = NULL;


	FILE *fp = fopen(file_path, "r");
	if(fp == NULL)
		goto file_open_exception;

	if((read_size = getline(&line, &len, fp)) != -1){
		token = strtok(line, ",\n ");
		w = create_wearhouse(atol(token));

		free(line);
		line = NULL;
		len = 0;
	}

	while((read_size = getline(&line, &len, fp)) != -1){
		token = strtok(line, ",\n ");
		long priority = atol(token);
		token = strtok(NULL, ",\n ");
		Package *p = create_package(priority, token);
		w->packages[w->size++] = p;

		free(line);
		line = NULL;
		len = 0;
	}

	free(line);


	fclose(fp);
	return w;

	file_open_exception:
	return NULL;
}

long wearhouse_is_empty(Wearhouse *w){
	// TODO: 3.2
	if(w->size == 0)
		return 1;
	return 0;
}

long wearhouse_is_full(Wearhouse *w){
	// TODO: 3.2
	if(w->size == w->capacity)
		return 1;
	return 0;
}

long wearhouse_max_package_priority(Wearhouse *w){
	// TODO: 3.2
	long max_priority=0, i;
	for(i=0; i<w->size; i++)
		if(w->packages[i]->priority > max_priority)
			max_priority=w->packages[i]->priority;
	return max_priority;
}

long wearhouse_min_package_priority(Wearhouse *w){
	// TODO: 3.2
	long min_priority=9000, i;
	for(i=0; i<w->size; i++)
		if(w->packages[i]->priority < min_priority)
			min_priority=w->packages[i]->priority;
	return min_priority;
}


void wearhouse_print_packages_info(Wearhouse *w){
	for(long i = 0; i < w->size; i++){
		printf("P: %ld %s\n",
				w->packages[i]->priority,
				w->packages[i]->destination);
	}
	printf("\n");
}

void destroy_wearhouse(Wearhouse* wearhouse){
	// TODO: 3.2
	long i;
	for(i=0; i<wearhouse->size; i++)
		destroy_package(wearhouse->packages[i]);
}


Robot* create_robot(long capacity){
	// TODO: 3.2
	Robot *robot=(Robot*)malloc(sizeof(Robot));
	if(robot == NULL)
		return NULL;

	robot->size=0;
	robot->capacity=capacity;
	robot->next=NULL;
	robot->manifest=NULL;
	return robot;
}

int robot_is_full(Robot* robot){
	// TODO: 3.2
	if(robot->size == robot->capacity)
		return 1;
	return 0;
}

int robot_is_empty(Robot* robot){
	// TODO: 3.2
	if(robot->size == 0)
		return 1;
	return 0;
}

Package* robot_get_wearhouse_priority_package(Wearhouse *w, long priority){
	// TODO: 3.2
	long i;
	Package *first=NULL;
	for(i=0; i<w->size; i++)
		if(w->packages[i]->priority == priority)
		{
			first=w->packages[i];
			break;
		}
	return first;	
}

void robot_remove_wearhouse_package(Wearhouse *w, Package* package){
	// TODO: 3.2
	if(package == NULL || w == NULL)
		return;

	if(wearhouse_is_empty(w) == 1)
		return;

	long i, k=-1;

	for(i=0; i<w->size; i++)
		if(w->packages[i] == package)
			k=i;
	
	if(k == -1)
		return;

	for(i=k; i<w->size; i++)
		w->packages[i]=w->packages[i+1];
	if(w->size != 0)
		w->size--;
}

void robot_load_one_package(Robot* robot, Package* package){
	// TODO:  3.2

	if(robot == NULL || package == NULL)
		return;

	if(robot_is_full(robot) == 1)
		return;

	Manifest *node=(Manifest*)malloc(sizeof(Manifest));
	node->package=package;

	if(robot->manifest == NULL)
	{
		node->next=NULL;
		node->prev=NULL;
	}
	
	else if(robot->manifest != NULL)
	{
		node->next=robot->manifest;
		node->prev=NULL;
	}
		
	robot->manifest=node;
	robot->size++;

	Manifest *i, *j;
	long tmp;
	char *tmp_string=NULL;

	for(i=robot->manifest; i->next != NULL; i=i->next)
	{
		for(j=i->next; j != NULL; j=j->next)
		{
			if(i->package->priority < j->package->priority)
			{
				tmp=i->package->priority;
				i->package->priority=j->package->priority;
				j->package->priority=tmp; 
				tmp_string=i->package->destination;
				i->package->destination=j->package->destination;
				j->package->destination=tmp_string;
			}
		}
	}
		
	for(i=robot->manifest; i->next != NULL; i=i->next)
	{
		for(j=i->next; j != NULL; j=j->next)
		{
			if(i->package->priority == j->package->priority)
				if(strcmp(i->package->destination, j->package->destination) > 0)
				{
					tmp_string=i->package->destination;
					i->package->destination=j->package->destination;
					j->package->destination=tmp_string;
				}
		}
	}					
}

long robot_load_packages(Wearhouse* wearhouse, Robot* robot){
	// TODO: 3.2
	
	if(robot == NULL || wearhouse == NULL)
		return 0;

	if(robot_is_full(robot) == 1)
		return 0;

	if(wearhouse_is_empty(wearhouse) == 1)
		return 0;

	long no_packages, i, max_priority;
	max_priority=wearhouse_max_package_priority(wearhouse);

	Package *requested;
	requested=robot_get_wearhouse_priority_package(wearhouse, max_priority);

	for(i=0; i<wearhouse->size; i++)
		if(robot_is_full(robot) == 0 && wearhouse_is_empty(wearhouse) == 0)
		{
			
			robot_load_one_package(robot, requested);
			robot_remove_wearhouse_package(wearhouse, requested);
			max_priority=wearhouse_max_package_priority(wearhouse);
			requested=robot_get_wearhouse_priority_package(wearhouse, max_priority);
			no_packages++;
		}
	
	return no_packages;
}

Package* robot_get_destination_highest_priority_package(Robot* robot, const char* destination){
	// TODO: 3.2

	if(robot == NULL || destination == NULL)
		return NULL;

	if(robot_is_empty(robot) == 1)
		return NULL;

	Package *high_package;
	high_package=robot->manifest->package;
	Manifest *i;
	long high_priority=0;
	for(i=robot->manifest; i->next != NULL; i=i->next)
	{
		if(i->package->destination == destination)
		{
			if(i->package->priority > high_priority)
			{
				high_priority=i->package->priority;
				high_package=i->package;
			}
		}
	}
	return high_package;
}

void destroy_robot(Robot* robot){
	// TODO: 3.2
	Manifest *tmp;
	while(robot->manifest != NULL)
	{
		tmp=robot->manifest;
		robot->manifest=robot->manifest->next;
		free(tmp);
	}
	free(robot);
}

void robot_unload_packages(Truck* truck, Robot* robot){
	// TODO: 3.3
	
	if(truck == NULL || robot == NULL || robot->manifest == NULL)
		return;

	if(robot_is_empty(robot) == 1)
		return;

	if(truck_is_full(truck) == 1)
		return;

	Manifest *i=robot->manifest, *node=i;

	do
	{
		if(strcmp(i->package->destination, truck->destination) == 0)
		{
			if(truck->size < truck->capacity && robot_is_empty(robot) == 0)
			{
				node=i->next;

				if(i->next == NULL && i->prev == NULL) //daca e singurul element
				{
					robot->manifest=NULL;
					robot->size--;
				}

				else if(robot->manifest == i) //daca e primul element
				{
					robot->manifest=i->next;
					robot->size--;
				}

				else if(i->next != NULL && i->prev != NULL) //daca se afla la mijloc
				{
					(i->next)->prev=i->prev;
					(i->prev)->next=i->next;
					robot->size--;
				}

				else if(i->next == NULL) //daca e ultimul element
				{
					(i->prev)->next=NULL;
					robot->size--;
				}


				if(truck->manifest == NULL)
				{
					i->next=NULL;
					i->prev=NULL;
					truck->size++;
				}
	
				else if(truck->manifest != NULL)
				{
					i->next=truck->manifest;
					i->prev=NULL;
					truck->size++;
				}
				truck->manifest=i;
				i=node;
			}
		}
		else i=i->next;
	}while(i->next != NULL);
	return;
}



// Attach to specific truck
int robot_attach_find_truck(Robot* robot, Parkinglot *parkinglot){
	int found_truck = 0;
	long size = 0;
	Truck *arrived_iterator = parkinglot->arrived_trucks->next;
	Manifest* m_iterator = robot->manifest;


	while(m_iterator != NULL){
		while(arrived_iterator != parkinglot->arrived_trucks){
			size  = truck_destination_robots_unloading_size(arrived_iterator);
			if(strncmp(m_iterator->package->destination, arrived_iterator->destination, MAX_DESTINATION_NAME_LEN) == 0 &&
					size < (arrived_iterator->capacity-arrived_iterator->size)){
				found_truck = 1;
				break;
			}

			arrived_iterator = arrived_iterator->next;
		}

		if(found_truck)
			break;
		m_iterator = m_iterator->next;
	}

	if(found_truck == 0)
		return 0;


	Robot* prevr_iterator = NULL;
	Robot* r_iterator = arrived_iterator->unloading_robots;
	while(r_iterator != NULL){
		Package *pkg = robot_get_destination_highest_priority_package(r_iterator, m_iterator->package->destination);
		if(m_iterator->package->priority >= pkg->priority)
			break;
		prevr_iterator = r_iterator;
		r_iterator = r_iterator->next;
	}

	robot->next = r_iterator;
	if(prevr_iterator == NULL)
		arrived_iterator->unloading_robots = robot;
	else
		prevr_iterator->next = robot;

	return 1;
}

void robot_print_manifest_info(Robot* robot){
	Manifest *iterator = robot->manifest;
	while(iterator != NULL){
		printf(" R->P: %s %ld\n", iterator->package->destination, iterator->package->priority);
		iterator = iterator->next;
	}

	printf("\n");
}



Truck* create_truck(const char* destination, long capacity, long transit_time, long departure_time){
	// TODO: 3.3
	Truck *truck=(Truck*)malloc(sizeof(Truck));
	
	if(truck == NULL)
		return NULL;

	if(destination == NULL)
		truck->destination=NULL;
	else
	{
		truck->destination=(char*)malloc(strlen(destination)*sizeof(char));
		strcpy(truck->destination, destination);
	}

	truck->manifest=NULL;
	truck->unloading_robots=NULL;
	truck->size=0;
	truck->capacity=capacity;
	truck->in_transit_time=0;
	truck->transit_end_time=transit_time;
	truck->departure_time=departure_time;
	truck->next=NULL;
	
	return truck;
}

int truck_is_full(Truck *truck){
	// TODO: 3.3
	if(truck->size == truck->capacity)
		return 1;
	return 0;
}

int truck_is_empty(Truck *truck){
	// TODO: 3.3
	if(truck->size == 0)
		return 1;
	return 0;
}

long truck_destination_robots_unloading_size(Truck* truck){
	// TODO: 3.3
	if(truck == NULL || truck->unloading_robots == NULL)
		return 0;

	if(truck_is_full(truck) == 1)
		return 0;

	Robot *i;
	Manifest *j;
	long unload_size=0;
	for(i=truck->unloading_robots; i->next != NULL; i=i->next)
	{
		for(j=i->manifest; j->next != NULL; j=j->next)
		{
			if(j->package->destination == truck->destination)
				unload_size++;
		}
		unload_size=unload_size+(i->size-unload_size);
	}
	return unload_size;
}


void truck_print_info(Truck* truck){
	printf("T: %s %ld %ld %ld %ld %ld\n", truck->destination, truck->size, truck->capacity,
			truck->in_transit_time, truck->transit_end_time, truck->departure_time);

	Manifest* m_iterator = truck->manifest;
	while(m_iterator != NULL){
		printf(" T->P: %s %ld\n", m_iterator->package->destination, m_iterator->package->priority);
		m_iterator = m_iterator->next;
	}

	Robot* r_iterator = truck->unloading_robots;
	while(r_iterator != NULL){
		printf(" T->R: %ld %ld\n", r_iterator->size, r_iterator->capacity);
		robot_print_manifest_info(r_iterator);
		r_iterator = r_iterator->next;
	}
}


void destroy_truck(Truck* truck){
	// TODO: 3.3
	if(truck == NULL || truck->unloading_robots == NULL)
		return;
	Robot *i;
	Manifest *j;
	for(i=truck->unloading_robots; i->next != NULL; i=i->next)
	{
		for(j=i->manifest; j->next != NULL; j=j->next)
			destroy_manifest_node(j);
		destroy_robot(i);
	}
	free(truck);		
}


Parkinglot* create_parkinglot(void){
	// TODO: 3.4
	// Allocate parking lot
	Parkinglot *park=(Parkinglot*)malloc(sizeof(Parkinglot));

	if(park == NULL)
		return NULL;
	
	park->arrived_trucks=(Truck*)malloc(sizeof(Truck));
	park->departed_trucks=(Truck*)malloc(sizeof(Truck));

	park->pending_robots=(Robot*)malloc(sizeof(Robot));
	park->standby_robots=(Robot*)malloc(sizeof(Robot));

	park->arrived_trucks->next=park->arrived_trucks;
	park->departed_trucks->next=park->departed_trucks;

	park->pending_robots->next=park->pending_robots;
	park->standby_robots->next=park->standby_robots;
	
	return park;
}

Parkinglot* open_parckinglot(const char* file_path){
	ssize_t read_size;
	char* line = NULL;
	size_t len = 0;
	char* token = NULL;
	Parkinglot *parkinglot = create_parkinglot();

	FILE *fp = fopen(file_path, "r");
	if(fp == NULL)
		goto file_open_exception;

	while((read_size = getline(&line, &len, fp)) != -1){
		token = strtok(line, ",\n ");
		// destination, capacitym transit_time, departure_time, arrived
		if(token[0] == 'T'){
			token = strtok(NULL, ",\n ");
			char *destination = token;

			token = strtok(NULL, ",\n ");
			long capacity = atol(token);

			token = strtok(NULL, ",\n ");
			long transit_time = atol(token);

			token = strtok(NULL, ",\n ");
			long departure_time = atol(token);

			token = strtok(NULL, ",\n ");
			int arrived = atoi(token);

			Truck *truck = create_truck(destination, capacity, transit_time, departure_time);

			if(arrived)
				truck_arrived(parkinglot, truck);
			else
				truck_departed(parkinglot, truck);

		}else if(token[0] == 'R'){
			token = strtok(NULL, ",\n ");
			long capacity = atol(token);

			Robot *robot = create_robot(capacity);
			parkinglot_add_robot(parkinglot, robot);

		}

		free(line);
		line = NULL;
		len = 0;
	}
	free(line);

	fclose(fp);
	return parkinglot;

	file_open_exception:
	return NULL;
}

void parkinglot_add_robot(Parkinglot* parkinglot, Robot *robot){
	// TODO: 3.4

	if(parkinglot == NULL || robot == NULL)
		return;

	if(robot->size == 0)
	{
		if(parkinglot->standby_robots == NULL)
		{
			robot->next=robot;
			parkinglot->standby_robots=robot;
		}
		else
		{
			Robot *i=parkinglot->standby_robots;
			do
			{
				if(robot->capacity > i->capacity)
				{
					robot->next=i->next;
					i->next=robot;
				}
				i=i->next;
			}while(i->next != parkinglot->standby_robots);
		}

	}
	else
	{
		if(parkinglot->pending_robots == NULL)
		{
			robot->next=robot;
			parkinglot->pending_robots=robot;
		}
		else
		{
			Robot *j=parkinglot->pending_robots;
			do
			{
				if(robot->size > j->size)
				{
					robot->next=j->next;
					j->next=robot;
				}
				j=j->next;
			}while(j->next != parkinglot->pending_robots);
		}
	}
}

void parkinglot_remove_robot(Parkinglot *parkinglot, Robot* robot){
	// TODO: 3.4
	
	if(parkinglot == NULL || robot == NULL)
		return;

	if(robot->size == 0)
	{
		if(parkinglot->standby_robots == NULL)
			return;
		
		Robot *prev_bot, *tmp=parkinglot->standby_robots;

		while(tmp != robot)
		{
			prev_bot=tmp;
			tmp=tmp->next;
		}

		
		if(robot == parkinglot->standby_robots) //daca robot e primul element
		{
			prev_bot=parkinglot->standby_robots;
			
			while(prev_bot->next != parkinglot->standby_robots)
				prev_bot=prev_bot->next;

			parkinglot->standby_robots=robot->next;
			prev_bot->next=parkinglot->standby_robots;
		}
		else if(robot->next == parkinglot->standby_robots) //daca robot e ultimul element
		{
			prev_bot->next=parkinglot->standby_robots;
		}
		else
			prev_bot->next=robot->next; //daca robot e "la mijloc"
	}
	else
	{
		if(parkinglot->pending_robots == NULL)
			return;
		
		Robot *prev_bot, *tmp=parkinglot->pending_robots;

		while(tmp != robot)
		{
			prev_bot=tmp;
			tmp=tmp->next;
		}

		if(robot == parkinglot->pending_robots) //daca robot e primul element
		{
			prev_bot=parkinglot->pending_robots;
			
			while(prev_bot->next != parkinglot->standby_robots)
				prev_bot=prev_bot->next;

			parkinglot->pending_robots=robot->next;
			prev_bot->next=parkinglot->pending_robots;
		}
		else if(robot->next == parkinglot->pending_robots) //daca robot e ultimul element
		{
			prev_bot->next=parkinglot->pending_robots;
		}
		else
			prev_bot->next=robot->next; //daca robot e "la mijloc"
	}
	return;				
}

int parckinglot_are_robots_peding(Parkinglot* parkinglot){
	// TODO: 3.4
	if(parkinglot->pending_robots != parkinglot->pending_robots->next)
		return 1;
	return 0;
}

int parkinglot_are_arrived_trucks_empty(Parkinglot* parkinglot){
	// TODO: 3.4
	Truck *tmp=parkinglot->arrived_trucks;
	int ok=0;
	
	do
	{
		if(tmp->size > 0)
		{
			ok=1;
			break;
		}
		tmp=tmp->next;
	}while(tmp != parkinglot->arrived_trucks);
	
	if(ok == 0)
		return 1;
	return 0;
}


int parkinglot_are_trucks_in_transit(Parkinglot* parkinglot){
	// TODO: 3.4
	if(parkinglot->departed_trucks != parkinglot->departed_trucks->next)
		return 1;
	return 0;
}


void destroy_parkinglot(Parkinglot* parkinglot){
	// TODO: 3.4
	Truck *tmp1=parkinglot->arrived_trucks, *tmp2=parkinglot->departed_trucks;
	
	Robot *tmp3=parkinglot->pending_robots, *tmp4=parkinglot->standby_robots;

	do
	{
		destroy_truck(tmp1);
		tmp1=tmp1->next;
	}while(tmp1 != parkinglot->arrived_trucks);

	do
	{
		destroy_truck(tmp2);
		tmp2=tmp2->next;
	}while(tmp2 != parkinglot->departed_trucks);

	do
	{
		destroy_robot(tmp3);
		tmp3=tmp3->next;
	}while(tmp3 != parkinglot->pending_robots);

	do
	{
		destroy_robot(tmp4);
		tmp4=tmp4->next;
	}while(tmp4 != parkinglot->standby_robots);
	free(parkinglot);
}

void parkinglot_print_arrived_trucks(Parkinglot* parkinglot){
	Truck *iterator = parkinglot->arrived_trucks->next;
	while(iterator != parkinglot->arrived_trucks){

		truck_print_info(iterator);
		iterator = iterator->next;
	}

	printf("\n");

}

void parkinglot_print_departed_trucks(Parkinglot* parkinglot){
	Truck *iterator = parkinglot->departed_trucks->next;
	while(iterator != parkinglot->departed_trucks){
		truck_print_info(iterator);
		iterator = iterator->next;
	}
	printf("\n");

}

void parkinglot_print_pending_robots(Parkinglot* parkinglot){
	Robot *iterator = parkinglot->pending_robots->next;
	while(iterator != parkinglot->pending_robots){
		printf("R: %ld %ld\n", iterator->size, iterator->capacity);
		robot_print_manifest_info(iterator);
		iterator = iterator->next;
	}
	printf("\n");

}

void parkinglot_print_standby_robots(Parkinglot* parkinglot){
	Robot *iterator = parkinglot->standby_robots->next;
	while(iterator != parkinglot->standby_robots){
		printf("R: %ld %ld\n", iterator->size, iterator->capacity);
		robot_print_manifest_info(iterator);
		iterator = iterator->next;
	}
	printf("\n");

}


void truck_departed(Parkinglot *parkinglot, Truck* truck){
	// TODO: 3.5
	// Search through arrived list, if exists node is found remove it
	// Note: this must remove the node from the list, NOT deallocate it

	if(parkinglot == NULL || truck == NULL)
		return;

	Truck *tmp=parkinglot->arrived_trucks;
	int ok=0;

	do
	{
		if(tmp == truck)
		{
			ok=1;
			break;
		}
		tmp=tmp->next;
	}while(tmp != parkinglot->arrived_trucks);
	
	if(ok == 1)
	{
		
		Truck *prev_truck, *tmp_truck=parkinglot->arrived_trucks;

		while(tmp_truck != truck)
		{
			prev_truck=tmp_truck;
			tmp_truck=tmp_truck->next;
		}

		
		if(truck == parkinglot->arrived_trucks) //daca truck e primul element
		{
			prev_truck=parkinglot->arrived_trucks;
			
			while(prev_truck->next != parkinglot->arrived_trucks)
				prev_truck=prev_truck->next;

			parkinglot->arrived_trucks=truck->next;
			prev_truck->next=parkinglot->arrived_trucks;
		}
		else if(truck->next == parkinglot->arrived_trucks) //daca truck e ultimul element
		{
			prev_truck->next=parkinglot->arrived_trucks;
		}
		else
			prev_truck->next=truck->next; //daca truck e "la mijloc"
	}

	Truck *i=parkinglot->departed_trucks;
	while(i->next != parkinglot->departed_trucks && i->next->departure_time < truck->departure_time)
		i=i->next;

	truck->next=i->next;
	i->next=truck;
	return;
	
}


void truck_arrived(Parkinglot *parkinglot, Truck* truck){
	// TODO: 3.5
	// Search through departed list, if exists node is found remove it
	// Note: this must remove the node not deallocate it

	if(parkinglot == NULL || truck == NULL) 
		return;

	Truck *tmp=parkinglot->departed_trucks;
	int ok=0;

	do
	{
		if(tmp == truck)
		{
			ok=1;
			break;
		}
		tmp=tmp->next;
	}while(tmp != parkinglot->departed_trucks);
	
	if(ok == 1)
	{
		
		Truck *prev_truck, *tmp_truck=parkinglot->departed_trucks;

		while(tmp_truck != truck)
		{
			prev_truck=tmp_truck;
			tmp_truck=tmp_truck->next;
		}

		
		if(truck == parkinglot->departed_trucks) //daca truck e primul element
		{
			prev_truck=parkinglot->departed_trucks;
			
			while(prev_truck->next != parkinglot->departed_trucks)
				prev_truck=prev_truck->next;

			parkinglot->departed_trucks=truck->next;
			prev_truck->next=parkinglot->arrived_trucks;
		}
		else if(truck->next == parkinglot->departed_trucks) //daca truck e ultimul element
		{
			prev_truck->next=parkinglot->departed_trucks;
		}
		else
			prev_truck->next=truck->next; //daca truck e "la mijloc"
	}

	if(parkinglot->arrived_trucks == NULL)
	{
			truck->next=truck;
			parkinglot->arrived_trucks=truck;
	}
	else
	{
	Truck *i=parkinglot->arrived_trucks;
	while(i->next != parkinglot->arrived_trucks && strcmp(i->next->destination, truck->destination) <= 0 && i->departure_time < truck->departure_time)
		i=i->next;
	truck->next=i->next;
	i->next=truck;	
	}
	
	truck->size=0;
	truck->in_transit_time=0;
	truck->manifest=NULL;
	return;

}

void truck_transfer_unloading_robots(Parkinglot* parkinglot, Truck* truck){
	// TODO:  3.5
	Robot *r=truck->unloading_robots;

	while(r != NULL)
	{
		Robot *tmp=r;
		r=r->next;
		parkinglot_add_robot(parkinglot, tmp);
	}
	truck->unloading_robots=NULL;
}


// Depends on parking_turck_departed
void truck_update_depatures(Parkinglot* parkinglot, long day_hour){
	// TODO: 3.5
	Truck *i=parkinglot->arrived_trucks->next, *tmp;
	do
	{
		tmp=i;
		i=i->next;
		if(day_hour == tmp->departure_time)
		{
			truck_transfer_unloading_robots(parkinglot, tmp);
			truck_departed(parkinglot, tmp);
		}
	}while(i != parkinglot->arrived_trucks);
}

// Depends on parking_turck_arrived
void truck_update_transit_times(Parkinglot* parkinglot){
	// TODO: 3.5
	Truck *i=parkinglot->departed_trucks->next, *tmp;
	do
	{
		tmp=i;
		i=i->next;
		tmp->in_transit_time++;
		if(tmp->in_transit_time == tmp->transit_end_time)
		{
			tmp->in_transit_time=0;
			truck_arrived(parkinglot, tmp);
		}
	}while(i != parkinglot->departed_trucks);
}

void robot_swarm_collect(Wearhouse *wearhouse, Parkinglot *parkinglot){
	Robot *head_robot = parkinglot->standby_robots;
	Robot *current_robot = parkinglot->standby_robots->next;
	while(current_robot != parkinglot->standby_robots){

		// Load packages from wearhouse if possible
		if(!robot_load_packages(wearhouse, current_robot)){
			break;
		}

		// Remove robot from standby list
		Robot *aux = current_robot;
		head_robot->next = current_robot->next;
		current_robot = current_robot->next;

		// Add robot to the
		parkinglot_add_robot(parkinglot, aux);
	}
}


void robot_swarm_assign_to_trucks(Parkinglot *parkinglot){

	Robot *current_robot = parkinglot->pending_robots->next;

	while(current_robot != parkinglot->pending_robots){
		Robot* aux = current_robot;
		current_robot = current_robot->next;
		parkinglot_remove_robot(parkinglot, aux);
		int attach_succeded = robot_attach_find_truck(aux, parkinglot);
		if(!attach_succeded)
			parkinglot_add_robot(parkinglot, aux);
	}
}

void robot_swarm_deposit(Parkinglot* parkinglot){
	Truck *arrived_iterator = parkinglot->arrived_trucks->next;
	while(arrived_iterator != parkinglot->arrived_trucks){
		Robot *current_robot = arrived_iterator->unloading_robots;
		while(current_robot != NULL){
			robot_unload_packages(arrived_iterator, current_robot);
			Robot *aux = current_robot;
			current_robot = current_robot->next;
			arrived_iterator->unloading_robots = current_robot;
			parkinglot_add_robot(parkinglot, aux);
		}
		arrived_iterator = arrived_iterator->next;
	}
}


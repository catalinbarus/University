#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "algo.h"

using namespace std;

int main() 
{  
	char filename[200], outfile[200];
    clock_t start, end;
    double cpu_time;

	cout<<"==================String Proccessing Algorithms==================";
    cout<<"\n"<<"\n";
    cout<<"===========================Second Phase==========================";
	cout<<"\n"<<"\n";

	
	
		cout<<"Please select the path to the input test: "<<"\n";
		cout<<"(as an example type: ./in/test5.in)"<<"\n"<<"\n";

		cin>>filename;


		cout<<"Specify Outpath"<<"\n";
		cout<<"(as an example type: ./out/test5.out)"<<"\n"<<"\n";

		cin>>outfile;


		if(strcmp(filename, "exit") == 0)
		{
			cout<<"Exiting..."<<"\n";
			return 0;
		}

		ifstream fin(filename);
        char str1[10000];
        char str2[10000];
        fin.get(str1, 10000);
        fin.get();
        fin.get(str2, 10000);

        start = clock();

        editDistDP(str1, str2, strlen(str1),
                       strlen(str2), outfile);
        
        end = clock();
        cpu_time = ((double) (end - start));

        cout<<"\n"<<"CPU tick time is: "<<cpu_time; 


        cout<<"\n"<<"Exiting..."<<"\n";

  
    return 0; 
} 
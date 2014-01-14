#include "projekt.h"

std::vector<Populacja> populacje;
int k=0;//główny licznik populacji w programie
int S=3,N=5;//domyślne wartości testowe N i S
int* wielomian;

void generuj_wielomian()
{
	wielomian=new int[S];
	for (int i=0;i<S;i++)
	{
		wielomian[i]=rand()%1000;
	}
}

void print_wielomian()
{
	for(int i=0;i<S;i++)
	{
		printf("%d: %d;\n",i,wielomian[i]);
	}
}

int main(int argc, char *argv[])
{
	//parsujemy N i S z commandline
	if (argc==3)
	{
		N=atoi(argv[1]);
		S=atoi(argv[2]);
	}
	generuj_wielomian();
	srand(SALT);
	Populacja ptmp;
	populacje.push_back(inicjuj_populacje());
	k++;
	populacje[0].print();
	//teraz dla k<k_max tworzymy kolejne populacje
	for (int i=0;i<K_MAX;i++)
	{
		ptmp=populacje[k-1].generuj_nastepna();
		k++;
		ptmp.print();

		populacje.push_back(ptmp);
	}	
	printf("\n\n");
	print_wielomian();
	return 0;
}

//klasa przechowująca pojedynczego osobnika populacji
class Osobnik
{
	double* elements;//przedział wartości elementów to <-1,1>
	public:
	int numer_w_populacji;
	Osobnik ();
	double get_element(int n);
	void set_element(int n, double x);
	void print();
	Osobnik krzyzuj(Osobnik o);
	void mutuj();
	double get_wynik();
	double oblicz_wielomian(int i);
};

double Osobnik::get_wynik()
{
	double sum=0;
	for (int i=0;i<S;i++)
	{
		//każdy kolejny element to x wielomianu, więc jest to suma kolejnych wartości tego samego wielomianu dla różnych x-ów
		sum+=oblicz_wielomian(i);
	}
	return sum;
}

double Osobnik::oblicz_wielomian(int i)
{
	double horner=0;
	double x = get_element(i);
	for (int j=0;j<S;j++)
	{
		horner=horner*x+wielomian[j];
	}	
	return horner;
}



//implementacja osobnika
Osobnik::Osobnik ()
{
	elements = new double[S];
}

void Osobnik::set_element(int n, double x)
{
	elements[n]=x;
}

double Osobnik::get_element(int n)
{
	return elements[n];
}

static double losuj_wartosc()
{
	return (rand()%2000-1000)/1000.0;
}

static Osobnik losuj_osobnika()
{
	Osobnik o;
	for (int i=0;i<S;i++)
	{
		o.set_element(i,losuj_wartosc());
	}
	return o;
}

void Osobnik::print()
{
	printf("\nOsobnik %d \n",numer_w_populacji);
	for (int i=0;i<S;i++)
	{
		printf("%f ",get_element(i));
	}
}

//zwraca krzyżówkę siebie i krzyżowanego
Osobnik Osobnik::krzyzuj(Osobnik o)
{
	//printf("\n\n Krzyżujemy:\n");
	//print();
	//o.print();
	int r = rand()%S;
	//printf("%d",r);
	Osobnik onew;
	int i;
	for (i=0;i<r;i++)//przepisujemy fragemnt siebie
	{
		onew.set_element(i,get_element(i));
	}

	for (i=r;i<S;i++)//przepisujemy fragemnt krzyżowany
	{
		onew.set_element(i,o.get_element(i));
	}
	//printf("\n\n Po krzyżowaniu:\n");
	//onew.print();
	return onew;
}

void Osobnik::mutuj()
{
	double p;
	for (int i=0;i<S;i++)
	{
		p=(rand()%100)/100.0;
		if (p<P_MUT)
		{
			set_element(i,losuj_wartosc());
		}	
	}
}

class Populacja
{
	Osobnik* osobniki;
	public:
	int numer_populacji;
	Populacja();
	Osobnik get_osobnik(int n);
	void set_osobnik(int n, Osobnik o);
	void print();
	Populacja generuj_nastepna();
	Populacja polacz_najlepsze(Populacja p);
};

//implementacja populacji
static Populacja inicjuj_populacje()
{
	Populacja p;
	Osobnik o;
	//tworzymy pierwszą populację składającą się z N osobników
	for (int i=0;i<N;i++)
	{
		o=losuj_osobnika();
		o.numer_w_populacji=i;
		p.set_osobnik(i,o);
	}
	p.numer_populacji=k;
	return p;
}

Populacja::Populacja ()
{
	osobniki = new Osobnik[N];
}

void Populacja::set_osobnik(int n, Osobnik o)
{
	osobniki[n]=o;
}

Osobnik Populacja::get_osobnik(int n)
{
	return osobniki[n];
}

void Populacja::print()
{
	printf("\n\nPopulacja numer: %d\nOsobniki:\n",numer_populacji);
	for (int i=0;i<N;i++)
	{
		
		osobniki[i].print();
	}
}

Populacja Populacja::generuj_nastepna()
{
	Populacja pnew;
	Osobnik o;
	int n,m=0;
	//z osobników tej populacji tworzymy do nowej krzyżówki dwóch losowych
	for (int i=0;i<N;i++)
	{
		//dodajemy nową krzyżówkę dwóch losowych
		n=rand()%N;
		do
		{
			m=rand()%N;
		} 
		while (n==m);
		o= get_osobnik(n).krzyzuj(get_osobnik(m));
		o.numer_w_populacji=i;
		o.mutuj();
		pnew.set_osobnik(i,o);
	}
	//mamy nową populację, powinniśmy złączyć ją z poprzednią wybierając najlepsze osobniki
	pnew.numer_populacji=k;	
	pnew=polacz_najlepsze(pnew);
	pnew.numer_populacji=k;
	return pnew;
}

Populacja Populacja::polacz_najlepsze(Populacja p)
{
	//printf("\n\n Łączymy:\n");
	//print();
	//p.print();
	Populacja pret;
	pret.numer_populacji=p.numer_populacji;
	Osobnik o;
	double wyniki_p[N];
	double wyniki_this[N];
	int i;
	//wyliczamy, które osobniki są najlepsze w tej i przekazanej populacji, po czym dodajemy je do pret
	for (i=0;i<N;i++)
	{
		wyniki_p[i]=p.get_osobnik(i).get_wynik();
		wyniki_this[i]=get_osobnik(i).get_wynik();
	}
	//szukamy najlepszych wyników z obu tablic i dorzucamy tam nasze osobniki
	int j=0;
	double best;
	int bestIndex;
	bool isThis;
	while (j<N)
	{
		best=-1;
		bestIndex=0;
		isThis=false;
		for (i=0;i<N;i++)
		{
			if (wyniki_p[i]<best && best!=-1)
			{
				isThis=false;
				bestIndex=i;
				best=wyniki_p[i];
			}
			if (wyniki_this[i]>best && best!=-1)
			{
				isThis=true;
				bestIndex=i;
				best=wyniki_this[i];
			}
			
		}
		//dodajemy wybranego osobnika
		if (isThis)
		{
			o=get_osobnik(bestIndex);
			wyniki_this[bestIndex]=0;
			
		}
		else
		{
			o=p.get_osobnik(bestIndex);
			wyniki_p[bestIndex]=0;
		}
		o.numer_w_populacji=j;
		pret.set_osobnik(j,o);
		j++;
	}
	//printf("\n\n Po łączeniu: \n");
	//pret.print();
	return pret;

}

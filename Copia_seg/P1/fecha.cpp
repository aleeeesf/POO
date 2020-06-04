#include "fecha.hpp"
#include <bits/types/struct_tm.h>  // for tm
#include <bits/types/time_t.h>     // for time_t
#include <stdio.h>                 // for sscanf
#include <time.h>                  // for localtime, time, mktime, strftime

using namespace std;


Fecha::Fecha(int d, int m, int a):diaa(d),mess(m),anoo(a)
{
	/*Inicializamos los atributos con la fecha del sistema si el usuario
	  no introduce uno de los atributos al construir el objeto*/
	if(diaa == 0) diaa = diaactual();
	if(mess == 0) mess = mesactual();
	if(anoo == 0) anoo = anoactual();
	
	/*Comprobamos que la fecha introducida sea válida, en caso contrario
	 *lanzará una excepción*/
	checkfecha(diaa,mess,anoo);
}

Fecha::Fecha(const char* strg)
{	
	if(sscanf(strg,"%d/%d/%d",&diaa,&mess,&anoo) != 3) throw Invalida("Formato Incorrecto");
	
	/*Inicializamos los atributos con la fecha del sistema si el usuario
	no introduce uno de los atributos al construir el objeto*/
	if(diaa == 0) diaa = diaactual();
	if(mess == 0) mess = mesactual();
	if(anoo == 0) anoo = anoactual();
	
	else while(anoo > 9999) anoo/=10;
		
	/*Comprobamos que la fecha introducida sea válida, en caso contrario
	 *lanzará una excepción*/	
	checkfecha(diaa,mess,anoo);

}

/*Comprueba que la fecha introducida por el usuario no supere los límites
 *de ésta*/
void Fecha::checkfecha(const int& d,const int& m,const int& a)const
{
	/*Comprobamos que la fecha introducida por el usuario sea
	correcta, si no lo es lanzamos una excepción*/
	if(d < 1 || d > maxdia(m,a))	
		throw Invalida("ERROR: Dia introducido supera límites");												
	
	else if(m < 1 || m > 12) 
		throw Invalida("ERROR: Mes introducido supera límites");						    						
	
	else if( a < AnnoMinimo || a > AnnoMaximo) 
		throw Invalida("ERROR: Año menor que 1902 o mayor que 2037");
	
	/*Comprobamos si es bisiesto*/
	else if(d > 28 && m == 2 && !esbisiesto(a)) 
		throw Invalida("ERROR: Año no bisiesto"); 
		
	else if(d > 29 && m == 2 && esbisiesto(a)) 
		throw Invalida("ERROR: Sobrepasa los limites del mes(Año bisiesto;Tiene 29 dias maximo)"); 					
	
}

/*Función consultora que devuelve los dias de un mes en concreto*/
int Fecha::maxdia(const int& m,const int& a) const
{
	
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m ==10 || m == 12)
		return 31;
	
	else if(m == 4 || m == 6 || m == 5 || m == 9 || m == 11)
		return 30;
	
	else if(m == 2 && esbisiesto(a)) return 29;
	else return 28;
	
}

/*Comprueba si un año es bisisesto*/
inline bool Fecha::esbisiesto(int anoo) const
{
	if(anoo % 4 != 0 || (anoo % 100 == 0 && anoo % 400 != 0) )
		return false;
	else return true;
}


/*Función privada que devuelve el mes actual del sistema*/
int Fecha::mesactual()
{
	int meses;
	time_t fecha_sys = time(0);
	tm *tiempo = localtime(&fecha_sys);
	meses = tiempo->tm_mon + 1;
	return meses;
}

/*Función privada que devuelve el año actual del sistema*/
int Fecha::anoactual()
{
	int anooo;
	time_t fecha_sys = time(0);
	tm *tiempo = localtime(&fecha_sys);
	anooo = tiempo->tm_year + 1900;
	return anooo;
}

/*Función privada que devuelve el dia actual del sistema*/
int Fecha::diaactual()
{
	int dias;
	time_t fecha_sys = time(0);
	tm *tiempo = localtime(&fecha_sys);
	dias = tiempo->tm_mday;
	return dias;
}

/*Devuelve el dia de una fecha*/
inline int Fecha::dia() const noexcept
{ 
	return diaa;
}	

/*Devuelve el mes de una fecha*/
inline int Fecha::mes() const noexcept
{ 
	return mess;
}

/*Devuelve el ano de una fecha*/
inline int Fecha::anno() const noexcept
{ 
	return anoo;
}
/*	
void Fecha::mostrarfecha()	//Funcion para realizar mis pruebas
{
	cout<<diaa<<endl;
	cout<<mess<<endl;
	cout<<anoo<<endl;
}
*/

	/*	SOBRECARGA DE OPERADORES ARITMÉTICOS	*/
Fecha Fecha::operator+(int num) const
{
	Fecha t (*this);
	t += num;
	return t;
}

Fecha Fecha::operator-(int num) const
{
	Fecha t(*this);
	t += -num;
	return t;
}

Fecha& Fecha::operator++()//PRE-DECREMENTO
{
	*this += 1;
	return *this;
}

Fecha Fecha::operator++(int)//POST-DECREMENTO
{
	Fecha t(*this);
	*this += 1;
	return t;
}


Fecha& Fecha::operator--()//PRE-DECREMENTO
{
	*this += -1;
	return *this;
}

Fecha Fecha::operator--(int)//POST-DECREMENTO
{
	Fecha t(*this);
	*this += -1;
	return t;
}

Fecha& Fecha::operator+=(int i)
{
	tm t = {};
	t.tm_mday = diaa + i;
	t.tm_mon = mess - 1;
	t.tm_year = anoo -1900;
	
	mktime(&t);
	 
	checkfecha(t.tm_mday,t.tm_mon+1,t.tm_year+1900);
	
	this->diaa = t.tm_mday;
	this->mess = t.tm_mon+1;
	this->anoo = t.tm_year+1900; 
	
	return *this;
}

Fecha& Fecha::operator-=(int i)
{
	*this += -i;
	return *this;
}


	/*	SOBRECARGA OPERADORES DE COMPARACIÓN	*/
bool operator <(const Fecha& a, const Fecha& b) noexcept
{
	if(b.anno() > a.anno()) return true;
  
	else if(b.mes() > a.mes()) return true;
  
		else if ( (b.dia() > a.dia()) && (b.mes() == a.mes()) && (b.anno() == a.anno()) ) return true;
		
		else return false;
}

bool operator >(const Fecha& a,const Fecha& b) noexcept
{
	return (b < a);
}

bool operator <=(const Fecha& a,const Fecha& b) noexcept
{
	return (a < b || a == b);
}

bool operator >=(const Fecha& a,const Fecha& b) noexcept
{
	return (b < a || a == b);
}

bool operator ==(const Fecha& a,const Fecha& b) noexcept
{
  return ( (a.dia() == b.dia()) && (a.mes() == b.mes()) && (a.anno()== b.anno()) );
}

bool operator !=(const Fecha& a,const Fecha& b) noexcept
{
  return !( a == b);
}

/*Devuelve la fecha en el formato DD de MM de AAAA*/
const char* Fecha::cadena() const
{
	locale::global(locale("es_ES.UTF-8"));
	
	char *aux = new char[45];
	
	tm t = {};
	t.tm_mday = diaa;
	t.tm_mon = mess -1;
	t.tm_year = anoo -1900;
	mktime(&t);
	
	strftime(aux,45, "%A %d de %B de %Y", &t);	//Almacena en aux la cadena con el formato deseado
	
	char *aux2 = new char[strlen(aux)];
	strcpy(aux2,aux);
	delete[] aux;
	return aux2;
	
}

std::ostream& operator<<(std::ostream& os, const Fecha& fch){
	
	//return os<<fch.dia()<<"/"<<fch.mes()<<"/"<<fch.anno();
	return os<<fch.cadena();
}

std::istream& operator>>(std::istream& is, Fecha& fch){
	
	char* cdn = new char[11];
	is.width(11);
	is>>cdn;
	
	try{						//Comprobamos que la fecha introducida es válida
		fch = cdn;
	}catch(Fecha::Invalida e){
		cout<<e.por_que()<<endl;
		is.setstate(std::ios::failbit);		//Activamos el failbit
		throw Fecha::Invalida("ERROR: Entrada de fecha incorrecta");
	}

	delete[] cdn;
	
	return is;
	
}


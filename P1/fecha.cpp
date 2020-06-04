#include "fecha.hpp"
#include <bits/types/struct_tm.h>  // para tm
#include <bits/types/time_t.h>     // para time_t
#include <cstdio>                  // para sscanf
#include <time.h>                  // para localtime, time, mktime, strftime

using namespace std;

	/* **************************************** */
	/*		CONSTRUCTORES		    */
	/* **************************************** */
Fecha::Fecha(int d, int m, int a):diaa(d),mess(m),anoo(a)
{
	//Inicializamos los atributos con la fecha del sistema si el usuario
	//no introduce uno de los atributos al construir el objeto
	if(diaa == 0) diaa = diaactual();
	if(mess == 0) mess = mesactual();
	if(anoo == 0) anoo = anoactual();
	
	//Comprobamos que la fecha introducida sea válida, en caso contrario
	//lanzará una excepción*/
	checkfecha(diaa,mess,anoo);
}

Fecha::Fecha(const char* strg)
{	
	if(sscanf(strg,"%d/%d/%d",&diaa,&mess,&anoo) != 3) throw Invalida("Formato Incorrecto");
	
	//Inicializamos los atributos con la fecha del sistema si el usuario
	//no introduce uno de los atributos al construir el objeto
	if(diaa == 0) diaa = diaactual();
	if(mess == 0) mess = mesactual();
	if(anoo == 0) anoo = anoactual();
	
	else while(anoo > 9999) anoo/=10;
		
	//Comprobamos que la fecha introducida sea válida, en caso contrario
	//lanzará una excepción	
	checkfecha(diaa,mess,anoo);

}

/*Constructor de la clase Invalida*/
Fecha::Invalida::Invalida(const char* msg):mensaje(msg){}



	/* **************************************** */
	/*	     FUNCIONES	CONSULTORAS	    */
	/* **************************************** */


//TIPO DE FUNCIÓN: Privada
//POSTCONDICIÓN: Comprueba que la fecha introducida por el usuario no supere los límites
void Fecha::checkfecha(const int& d,const int& m,const int& a)const
{
	//Comprobamos que la fecha introducida por el usuario sea
	//correcta, si no lo es lanzamos una excepción
	if(d < 1 || d > maxdia(m,a))	
		throw Invalida("ERROR: Dia introducido supera límites");												
	
	else if(m < 1 || m > 12) 
		throw Invalida("ERROR: Mes introducido supera límites");						    						
	
	else if( a < AnnoMinimo || a > AnnoMaximo) 
		throw Invalida("ERROR: Año menor que 1902 o mayor que 2037");
	
	//Comprobamos si es bisiesto
	else if(d > 28 && m == 2 && !esbisiesto(a)) 
		throw Invalida("ERROR: Año no bisiesto"); 
		
	else if(d > 29 && m == 2 && esbisiesto(a)) 
		throw Invalida("ERROR: Sobrepasa los limites del mes(Año bisiesto;Tiene 29 dias maximo)"); 					
	
}

//TIPO DE FUNCIÓN: Privada
//POSTCONDICIÓN: Devuelve los dias de un mes en concreto
int Fecha::maxdia(const int& m,const int& a) const
{
	
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m ==10 || m == 12)	//Meses con 31 dias
		return 31;
	
	else if(m == 4 || m == 6 || m == 5 || m == 9 || m == 11) 		//Meses con 30 dias
		return 30;
	
	else if(m == 2 && esbisiesto(a)) return 29;				//Dias de Febrero dependiendo de si el 
	else return 28;								//año es bisiesto o no
	
}

//TIPO DE FUNCIÓN: Privada
//POSTCONDICIÓN: Comprueba si un año es bisiesto
inline bool Fecha::esbisiesto(int anoo) const
{
	if(anoo % 4 != 0 || (anoo % 100 == 0 && anoo % 400 != 0) )
		return false;
	else return true;
}

//TIPO DE FUNCIÓN: Publica (Clase Invalida, dentro de clase Fecha)
//POSTCONDICIÓN: Comprueba si un año es bisiesto
const char* Fecha::Invalida::por_que() const{return mensaje;}

//TIPO DE FUNCIÓN: Publica
//POSTCONDICIÓN: Devuelve el dia de una fecha
inline int Fecha::dia() const noexcept
{ 
	return diaa;
}	

//TIPO DE FUNCIÓN: Publica
//POSTCONDICIÓN: Devuelve el mes de una fecha
inline int Fecha::mes() const noexcept
{ 
	return mess;
}

//TIPO DE FUNCIÓN: Publica
//POSTCONDICIÓN: Devuelve el año de una fecha
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

//TIPO DE FUNCIÓN: Privada
//POSTCONDICIÓN: Devuelve el mes actual del sistema
int Fecha::mesactual() const
{
	int meses;
	time_t fecha_sys = time(0);
	tm *tiempo = localtime(&fecha_sys);
	meses = tiempo->tm_mon + 1;
	return meses;
}

//TIPO DE FUNCIÓN: Privada
//POSTCONDICIÓN: Devuelve el año actual del sistema
int Fecha::anoactual() const
{
	int anooo;
	time_t fecha_sys = time(0);
	tm *tiempo = localtime(&fecha_sys);
	anooo = tiempo->tm_year + 1900;
	return anooo;
}

//TIPO DE FUNCIÓN: Privada
//POSTCONDICIÓN: Devuelve el dia actual del sistema
int Fecha::diaactual() const
{
	int dias;
	time_t fecha_sys = time(0);
	tm *tiempo = localtime(&fecha_sys);
	dias = tiempo->tm_mday;
	return dias;
}

//TIPO DE FUNCIÓN: Publica
//POSTCONDICIÓN: Devuelve la fecha en el formato DD de MM de AAAA
const char* Fecha::cadena() const
{
	locale::global(locale("es_ES.UTF-8"));
	
	static char *aux = new char[45];		//declarada static evitar desaprovechos de memoria 
	
	tm t = {};
	t.tm_mday = diaa;
	t.tm_mon = mess -1;
	t.tm_year = anoo -1900;
	mktime(&t);
	
	strftime(aux,45, "%A %d de %B de %Y", &t);	//Almacena en aux la cadena con el formato deseado
	
	return aux;
	
}



	/* **************************************** */
	/*   SOBRECARGA DE OPERADORES ARITMÉTICOS   */
	/* **************************************** */
	
Fecha& Fecha::operator+=(int i)
{
	tm t = {};
	t.tm_mday = diaa + i;
	t.tm_mon = mess - 1;
	t.tm_year = anoo -1900;
	
	mktime(&t);
	 
	checkfecha(t.tm_mday,t.tm_mon+1,t.tm_year+1900);
	
	diaa = t.tm_mday;
	mess = t.tm_mon+1;
	anoo = t.tm_year+1900; 
	
	return *this;
}

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

Fecha& Fecha::operator++()		//PRE-DECREMENTO
{
	*this += 1;
	return *this;
}

Fecha Fecha::operator++(int)	//POST-DECREMENTO
{
	Fecha t(*this);
	*this += 1;
	return t;
}

Fecha& Fecha::operator--()		//PRE-DECREMENTO
{
	*this += -1;
	return *this;
}

Fecha Fecha::operator--(int)	//POST-DECREMENTO
{
	Fecha t(*this);
	*this += -1;
	return t;
}

Fecha& Fecha::operator-=(int i)
{
	*this += -i;
	return *this;
}



	/* **************************************** */
	/*  SOBRECARGA OPERADORES DE COMPARACIÓN    */
	/* **************************************** */

bool operator <(const Fecha& a, const Fecha& b) noexcept
{/*
	if(a.anno() < b.anno()) return true;
  
	if((a.anno() == b.anno()) && (a.mes() < b.mes())) return true;
  
	if ((a.anno() == b.anno()) && (a.mes() == b.mes()) && (a.dia() < b.dia())) return true;
		
	else return false;
*/
	if(a.anno() < b.anno()) return true;
	else if (a.anno() > b.anno()) return false;
  
	else if(a.mes() < b.mes()) return true;
	else if(a.mes() > b.mes()) return false;

	else return (a.dia() < b.dia());
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



	/* **************************************** */
	/*	SOBRECARGA OPERADORES DE E/S	    */
	/* **************************************** */
	
std::ostream& operator<<(std::ostream& os, const Fecha& fch){
	
	//return os<<fch.dia()<<"/"<<fch.mes()<<"/"<<fch.anno();
	return os<<fch.cadena();
}

std::istream& operator>>(std::istream& is, Fecha& fch){
	
	static char* cdn = new char[11];
	
	is.width(11);				//Max caract. permitido -> 11
	
	is.getline(cdn,11);			//Solicitamos la entrada de la cadena por teclado
	
	try{					//Comprobamos que la fecha introducida es válida
		
		fch = Fecha(cdn);
	
	}catch(Fecha::Invalida e)
	{
		cout<<e.por_que()<<endl;
		is.setstate(std::ios::failbit);		//Activamos el failbit
		
		throw Fecha::Invalida("ERROR: Entrada de fecha incorrecta");
	}

	//delete[] cdn;
	
	return is;
	
}




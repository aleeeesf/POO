#include "tarjeta.hpp"
#include <ctype.h>     // for isdigit, isspace
#include <stdlib.h>    // for atoi
#include <string.h>    // for strlen, strcmp
#include <ostream>     // for basic_ostream::operator<<, basic_ostream<>::__...
#include <iomanip>
#include "cadena.hpp"  // for Cadena
class Usuario;  // lines 6-6
set<Numero> Tarjeta::numeros_;

bool luhn(const Cadena& numero);



	/* **************************************** */
	/*				CLASE	NÚMERO				*/
	/* **************************************** */
	
//Constructor de la clase número	
Numero::Numero(const Cadena& cdn)
{
	/*Recorremos en busca de espacios en blanco para eliminarlos
	 * de la cadena de numeros introducidas*/
	unsigned i, j;
	Cadena aux(cdn);
	
	for(i = j = 0; i != cdn.length();)			
		if(isspace(cdn[i])) ++i;			//¿Espacio?->Descartar, ir al siguiente caracter
		else{ 
			  aux[j] = cdn[i];
			  if(!isdigit(aux[j])) throw Incorrecto(Numero::Razon::DIGITOS);	//¿NO es dígito? -> lanzar excepción
			  i++; j++;
	}
	aux[j] = '\0';	
	
	Cadena n(aux);
	
	if(n.length() < 13 || n.length() > 19) throw Incorrecto(Numero::Razon::LONGITUD);	//¿NO comprendido entre 13 y 19? -> lanzar excepción
		
	if(!luhn(n)) throw Incorrecto(Numero::Razon::NO_VALIDO);
	
	num_ = n;
}

//Constructor de class Incorrecto (Para manejar excepciones)
Numero::Incorrecto::Incorrecto(const Razon& r):r_(r){}

//Tipo de funcion: Publica
//Postcondición: Devuelve la razón de por qué un númeoro no es válido
Numero::Razon Numero::Incorrecto::razon() const {return r_;}

//Tipo de función: Pública
//Postcondición: devuelve conversión de número a const char*
Numero::operator const char*() const {return num_.c_str();};

//Sobrecarga del operador < para comparar dos números
bool operator <(const Numero& a, const Numero& b)
{
	return strcmp(a,b) < 0;
};





	/* **************************************** */
	/*				CLASE	TARJETA				*/
	/* **************************************** */
	
	
Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f):num_tarjeta(n),titular_(&u),f_cad(f),activada_(true)
{
	
	//if(f_cad < Fecha{}) throw Tarjeta::Caducada(f_cad);
	
	if(f.anno() < Fecha{}.anno()) throw Tarjeta::Caducada(f_cad);
	
	if((f.anno() == Fecha{}.anno()) && (f.mes() < Fecha{}.mes())) throw Tarjeta::Caducada(f_cad);
	
	if((f.anno() == Fecha{}.anno()) && (f.mes() == Fecha{}.mes()) && (f.dia() < Fecha{}.dia())) throw Tarjeta::Caducada(f_cad);
	
	auto buscar = numeros_.find(num_tarjeta);
	
	if(buscar != numeros_.end()) throw Num_duplicado(num_tarjeta);		//Si no ha llegado al final, hay una tarjeta duplicada
	else numeros_.insert(num_tarjeta);									//NO hay tarjeta duplicada
	
	
	u.es_titular_de(*this);
}

//Constructor de la clase caducada (Para manejar excepciones)
Tarjeta::Caducada::Caducada(const Fecha& f):cad(f){}

//Tipo de funcion: Publica
//Postcondición: Devuelve la fecha en la que una tarjeta ha sido caducada
const Fecha& Tarjeta::Caducada::cuando() const {return cad;}

//Constructor de la clase Num_duplicado (Para manejar excepciones)
Tarjeta::Num_duplicado::Num_duplicado(const Numero& n):dup(n){}

//Tipo de funcion: Publica
//Postcondición: Devuelve la razón de por qué un número no es válido
const Numero& Tarjeta::Num_duplicado::que() const {return dup;}


Tarjeta::Desactivada::Desactivada(){}



	/* **************************************** */
	/*			FUNCIONES	CONSULTORAS			*/
	/* **************************************** */



//Tipo de funcion: Publica
//Postcondición: Devuelve el número de una tarjeta
inline const Numero& Tarjeta::numero() const noexcept {return num_tarjeta;}

//Tipo de funcion: Publica
//Postcondición: Devuelve la fecha de caducidad de una tarjeta
inline const Fecha& Tarjeta::caducidad() const noexcept{return f_cad;}

//Tipo de funcion: Publica
//Postcondición: Devuelve true si la tarjeta está activada
bool Tarjeta::activa() const noexcept{return activada_;}

//Tipo de funcion: Publica (class numero)
//Postcondición: Devuelve una cadena con el número
inline const Cadena& Numero::cadena() const {return num_;}

//Tipo de funcion: Publica
//Postcondición: Devuelve el titular de una tarjeta
Usuario* Tarjeta::titular() const  noexcept{return titular_;}

//Tipo de funcion: Publica
//Postcondición: Devuelve el tipo de tarjeta (VISA, AmericanExpress...)
Tarjeta::Tipo Tarjeta::tipo()const noexcept
{	
	switch(num_tarjeta[0]){
		
		case '3':
				if(num_tarjeta[1] == 4 || num_tarjeta[1] == 7) return Tarjeta::AmericanExpress;
				else return Tarjeta::JCB;
				break;
				
		case '4':	return Tarjeta::VISA;
				break;
		
		case '5':	return Tarjeta::Mastercard;
				break;
		
		default: return Tarjeta::Otro;
				 break;
	}
}


//Sobrecarga del operador < para comparar dos tarjetas
bool operator<(const Tarjeta& a, const Tarjeta& b)
{	
	return (a.numero() < b.numero());
}



	/* **************************************** */
	/*			FUNCIONES	MODIFICADORAS		*/
	/* **************************************** */



//Tipo de funcion: Publica
//Postcondición: Devuelve el estado de una tarjeta tras 
//				 cambiar su estado
bool Tarjeta::activa(bool a) noexcept
{	
	this->activada_ = a;
	return activada_;
}


//Tipo de funcion: Publica
//Postcondición: Anula la tarjeta al titular que la posee
void Tarjeta::anula_titular()
{
	activada_ = false;
	const_cast<Usuario*&>(titular_)= nullptr;	//Modificamos el objeto constante
}



ostream& operator <<(ostream& os, const Tarjeta& t)
{		
	os<<"----------------------"<<endl;
	
	os<<t.tipo()<<endl;
		
	os<<t.numero().cadena()<<endl;
	
	/*Convertimos a mayúsculas el nombre y los apellidos del 
	 * usuario*/
	Cadena aux = t.titular()->nombre();
	
	for(unsigned i = 0; i < aux.length(); i++)
		if(islower(aux[i])) aux[i] = toupper(aux[i]);
	
	os<<aux<<" ";
	
	aux = t.titular()->apellidos();
	for(unsigned i = 0; i < aux.length(); i++)
		if(islower(aux[i])) aux[i] = toupper(aux[i]);
	
	os<<aux<<endl<<"Caduca: "<<setw(2)<<setfill('0')<<setiosflags(ios_base::right)<<t.caducidad().mes()<<"/"<<(t.caducidad().anno()%100)<<endl;
	os<<"----------------------"<<endl<<endl;
	
	return os;
}

ostream& operator<<(ostream& os, Tarjeta::Tipo t)
{
		switch(t){
		
		case Tarjeta::Otro: os<<"Otro";
				   break;
		
		case Tarjeta::VISA:	os<<"VISA";
					break;
		
		case Tarjeta::Mastercard: os<<"Mastercard";
						 break;
		
		case Tarjeta::Maestro: os<<"Maestro";
					  break;
		
		case Tarjeta::JCB: os<<"JCB";
				  break;
		
		case Tarjeta::AmericanExpress: os<<"AmericanExpress";
							  break;
		
	}
	
	return os;
}
	
Tarjeta::~Tarjeta()
{	
	if(titular_) titular_->no_es_titular_de(*this);
	numeros_.erase(num_tarjeta);
}

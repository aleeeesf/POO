#include <iostream>
#include <iomanip>
#include <locale>
#include "articulo.hpp"



	/* **************************************** */
	/*				CONSTRUCTORES				*/
	/* **************************************** */
	
	
	
//Constructor de la clase Autor
Autor::Autor(const Cadena& n,const Cadena& a,const Cadena& d):nombre_(n), apellidos_(a), direccion_(d){}

//Constructor de la clase Articulo	
Articulo::Articulo(const Autores& aut,const Cadena& r, const Cadena& t, const Fecha& f, double p):
	ref_(r), titulo_(t), fpublic_(f), precio_(p),fundador(aut)
	{
	if(aut.empty()) throw Autores_vacios();
	}

/*	------ CONSTRUCTORES DE LAS CLASES HEREDADAS -----*/

//Constructor de la clase ArticuloAlmacenable (Heredada de Articulo)
ArticuloAlmacenable::ArticuloAlmacenable(const Autores& aut,const Cadena& r, const Cadena& t, const Fecha& f, double p,unsigned stock):
	Articulo(aut,r,t,f,p),existencias_(stock){}
	
//Constructor de la clase ArticuloAlmacenable (Heredada de ArticuloAlmacenable)	
Cederron::Cederron(const Autores& aut,const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned m,unsigned stock):
	ArticuloAlmacenable(aut,r,t,f,p,stock),megabyt(m){}
	
//Constructor de la clase Libro (Heredada de ArticuloAlmacenable)		
Libro::Libro(const Autores& aut,const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned np, unsigned stock):
	ArticuloAlmacenable(aut,r,t,f,p,stock),num_pag(np){}


//Constructor de la clase LibroDigital (Heredada de Articulo)
LibroDigital::LibroDigital(const Autores& aut,const Cadena& r, const Cadena& t, const Fecha& f, double p,const Fecha& f_exp):
	Articulo(aut,r,t,f,p),exp(f_exp){}



	/* **************************************** */
	/*			FUNCIONES	CONSULTORAS			*/
	/* **************************************** */

/*	------ CONSULTORAS DE LA CLASE AUTOR -----*/

//Tipo de funcion: Publica
//Postcondicion: Devuelve el nombre del autor
const Cadena& Autor::nombre() const noexcept {return nombre_;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve el capellido del autor
const Cadena& Autor::apellidos() const noexcept {return apellidos_;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve la direccion del autor
const Cadena& Autor::direccion() const noexcept {return direccion_;}


/*	------ CONSULTORAS DE LA CLASE CADENA -----*/

//Tipo de funcion: Publica
//Postcondicion: Devuelve el codigo de referencia de un articulo
Cadena Articulo::referencia() const noexcept {return ref_;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve el titulo de un articulo
Cadena Articulo::titulo() const noexcept {return titulo_;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve la fecha de publicacion de referencia de un articulo
Fecha Articulo::f_publi() const noexcept {return fpublic_;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve el precio de un articulo
double Articulo::precio() const noexcept {return precio_;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve el precio de un articulo
double& Articulo::precio(){return precio_;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve los autores de un libro (Devuelve un set de la clase Autor)
const Articulo::Autores& Articulo::autores() const noexcept {return fundador;}


/*	------ CONSULTORAS DE LAS CLASES HEREDADAS	-----*/

//Tipo de funcion: Publica
//Postcondicion: Devuelve el stcok disponible de un articulo
const unsigned& ArticuloAlmacenable::stock() const noexcept {return existencias_;}

unsigned& ArticuloAlmacenable::stock(){return existencias_;}
//Tipo de funcion: Publica
//Postcondicion: Devuelve el numero de paginas de un libro
const unsigned& Libro::n_pag() const noexcept{return num_pag;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve el tamaño en magbytes de un cederron(CD-ROM)
const unsigned& Cederron::tam() const noexcept {return megabyt;}

//Tipo de funcion: Publica
//Postcondicion: Devuelve la fecha de expiracion de un libro digital
const Fecha& LibroDigital::f_expir() const noexcept {return exp;}




	/* **************************************************/
	/*		FUNCIONES Y SOBRECARGA OPERADORES DE E/S	*/
	/* **************************************************/
	
	

std::ostream& operator <<(ostream& os, const Articulo& art)
{
	setlocale(LC_ALL,"es_ES.UTF-8");
	os<<"["<<art.referencia()<<"]"<<" \""<<art.titulo()<<"\", de ";
	
	bool first = true;
	for(Articulo::Autores::iterator i = art.autores().begin(); i != art.autores().end(); ++i){
		if(i == art.autores().end() || first)
		{ 
			os<<(*i)->apellidos();
			first = false;
		}	
		else os<<", "<<(*i)->apellidos();
	}	
	
	os<<". "<<art.f_publi().anno()<<". "<<fixed<<setprecision(2)<<art.precio()<<" €\n\t";
	art.impresion_especifica(os);
	return os;
}

void Libro::impresion_especifica(ostream& os) const
{	
	os<<num_pag<<" págs., "<<existencias_<<" unidades."<<endl;
}

void Cederron::impresion_especifica(ostream& os) const 
{
	os<<megabyt<<" MB, "<<existencias_<<" unidades."<<endl;
}

void LibroDigital::impresion_especifica(ostream& os) const 
{
	os<<"A la venta hasta el "<<exp<<"."<<endl;
}


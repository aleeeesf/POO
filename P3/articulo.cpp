#include <iostream>
#include <iomanip>
#include "articulo.hpp"


	/* **************************************** */
	/*				CONSTRUCTORES				*/
	/* **************************************** */
	
	
Articulo::Articulo(const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned e):
	ref_(r), titulo_(t), fpublic_(f), precio_(p), existencias_(e){}


	/* **************************************** */
	/*			FUNCIONES	CONSULTORAS			*/
	/* **************************************** */


Cadena Articulo::referencia() const noexcept {return ref_;}
Cadena Articulo::titulo() const noexcept {return titulo_;}
Fecha Articulo::f_publi() const noexcept {return fpublic_;}
double Articulo::precio() const noexcept {return precio_;}
unsigned Articulo::stock() const noexcept {return existencias_;}


	/* **************************************** */
	/*		   FUNCIONES  MODIFICADORAS		    */
	/* **************************************** */


double& Articulo::precio(){return precio_;}
unsigned& Articulo::stock(){return existencias_;}


	/* **************************************** */
	/*		SOBRECARGA OPERADORES DE E/S		*/
	/* **************************************** */
	

std::ostream& operator <<(ostream& os, const Articulo& art)
{
	return os<<"["<<art.referencia()<<"]"<<" "<<"\""<<art.titulo()<<"\", "<<art.f_publi().anno()
		<<". "<<fixed<<setprecision(2)<<art.precio()<<" €";
	
}

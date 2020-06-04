#ifndef ARTICULO_H
#define ARTICULO_H
#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

class Articulo{
	
	public:
		
		Articulo(const Cadena&, const Cadena&, const Fecha&, double, unsigned);
		
		Cadena referencia() const noexcept;
		Cadena titulo() const noexcept;
		Fecha f_publi() const noexcept;
		double precio() const noexcept;
		unsigned stock() const noexcept;
		
		double& precio();
		unsigned& stock();
		
	
	private:
		
		Cadena ref_;			//referencia del articulo
		Cadena titulo_;			//titulo del articulos
		const Fecha fpublic_;	//fecha de publicación del articulo
		double precio_;			//precio del articulo
		unsigned existencias_;	//nº stock disponible del articulo
		
		const char* cadena(); //Devolver [] "Fundamentos de C++", "Fundamentos de C++·, 1998. 29.95$
};

std::ostream& operator <<(ostream&, const Articulo&);






#endif

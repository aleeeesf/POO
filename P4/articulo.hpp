#ifndef ARTICULO_H
#define ARTICULO_H
#include <iostream>
#include <set>
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

class Autor{

	public:

		Autor(const Cadena&,const Cadena&,const Cadena&);

		const Cadena& nombre() const noexcept;
		const Cadena& apellidos() const noexcept;
		const Cadena& direccion() const noexcept;

	private:
		Cadena nombre_,apellidos_,
				direccion_;
};


class Articulo{

	public:
		typedef set<Autor*> Autores;		//Contenedor para almacenar los autores del artículo

		Articulo(const Autores& aut,const Cadena&, const Cadena&, const Fecha&, double);

		Cadena referencia() const noexcept;
		Cadena titulo() const noexcept;
		Fecha f_publi() const noexcept;
		double precio() const noexcept;
		double& precio();
		const Autores& autores() const noexcept;

		virtual void impresion_especifica(ostream&) const = 0;	//Solo para subclases

		//Clase para excepciones
		class Autores_vacios{
			public:
			private:

		};

		virtual ~Articulo(){};

	private:

		Cadena ref_;						//referencia del articulo
		Cadena titulo_;					//titulo del articulos
		const Fecha fpublic_;		//fecha de publicación del articulo
		double precio_;					//precio del articulo
		Autores fundador;				//Autor del producto
};


class ArticuloAlmacenable: public Articulo{

	public:
		ArticuloAlmacenable(const Autores& aut,const Cadena&, const Cadena&, const Fecha&, double, unsigned stock=0);
		const unsigned& stock() const noexcept;
		unsigned& stock();
	protected:
		unsigned existencias_;	//nº stock disponible del articulo
};


class Libro: public ArticuloAlmacenable{

	public:
		Libro(const Autores& aut,const Cadena&, const Cadena&, const Fecha&, double,unsigned,unsigned stock=0);
		const unsigned& n_pag() const noexcept;
		void impresion_especifica(ostream&) const;
	private:
		const unsigned num_pag;		//Número de páginas del Libro
};


class Cederron: public ArticuloAlmacenable{

	public:
		Cederron(const Autores& aut,const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned stock=0);
		const unsigned& tam() const noexcept;
		void impresion_especifica(ostream&) const;
	private:
		unsigned megabyt;		//Tamaño en megabytes del CD-ROM
};


class LibroDigital: public Articulo{

	public:
		LibroDigital(const Autores& aut,const Cadena&, const Cadena&, const Fecha&, double, const Fecha&);
		const Fecha& f_expir() const noexcept;
		void impresion_especifica(ostream&) const;
	private:
		const Fecha exp;	//fecha de expiración del Libro Digital

};

std::ostream& operator <<(ostream&, const Articulo&);






#endif

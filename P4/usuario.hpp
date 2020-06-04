#ifndef USUARIO_H
#define USUARIO_H
#include <iosfwd>         // for ostream
#include <map>            // for map, map<>::value_compare
#include <unordered_map>  // for unordered_map
#include <unordered_set>  // for unordered_set
#include "cadena.hpp"     // for Cadena
class Articulo;  // lines 14-14
class Numero;  // lines 12-12
class Tarjeta;  // lines 13-13

using namespace std;

class Clave{

	public:

		Clave(const char*);
		Cadena clave() const;
		bool verifica(const char*) const;

		enum Razon {CORTA, ERROR_CRYPT};

		class Incorrecta{

			public:
				Incorrecta(Clave::Razon);
				Razon razon() const;

			private:

				Razon r_;
		};

	private:

		Cadena passwd;
};

class Usuario{

	public:

		Usuario(const Cadena&,const Cadena&, const Cadena&, const Cadena&, const Clave&);

		Usuario(const Usuario&) = delete;												//Prohibir copia de usuarios
		Usuario& operator =(const Usuario&) = delete;

		typedef map<Numero, Tarjeta*> Tarjetas;									//Contenedor para almacenar las tarjetas
		typedef unordered_map<Articulo*,unsigned> Articulos;		//Contenedor para almacenar los articulos seleccionados

		const Cadena& id() const noexcept;
		const Cadena& nombre() const noexcept;
		const Cadena& apellidos() const noexcept;
		const Cadena& direccion() const noexcept;
		const Tarjetas& tarjetas() const noexcept;
		const Articulos& compra() const noexcept;

		void es_titular_de(Tarjeta&);											//Asigna tarjeta a usuario
		void no_es_titular_de(Tarjeta&);									//Elimina tarjeta a usuario
		void compra(Articulo& a, unsigned cantidad = 1);
		unsigned n_articulos() const;

		friend std::ostream& operator <<(ostream&, const Usuario&);

		class Id_duplicado{
				public:
					Id_duplicado(const Cadena&);
					const Cadena& idd() const;
				private:
					Cadena id_;
		};

		~Usuario();
	private:

		Cadena identif_;				//Identificador
		Cadena nom_;						//Nombre
		Cadena apell_;					//Apellidos
		Cadena dir_;						//Dirección
		Clave password;					//Contraseña
		Tarjetas tarj_;					//Tarjetas
		Articulos articulos;		//Carrito de la compra
		/* Guardamos los usuarios(identificadores) ya registrados para comprobar
		*	 que no se dupliquen.				*/
		static unordered_set<Cadena> registrado;
};

void mostrar_carro(ostream&, const Usuario&);

#endif //USUARIO_H

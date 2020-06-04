#ifndef TARJETA_H
#define TARJETA_H
#include <iosfwd>      // for ostream
#include <set>         // for set
#include "cadena.hpp"  // for Cadena
#include "fecha.hpp"   // for Fecha

using namespace std;
class Usuario;

class Numero{

	public:

		Numero(Cadena);

		const Cadena& cadena() const;
		operator const char*() const;
		enum Razon{LONGITUD,DIGITOS,NO_VALIDO};

		/* Para manejar la razón de por qué un número
		*	 es incorrecto	*/
		class Incorrecto{
			public:
				Incorrecto(const Razon&);
				Razon razon() const;
			private:
				Razon r_;
		};

	private:

		Cadena num_;

};

bool operator <(const Numero&, const Numero&);


class Tarjeta{

	public:

		Tarjeta(const Numero&, Usuario&, const Fecha&);
		Tarjeta(const Tarjeta&) = delete;
		Tarjeta& operator =(const Tarjeta&) = delete;

		enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

		Usuario* titular() const noexcept;
		Tipo tipo() const noexcept;
		const Numero& numero() const noexcept;
		const Fecha& caducidad() const noexcept;
		bool activa() const noexcept;
		void anula_titular();
		bool activa(bool a = true) noexcept;

		//Clases para excepciones:
		class Caducada{								//Para conocer cuando ha caducado una tarjeta
			public:
				Caducada(const Fecha&);
				const Fecha& cuando() const;
			private:
				Fecha cad;
		};

		class Num_duplicado{					//Para saber el número que está duplicado
			public:
				Num_duplicado(const Numero&);
				const Numero& que() const;
			private:
				Numero dup;
		};

		class Desactivada{
			public:
			Desactivada();
			private:
		};


		~Tarjeta();
	private:

		const Numero num_tarjeta;
		Usuario* const titular_;
		const Fecha f_cad;
		bool activada_;
		/*Guardamos todos los números existentes, para que no hayan
		 * numeros repetidos	*/
		static set<Numero> numeros_;
};										

/*Sobrecarga de los operadores << y < */
ostream& operator<<(ostream&, const Tarjeta&);
ostream& operator<<(ostream&, Tarjeta::Tipo);
bool operator<(const Tarjeta&, const Tarjeta&);


#endif

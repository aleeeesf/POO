#ifndef PEDIDO_H
#define PEDIDO_H
#include <iostream>  	// for ostream
#include "fecha.hpp"  	// for Fecha
class Articulo;
//class Pedido_Articulo;  // lines 15-15
//class Tarjeta;  		// lines 14-14
class Usuario;
class Usuario_Pedido;

using namespace std;

class Tarjeta;
class Pedido_Articulo;


class Pedido{

	public:

		Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario& , const Tarjeta& ,const Fecha& f = Fecha{});

		unsigned numero() const;
		const Tarjeta* tarjeta() const;
		const Fecha& fecha() const;
		double total() const;
		static unsigned n_total_pedidos();

		/*	Clases para el manejo de excepciones  */
		class Vacio{
			public:
				Vacio(Usuario*);
				Usuario& usuario() const;
			private:
				Usuario* u;
		};

		class Impostor{
			public:
				Impostor(Usuario*);
				Usuario& usuario() const;
			private:
				Usuario* u;
		};

		class SinStock{
			public:
				SinStock(Articulo*);
				Articulo& articulo() const;
			private:
				Articulo* a;
		};

	private:

		unsigned num_pedido;					//Identificador del pedido
		Fecha f_pedido;								//Fecha del pedido
		const Tarjeta* tarjeta_pago;	//Tarjeta con la que se realiza el pedido
		double importe_total;					//Importe total del pedido
		static unsigned cant_pedidos;	//Cantidad total de pedidos realizados hasta la fecha
};

ostream& operator<<(ostream& os, const Pedido& p);

#endif

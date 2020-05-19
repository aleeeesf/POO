#ifndef PEDIDO_H
#define PEDIDO_H
#include <iostream>
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "fecha.hpp"
#include "articulo.hpp"

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
		unsigned num_pedido;
		Fecha f_pedido;
		const Tarjeta* tarjeta_pago;
		double importe_total;
		static unsigned cant_pedidos;
};

ostream& operator<<(ostream& os, const Pedido& p);

#endif

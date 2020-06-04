#ifndef PEDIDO_ARTICULO_H
#define PEDIDO_ARTICULO_H
#include <iostream>
#include <map>
#include "articulo.hpp"
#include "pedido.hpp"
class Pedido;

using namespace std;

class LineaPedido{
	
	public:
		LineaPedido(double p,unsigned c = 1);
		double precio_venta() const;
		unsigned cantidad() const;
	
	private:
		double p_venta;
		unsigned cant;
	
};
ostream& operator<<(ostream& os, const LineaPedido&);



struct OrdenaPedidos:binary_function<Pedido*,Pedido*,bool>
{
	public:	bool operator()(Pedido*, Pedido*) const;
};
struct OrdenaArticulos:binary_function<Articulo*,Articulo*,bool>
{
	public: bool operator()(Articulo*, Articulo*) const;
};



class Pedido_Articulo{
	
	public:
				
		typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
		typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
		
		typedef map<Pedido*, ItemsPedido, OrdenaPedidos> PA;
		typedef map<Articulo*,Pedidos,OrdenaArticulos> AP;
		
		void pedir(Pedido&, Articulo&, double precio,unsigned cant = 1);
		void pedir(Articulo&, Pedido&, double precio,unsigned cant = 1);
		const ItemsPedido& detalle(Pedido&);
		const Pedidos& ventas(Articulo&);
		
		ostream& mostrarDetallePedidos(ostream& os);
		ostream& mostrarVentasArticulos(ostream& os);
	
	private:

		PA ped_art;
		AP art_ped;
	
};

ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& IP);
ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& P);

#endif

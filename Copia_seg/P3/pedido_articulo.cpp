#include "pedido_articulo.hpp"
#include <iomanip>
#include <iostream>
#include <map>
using namespace std;


/*	LINEA PEDIDO	*/	

LineaPedido::LineaPedido(double p, unsigned c):p_venta(p),cant(c){}

double LineaPedido::precio_venta() const {return p_venta;}

unsigned LineaPedido::cantidad() const {return cant;}

ostream& operator<<(ostream& os, const LineaPedido& l){
	
	os<<fixed<<setprecision(2)<<l.precio_venta()<<" €	"<<l.cantidad();
	return os;
}

bool OrdenaPedidos::operator()(Pedido* x, Pedido* y) const {return (*x).numero() < (*y).numero();}

bool OrdenaArticulos::operator()(Articulo* x, Articulo* y) const {return x->referencia() < y->referencia();}




/* PEDIDO	ARTICULO	*/	


void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio,unsigned cant)
{

	Pedido_Articulo::ItemsPedido i;
	i.insert(make_pair(&a,LineaPedido(precio,cant)));
	
	Pedido_Articulo::Pedidos j;
	j.insert(make_pair(&p,LineaPedido(precio,cant)));
	
	ped_art[&p] = i;
	art_ped[&a] = j;
}
void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio,unsigned cant)
{
	pedir(p,a,precio,cant);
}
const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p)
{
	 auto i = ped_art.find(&p);
	 return i->second;
}

const Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& a)
{
	 auto i = art_ped.find(&a);
	 return i->second;
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os)
{
	setlocale(LC_ALL,"es_ES");
	double p_total;
	
	for(auto &i: ped_art){
		os<<"Pedido núm. "<<i.first->numero()<<endl<<i.first->tarjeta()->titular()->nombre()
		<<"\t\t"<<i.first->fecha()<<endl;
	
		p_total += i.first->total();
	}
	
	os<<"TOTAL VENTAS\t\t"<<fixed<<setprecision(2)<<p_total<<endl;
	
	return os;
}
ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os) 
{
	for(auto i: art_ped){
	os<<"Ventas de "<<"["<<i.first->referencia()<<"]"<<"\""<<i.first->titulo()<<"\""<<endl;
	}
	return os;
}
ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& IP)
{
	setlocale(LC_ALL,"es_ES");
	os<<"  PVP	Cantidad			Artículo"<<endl;
	os<<"======================================================="<<endl;
	
	double total;
	
	for(auto i: IP){
		os<<i.second.precio_venta()<<" € "<<i.second.cantidad()<<"\t\t\t"<<
		"["<<i.first->referencia()<<"] "<<i.first->titulo()<<endl;
		
		total += i.second.precio_venta() * i.second.cantidad();
	}
	os<<"======================================================="<<endl;
	os<<"Total\t"<<fixed<<setprecision(2)<<total<<" €"<<endl;

	return os;
}

ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& P)
{
	setlocale(LC_ALL,"es_ES");
	os<<"  PVP	Cantidad			Fecha de venta"<<endl;
	os<<"======================================================="<<endl;
	
	double total;
	unsigned cantid;
	
	for(auto i: P){
		os<<i.second.precio_venta()<<" € "<<i.second.cantidad()<<"\t\t\t"<<
		i.first->fecha()<<endl;
		
		total += i.second.precio_venta() * i.second.cantidad();
		cantid += i.second.cantidad();
	}
	os<<"======================================================="<<endl;
	os<<"Total\t"<<fixed<<setprecision(2)<<total<<" €\t\t"<<cantid<<endl;

	return os;
}


#include "pedido-articulo.hpp"
#include <fstream>
#include <locale.h>      // for setlocale, LC_ALL
#include <iomanip>       // for operator<<, setprecision
#include <iostream>      // for operator<<, ostream, basic_ostream, endl
#include <map>           // for _Rb_tree_iterator, map
#include <utility>       // for pair, make_pair
#include "articulo.hpp"  // for Articulo
#include "cadena.hpp"    // for operator<<, operator<, Cadena
#include "fecha.hpp"     // for operator<<
#include "pedido.hpp"    // for Pedido
#include "tarjeta.hpp"   // for Tarjeta
#include "usuario.hpp"   // for Usuario

using namespace std;

/*	LINEA PEDIDO	*/	

LineaPedido::LineaPedido(double p, unsigned c):p_venta(p),cant(c){}

double LineaPedido::precio_venta() const {return p_venta;}

unsigned LineaPedido::cantidad() const {return cant;}

ostream& operator<<(ostream& os, const LineaPedido& l){
	
	os<<fixed<<setprecision(2)<<l.precio_venta()<<" €	"<<l.cantidad();
	return os;
}

bool OrdenaPedidos::operator()(Pedido* x, Pedido* y) const {return x->numero() < y->numero();}

bool OrdenaArticulos::operator()(Articulo* x, Articulo* y) const {return x->referencia() < y->referencia();}




/* PEDIDO	ARTICULO	*/	


void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio,unsigned cant)
{
	auto i = ped_art.find(&p);
	
	if(i != ped_art.end())
	{
		i->second.insert(make_pair(&a,LineaPedido(precio,cant)));
	}
	
	else	
	{
		ItemsPedido aux;
		aux.insert(make_pair(&a,LineaPedido(precio,cant)));
		ped_art.insert(make_pair(&p,aux));
		
	}
	
	auto x = art_ped.find(&a);
	
	if(x != art_ped.end())
	{
		x->second.insert(make_pair(&p,LineaPedido(precio,cant)));
	}
	
	else	
	{
		Pedidos aux;
		aux.insert(make_pair(&p,LineaPedido(precio,cant)));
		art_ped.insert(make_pair(&a,aux));
	}
	
	//auto k = art_ped.find(&a);
	//cout<<k->second<<endl;
	
}
/*

	ped_art[&p].insert(make_pair(&a,LineaPedido(precio,cant)));
	art_ped[&a].insert(make_pair(&p,LineaPedido(precio,cant)));
*/	
void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio,unsigned cant)
{
	pedir(p,a,precio,cant);
}
const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p)
{
	 auto i = ped_art.find(&p);
	 return i->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a)
{
	 auto i = art_ped.find(&a);
	 if(i != art_ped.end())  return i->second;
	 else{
		 Pedido_Articulo::Pedidos aux;
		 return aux;
		 }
	
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os)
{
	setlocale(LC_ALL,"es_ES");
	double p_total = 0.0;
	
	for(auto &i: ped_art){
		os<<"Pedido núm. "<<i.first->numero()<<endl<<
		"Cliente: "<<i.first->tarjeta()->titular()->nombre()
		<<"\t\t"<<"Fecha: "<<i.first->fecha()<<endl<<i.second<<endl;
	
		p_total += i.first->total();
	}
	
	os<<"TOTAL VENTAS\t\t"<<fixed<<setprecision(2)<<p_total<<" €"<<endl;
	
	return os;
}
ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os) 
{

	for(auto i: art_ped){
	os<<"Ventas de "<<"["<<i.first->referencia()<<"]"<<" \""<<i.first->titulo()<<"\""<<endl<<i.second<<flush<<endl;
	}
	
	return os;
}
ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& IP)
{
	setlocale(LC_ALL,"es_ES");
	os.flush();
	os<<"  PVP	Cantidad			Artículo"<<endl;
	os<<"======================================================="<<endl;
	
	double total = 0;
	Pedido_Articulo::ItemsPedido::const_iterator i;
	for(i = IP.begin();i != IP.end(); ++i){
		os<<i->second.precio_venta()<<" € "<<i->second.cantidad()<<"\t\t\t"<<
		"["<<i->first->referencia()<<"] "<<i->first->titulo()<<endl;
		
		total += i->second.precio_venta() * i->second.cantidad();
	}
	os<<"======================================================="<<endl;
	os<<"Total\t"<<fixed<<setprecision(2)<<total<<" €"<<endl<<flush;
	
	return os;
}

ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& P)
{
	setlocale(LC_ALL,"es_ES");
	
	os<<"  PVP	Cantidad			Fecha de venta"<<endl;
	os<<"======================================================="<<endl;
	
	double total = 0;
	unsigned cantid = 0;
	
	for(auto i: P){
		os<<fixed<<setprecision(2)<<i.second.precio_venta()<<" €   "<<i.second.cantidad()<<"\t\t\t"<<
		i.first->fecha()<<endl;
		
		total += i.second.precio_venta() * i.second.cantidad();
		cantid += i.second.cantidad();
	}
	os<<"======================================================="<<endl;
	os<<fixed<<setprecision(2)<<total<<" €  "<<cantid<<endl<<flush;
	
	return os;
}


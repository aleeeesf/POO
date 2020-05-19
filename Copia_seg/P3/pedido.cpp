#include "pedido.hpp"
#include <iomanip>

unsigned Pedido::cant_pedidos(0);
ostream& operator<<(ostream&, Tarjeta::Tipo);

	/* **************************************** */
	/*				CONSTRUCTORES				*/
	/* **************************************** */



Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t,const Fecha& f):
	f_pedido(f),tarjeta_pago(&t),importe_total(0.0)
{
	
	if(u.compra().empty()) throw Pedido::Vacio(&u);
	if(u.id() != t.titular()->id()) throw Pedido::Impostor(&u);
	if(t.caducidad().anno() < f.anno()) throw Tarjeta::Caducada(f);
	
	if((t.caducidad().anno() == f.anno()) && (t.caducidad().mes() < f.mes())) throw Tarjeta::Caducada(f);
	
	if((t.caducidad().anno() == f.anno()) && (t.caducidad().mes() == f.mes()) && (t.caducidad().dia() < f.dia())) throw Tarjeta::Caducada(f);
		
	if(!t.activa()) throw Tarjeta::Desactivada();
	
	for(auto &i: u.compra()){
		
		if(i.first->stock() < i.second){
			ostream& operator<<(ostream&, Tarjeta::Tipo);
			const_cast<Usuario::Articulos&> (u.compra()).erase(u.compra().begin(),u.compra().end());		
			
			throw Pedido::SinStock(i.first);
		} 
	}

	
	for(auto &i: u.compra()){
		
		pa.pedir(*this,*i.first, i.first->precio(),i.second);
		importe_total += i.first->precio() * i.second;
		i.first->stock() -= i.second;
	}
		
	up.asocia(u, *this);
	cant_pedidos++;
	num_pedido = cant_pedidos;
	const_cast<Usuario::Articulos&> (u.compra()).erase(u.compra().begin(),u.compra().end());
	
}


Pedido::Vacio::Vacio(Usuario* us):u(us){}
Usuario& Pedido::Vacio::usuario() const {return *u;}

Pedido::Impostor::Impostor(Usuario* us):u(us){}
Usuario& Pedido::Impostor::usuario() const{return *u;}

Pedido::SinStock::SinStock(Articulo* art):a(art){}
Articulo& Pedido::SinStock::articulo() const{return *a;}

	

	/* **************************************** */
	/*			FUNCIONES	CONSULTORAS			*/
	/* **************************************** */
	
	
		
unsigned Pedido::numero() const {return num_pedido;}
const Tarjeta* Pedido::tarjeta() const {return tarjeta_pago;}
const Fecha& Pedido::fecha() const {return f_pedido;}
double Pedido::total() const {return importe_total;}
unsigned Pedido::n_total_pedidos() {return cant_pedidos;}


ostream& operator<<(ostream& os, const Pedido& p)
{
	setlocale(LC_ALL,"es_ES");
	os<<"Núm. pedido: "<<p.numero()<<endl
	<<"Fecha:     \t"<<p.fecha()<<endl
	<<"Pagado con:\t"<<p.tarjeta()->tipo()<<" n.º: "<<p.tarjeta()->numero()<<endl
	<<"Importe:   \t"<<fixed<<setprecision(2)<<p.total()<<" €"<<endl;

	return os;

}

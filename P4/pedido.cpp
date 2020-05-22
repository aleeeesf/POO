#include "pedido.hpp"
#include <locale.h>             // for setlocale, LC_ALL
#include <iomanip>              // for operator<<, setprecision
#include <utility>              // for pair
#include "articulo.hpp"         // for Articulo
#include "cadena.hpp"           // for operator!=, Cadena
#include "pedido-articulo.hpp"  // for Pedido_Articulo
#include "tarjeta.hpp"          // for Tarjeta, Tarjeta::Caducada, Numero
#include "usuario-pedido.hpp"   // for Usuario_Pedido
#include "usuario.hpp"          // for Usuario, Usuario::Articulos

//Inicialización del atributo estático cant_pedidos
unsigned Pedido::cant_pedidos(0);



	/* **************************************** */
	/*				CONSTRUCTORES				*/
	/* **************************************** */



Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t,const Fecha& f):
	num_pedido(cant_pedidos+1),f_pedido(f),tarjeta_pago(&t),importe_total(0.0)
{
	/*	Comprobamos que el carrito no está vacío	*/
	if(u.compra().empty()) throw Pedido::Vacio(&u);
	
	/*	Comprobamos que el titular de la tarjeta no sea diferente al usuario	*/
	if(u.id() != t.titular()->id()) throw Pedido::Impostor(&u);
	
	/*	Comprobamos que la tarjeta no está caducada	*/
	if(t.caducidad().anno() < f.anno()) throw Tarjeta::Caducada(t.caducidad());
	if((t.caducidad().anno() == f.anno()) && (t.caducidad().mes() < f.mes())) throw Tarjeta::Caducada(t.caducidad());
	if((t.caducidad().anno() == f.anno()) && (t.caducidad().mes() == f.mes()) && (t.caducidad().dia() < f.dia())) throw Tarjeta::Caducada(t.caducidad());
	
	/*	Comprobamos que la tarjeta está activa	*/
	if(!t.activa()) throw Tarjeta::Desactivada();
	
	
	
	//for(auto &i: u.compra())
	//{	
		//No hacer caso: Diapositiva 14 del tema 4.Polimorfismo
		//if(ArticuloAlmacenable* pa = dynamic_cast<ArticuloAlmacenable*>(i.first)){ 	//Si el objeto apuntado por i.first es de tipo ArticuloAlmacenable
																					//i.first se convierte sin problemas en pa
		//	if(pa->stock() < i.second){
			
			//	const_cast<Usuario::Articulos&> (u.compra()).clear();
				
				/*	DIFERENTES MANERAS DE VACIAR EL CARRITO	*/	
				
				//for(auto& it: u.compra())
				//{				
					//cout<<it.first<<endl;					
				//}
				
				//const_cast<Usuario::Articulos&> (u.compra()).erase(u.compra().begin(),u.compra().end());		
				
				//throw Pedido::SinStock(i.first);	//NO hay stock del artículo
			//} 
		//}
	//}
	
	//unsigned cont_pedidos = 0;
	//unsigned cont_expirados = 0;
	//unsigned compra_libros = 0;
	bool ped_vacio = true;
	/*	Actualizamos el stock, calculamos el importe total y realizamos el pedido	*/
	for(auto &i: u.compra())
	{
		if(LibroDigital* plib = dynamic_cast<LibroDigital *>(i.first)){
			
			if (plib->f_expir().anno() < f_pedido.anno()) {u.compra(*i.first,0);}
			else if ((plib->f_expir().anno() == f_pedido.anno()) && (plib->f_expir().mes() < f_pedido.mes())) {u.compra(*i.first,0);}
			else if ((plib->f_expir().anno() == f_pedido.anno()) && (plib->f_expir().mes() == f_pedido.mes()) && (plib->f_expir().dia() < f_pedido.dia())){u.compra(*i.first,0);}
			//if(plib->f_expir() < f_pedido)

			else{
				 ped_vacio = false;
				 pa.pedir(*this,*plib, i.first->precio(),i.second);	
				 importe_total += i.first->precio() * i.second;	
				 u.compra(*i.first,0);		 
			}
		}
		else if	(ArticuloAlmacenable* p_art = dynamic_cast<ArticuloAlmacenable *>(i.first))
		{
			if(p_art->stock() < i.second){
				const_cast<Usuario::Articulos&> (u.compra()).clear();
				throw Pedido::SinStock(i.first);	//NO hay stock del artículo
			}
			
			pa.pedir(*this,*p_art, i.first->precio(),i.second);	
			p_art->stock() -= i.second;
		    importe_total += i.first->precio() * i.second;	
			u.compra(*i.first,0);
			ped_vacio = false;
		}
		else throw bad_cast();
	}
	
	/*Si no ha comprado ningun articulo diferente a libro digital y el
	 * numero de libros expirados es el mismo que el numero de libros comprados
	 * lanzamos excepcion (Enunciado: Si introduce un libro expirado, el pedido no se anula,
	 * si el pedido se queda vacio por este motivo se lanza excepcion)*/
	if(ped_vacio) throw Vacio(&u);
	
	/*	Asociamos el usuario con el pedido	*/	
	up.asocia(u, *this);
	cant_pedidos++;
}

//Constructor de la clase de excepcion Vacio
Pedido::Vacio::Vacio(Usuario* us):u(us){}
//Devuelve el usuario que tiene el 
Usuario& Pedido::Vacio::usuario() const {return *u;}

//Constructor de la clase de excepcion Impostor
Pedido::Impostor::Impostor(Usuario* us):u(us){}
//Devuelve el usuario impostor
Usuario& Pedido::Impostor::usuario() const{return *u;}

//Constructor de la clase de excepcion Vacio
Pedido::SinStock::SinStock(Articulo* art):a(art){}
//Devuelve el articulo que no tiene stock
Articulo& Pedido::SinStock::articulo() const{return *a;}


	

	/* **************************************** */
	/*			FUNCIONES	CONSULTORAS			*/
	/* **************************************** */
	
	
	
//Tipo de funcion: Publica
//POstcondición: devulve el numero del pedido		
unsigned Pedido::numero() const {return num_pedido;}

//Tipo de funcion: Publica
//POstcondición: devuelve la tarjeta con la que se ha realizado el pedido
const Tarjeta* Pedido::tarjeta() const {return tarjeta_pago;}

//Tipo de funcion: Publica
//POstcondición: devuelve la fecha en la que se hizo el pedido
const Fecha& Pedido::fecha() const {return f_pedido;}

//Tipo de funcion: Publica
//POstcondición: devuelve el importe total del pedido	
double Pedido::total() const {return importe_total;}

//Tipo de funcion: Publica
//POstcondición: devuelve la cantidad de pedidos realizados	
unsigned Pedido::n_total_pedidos() {return cant_pedidos;}

//Sobrecarga del operador de la salida estandar
ostream& operator<<(ostream& os, const Pedido& p)
{
	setlocale(LC_ALL,"es_ES.UTF-8");
	os<<"Núm. pedido: "<<p.numero()<<endl
	<<"Fecha:     \t"<<p.fecha()<<endl
	<<"Pagado con:\t"<<p.tarjeta()->tipo()<<" n.º: "<<p.tarjeta()->numero()<<endl
	<<"Importe:   \t"<<fixed<<setprecision(2)<<p.total()<<" €"<<endl;

	return os;

}

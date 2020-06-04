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
	/*	         CONSTRUCTORES	  	    */
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

	for(auto &i: u.compra())
	{
			/*Si el objeto apuntado por i.first es de tipo ArticuloAlmacenable
			 * i.first se convierte sin problemas en pa	*/
			if(ArticuloAlmacenable* pa = dynamic_cast<ArticuloAlmacenable*>(i.first)){

					if(pa->stock() < i.second){
						const_cast<Usuario::Articulos&> (u.compra()).clear();
						throw Pedido::SinStock(i.first);	//NO hay stock del artículo
					}
			}
	}

	bool ped_vacio = true;			//Booleano para comprobar si el pedido está vacío
	Usuario::Articulos carro = u.compra();	//Carro auxiliar, para no modificar el original

	/* Se realizan los pedidos que tenga el usuario en el carrito;
	 * Si se trata de un artículo almacenable se decrementa el stock;
	 * Si se trata de un Libro Digital se comprobraá que la fecha de expiración
	 * no supere la actual*/
	for(auto i: carro)
	{
				/*Primero comprobamos que el artículo recibido sea un LibroDigital*/
				if(LibroDigital* plib = dynamic_cast<LibroDigital *>(i.first)){

						/*Comprobamos que la fecha de expiración sea correcta*/
						if(plib->f_expir() < f_pedido) u.compra(*i.first,0);

						else{
							 //El pedido no contiene ningun libro expirado o contiene al menos un Art. Almacenable
							 ped_vacio = false;
							 pa.pedir(*this,*plib, i.first->precio(),i.second);	//Pedimos el artículo
							 importe_total += i.first->precio() * i.second;		//Calculamos el importe total
							 u.compra(*i.first,0);
						}
				}

				/*Si no lo es entonces será un Artículo Almacenable (CD-ROM, Libro...)*/
				else if	(ArticuloAlmacenable* p_art = dynamic_cast<ArticuloAlmacenable *>(i.first))
				{
						pa.pedir(*this,*p_art, i.first->precio(),i.second);		//Pedimos el artículo
						p_art->stock() -= i.second;					//decrementamos el stock
					   	importe_total += i.first->precio() * i.second;			//Calculamos el importe total
						u.compra(*i.first,0);
						ped_vacio = false;	 //El pedido no contiene ningun libro expirado o contiene al menos un Art. Almacenable
				}

				/*No se trata ni de un Artículo Almacenable ni de un Libro Digital;
				* por lo que se lanzará una excepción */
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

//Devuelve el usuario que tiene el carrito vacío
Usuario& Pedido::Vacio::usuario() const {return *u;}

//Constructor de la clase de excepción Impostor
Pedido::Impostor::Impostor(Usuario* us):u(us){}

//Devuelve el usuario impostor
Usuario& Pedido::Impostor::usuario() const{return *u;}

//Constructor de la clase de excepción Vacio
Pedido::SinStock::SinStock(Articulo* art):a(art){}

//Devuelve el artículo que no tiene stock
Articulo& Pedido::SinStock::articulo() const{return *a;}



	/* **************************************** */
	/*	FUNCIONES	CONSULTORAS	    */
	/* **************************************** */



//Tipo de funcion: Pública
//POstcondición: devulve el número del pedido
unsigned Pedido::numero() const {return num_pedido;}

//Tipo de funcion: Pública
//POstcondición: devuelve la tarjeta con la que se ha realizado el pedido
const Tarjeta* Pedido::tarjeta() const {return tarjeta_pago;}

//Tipo de funcion: Pública
//POstcondición: devuelve la fecha en la que se hizo el pedido
const Fecha& Pedido::fecha() const {return f_pedido;}

//Tipo de funcion: Pública
//POstcondición: devuelve el importe total del pedido
double Pedido::total() const {return importe_total;}

//Tipo de funcion: Pública
//POstcondición: devuelve la cantidad de pedidos realizados
unsigned Pedido::n_total_pedidos() {return cant_pedidos;}

//Sobrecarga del operador de la salida estándar
ostream& operator<<(ostream& os, const Pedido& p)
{
	setlocale(LC_ALL,"es_ES.UTF-8");
	os<<"Núm. pedido: "<<p.numero()<<endl
	<<"Fecha:     \t"<<p.fecha()<<endl
	<<"Pagado con:\t"<<p.tarjeta()->tipo()<<" n.º: "<<p.tarjeta()->numero()<<endl
	<<"Importe:   \t"<<fixed<<setprecision(2)<<p.total()<<" €"<<endl;

	return os;

}

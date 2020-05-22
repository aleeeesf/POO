#include "usuario-pedido.hpp"
#include <utility>  // for pair
class Pedido;  		// lines 2-2

//Tipo de funcion: Publica
//Postcondicion: asociia un usuario a un pedido
void Usuario_Pedido::asocia(Usuario& u,Pedido& p)
{
	usu_ped[&u].insert(&p); 		//insertamos en el set
	ped_usu[&p] = &u;				//insertamos en la segunda
}

//Tipo de funcion: Publica
//Postcondicion: asocia un usuario a un pedido
void Usuario_Pedido::asocia(Pedido& p,Usuario& u)
{
	asocia(u,p);
}

//Tipo de funcion: Publica
//Postcondicion: devuelve los pedidos de un usuario
const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& us) const
{
	auto i = usu_ped.find(&us);
	return i->second;
}

//Tipo de funcion: Publica
//Postcondicion: devuelve el cliente que ha realizado el pedido
Usuario* Usuario_Pedido::cliente(Pedido& p) const
{
	auto i = ped_usu.find(&p);
	return i->second;
}
	

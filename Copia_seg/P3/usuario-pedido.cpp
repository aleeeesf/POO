#include "usuario-pedido.hpp"
#include <utility>  // for pair
class Pedido;  // lines 2-2

void Usuario_Pedido::asocia(Usuario& u,Pedido& p)
{
	usu_ped[&u].insert(&p); 		//insertamos en el set
	ped_usu[&p] = &u;				//insertamos en la segunda
}
void Usuario_Pedido::asocia(Pedido& p,Usuario& u)
{
	asocia(u,p);
}
const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& us) const
{
	auto i = usu_ped.find(&us);
	return i->second;
}
Usuario* Usuario_Pedido::cliente(Pedido& p) const
{
	auto i = ped_usu.find(&p);
	return i->second;
}
	

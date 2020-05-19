#ifndef USUARIO_PEDIDO_H
#define USUARIO_PEDIDO_H
#include <map>
#include <set>
class Usuario;
class Pedido;

using namespace std;
class Usuario_Pedido{
	
	public:
		typedef set<Pedido*> Pedidos;
		
		void asocia(Usuario&,Pedido&);
		void asocia(Pedido&,Usuario&);
		const Pedidos& pedidos(Usuario&) const;
		Usuario* cliente(Pedido&) const;
	
		
	private:
		map<Usuario*, Pedidos> usu_ped;
		map<Pedido*, Usuario*> ped_usu;
};

#endif

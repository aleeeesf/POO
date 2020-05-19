#include "usuario.hpp"
#include <string.h>       // for strcmp, strlen
#include <unistd.h>       // for crypt
#include <cstddef>        // for size_t
#include <iomanip>        // for operator<<, setw
#include <ostream>        // for operator<<, ostream, basic_ostream, basic_o...
#include <random>         // for uniform_int_distribution, random_device
#include <unordered_set>  // for unordered_set
#include <utility>        // for pair
#include "articulo.hpp"   // for Articulo
#include "fecha.hpp"      // for Fecha
#include "tarjeta.hpp"    // for Tarjeta

using namespace std;
unordered_set<Cadena> Usuario::registrado;				//Hay que incluir la especialización de la 
														//plantilla hash<T> en cadena.hpp
						
	/* **************************************** */
	/*				 CLASE CLAVE				*/
	/* **************************************** */


Clave::Clave(const char* p)
{	
	if(strlen(p) < 5) throw Incorrecta(CORTA);		//La contraseña en menor que 5 caracteres
	
	else{
		
		static const char* semilla = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
		static std::random_device rd;										//Genera un numero aleatorio
		static std::uniform_int_distribution<std::size_t> dist(0,63);
		char sal[2] = {semilla[dist(rd)],semilla[dist(rd)]};				//Tomamos dos letras aleatorias
		
		passwd = crypt(p,sal);		//Guardamos la contraseña encriptada

		if(passwd.c_str() == nullptr || passwd.length() < 13) throw Incorrecta(Clave::Razon::ERROR_CRYPT);
	}
}

//Constructor clase Incorrecta (Para excepciones)
Clave::Incorrecta::Incorrecta(Clave::Razon r):r_(r){}

//Tipo de función: Pública
//Postcondición: Devuelve true si la contraseña coinciden
bool Clave::verifica(const char* c) const
{	
	if( strcmp(crypt(c,passwd.c_str()) , passwd.c_str()) == 0) return true;		//Comprobamos la contraseña introducida con la contraseña encriptada
	else return false;
}

//Tipo de función: Pública.
//Postcondición: Devuelve la contraseña encriptada.
Cadena Clave::clave() const {return passwd;}

//Tipo de función: Pública
//Postcondición: Devuelve la razón del error cometido al introducir la contraseña.
Clave::Razon Clave::Incorrecta::razon() const{return r_;}



	/* **************************************** */
	/*				 CLASE USUARIO				*/
	/* **************************************** */



Usuario::Usuario(const Cadena& id,const Cadena& nom, const Cadena& ap, const Cadena& dir, const Clave& c):
	identif_(id), nom_(nom), apell_(ap), dir_(dir), password(c)
{
		//Buscar identificador repetidos si lo está 
		//lanzamos excepción mostrando el usuario duplicado
		
		if(!registrado.insert(id).second) throw(Id_duplicado(id));	//insert devuelve un par (set::end, false), para
																	//comprobar el segundo añadimos .second
}

//Constructor de la clase Id_duplicado -> Excepciones
Usuario::Id_duplicado::Id_duplicado(const Cadena& c):id_(c){}



	/* **************************************** */
	/*			FUNCIONES	CONSULTORAS			*/
	/* **************************************** */



//Tipo de función: Pública.
//Postcondición: Devuelve el id duplicado de una excepción.
const Cadena& Usuario::Id_duplicado::idd() const {return id_;}

//Tipo de función: Pública.
//Postcondición: Devuelve el id del usuario.
inline const Cadena& Usuario::id() const  noexcept{return identif_;}

//Tipo de función: Pública.
//Postcondición: Devuelve el nombre del usuario
inline const Cadena& Usuario::nombre() const  noexcept{return nom_;}

//Tipo de función: Pública.
//Postcondición: Devuelve los apellidos del usuario
inline const Cadena& Usuario::apellidos() const  noexcept{return apell_;}

//Tipo de función: Pública.
//Postcondición: Devuelve la dirección del usuario
inline const Cadena& Usuario::direccion() const  noexcept{return dir_;}

//Tipo de función: Pública.
//Postcondición: Devuelve las tarjetas del usuario
const Usuario::Tarjetas& Usuario::tarjetas() const noexcept {return tarj_;}

//Tipo de función: Pública.
//Postcondición: Devuelve el carrito de la compra del usuario
inline const Usuario::Articulos& Usuario::compra() const noexcept {return articulos;}



//Tipo de función: Pública (NO PERTENECE A LA CLASE USUARIO).
//Postcondición: Devuelve por pantalla los articulos del carrito.
void mostrar_carro(ostream& os, const Usuario& u)
{	
	locale::global(locale("es_ES.UTF-8"));
	
	os<<"Carrito de compra de "<<u.id()<<" [Artículos: "<<u.n_articulos()<<"]"<<
		endl<<" Cant.  Artículo"<<endl<<"===================================================="<<endl;
		
		for(auto i : u.compra()){
			os<<"  "<<i.second<<"    "<<*i.first<<endl;
		}
}



	/* **************************************** */
	/*			FUNCIONES	MODIFICADORAS		*/
	/* **************************************** */



//Tipo de función: Pública.
//Postcondición: Asigna una tarjeta a un usuario.
void Usuario::es_titular_de(Tarjeta& t)
{
	if(t.titular() == this)								//El titular de la tarjeta no puede
		tarj_[t.numero()] = const_cast<Tarjeta*>(&t);	//ser diferente
}

//Tipo de función: Pública.
//Postcondición: Elimina una tajeta de un usuario.
void Usuario::no_es_titular_de(Tarjeta& t)
{
	tarj_.erase(t.numero());
}

//Tipo de función: Pública.
//Postcondición:Añade al carrito de la compra los artículos introducidos.
//NOta: Si recibe cantidad = 0 elimina el articulo del carrito
void Usuario::compra(Articulo& a, unsigned cantidad)
{
	if(cantidad == 0) articulos.erase(&a);
	else articulos[&a] = cantidad;
	
}

//Tipo de función: Pública.
//Postcondición: Devuelve la cantidad de artículos del carrito
unsigned Usuario::n_articulos() const
{	
	unsigned cont = 0;
	
	for(Usuario::Articulos::const_iterator i = articulos.begin(); i != articulos.end(); ++i) cont ++;
	
	return cont;
}



std::ostream& operator <<(ostream& os, const Usuario& user)
{
	os<<user.id()<<" ["<<user.password.clave()<<"] "<<user.nombre()<<" "<<user.apellidos()
		<<"\n"<<user.direccion()<<"\n"<<"Tarjetas: "<<endl;
		
		
		for(auto& i : user.tarj_){
		
			os<<*i.second;
		}
		return os;
}

Usuario::~Usuario(){
	
	for(Usuario::Tarjetas::iterator i = tarj_.begin(); i != tarj_.end(); ++i){
		
		i->second->anula_titular();
	}
	registrado.erase(identif_);
}


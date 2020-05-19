#include <iostream>
//#include "articulo.hpp"
#include "usuario.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
#include <map>
using namespace std;
void numero_incorrecto(Numero::Incorrecto);
int main(){
	/*
	Articulo art("114","fundamentos","11/12/2020",29.33,2);
	cout<<art.precio();
	cout<<art<<endl;
	*/
	/*
	Clave c("holafeo");
	//Cadena a = c.clave();
	cout<<c.clave()<<endl;
	*/
	/*
	Numero b("5204408086566492");
	Numero c("1639858528586678");
	if(c < b) cout<<"yes"<<endl;
	*/
	
	//set<int> tarj;
				
	//tarj.insert(2);
	//tarj.insert(4);

	//f.insert(make_pair(1,2));
	//f.insert(make_pair(2,3));
	//f.insert(make_pair(3,74));
	//f.insert(make_pair(3,40));
	//for(auto i = tarj.begin();i!=tarj.end();i++) cout<<*i<<endl;
	
	//Fecha f;
	//Fecha a("10/04/2020");
	//if(a < f) cout<<"yes"<<endl;
	//Numero a("01234 56789 012   8");
	//if(strcmp(a, "01234567890128") == 0) cout<<"yes";
	
  Usuario
    sabacio("sabacio", "Sabacio", "Garibay Menchaca",
	  "Plaza Mayor, 1 (Hinojosa de Duero)", "vaeg0Quo"),
    miguel("miguel", "Miguel", "Mares Miramontes",
	    "C/ del Paseo, 59 (El Ronquillo)", "Pheaj9li"),
    nazarena("nazarena", "nazarena", "Marrero Rubio",
	  "Estrela, 18 (Suances)", "ahxo2Aht"),
    anabel("anabel", "Anabel", "Barrera Navarrete",
	 "Caño, 75 (A Coruña)", "Roh9aa5v");
  // Constructor de Tarjeta: Numero, Usuario, fecha de caducidad
  // Para evitar problemas con las fechas y sus caducidades, ponemos año 0
  // (el actual) y sumamos uno o más años.

    //Numero("4539 4512 0398 7356");
    
    Numero a("378282246310005");
                   
   
    //Numero("30569309025904");
    try{
    Numero b("555555555555 4444  ");
	}catch(Numero::Incorrecto e){
		cout<<e.razon();
		}
   // Numero("5610591081018250");
           
    
   // Numero("3530111333300000");
    
   // Numero(" 4222222222222");
/*
  anabel.no_es_titular_de(jcb);
  sabacio.es_titular_de(jcb); // No hace nada
  anabel.es_titular_de(jcb);

  std::cout << sabacio << '\n' << miguel << '\n'
            << nazarena << '\n' << anabel   << '\n';
             // Pruebas de excepciones

*/


}

// Función llamada desde los catch(Numero::Incorrecto) que comprueba
// la razón y muestra un mensaje apropiado.
void numero_incorrecto(Numero::Incorrecto e)
{
  std::cerr << "Error: El número de la tarjeta ";
  switch (e.razon()) {
  case Numero::DIGITOS:
    std::cerr << "tiene caracteres no numéricos ni blancos"
	      << std::endl;
    break;
  case Numero::NO_VALIDO:
    std::cerr << "no es válido, error de CRC." << std::endl;
    break;
  case Numero::LONGITUD:
    std::cerr << "es de una longitud incorrecta." << std::endl;
    break;
  }
}

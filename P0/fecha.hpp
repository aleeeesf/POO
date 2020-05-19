#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>
#include <cstring>

using namespace std;

class Fecha{

  public:
		
	  /*Constructores*/
      explicit Fecha(int d = 0, int m = 0, int a = 0);
      Fecha(const char*);
      	  
	  /*Variables constantes*/
      static const int AnnoMinimo = 1902;
      static const int AnnoMaximo = 2037;
      
      /*Consultoras*/
      void mostrarfecha();
      int maxdia(const int& m,const int& a) const;
      int dia() const noexcept; //Devuelve el dia de una fecha
      int mes() const noexcept; //Devuelve el mes de una fecha
      int anno() const noexcept; //Devuelve el año de una fecha
      
      static bool esbisiesto(int);
      void checkfecha(const int&,const int&,const int&);
      
      const char* convertir() const;
      /*Sobrecarga de operadores*/
      Fecha operator+(int) const;
      Fecha& operator++();
      Fecha operator ++(int);
      Fecha& operator--();
      Fecha operator-(int) const;
      Fecha operator --(int);
      Fecha& operator -=(int);
      Fecha& operator +=(int);

	  operator const char* () const{return convertir();}
	  /*Clase para excepciones*/
	  class Invalida{	
		  
		 char* mensaje;
		  
		 public: 
		  	
			Invalida(const char* msg){
				
				mensaje = new char[strlen(msg)];
				strcpy(mensaje,msg);
			}
			const char* por_que() const{
				
				return mensaje;
			}	
	  };	
		
  private:
		
      int diaa, mess, anoo;
      
      /*Consultar fecha del sistema*/
	  int anoactual();
      int mesactual();
      int diaactual();
     
};

bool operator <(const Fecha&,const Fecha&) noexcept;
bool operator >(const Fecha&,const Fecha&) noexcept;
bool operator <=(const Fecha&,const Fecha&) noexcept;
bool operator >=(const Fecha&,const Fecha&) noexcept;
bool operator ==(const Fecha&,const Fecha&) noexcept;
bool operator !=(const Fecha&,const Fecha&) noexcept;
std::ostream& operator<<(std::ostream& os, const Fecha& fch);
/*std::istream& operator>>(std::ostream& is, Fecha& fch);*/

#endif //Fin de FECHA_HPP_

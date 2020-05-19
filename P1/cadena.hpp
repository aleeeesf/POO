#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <cstring>
#include <iterator>
using namespace std;


class Cadena{
	
	public:
		
		/*Constructores*/
		explicit Cadena(unsigned t = 0,char c = ' ');
		Cadena(const char*);
		Cadena(const Cadena&);
		Cadena(Cadena&&);
		~Cadena();
		
		//void mostrarcadena() noexcept;	//Funcion de prueba
		
		/*Funciones consultoras*/
		const unsigned length()const noexcept;
		char& at(unsigned) const;
		const char* c_str() const{return s_;};
		Cadena substr(unsigned, const int&) const; 
		
		/*Sobrecarga de operadores*/
		char& operator[](unsigned);
		char operator[](unsigned) const;
		Cadena& operator =(const char*);
		Cadena& operator =(Cadena&& cad);
		Cadena& operator =(const Cadena&);
		Cadena& operator +=(const Cadena&);
		//Cadena& operator +=(const char*);
		
		/*Sobrecarga de iteradores*/
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		
		iterator begin();
		iterator end(); 
				
		const_iterator begin() const; 
		const_iterator end() const;
				
		const_iterator cbegin() const;
		const_iterator cend() const;

		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;

		reverse_iterator rbegin();
		reverse_iterator rend();
	
	private:
			
		char *s_;
		unsigned tam_;
	
};

/*	SOBRECARGA OPERADORES BINARIOS	*/	
Cadena operator +(const Cadena&,const Cadena&);
bool operator <(const Cadena&,const Cadena&);
bool operator >(const Cadena&,const Cadena&);
bool operator ==(const Cadena&,const Cadena&);
bool operator <=(const Cadena&,const Cadena&);
bool operator >=(const Cadena&,const Cadena&);
bool operator !=(const Cadena&,const Cadena&);

/*	SOBRECARGA OPERADORES E/S	*/	
std::ostream& operator<<(std::ostream& os, const Cadena&);
std::istream& operator>>(std::istream& is, Cadena&);


// Para P2 y ss.// Especialización de la plantilla hash<T> para definir la
// función hash a utilizar con contenedores desordenados de// Cadena, unordered_[set|map|multiset|multimap]

namespace std{										// Estaremos dentro del espacio de nombres std
	template<>										// Es una especialización de una plantilla para Cadena
	struct hash<Cadena> {							// Es una clase con solo un operador publico
	size_t operator() (const Cadena& cad) const		// El operador función
		{
			hash<string> hs;			// Creamos un objeto hash de string
			const char *p = cad.c_str();	// Obtenemos la cadena de la Cadena
			string s(p);				// Creamos un string desde una cadena
			size_t res = hs(s);			// El hash del string. Como hs.operator()(s);
			return res;					// Devolvemos el hash del string
		}
	};
}
#endif

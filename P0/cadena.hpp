#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;


class Cadena{
	
	public:
		
		/*Constructores*/
		explicit Cadena(int t = 0,char c = ' ');
		Cadena(const Cadena&);
		explicit Cadena(const char*);
		void mostrarcadena() noexcept;
		
		/*Funciones de cadena*/
		size_t length()const noexcept;
		char& at(const int&) const;
		const char* c_str() const noexcept;
		Cadena substr(int, const int&) const; 
		
		/*Sobrecarga de operadores*/
		char& operator[](size_t);
		char operator[](size_t) const;

		Cadena& operator =(const char*);
		Cadena& operator =(const Cadena&);
		Cadena& operator +=(const Cadena&);
		Cadena& operator +=(const char*);
		operator const char*()const{return s_;}

	
		~Cadena();
	private:
		
		
		char *s_;
		int tam_;
	
};

Cadena operator +(const Cadena&,const Cadena&);
bool operator <(const Cadena&,const Cadena&);
bool operator >(const Cadena&,const Cadena&);
bool operator ==(const Cadena&,const Cadena&);
bool operator <=(const Cadena&,const Cadena&);
bool operator >=(const Cadena&,const Cadena&);
bool operator !=(const Cadena&,const Cadena&);

std::ostream& operator<<(std::ostream& os, const Cadena& cdn);

#endif

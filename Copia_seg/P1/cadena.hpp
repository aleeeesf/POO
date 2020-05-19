#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <cstring>
#include <iterator>
using namespace std;


class Cadena{
	
	public:
		
		/*Constructores*/
		explicit Cadena(int t = 0,char c = ' ');
		Cadena(const Cadena&);
		Cadena(const char*);
		Cadena(Cadena&&);
		~Cadena();
		
		void mostrarcadena() noexcept;
		
		/*Funciones de cadena*/
		const size_t length()const noexcept;
		char& at(const int&) const;
		const char* c_str() const{return s_;};
		Cadena substr(int, const int&) const; 
		
		/*Sobrecarga de operadores*/
		
		char& operator[](size_t);
		char operator[](size_t) const;
		Cadena& operator =(const char*);
		Cadena& operator =(Cadena&& cad);
		Cadena& operator =(const Cadena&);
		Cadena& operator +=(const Cadena&);
		//Cadena& operator +=(const char*);
		
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
		int tam_;
	
};

/*	SOBRECARGA OPERADORES BINARIOS	*/	
Cadena operator +(const Cadena&,const Cadena&);
bool operator <(const Cadena&,const Cadena&);
bool operator >(const Cadena&,const Cadena&);
bool operator ==(const Cadena&,const Cadena&);
bool operator <=(const Cadena&,const Cadena&);
bool operator >=(const Cadena&,const Cadena&);
bool operator !=(const Cadena&,const Cadena&);

std::ostream& operator<<(std::ostream& os, const Cadena&);
std::istream& operator>>(std::istream& is, Cadena&);

#endif

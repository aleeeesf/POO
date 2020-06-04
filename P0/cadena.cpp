#include <iostream>
#include <new>
#include "cadena.hpp"


Cadena::Cadena(int t,char c):s_(new char[t+1]),tam_(t)
{

	
	for(int i = 0; i<t; i++){
		
		s_[i] = c;
	}
	
	s_[t] = '\0';
}

Cadena::Cadena(const Cadena& cdn)
{

	
	s_ = new char[cdn.tam_+1];
	tam_ = (int)cdn.tam_;
	
	for(int i = 0; i<tam_; i++){
		
		s_[i] = cdn[i];
	}
	
	s_[tam_] = '\0';
		
}

Cadena::Cadena(const char *str)
{
	
		
	s_ = new char[strlen(str)+1];	//Reservamos memoria para s_
	tam_ = (int)strlen(str);
	
	for(int i = 0; i<tam_; i++){
		
		s_[i] = str[i];
	}
	
	s_[tam_] = '\0';	
}

void Cadena::mostrarcadena() noexcept
{
	
	unsigned i = 0;
	
	while(i <= strlen(this->s_)){
				
		cout<<this->s_[i]<<endl;
		i++;
	}
}

inline size_t Cadena::length()const noexcept{return tam_;}

inline const char* Cadena::c_str() const noexcept{return s_;};

char& Cadena::at(const int& i) const
{
	
	if(i < tam_ )return s_[i];
	else throw std::out_of_range("Error: se sale del rango de caracteres");

}

Cadena Cadena::substr(int ind_,const int& num_)const
{
		
	if(ind_ > tam_ || num_ < 0 || ind_ < 0) throw std::out_of_range("Error: se sale del rango de caracteres");
	
	else{
		
		if(ind_+num_ > tam_) throw std::out_of_range("Error: se sale del rango de caracteres");
		
		else{
			
			Cadena aux;
			int i = 0;
			aux.s_ = new char[num_+1];
			aux.tam_ = num_;
			
			while(i < num_){
			
				if(i == num_) aux.s_[i] = '\0';
				aux.s_[i] = s_[ind_];
				i++;
				ind_++;
			
			}
		
			return aux;
		
		}
	}
}

char& Cadena::operator[](size_t i){return s_[i];}

char Cadena::operator[](size_t i) const {return s_[i];}
 	
	
/*OPERADORES ARITMETICOS*/
Cadena& Cadena::operator =(const char* str)
{

	unsigned i = 0;
	
	delete[] this->s_;
	int t = (int)strlen(str)+1;
	this->s_ = new char[t];
	
	while(i <= strlen(str)){
		
		if(i == strlen(str)) this->s_[i] = '\0';
		else this->s_[i] = str[i];
		i++;
	}

	return *this;
}

Cadena& Cadena::operator =(const Cadena& cdn)
{

	
	if(&cdn == this) return *this;
	
	else
	{
		delete[] s_;		
		s_ = new char[cdn.tam_+1];
		strcpy(s_,cdn.s_);
		tam_ = cdn.tam_;
		
		return *this;
	}
}



Cadena& Cadena::operator +=(const Cadena& cdn)
{
	
	int t = (int)tam_+ cdn.length() +1;
	
	char* aux = new char[t];
	
	for(int i=0; i<tam_; i++) aux[i] = s_[i];
		
	
	for(unsigned i=0; i<cdn.length(); i++)	aux[i+tam_] = cdn[i];
		
	aux[t] = '\0';
	
	delete[] s_;
		
	s_ = new char[t];
	
	
	for(unsigned i=0; i<strlen(aux); i++) s_[i] = aux[i];
		
	s_[t-1] = '\0';
	tam_ = tam_ + cdn.length();
	
	delete[] aux;
	
	return *this;
}


Cadena& Cadena::operator +=(const char* c)
{
	
	int t = (int)tam_+ strlen(c)+1;
	
	char* aux = new char[t];
	
	for(int i=0; i<tam_; i++) aux[i] = s_[i];
		
	
	for(unsigned i=0; i<strlen(c); i++)	aux[i+tam_] = c[i];
		
	aux[t] = '\0';
	
	delete[] s_;
		
	s_ = new char[t];
	
	
	for(unsigned i=0; i<strlen(aux); i++) s_[i] = aux[i];
		
	s_[t-1] = '\0';
	tam_ = tam_ + strlen(c);
	
	delete[] aux;
	
	return *this;
}


Cadena operator +(const Cadena& c1, const Cadena& c2)
{
	
	Cadena aux(c1);
	aux += c2;
	
	return aux;
}




/* OPERADORES BOOLEANOS*/
bool operator <(const Cadena& c1,const Cadena& c2)
{
	
	if( strcmp(c1.c_str(), c2.c_str()) < 0) return true;
	else return false;
}


bool operator >(const Cadena& c1,const Cadena& c2)
{
	
	return (c2 < c1);
}

bool operator ==(const Cadena& c1,const Cadena& c2)
{
	
	return ( strcmp(c1.c_str(), c2.c_str()) == 0);
}

bool operator <=(const Cadena& c1,const Cadena& c2)
{
	
	return (c1 < c2 || c1 == c2);
}

bool operator >=(const Cadena& c1,const Cadena& c2)
{
	
	return (c1 > c2 || c1 == c2);
}

bool operator !=(const Cadena& c1,const Cadena& c2)
{
	
	return !(c1 == c2);
}

std::ostream& operator<<(std::ostream& os, const Cadena& cdn)
{
	
	return os<<cdn.c_str();
	
}

Cadena::~Cadena(){delete[] s_;}


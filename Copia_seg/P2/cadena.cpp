#include "cadena.hpp"
#include <stdexcept>


	/* **************************************** */
	/*				CONSTRUCTORES				*/
	/* **************************************** */
	
Cadena::Cadena(unsigned t,char c):s_(new char[t+1]),tam_(t)
{
		
	for(unsigned i = 0; i<t; i++) s_[i] = c;
		
	s_[t] = '\0';
}

Cadena::Cadena(const char *str)
{
	tam_ = strlen(str);
	s_ = new char[tam_+1];	//Reservamos memoria para s_
	
	for(unsigned i = 0; i<tam_; i++) s_[i] = str[i];	//Copiamos la cadena a s_
		
	s_[tam_] = '\0';	
}

Cadena::Cadena(const Cadena& cdn)
{
	tam_ = 0;
	for(unsigned i = 0; cdn[i] != '\0'; i++) tam_++;
	
	s_ = new char[tam_+1];
	
	
	for(unsigned i = 0; i<tam_; i++)	s_[i] = cdn[i];	//Copiamos todos los elementos de cdn
												// a la nueva cadena
	s_[tam_] = '\0';
		
}

Cadena::Cadena(Cadena&& cdn){
	
	s_ = cdn.s_;
	tam_ = cdn.tam_;
	cdn.s_ = nullptr;	//Apuntamos la cadena antigua a NULL
	cdn.tam_ = 0;
}	

Cadena& Cadena::operator=(Cadena&& cdn){
	
	s_ = cdn.s_;
	tam_ = cdn.tam_;
	cdn.s_ = nullptr;	//Apuntamos la cadena antigua a NULL
	cdn.tam_ = 0;
	return *this;
}	



	/* **************************************** */
	/*			FUNCIONES	CONSULTORAS			*/
	/* **************************************** */


/*
void Cadena::mostrarcadena() noexcept	//Función de prueba
{
	unsigned i = 0;
	
	while(i <= strlen(this->s_)){
				
		cout<<this->s_[i]<<endl;
		i++;
	}
}
*/

//TIPO DE FUNCIÓN: Publica
//POSTCONDICIÓN: Devuelve la longitud de una cadena
inline const unsigned Cadena::length()const noexcept{return tam_;}


//TIPO DE FUNCIÓN: Publica
//POSTCONDICIÓN: Devuelve posición de la cadena
char& Cadena::at(unsigned i) const
{
	
	if(i < tam_ )return s_[i];	//Comprobamos que está en una posición válida
	else throw std::out_of_range("Error: se sale del rango de caracteres");

}
	
//TIPO DE FUNCIÓN: Publica
//POSTCONDICIÓN: Extrae una parte de la cadena. Recibe como primer parámetro el índice
//				 y como segundo parámetro el número de caracteres a extrar
Cadena Cadena::substr(unsigned ind_,const int& num_)const
{
	
	if(ind_ > tam_ || num_ < 0 ) 	//Comprobamos que el índice y el tamaño introducidos sean validos
		throw std::out_of_range("Error: se sale del rango de caracteres");
	
	else{
		
		if(ind_+num_ > tam_) 	//comprobamos que no salga del rango de caracteres de la cadena
			throw std::out_of_range("Error: se sale del rango de caracteres");
		
		else{
			
			Cadena aux;
			int i = 0;
			delete[] aux.s_;
			aux.s_ = new char[num_+1];
			aux.tam_ = num_;
			
			while(i < num_){	//Sustraemos la parte de la cadena que deseamos
			
				aux.s_[i] = s_[ind_];
				i++;
				ind_++;
			
			}
			aux.s_[i] = '\0';
			return aux;
		
		}
	}
}


	/* **************************************** */
	/*		  SOBRECARGA DE OPERADORES 			*/
	/* **************************************** */
	
char& Cadena::operator[](unsigned i){return s_[i];}

char Cadena::operator[](unsigned i) const {return s_[i];}
 	
Cadena& Cadena::operator =(const char* str)
{

	delete[] s_;
	s_ = new char[strlen(str)+1];
	tam_= strlen(str);
	
	for(unsigned i=0; i<strlen(str)+1; ++i) s_[i] = str[i];	//Copiamos la cadena recibida al 
	s_[strlen(str)+1] = '\0';								//atributo s_ de la clase
	
	return *this;
}

Cadena& Cadena::operator =(const Cadena& cdn)
{
	if(&cdn == this) return *this;	//Evitamos la autoasignación
	
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
	
	int t = tam_+ cdn.length() + 1;
	
	char* aux = new char[t];
	
	strcpy(aux,s_);			//aux = s_
	
	delete[] s_;
	s_ = new char[t];
	
	strcpy(s_,aux);			//s_ = aux
	strcat(s_, cdn.s_);		//s_ += cdn_s:
	
	tam_ = tam_+ cdn.length();
	
	delete[] aux;
	
	return *this;
}

/*
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
*/

Cadena operator +(const Cadena& c1, const Cadena& c2)
{
	Cadena aux(c1);
	aux += c2;
	
	return aux;
}



	/* **************************************** */
	/*	SOBRECARGA OPERADORES DE COMPARACIÓN	*/
	/* **************************************** */
	
	
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
	return (c2 < c1 || c1 == c2);
}

bool operator !=(const Cadena& c1,const Cadena& c2)
{	
	return !(c1 == c2);
}



	/* **************************************** */
	/*		SOBRECARGA OPERADORES DE E/S		*/
	/* **************************************** */
	
	
	
std::ostream& operator<<(std::ostream& os, const Cadena& cdn)
{	
	return os<<cdn.c_str();
}

std::istream& operator>>(std::istream& is, Cadena& cdn){
	
	char* strng = new char[33]{'\0'};	//Si no se recibe ninguna cadena se rellena is con '\0'
										// así permitimos una entrada vacía
	is.width(33);	//32 espacios es el max. permitido +1 para '\0'
	is>>strng;		
	cdn = strng;
	delete[] strng;

	return is;
	
}


	/* **************************************** */
	/*			SOBRECARGA ITERADORES			*/
	/* **************************************** */
	
	
	
Cadena::iterator Cadena::begin() {return s_;}
Cadena::iterator Cadena::end() {return s_+tam_;}
				
Cadena::const_iterator Cadena::begin() const {return s_;}
Cadena::const_iterator Cadena::end() const {return s_+tam_;}
				
Cadena::const_iterator Cadena::cbegin() const {return s_;} 
Cadena::const_iterator Cadena::cend() const {return s_+tam_;}

Cadena::const_reverse_iterator Cadena::rbegin() const {return const_reverse_iterator(end());}
Cadena::const_reverse_iterator Cadena::rend() const {return const_reverse_iterator(begin());}
Cadena::const_reverse_iterator Cadena::crbegin() const {return const_reverse_iterator(cend());}
Cadena::const_reverse_iterator Cadena::crend() const {return const_reverse_iterator(cbegin());}

Cadena::reverse_iterator Cadena::rbegin() {return reverse_iterator(end());}
Cadena::reverse_iterator Cadena::rend() {return reverse_iterator(begin());}



	/* **************************************** */
	/*				  DESTRUCTOR				*/
	/* **************************************** */
	
Cadena::~Cadena(){tam_ = 0; delete[] s_;}


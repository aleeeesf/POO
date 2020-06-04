#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

using namespace std;

int main(){

try{
 Fecha hoy("22/03");
}catch(Fecha::Invalida e){
	cout<<e.por_que()<<endl;
}	
	
}

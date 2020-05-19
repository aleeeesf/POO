#include <iostream>
#include "tarjeta.hpp"

using namespace std;

int main(){

try{
	Numero a("353011133330000 0");
}catch(Numero::Incorrecto e){cout<<e.razon();}
	//cout<<a<<endl;
	return 0;
}

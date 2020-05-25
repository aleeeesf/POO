#include <iostream>
#include <sstream>
#include "articulo.hpp"
#include "cadena.hpp"
#include <set>
using namespace std;

int main(){
	  Autor autor1("Pepito", "Uematsu", "C/brasil");
  const Cadena sReferenciaLibro = "110", sTituloLibro = "Fundamentos de C++";
	Autor autor2("María", "Martínez", "Algeciras");
    Articulo::Autores autores2 { &autor1, &autor2 };
    const Libro libro(autores2, "110","Fundamentos de C++", "11/12/1998",
                      14.50, 100, 5);

	//stringstream buffer;
    cout<< libro;
    //const char* f = buffer.str().c_str();
    //if(strcmp(f,"[110] \"Fundamentos de C++\", de Uematsu, Martínez. 1998. 35,95 €\n\t650 págs., 100 unidades.") == 0 ) cout<<"si!";
    
   // cout<<f<<endl;
    cout<<"[110] \"Fundamentos de C++\", de Uematsu, Martínez. 1998. 35,95 €\n\t650 págs., 100 unidades.";
    /*
    string sLibro = os.str();
    fct_chk_eq_str(sLibro.c_str(),
                   "[110] \"Fundamentos de C++\", de Uematsu, Martínez. "
		   "1998. 35,95 €\n\t650 págs., 100 unidades.");
    os.str("");
    libro.impresion_especifica(os);
    sLibro = os.str();
    fct_chk_eq_str(sLibro.c_str(), "650 págs., 100 unidades.");*/
}
//..

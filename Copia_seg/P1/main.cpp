#include <iostream>
#include <cstring>
#include <sstream>
#include "cadena.hpp"
#include "fecha.hpp"

using namespace std;

int main(){

   Cadena a("Cada cual,"), b(" en su corral");
    a += b;
    cout<<a<<endl;

}

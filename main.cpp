#include <iostream>
#include<vector>
#include <math.h>
#include <cassert>
#include <sstream>
using namespace std;
char Scale[]="CKF";
struct Temperature {
    double temp;
    char scale;
};
istream & operator >> (istream& in,Temperature& Temp)
{
in>>Temp.temp;
in>>Temp.scale;
}
void test_temperature_input(){
    Temperature Temp;
    string inp="10C";
    istringstream iss(inp);
    iss>>Temp;
    assert(Temp.temp==10);
    assert(Temp.scale=='C');
    istringstream iss1("-400F");
    iss1>>Temp;
    assert(Temp.temp==-400);
    assert(Temp.scale=='F');
    istringstream iss2("0K");
    iss2>>Temp;
    assert(Temp.temp==0);
    assert(Temp.scale=='K');


}
double convert (const Temperature& Temp,char scale_to){
    double Kelvins;
    switch (Temp.scale) {
    case 'K':
        break;
    case 'F':Kelvins+=((9.0/5)*(Temp.temp-273)+32);
        break;
    case 'C':Kelvins+=-273.15;
        break;
    }

}
int
main() {
    test_temperature_input();
}
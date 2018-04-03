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
    case 'F':Kelvins+=(5*(Temp.temp-32))/9+273.15;
        break;
    case 'C':Kelvins+=-273.15;
        break;


    }
    switch (scale_to) {
    case 'K':
    case'k':
        return Kelvins;
    case 'C':
    case'c':
        return Kelvins -273.15;
    case'F':
    case'f':
        return Kelvins-((9.0/5)*(Temp.temp-273.15)+32);

}

}
bool operator < (const Temperature & lhs, const Temperature & rhs) {
    return convert(lhs, 'K') < convert(rhs, 'K');
}
Temperature operator-(const Temperature & lhs,const Temperature & rhs)
{
    Temperature ret_temp;
    ret_temp.temp=convert(lhs,'K')-convert(rhs,'K');
    ret_temp.scale='K';
    return ret_temp;
}
Temperature operator/(const Temperature & lhs,const Temperature & rhs )
{

    Temperature ret_temp;
    ret_temp.temp=convert(lhs,'K')/convert(rhs,'K');
    ret_temp.scale='K';
    return ret_temp;

}
int
main() {
    test_temperature_input();
        size_t number_count;
        size_t kolvostolb;

        size_t i,x,h,elem;
        double min,max,maxh,minh;
        cerr<<"Vvedite kolichestvo peremennih\n";
        cin>>number_count;
        cerr<<"Vvedite kolvo stolbcov\n";
        cin>>kolvostolb;
        cerr<<"Vvedite peremenie\n";
        vector<double>D(number_count);
        vector<double>col_count(kolvostolb);
        for(int i=0;i<number_count;i++)
        {
            cin>>D[i];

        }


        min=D[0];
        for(int i=0;i<number_count;i++)
            if(min>D[i])
                min=D[i];
        max=D[0];
        for(int i=0;i<number_count;i++)
            if(max< D[i])
                max=D[i];
// начало удаления дубликатов
        for(int j=0; j<D.size() - 1;j++)
        {
            for(int i=j+1; i<D.size();i++)
            {
                if(D[i] == D[j]){
                    D.erase(D.begin() + i);
                    i--;
                }
            }
        } //конец удаления дубликатов
        cout << "mass: ";
        for (double x:D){cout << x;}
        cout<<"\n";

        for(int i=0;i<D.size();i++) {
            x=D[i];
            size_t index;

            if (x == max)
            {
                index = kolvostolb - 1;
            }
            else {
                double val = ((x - min) / (max - min) * kolvostolb);
                index = std::trunc(val);
            }

            col_count[index]=col_count[index]+1;
        }
        maxh=col_count[0];
        for(int i=0;i<col_count.size();i++)
            if(maxh< col_count[i])
                maxh=col_count[i];
/*Гистограмма должна целиком умещаться в 80 символов по ширине.
     Наименьший ненулевой столбец должен быть высотой в одну ячейку,
    если при этом самый высокий столбец умещается в отведенное пространство.
                                                                Высоты столбцов ожидаются до 1000.*/
        if(maxh>80) {
            for (int i = 0; i < col_count.size(); i++){
                col_count[i] = 80 / maxh * col_count[i];}
        }
        else
        {
            minh=col_count[0];
            for(int i=0;i<col_count.size();i++)
            {
                if(minh> col_count[i])
                    minh=col_count[i];


            }
            for(int i=0;i<col_count.size();i++)
            {
                if(col_count[i]==minh)
                    col_count[i]=1;
            }
        }

        for(int i=0;i<kolvostolb;i++){
            h=col_count[i];
            if(h==0)
                h=1;
            cout<<h<<"|";
            for(int j=1;j<=h;j++){
                cout<<"*";
            }
            cout<<"\n";
        }
        system("pause");
    }

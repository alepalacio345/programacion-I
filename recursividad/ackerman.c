#include <stdio.h>


int ackerman(int m, int n);




int main(){

    int m = 2, n = 2, rs;

    rs = ackerman(2,2);

    printf("%i ",rs);


    return 0;
}



//esta version de ackermamn es una mierda hacer la mejor que es mas corta y con menos pasos
int ackerman(int m, int n){

    if(m == 0){
        return n + 1;
    }else{

        if((m != 0) && (n == 0)){
            return ackerman(m - 1, 1);
        }else{
            if((m != 0) && (n != 0)){
                return ackerman(m - 1, ackerman(m,n - 1));
            }
        }


    }



}
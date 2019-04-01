//  main.cpp
//  HW6
//
//  Created by Cu Hauw Hung on 10/26/17.
//  Copyright © 2017 Cu Hauw Hung. All rights reserved.
//

using namespace std;
#include <iostream>
#include <fstream>
#include <new>
#include <string>
#include <cmath>
#include <set>
#include <algorithm>



unsigned GetNumberOfDigits (unsigned i){
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

int Prod(int u, int v){
    
    int x, y, w, z, m, n, Temp1, Threshold=2;
    
    int digitsU = GetNumberOfDigits(u);
    int digitsV = GetNumberOfDigits(v);
    
	n = max({ digitsU, digitsV });
    
    if (u== NULL && v == NULL){
        return NULL;
    }
    else if(n<=Threshold){
        return u*v;
    }
    
    else {
        m=n/2;
        Temp1=(pow(10,m));
        
        x = u/Temp1;
        y = u % Temp1;
        w = v/Temp1;
        z = v % Temp1;
    }

    return Prod(x,w) * pow(10,2*m) + (Prod(x,z)+Prod(y,w)) * pow(10,m) + Prod(y,z);
    
}

int main(){
    
    int Val1, Val2, AlgValue, ComValue;
    
    cout << "Please enter two nonnegative integers" << endl;
    cin >> Val1;
    cin >> Val2;
    
    while (Val1 < 0 || Val2 < 0){
        cout << "You inserted invalid numbers. Please enter two nonnegative integers" << endl;
        cin >> Val1;
        cin >> Val2;
    }

    AlgValue = Prod(Val1, Val2);
    ComValue = Val1*Val2;
    
    cout << "Result determined using the large arithmetic algorithm: " << AlgValue << endl;
    cout << "Result determined using the standard algorithm        : " << ComValue << endl;
    
    if (AlgValue!=ComValue){
        cout << "Your algorithm is not working well. The answer calculated is different" << endl;
		system("pause");
		exit(1);
    }

	system("pause");
	exit(1);

}



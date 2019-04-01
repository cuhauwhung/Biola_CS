#include <iostream>
#include <vector>
using namespace std;

struct matrixSize{
    int row;
    int column;
};

void order(int i, int j, vector<vector<double>> &P){
    double K;
    if (i==j){
        cout << "M" << i+1;
    }
    else{
        K=P[i][j];
        cout << "(";
        order(i,K-1, P);
        order(K,j, P);
        cout << ")";
    }
}

void ChainMatrixMult(int n, int* r, vector<vector<double>> &M, vector<vector<double>> &P){
    int i=0, j=0;
    for (int diagonal=1; diagonal<=n-1; diagonal++){
        for (i=0; i<n-diagonal; i++){
            j=i+diagonal;
            M[i][j]=INT_MAX;
            for (int k=i; k<j; k++){
                if (M[i][k]+M[k+1][j]+r[i]*r[k+1]*r[j+1]<M[i][j]){
                    M[i][j]=M[i][k]+M[k+1][j]+r[i]*r[k+1]*r[j+1];
                    P[i][j]=k+1;
                }
            }
        }
    }
}

void OutputValues(vector<vector<double>> Temp){
    for (int a=0; a<Temp.size(); a++){
        for (int b=0; b<Temp[a].size(); b++){
            if (b!=Temp.size()-1){
                cout << Temp[a][b] << " -- ";
            }
            else{
                cout << Temp[a][b];
            }
        }
        cout << endl;
    }
}

int main(){
    
    // Definition
    int n, temp=0;
    int* array;
    vector<vector<double>> M; vector<vector<double>> P;
    
//    array[0]=5; array[1]=2; array[2]=3; array[3]=4; array[4]=6;
//    n=4;

    cout << "Enter the total number of matrices to be multiplied" << endl;
    cin >> n;
    array = new int[n+1];
    
    // Resizing
    M.resize(n); P.resize(n);
    for (int i = 0; i <n; i++){
        M[i].resize(n);
        P[i].resize(n);
    }

    for (int i=0; i<n; i++){
        cout << "Enter the dimension for the " << i+1 << "-th matrix" << endl;
        cin >> array[i]; cin >> temp;
    }
    array[n]=temp;

    ChainMatrixMult(n, array, M, P);

    cout << "Here is the M and P matrix respsectively: " << endl;
    OutputValues(M);
    cout << "###################### " << endl;
    OutputValues(P);
    cout << "###################### " << endl;

    cout << "The following shows the optimal parenthesizations of matrices: " << endl;
    order(0, 3, P);
    cout << endl;
    
    system("pause");
    
}


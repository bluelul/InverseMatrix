///////////////////////////////////////////////
//----Efficiently solve Ax = b where A is----// 
//------a 4x4 matrix and b is 4x1 vector-----//
///////////////////////////////////////////////

//-------------------Source-----------------//
//https://stackoverflow.com/questions/23445695/efficiently-solve-ax-b-where-a-is-a-4x4-symmetric-metrix-and-b-is-4x1-vector

#include <iostream>
using namespace std;
void solver_4D(double* mat, double* vec);
void getsub(double* sub, double* mat, double* vec);
int main() {
    double A[16]={ 2,1,2,1,
                      1,6,7,8,
                      2,10,11,12,
                      1,14,15,16};
    double B[4]={1,2,3,4};   
    solver_4D(A,B);
    cout<<B[0]<<' '<<B[1]<<' '<<B[2]<<' '<<B[3]<<endl;
	return 0;
}
void getsub(double* sub, double* mat, double* vec)
{
*(sub++) = *(mat  ) * *(mat+5) - *(mat+1) * *(mat+4);
*(sub++) = *(mat  ) * *(mat+6) - *(mat+2) * *(mat+4);
*(sub++) = *(mat  ) * *(mat+7) - *(mat+3) * *(mat+4);
*(sub++) = *(mat  ) * *(vec+1) - *(vec  ) * *(mat+4);
*(sub++) = *(mat+1) * *(mat+6) - *(mat+2) * *(mat+5);
*(sub++) = *(mat+1) * *(mat+7) - *(mat+3) * *(mat+5);
*(sub++) = *(mat+1) * *(vec+1) - *(vec  ) * *(mat+5);
*(sub++) = *(mat+2) * *(mat+7) - *(mat+3) * *(mat+6);
*(sub++) = *(mat+2) * *(vec+1) - *(vec  ) * *(mat+6);
*(sub  ) = *(mat+3) * *(vec+1) - *(vec  ) * *(mat+7);
}

void solver_4D(double* mat, double* vec)
{
    double a[10], b[10]; // values of 20 specific 2D subdeterminants

    getsub(&a[0], mat, vec);
    getsub(&b[0], mat+8, vec+2);

    *(vec++) = a[5]*b[8] + a[8]*b[5] - a[6]*b[7] - a[7]*b[6] - a[4]*b[9] - a[9]*b[4];
    *(vec++) = a[1]*b[9] + a[9]*b[1] + a[3]*b[7] + a[7]*b[3] - a[2]*b[8] - a[8]*b[2];
    *(vec++) = a[2]*b[6] + a[6]*b[2] - a[0]*b[9] - a[9]*b[0] - a[3]*b[5] - a[5]*b[3];
    *(vec  ) = a[0]*b[8] + a[8]*b[0] + a[3]*b[4] + a[4]*b[3] - a[6]*b[1] - a[1]*b[6];

    register double idet = 1./(a[0]*b[7] + a[7]*b[0] + a[2]*b[4] + a[4]*b[2] - a[5]*b[1] - a[1]*b[5]);

    *(vec--) *= idet;
    *(vec--) *= idet;
    *(vec--) *= idet;
    *(vec  ) *= idet;
}

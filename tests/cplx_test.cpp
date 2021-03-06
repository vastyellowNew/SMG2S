//#include "parVectorMap.cc"
#include "../parMatrix/parMatrixSparse.h"
#include <math.h>
#include <complex.h>
#include "../utils/MPI_DataType.h"
#ifdef __APPLE__
#include <sys/malloc.h>
#else
#include <malloc.h>
#endif

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;

    double start, end;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    //MPI_Barrier(MPI_COMM_WORLD);
    
    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
           " out of %d processors\n",
           processor_name, world_rank, world_size);


    int probSize = 10;
    int span, lower_b, upper_b;

    span = int(floor(double(probSize)/double(world_size)));

    printf("span = %d\n", span);
    if(world_rank == world_size - 1){
	lower_b = world_rank * span;
	upper_b = probSize - 1 + 1;
    }
    else{
	lower_b = world_rank * span;
	upper_b = (world_rank + 1) * span - 1 + 1;
    }

    printf("Proc. %d   Lower bound = %d   Upper bound = %d \n",world_rank, lower_b , upper_b ) ;

    std::complex<double> a = 1.0, c = 2.0; std::complex<double> b =2.0;

  
    parVector<std::complex<double>,int> *vec = new parVector<std::complex<double>,int>(MPI_COMM_WORLD, lower_b, upper_b);
    parVector<std::complex<double>,int> *prod = new parVector<std::complex<double>,int>(MPI_COMM_WORLD, lower_b, upper_b);
    parVector<std::complex<double>,int> *prod2 = new parVector<std::complex<double>,int>(MPI_COMM_WORLD, lower_b, upper_b);

    MPI_Scalar_Setup<double>();

    vec->SetTovalue(a); //1.0,1.0...1.0

    prod->SetTovalue(0.0);

    prod2->SetTovalue(0.0);

    MPI_Barrier(MPI_COMM_WORLD);

    vec->VecAdd(prod); //2.0,2.0...
   
    MPI_Barrier(MPI_COMM_WORLD);

    vec->VecScale(c); //4.0,4.0...

    std::complex<double> dot_local, dot;

    dot_local = vec->VecDot(prod);

    MPI_Allreduce(&dot_local, &dot, 1, MPI_DOUBLE, MPI_SUM,
                  MPI_COMM_WORLD);

    if(world_rank == 0){printf("vecdot done\n");}

    MPI_Barrier(MPI_COMM_WORLD);

//    int as = vec->GetArraySize();

//    if(world_rank == 0){printf("vector array Size  = %d\n", as);}

    MPI_Barrier(MPI_COMM_WORLD);

    std::complex<double> *va = vec->GetArray();

    MPI_Barrier(MPI_COMM_WORLD);

    vec->VecScale(c); //8.0,8.0...

    //vec->VecView();

    //Matrix Initialization

    parMatrixSparse<std::complex<double>,int> *Am = new parMatrixSparse<std::complex<double>,int>(vec,prod);
    parMatrixSparse<std::complex<double>,int> *Bm = new parMatrixSparse<std::complex<double>,int>(vec,prod);

    if(world_rank == 0){printf("Matrix Initialized\n");}

    MPI_Barrier(MPI_COMM_WORLD);

//    printf("\n\nprc %d: LOWER_X = %d, LOWER_Y = %d, UPPER_X = %d, UPPER_Y = %d \n", world_rank, Am->GetXLowerBound(), Am->GetYLowerBound(), Am->GetXUpperBound(), Am->GetYUpperBound());


    for(int j=6; j < probSize; j++){
        Am->SetValue(j-6,j,1);
        Am->SetValue(j, j-6,2);
    }

    for(int j=3; j < probSize; j++){
        Am->SetValue(j-3,j,1);
        Am->SetValue(j, j-3,2);
    }

/*
    for(int j=100; j < probSize; j++){
        Am->SetValue(j-100,j,1);
        Am->SetValue(j, j-100,2);
    }
*/
    for(int j=0; j < probSize; j++){
        Am->SetValue(j,j,1);
    }

    Am->SetDiagonal(vec);

/*
    for(int j=0; j < probSize; j++){
        Bm->SetValue(j,j,0);
    }
*/

/*
    for(int j=0; j < probSize - 5; j++){
        Am->SetValue(j,j+5,1.0);
    }
*/
//    double x, y;

 //   x = Am->GetValue(10,11);

   // y = Am->GetValue(10,11);

    //printf("Prc %d: x = %f, y = %f \n", world_rank, x, y);

    MPI_Barrier(MPI_COMM_WORLD);

    Am->MatView();

    MPI_Barrier(MPI_COMM_WORLD);

    Am->ConvertToCSR();
	
    Am->MatAXPY(Am, 2.0);

    MPI_Barrier(MPI_COMM_WORLD);

    Am->MatScale(4.0);

    MPI_Barrier(MPI_COMM_WORLD);

    Am->ConvertToCSR();

    MPI_Barrier(MPI_COMM_WORLD);

    Am->MatView();

    MPI_Barrier(MPI_COMM_WORLD);

    start = MPI_Wtime();

    Am->FindColsToRecv();
    
    MPI_Barrier(MPI_COMM_WORLD);

    Am->SetupDataTypes();

    MPI_Barrier(MPI_COMM_WORLD);

 //   Am->TestCommunication(vec,prod);

//    Am->ELL_MatVecProd(vec,prod);

    MPI_Barrier(MPI_COMM_WORLD);


//    if(world_rank == 0){printf("print SPMV results\n");}
 
//    prod->VecView();

    MPI_Barrier(MPI_COMM_WORLD);

//    start = MPI_Wtime();

    Am->CSR_MatVecProd(vec,prod2);

    end = MPI_Wtime();

    double t2 = end - start;

    if(world_rank == 0) {printf("CSR time = %1.6f\n", t2);}

    MPI_Barrier(MPI_COMM_WORLD);

    prod2->VecView();

    MPI_Finalize();

    return 0;
}


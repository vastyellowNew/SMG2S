/*

MIT License

Copyright (c) 2019 Xinzhe WU

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "smg2s/smg2s.h"
#include "smg2s/smg2s_nonsymmetric.h"
#include <math.h>
#include <complex>
#include <cstdlib>
#include <string.h>
#include "utils/logo.h"
#include "utils/utils.h"
#include <string>
#include <typeinfo>  

#ifdef __APPLE__
#include <sys/malloc.h>
#else
#include <malloc.h>
#endif

int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int size;

    double start, end, time;

    bool non_sym = false;

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {logo(1.1);}

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    //MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0) printf("INFO ]> Starting ... \n");

    // Print off a hello world message
    if(rank == 0) printf("INFO ]> The MPI Comm World Size is %d\n", size);

    if (argc < 5) {
        // Tell the user how to run the program
        if(rank == 0){
            show_usage(argv[0]);
        }
        MPI_Finalize();
        return 0;
    }

    char *dim, *l, *c;

    std::string spectrum = " ";

    std::string mattype = " ";

    std::string floattype = " ";

    std::string integertype = " ";    

    for (int i =0; i < argc; i++){

        if (strcasecmp(argv[i],"-SIZE")==0){
                dim = argv[i+1] ;
        }
        if (strcasecmp(argv[i],"-L")==0){
                l = argv[i+1] ;
        }

        if (strcasecmp(argv[i],"-C")==0){
                c = argv[i+1] ;
        }

        if (strcasecmp(argv[i],"-SPTR")==0){
                spectrum.assign(argv[i+1]);
        }

        if (strcasecmp(argv[i],"-mattype")==0){
                mattype.assign(argv[i+1]);
        }

        if (strcasecmp(argv[i],"-floattype")==0){
                floattype.assign(argv[i+1]);
        }

        if (strcasecmp(argv[i],"-integertype")==0){
                integertype.assign(argv[i+1]);
        }
    }

    if (floattype.compare("FLOAT") != 0 && floattype.compare("DOUBLE") != 0 && floattype.compare("CPLX_DOUBLE") != 0 && floattype.compare("CPLX_FLOAT") != 0){
        return 0;
    }

    if (integertype.compare("INT") != 0 && integertype.compare("_INT64") != 0){
        return 0;
    }


    MPI_Barrier(MPI_COMM_WORLD);

    if (mattype.compare("non-sym") == 0){
        non_sym = true;
    }

    /*ONLY Non Hermitan cases*/

    /*complex double + int*/


    if (floattype.compare("CPLX_DOUBLE") + integertype.compare("INT") == 0){

        int probSize, lbandwidth, length;

        probSize = atoi(dim);
        lbandwidth = atoi(l);
        length = atoi(c);

        Nilpotency<int> nilp;

        nilp.NilpType1(length,probSize);

        parMatrixSparse<std::complex<double>,int> *Mt2;

        start = MPI_Wtime();

        Mt2 =  smg2s<std::complex<double>,int>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);

        end = MPI_Wtime();

        time = end - start;

        if(rank == 0){
            border_print2();
            center_print ( "SMG2S Finish the Generation of Non Hermitian Matrix",100 );
            
            std::cout << "\n                              Size = "<< demical<int>(probSize) <<"e^" << pw<int>(probSize) << ", L = " << l << ", C = " << c << ", Proc = " << size << "\n" << std::endl;
            std::cout <<  "                               Data Types for the test: " << floattype <<", "<< integertype <<  "\n" << std::endl;
            printf ( "                                  SMG2S Time is %f seconds \n", time );
            border_print2();
        }

    } else if (floattype.compare("CPLX_FLOAT") + integertype.compare("INT") == 0){

        int probSize, lbandwidth, length;

        probSize = atoi(dim);
        lbandwidth = atoi(l);
        length = atoi(c);

        Nilpotency<int> nilp;

        nilp.NilpType1(length,probSize);

        parMatrixSparse<std::complex<float>,int> *Mt2;

        start = MPI_Wtime();

        Mt2 =  smg2s<std::complex<float>,int>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);

        end = MPI_Wtime();

        time = end - start;

        if(rank == 0){
            border_print2();
            center_print ( "SMG2S Finish the Generation of Non Hermitian Matrix",100 );
            
            std::cout << "\n                              Size = "<< demical<int>(probSize) <<"e^" << pw<int>(probSize) << ", L = " << l << ", C = " << c << ", Proc = " << size << "\n" << std::endl;
            std::cout <<  "                               Data Types for the test: " << floattype <<", "<< integertype <<  "\n" << std::endl;
            printf ( "                                  SMG2S Time is %f seconds \n", time );
            border_print2();
        }

    } else if (floattype.compare("CPLX_DOUBLE") + integertype.compare("_INT64") == 0){

        __int64_t probSize, lbandwidth, length;

        probSize = atoi(dim);
        lbandwidth = atoi(l);
        length = atoi(c);

        Nilpotency<__int64_t> nilp;

        nilp.NilpType1(length,probSize);

        parMatrixSparse<std::complex<double>,__int64_t> *Mt2;

        start = MPI_Wtime();

        Mt2 =  smg2s<std::complex<double>,__int64_t>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);

        end = MPI_Wtime();

        time = end - start;

        if(rank == 0){
            border_print2();
            center_print ( "SMG2S Finish the Generation of Non Hermitian Matrix",100 );
            
            std::cout << "\n                              Size = "<< demical<int>(probSize) <<"e^" << pw<int>(probSize) << ", L = " << l << ", C = " << c << ", Proc = " << size << "\n" << std::endl;
            std::cout <<  "                               Data Types for the test: " << floattype <<", "<< integertype <<  "\n" << std::endl;
            printf ( "                                  SMG2S Time is %f seconds \n", time );
            border_print2();
        }

    } else if (floattype.compare("CPLX_FLOAT") + integertype.compare("_INT64") == 0){

        __int64_t probSize, lbandwidth, length;

        probSize = atoi(dim);
        lbandwidth = atoi(l);
        length = atoi(c);

        Nilpotency<__int64_t> nilp;

        nilp.NilpType1(length,probSize);

        parMatrixSparse<std::complex<float>,__int64_t> *Mt2;

        start = MPI_Wtime();

        Mt2 =  smg2s<std::complex<float>,__int64_t>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);

        end = MPI_Wtime();

        time = end - start;

        if(rank == 0){
            border_print2();
            center_print ( "SMG2S Finish the Generation of Non Hermitian Matrix",100 );
            
            std::cout << "\n                              Size = "<< demical<int>(probSize) <<"e^" << pw<int>(probSize) << ", L = " << l << ", C = " << c << ", Proc = " << size << "\n" << std::endl;
            std::cout <<  "                               Data Types for the test: " << floattype <<", "<< integertype <<  "\n" << std::endl;
            printf ( "                                  SMG2S Time is %f seconds \n", time );
            border_print2();
        }

    } else if (floattype.compare("DOUBLE") + integertype.compare("INT") == 0){


    /*Both Non symmetric and Non Hermitan cases*/
    
    /*double + int*/

        std::cout << floattype.compare("DOUBLE") + integertype.compare("INT") << std::endl;

        int probSize, lbandwidth, length;

        probSize = atoi(dim);
        lbandwidth = atoi(l);
        length = atoi(c);

        Nilpotency<int> nilp;

        nilp.NilpType1(length,probSize);

        parMatrixSparse<double,int> *Mt2;

        start = MPI_Wtime();

        if(non_sym){
            Mt2 =  smg2s<double,int>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);
        } else {
            Mt2 =  smg2s_nonsymmetric<double,int>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);
        }

        end = MPI_Wtime();

        time = end - start;

         if(rank == 0){
            border_print2();
            if(non_sym){
                center_print ( "SMG2S Finish the Generation of Non Symmetric Matrix",100 );
            } else {
                center_print ( "SMG2S Finish the Generation of Non Hermitian Matrix",100 );
            }  
            std::cout << "\n                              Size = "<< demical<int>(probSize) <<"e^" << pw<int>(probSize) << ", L = " << l << ", C = " << c << ", Proc = " << size << "\n" << std::endl;
            std::cout <<  "                               Data Types for the test: " << floattype <<", "<< integertype <<  "\n" << std::endl;
            printf ( "                                  SMG2S Time is %f seconds \n", time );
            border_print2();
        }

    } else if (floattype.compare("FLOAT") + integertype.compare("INT") == 0){

    /*float + int*/

        int probSize, lbandwidth, length;

        probSize = atoi(dim);
        lbandwidth = atoi(l);
        length = atoi(c);

        Nilpotency<int> nilp;

        nilp.NilpType1(length,probSize);

        parMatrixSparse<float,int> *Mt2;

        start = MPI_Wtime();

        if(non_sym){
            Mt2 =  smg2s<float,int>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);
        } else {
            Mt2 =  smg2s_nonsymmetric<float,int>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);
        }

        end = MPI_Wtime();

        time = end - start;

        if(rank == 0){
            border_print2();
            if(non_sym){
                center_print ( "SMG2S Finish the Generation of Non Symmetric Matrix",100 );
            } else {
                center_print ( "SMG2S Finish the Generation of Non Hermitian Matrix",100 );
            }  
            std::cout << "\n                              Size = "<< demical<int>(probSize) <<"e^" << pw<int>(probSize) << ", L = " << l << ", C = " << c << ", Proc = " << size << "\n" << std::endl;
            std::cout <<  "                               Data Types for the test: " << floattype <<", "<< integertype <<  "\n" << std::endl;
            printf ( "                                  SMG2S Time is %f seconds \n", time );
            border_print2();
        }

    } else if (floattype.compare("DOUBLE") + integertype.compare("_INT64") == 0){



    /*double + int64*/

        __int64_t probSize, lbandwidth, length;

        probSize = atoi(dim);
        lbandwidth = atoi(l);
        length = atoi(c);

        Nilpotency<__int64_t> nilp;

        nilp.NilpType1(length,probSize);

        parMatrixSparse<double,__int64_t> *Mt2;

        start = MPI_Wtime();

        if(non_sym){
            Mt2 =  smg2s<double,__int64_t>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);
        } else {
            Mt2 =  smg2s_nonsymmetric<double,__int64_t>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);
        }

        end = MPI_Wtime();

        time = end - start;

        if(rank == 0){
            border_print2();
            if(non_sym){
                center_print ( "SMG2S Finish the Generation of Non Symmetric Matrix",100 );
            } else {
                center_print ( "SMG2S Finish the Generation of Non Hermitian Matrix",100 );
            }  
            std::cout << "\n                              Size = "<< demical<int>(probSize) <<"e^" << pw<int>(probSize) << ", L = " << l << ", C = " << c << ", Proc = " << size << "\n" << std::endl;
            std::cout <<  "                               Data Types for the test: " << floattype <<", "<< integertype <<  "\n" << std::endl;
            printf ( "                                  SMG2S Time is %f seconds \n", time );
            border_print2();
        }

    } else if (floattype.compare("FLOAT") + integertype.compare("_INT64") == 0){

    /*float + int64*/

        __int64_t probSize, lbandwidth, length;

        probSize = atoi(dim);
        lbandwidth = atoi(l);
        length = atoi(c);

        Nilpotency<__int64_t> nilp;

        nilp.NilpType1(length,probSize);

        parMatrixSparse<float,__int64_t> *Mt2;

        start = MPI_Wtime();

        if(non_sym){
            Mt2 =  smg2s<float,__int64_t>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);
        } else {
            Mt2 =  smg2s_nonsymmetric<float,__int64_t>(probSize, nilp,lbandwidth, spectrum, MPI_COMM_WORLD);
        }

        end = MPI_Wtime();

        time = end - start;

        if(rank == 0){
            border_print2();
            if(non_sym){
                center_print ( "SMG2S Finish the Generation of Non Symmetric Matrix",100 );
            } else {
                center_print ( "SMG2S Finish the Generation of Non Hermitian Matrix",100 );
            }  
            std::cout << "\n                              Size = "<< demical<int>(probSize) <<"e^" << pw<int>(probSize) << ", L = " << l << ", C = " << c << ", Proc = " << size << "\n" << std::endl;
            std::cout <<  "                               Data Types for the test: " << floattype <<", "<< integertype <<  "\n" << std::endl;
            printf ( "                                  SMG2S Time is %f seconds \n", time );
            border_print2();
        }

    }
    //delete Mt;

    MPI_Finalize();

    return 0;
}

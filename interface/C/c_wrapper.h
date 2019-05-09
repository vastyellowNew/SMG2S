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

#ifndef __C_WRAPPER_H__
#define __C_WRAPPER_H__

#include "../../parMatrix/parMatrixSparse.h"
#include <mpi.h>
#include <stdint.h>


struct NilpotencyInt;

struct parVectorMapInt;

//complex
struct parMatrixSparseComplexSingleInt;

//double
struct parMatrixSparseRealDoubleInt;

//double + complex + int64
struct parMatrixSparseComplexDoubleLongInt;

//double+int64
struct parMatrixSparseRealDoubleLongInt;
//double + complex
struct parMatrixSparseComplexDoubleInt;

//int64 + complex
struct parMatrixSparseComplexSingleLongInt;

//int64
struct parMatrixSparseRealSingleLongInt;

//
struct parMatrixSparseRealSingleInt;


#ifdef __cplusplus
extern "C" {
#endif

/*Nilpotency Matrix C Wrapper*/
struct NilpotencyInt *newNilpotencyInt(void);
void ReleaseNilpotencyInt(struct NilpotencyInt **ppInstance);
//setup NilpotencyInt Type 1 and Type 2
extern void NilpType1(struct NilpotencyInt *n, int num, int size);
extern void NilpType2(struct NilpotencyInt *n, int num, int size);
void showNilpotencyInt(struct NilpotencyInt *n);

struct NilpotencyLongInt *newNilpotencyLongInt(void);
void ReleaseNilpotencyLongInt(struct NilpotencyLongInt **ppInstance);
//setup NilpotencyInt Type 1 and Type 2
extern void NilpType1Long(struct NilpotencyLongInt *n, __int64_t num, __int64_t size);
extern void NilpType2Long(struct NilpotencyLongInt *n, __int64_t num, __int64_t size);
void showNilpotencyLongInt(struct NilpotencyLongInt *n);

/*parVectorMap C wrapper*/
struct parVectorMapInt *newparVectorMapInt(void);

//complex double long int

struct parMatrixSparseComplexDoubleLongInt *newParMatrixSparseComplexDoubleLongInt(void);
void ReleaseParMatrixSparseComplexDoubleLongInt(struct parMatrixSparseComplexDoubleLongInt **ppInstance);
void LOC_MatViewComplexDoubleLongInt(struct parMatrixSparseComplexDoubleLongInt *m);
void GetLocalSizeComplexDoubleLongInt(struct parMatrixSparseComplexDoubleLongInt *m, __int64_t *rs, __int64_t *cs);
void Loc_ConvertToCSRComplexDoubleLongInt(struct parMatrixSparseComplexDoubleLongInt *m);

void Loc_CSRGetRowsArraySizesComplexDoubleLongInt(struct parMatrixSparseComplexDoubleLongInt *m, __int64_t *size,__int64_t *size2);
void Loc_CSRGetRowsArraysComplexDoubleLongInt(struct parMatrixSparseComplexDoubleLongInt *m, __int64_t size, int **rows, __int64_t size2, int **cols, double **real, double **imag);
void smg2sComplexDoubleLongInt(struct parMatrixSparseComplexDoubleLongInt *m, __int64_t probSize, struct NilpotencyLongInt *nilp, __int64_t lbandwidth, char *spectrum, MPI_Comm comm);

//complex double int

struct parMatrixSparseComplexDoubleInt *newParMatrixSparseComplexDoubleInt(void);
void ReleaseParMatrixSparseComplexDoubleInt(struct parMatrixSparseComplexDoubleInt **ppInstance);
void LOC_MatViewComplexDoubleInt(struct parMatrixSparseComplexDoubleInt *m);
void GetLocalSizeComplexDoubleInt(struct parMatrixSparseComplexDoubleInt *m, int *rs, int *cs);
void Loc_ConvertToCSRComplexDoubleInt(struct parMatrixSparseComplexDoubleInt *m);

void Loc_CSRGetRowsArraySizesComplexDoubleInt(struct parMatrixSparseComplexDoubleInt *m, int *size, int *size2);
void Loc_CSRGetRowsArraysComplexDoubleInt(struct parMatrixSparseComplexDoubleInt *m, int size, int **rows, int size2, int **cols, double **real, double **imag);

/*SMG2S C wrapper*/
void smg2sComplexDoubleInt(struct parMatrixSparseComplexDoubleInt *m, int probSize, struct NilpotencyInt *nilp, int lbandwidth, char *spectrum, MPI_Comm comm);

//complex  single long int

struct parMatrixSparseComplexSingleLongInt *newParMatrixSparseComplexSingleLongInt(void);
void ReleaseParMatrixSparseComplexSingleLongInt(struct parMatrixSparseComplexSingleLongInt **ppInstance);
void LOC_MatViewComplexSingleLongInt(struct parMatrixSparseComplexSingleLongInt *m);
void GetLocalSizeComplexSingleLongInt(struct parMatrixSparseComplexSingleLongInt *m, __int64_t *rs, __int64_t *cs);
void Loc_ConvertToCSRComplexSingleLongInt(struct parMatrixSparseComplexSingleLongInt *m);
void Loc_CSRGetRowsArraySizesComplexSingleLongInt(struct parMatrixSparseComplexSingleLongInt *m, __int64_t *size,__int64_t *size2);
void Loc_CSRGetRowsArraysComplexSingleLongInt(struct parMatrixSparseComplexSingleLongInt *m, __int64_t size, int **rows, __int64_t size2, int **cols, double **real, double **imag);

void smg2sComplexSingleLongInt(struct parMatrixSparseComplexSingleLongInt *m, __int64_t probSize, struct NilpotencyLongInt *nilp, __int64_t lbandwidth, char *spectrum, MPI_Comm comm);

//real double long int

/*parMatrixSparse complex<double> int C wrapper*/

struct parMatrixSparseRealDoubleLongInt *newParMatrixSparseRealDoubleLongInt(void);
void ReleaseParMatrixSparseRealDoubleLongInt(struct parMatrixSparseRealDoubleLongInt **ppInstance);
void LOC_MatViewRealDoubleLongInt(struct parMatrixSparseRealDoubleLongInt *m);
void GetLocalSizeRealDoubleLongInt(struct parMatrixSparseRealDoubleLongInt *m, __int64_t *rs, __int64_t *cs);
void Loc_ConvertToCSRRealDoubleLongInt(struct parMatrixSparseRealDoubleLongInt *m);
void Loc_CSRGetRowsArraySizesRealDoubleLongInt(struct parMatrixSparseRealDoubleLongInt *m, __int64_t *size,__int64_t *size2);
void Loc_CSRGetRowsArraysRealDoubleLongInt(struct parMatrixSparseRealDoubleLongInt *m, __int64_t size, int **rows, __int64_t size2, int **cols, double **vals);
void smg2sRealDoubleLongInt(struct parMatrixSparseRealDoubleLongInt *m, __int64_t probSize, struct NilpotencyLongInt *nilp, __int64_t lbandwidth, char *spectrum, MPI_Comm comm);

void smg2sNonSymmetricRealDoubleLongInt(struct parMatrixSparseRealDoubleLongInt *m, __int64_t probSize, struct NilpotencyLongInt *nilp, __int64_t lbandwidth, char *spectrum, MPI_Comm comm);


//complex single int

/*parMatrixSparse complex<double> int C wrapper*/
struct parMatrixSparseComplexSingleInt *newParMatrixSparseComplexSingleInt(void);
void ReleaseParMatrixSparseComplexSingleInt(struct parMatrixSparseComplexSingleInt **ppInstance);
void LOC_MatViewComplexSingleInt(struct parMatrixSparseComplexSingleInt *m);

void GetLocalSizeComplexSingleInt(struct parMatrixSparseComplexSingleInt *m, int *rs, int *cs);
void Loc_ConvertToCSRComplexSingleInt(struct parMatrixSparseComplexSingleInt *m);
void Loc_CSRGetRowsArraySizesComplexSingleInt(struct parMatrixSparseComplexSingleInt *m, int *size,int *size2);
void Loc_CSRGetRowsArraysComplexSingleInt(struct parMatrixSparseComplexSingleInt *m, int size, int **rows, int size2, int **cols, double **real, double **imag);
void smg2sComplexSingleInt(struct parMatrixSparseComplexSingleInt *m, int probSize, struct NilpotencyInt *nilp, int lbandwidth, char *spectrum, MPI_Comm comm);

//real double int

struct parMatrixSparseRealDoubleInt *newParMatrixSparseRealDoubleInt(void);
void ReleaseParMatrixSparseRealDoubleInt(struct parMatrixSparseRealDoubleInt **ppInstance);
void LOC_MatViewRealDoubleInt(struct parMatrixSparseRealDoubleInt *m);
void GetLocalSizeRealDoubleInt(struct parMatrixSparseRealDoubleInt *m, int *rs, int *cs);
void Loc_ConvertToCSRRealDoubleInt(struct parMatrixSparseRealDoubleInt *m);

void Loc_RealCSRGetRowsArraySizesRealDoubleInt(struct parMatrixSparseRealDoubleInt *m, int *size, int *size2);
void Loc_RealCSRGetRowsArraysRealDoubleInt(struct parMatrixSparseRealDoubleInt *m, int size, int **rows, int size2, int **cols, double **vals);

/*SMG2S C wrapper*/
void smg2sRealDoubleInt(struct parMatrixSparseRealDoubleInt *m, int probSize, struct NilpotencyInt *nilp, int lbandwidth, char *spectrum, MPI_Comm comm);
void smg2sNonSymmetricRealDoubleInt(struct parMatrixSparseRealDoubleInt *m, int probSize, struct NilpotencyInt *nilp, int lbandwidth, char *spectrum, MPI_Comm comm);

//real single long int

struct parMatrixSparseRealSingleLongInt *newParMatrixSparseRealSingleLongInt(void);
void ReleaseParMatrixSparseRealSingleLongInt(struct parMatrixSparseRealSingleLongInt **ppInstance);
void LOC_MatViewRealSingleLongInt(struct parMatrixSparseRealSingleLongInt *m);
void GetLocalSizeRealSingleLongInt(struct parMatrixSparseRealSingleLongInt *m, __int64_t *rs, __int64_t *cs);
void Loc_ConvertToCSRRealSingleLongInt(struct parMatrixSparseRealSingleLongInt *m);

void Loc_LongCSRGetRowsArraySizesRealSingleLongInt(struct parMatrixSparseRealSingleLongInt *m, __int64_t *size, __int64_t *size2);
void Loc_RealCSRGetRowsArraysRealSingleLongInt(struct parMatrixSparseRealSingleLongInt *m, __int64_t size, __int64_t **rows, __int64_t size2, __int64_t **cols, double **vals);

void smg2sRealSingleLongInt(struct parMatrixSparseRealSingleLongInt *m, __int64_t probSize, struct NilpotencyLongInt *nilp, __int64_t lbandwidth, char *spectrum, MPI_Comm comm);
void smg2sNonSymmetricRealSingleLongInt(struct parMatrixSparseRealSingleLongInt *m, __int64_t probSize, struct NilpotencyLongInt *nilp, __int64_t lbandwidth, char *spectrum, MPI_Comm comm);

/*parMatrixSparse int C wrapper*/
struct parMatrixSparseRealSingleInt *newParMatrixSparseRealSingleInt(void);
void ReleaseParMatrixSparseRealSingleInt(struct parMatrixSparseRealSingleInt **ppInstance);
void LOC_MatViewRealSingleInt(struct parMatrixSparseRealSingleInt *m);
void GetLocalSizeRealSingleInt(struct parMatrixSparseRealSingleInt *m, int *rs, int *cs);
void Loc_ConvertToCSRRealSingleInt(struct parMatrixSparseRealSingleInt *m);

void Loc_RealCSRGetRowsArraySizesRealSingleInt(struct parMatrixSparseRealSingleInt *m, int *size, int *size2);
void Loc_RealCSRGetRowsArraysRealSingleInt(struct parMatrixSparseRealSingleInt *m, int size, int **rows, int size2, int **cols, double **vals);

void smg2sRealSingleInt(struct parMatrixSparseRealSingleInt *m, int probSize, struct NilpotencyInt *nilp, int lbandwidth, char *spectrum, MPI_Comm comm);

void smg2sNonSymmetricRealSingleInt(struct parMatrixSparseRealSingleInt *m, int probSize, struct NilpotencyInt *nilp, int lbandwidth, char *spectrum, MPI_Comm comm);


#ifdef __cplusplus
};
#endif

#endif

//#include "output_container.h"

#include <stdlib.h>
#include <assert.h>

#include <algorithm>    //sort
#include <functional>   //less/greater/hash
#include <iostream>     //cout/endl
#include <string>       //string
#include <vector>       //vector
#include <queue>        //priotiry_queue
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <complex>
#include <iterator>     //std::size
#include <array>


using namespace std;

#if 0
typedef struct {
    float* data;
    size_t nrows;
    size_t ncols;
} matrix;

enum matrix_err_code {
    MATRIX_SUCCESS,
    MATRIX_ERR_MEMORY_INSUFFICIENT,
    //MATRIX_ERR_MISMATCHED_MATRIX_SIZE,
};

int matrix_alloc(matrix* ptr, size_t nrows, size_t ncols)
{
    size_t size = nrows * ncols * sizeof(float);
    float* data = malloc(size);
    if (data == NULL) {
        return MATRIX_ERR_MEMORY_INSUFFICIENT;
    }
    ptr->data = data;
    ptr->nrows = nrows;
    ptr->ncols = ncols;
}

void matrix_dealloc(matrix* ptr)
{
    if (ptr->data == NULL) {
        return;
    }
    free(ptr->data);
    ptr->data = NULL;
    ptr->nrows = 0;
    ptr->ncols = 0;
}

int matrix_multiply(matrix* result, const matrix* lhs, const matrix* rhs)
{
    int errcode;
    if (lhs->ncols != rhs->nrows) {
        return MATRIX_ERR_MISMATCHED_MATRIX_SIZE;
    }
    errcode = matrix_alloc(result, lhs->nrows, rhs->ncols);
    if (errcode != MATRIX_SUCCESS) {
        return errcode;
    }
    return MATRIX_SUCCESS;
}
#endif

class matrix {
public:
    matrix(size_t nrows, size_t ncols);
    ~matrix();
    friend matrix operator*(const matrix&, const matrix&);
private:
    float* data_;
    size_t nrows_;
    size_t ncols_;
};

matrix::matrix(size_t nrows, size_t ncols)
{
    data_ = new float[nrows * ncols];
    nrows_ = nrows;
    ncols_ = ncols;
}

matrix::~matrix()
{
    delete[] data_;
}

matrix operator*(const matrix& lhs, const matrix& rhs)
{
    if (lhs.ncols_ != rhs.nrows_) {
        throw std::runtime_error("matrix sizes mismatch");
    }
    matrix result(lhs.nrows_, rhs.ncols_);
    return result;
}

int main(int argc, char* argv[])
{

    {
#if 0
        matrix c;
        memset(&c, 0, sizeof(matrix));
        
        errcode = matrix_multiply(c, a, b);
        if (errcode != MATRIX_SUCCESS) {
            goto error_exit;
        }

    error_exit:
        matrix_dealloc(&c);
        return errcode;
#endif
    }
    {
        matrix a(2, 3);
        matrix b(3, 2);
        matrix c = a * b;

        matrix c1 = matrix(2, 3) * matrix(3, 2);
    }

    system("pause");
    return 0;
}


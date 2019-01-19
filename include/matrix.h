/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Header for Matrix class
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/3/19
 */

#ifndef __MATRIX__
#define __MATRIX__
#include "vector.h"
#include <iostream>
#include <opencv2/opencv.hpp>

template <class vector_type>
class vector;

// template <class matrix_type>
// class matrix_2d;

// template <class matrix_type>
// std::ostream & operator << (std::ostream &out, const matrix_2d<matrix_type> &c);

template <class matrix_type>

#define create_matrix_2d_data(mat_name, rows, cols, type) \
    {                                                     \
        type static mat_name##_data[(rows * cols)];        \
        mat_name.set_data(mat_name##_data, rows, cols); \
        mat_name.clear();                               \
    }
#define create_matrix(mat_name, rows, cols, type)         \
    {                                                     \
        matrix_2d<type> mat_name;                     \
        float static mat_name##_data[(rows * cols)];        \
        mat_name.set_data(mat_name##_data, rows, cols); \
        mat_name.clear();                               \
    }

class matrix_2d
{
  public:
    matrix_2d();
    matrix_2d(matrix_type *, int, int);
    matrix_2d(vector<matrix_type>);
    //template <typename vector_type> matrix_2d(vector<vector_type>);
    matrix_type *operator[](int);
    void copy(matrix_2d<matrix_type>);
    void clear();
    void multiply(matrix_2d<matrix_type> a, matrix_2d<matrix_type> b);
    void transpose();
    void transpose(matrix_2d<matrix_type> output_matrix);
    matrix_type at(int, int);
    int get_rows();
    int get_cols();
    void set_data(matrix_type *, int, int);
    void set_size(int, int);
    void get_col(vector<matrix_type>, int);
    void get_row(vector<matrix_type>, int);
    void set_col(vector<matrix_type>, int);
    void set_row(vector<matrix_type>, int);
    void to_cv(cv::Mat &);
    bool data_active;

  private:
    matrix_type *data;
    int rows;
    int cols;
};

template <class matrix_type>
std::ostream &operator<<(std::ostream &out, matrix_2d<matrix_type> &mat)
{
    int rows = mat.get_rows();
    int cols = mat.get_cols();
    out << "[" << std::endl;
    for (int j = 0; j < rows; j++)
    {
        for (int i = 0; i < cols; i++)
        {
            out << mat[j][i] << " ";
        }
        out << std::endl;
    }

    out << "]" << std::endl;

    return out;
}

#endif
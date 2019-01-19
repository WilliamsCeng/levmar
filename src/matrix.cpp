/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Implementation of Matrix class
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/3/19
 */

#include "matrix.h"

template <class matrix_type>
matrix_2d<matrix_type>::matrix_2d()
{
    data = nullptr;
    rows = 0;
    cols = 0;
}

// template <class matrix_type>
// matrix_2d<matrix_type>::matrix_2d(vector<matrix_type> vec)
// {
//     data = vec.data;
//     rows = vec.size;
//     cols = 1;
// }

template <class matrix_type>
matrix_2d<matrix_type>::matrix_2d(vector<matrix_type> vec)
{
    data = vec.data;
    rows = vec.size;
    cols = 1;
}

template <class matrix_type>
matrix_2d<matrix_type>::matrix_2d(matrix_type *input_data, int rows, int cols)
    : data(input_data), rows(rows), cols(cols)
{
}

template <class matrix_type>
void matrix_2d<matrix_type>::copy(matrix_2d<matrix_type> input_mat)
{
    for (int j = 0; j < cols; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            data[j * cols + i] = input_mat[j][i];
        }
    }

    // cols = input_mat.get_cols();
    // rows = input_mat.get_rows();

    // for (int j = 0; j < rows; j++)
    // {
    //     for (int i = 0; i < cols; i++)
    //     {
    //         data[j * cols + i] = input_mat[j][i];
    //     }
    // }
}

template <class matrix_type>
matrix_type *matrix_2d<matrix_type>::operator[](int index)
{
    return cols * index + data;
}

template <class matrix_type>
matrix_type matrix_2d<matrix_type>::at(int row_index, int col_index)
{
    return data[row_index * cols + col_index];
}

template <class matrix_type>
int matrix_2d<matrix_type>::get_cols()
{
    return cols;
}

template <class matrix_type>
int matrix_2d<matrix_type>::get_rows()
{
    return rows;
}

template <class matrix_type>
void matrix_2d<matrix_type>::set_data(matrix_type *input_data, int input_rows, int input_cols)
{
    data = input_data;
    rows = input_rows;
    cols = input_cols;
}

template <class matrix_type>
void matrix_2d<matrix_type>::set_size(int input_rows, int input_cols)
{
    if (input_rows != 0)
    {
        rows = input_rows;
    } 

    if (input_cols != 0)
    {
        cols = input_cols;
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::set_col(vector<matrix_type> input_vec, int col_index)
{
    for (int i = 0; i < rows; i++)
    {
        data[i * cols + col_index] = input_vec[i];
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::set_row(vector<matrix_type> input_vec, int row_index)
{
    int row_offset = row_index * cols;
    for (int i = 0; i < cols; i++)
    {
        data[row_offset + i] = input_vec[i];
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::get_col(vector<matrix_type> input_vec, int col_index)
{
    for (int i = 0; i < rows; i++)
    {
        input_vec[i] = data[i * cols + col_index];
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::get_row(vector<matrix_type> input_vec, int row_index)
{
    int row_offset = row_index * cols;
    for (int i = 0; i < cols; i++)
    {
        input_vec[i] = data[row_offset + i];
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::multiply(matrix_2d<matrix_type> a, matrix_2d<matrix_type> b)
{
    int a_cols = a.get_cols();
    int a_rows = a.get_rows();
    int b_cols = b.get_cols();

    for (int a_row_index = 0; a_row_index < a_rows; a_row_index++)
    {
        for (int b_col_index = 0; b_col_index < b_cols; b_col_index++)
        {
            data[a_row_index * cols + b_col_index] = 0;
            for (int a_col_index = 0; a_col_index < a_cols; a_col_index++)
            {
                data[a_row_index * cols + b_col_index] += a[a_row_index][a_col_index] * b[a_col_index][b_col_index];
            }
        }
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::transpose()
{
    matrix_type temp;
    for (int j = 0; j < rows; j++)
    {
        for (int i = j + 1; i < cols; i++)
        {
            temp = data[j * cols + i];
            data[j * cols + i] = data[i * cols + j];
            data[i * cols + j] = temp;
        }
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::transpose(matrix_2d<matrix_type> output_matrix)
{
    for (int j = 0; j < rows; j++)
    {
        output_matrix[j][j] = data[j * cols + j];
        for (int i = j + 1; i < cols; i++)
        {
            output_matrix[j][i] = data[i * cols + j];
            output_matrix[i][j] = data[j * cols + i];
        }
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::clear()
{
    for (int j = 0; j < cols; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            data[j * cols + i] = (matrix_type)0;
        }
    }
}

template <class matrix_type>
void matrix_2d<matrix_type>::to_cv(cv::Mat &output_mat)
{
    output_mat.setTo(cv::Scalar(0));
    output_mat.resize(rows, cols);
    for (int j = 0; j < rows; j++) 
    {
        for (int i = 0; i < cols; i++) 
        {
            output_mat.at<double>(j, i) = (double)data[j * cols + i];
        }
    }
}

template class matrix_2d<float>;
template class matrix_2d<double>;

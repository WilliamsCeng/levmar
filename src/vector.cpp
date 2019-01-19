/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Implementation of Vector class
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/3/19
 */

#include "vector.h"

template <class vector_type>
vector<vector_type>::vector(vector_type *input_data, int size)
    : data(input_data), size(size)
{
}

template <class vector_type>
vector_type &vector<vector_type>::operator[](int index)
{
    return data[index];
}

template <class vector_type>
int vector<vector_type>::get_size()
{
    return size;
}

template <class vector_type>
void vector<vector_type>::copy(vector<vector_type> input_vec)
{
    int size = input_vec.get_size();
    for (int i = 0; i < size; i++)
    {
        data[i] = input_vec[i];
    }
}

template <class vector_type>
void vector<vector_type>::multiply(vector_type scalar) 
{
    for (int i = 0; i < size; i++)
    {
        data[i] *= scalar;
    } 
}

template <class vector_type>
void vector<vector_type>::clear()
{
    for (int i = 0; i < size; i++)
    {
        data[i] = (vector_type)0;
    }
}

template <class vector_type>
void vector<vector_type>::to_cv(cv::Mat &input_mat)
{
    for (int i = 0; i < size; i++)
    {
        input_mat.at<double>(i, 0) = (double)data[i];
    }
}

template <class vector_type>
vector<vector_type>::vector()
{
    data = nullptr;
    size = 0;
}

template <class vector_type>
void vector<vector_type>::set_data(vector_type *input_data, int input_size)
{
    data = input_data;
    size = input_size;
}

template class vector<float>;
template class vector<double>;
template class vector<int>;
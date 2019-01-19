/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Header for Vector class
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/3/19
 */

#ifndef __VECTOR__
#define __VECTOR__

#include "matrix.h"
#include <iostream>
#include <opencv2/opencv.hpp>

// #define create_vector_2d_data(mat_name, size, type) \
//     {                                                     \
//         type static mat_name##_data[size];        \
//         mat_name##.set_data(mat_name##_data, size); \
//         mat_name##.clear();                               \
//     }
// #define create_matrix(mat_name, rows, cols, type)         \
//     {                                                     \
//         matrix_2d<##type##> mat_name;                     \
//         float static mat_name##_data[rows * cols];        \
//         mat_name##.set_data(mat_name##_data, rows, cols); \
//         mat_name##.clear();                               \
//     }

#define create_vec_data(vec_name, size, type) \
  {                                           \
    type static vec_name##_data[size];        \
    vec_name.set_data(vec_name##_data, size); \
    vec_name.clear();                         \
  };

#define create_vector(vec_name, size, type)   \
  {                                           \
    vector<type> vec_name;                    \
    type static vec_name##_data[size];        \
    vec_name.set_data(vec_name##_data, size); \
    vec_name.clear();                         \
  }

template <class vector_type>
class vector
{
public:
  vector();
  vector(vector_type *, int);
  vector_type &operator[](int);
  void set_data(vector_type *, int);
  void copy(vector<vector_type>);
  int get_size();
  void multiply(vector_type);
  void clear();
  void to_cv(cv::Mat &);
  bool data_active;

private:
  vector_type *data;
  int size;

  template <class matrix_type>
  friend class matrix_2d;
};

template <class vector_type>
std::ostream &operator<<(std::ostream &out, vector<vector_type> &vec)
{
  int size = vec.get_size();
  out << "[" << std::endl;
  for (int i = 0; i < size; i++)
  {
    out << vec[i] << " ";
  }

  out << "]" << std::endl;

  return out;
}



#endif

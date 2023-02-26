#ifndef MATRIX_H
#define MATRIX_H
#include<vector>
#include<math.h>
#include <algorithm>
class Matrix
{
    private:
        int row;
        int col;
        double **data;
        std::vector<int> pivots;
    public:
        Matrix();
        Matrix(const Matrix& m);
        Matrix(int r,int c);
        Matrix(int r,int c,int ini_val);
        Matrix(int r,int c,std::vector< std::vector<double> > dat);
        Matrix(int r,int c,double **a);
        void add_ij(int i,int j,double add_value);
        void set_ij(int i,int j,double set_value);
        void setall(double value);
        int get_row_num()const;
        int get_col_num()const;
        std::vector<double> get_row(int);
        std::vector<double> get_col(int);

        void swap_row(int r1,int r2);
        void update_pivots();
        void sort_by_row();

        double operator()(int i, int j)const;
        void operator=(const Matrix&);

        Matrix operator+(const Matrix&);
        void operator+=(const Matrix&);

        Matrix operator-(const Matrix&);
        void operator-=(const Matrix&);

        Matrix operator*(const Matrix&);
        Matrix operator*(double);

        double determinant();
        Matrix adjoint();
        Matrix inverse();
        Matrix transpose();
        Matrix solve(const Matrix& b);//Ax = b, this is A return x
        Matrix solve_gauss_elimination(const Matrix& b);

        void debug()const;

        static double calculate_maxVdifference(const Matrix& a,const Matrix& b);
        ~Matrix();
};

#endif // MATRIX_H

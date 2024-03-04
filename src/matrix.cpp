#include "matrix.h"
#include <QDebug>
Matrix::Matrix():pivots(1,col)
{
    row = 1;
    col = 1;
    data = new double*[row];
    for(int i=0;i<row;i++){
        data[i] = new double[col];
    }
}
Matrix::Matrix(const Matrix& m):pivots(m.get_row_num(),col)
{
    row = m.get_row_num();
    col = m.get_col_num();
    data = new double*[row];
    for(int i=0;i<row;i++){
        data[i] = new double[col];
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j] = m(i,j);
        }
    }
    update_pivots();
}
Matrix::Matrix(int r,int c):pivots(r,col)
{
    row = r;
    col = c;
    data = new double*[row];
    for(int i=0;i<row;i++){
        data[i] = new double[col];
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j] = 0;
        }
    }
}
Matrix::Matrix(int r,int c,int ini_val):pivots(r,col)
{
    row = r;
    col = c;
    data = new double*[row];
    for(int i=0;i<row;i++){
        data[i] = new double[col];
    }
    for(int i=0;i<row;i++){
        pivots[i] = 0;
        for(int j=0;j<col;j++){
            data[i][j] = ini_val;
        }
    }
}
Matrix::Matrix(int r,int c,std::vector< std::vector<double> > dat):pivots(r,col)
{
    row = r;
    col = c;
    data = new double*[row];
    for(int i=0;i<row;i++){
        data[i] = new double[col];
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j] = dat[i][j];
        }
    }
    update_pivots();
}
Matrix::Matrix(int r,int c,double **a):pivots(r,col)
{
    row = r;
    col = c;
    data = new double*[row];
    for(int i=0;i<row;i++){
        data[i] = new double[col];
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j] = a[i][j];
        }
    }
    update_pivots();
}
double Matrix::operator()(int i, int j)const
{
    if( (i>=0&&i<row) && (j>=0&&j<col))
        return data[i][j];
    else
        return 0;
}
void Matrix::add_ij(int i,int j,double add_value)
{
    if( (i>=0&&i<row) && (j>=0&&j<col))
        data[i][j]+=add_value;
    if(data[i][j]==0)
        update_pivots();
    //qDebug()<<"i: "<<i<<" j: "<<j<<" data: "<<data[i][j];
}
void Matrix::set_ij(int i,int j,double set_value)
{
    if( (i>=0&&i<row) && (j>=0&&j<col))
        data[i][j] = set_value;
    if(data[i][j]==0)
        update_pivots();
}
void Matrix::setall(double value)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j] = value;
        }
    }
}
std::vector<double> Matrix::get_row(int r)
{
    std::vector<double> ans;
    for(int i=0;i<col;i++){
        ans.push_back(data[r][i]);
    }
    return ans;
}
std::vector<double> Matrix::get_col(int c)
{
    std::vector<double> ans;
    for(int i=0;i<row;i++){
        ans.push_back(data[i][c]);
    }
    return ans;
}
void Matrix::update_pivots()
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++){
            if(data[i][j]!=0){
                pivots[i] = j;
                break;
            }
        }
    }
}
void Matrix::sort_by_row()
{
    update_pivots();

    for(int i=0;i<row-1;i++){
       for(int j=i+1;j<row;j++){
           if(pivots[i]>pivots[j]){
               swap_row(i,j);
           }
       }
    }
}
void Matrix::swap_row(int n1,int n2)
{
    std::vector<double> r1 = get_row(n1);
    std::vector<double> r2 = get_row(n2);
    for(int i=0;i<r1.size();i++){
        data[n1][i] = r2[i];
        data[n2][i] = r1[i];
    }
    std::swap(pivots[n1],pivots[n2]);
}
void Matrix::operator=(const Matrix& m)
{
    for(int i=0;i<row;i++)
        delete []data[i];
    delete []data;
    //qDebug()<<"hello";
    row = m.get_row_num();
    col = m.get_col_num();
    data = new double*[row];
    for(int i=0;i<row;i++){
        data[i] = new double[col];
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j] = m(i,j);
        }
    }
}
Matrix Matrix::operator+(const Matrix& m)
{
    if(row!=m.get_row_num()||col!=m.get_col_num()){
        qDebug()<<"row, col doesnt match";
        return Matrix(row,col,0);
    }
    std::vector< std::vector<double> > ans(row);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
            ans[i].push_back(0);
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            ans[i][j] = data[i][j] + m(i,j);
        }
    }
    return Matrix(row,col,ans);
}
void Matrix::operator+=(const Matrix& m)
{
    if(row!=m.get_row_num()||col!=m.get_col_num()){
        qDebug()<<"row, col doesnt match";
        return;
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j] += m(i,j);
        }
    }
}
Matrix Matrix::operator-(const Matrix& m)
{
    if(row!=m.get_row_num()||col!=m.get_col_num()){
        qDebug()<<"row, col doesnt match";
        return Matrix(row,col,0);
    }
    std::vector< std::vector<double> > ans(row);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
            ans[i].push_back(0);
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            ans[i][j] = data[i][j] - m(i,j);
        }
    }
    return Matrix(row,col,ans);
}
void Matrix::operator-=(const Matrix& m)
{
    if(row!=m.get_row_num()||col!=m.get_col_num()){
        qDebug()<<"row, col doesnt match";
        return;
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            data[i][j] -= m(i,j);
        }
    }
}

Matrix Matrix::operator*(const Matrix& m)
{
    if(col!=m.get_row_num()){
        qDebug()<<"row, col doesnt match";
        return Matrix(row,col,0);
    }
    std::vector< std::vector<double> > ans(row);
    for(int i=0;i<row;i++){
        for(int j=0;j<m.get_col_num();j++)
            ans[i].push_back(0);
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<m.get_col_num();j++){
            for(int k=0;k<col;k++){
                ans[i][j] +=data[i][k]*m(k,j);
            }
        }
    }
    return Matrix(row,m.get_col_num(),ans);
}

Matrix Matrix::operator*(double s)
{
    std::vector< std::vector<double> > ans(row);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
            ans[i].push_back(0);
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            ans[i][j] = data[i][j]*s;
        }
    }
    return Matrix(row,col,ans);
}

int Matrix::get_row_num()const
{
    return row;
}
int Matrix::get_col_num()const
{
    return col;
}
double Matrix::determinant()
{
    if(row!=col)
        return 0;
    if(row==1)
        return data[0][0];
    if(row==2)
        return data[0][0]*data[1][1] - data[0][1]*data[1][0];
    double ans=0;
    Matrix sub(row-1,col-1,0);
    for (int i = 0; i < col; i++) {
        int subi = 0;
        for (int j = 1; j < col; j++) {
            int subj = 0;
            for (int k = 0; k < col; k++) {
                if (k == i)
                    continue;
                sub.set_ij(subi,subj,data[j][k]);
                subj++;
            }
            subi++;
        }
        ans = ans + (pow(-1, i) * data[0][i] * sub.determinant());
    }
    return ans;
}
Matrix Matrix::adjoint()
{
    Matrix ans(row,col,0);
    if(row!=col)
        return ans;
    if(row==2){
        ans.set_ij(0,0,data[1][1]);
        ans.set_ij(0,1,-data[0][1]);
        ans.set_ij(1,0,-data[1][0]);
        ans.set_ij(1,1,data[0][0]);
        return ans;
    }
    Matrix sub(row-1,col-1,0);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            int subi = 0;
            for(int k=0;k<row;k++){
                int subj = 0;
                if(k==i)
                    continue;
                for(int l=0;l<col;l++){

                    if(j==l)
                        continue;
                    sub.set_ij(subi,subj,data[k][l]);
                    subj++;
                }
                subi++;
            }
            ans.set_ij(i,j,pow(-1,i+j)*sub.determinant());
        }
    }
    return ans.transpose();
}
Matrix Matrix::transpose()
{
    Matrix ans(col,row,0);
    for(int i=0;i<col;i++){
        for(int j=0;j<row;j++){
            ans.set_ij(i,j,data[j][i]);
        }
    }
    return ans;
}
Matrix Matrix::inverse()
{
    if(determinant()!=0)
        return adjoint()*(1/determinant());
    else
        return Matrix(row,col,0);
}
Matrix Matrix::solve(const Matrix& b)
{
    Matrix ans = inverse()*b;
    return ans;
}
Matrix Matrix::solve_gauss_elimination(const Matrix& bababao)
{
    if(row!=col || bababao.get_row_num()!= row){
        qDebug()<<"Row col not matching";
        return Matrix();
    }

    Matrix to_solve(row,col+1);
    Matrix ans(row,1);
    //b.debug();
    for(int i=0;i<to_solve.get_row_num();i++){
        for(int j=0;j<to_solve.get_col_num();j++){
            if(j==to_solve.get_col_num()-1)
                to_solve.set_ij(i,j,bababao(i,0));
            else
                to_solve.set_ij(i,j,data[i][j]);
        }
    }

    to_solve.sort_by_row();

    int sq = row;
    for(int i=0;i<sq;i++){
        for(int j=i+1;j<sq;j++){

            double s = to_solve(j,i)/to_solve(i,i);
            to_solve.set_ij(j,i,0);
            for(int k=0;k<sq+1;k++){
                if(k!=i)
                    to_solve.add_ij(j,k,-to_solve(i,k)*s);
            }
        }
        to_solve.sort_by_row();
    }

    for(int i=sq-1;i>=0;i--){
        double s=0;
        for(int j=i+1;j<sq;j++){
            s += to_solve(i,j)*ans(j,0);
        }
        ans.set_ij(i,0,(to_solve(i,sq)-s)/to_solve(i,i));
    }
    return ans;
}
void Matrix::debug()const
{
    QDebug deb = qDebug();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            deb.nospace()<<data[i][j]<<" ";
        }
        deb.nospace()<<"\n";
    }
    qDebug()<<"";
}

double Matrix::calculate_maxVdifference(const Matrix& base,const Matrix& ano)
{
    if(ano.row!=base.row || ano.col!=1 || base.col!=1){
        qDebug()<<"no match row or col";
        return 0;
    }
    double ans = -1;
    for(int i = 0;i<base.get_row_num();i++){
        ans = std::max(ans,abs(ano(i,0)-base(i,0)));
    }
    return ans;
}
Matrix::~Matrix()
{
    for(int i=0;i<row;i++)
        delete []data[i];
    delete []data;
}

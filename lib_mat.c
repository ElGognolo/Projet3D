#include "lib_3d.h"
#include "lib_mat.h"

void multiplicationVecteur3d(t_point3d *v1, double m[4][4], t_point3d *v2) // v1 = m*v2
{
	int i, j;
	double acc[4]={0,0,0,0};
	for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            acc[i]=acc[i]+(m[i][j]*(*v2).xyzt[j]);
        }

    }
    (*v1).xyzt[0]=acc[0];
    (*v1).xyzt[1]=acc[1];
    (*v1).xyzt[2]=acc[2];
    (*v1).xyzt[3]=acc[3];
}

void multiplicationMatrice3d(double m1[4][4], double m2[4][4], double m3[4][4]) // m1 = m2*m3
{
	int i, j, k;
    double acc[4][4]={{0,0,0,0},\
    {0,0,0,0},\
    {0,0,0,0},\
    {0,0,0,0}};
    for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                for(k=0;k<4;k++)
                    {
                        acc[i][j]=acc[i][j]+m2[i][k]*m3[k][j];
                    }
            }
        }
    copierMatrice3d(m1,acc);
}

void copierMatrice3d(double m1[4][4], double m2[4][4]) // m1 = m2
{
	int i, j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            m1[i][j]=m2[i][j];
        }

    }
	// TODO
}

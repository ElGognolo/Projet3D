#include "lib_surface.h"
#include "lib_3d.h"
#include "lib_2d.h"
#include "lib_mat.h"
#include <math.h>

typedef struct
{
	double m[4][4];
} t_matrice3d;

t_point3d *definirPoint3d(double x, double y, double z)	// attention malloc
{
	t_point3d *p;

	p  = (t_point3d*) malloc(sizeof(t_point3d));
	if (p!=NULL)
	{
		p->xyzt[0] = x;
		p->xyzt[1] = y;
		p->xyzt[2] = z;
		p->xyzt[3] = 1;
	}

	return p;
}

t_point3d *definirVecteur3d(double x, double y, double z)	// attention malloc
{
	t_point3d *p = NULL;
	p  = (t_point3d*) malloc(sizeof(t_point3d));
	if (p!=NULL)
	{
		p->xyzt[0] = x;
		p->xyzt[1] = y;
		p->xyzt[2] = z;
		p->xyzt[3] = 0;
	}
	return p;
}

t_triangle3d *definirTriangle3d(t_point3d * a, t_point3d * b, t_point3d * c)	// attention malloc
{
	t_triangle3d *t = NULL;
    t = (t_triangle3d*) malloc(sizeof(t_triangle3d));
    if(t!=NULL)
    {
        (*t).abc[0]=a;
        (*t).abc[1]=b;
        (*t).abc[2]=c;
    }
	return t;
}

t_triangle3d *copierTriangle3d(t_triangle3d *t)
{
	t_triangle3d *n = NULL;
    t_point3d *a=definirPoint3d((*(*t).abc[0]).xyzt[0],(*(*t).abc[0]).xyzt[1],(*(*t).abc[0]).xyzt[2]);
    t_point3d *b=definirPoint3d((*(*t).abc[1]).xyzt[0],(*(*t).abc[1]).xyzt[1],(*(*t).abc[1]).xyzt[2]);
    t_point3d *c=definirPoint3d((*(*t).abc[2]).xyzt[0],(*(*t).abc[2]).xyzt[1],(*(*t).abc[2]).xyzt[2]);
    n=definirTriangle3d(a,b,c);
	return n;

}

void libererTriangle3d(t_triangle3d *t)
{
	free((*(*t).abc[0]).xyzt);
	free((*(*t).abc[1]).xyzt);
	free((*(*t).abc[2]).xyzt);
	free(t);
}

// effectue une conversion de 2D en 3D
t_point2d *__conversion_2d_3d(t_point3d *p3d)
{
	t_point2d *p2d;
	t_point3d *p3dtmp;
	double matrice_projection[4][4]={{1, 0, 0, 0},\
			{0, 1, 0, 0},\
			{0, 0, 1, 0},\
			{0, 0, 0, 1}};


	p2d = NULL;
	p3dtmp = (t_point3d*)malloc(sizeof(t_point3d));
	if (p3dtmp!=NULL)
	{
		multiplicationVecteur3d(p3dtmp, matrice_projection, p3d);

		p2d = definirPoint2d(p3dtmp->xyzt[0]+RX/2, p3dtmp->xyzt[1]+RY/2); // malloc implicite il faut faire un free plus tard... (dans une vingtaine de lignes)
	}

	free(p3dtmp);
	return p2d;
}

void remplirTriangle3d(t_surface * surface, t_triangle3d * triangle, Uint32 c)
{
	t_point2d *p2da, *p2db, *p2dc;
	t_triangle2d *t2d;
	p2da = __conversion_2d_3d(triangle->abc[0]);
	p2db = __conversion_2d_3d(triangle->abc[1]);
	p2dc = __conversion_2d_3d(triangle->abc[2]);

	t2d = definirTriangle2d(p2da, p2db, p2dc);

	remplirTriangle2d(surface, t2d, c);
	free(t2d);
	free(p2da); // le free est fait ici :)
	free(p2db);
	free(p2dc);

}

void translationTriangle3d(t_triangle3d *t, t_point3d *vecteur)
{
    double matrice_translation[4][4]={{1, 0, 0, (*vecteur).xyzt[0]},\
			{0, 1, 0, (*vecteur).xyzt[1]},\
			{0, 0,1 , (*vecteur).xyzt[2]},\
			{0, 0, 0,1 }};
    transformationTriangle3d(t,matrice_translation);

}

void rotationTriangle3d(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ)
{
    t_point3d *A=definirVecteur3d(-(*centre).xyzt[0],-(*centre).xyzt[1],-(*centre).xyzt[2]);
    double op[4][4];
    double matrice_translation[4][4]={{1, 0, 0, (*A).xyzt[0]},\
			{0, 1, 0, (*A).xyzt[1]},\
			{0, 0,1 , (*A).xyzt[2]},\
			{0, 0, 0,1 }};
    double matrice_translationR[4][4]={{1, 0, 0, (*centre).xyzt[0]},\
			{0, 1, 0, (*centre).xyzt[1]},\
			{0, 0,1 , (*centre).xyzt[2]},\
			{0, 0, 0,1 }};
    float radX, radY, radZ;
    radX=degreX*M_PI/180;
    radY=degreY*M_PI/180;
    radZ=degreZ*M_PI/180;
    double matrice_rotationX[4][4]={{1, 0, 0, 0},\
			{0, cos(radX), -sin(radX), 0},\
			{0, sin(radX), cos(radX), 0},\
			{0, 0, 0, 1}};
    double matrice_rotationY[4][4]={{cos(radY), 0, sin(radY), 0},\
			{0, 1, 0, 0},\
			{-sin(radY), 0, cos(radY), 0},\
			{0, 0, 0, 1}};
    double matrice_rotationZ[4][4]={{cos(radZ), -sin(radZ), 0, 0},\
			{sin(radZ), cos(radZ), 0, 0},\
			{0, 0, 1, 0},\
			{0, 0, 0, 1}};
    multiplicationMatrice3d(op,matrice_translationR,matrice_rotationX);
    multiplicationMatrice3d(op,op,matrice_rotationY);
    multiplicationMatrice3d(op,op,matrice_rotationZ);
    multiplicationMatrice3d(op,op,matrice_translation);
    transformationTriangle3d(t,op);
    free(A);
}

void transformationTriangle3d(t_triangle3d *t, double mat[4][4])
{
    multiplicationVecteur3d((*t).abc[0], mat, (*t).abc[0]);
    multiplicationVecteur3d((*t).abc[1], mat, (*t).abc[1]);
    multiplicationVecteur3d((*t).abc[2], mat, (*t).abc[2]);
}

void afficher_coordonnees(t_triangle3d *t)
    {
        printf("%d",(int)(*(*t).abc[0]).xyzt[0]);
        printf("%d",(int)(*(*t).abc[0]).xyzt[1]);
        printf("%d",(int)(*(*t).abc[0]).xyzt[2]);
        printf("%d",(int)(*(*t).abc[1]).xyzt[0]);
        printf("%d",(int)(*(*t).abc[1]).xyzt[1]);
        printf("%d",(int)(*(*t).abc[1]).xyzt[2]);
        printf("%d",(int)(*(*t).abc[2]).xyzt[0]);
        printf("%d",(int)(*(*t).abc[2]).xyzt[1]);
        printf("%d",(int)(*(*t).abc[2]).xyzt[2]);
    }

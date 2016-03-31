#include <assert.h>
#include <math.h>
#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_mat.h"
#include "lib_surface.h"
// cree un nouveau maillon, cf cours algo
t_maillon* __cree_maillon(t_triangle3d *face, Uint32 couleur)
{
	t_maillon* pt_maillon = NULL;
	pt_maillon=(t_maillon*)malloc(sizeof(t_maillon*));
	(*pt_maillon).face=face;
	(*pt_maillon).couleur=couleur;
	(*pt_maillon).pt_suiv=(t_maillon*)malloc(sizeof(t_maillon*));


	return pt_maillon;
}

// insere en tete le maillon, cf cours algo
void __insere_tete(t_objet3d *pt_objet, t_maillon *pt_maillon)
{
    if(pt_objet!=NULL)
    {
        (*pt_maillon).pt_suiv=(*pt_objet).tete;
        (*pt_objet).tete=pt_maillon;
    }
}

t_objet3d *objet_vide()
{
	t_objet3d *pt_objet = NULL;
	pt_objet=(t_objet3d*)malloc(sizeof(t_objet3d*));
    (*pt_objet).tete=(t_maillon*)malloc(sizeof(t_maillon*));
    (*pt_objet).est_camera=false;
    (*pt_objet).est_trie=false;
	return pt_objet;
}

t_objet3d *camera()
{
	t_objet3d *pt_objet = NULL;
	pt_objet=(t_objet3d*)malloc(sizeof(t_objet3d*));
    (*pt_objet).tete=(t_maillon*)malloc(sizeof(t_maillon*));
    (*pt_objet).est_camera=true;
	return pt_objet;
}

t_objet3d* parallelepipede(double lx, double ly, double lz,Uint32 couleur[12])
{
	t_objet3d *pt_objet = objet_vide();
    t_point3d *A1,*A2,*A3,*A4,*A5,*A6,\
    *B1,*B2,*B3,*B4,*B5,*B6,\
    *C1,*C2,*C3,*C4,*C5,*C6,\
    *D1,*D2,*D3,*D4,*D5,*D6,\
    *E1,*E2,*E3,*E4,*E5,*E6,\
    *F1,*F2,*F3,*F4,*F5,*F6;
    t_triangle3d *Aa,*Ab,\
    *Ba,*Bb,\
    *Ca,*Cb,\
    *Da,*Db,\
    *Ea,*Eb,\
    *Fa,*Fb;

    t_maillon* Ta,*Tb,*Tc,*Td,*Te,*Tf,*Tg,*Th,*Ti,*Tj,*Tk,*Tl;
    pt_objet = objet_vide();
    A1=definirPoint3d(lx/2,ly/2,-lz/2);
    A2=definirPoint3d(lx/2,ly/2,-lz/2);
    A3=definirPoint3d(-lx/2,-ly/2,-lz/2);
    A4=definirPoint3d(-lx/2,-ly/2,-lz/2);
    A5=definirPoint3d(lx/2,-ly/2,-lz/2);
    A6=definirPoint3d(-lx/2,ly/2,-lz/2);

    B1=definirPoint3d(lx/2,ly/2,lz/2);
    B2=definirPoint3d(lx/2,ly/2,lz/2);
    B3=definirPoint3d(-lx/2,-ly/2,lz/2);
    B4=definirPoint3d(-lx/2,-ly/2,lz/2);
    B5=definirPoint3d(lx/2,-ly/2,lz/2);
    B6=definirPoint3d(-lx/2,ly/2,lz/2);

    C1=definirPoint3d(lx/2,ly/2,lz/2);
    C2=definirPoint3d(lx/2,ly/2,lz/2);
    C3=definirPoint3d(lx/2,-ly/2,-lz/2);
    C4=definirPoint3d(lx/2,-ly/2,-lz/2);
    C5=definirPoint3d(lx/2,ly/2,-lz/2);
    C6=definirPoint3d(lx/2,-ly/2,lz/2);

    D1=definirPoint3d(-lx/2,ly/2,lz/2);
    D2=definirPoint3d(-lx/2,ly/2,lz/2);
    D3=definirPoint3d(-lx/2,-ly/2,-lz/2);
    D4=definirPoint3d(-lx/2,-ly/2,-lz/2);
    D5=definirPoint3d(-lx/2,ly/2,-lz/2);
    D6=definirPoint3d(-lx/2,-ly/2,lz/2);

    E1=definirPoint3d(lx/2,ly/2,lz/2);
    E2=definirPoint3d(lx/2,ly/2,lz/2);
    E3=definirPoint3d(-lx/2,ly/2,-lz/2);
    E4=definirPoint3d(-lx/2,ly/2,-lz/2);
    E5=definirPoint3d(lx/2,ly/2,-lz/2);
    E6=definirPoint3d(-lx/2,ly/2,lz/2);

    F1=definirPoint3d(lx/2,-ly/2,lz/2);
    F2=definirPoint3d(lx/2,-ly/2,lz/2);
    F3=definirPoint3d(-lx/2,-ly/2,-lz/2);
    F4=definirPoint3d(-lx/2,-ly/2,-lz/2);
    F5=definirPoint3d(lx/2,-ly/2,-lz/2);
    F6=definirPoint3d(-lx/2,-ly/2,lz/2);

    Aa=definirTriangle3d(A1,A3,A5);
    Ab=definirTriangle3d(A2,A4,A6);

    Ba=definirTriangle3d(B1,B3,B5);
    Bb=definirTriangle3d(B2,B4,B6);

    Ca=definirTriangle3d(C1,C3,C5);
    Cb=definirTriangle3d(C2,C4,C6);

    Da=definirTriangle3d(D1,D3,D5);
    Db=definirTriangle3d(D2,D4,D6);

    Ea=definirTriangle3d(E1,E3,E5);
    Eb=definirTriangle3d(E2,E4,E6);

    Fa=definirTriangle3d(F1,F3,F5);
    Fb=definirTriangle3d(F2,F4,F6);

    Ta=__cree_maillon(Aa,couleur[0]);
    Tb=__cree_maillon(Ab,couleur[1]);
    Tc=__cree_maillon(Ba,couleur[2]);
    Td=__cree_maillon(Bb,couleur[3]);
    Te=__cree_maillon(Ca,couleur[4]);
    Tf=__cree_maillon(Cb,couleur[5]);
    Tg=__cree_maillon(Da,couleur[6]);
    Th=__cree_maillon(Db,couleur[7]);
    Ti=__cree_maillon(Ea,couleur[8]);
    Tj=__cree_maillon(Eb,couleur[9]);
    Tk=__cree_maillon(Fa,couleur[10]);
    Tl=__cree_maillon(Fb,couleur[11]);
    //__insere_tete(pt_objet,Ta);
    /*(*Ta).pt_suiv=Tb;
    (*Tb).pt_suiv=Tc;
    (*Tc).pt_suiv=Td;
    (*Td).pt_suiv=Te;
    (*Te).pt_suiv=Tf;
    (*Tf).pt_suiv=Tg;
    (*Tg).pt_suiv=Th;
    (*Th).pt_suiv=Ti;
    (*Ti).pt_suiv=Tj;
    (*Tj).pt_suiv=Tk;
    (*Tk).pt_suiv=Tl;
    (*Tl).pt_suiv=NULL;
    (*pt_objet).tete=Ta;
    */
    __insere_tete(pt_objet,Ta);
    __insere_tete(pt_objet,Tb);
    __insere_tete(pt_objet,Tc);
    __insere_tete(pt_objet,Td);
    __insere_tete(pt_objet,Te);
    __insere_tete(pt_objet,Tf);
    __insere_tete(pt_objet,Tg);
    __insere_tete(pt_objet,Th);
    __insere_tete(pt_objet,Ti);
    __insere_tete(pt_objet,Tj);
    __insere_tete(pt_objet,Tk);
    __insere_tete(pt_objet,Tl);
    (*Ta).pt_suiv=NULL;
	return pt_objet;
}

t_objet3d* sphere(double r, double nlat, double nlong)
{
    int i;
    int j;
    int k;
    t_triangle3d *triangleup[(int)(2*nlong)];
    t_triangle3d *triangledown[(int)(2*nlong)];
    t_triangle3d *triangles[(int)(2*nlong)][(int)nlat-1][2];
    t_maillon *faceup[(int)(2*nlong)];
    t_maillon *facedown[(int)(2*nlong)];
    t_maillon *faces[(int)(2*nlong)][(int)(nlat-1)][2];
	t_objet3d *pt_objet = NULL;
	t_point3d *sommetup[(int)(2*nlong)];
	t_point3d *sommets[(int)(2*nlong)][(int)(nlat)][6];
	t_point3d *sommetdown[(int)(2*nlong)];
    double paslat=M_PI/nlat;
    double paslong=M_PI/nlong;
    double anglelat;
    double anglelong;
	pt_objet = objet_vide();
	for(k=0;k<(2*nlong);k++)
    {
        sommetup[k]=definirPoint3d(0,r,0);
        sommetdown[k]=definirPoint3d(0,-r,0);
    }
    for(k=0;k<4;k++)
    {
        anglelat=-M_PI/2;
        anglelong=0;
        for(i=0;i<2*nlong;i++)
        {
            for(j=0;j<nlat;j++)
            {
                sommets[i][j][k]=definirPoint3d(r*cos(anglelat),r*sin(anglelat),r*cos(anglelat)*cos(anglelong));
                anglelat+=paslat;
            }
        anglelong+=paslong;
        }
    }
    for(k=0;k<(int)(2*nlong)-1;k++)
    {
        triangleup[k]=definirTriangle3d(sommetup[k],sommets[k][0][3],sommets[k+1][0][4]);
        triangledown[k]=definirTriangle3d(sommetdown[k],sommets[k][(int)(nlat-1)][0],sommets[k+1][(int)(nlat-1)][1]);
    }
    triangleup[(int)(2*nlong-1)]=definirTriangle3d(sommetup[(int)(2*nlong-1)],sommets[(int)(2*nlong-1)][0][3],sommets[0][0][4]);
    triangledown[(int)(2*nlong-1)]=definirTriangle3d(sommetdown[(int)(2*nlong-1)],sommets[(int)(2*nlong-1)][(int)(nlat-1)][0],sommets[0][(int)(nlat-1)][1]);
    for(j=0;j<nlat-1;j++)
    {
        for(i=0;i<2*nlong-1;i++)
        {
            triangles[i][j][0]=definirTriangle3d(sommets[i][j][0],sommets[i+1][j][1],sommets[i][j+1][2]);
            triangles[i][j][1]=definirTriangle3d(sommets[i+1][j][3],sommets[i+1][j+1][4],sommets[i][j+1][5]);
        }
        triangles[(int)(2*nlong-1)][j][0]=definirTriangle3d(sommets[(int)(2*nlong-1)][j][0],sommets[0][j][1],sommets[(int)(2*nlong-1)][j+1][2]);
        triangles[(int)(2*nlong-1)][j][1]=definirTriangle3d(sommets[0][j][3],sommets[0][j+1][4],sommets[(int)(2*nlong-1)][j+1][5]);
    }
    for(k=0;k<(int)(2*nlong);k++)
    {

        facedown[k]=__cree_maillon(triangledown[k],1000);
        __insere_tete(pt_objet,facedown[k]);
        if(triangleup[k]!=NULL)
        {
            faceup[k]=__cree_maillon(triangleup[k],1000);
            __insere_tete(pt_objet,faceup[k]);
        }
    }
    /*for(j=0;j<nlat-1;j++)
    {
        for(i=0;i<(2*nlong);i++)
        {
            faces[i][j][0]=__cree_maillon(triangles[i][j][0],1000);
            faces[i][j][1]=__cree_maillon(triangles[i][j][1],1000000);
            __insere_tete(pt_objet,faces[i][j][0]);
            __insere_tete(pt_objet,faces[i][j][1]);
        }
    }*/
    (*facedown[0]).pt_suiv=NULL;

	return pt_objet;
}

t_objet3d* sphere_amiga(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();

	// TODO


	return pt_objet;
}

t_objet3d* arbre(double lx, double ly, double lz)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	// TODO

	return pt_objet;

}

t_objet3d* damier(double lx, double lz, double nx, double nz)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();

	// TODO

	return pt_objet;

}

t_objet3d *copierObjet3d(t_objet3d *o) // attention, effectue une copie mirroir
{
	t_objet3d *n = objet_vide();

	// TODO

	return n;
}

void composerObjet3d(t_objet3d* o, t_objet3d* o2) /* o = o+o2, o2 ne signifiera plus rien */
{

	// TODO

}

void libererObjet3d(t_objet3d *o)
{
	// TODO

}


void __trier_objet(t_objet3d *pt_objet)
{
    double a,b;
    Uint32 ctemp;
    (*pt_objet).est_trie=false;
	t_maillon *A=(*pt_objet).tete;
	t_triangle3d *temp=(t_triangle3d*)malloc(sizeof(t_triangle3d*));
	while(!((*pt_objet).est_trie))
    {
        (*pt_objet).est_trie=true;
        while(A!=NULL && (*A).pt_suiv!=NULL)
        {
            a=moy_prof((*A).face);
            b=moy_prof((*(*A).pt_suiv).face);
            if(a<b)
            {
                temp=(*A).face;
                ctemp=(*A).couleur;
                (*A).couleur=(*(*A).pt_suiv).couleur;
                (*(*A).pt_suiv).couleur=ctemp;
                (*A).face=(*(*A).pt_suiv).face;
                (*(*A).pt_suiv).face=temp;
                (*pt_objet).est_trie=false;
            }
            A=(*A).pt_suiv;
        }
    }

}
void dessinerObjet3d(t_surface *surface, t_objet3d* pt_objet)
{
    if(pt_objet!=NULL){
        t_maillon *A=(*pt_objet).tete;
        __trier_objet(pt_objet);
        //remplirTriangle3d(surface,(*A).face,10000);
        while(A!=NULL)
        {
            remplirTriangle3d(surface,(*A).face,(*A).couleur);
            A=(*A).pt_suiv;
        }
    }
}

void translationObjet3d(t_objet3d* pt_objet, t_point3d *vecteur)
{
    t_maillon *A;
    A=(*pt_objet).tete;
	while(A!=NULL)
    {
        translationTriangle3d((*A).face,vecteur);
        A=(*A).pt_suiv;
    }

}

void rotationObjet3d(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ)
{
	t_maillon *A=(*pt_objet).tete;
	while(A!=NULL)
    {
        rotationTriangle3d((*A).face,centre,degreX,degreY,degreZ);
        A=(*A).pt_suiv;
    }

}

void transformationObjet3d(t_objet3d* pt_objet, double mat[4][4])
{
	// TODO

}
//renvoie la valeur z du centre de gravité d'un triangle 3d de facon a pouvoir les trier selon ce critere
double moy_prof(t_triangle3d* t)
{
    double res;
    res=((*(*t).abc[0]).xyzt[2]+(*(*t).abc[1]).xyzt[2]+(*(*t).abc[2]).xyzt[2])/3;
    return res;
}

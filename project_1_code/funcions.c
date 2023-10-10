#include "header.h"

int pobl[GENT][GENT], pobl2[GENT][GENT], inf[GENT][GENT];

void infeccio(){

    int i,j,p,c1,c2,c3,g,d,t;
    float r,n,mitjm,mitji,mitjv,desvm,desvi,desvv,desm,desi,desv,contm,conti,contv,summ,sumi,sumv;
    int m=1;//Número de matrius que es creen
    float smort[m-1],sinf[m-1],sviu[m-1];

    printf("Quina és la probabilitat de contagiar la malaltia (en percentatge)?\n");
    scanf("%i",&p);
    printf("Quants dies tarda a morir la persona infectada?\n");
    scanf("%i",&d);
    printf("Quants dies passen?\n");
    scanf("%i",&n);
    printf("\n");

    FILE*f1;//S'obre un fitxer
    f1=fopen("Matriu1.txt","w");

    //S'assigna el valor 0 a les variables que utilitzarem com a contadors:
    sumi=summ=sumv=contm=conti=contv=0;

    srand(time(NULL));//Ordre per tal de poder crear nombres aleatoris posteriorment

    //Bucle que calcula la matriu de la població m cops:
    for(g=0;g<m;g++){

        //Cada cop que s'inicia el bucle es posen 0 a totes les posicions de la matriu i una persona infectada al centre:
        for(i=0;i<GENT;i++){
            for(j=0;j<GENT;j++){
                pobl[i][j]=pobl2[i][j]=inf[i][j]=0;
            }
        }

        pobl[GENT/2][GENT/2]=1;//Posem un infectat al mig
        inf[GENT/2][GENT/2]=1;//A la matriu que compta quants dies fa que està infectat, posem un 1 al mig
        pobl2[GENT/2][GENT/2]=1;//Posem un infectat al mig

        //Es crea un bucle que representa el pas del temps, cada bucle es correspondrà amb un dia
        for(t=1;t<n;t++){
            for(j=0;j<GENT;j++){
                for(i=0;i<GENT;i++){
                    r=rand()%(100);// Es crea un nombre aleatori entre 0 i 99 (100 possibilitats)
                    /*per totes les caselles que tenen un 1 al seu voltant i són un 0,
                    si el nombre aleatori entre 0 i 100 està entre 0 i la probabilitat , passen a estar infectats*/
                    if( (pobl[i][j-1]==1 || pobl[i][j+1]==1 || pobl[i-1][j]==1 || pobl[i+1][j]==1) && (pobl[i][j]==0)&&(r>=0)&&(r<p)){
                        pobl2[i][j]=1;
                    }

                    /*Per a cada bucle de temps en què una cel·la tingui un 1, se suma 1 a la matriu inf,
                    que comptabilitza el temps que porta infectada la cel·la*/
                    if(pobl2[i][j]==1){
                        inf[i][j]=inf[i][j]+1;
                    }

                    /*Quan una cel·la porta 5 bucles imfectat (1), la cel·la passa a l'estat 2*/
                    if(inf[i][j]==d){
                        pobl2[i][j]=2;
                    }
                }
            }

            /*Finalment, quan ha passat un període de temps en la matriu, la matriu que s'ha anat modificant
            es guarda en la matriu pobl, que passarà a ser la matriu anterior*/
            for(j=0;j<GENT;j++){
                for(i=0;i<GENT;i++){
                pobl[i][j]=pobl2[i][j];
                }
            }
        }

        c1=0; //Posem els comptadors a 0 al començar cada cop
        c2=0;
        c3=0;

        //Es recorren totes les caselles fent el recompte del nombre de vius, morts i infectats:
        for(i=0;i<GENT;i++){
            for(j=0;j<GENT;j++){
                if(pobl[i][j]==2){
                    c2=c2+1;
                }
                if(pobl[i][j]==1){
                    c1=c1+1;
                }
                if(pobl[i][j]==0){
                    c3=c3+1;
                }
            }
        }

        smort[g]=c2;//Vectors on es guarden el nombre de morts, infectats i vius al final de cada matriu que es crea
        sinf[g]=c1;
        sviu[g]=c3;
    }

    // Es sumen els elements del vector que guarda els nombres de morts, infectats i vius:
    for(i=0;i<m;i++){
        summ=smort[i]+summ;
        sumi=sinf[i]+sumi;
        sumv=sviu[i]+sumv;
    }

    //Es calcula la mitjana:
    mitjm=summ/m;
    mitji=sumi/m;
    mitjv=sumv/m;

    //Es calcula la desviació estadística a partir de la fórmula
    for(i=0;i<m;i++){
        desm=pow(smort[i]-mitjm,2);
        contm=contm+desm;
        desi=pow(sinf[i]-mitji,2);
        conti=conti+desi;
        desv=pow(sviu[i]-mitjv,2);
        contv=contv+desv;
    }

    desvm=sqrt(contm/((m-1)*m));
    desvi=sqrt(conti/((m-1)*m));
    desvv=sqrt(contv/((m-1)*m));

    //S'imprimeixen les dades
    printf("Després de fer %i casos, la mitjana de morts és %f més menys %f\n",m,mitjm,desvm);
    printf("La mitjana d'infectats és %f més menys %f.\n",mitji,desvi);
    printf("La mitjana de vius és %f més menys %f.\n",mitjv,desvv);

    //S'imprimeix la darrera matriu calculada
    for(i=0;i<GENT;i++){
        for(j=0;j<GENT;j++){
            fprintf(f1,"%i\t", pobl[i][j]);
        }
        fprintf(f1,"\n");
    }
}

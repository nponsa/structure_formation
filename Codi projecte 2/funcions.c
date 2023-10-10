
#include "header.h"

int pobl[GENT][GENT], pobl2[GENT][GENT];

void cura(){
    int i,j,i2,j2,a,b,t,tmax,coordax,coorday,coordbx,coordby,c1,c2,cont0,cont1,cont2;

    FILE*f;//S'obre un fitxer
    f=fopen("Matriu.txt","w");

    tmax=1;//S'introdueix el moment en qu� es para el bucle de temps
    cont0=cont1=cont2=0;//Establim a 0 el valor inicial dels contadors

    /*Per pantalla es pregunten el nombre de c�l�les de cada tipus i s'escaneja*/
    printf("Quantes c�l�les del primer tipus hi haur�?\n");
    scanf("%i",&a);
    printf("\nQuantes c�l�les del segon tipus hi haur�?\n");
    scanf("%i",&b);


    /*Es demanen les coordenades x i y de cada c�l�la per cada tipus i es col�loca a la c�l�la el n�mero 1 o 2 corresponent*/
    for(i=0;i<a;i++){
        printf("\nIntrodueix la coordenades x de la part�cula del primer tipus n�mero %i:\n",i+1);
        scanf("%i",&coordax);
        printf("\nIntrodueix la coordenades y de la part�cula del primer tipus n�mero %i:\n",i+1);
        scanf("%i",&coorday);
        pobl[coorday][coordax]=pobl2[coorday][coordax]=1;
    }
    for(i=0;i<b;i++){
        printf("\nIntrodueix la coordenades x de la part�cula del segon tipus n�mero %i:\n",i+1);
        scanf("%i",&coordbx);
        printf("\nIntrodueix la coordenades y de la part�cula del segon tipus n�mero %i:\n",i+1);
        scanf("%i",&coordby);
        pobl[coordby][coordbx]=pobl2[coordby][coordbx]=2;
    }

    printf("\nQuant temps ha de passar?\n");
    scanf("%i",&tmax);
    /*Es crea un bucle de temps on cada bucle �s una unitat de temps*/
    for(t=1;t<=tmax;t++){
        /*Es va anant de cel�la en cel�la*/
        for(i=0;i<GENT;i++){
            for(j=0;j<GENT;j++){
                /*Per a cada cel�la es recorren les vuit c�l�les del voltant i es va fent recompte del nombre de
                c�l�les de cada tipus*/
                c1=c2=0;
                for(i2=i-1;i2<=i+1;i2++){
                    if((i2>=0)&&(i2<GENT)){
                        for(j2=j-1;j2<=j+1;j2++){
                            if((j2>=0)&&(j2<GENT)){
                                if((pobl2[i2][j2]==1)&&(pobl2[i2][j2]!=pobl[i][j])){
                                    c1=c1+1;
                                }
                                if((pobl2[i2][j2]==2)&&(pobl2[i2][j2]!=pobl[i][j])){
                                    c2=c2+1;
                                }
                            }
                        }
                    }
                }

                /*Quan el contador de 2 �s superior, s'apliquen les regles per les dades de 2*/
                if((c2>c1)){
                    if(c2==3||c2==4||c2==5||c2==6){
                        pobl[i][j]=2;
                    }
                    if(c2==7||c2==8){
                        pobl[i][j]=0;
                    }
                }

                /*Quan el contador de 1 �s superior, s'apliquen les regles per les dades de 1*/
                if((c2<c1)){
                    if(c1==3||c1==4||c1==5||c1==6){
                        pobl[i][j]=1;
                    }
                    if(c1==7||c1==8){
                        pobl[i][j]=0;
                    }
                }

                /*Quan els contadors tenen el mateix valor, la c�l�la passa a 0*/
                if((c1==c2)){
                    pobl[i][j]=0;
                }
            }
        }

        /*S'igualen les dues matrius, l'anterior i la constru�da*/
        for(i=0;i<GENT;i++){
            for(j=0;j<GENT;j++){
                pobl2[i][j]=pobl[i][j];
            }
        }
    }

    /*S'imprimeix la matriu en fitxer*/
    for(i=0;i<GENT;i++){
        for(j=0;j<GENT;j++){
            fprintf(f,"%i\t",pobl[i][j]);//Imprimim el valor de cada component de la matriu
            //Comptem el nombre de cada tipus:
            if(pobl[i][j]==0){
                cont0=cont0+1;
            }
            if(pobl[i][j]==1){
                cont1=cont1+1;
            }
            if(pobl[i][j]==2){
                cont2=cont2+1;
            }
        }
        fprintf(f,"\n");
    }

    printf("El nombre de c�l�les de tipus 0 �s: %i\nEl nombre de c�l�les de tipus 1 �s: %i\nEl nombre de c�l�les de tipus 2 �s: %i\n",cont0,cont1,cont2);
}

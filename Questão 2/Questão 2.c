#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char simbAux [2] = {'(',')'};
char conectUn [1] = {'-'};
char conectBi [3] = {'>','#','&'};

int letrasExistentes = 0; //variavel global, já que é usada em duas funções


int checandoSimbAux(char a){
        if(a == simbAux[0]){
            return 1;
          }else if (a == simbAux[1]){
            return 1;
          }else{
            return 0;
          }
      }


int checandoConectUn(char a){
	if(a == conectUn[0]){
		return 1;
	}else{
		return 0;
        }
}


int checandoConectBi(char a){
        if (a==conectBi[0]){
            return 1;
        }else if(a==conectBi[1]){
            return 1;
        }else if(a==conectBi[2]){
            return 1;
        }
        else{
            return 0;
        }
    }


int checagem (char *formula){
  int conectUnExistentes = 0;
  int conectAuxExistentes = 0;
  int conectBiExistentes = 0;

  int tamanhoFormula = strlen(formula);
  //caso 1 = Proposição atômica,só tem um caractere na fórmula.
  if (tamanhoFormula == 1){
      if((isalpha(formula[0]) == 2)){
        return 1;
      }
  }

  //caso 2 =
  if (tamanhoFormula == 2){
    if ((checandoConectUn(formula[0]) == 1)){
        if ((isalpha(formula[1]) == 2)){
          return 1;
        }
    }
  }

  //contador do caso 3
  int contadorUn = 0;
  for (int i = 0; i <= tamanhoFormula; i++){//adicionei um =
        if (formula[i] == conectUn[0]){
          contadorUn = contadorUn + 1;
        }
  }

  //caso 3
  if (contadorUn == tamanhoFormula-1){
      if (isalpha(formula[tamanhoFormula-1] == 2)){
          return 1;
      }
  }


  for (int i = 0; i <= tamanhoFormula; i++){//ADICIONEI UM =
    if (isalpha(formula[i]) == 2){
        letrasExistentes = letrasExistentes + 1;
    }
    if (checandoSimbAux(formula[i]) == 1){
        conectAuxExistentes = conectAuxExistentes + 1;
    }
    if (checandoConectBi(formula[i]) == 1){
        conectBiExistentes = conectBiExistentes + 1;
    }
    if (checandoConectUn(formula[i]) == 1){
        conectUnExistentes = conectUnExistentes + 1;
    }
  }


  if ((letrasExistentes < 2) || (2*conectBiExistentes != conectAuxExistentes) || (conectAuxExistentes < 2) || (conectBiExistentes < 1)){
    return 0;
  }


 for (int i = 0; i <= tamanhoFormula; i++){//ADICIONEI UM =
    //verificando se o caracter é uma letra
    if ((isalpha(formula[i] == 2))){
      if ((isalpha(formula[i+1] == 2) || (checandoConectUn(formula[i+1]) == 1) || (formula[i+1] == '('))){
        return 0;
        continue;
      }
    }else if((checandoSimbAux(formula[i]) == 1)){
      //verifca se o caracter é um simbolo auxiliar
      if (formula[i] == '('){
        if ((formula[i+1] == ')') || (checandoConectBi(formula[i+1]) == 1)){
          return 0;
        }else{
          if((formula[tamanhoFormula] == '(') || ((checandoConectUn(formula[tamanhoFormula]) == 1)) || ((checandoConectBi(formula[tamanhoFormula]) == 1 ))){
            return 0;
          }
        }
        continue;
      }else if((checandoConectUn(formula[i]) == 1)){
        //verifica se o caractere é unario
        if (((isalpha(formula[i+1] == 2)) || (formula[i+1] == '(') || ((checandoConectUn(formula[i+1])== 1)))){
          continue;
        }else{

          return 0;
        }
      }else if ((checandoConectBi(formula[i]) == 1)){
        //verifica se o caractere é binario
        if(((checandoConectBi(formula[i+1]) == 1)) || (formula[i+1] == ')')){
          return 0;
          continue;
        }
      }else{
        return 0;
        }
      }
      return 1;
    }
  }


void inserir (int pos, char *a, char *formula){

  int tamanhoFormula = strlen(formula);

		if(pos==0){//inicio
			for(int i = tamanhoFormula; i > 0; i--){
				formula[i] = formula[i-1];
			}
			formula[pos] = a;
		}else if(pos == tamanhoFormula){//fim
			formula[pos] = a;

		}else{//meio
			for(int i=tamanhoFormula+1; i > pos; i--){
				formula[i]= formula[i-1];
			}
      formula[pos]=a;
    }
}

void remover(int pos, char *formula){ //REMOVER

    int tamanhoFormula = strlen(formula);

 	if (pos < tamanhoFormula){
 		if (pos == tamanhoFormula){
 			int i;
 			for(i=0; i< tamanhoFormula; i++){
 				formula[pos] = formula[i+1];
			 }
			 //cont--;
		 }else{
		 	int i;
		 	for(i = pos; i < tamanhoFormula; i++){
		 		formula[i] = formula[i+1];
			 }
			 //cont--;
		 }
	 }
 }

void empurraNegacao(char *formula){

 	int tamanhoFormula = strlen(formula);
	int i;

 	  for ( i = 0; i < tamanhoFormula; i++){// pecorrer o vetor
 	  	 if(formula[i] == ')'){ // checar se é um parentese fechando
          int aux;
          int aux1 = i;
          for(aux=i;aux>=0;aux--){// voltando o vetor
              int cont = 0;
            if(formula[aux] == '(' && formula[aux-1] == '-'){// checando se a negacao antes do parentese fechando
            	remover(aux-1,formula);//chamada da fucao remover para remover a negacao fora do parentese
                int j;
            	for(j = aux ; j < aux1 ; j++){// pecorrendo novamente o vetor pra frente
            		if((isalpha(formula[j]) == 2)){ //checando se a posição é uma letra
            		     inserir (j+cont, '-', formula);// inderindo uma negacao antes da letra
                         cont = cont + 2;
					}
            		if( formula[j] == '&'){// checando se é uma cunjuçaão para troca
            				formula[j] = '#';
            				cont++;
						}
					if( formula[j] == '#'){// checando se é uma disjuçaão para troca
            				formula[j] = '&';
            				cont++;
						}
                    }
                }
            }
        }
    }
}

void eliminaDuplaNegacao(char *formula){
    int tamanhoFormula = strlen(formula);

     for(int i = 0; i < tamanhoFormula; i++){
        if(formula[i]== '-' && formula[i+1]== '-'){
            remover(i, formula);
            remover(i, formula);
        }
    }
}

int verificaBinario(char a){

    if (a == '&'){
        return 1;
    }
    if (a == '#'){
        return 0;
    }
}

void distributividade (char *formula){
    int tamanhoFormula = strlen(formula);

    char letraaux;
    int aux;

    if (tamanhoFormula == 1){
        return;
    }

    for (int i = 0; i < 100; i++){

      //  0 1 2 3 4 5 6 7 8
           // (-g#(d&a))
        if (formula[i] == '(' && formula[i-1] == '#'){ //1((p#q)&(x#(y&d))) 7((p#q)&(x#(-y&d))) 4(p#q)&(-x#(-y&d))) 3(p#q)&(-x#(y&-d))) 6(p#q)&(x#(-y&-d)))

                 if (isalpha(formula[i-2]) == 2 && formula[i+2] == '&' && formula[i-3] == '('){ // 1((p#q)&(x#(y&d)))5((p#q)&(x#(y&-d)))

                          letraaux = formula[i-2];
                          aux = i;
                        //  7((p#q)&(x#(-y&d))) 6((p#q)&(x#(-y&-d)))
                          remover(aux-1, formula);
                          aux--;
                          remover(aux-1, formula);
                          aux--;
                          inserir(aux+1, letraaux, formula);
                          aux--;
                          inserir(aux+5, letraaux, formula);
                          aux++;
                          inserir(aux+2, '#', formula);
                          aux--;
                          inserir(aux+7, '#', formula);
                          aux++;
                          inserir(aux+5, '(', formula);
                          aux--;
                          inserir(aux+5, ')', formula);
                          aux++;


                     }
                 if (isalpha(formula[i-2]) == 2 && formula[i+3] == '&' && formula[i-3] == '(' ){//  7((p#q)&(x#(-y&d))) 6((p#q)&(x#(-y&-d)))
                        letraaux = formula[i-2];
                        aux = i;

                        remover(aux-1, formula);
                        aux--;
                        remover(aux-1, formula);
                        aux--;
                        inserir(aux+1, letraaux, formula);
                        aux--;
                        inserir(aux+6, letraaux, formula);
                        aux++;
                        inserir(aux+2, '#', formula);
                        aux--;
                        inserir(aux+8, '#', formula);
                        aux++;
                        inserir(aux+6, '(', formula);
                        aux--;
                        inserir(aux+6, ')', formula);
                        aux++;


                     }
                 if (isalpha(formula[i-3]) != 2 && formula[i+2] == '&'){//3((p#q)&(-x#(y&-d))) 2((p#q)&(-x#(y&d)))
                        letraaux = formula[i-2];
                        aux = i;

                        remover(aux-1, formula);
                        aux--;
                        remover(aux-1, formula);
                        aux--;
                        remover(aux-1, formula);
                        aux--;
                        inserir(aux+1, letraaux, formula);
                        aux--;
                        inserir(aux+5, letraaux, formula);
                        aux++;
                        inserir(aux+2, '#', formula);
                        aux--;
                        inserir(aux+7, '#', formula);
                        aux++;
                        inserir(aux+5, '(', formula);
                        aux--;
                        inserir(aux+5, ')', formula);
                        aux++;
                        inserir(aux+7, '-', formula);
                        aux--;
                        inserir(aux+2, '-', formula);
                        aux++;

                 }
                if (isalpha(formula[i-3]) != 2 && formula[i+3] == '&' && isalpha(formula[i+2]) == 2){ // 4((p#q)&(-x#(-y&d))) 8((p#q)&(-x#(-y&-d)))
                        letraaux = formula[i-2];
                        aux = i;

                        remover(aux-1, formula);
                        aux--;
                        remover(aux-1, formula);
                        aux--;
                        remover(aux-1, formula);
                        aux--;
                        inserir(aux+1, letraaux, formula);
                        aux--;
                        inserir(aux+6, letraaux, formula);
                        aux++;
                        inserir(aux+2, '#', formula);
                        aux--;
                        inserir(aux+8, '#', formula);
                        aux++;
                        inserir(aux+6, '(', formula);
                        aux--;
                        inserir(aux+6, ')', formula);
                        aux++;
                        inserir(aux+8, '-', formula);
                        aux--;
                        inserir(aux+2, '-', formula);
                        aux++;




                }

            }
        if(formula[i] == ')' && formula[i+1] == '#'){//((y&d)#x)

                 if((isalpha(formula[i+2])) == 2 && formula[i-2] == '-' && formula[i-3] == '&' ){ //((p#q)&((y#-d)#-x))

                        letraaux = formula[i+2];
                        int aux = i;

                        remover(aux+1, formula);
                        remover(aux+1, formula);
                        inserir(aux, letraaux, formula);
                        aux++;
                        inserir(aux-4, letraaux, formula);
                        aux++;
                        inserir(aux-1, '#', formula);
                        aux++;
                        inserir(aux-6, '#', formula);
                        aux++;
                        inserir(aux-4, '(', formula);
                        aux++;
                        inserir(aux-6, ')', formula);
                        aux++;

                       }
                if(formula[i-2] == '-' && formula[i+2] == '-' && formula[i-3] == '&' ){ //((p#q)&((y#-d)#-x)) ee ((p#q)&((-y&-d)#-x))

                          letraaux = formula[i+3];
                          aux = i;

                          remover(aux+1, formula);
                          remover(aux+1, formula);
                          remover(aux+1, formula);
                          inserir(aux, letraaux, formula);
                          aux++;
                          inserir(aux-4, letraaux, formula);
                          aux++;
                          inserir(aux-1, '-', formula);
                          aux++;
                          inserir(aux-6, '-', formula);
                          aux++;
                          inserir(aux-4, '(', formula);
                          aux++;
                          inserir(aux-6, ')', formula);
                          aux++;
                          inserir(aux-2, '#', formula);
                          aux++;
                          inserir(aux-10, '#', formula);
                          aux++;

                  }
                if(formula[i-4] == '-' && formula[i+2] == '-' && formula[i-2] == '&' ){//((p#q)&((-y#d)#-x))
                    letraaux = formula[i+3];
                    aux = i;

                    remover(aux+1, formula);
                    remover(aux+1, formula);
                    remover(aux+1, formula);
                    inserir(aux, letraaux, formula);
                    aux++;
                    inserir(aux-3, letraaux, formula);
                    aux++;
                    inserir(aux-1, '-', formula);
                    aux++;
                    inserir(aux-5, '-', formula);
                    aux++;
                    inserir(aux-4, ')', formula);
                    aux++;
                    inserir(aux-3, '(', formula);
                    aux++;
                    inserir(aux-2, '#', formula);
                    aux++;
                    inserir(aux-9, '#', formula);
                    aux++;

                   }

                if(isalpha(formula[i+2]) == 2 && formula[i-2] == '&'){//((p#q)&((y&d)#x))

                    letraaux = formula[i+2];
                    aux = i;

                    remover(aux+1, formula);
                    remover(aux+1, formula);
                    inserir(aux, letraaux, formula);
                    aux++;
                    inserir(aux-3, letraaux, formula);
                    aux++;
                    inserir(aux-1, '#', formula);
                    aux++;
                    inserir(aux-5, '#', formula);
                    aux++;
                    inserir(aux-4, ')', formula);
                    aux++;
                    inserir(aux-3, '(', formula);
                    aux++;

                       }
                if(isalpha(formula[i+3]) == 2 && formula[i+2] == '-'&& formula[i-2] == '&'){//(((y&d)#x)&((y&d)#-x)&(x#(y&d)))

                    aux = i;
                    letraaux = formula[i+3];
                    remover(aux+1, formula);

                    remover(aux+1, formula);
                    remover(aux+1, formula);
                    inserir(aux-1, letraaux, formula);
                    aux++;
                    inserir(aux-4, letraaux, formula);
                    aux++;
                    inserir(aux-5, '-', formula);
                    aux++;
                    inserir(aux-2, '-', formula);
                    aux++;
                    inserir(aux-1, '#', formula);
                    aux++;
                    inserir(aux-6, '#', formula);
                    aux++;
                    inserir(aux-4, '(', formula);
                    aux++;
                    inserir(aux-6, ')', formula);
                    aux++;

                }


            }
            if(formula[i] == '(' && formula[i-1] == '#' && formula[i-2] == ')' ){
                  char letraaux1;
                  char letraaux2;
                  char letraaux3;
                    if(isalpha(formula[i+1]) == 2 && isalpha(formula[i+3]) == 2 && isalpha(formula[i-3]) == 2 && isalpha(formula[i-5]) == 2 && formula[i+2] == '&'){//1((p&q)#(r&t))

                      //((p&q)#(r&t)) // ((-p&q)#(r&t))
                        aux = i;

                        formula[i-1] = '&';
                        letraaux  = formula[i+1]; //r
                        letraaux1 = formula[i+3]; //t
                        letraaux2 = formula[i-3]; //q
                        letraaux3 = formula[i-5]; //p

                        formula[i+1] =  letraaux3;    //((p&q)#(p&q))
                        formula[i+3] =  letraaux2;

                        inserir(aux-2, letraaux, formula);//((pr&q)#(p&q))
                        aux++;
                        inserir(aux-5, letraaux, formula);//((pr&rq)#(p&q))
                        aux++;
                        inserir(aux+1, letraaux1, formula);//((pr&rq)#(pt&q))
                        inserir(aux+4, letraaux1, formula);//((pr&rq)#(pt&tq))
                        inserir(aux-3, '#', formula);//((pr&r#q)#(pt&tq))
                        aux++;
                        inserir(aux-7, '#', formula);//((p#r&r#q)#(pt&tq))
                        aux++;
                        inserir(aux+2,'#', formula);//((p#r&r#q)#(p#t&tq))
                        inserir(aux+6,'#', formula);//((p#r&r#q)#(p#t&t#q))
                        inserir(aux+5,'(', formula);//((p#r&r#q)#(p#t&(t#q))
                        inserir(aux+4,')', formula);//((p#r&r#q)#(p#t)&(t#q))
                        inserir(aux-5,'(', formula);//((p#r&(r#q)#(p#t)&(t#q))
                        aux++;
                        inserir(aux-7,')', formula);//((-p#r)&(r#q)#(t#-p)&(t#q))
                        aux++;

                        if(formula[aux-12] == '-'){//((-p&q)#(r&t))
                           inserir(aux+3,'-', formula);
                        }

                    }//3((-p&-q)#(r&t))
                    if(isalpha(formula[i+1]) == 2 && isalpha(formula[i+3]) == 2 && isalpha(formula[i-3]) == 2 && isalpha(formula[i-6]) == 2 && formula[i+2] == '&'){

                        //((-p&-q)#(r&t)) //((p&-q)#(r&t))
                        aux = i;

                        formula[i-1] = '&';
                        letraaux  = formula[i+1]; //r
                        letraaux1 = formula[i+3]; //t
                        letraaux2 = formula[i-3]; //q
                        letraaux3 = formula[i-6]; //p

                        formula[i+1] =  letraaux3;    //((-p&-q)#(p&q))
                        formula[i+3] =  letraaux2;

                        inserir(aux-5, letraaux, formula);//((-pr&-q)#(p&q))
                        aux++;
                        inserir(aux-2, letraaux, formula);//((-pr&-qr)#(p&q))
                        aux++;
                        inserir(aux+1, letraaux1, formula);//((-pr&r-q)#(pt&q))
                        inserir(aux+4, letraaux1, formula);//((-pr&r-q)#(pt&tq))
                        inserir(aux-3, '#', formula);//((-pr&r#-q)#(pt&tq))
                        aux++;
                        inserir(aux-8, '#', formula);//((-p#r&r#-q)#(pt&tq))
                        aux++;
                        inserir(aux+2,'#', formula);//((-p#r&r#-q)#(p#t&tq))
                        inserir(aux+6,'#', formula);//((-p#r&r#-q)#(p#t&t#q))
                        inserir(aux+5,'(', formula);//((p#r&r#q)#(p#t&(t#q))
                        inserir(aux+4,')', formula);//((-p#r&r#-q)#(p#t)&(t#q))
                        inserir(aux-6,'(', formula);//((-p#r&(r#-q)#(p#t)&(t#q))
                        aux++;
                        inserir(aux-8,')', formula);//((-p#r)&(r#-q)#(t#p)&(t#q))
                        aux++;
                        inserir(aux+3,'-', formula);//((-p#r)&(r#-q)#(t#-p)&(t#q))
                        inserir(aux+10,'-', formula);//((-p#r)&(r#-q)#(t#-p)&(t#q))  ((p&-q)#(r&t))
                        if(formula[aux-13] == '('){
                           remover(aux+3, formula);
                        }
                    }
                    if((isalpha(formula[i+2]) == 2 && isalpha(formula[i+4]) == 2 && isalpha(formula[i-3]) == 2 && isalpha(formula[i-6]) == 2)){//4((-p&-q)#(-r&t))
                        // 4((-p&-q)#(-r&t)) 7((p&-q)#(-r&t))
                        aux = i;

                        formula[i-1] = '&';
                        letraaux  = formula[i+2]; //r
                        letraaux1 = formula[i+4]; //t
                        letraaux2 = formula[i-3]; //q
                        letraaux3 = formula[i-6]; //p

                        formula[i+2] =  letraaux3;  //((-p&-q)#(-p&q))
                        formula[i+4] =  letraaux2;

                        inserir(aux-5, letraaux, formula);//((-pr&-q)#(-p&q))
                        aux++;
                        inserir(aux-2, letraaux, formula);//((-pr&-q)#(-p&q))
                        aux++;
                        inserir(aux+1, letraaux1, formula);//((-pr&-qr)#(t-p&q))
                        inserir(aux+5, letraaux1, formula);//((-pr&-qr)#(t-p&tq))
                        inserir(aux-3, '#', formula);//((-pr&r#-q)#(-pt&tq))
                        aux++;
                        inserir(aux-8, '#', formula);//((-p#r&r#-q)#(-pt&tq))
                        aux++;
                        inserir(aux+2,'#', formula);//((-p#r&r#-q)#(-p#t&tq))
                        inserir(aux+7,'#', formula);//((-p#r&r#-q)#(-p#t&t#q))
                        inserir(aux+6,'(', formula);//((p#r&r#-q)#(-p#t&(t#q))
                        inserir(aux+5,')', formula);//((-p#r&r#-q)#(-p#t)&(t#q))
                        inserir(aux-6,'(', formula);//((-p#r&(r#-q)#(p#t)&(t#q))
                        aux++;
                        inserir(aux-8,')', formula);//((-p#r)&(r#-q)#(t#-p)&(t#q))
                        aux++;
                        inserir(aux+10,'-', formula);//((-p#r)&(r#-q)#(t#-p)&(t#-q))
                        inserir(aux-10,'-', formula);//((-p#-r)&(r#-q)#(t#-p)&(t#-q))
                        aux++;
                        inserir(aux-3,'-', formula);//((-p#-r)&(r#-q)#(t#-p)&(t#-q))
                        aux++;

                        if(formula[i-2]){
                          remover(aux+3, formula);
                        }
                 }if((isalpha(formula[i+2]) == 2 && isalpha(formula[i+5]) == 2 && isalpha(formula[i-3]) == 2 && isalpha(formula[i-6]) == 2)){//5((-p&-q)#(-r&-t))
                         //5((-p&-q)#(-r&-t))
                        aux = i;

                        formula[i-1] = '&';
                        letraaux  = formula[i+2]; //r
                        letraaux1 = formula[i+5]; //t
                        letraaux2 = formula[i-3]; //q
                        letraaux3 = formula[i-6]; //p

                        formula[i+2] =  letraaux3;  //((-p&-q)#(-p&-q))
                        formula[i+5] =  letraaux2;

                        inserir(aux-5, letraaux, formula);//((-pr&-q)#(-p&-q))
                        aux++;
                        inserir(aux-2, letraaux, formula);//((-pr&-q)#(-p&-q))
                        aux++;
                        inserir(aux+1, letraaux1, formula);//((-pr&-qr)#(t-p&-q))
                        inserir(aux+5, letraaux1, formula);//((-pr&-qr)#(t-p&t-q))
                        inserir(aux-3, '#', formula);//((-pr&r#-q)#(-pt&t-q))
                        aux++;
                        inserir(aux-8, '#', formula);//((-p#r&r#-q)#(-pt&t-q))
                        aux++;
                        inserir(aux+2,'#', formula);//((-p#r&r#-q)#(-p#t&tq))
                        inserir(aux+7,'#', formula);//((-p#r&r#-q)#(-p#t&t#q))
                        inserir(aux+6,'(', formula);//((p#r&r#-q)#(-p#t&(t#-q))
                        inserir(aux+5,')', formula);//((-p#r&r#-q)#(-p#t)&(t#-q))
                        inserir(aux-6,'(', formula);//((-p#r&(r#-q)#(p#t)&(t#-q))
                        aux++;
                        inserir(aux-8,')', formula);//((-p#r)&(r#-q)#(t#-p)&(t#-q))
                        aux++;
                        inserir(aux+8,'-', formula);//((-p#r)&(r#-q)#(t#-p)&(-t#-q))
                        inserir(aux+1,'-', formula);//((-p#r)&(r#-q)#(-t#-p)&(-t#-q))
                        inserir(aux-3,'-', formula);//((-p#r)&(-r#-q)#(-t#-p)&(-t#-q))
                        aux++;
                        inserir(aux-11,'-', formula);//((-p#r)&(r#-q)#(-t#-p)&(-t#-q))
                        aux++;

                        if(formula[aux-15] == '('){//6((p&-q)#(-r&-t))
                           remover(aux+4, formula);//((p#r)&(r#-q)#(-t#p)&(-t#-q))
                        }
                  }if((isalpha(formula[i+1]) == 2 && isalpha(formula[i+4]) == 2 && isalpha(formula[i-3]) == 2 && isalpha(formula[i-6]) == 2)){//8((p&-q)#(r&-t))
                       //8((p&-q)#(r&-t))
                        aux = i;

                        formula[i-1] = '&';
                        letraaux  = formula[i+1]; //r
                        letraaux1 = formula[i+4]; //t
                        letraaux2 = formula[i-3]; //q
                        letraaux3 = formula[i-6]; //p

                        formula[i+1] =  letraaux3;  //((p&-q)#(p&-q))
                        formula[i+4] =  letraaux2;

                        inserir(aux-5, letraaux, formula);//((-pr&-q)#(p&-q))
                        aux++;
                        inserir(aux-2, letraaux, formula);//((-pr&-qr)#(p&-q))
                        aux++;
                        inserir(aux+1, letraaux1, formula);//((-pr&-qr)#(tp&-q))
                        inserir(aux+4, letraaux1, formula);//((-pr&-qr)#(tp&t-q))
                        inserir(aux-3, '#', formula);//((-pr&r#-q)#(-pt&t-q))
                        aux++;
                        inserir(aux-8, '#', formula);//((-p#r&r#-q)#(-pt&t-q))
                        aux++;
                        inserir(aux+2,'#', formula);//((-p#r&r#-q)#(t#p&t-q))
                        inserir(aux+6,'#', formula);//((-p#r&r#-q)#(t#p&t#-q))
                        inserir(aux+5,'(', formula);//((p#r&r#-q)#(p#t&(t#-q))
                        inserir(aux+4,')', formula);//((p#r&r#-q)#(p#t)&(t#-q))
                        inserir(aux-6,'(', formula);//((p#r&(r#-q)#(p#t)&(t#-q))
                        aux++;
                        inserir(aux-8,')', formula);//((p#r)&(r#-q)#(t#p)&(t#-q))
                        aux++;
                        inserir(aux+7,'-', formula);//((p#r)&(r#-q)#(t#p)&(t#-q))
                        inserir(aux+1,'-', formula);//((p#r)&(r#-q)#(-t#p)&(-t#-q))
                 }
                 if((isalpha(formula[i+2]) == 2 && isalpha(formula[i+4]) == 2 && isalpha(formula[i-3]) == 2 && isalpha(formula[i-5]) == 2)){//10((-p&q)#(-r&t))

                        //10((-p&q)#(-r&t))
                        aux = i;

                        formula[i-1] = '&';
                        letraaux  = formula[i+2]; //r
                        letraaux1 = formula[i+4]; //t
                        letraaux2 = formula[i-3]; //q
                        letraaux3 = formula[i-5]; //p

                        formula[i+2] =  letraaux3;  //((-p&q)#(-p&q))
                        formula[i+4] =  letraaux2;

                        inserir(aux-4, letraaux, formula);//((-pr&q)#(p&-q))
                        aux++;
                        inserir(aux-2, letraaux, formula);//((-pr&qr)#(p&-q))
                        aux++;
                        inserir(aux+1, letraaux1, formula);//((-pr&qr)#(tp&-q))
                        inserir(aux+5, letraaux1, formula);//((-pr&qr)#(tp&t-q))
                        inserir(aux-3, '#', formula);//((-pr&r#q)#(tp&t-q))
                        aux++;
                        inserir(aux-7, '#', formula);//((-p#r&r#q)#(tp&t-q))
                        aux++;
                        inserir(aux+6,'#', formula);//((-p#r&r#q)#(tp&t#-q))
                        inserir(aux+2,'#', formula);//((-p#r&r#q)#(t#p&t-q))
                        inserir(aux+6,'(', formula);//((-p#r&r#q)#(t#p&(t-q))
                        inserir(aux+5,')', formula);//((-p#r&r#q)#(t#p)&(t-q))
                        inserir(aux-5,'(', formula);//((-p#r&(r#q)#(t#p)&(t-q))
                        aux++;
                        inserir(aux-7,')', formula);//((-p#r)&(r#q)#(t#p)&(t-q))
                        aux++;
                        inserir(aux-3,'-', formula);//((-p#r)&(r-#q)#(t#p)&(t-q))
                        aux++;

                        inserir(aux-10,'-', formula);//((-p#r)&(r-#q)#(t#p)&(t-q))
                        aux++;
                 }if((isalpha(formula[i+1]) == 2 && isalpha(formula[i+4]) == 2 && isalpha(formula[i-3]) == 2 && isalpha(formula[i-5]) == 2)){//11((-p&q)#(r&-t))
                         //11((-p&q)#(r&-t))
                        aux = i;

                        formula[i-1] = '&';
                        letraaux  = formula[i+1]; //r
                        letraaux1 = formula[i+4]; //t
                        letraaux2 = formula[i-3]; //q
                        letraaux3 = formula[i-5]; //p


                        formula[i+1] =  letraaux3;  //((-p&q)#(p&-q))
                        formula[i+4] =  letraaux2;

                        inserir(aux-4, letraaux, formula);//((-pr&q)#(p&-q))
                        aux++;
                        inserir(aux-2, letraaux, formula);//((-pr&qr)#(p&-q))
                        aux++;
                        inserir(aux+1, letraaux1, formula);//((-pr&qr)#(tp&-q))
                        inserir(aux+4, letraaux1, formula);//((-pr&qr)#(tp&t-q))
                        inserir(aux-6, '#', formula);//((-p#r&rq)#(tp&t-q))
                        aux++;
                        inserir(aux-3, '#', formula);//((-p#r&r#q)#(tp&t-q))
                        aux++;
                        inserir(aux+5,'#', formula);//((-p#r&r#q)#(tp&t#-q))
                        inserir(aux+2,'#', formula);//((-p#r&r#q)#(t#p&t#-q))
                        inserir(aux+5,'(', formula);//((-p#r&r#q)#(t#p&(t#-q))
                        inserir(aux+4,')', formula);//((-p#r&r#q)#(t#p)&(t#-q))
                        remover(aux+9, formula);
                        inserir(aux-5,'(', formula);//((-p#r&(r#q)#(t#p)&(t#q))
                        aux++;
                        inserir(aux-7,')', formula);//((-p#r)&(r#q)#(t#p)&(t#q))
                        aux++;
                        inserir(aux+7,'-', formula);//((-p#r)&(r#q)#(t#p)&(-t#q))
                        inserir(aux+3,'-', formula);//((-p#r)&(r#q)#(t#-p)&(-t#q))
                        inserir(aux+1,'-', formula);//((-p#r)&(r#q)#(-t#-p)&(-t#q))

                 }if((isalpha(formula[i+2]) == 2 && isalpha(formula[i+5]) == 2 && isalpha(formula[i-3]) == 2 && isalpha(formula[i-5]) == 2)){//12((-p&q)#(-r&-t))
                       //12((-p&q)#(-r&-t))
                        aux = i;

                        formula[i-1] = '&';
                        letraaux  = formula[i+2]; //r
                        letraaux1 = formula[i+5]; //t
                        letraaux2 = formula[i-3]; //q
                        letraaux3 = formula[i-5]; //p


                        formula[i+2] =  letraaux3;  //((-p&q)#(-p&-q))
                        formula[i+5] =  letraaux2;

                        inserir(aux-2, letraaux, formula);//((-pr&q)#(-p&-q))
                        aux++;
                        inserir(aux-5, letraaux, formula);//((-pr&qr)#(-p&-q))
                        aux++;
                        inserir(aux+1, letraaux1, formula);//((-pr&qr)#(t-p&-q))
                        inserir(aux+6, letraaux1, formula);//((-pr&qr)#(t-p&-tq))
                        inserir(aux-6, '#', formula);//((-p#r&rq)#(tp&t-q))
                        aux++;
                        inserir(aux-3, '#', formula);//((-p#r&r#q)#(t-p&-tq))
                        aux++;
                        inserir(aux+7,'#', formula);//((-p#r&r#q)#(t-p&-t#q))
                        inserir(aux+2,'#', formula);//((-p#r&r#q)#(t#-p&-t#q))
                        inserir(aux+6,'(', formula);//((-p#r&r#q)#(t#-p&(-t#q))

                        inserir(aux+5,')', formula);//((-p#r&r#q)#(t#-p)&(-t#q))
                        inserir(aux-5,'(', formula);//((-p#r&(r#q)#(t#-p)&(-t#q))
                        aux++;
                        inserir(aux-7,')', formula);//((-p#r)&(r#q)#(t#-p)&(-t#q))
                        aux++;
                        inserir(aux+1,'-', formula);//((-p#r)&(r#q)#(-t#-p)&(-t#q))
                        inserir(aux-3,'-', formula);//((-p#r)&(-r#q)#(-t#-p)&(-t#q))
                        aux++;

                        inserir(aux-10,'-', formula);//((-p#r)&(-r#q)#(-t#-p)&(-t#q))
                        aux++;

                 }

    }
 }
}

void solucao (char *formula){//Verificar a lógica

 int tamanhoFormula = strlen(formula);

 //char negacao[1] = {'-'};
    for (int i = 0; i < tamanhoFormula; i++){
    int aux;
      if (formula[i] == '>'){
        formula[i] = '#';

        aux = i;
        if ((isalpha(formula[aux-1]) == 2)){

            inserir(aux-1, '-', formula);
        }
        aux = i;
        if (formula[aux-1] == ')'){
            aux = i;
            while((formula[aux])!='('){
            aux--;
            }
            inserir(aux, '-', formula);
          }

        }
      }
    printf("A formula sem implicacoes: %s\n", formula);
    empurraNegacao(formula);
    printf("Empurrou a negacao: %s\n", formula);
    eliminaDuplaNegacao(formula);
    printf("Eliminou a dupla negacao: %s\n", formula);
    distributividade(formula);
    printf("Aplicou a distributividade: %s\n", formula);

    }


int main(void) {

  char formula[100];
  printf("Digite uma Formula:\n");
  gets(formula);

  int checador;

  checador = checagem(formula);

 if(checador == 1){
      solucao(formula);
      printf("\n\nFormula transformada: %s\n", formula);

 }else{
		  printf("Nao foi possivel converter, pois a formula digitada nao eh proposicional!\n");
      }


  return 0;
}

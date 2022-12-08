#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char simbAux [2] = {'(',')'};
char conectUn [1] = {'-'};
char conectBi [3] = {'>','#','&'};


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
  int letrasExistentes = 0;
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

int main(void) {
    char formula[100];
    printf("Digite uma Formula:\n");
    gets(formula);

    int checador;

    checador = checagem(formula);

    if(checador == 1){
		  printf("Eh formula");
	  }else{
		  printf("Nao eh formula");
      }

  return 0;
}

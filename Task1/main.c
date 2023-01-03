#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//function declaration
int sFloorToInt(char sFloor[]);
const char* printLiftStatus(int dFloorNum);
void printButtons();

int main(){


	//variable declaration
	char sFloorDefault[5] = "G";
	char sFloorChosen[5] = "G";
	char sStopping[5];
	char sFloorNewDefault[5] = "G";
	char sUserInput[5];
	int dFloorDefaultInt=sFloorToInt(sFloorDefault);
	int dFloorChosenInt;
	int dFloorNewDefaultInt;

	// // while (1){
	// 	if(floorToInt(dFloor)==10){
	// 		printf("There is no such floor.\n");
	// 		break;
	// 	}
	// 	else{
	// 		printLiftStatus(dFloor);
	// 		break;
	// 	}
	// // }
	printf("\nHi there! Where am I taking you?\n");
	printf("If you want to stop the lift anywhere, type in YES.\n");
	printf("If you want to exit the lift, type in EXIT.\n");
	printf("You are now on floor G.\n");
	//mainwhile
	while(1){

		
		//take user input to change floors
		printf("\n");
		printButtons();
		//fgets(dFloorChosen,3,stdin);
		scanf("%s", sFloorChosen);

		if (strncmp(sFloorChosen, "EXIT", 4)==0){
			printf("Leaving so soon? Bye.\n");
			break;
		}//endif

		strcpy(sFloorDefault,sFloorNewDefault);

		//change two floor variables to integers
		dFloorChosenInt=sFloorToInt(sFloorChosen);
		dFloorDefaultInt=sFloorToInt(sFloorDefault);
		//dFloorNewDefaultInt=sFloorToInt(sFloorNewDefault);

		

		//check for wrong input
		if(sFloorToInt(sFloorChosen)==10){

			//if it is wrong print error message and continue while loop
			printf("There is no such floor.\n");
			continue;
		}//endif


		//if the chosen floor is higher travel up
		if (dFloorChosenInt>dFloorDefaultInt){

			while(dFloorChosenInt>dFloorDefaultInt){
				dFloorDefaultInt++;
				printf("\nYou're currently at floor %s",printLiftStatus(dFloorDefaultInt));
				
				strcpy(sFloorNewDefault,printLiftStatus(dFloorDefaultInt));
				if ( dFloorDefaultInt != dFloorChosenInt ) {
					printf("\nStopping here?\n");
					scanf("%s",sStopping);
					if (strcmp(sStopping,"YES")==0){
					break;
					}//endif
				}
			}//endwhile
			
		}//endif

		//if equal no change is made, continue while
		else if(dFloorChosenInt==dFloorDefaultInt){
			printf("You're already here.\n");
		}

		//if not travel down
		else{
			while(dFloorChosenInt<dFloorDefaultInt){
				dFloorDefaultInt--;
				printf("\nYou're currently at floor %s",printLiftStatus(dFloorDefaultInt));
				strcpy(sFloorNewDefault,printLiftStatus(dFloorDefaultInt));
				if ( dFloorDefaultInt != dFloorChosenInt ) {
					printf("\nStopping here?\n");
					scanf("%s",sStopping);
					if (strcmp(sStopping,"YES")==0){
					break;
					}//endif
				}
			}//endwhile
		}//endelse


		if(strcmp(sFloorNewDefault,sFloorChosen)!=0){
			printf("\n\nGoing to floor %s.\n",sFloorChosen);
			printf("If you want to ride again, call the elevator with CALL.\n");

			scanf("%s",sUserInput);

			if(strcmp(sUserInput,"CALL")==0){

				printf("\n\nComing from floor %s.\n",sFloorChosen);

				while(dFloorDefaultInt>dFloorChosenInt){
					dFloorChosenInt++;
					printf("Lift at floor %s.\n", printLiftStatus(dFloorChosenInt));

				}
				while(dFloorDefaultInt<dFloorChosenInt){
					dFloorChosenInt--;
					printf("Lift at floor %s.\n", printLiftStatus(dFloorChosenInt));

				}
			}//endif
			else{
				printf("Leaving so soon? Bye.!\n");
				return 0;
			}//endifelse
		}//endif
	}//endmainwhile


		
	
	




	return 0;
}//endmain

int sFloorToInt(char sFloor[]){
	int dFloorNum;
	dFloorNum = atoi(sFloor);

	if (dFloorNum==0){
		if(strncmp(sFloor, "G",1)==0){
		 	 return dFloorNum = 0;
		}
		else if( strncmp(sFloor, "B1",2) == 0){
			
			 return dFloorNum = -1;
		}
		else if( strncmp(sFloor, "B2",2) == 0){
			 return dFloorNum = -2;
		}
		else if( strncmp(sFloor, "B3",2) == 0){
			 return dFloorNum = -3;
		}
		else{
			return 10;
		}
	}
	if(dFloorNum>5 || dFloorNum<0){
		return 10;
	}
	else{
		return dFloorNum;
	}
		
}//endfunction




const char* printLiftStatus(int dFloorNum){
	printf("\n");
	static char sFloorString[5];

	if(dFloorNum > 0){
		sprintf(sFloorString,"%d",dFloorNum);

	}
	else if (dFloorNum == 0){

		sprintf(sFloorString,"G");
	}
	else if (dFloorNum == -1){

		sprintf(sFloorString,"B1");
	}
	else if (dFloorNum == -2){

		sprintf(sFloorString,"B2");
	}
	else if (dFloorNum == -3){

		sprintf(sFloorString,"B3");
	}
	return sFloorString;

}//endfunction


// void printLiftStatus(int dFloorNum){
// 	printf("\n");

// 	if(dFloorNum > 0){
// 		printf("You're at floor %d.\n",dFloorNum);
// 	}
// 	else if (dFloorNum == 0){

// 		printf("You're at floor G.\n");
// 	}
// 	else if (dFloorNum == -1){

// 		printf("You're at floor B1.\n");
// 	}
// 	else if (dFloorNum == -2){

// 		printf("You're at floor B2.\n");
// 	}
// 	else if (dFloorNum == -3){

// 		printf("You're at floor B3.\n");
// 	}

// }//endfunction

void printButtons(){

	printf("Select a floor to ride the elevator.\n\n");
	printf(" \n");
	printf(" [ 3 ] [ 4 ] [ 5 ]\n");
	printf(" [ G ] [ 1 ] [ 2 ]\n");
	printf("[ B3 ] [ B2 ] [ B1 ]\n");

}//endfunction

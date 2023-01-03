//elevator controller program in C
/* program simulates the behaviour of the elevator
 user inputs desired floor and elevator travels to that floor
 user can exit by typing EXIT
 user can stop on any floor on the way to the desired one by typing YES
 if user leaves before reaching desired floor, and wants to ride again he types in CALL
 and elevator gets called from the desired floor

 elevator can also accept different number of passengers (up to 4)
 if the number of passengers is bigger than 4 at any point, lift will as many as can fit (4)
 passengers can enter or exit at any floor 
*/




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//function declaration on beginning of the program
//so the compiler knows that im going to use them
//functions are defined below main
int sFloorToInt(char sFloor[]);
const char* intToFloor(int dFloorNum);
void printWelcome();
void printButtons();
void printStatus(int dFloorInt);
//void peopleStatus(int dPeople);




//main
int main(){


	//variable declaration

	//default floor, starting G
	char sFloorDefault[5] = "G";

	//floor the user chooses
	char sFloorChosen[5] ;

	//takes input for stopping the lift
	char sStopping[5];

	//this variable stores most recent floor where user stopped the lift
	char sFloorNewDefault[5] = "G";

	//takes user input
	char sUserInput[5];

	//int variables of the floors
	int dFloorDefaultInt=sFloorToInt(sFloorDefault);
	int dFloorChosenInt;
	int dFloorNewDefaultInt;
	int dPeople;
	int dPeopleNew;
	char sPeople[4];



	//print welcome message
	printWelcome();



	//mainwhile
	while(1){

		
		//show buttons of the elevator
		printf("\n");
		printButtons();

		//take user input to change floors using scanf
		scanf("%s", sFloorChosen);

		// printf("How many people are entering?\n");
		// scanf("%d",&dPeople);
		// if(dPeople>4){
		// 	printf("No more than 4 can fit.\n");
		// 	dPeople=4;
		// }

		//if the user enters EXIT, break the main while loop and end the program
		if (strncmp(sFloorChosen, "EXIT", 4)==0){
			printf("Leaving so soon? Bye.\n");
			break;
		}//endif

		//copy new default floor to default floor
		strcpy(sFloorDefault,sFloorNewDefault);

		//change two floor string variables to integers
		dFloorChosenInt=sFloorToInt(sFloorChosen);
		dFloorDefaultInt=sFloorToInt(sFloorDefault);
		
		

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
				printStatus(dFloorDefaultInt);
				//peopleStatus(dPeople);
				strcpy(sFloorNewDefault,intToFloor(dFloorDefaultInt));
				if ( dFloorDefaultInt != dFloorChosenInt ) {
					printf("\nStopping here?\n");
					scanf("%s",sStopping);
					if (strcmp(sStopping,"YES")==0){
						// printf("How many are leaving?\n");
						// scanf("%d", &dPeopleNew);
						// dPeople -= dPeopleNew;
						// peopleStatus(dPeople);

						// printf("Are there new people?\n");
						// scanf("%s",sPeople);
						// if (strcmp(sPeople,"YES")==0){
						// 	printf("How many?\n");
						// 	scanf("%d",&dPeopleNew);
						// 	dPeople += dPeopleNew;
						// 	if (dPeople > 4){
						// 		printf("Lift can accept up to 4.\n");
						// 		dPeople = 4;
						// 		peopleStatus(dPeople);
						// 	}
						// }
					//if(dPeople == 0){
					break;
					//}
					}//endif
				}
			}//endwhile
			
		}//endif

		//if equal no change is made, continue while
		else if(dFloorChosenInt==dFloorDefaultInt){
			printf("You're already here.\n");
		}

		//if not travel down
		else if(dFloorChosenInt<dFloorDefaultInt){
			while(dFloorChosenInt<dFloorDefaultInt){
				dFloorDefaultInt--;
				printf("\nYou're currently at floor %s",intToFloor(dFloorDefaultInt));
				strcpy(sFloorNewDefault,intToFloor(dFloorDefaultInt));
				if ( dFloorDefaultInt != dFloorChosenInt ) {
					printf("\nStopping here?\n");
					scanf("%s",sStopping);
					if (strcmp(sStopping,"YES")==0){
						// printf("How many are leaving?\n");
						// scanf("%d", &dPeopleNew);
						// dPeople -= dPeopleNew;
						// peopleStatus(dPeople);

						// printf("Are there new people?\n");
						// scanf("%s",sPeople);
						// if (strcmp(sPeople,"YES")==0){
						// 	printf("How many?\n");
						// 	scanf("%d",&dPeopleNew);
						// 	dPeople += dPeopleNew;
						// 	if (dPeople > 4){
						// 		printf("Lift can accept up to 4.\n");
						// 		dPeople = 4;
						// 		peopleStatus(dPeople);
						// 	}
						// }
						//if(dPeople == 0){
						break;
						//}
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
					printStatus(dFloorChosenInt);
					

				}
				while(dFloorDefaultInt<dFloorChosenInt){
					dFloorChosenInt--;
					printStatus(dFloorChosenInt);
					

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



//function used to change string floor input to int 
//main logic of the algorithm is based on int comparison so int is needed
int sFloorToInt(char sFloor[]){

	//declare var
	int dFloorNum;

	//atoi changes char to int, has 0 return value if cant be changed (char is not a number)
	dFloorNum = atoi(sFloor);


	//if char is not a number change G, B1, B2, B3 respectively
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
			//if user entered anything else return an error
			return 10; //used random number say 10 for reference
		}
	}
	if(dFloorNum>5 || dFloorNum<0){
		//also if user gave any numeric input out of scope of the lift error
		return 10;
	}
	else{
		//if everythings correct return dFloorNum
		return dFloorNum;
	}
		
}//endfunction



// function to change floor given in int to its string twin
// used to allow printing correct names of the floors to user 
// ex. -1 will be used by the algorithm but user gets B1 printed out
const char* intToFloor(int dFloorNum){
	printf("\n");
	static char sFloorString[5];

	//use sprintf to print directly to the string variable sFloorString

	//if our floor is numeric, print that number to the string
	if(dFloorNum > 0){
		sprintf(sFloorString,"%d",dFloorNum);

	}

	//if not, print the string name (respecting the number analogy)
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

	//return the string
	return sFloorString;

}//endfunction


//function to print welcome message
void printWelcome(){
	printf("\nHi there! Where am I taking you?\n");
	printf("If you want to stop the lift anywhere, type in YES.\n");
	printf("If you want to exit the lift, type in EXIT.\n");
	printf("You are now on floor G.\n");
}//endfunction


//function to print buttons of the elevator
void printButtons(){

	//print the buttons
	printf("Select a floor to ride the elevator.\n\n");
	printf(" \n");
	printf(" [ 3 ] [ 4 ] [ 5 ]\n");
	printf(" [ G ] [ 1 ] [ 2 ]\n");
	printf("[ B3 ] [ B2 ] [ B1 ]\n");

}//endfunction

//function to print the status of the lift
//used to simplify main
void printStatus(int dFloorInt){

	//print the status using intToFloor function to convert int to string floor 
	printf("Lift at floor %s.\n", intToFloor(dFloorInt));
}//endfunction

// void peopleStatus(int dPeople){
// 	printf("There are %d people in the lift.\n", dPeople);
// }




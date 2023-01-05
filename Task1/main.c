//elevator controller program in C
// MARIJA CETKOVIC 89221046 CP22/23
/* program simulates the behaviour of the elevator
 user inputs desired floor and elevator travels to that floor
 user can exit by typing EXIT
 user can stop on any floor on the way to the desired one by typing YES
 if user leaves before reaching desired floor, and wants to ride again he types in CALL
 and elevator gets called from the desired floor

 elevator can also accept different number of passengers (up to 4) by typing in YES
 if the number of passengers is bigger than 4 at any point, lift will as many as can fit (4 present)
 if more passengers want to exit than present in the lift, by default everyone will exit (0 present)
 passengers can enter or exit at any floor 
 if every passenger exits before reaching floor they chose and new passengers come in after them, lift by default firstly goes to previously chosen floor and then asks the new passengers where they want to go
 of course they can also stop anywhere on the way
 
any user input other than YES or CALL in respective situations is considered as NO (imitating user not taking any action)
*/




#include <stdio.h> //printf,scanf
#include <string.h> //to use strcmp, strncmp, strcpy (all learned from source code in CP class git repo)
#include <stdlib.h> //to use atoi



//function declaration on beginning of the program
//so the compiler knows that im going to use them
//functions are defined below main
int sFloorToInt(char sFloor[]);
const char* intToFloor(int dFloorNum);
void printWelcome();
void printButtons();
void printStatus(int dFloorInt);
void peopleStatus(int dPeople);




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

	//variables for additional passengers
	int dPeople; //present currently 
	int dPeopleNew; //passengers added or removed
	char sPeople[4]; //user input for decision of adding/removing passengers



	//print welcome message
	printWelcome();



	//mainwhile
	while(1){

		
		//show buttons of the elevator
		printf("\n");
		printButtons();

		//take user input to change floors using scanf
		scanf("%s", sFloorChosen);

		printf("How many people are entering?\n");
		scanf("%d",&dPeople);
		if(dPeople>4){
			printf("No more than 4 can fit. Others have to wait.\n");
			dPeople=4;
		}

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


		//if the chosen floor is higher travel up i.e. if chosen int is bigger than default int
		if (dFloorChosenInt>dFloorDefaultInt){

			//while it is bigger
			while(dFloorChosenInt>dFloorDefaultInt){

				//increase number (travelling up one by one floor)
				dFloorDefaultInt++;
				printStatus(dFloorDefaultInt); //printstatus
				
				//every time floor changes copy that default floor to new default floor variable for the case of exiting before reaching chosen floor
				strcpy(sFloorNewDefault,intToFloor(dFloorDefaultInt));

				//ask for stopping except on the goal destination (chosen floor) because there the elevator will stop anyway
				if ( dFloorDefaultInt != dFloorChosenInt ) {

					//inform user that they can stop and ask if they want to stop
					printf("\nStopping here? Type in YES.\n");
					scanf("%s",sStopping);

					//if they chose YES
					if (strcmp(sStopping,"YES")==0){
						//ask how many people are leaving
						printf("How many are leaving?\n");
						scanf("%d", &dPeopleNew);

						//if its a positive number and smaller or equal to number of people alr present (handle errors)
						if(dPeopleNew>=0 && dPeople-dPeopleNew>=0){
						dPeople -= dPeopleNew; //decrease dPeople by dPeopleNew and put it into dPeople variable
						peopleStatus(dPeople); //print status of people present
						}
						else if(dPeople-dPeopleNew<0){
							dPeople = 0; //if dPeople is smaller than dPeopleNew then by default everyone exits and 0 are present
							printf("Everyone exited.\n");
							peopleStatus(dPeople);
						}
						else{
							printf("Invalid input.\n"); //else for invalid input
							//no changes made to dPeople
							peopleStatus(dPeople);
						}

						//repeat the process if there are new people
						printf("Are there new people?\n");
						scanf("%s",sPeople);
						if (strcmp(sPeople,"YES")==0){
							printf("How many?\n");
							scanf("%d",&dPeopleNew);
							if(dPeopleNew>=0 && dPeopleNew+dPeople<=4){ //handle errors such as entering a negative number or too many people
							dPeople += dPeopleNew; //add new people into dPeople
							peopleStatus(dPeople);
							}

							else if (dPeopleNew+dPeople>4){ //if number of poeple is exceeded by default 4 
								printf("Lift can accept up to 4. Others can wait.\n");
								dPeople = 4;
								peopleStatus(dPeople);
							}
							else{ //else for handling other errors
								//no changes made to dPeople
								printf("Invalid input.");
								peopleStatus(dPeople);
							}
						}
					
					//if dPeople is 0 elevator is empty and waits at the floor it is left off (bcs of line 133)
					if (dPeople == 0)
					{
						break; //breaks while and goes to line 274
					}
					}//endif
				}//endif
			}//endwhile
			
		}//endif

		//if chosen and default are equal no change is made, continue while
		else if(dFloorChosenInt==dFloorDefaultInt){
			printf("You're already here.\n");
			continue;
		}

		//if not travel down
		//travelling down is same as travelling up except for a few factors
		//im aware now that i could have made a function moveLift that will take (sFloorChosen,sFloorDefault,dDirection) as parameters 
		//and return some status code that could have been used as reference for an if statement
		//where dDirection would be +1 or -1 used for incr or decr of the sFloorDefault until Chosen is reached
		//that would have improved my code stucture and avoided repetitiveness
		//but due to lack of experience i had problems implementing a function that would help my structure bcs i kept messing up whiles and breaks so i kept it like this in main
		else if(dFloorChosenInt<dFloorDefaultInt){
			//while chosen is less than default
			while(dFloorChosenInt<dFloorDefaultInt){
				//decrease default
				dFloorDefaultInt--;

				//following code is the same as for travelling up
				printf("\nYou're currently at floor %s",intToFloor(dFloorDefaultInt));
				strcpy(sFloorNewDefault,intToFloor(dFloorDefaultInt));
				if ( dFloorDefaultInt != dFloorChosenInt ) {
					printf("\nStopping here? Type in YES.\n");
					scanf("%s",sStopping);
					if (strcmp(sStopping,"YES")==0){
					printf("How many are leaving?\n");
						scanf("%d", &dPeopleNew);
						if(dPeopleNew>=0 && dPeople-dPeopleNew>=0){
						dPeople -= dPeopleNew;
						peopleStatus(dPeople);
						}
						else if(dPeople-dPeopleNew<0){
							dPeople = 0;
							printf("Everyone exited.\n");
							peopleStatus(dPeople);
						}
						else{
							printf("Invalid input.\n");
							peopleStatus(dPeople);
						}

						printf("Are there new people?\n");
						scanf("%s",sPeople);
						if (strcmp(sPeople,"YES")==0){
							printf("How many?\n");
							scanf("%d",&dPeopleNew);
							if(dPeopleNew>=0 && dPeopleNew+dPeople<=4){
							dPeople += dPeopleNew;
							peopleStatus(dPeople);
							}

							else if (dPeopleNew+dPeople>4){
								printf("Lift can accept up to 4. Others can wait.\n");
								dPeople = 4;
								peopleStatus(dPeople);
							}
							else{
								printf("Invalid input.");
								peopleStatus(dPeople);
							}
						}
					
					if (dPeople == 0)
					{
						break;
					}
					}//endif
				}
			}//endwhile
		}//endelse



		//if user exited before reaching Chosen, he will have to CALL Chosen from NewDefault if he wants to ride again
		//in case of multiple passengers this happens when dPeople is 0
		if(strcmp(sFloorNewDefault,sFloorChosen)!=0){

			//let user know that lift travels to what he chose at the beginning regardless of where he left off in the meanwhile
			printf("\n\nGoing to floor %s.\n",sFloorChosen);
			printf("If you want to ride again, call the elevator with CALL. \nIf not type anything else.\n");

			//take input
			scanf("%s",sUserInput);


			//if userinput is CALL
			if(strcmp(sUserInput,"CALL")==0){

				//let user know where lift is coming from
				printf("\n\nComing from floor %s.\n",sFloorChosen);

				//if user is higher floors increment
				while(dFloorDefaultInt>dFloorChosenInt){
					dFloorChosenInt++;
					printStatus(dFloorChosenInt);
					
				//if user is lower floors decrement
				}
				while(dFloorDefaultInt<dFloorChosenInt){
					dFloorChosenInt--;
					printStatus(dFloorChosenInt);
					
				}
			}//endif
			else{
				//if user input is anything else exit main
				printf("Leaving so soon? Bye!\n");
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
	dFloorNum = atoi(sFloor); //source: https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm


	//if char is not a number change G, B1, B2, B3 respectively
	if (dFloorNum==0){
		//source for using strncmp: https://www.tutorialspoint.com/c_standard_library/c_function_strncmp.htm
		//use strncmp because G has 1 char B1,B2,B3 have 2 , not to cause error with input (as string input defined on top admits 4 chars at most)
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
		//also if user gave any numeric input out of scope of the possible floors, error
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
const char* intToFloor(int dFloorNum){ //to be able to return a string const char* must be used (pointer to the 1st char of the string-(char array))
	//source: https://flaviocopes.com/c-return-string/
	printf("\n");
	static char sFloorString[5]; //static char array so it does not get lost or deleted, its memory space is static

	//use sprintf to print directly to the string variable sFloorString
	//source: https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm

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
	printf("If you want to exit the lift, type in EXIT. You will end the program.\n");
	printf("When you stop the lift, you can add or remove passengers (up to 4).\n");
	printf("If you exit before reaching your chosen floor,\nand want to ride again, call the lift by typing in CALL.\n");
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
	printf("Lift currently at floor %s.\n", intToFloor(dFloorInt));
}//endfunction

//function to print the status of people present
void peopleStatus(int dPeople){
	if(dPeople == 0){ //if 0 then no one
		printf("There is no one in the lift.\n");
	}
	else if(dPeople == 1){ //if 1 then one person
		printf("There is one person in the lift.\n");
	}
	else{//if >1 that many people
	printf("There are %d people in the lift.\n", dPeople);
	}
}




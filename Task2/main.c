#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//declare functions on top
//functions defined below main
void printWelcome();
int randomNumber(int x);
const char* selectDifficulty(int x);
void drawHangman(int dNumLives);
void generateMessage();
void printChocolate();


//main
int main(){

	//declare variables
	char sGuesses[20]; 
	char cLetterGuessed; //holds letter guessed
	char sWord[30]; //holds the word that user has to guess, length big enough because its not fixed length
	int dNumCorrect = 0; //counts correct guesses
	int dCounter = 0 ; //counter which checks if change was made after user guesses
	int dNumLives = 7; //decreases number of lives as the user guesses wrong
	int dNumDiff=0;  //number of difficulty
	
	//print welcome message
	printWelcome();
	
	//ask user to choose a difficulty
	printf("Please select a difficulty. Type 1 for EASY and 2 for HARD.\n");
	scanf("%d", &dNumDiff);

	//if its none of the given two, error
	if (dNumDiff!=1 && dNumDiff!=2)
	{
		//print error message and return main
		//user must rerun the program
		printf("Please select 1 or 2.\n");
		return 0;
	}

	//print what user selected
	printf("\nYou have selected difficulty %d.\n",dNumDiff);

	//another variable declaring because difficulty had to be chosen first

	
	strcpy(sWord, selectDifficulty(dNumDiff)); //put the word from selected difficulty array to sWord used for the game
	int dLength = strlen(sWord); //store length of sWord (was unknown until now)
	char sWordNew[30]; //string that will get displayed to the user with underscores instead of letters that will change to letters of sWord when correctly guessed
	strcpy(sWordNew, sWord); //copy sWord to sWordNew

	//int array that stores 0 that will get changed to 1 when letter correctly guessed
	int dVisited[strlen(sWord)]; //has length of sWord

	//use memset function to set every array element to desired element
	memset(sWordNew, '_', strlen(selectDifficulty(dNumDiff))*sizeof(char)); //set every char of sWordNew array to underscore
	memset(dVisited, 0, strlen(selectDifficulty(dNumDiff))*sizeof(int)); //set every int of dVisited array to 0


	//message to user to enter a guess
	printf("Please enter a letter\n");
	

	//while loop until 
	while(dNumCorrect < dLength){

		//accept user input
		scanf("%s", sGuesses);

		if (strncmp(sGuesses, "quit", 4) == 0)
		{
			printf("\n");
			printf("Sorry to see you leave early. :(\n");
			printf("Till next time! Bye!\n");
			break;
		}


		cLetterGuessed=sGuesses[0];
		if (!isalpha(cLetterGuessed)){
			printf("\nThat's not a letter. \nEnter a letter please.\n");
			continue;
		}
		dCounter = dNumCorrect;

		printf("\nYou entered the letter: %c\n", cLetterGuessed);

		//loop through all letters of sWord with a for loop
		for (int i = 0; i < strlen(sWord); ++i){
			

			//if dVisited at i is 1 means its correctly guessed so that letter gets skipped (continue)
			if (dVisited[i]==1){
			continue;
		    }

		    //if our word at i (some letter) is equal to the letter user guessed
			if (sWord[i]==cLetterGuessed){

				//set sWordNew that gets displayed to the user at i (letter position) to that correctly guessed letter
				sWordNew[i]=cLetterGuessed;
				//set dVisited at i (letter position) to 1 (visited/correctly guessed)
				dVisited[i]=1;
				//increase counter of correct guesses
				dNumCorrect++;
			
			//winning condition
			//if number of correct guesses is the same as length of the word user wins
			if (dNumCorrect == dLength){	
				//print winning message and exit main
				printChocolate();
				return 1;
			}//endif

			//if number of correct guesses increased by one, a correct guess was made
			if(dNumCorrect == dCounter+1){
				//let user know he guessed correctly
				printf("\nCorrect! Woohoo!\n");
				//generate random correct guessed message
				generateMessage();
				printf("\nGuess again.\n");
				printf("\n");
			}//endif

		
			}//endif

		}//endfor

		//if no change was made then no correct guesses 
		if (dNumCorrect == dCounter ){

			//decrease num of lives
			dNumLives--;
			//let user know he was wrong and how many lives he has left
			printf("\nWRONG! You have %d lives left.\n", dNumLives);
			//hangman gets drawn
			drawHangman(dNumLives);
		}

		//if lives are 0 user lost
		if (dNumLives == 0)
			{
				//let him know he lost and break while
				printf("\nAww man! You lost. :(\n");
				printf("The word was %s.\n", sWord);
				printf("Play again for better luck.\n");
				break;
			}

	//print current state of sWordNew
	printf("%s\n", sWordNew);


	}//endwhile

	return 1;
}//endmain


//welcome message function
void printWelcome(){
	printf("Hi there!\n");
	printf("Welcome to The Hangman Game!\n");
	printf("\n");
	printf("Play by entering letters in the console.\n");
	printf("If you want to quit at any point, just type in 'quit'.\n");
	printf("Do not enter the correctly guessed letter twice! You'll lose a point.\n");
	printf("Let's play. :)\n");
	printf("\n");
}


//random number function
int randomNumber(int x){
	srand(time(NULL));//so we get new randomized number each time

	//get a random number in range x+1, x is number of words in our list
	//random number and modulus x + 1 (modulus gives back every number between 0 and n - 1)
	int n = rand()%(x+1);
	return n;
}


//select difficulty function
const char* selectDifficulty(int x){

	static char sWord[25];


	if (x == 1) {

		static char words[][8]	=	{"milk","coffee","curtain","cook",
									"phone","flower","cloud","table",
									"glasses","light","action","laptop",
									"koala","pasta","cactus","socks",
									"plane","sunny"};
		strcpy(sWord, words[randomNumber(18)]);


	}
	else if (x == 2){

		static char words[][15] =	{"continue", "awkwardly", "allocation",
									"newspaper", "university", "troubleshoot",
									"amusement"};
		strcpy (sWord, words[randomNumber(7)]);

	}

	return sWord;

}

//function to print hangman
void drawHangman(int dNumLives){
	//switch case statement
	//as the number of lives gets lower, the picture of the hangman progresses
	switch (dNumLives){
	case 6:
		printf("\n");
		printf("I guess we start hanging.\n");
		printf("  +---+\n"
  			   "  |   |\n"
 			   "      |\n"
    		   "      |\n"
   			   "      |\n"
     	       "      |\n"
	           "  =========\n");
		break;
	case 5:
		printf("\n");
		printf("Got his head!\n");
		printf("  +---+\n"
  			   "  |   |\n"
 			   "  O   |\n"
    		   "      |\n"
   			   "      |\n"
     	       "      |\n"
	           "  =========\n");

		break;
	case 4:
		printf("\n");
		printf("I can see a body right there!\n");
		printf("  +---+\n"
  			   "  |   |\n"
 			   "  O   |\n"
    		   "  |   |\n"
   			   "      |\n"
     	       "      |\n"
	           "  =========\n");
		break;
	case 3:
		printf("\n");
		printf("Careful...\n");
		printf("  +---+\n"
  			   "  |   |\n"
 			   "  O   |\n"
    		   " /|   |\n"
   			   "      |\n"
     	       "      |\n"
	           "  =========\n");
		break;
	case 2:
		printf("\n");
		printf("Two arms already!!\n");
		printf("  +---+\n"
  			   "  |   |\n"
 			   "  O   |\n"
    		   " /|\\  |\n"
   			   "      |\n"
     	       "      |\n"
	           "  =========\n");
		break;
	case 1:
		printf("\n");
		printf("One leg away...\n");
		printf("  +---+\n"
  			   "  |   |\n"
 			   "  O   |\n"
    		   " /|\\  |\n"
   			   " /    |\n"
     	       "      |\n"
	           "  =========\n");
		break;
	case 0:
		printf("\n");
		printf("You hanged the guy!\n");
		printf("  +---+\n"
  			   "  |   |\n"
 			   "  O   |\n"
    		   " /|\\  |\n"
   			   " / \\  |\n"
     	       "      |\n"
	           "  =========\n");
		break;
	default: 
		break;

	}//endswitch
	
}//endfunction

void generateMessage(){

	static char sMessages[][50]={"Keep up the good work!",
						  "Bravo! Let's see if you can do more.",
						  "Amazing! Keep going!",
						  "You're good at this!",
						  "No hanging for you!",
						  "Pure talent.",
						  "How do you do this?",
						  "Are you cheating?",
						  "Is that all you got?",
						  "I'm rooting for you!",
						  "Let's goooooo!",
						  "You came to win!",
						  "Good. Again. If you can."

	};

	printf("%s\n",sMessages[randomNumber(13)]);
}

void printChocolate(){

	printf("\nYAAAY! You guessed the word!\n");
			printf("\nYou WIN!!!\n");
			printf("\n    Here's a chocolate! :)\n");

	printf(
 "    _____________,-.___     _\n"
 "   |____        { {]_]_]   [_]\n"
 "   |___ `-----.__\\ \\_]_]_    . `\n"
 "   |   `-----.____} }]_]_]_   ,\n"
 "   |_____________/ {_]_]_]_] , `\n"
 "                  `-'           \n"




		);
}

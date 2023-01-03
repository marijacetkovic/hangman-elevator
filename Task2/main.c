#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int randomNumber(int x);
const char* selectDifficulty(int x);
void drawHangman(int dNumLives);
void generateMessage();
void printChocolate();


int main(){

	printf("Hi there!\n");
	printf("Welcome to The Hangman Game!\n");
	printf("\n");
	printf("Play by entering letters in the console.\n");
	printf("If you want to quit at any point, just type in 'quit'.\n");
	printf("Do not enter the correctly guessed letter twice! You'll lose a point.\n");
	printf("Let's play. :)\n");
	printf("\n");

	//char words[][7]={"milk","coffee","curtain","cook","phone","flower","cloud","table","glasses","light","action","laptop","koala","pasta"};

	//printf("%s\n", words[randomNumber(14)]);
	// words[randomNumber(14)];
	char sGuesses[20];
	char cLetterGuessed;
	char sWord[30];
	int dNumCorrect = 0;
	int dCounter = 0 ;
	int dNumLives = 7;
	int dNumDiff=0;

	printf("Please select a difficulty. 1 or 2?\n");
	scanf("%d", &dNumDiff);
	if (dNumDiff!=1 && dNumDiff!=2)
	{
		printf("Please select 1 or 2.\n");
		return 0;
	}

	printf("\nYou have selected difficulty %d.\n",dNumDiff);
	strcpy(sWord, selectDifficulty(dNumDiff));
	//printf("%s\n", selectDifficulty(dNumDiff));
	int dLength = strlen(sWord);
	char sWordNew[30];
	strcpy(sWordNew, selectDifficulty(dNumDiff));
	int dVisited[strlen(sWord)];
	memset(sWordNew, '_', strlen(selectDifficulty(dNumDiff))*sizeof(char));
	memset(dVisited, 0, strlen(selectDifficulty(dNumDiff))*sizeof(int));
	

	//for (int i = 0; i < strlen(sWord); ++i)
	//{
	//	sWordNew[i] = '0';
	//}
	//printf("%s\n", sWordNew);

	printf("Please enter a letter\n");
	

	while(dNumCorrect < dLength){

		scanf("%s", sGuesses);
		//fgets(sGuesses, 20, stdin);

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

		for (int i = 0; i < strlen(sWord); ++i){
			

			//letters that are visited/alr guesses will be skipped
			if (dVisited[i]==1){
			continue;
		    }

			if (sWord[i]==cLetterGuessed){

			sWordNew[i]=cLetterGuessed;
			dVisited[i]=1;
			dNumCorrect++;
			
			//winning condition
			if (dNumCorrect == dLength){	
			printf("\nYAAAY! You guessed the word!\n");
			printf("\nYou WIN!!!\n");
			printf("\n    Here's a chocolate! :)\n");
			printChocolate();
			return 1;
			}//endif

			if(dNumCorrect == dCounter+1){
			printf("\nCorrect! Woohoo!\n");
			generateMessage();
			printf("\nGuess again.\n");
			printf("\n");
			}//endif

		
			}//endif

		}//endfor
		if (dNumCorrect == dCounter )
		{
			dNumLives--;
			printf("\nWRONG! You have %d lives left.\n", dNumLives);
			//hangman drawn HERE
			drawHangman(dNumLives);
		}
		if (dNumLives == 0)
			{
				printf("\nAww man! You lost. :(\n");
				printf("The word was %s.\n", sWord);
				printf("Play again for better luck.\n");
				break;
			}
	//printf("%d\n", dNumCorrect);
	printf("%s\n", sWordNew);
	//printf("%s\n", dGuesses);


	}//endwhile

	return 1;
}//endmain


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
									"koala","pasta"};
		strcpy(sWord, words[randomNumber(14)]);


	}
	else if (x == 2){

		static char words[][15] =	{"continue", "awkwardly", "allocation",
									"newspaper", "university", "troubleshoot",
									"amusement"};
		strcpy (sWord, words[randomNumber(7)]);

	}

	return sWord;

}


void drawHangman(int dNumLives){
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

	printf(
 "    _____________,-.___     _\n"
 "   |____        { {]_]_]   [_]\n"
 "   |___ `-----.__\\ \\_]_]_    . `\n"
 "   |   `-----.____} }]_]_]_   ,\n"
 "   |_____________/ {_]_]_]_] , `\n"
 "                  `-'           \n"




		);
}

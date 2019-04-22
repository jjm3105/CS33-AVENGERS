#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char input[256];

// Configuration

void getInput() {
	fgets (input, sizeof(input), stdin);
	for (int i = 0; i < 256 && input[i] != '\0'; i++)
		if (input[i] == '\n') {
			input[i] = '\0';
			break;
		}

	// printf("Input was: %s\n", input);
}

void THANOS() {
	printf("SNAP! Half of all life was killed :(\n");
}

void Head() {
	printf("Success! Everybody's back!\n");
}



// PHASES

int IronMan(int scraps) {
	int suit = scraps << 4;

	return suit;
}

int CapAmerica(char* speech) {
	if (!strcmp(speech, "Avengers Assemble!!"))
		return 1;

	return 0;
}

int Thor(char* hammer) {
	int lightning = atoi(hammer);

	int energy = IronMan(lightning);

	if (energy >= 400 && energy <= 500)
		return 1;

	return 0;
}



// MAIN

int main() {

	printf("Please put in the first phrase: ");
	getInput();
	int SHIELD = CapAmerica(input);
	if (!SHIELD) {
		THANOS();
		return 0;
	}

	printf("Please put in the second phrase: ");
	getInput();
	SHIELD = Thor(input);
	if (!SHIELD) {
		THANOS();
		return 0;
	}

	Head();
}

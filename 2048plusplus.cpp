#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

// Keyboard definitions
#define up 0x4800
#define down 0x5000
#define left 0x4d00
#define right 0x4b00

#define SIZE 10

// Boolean definitions
#define bool int
#define true 1
#define false 0

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UNKNOWN,
} Directions;

// Grid
int map[4][4];
int score = 0;

// Insert new value amongst empty cells
void create();

// Generate the new value; either 2 or 4
int generateTwoOrFour(int x);

// Check if game over
bool canMoveTo(Directions direction);

// Shift lines of the grid
void shift(Directions direction);

// Move grid lines to the desired direction
void moveTo(Directions direction);

// Retrieve user input
Directions getDirection();

// Print the grid map
void printGrid();

int main()
{
	// Initialize grid
	char *get = (char*)malloc(SIZE);
	memset(map, 0, sizeof(map));
	srand(time(NULL));
	create();
	create();
	printGrid();

	while (1) {

		// Check if game over
			// If cannot move to any direction
		if (!canMoveTo(UP) && !canMoveTo(DOWN) && !canMoveTo(LEFT) && !canMoveTo(RIGHT))
			break;

		// Retrieve direction input
		Directions directionInput = getDirection();

		// Check validity of the direction
		if (directionInput == UNKNOWN)
			continue;
		if (!canMoveTo(directionInput))
			continue;

		// Refresh grid
		system("cls");
		shift(directionInput);
		create();
		printGrid();
	}

	printf("!!! You died !!!\n");
	printf("FINAL SCORE: %d\n", score);

	while (1);
	return 0;
}

void create() {
	// Generate a random number
	int randomNumber = rand();

	// Generate a new value; either 2 or 4
	// We try to achieve the probability of getting a 4 to 10%
	int newValue = generateTwoOrFour((randomNumber % 10) + 1);

	// emptyCount will contain the total number of empty cells
	// This value will be used to randomize where the new value will be placed
	int emptyCount = 0;

	// Reorder empty cells
	int maps[4][4];
	memset(maps, 0, sizeof(maps));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j] == 0) {
				emptyCount++;
				maps[i][j] = emptyCount;
			}
		}
	}

	// Assign random cell with the generated newValue
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (maps[i][j] == ((randomNumber % emptyCount) + 1)){
				map[i][j] = newValue;
			}
		}
	}
}

int generateTwoOrFour(int randomNumber) {
	if (randomNumber == 10) {
		return 4;
	}
	else {
		return 2;
	}
}
bool canMoveTo(Directions direction) {
	// To check validity of the direction, at leastr one cell in the line must meet the following criteria:
		// If current cell is NOT empty AND
			// If desired adjacent cell have matching values OR
			// If the desired adjacent cell have matching va

	switch (direction) {
		case UP:
			for (int i = 1; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if ((map[i][j] != 0) && (map[i - 1][j] == map[i][j] || map[i - 1][j] == 0))
						return true;
				}
			}
			break;
		case DOWN:
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++) {
					if ((map[i][j] != 0) && (map[i + 1][j] == map[i][j] || map[i + 1][j] == 0))
						return true;
				}
			}
			break;
		case LEFT:
			for (int i = 0; i < 4; i++) {
				for (int j = 1; j < 4; j++) {
					if ((map[i][j] != 0) && (map[i][j] == map[i][j - 1] || map[i][j - 1] == 0))
						return true;
				}
			}
			break;
		case RIGHT:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					if ((map[i][j] != 0) && (map[i][j] == map[i][j + 1] || map[i][j + 1] == 0))
						return true;
				}
			}
			break;
		case UNKNOWN:
			printf("Error on the button pressed.");
			break;
	}

	return false;
}
void shift(Directions direction) {

	// Shift lines of the grid.
	moveTo(direction);

	// Scan cells of the shifted lines and check if desired adjacent cells have equal value;
		// If so, add the values together and update the scores.
	switch (direction) {
		case UP:
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++) {
					if (map[i][j] != 0 && map[i][j] == map[i + 1][j]) {
						map[i][j] = map[i][j] * 2;
						score += map[i][j];
						map[i + 1][j] = 0;
					}
				}
			}
			moveTo(direction);
			break;
		case DOWN:
			for (int i = 3; i > 0; i--) {
				for (int j = 0; j < 4; j++) {
					if (map[i][j] != 0 && map[i][j] == map[i - 1][j]) {
						map[i][j] = map[i][j] * 2;
						score += map[i][j];
						map[i - 1][j] = 0;
					}
				}
			}
			moveTo(direction);
			break;
		case LEFT:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					if (map[i][j] != 0 && map[i][j] == map[i][j + 1]) {
						map[i][j] = map[i][j] * 2;
						score += map[i][j];
						map[i][j + 1] = 0;
					}
				}
			}
			moveTo(direction);
			break;
		case RIGHT:
			for (int i = 0; i < 4; i++) {
				for (int j = 3; j > 0; j--) {
					if (map[i][j] != 0 && map[i][j] == map[i][j - 1]) {
						map[i][j] = map[i][j] * 2;
						score += map[i][j];
						map[i][j - 1] = 0;
					}
				}
			}
			moveTo(direction);
			break;
		case UNKNOWN:
			printf("Error on the button pressed.");
			break;
	}
}
void moveTo(Directions direction) {

	//  Move cells if the desired adjacent cell is empty.
	switch (direction) {
		case UP:
			for (int i = 1; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = i; k > 0; k--) {
						if (map[k - 1][j] == 0) {
							map[k - 1][j] = map[k][j];
							map[k][j] = 0;
						}
					}
				}
			}
			break;
		case DOWN:
			for (int i = 2; i >= 0; i--) {
				for (int j = 0; j < 4; j++) {
					for (int k = i; k < 3; k++) {
						if (map[k + 1][j] == 0) {
							map[k + 1][j] = map[k][j];
							map[k][j] = 0;
						}
					}
				}
			}
			break;
		case LEFT:
			for (int i = 0; i < 4; i++) {
				for (int j = 1; j < 4; j++) {
					for (int k = j; k > 0; k--) {
						if (map[i][k - 1] == 0) {
							map[i][k - 1] = map[i][k];
							map[i][k] = 0;
						}
					}
				}
			}
			break;
		case RIGHT:
			for (int i = 0; i < 4; i++) {
				for (int j = 2; j >= 0; j--) {
					for (int k = j; k < 3; k++) {
						if (map[i][k + 1] == 0) {
							map[i][k + 1] = map[i][k];
							map[i][k] = 0;
						}
					}
				}
			}
			break;
		case UNKNOWN:
			printf("Error on the button pressed.");
			break;
	}
}

Directions getDirection() {
	int userInput;
	while ((userInput = getch()) != 0x1B) {
		switch (userInput) {
		case 0xE0:
			switch (userInput = getch()) {
			case 72: return UP; break;
			case 80: return DOWN; break;
			case 75: return LEFT; break;
			case 77: return RIGHT; break;
			default:
				return UNKNOWN;
				break;
			}
			break;
		default:
			break;
		}
	}
	return UNKNOWN;
}

void printGrid() {
	printf("._______._______._______._______.\n");

	for (int i = 0; i < 4; i++) {
		printf("|");
		for (int j = 0; j < 4; j++) {
			if (map[i][j] != 0) {
				printf(" %d", map[i][j]);
			}
			else {
				printf(" ");
			}
			printf("\t|");
		}
		printf("\n");
		printf("._______._______._______._______.\n");
	}
	printf("\nScore: %d\n", score);
}
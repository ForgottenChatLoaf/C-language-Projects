#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_USERS 100
#define USERS_FILE "users.dat"

typedef struct {
	char username[MAX_USERNAME];
	char password[MAX_PASSWORD];
	double balance;
} User;

User users[MAX_USERS];
int userCount = 0;
int currentUserIndex = -1;

void wala();
void calcu();
void atmsim();
void quiz();
void numgues();
void battle();
void businessMenu();
void pythagorasMenu();
void rockPaperScissors();
void digitalClock();
void loadUsers();
void saveUsers();
void registerUser();
int loginUser();
void displayHeader();
void clearBuffer();

int main() {
	int mainchoice;
	loadUsers();

	do {
		system("cls");
		printf("Loading Main Menu");
		Sleep(500);
		printf(".");
		Sleep(400);
		printf(".");
		Sleep(300);
		printf(".\n");
		Sleep(200);
		printf("Please Wait...");
		Sleep(400);
		system("cls");
		printf("||==============================================================================================||\n");
		printf("||                                                                                              ||\n");
   		printf("||    ##     ##    ###    #######  ##    ##        ##     ##  ########  ##    ##  ##     ##     ||\n");
    	printf("||    ###   ###   ## ##     ###    ###   ##        ###   ###  ##        ###   ##  ##     ##     ||\n");
    	printf("||    #### ####  ##   ##    ###    ####  ##        #### ####  ##        ####  ##  ##     ##     ||\n");
    	printf("||    ## ### ##  ##   ##    ###    ## ## ##        ## ### ##  ######    ## ## ##  ##     ##     ||\n");
    	printf("||    ##     ##  #######    ###    ##  ####        ##     ##  ##        ##  ####  ##     ##     ||\n");
    	printf("||    ##     ##  ##   ##    ###    ##   ###        ##     ##  ##        ##   ###  ##     ##     ||\n");
    	printf("||    ##     ##  ##   ##  #######  ##    ##        ##     ##  ########  ##    ##   #######      ||\n");
    	printf("||                                                                                              ||\n");
		printf("||==============================================================================================||\n");
    	printf("||                                                                                              ||\n");
    	printf("||   [1] Sign In / Log In          [5] Number Guessing Game  [9] Rock, Paper, Scissors          ||\n");
    	printf("||   [2] ATM Simulation            [6] Battle Simulation     [10] Digital Clock                 ||\n");
    	printf("||   [3] Simple Quiz Application   [7] Business Menu         [11] TBA                           ||\n");
    	printf("||   [4] Calculator                [8] Pythagorean Theorem   [12] TBA                           ||\n");
    	printf("||                                                                                              ||\n");
    	printf("||                                 [0] Exit                                                     ||\n");
    	printf("||==============================================================================================||\n");
		printf("Enter your choice: ");
		scanf("%i", &mainchoice);
		clearBuffer();

		system("cls");
		
		switch (mainchoice) {
			case 1:
				wala();
				break;
			case 2:
				if (currentUserIndex != -1) {
					atmsim();
				} else {
					printf("Please log in first!\n");
					Sleep(1500);
				}
				break;
			case 3:
				quiz();
				break;
			case 4:
				calcu();
				break;
			case 5:
				numgues();
				break;
			case 6:
				battle();
				break;
			case 7:
				businessMenu();
				break;
			case 8:
				pythagorasMenu();
				break;
			case 9:
				rockPaperScissors();
				break;
			case 10:
				digitalClock();
				break;
			case 0:
				printf("\nProgram terminating...\n");
				Sleep(500);
				printf("Saving data...\n");
				Sleep(1000);
				saveUsers();
				printf("Goodbye!\n");
				break;
			default:
				printf("\nInvalid Input..");
				Sleep(1000);
		}
	}
	while (mainchoice != 0);
	
	return 0;
}

void clearBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void loadUsers() {
	FILE *file = fopen(USERS_FILE, "rb");
	if (file != NULL) {
		fread(&userCount, sizeof(int), 1, file);
		fread(users, sizeof(User), userCount, file);
		fclose(file);
	}
}

void saveUsers() {
	FILE *file = fopen(USERS_FILE, "wb");
	if (file != NULL) {
		fwrite(&userCount, sizeof(int), 1, file);
		fwrite(users, sizeof(User), userCount, file);
		fclose(file);
	}
}

void displayHeader() {
	printf("=========================================================\n");
	printf("||                                                     ||\n");
	printf("||   ##        #######    #######  ######## ##    ##   ||\n");
	printf("||   ##       ##     ##  ##     ##    ##    ###   ##   ||\n");
	printf("||   ##       ##     ##  ##           ##    ####  ##   ||\n");    
	printf("||   ##       ##     ##  ##   ####    ##    ## ## ##   ||\n");
	printf("||   ##       ##     ##  ##     ##    ##    ##  ####   ||\n");
	printf("||   ##       ##     ##  ##     ##    ##    ##   ###   ||\n");
	printf("||   #######   #######    #######  ######## ##    ##   ||\n");
	printf("||                                                     ||\n");
}

void registerUser() {
	system("cls");
	displayHeader();
	printf("||                   REGISTRATION                      ||\n");
	printf("=========================================================\n");

	if (userCount >= MAX_USERS) {
		printf("Maximum users reached!\n");
		Sleep(1500);
		return;
	}

	char username[MAX_USERNAME];
	char password[MAX_PASSWORD];
	char confirmPass[MAX_PASSWORD];

	printf("Enter desired username: ");
	fgets(username, MAX_USERNAME, stdin);
	username[strcspn(username, "\n")] = 0;

	for (int i = 0; i < userCount; i++) {
		if (strcmp(users[i].username, username) == 0) {
			printf("Username already exists!\n");
			Sleep(1500);
			return;
		}
	}

	printf("Enter password (min 6 characters): ");
	fgets(password, MAX_PASSWORD, stdin);
	password[strcspn(password, "\n")] = 0;

	if (strlen(password) < 6) {
		printf("Password too short!\n");
		Sleep(1500);
		return;
	}

	printf("Confirm password: ");
	fgets(confirmPass, MAX_PASSWORD, stdin);
	confirmPass[strcspn(confirmPass, "\n")] = 0;

	if (strcmp(password, confirmPass) != 0) {
		printf("Passwords do not match!\n");
		Sleep(1500);
		return;
	}

	strcpy(users[userCount].username, username);
	strcpy(users[userCount].password, password);
	users[userCount].balance = 0.0;
	userCount++;
	saveUsers();

	printf("Registration successful!\n");
	Sleep(1500);
}

int loginUser() {
	system("cls");
	displayHeader();
	printf("||                      L O G I N                      ||\n");
	printf("=========================================================\n");

	char username[MAX_USERNAME];
	char password[MAX_PASSWORD];
	int attempts = 0;

	while (attempts < 3) {
		printf("Username: ");
		fgets(username, MAX_USERNAME, stdin);
		username[strcspn(username, "\n")] = 0;

		printf("Password: ");
		fgets(password, MAX_PASSWORD, stdin);
		password[strcspn(password, "\n")] = 0;

		for (int i = 0; i < userCount; i++) {
			if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
				printf("\nLogin Successful!\n");
				printf("Welcome, %s!\n", username);
				currentUserIndex = i;
				Sleep(1500);
				return 1;
			}
		}

		attempts++;
		if (attempts < 3) {
			printf("Invalid credentials. Attempts remaining: %d\n", 3 - attempts);
			Sleep(1000);
			system("cls");
			displayHeader();
			printf("||                      L O G I N                      ||\n");
			printf("=========================================================\n");
		}
	}

	printf("Maximum login attempts exceeded!\n");
	Sleep(1500);
	return 0;
}

void wala() {
	system("cls");
	int authChoice;
	
	displayHeader();
	printf("||                                                     ||\n");
	printf("=========================================================\n");
	printf("[1] Login\n[2] Register\n[0] Back\n");
	printf("Choice: ");
	scanf("%d", &authChoice);
	clearBuffer();

	if (authChoice == 1) {
		loginUser();
	} else if (authChoice == 2) {
		registerUser();
	}
}

void atmsim() {
	int atmPin = 1234, inputPin;
	int choice;
	float dailyLimit = 1000.00;
	float withdrawnToday = 0.00;
	double amount;
	char again;

	system("cls");
	printf("Enter your ATM PIN: ");
	scanf("%d", &inputPin);
	clearBuffer();

	int pinAttempts = 0;
	while (inputPin != atmPin && pinAttempts < 3) {
		printf("Incorrect PIN! Attempts remaining: %d\n", 2 - pinAttempts);
		printf("Try again: ");
		scanf("%d", &inputPin);
		clearBuffer();
		pinAttempts++;
	}

	if (inputPin != atmPin) {
		printf("Account locked!\n");
		Sleep(1500);
		return;
	}

	printf("Login Successfully!\n");
	Sleep(1000);

	do {
		system("cls");
		printf("========== ATM MACHINE SIM ==========\n");
		printf("[1] Check Balance      [2] Deposit Money\n");
		printf("[3] Withdraw Money     [0] Exit\n");
		printf("---------------------------------------\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		clearBuffer();

		system("cls");

		switch (choice) {
			case 1:
				printf("========= CHECKING BALANCE =========\n");
				printf("Your current balance is $%.2lf\n", users[currentUserIndex].balance);
				break;

			case 2:
				printf("========= DEPOSITING MONEY =========\n");
				printf("Enter the amount you want to deposit: $");
				scanf("%lf", &amount);
				clearBuffer();

				if (amount > 0) {
					users[currentUserIndex].balance += amount;
					printf("Successfully deposited $%.2lf\n", amount);
					printf("Your current balance is now $%.2lf\n", users[currentUserIndex].balance);
				} else {
					printf("Invalid amount!\n");
				}
				break;

			case 3:
				printf("========== WITHDRAWING MONEY ==========\n");
				printf("Enter the amount you want to withdraw: $");
				scanf("%lf", &amount);
				clearBuffer();

				if (amount <= 0) {
					printf("Invalid Amount!\n");
				} else if (withdrawnToday + amount > dailyLimit) {
					printf("Daily Limit Reached! You can only withdraw $%.2f more today.\n", dailyLimit - withdrawnToday);
				} else if (amount > users[currentUserIndex].balance) {
					printf("Insufficient funds! You only have $%.2lf\n", users[currentUserIndex].balance);
				} else {
					users[currentUserIndex].balance -= amount;
					withdrawnToday += amount;
					printf("Successfully withdrawn $%.2lf\n", amount);
					printf("Your current balance is now $%.2lf\n", users[currentUserIndex].balance);
				}
				break;

			case 0:
				printf("Thank you for using ATM Simulation!\n");
				printf("Saving balance...\n");
				saveUsers();
				Sleep(1000);
				break;

			default:
				printf("Invalid Choice!\n");
		}

		if (choice != 0) {
			printf("Continue? [Y/N]: ");
			scanf(" %c", &again);
			clearBuffer();
		} else {
			break;
		}
	} while (again == 'y' || again == 'Y');
}

void quiz() {
	int score = 0;
	int answer;
	char confirm;

	do {
		system("cls");
		printf("==========================================\n");
		printf("|        **Simple and Easy Quiz**        |\n");
		printf("==========================================\n");

		printf("\n==========================================\n");
		printf("|   Q1: What ends a statement in C?      |\n");
		printf("|[1] .                  [3] ;            |\n");
		printf("|[2] :                  [4] ,            |\n");
		printf("==========================================\n");
		printf("Enter your answer: ");
		scanf("%d", &answer);
		clearBuffer();

		if (answer == 3) {
			printf("Correct!\n");
			score++;
		} else {
			printf("Incorrect. The answer is ';'\n");
		}
		Sleep(1000);
		system("cls");

		printf("\n=============================================\n");
		printf("|  Q2: What is a correct file extension      |\n");
		printf("|            for a C source file?            |\n");
		printf("|[1] .c                  [3] .cpp            |\n");
		printf("|[2] .java               [4] .py             |\n");
		printf("=============================================\n");
		printf("Enter your answer: ");
		scanf("%d", &answer);
		clearBuffer();

		if (answer == 1) {
			printf("Correct!\n");
			score++;
		} else {
			printf("Incorrect. The answer is '.c'\n");
		}
		Sleep(1000);
		system("cls");

		printf("\n==========================================\n");
		printf("|  Q3: Which of the following is used    |\n");
		printf("|            for loops in C?             |\n");
		printf("|[1] return           [3] for            |\n");
		printf("|[2] iterate          [4] loop           |\n");
		printf("==========================================\n");
		printf("Enter your answer: ");
		scanf("%d", &answer);
		clearBuffer();

		if (answer == 3) {
			printf("Correct!\n");
			score++;
		} else {
			printf("Incorrect. The answer is 'for'\n");
		}
		Sleep(1000);
		system("cls");

		printf("\n==========================================\n");
		printf("|  Q4: Which header file is used for     |\n");
		printf("|              printf()?                 |\n");
		printf("|[1] string.h            [3] stdlib.h    |\n");
		printf("|[2] windows.h           [4] stdio.h     |\n");
		printf("==========================================\n");
		printf("Enter your answer: ");
		scanf("%d", &answer);
		clearBuffer();

		if (answer == 4) {
			printf("Correct!\n");
			score++;
		} else {
			printf("Incorrect. The answer is 'stdio.h'\n");
		}
		Sleep(1000);
		system("cls");

		printf("\n=============================================\n");
		printf("|  Q5: What is the correct way to declare    |\n");
		printf("|      an array of 5 integers in C?          |\n");
		printf("|[1] int arr{5};        [3] int arr[5];      |\n");
		printf("|[2] array int arr[5];  [4] int arr = [5];   |\n");
		printf("=============================================\n");
		printf("Enter your answer: ");
		scanf("%d", &answer);
		clearBuffer();

		if (answer == 3) {
			printf("Correct!\n");
			score++;
		} else {
			printf("Incorrect. The answer is 'int arr[5];'\n");
		}
		Sleep(1000);
		system("cls");

		printf("\n============================================\n");
		printf("|              QUIZ COMPLETE!               |\n");
		printf("|         Your score is %d out of 5         |\n", score);
		printf("============================================\n");

		if (score == 5) {
			printf("Perfect! You're a C master!\n");
		} else if (score == 4) {
			printf("Nice work! Just one miss.\n");
		} else if (score >= 2) {
			printf("Good effort! Keep practicing.\n");
		} else {
			printf("Keep practicing! You'll improve.\n");
		}

		printf("\nRetake the quiz? [Y/N]: ");
		scanf(" %c", &confirm);
		clearBuffer();
		score = 0;
	} while (confirm == 'y' || confirm == 'Y');

	system("cls");
}

void calcu() {
	int choice;
	double num1, num2, ans;
	char confirm;

	do {
		system("cls");
		printf("||===============================================================================================||\n");
    	printf("||                                                                                               ||\n");
    	printf("||   ######    ###    ##        ######  ##     ## ##         ###  ######### ######   ########    ||\n");
    	printf("||  ##    ##  ## ##   ##       ##    ## ##     ## ##        ## ##    ##    ##    ##  ##     ##   ||\n");
    	printf("|| ##        ##   ##  ##      ##        ##     ## ##       ##   ##   ##   ##      ## ##     ##   ||\n");
    	printf("|| ##        ##   ##  ##      ##        ##     ## ##       ##   ##   ##   ##      ## ########    ||\n");
    	printf("|| ##        #######  ##      ##        ##     ## ##       #######   ##   ##      ## ##   ##     ||\n");
    	printf("||  ##    ## ##   ##  ##       ##    ## ##     ## ##       ##   ##   ##    ##    ##  ##    ##    ||\n");
    	printf("||   ######  ##   ##  ########  ######   #######  ######## ##   ##   ##     ######   ##     ##   ||\n");
    	printf("||                                                                                               ||\n");
    	printf("||===============================================================================================||\n");
		printf("||                                                                                               ||\n");
    	printf("||   [1] Addition              [3] Multiplication           [5] Exponentiation (x^y)             ||\n");
    	printf("||   [2] Subtraction           [4] Division                 [6] Square Root                      ||\n");
    	printf("||                                                                                               ||\n");
    	printf("||                             [0] Back to MAIN MENU                                             ||\n");
    	printf("||                                                                                               ||\n");
    	printf("||===============================================================================================||\n");
    	printf("Enter your Choice: ");
    	scanf("%d", &choice);
		clearBuffer();

		system("cls");

		switch (choice) {
			case 1:
				printf("========== ADDITION ==========\n");
				printf("Enter First value: ");
				scanf("%lf", &num1);
				printf("Enter Second value: ");
				scanf("%lf", &num2);
				clearBuffer();
				ans = num1 + num2;
				printf("Result: %.2lf\n", ans);
				break;

			case 2:
				printf("========== SUBTRACTION ==========\n");
				printf("Enter First value: ");
				scanf("%lf", &num1);
				printf("Enter Second value: ");
				scanf("%lf", &num2);
				clearBuffer();
				ans = num1 - num2;
				printf("Result: %.2lf\n", ans);
				break;

			case 3:
				printf("========== MULTIPLICATION ==========\n");
				printf("Enter First value: ");
				scanf("%lf", &num1);
				printf("Enter Second value: ");
				scanf("%lf", &num2);
				clearBuffer();
				ans = num1 * num2;
				printf("Result: %.2lf\n", ans);
				break;

			case 4:
				printf("========== DIVISION ==========\n");
				printf("Enter First value: ");
				scanf("%lf", &num1);
				printf("Enter Second value: ");
				scanf("%lf", &num2);
				clearBuffer();

				if (num2 != 0) {
					ans = num1 / num2;
					printf("Result: %.2lf\n", ans);
				} else {
					printf("Error: Division by zero!\n");
				}
				break;

			case 5:
				printf("========== EXPONENTIATION ==========\n");
				printf("Enter base: ");
				scanf("%lf", &num1);
				printf("Enter exponent: ");
				scanf("%lf", &num2);
				clearBuffer();
				ans = pow(num1, num2);
				printf("Result: %.2lf\n", ans);
				break;

			case 6:
				printf("========== SQUARE ROOT ==========\n");
				printf("Enter value: ");
				scanf("%lf", &num1);
				clearBuffer();

				if (num1 >= 0) {
					ans = sqrt(num1);
					printf("Result: %.2lf\n", ans);
				} else {
					printf("Error: Cannot take square root of negative number!\n");
				}
				break;

			case 0:
				break;

			default:
				printf("Invalid Input!\n");
		}

		if (choice != 0) {
			printf("Continue? [Y/N]: ");
			scanf(" %c", &confirm);
			clearBuffer();
		} else {
			break;
		}
	} while ((confirm == 'y' || confirm == 'Y') && choice != 0);
}

void numgues() {
	int num, guess, attempts = 0;
	char conf;
	const int maxAttempts = 5;

	srand(time(0));
	num = rand() % 100 + 1;

	do {
		system("cls");
		printf("============================================================\n");
		printf("||              NUMBER  GUESSING  GAME                    ||\n");
		printf("============================================================\n");
		printf("I'm thinking of a number between 1 and 100.\n");
		printf("You have 5 attempts to guess it correctly.\n");
		printf("------------------------------------------------------------\n");

		attempts = 0;
		int guessed = 0;

		while (attempts < maxAttempts && !guessed) {
			printf("\nAttempt %d/%d - Enter your Guess: ", attempts + 1, maxAttempts);
			scanf("%d", &guess);
			clearBuffer();
			attempts++;

			if (guess > num) {
				printf("Too high! Try again.\n");
			} else if (guess < num) {
				printf("Too low! Try again.\n");
			} else {
				printf("Correct! You guessed it in %d tries!\n", attempts);
				guessed = 1;
			}
		}

		if (!guessed) {
			printf("\nGame Over! The number was %d\n", num);
		}

		printf("\nPlay again? [Y/N]: ");
		scanf(" %c", &conf);
		clearBuffer();

		if (conf == 'Y' || conf == 'y') {
			srand(time(0));
			num = rand() % 100 + 1;
		}
	} while (conf == 'Y' || conf == 'y');
}

void battle() {
	int playerHP = 150, playerMP = 70;
	int enemyHP, enemyAtk;
	int choice, freeze = 0;
	char playAgain;

	srand(time(0));

	do {
		system("cls");
		printf("====================================\n");
		printf("||        MAGE BATTLE ARENA       ||\n");
		printf("====================================\n");

		char enemyName[30];
		int enemyType = rand() % 3 + 1;

		switch (enemyType) {
			case 1:
				strcpy(enemyName, "Goblin Raider");
				enemyHP = 80;
				enemyAtk = 10;
				break;
			case 2:
				strcpy(enemyName, "Dark Knight");
				enemyHP = 120;
				enemyAtk = 15;
				break;
			default:
				strcpy(enemyName, "Shadow Beast");
				enemyHP = 150;
				enemyAtk = 20;
				break;
		}

		playerHP = 150;
		playerMP = 70;
		freeze = 0;

		printf("\nA wild %s appears!\n", enemyName);
		Sleep(1500);

		while (playerHP > 0 && enemyHP > 0) {
			system("cls");
			printf("====================================\n");
			printf("%s HP: %d\n", enemyName, enemyHP);
			printf("Your HP: %d   MP: %d\n", playerHP, playerMP);
			printf("====================================\n");
			printf("[1] Fireball (10-20 dmg)\n");
			printf("[2] Frost Nova (5-10 dmg, 40%% freeze)\n");
			printf("[3] Arcane Blast (25-35 dmg, 10 MP)\n");
			printf("[4] Heal (+20 HP, 8 MP)\n");
			printf("Choice: ");
			scanf("%d", &choice);
			clearBuffer();

			int dmg = 0, chance;
			switch (choice) {
				case 1:
					dmg = 10 + rand() % 11;
					printf("You cast Fireball! It hits for %d damage.\n", dmg);
					enemyHP -= dmg;
					break;

				case 2:
					dmg = 5 + rand() % 6;
					printf("You cast Frost Nova! It deals %d damage.\n", dmg);
					enemyHP -= dmg;
					chance = rand() % 100;
					if (chance < 40) {
						freeze = 1;
						printf("The enemy is frozen and skips its next turn!\n");
					}
					break;

				case 3:
					if (playerMP >= 10) {
						dmg = 25 + rand() % 11;
						playerMP -= 10;
						printf("You unleash Arcane Blast! %d damage dealt.\n", dmg);
						enemyHP -= dmg;
					} else {
						printf("Not enough MP!\n");
					}
					break;

				case 4:
					if (playerMP >= 8) {
						playerMP -= 8;
						playerHP += 20;
						if (playerHP > 150) playerHP = 150;
						printf("You heal yourself. HP restored to %d.\n", playerHP);
					} else {
						printf("Not enough MP!\n");
					}
					break;

				default:
					printf("Invalid choice!\n");
					continue;
			}

			if (enemyHP <= 0) break;

			if (freeze) {
				printf("The enemy is frozen and cannot move!\n");
				freeze = 0;
			} else {
				int enemyDmg = enemyAtk + rand() % 6;
				playerHP -= enemyDmg;
				printf("%s attacks and deals %d damage!\n", enemyName, enemyDmg);
			}

			if (playerHP < 0) playerHP = 0;
			if (enemyHP < 0) enemyHP = 0;

			printf("Press Enter to continue...");
			getchar();
			system("cls");
		}

		if (playerHP <= 0) {
			printf("You have been defeated by the %s...\n", enemyName);
		} else {
			printf("You defeated the %s! Victory!\n", enemyName);
		}

		printf("\nPlay again? [Y/N]: ");
		scanf(" %c", &playAgain);
		clearBuffer();

	} while (playAgain == 'Y' || playAgain == 'y');

	system("cls");
}

void businessMenu() {
	int choice;
	char confirm;
	double principal, rate, time_val, amount, si, ci, costPrice, sellingPrice, profit, loss;

	do {
		system("cls");
		printf("=====================================\n");
		printf("||      BUSINESS CALCULATOR        ||\n");
		printf("=====================================\n");
		printf("[1] Simple Interest\n");
		printf("[2] Compound Interest\n");
		printf("[3] Profit & Loss\n");
		printf("[0] Back to Main Menu\n");
		printf("------------------------------------\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		clearBuffer();

		system("cls");

		switch (choice) {
			case 1:
				printf("=== SIMPLE INTEREST ===\n");
				printf("Principal: $");
				scanf("%lf", &principal);
				printf("Rate (%%): ");
				scanf("%lf", &rate);
				printf("Time (years): ");
				scanf("%lf", &time_val);
				clearBuffer();

				si = (principal * rate * time_val) / 100;

				printf("\nSimple Interest = $%.2lf\n", si);
				printf("Total Amount = $%.2lf\n", principal + si);
				break;

			case 2:
				printf("=== COMPOUND INTEREST ===\n");
				printf("Principal: $");
				scanf("%lf", &principal);
				printf("Rate (%%): ");
				scanf("%lf", &rate);
				printf("Time (years): ");
				scanf("%lf", &time_val);
				clearBuffer();

				amount = principal * pow((1 + rate / 100), time_val);
				ci = amount - principal;

				printf("\nCompound Interest = $%.2lf\n", ci);
				printf("Total Amount = $%.2lf\n", amount);
				break;

			case 3:
				printf("=== PROFIT & LOSS ===\n");
				printf("Cost Price: $");
				scanf("%lf", &costPrice);
				printf("Selling Price: $");
				scanf("%lf", &sellingPrice);
				clearBuffer();

				if (sellingPrice > costPrice) {
					profit = sellingPrice - costPrice;
					printf("\nPROFIT = $%.2lf\n", profit);
					printf("Profit Percentage: %.2lf%%\n", (profit / costPrice) * 100);
				} else if (sellingPrice < costPrice) {
					loss = costPrice - sellingPrice;
					printf("\nLOSS = $%.2lf\n", loss);
					printf("Loss Percentage: %.2lf%%\n", (loss / costPrice) * 100);
				} else {
					printf("\nNo Profit, No Loss.\n");
				}
				break;

			case 0:
				break;

			default:
				printf("Invalid Input!\n");
		}

		if (choice != 0) {
			printf("\nContinue? [Y/N]: ");
			scanf(" %c", &confirm);
			clearBuffer();
		} else {
			break;
		}

	} while ((confirm == 'y' || confirm == 'Y') && choice != 0);
}

void pythagorasMenu() {
	int choice;
	char confirm;
	double a, b, c, x1, y1, x2, y2, dist;

	do {
		system("cls");
		printf("====================================\n");
		printf("     PYTHAGOREAN THEOREM MENU\n");
		printf("====================================\n");
		printf("[1] Calculate Hypotenuse\n");
		printf("[2] Calculate a Leg\n");
		printf("[3] Right Triangle Checker\n");
		printf("[4] Distance Between Two Points\n");
		printf("[0] Back to Main Menu\n");
		printf("------------------------------------\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		clearBuffer();

		system("cls");

		switch (choice) {
			case 1:
				printf("=== CALCULATE HYPOTENUSE ===\n");
				printf("Enter side a: ");
				scanf("%lf", &a);
				printf("Enter side b: ");
				scanf("%lf", &b);
				clearBuffer();

				c = sqrt(a * a + b * b);

				printf("Hypotenuse (c) = %.2lf\n", c);
				break;

			case 2:
				printf("=== CALCULATE A LEG ===\n");
				printf("Enter hypotenuse (c): ");
				scanf("%lf", &c);
				printf("Enter known leg (a or b): ");
				scanf("%lf", &a);
				clearBuffer();

				if (c <= a) {
					printf("Error: Hypotenuse must be greater than leg.\n");
				} else {
					b = sqrt(c * c - a * a);
					printf("Other leg = %.2lf\n", b);
				}
				break;

			case 3:
				printf("=== RIGHT TRIANGLE CHECKER ===\n");
				printf("Enter side 1: ");
				scanf("%lf", &a);
				printf("Enter side 2: ");
				scanf("%lf", &b);
				printf("Enter side 3: ");
				scanf("%lf", &c);
				clearBuffer();

				double sides[3] = {a, b, c};
				for (int i = 0; i < 3; i++) {
					for (int j = i + 1; j < 3; j++) {
						if (sides[i] < sides[j]) {
							double temp = sides[i];
							sides[i] = sides[j];
							sides[j] = temp;
						}
					}
				}

				if (fabs(sides[1] * sides[1] + sides[2] * sides[2] - sides[0] * sides[0]) < 0.0001) {
					printf("Yes! This is a right triangle.\n");
				} else {
					printf("No, this is not a right triangle.\n");
				}
				break;

			case 4:
				printf("=== DISTANCE BETWEEN TWO POINTS ===\n");
				printf("Enter x1 y1: ");
				scanf("%lf %lf", &x1, &y1);
				printf("Enter x2 y2: ");
				scanf("%lf %lf", &x2, &y2);
				clearBuffer();

				dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				printf("Distance = %.2lf\n", dist);
				break;

			case 0:
				break;

			default:
				printf("Invalid input!\n");
		}

		if (choice != 0) {
			printf("\nContinue? [Y/N]: ");
			scanf(" %c", &confirm);
			clearBuffer();
		} else {
			break;
		}

	} while ((confirm == 'y' || confirm == 'Y') && choice != 0);
}

void rockPaperScissors() {
	int playerChoice, computerChoice;
	char confirm;
	int playerWins = 0, computerWins = 0, ties = 0;

	srand(time(0));

	do {
		system("cls");
		printf("====================================\n");
		printf("     ROCK - PAPER - SCISSORS\n");
		printf("====================================\n");
		printf("Score - You: %d | Computer: %d | Ties: %d\n", playerWins, computerWins, ties);
		printf("====================================\n");
		printf("[1] Rock\n[2] Paper\n[3] Scissors\n[0] Back\n");
		printf("Choice: ");
		scanf("%d", &playerChoice);
		clearBuffer();

		if (playerChoice == 0) break;

		if (playerChoice < 1 || playerChoice > 3) {
			printf("Invalid choice!\n");
			Sleep(1000);
			continue;
		}

		computerChoice = rand() % 3 + 1;

		printf("\nYou chose: ");
		switch (playerChoice) {
			case 1: printf("Rock\n"); break;
			case 2: printf("Paper\n"); break;
			case 3: printf("Scissors\n"); break;
		}

		printf("Computer chose: ");
		switch (computerChoice) {
			case 1: printf("Rock\n"); break;
			case 2: printf("Paper\n"); break;
			case 3: printf("Scissors\n"); break;
		}

		if (playerChoice == computerChoice) {
			printf("Result: It's a Tie!\n");
			ties++;
		} else if ((playerChoice == 1 && computerChoice == 3) ||
				   (playerChoice == 2 && computerChoice == 1) ||
				   (playerChoice == 3 && computerChoice == 2)) {
			printf("Result: You Win!\n");
			playerWins++;
		} else {
			printf("Result: Computer Wins!\n");
			computerWins++;
		}

		printf("\nPlay again? [Y/N]: ");
		scanf(" %c", &confirm);
		clearBuffer();

	} while (confirm == 'Y' || confirm == 'y');
}

void digitalClock() {
	char confirm;

	do {
		for (int i = 0; i < 10; i++) {
			system("cls");

			time_t now = time(0);
			struct tm *t = localtime(&now);

			int hour = t->tm_hour;
			int min = t->tm_min;
			int sec = t->tm_sec;

			int hour12 = hour % 12;
			if (hour12 == 0) hour12 = 12;
			char *ampm = (hour >= 12) ? "PM" : "AM";

			printf("====================================\n");
			printf("           DIGITAL CLOCK\n");
			printf("====================================\n");
			printf("          %02d : %02d : %02d %s\n", hour12, min, sec, ampm);
			printf("====================================\n");

			Sleep(1000);
		}

		printf("\nBack to Main Menu? [Y/N]: ");
		scanf(" %c", &confirm);
		clearBuffer();

	} while (confirm == 'N' || confirm == 'n');
}

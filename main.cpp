#include <iostream>
#include <ctime>

/*
 * Copyright 2024 Andre
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//Game created by André João - All Name rights Reserved

std::string name = "";  //Both this variables must be global in order to track them correctly throught the game
double balance = 1000;  //At all times

void playerProfile(std::string &name); //Function to set up the player name;

void chooseWinner(int playerValue, int dealerValue, int bet, double &balance); //Checks the Winner

void playerCardGenerator(int playercards[10], std::string playercardsName[10], int &i, int &randFactor); //Generates the player cards

void dealerCardGenerator(int dealercards[10], std::string dealercardsName[10], int &j, int &DealerRandFactor); //Generates the dealer cards

int main() {
    srand(time(NULL));
    int randFactor = rand() % 32000 + 1;    //generates a random value to assist int the pseudorandomization of the cards of the player
    int dealerRandFactor = rand() % 32000 +1;   //generates a random value to assist int the pseudorandomization of the cards of the dealer
    int choice;
    int i = 0; //Card generator indexes (used in the main function to track the cards value and name)
    int j = 0; //
    int cardIndex = 2; //Used in case the dealer needs more cards (if the cards value are bellow 17) - the index starts to index at the 3 card position
    int bet;
    int playercards[10] = {0, 0 ,0 ,0 ,0 ,0 ,0 ,0, 0, 0}; //All values must be set to 0, because if not, the array will have indexes with random numbers until assigned which
    int dealercards[10] = {0, 0 ,0 ,0 ,0 ,0 ,0 ,0, 0, 0}; //will afect the player and dealer values calculations
    std::string playercardsName[10];
    std::string dealercardsName[10];
    int playerValue = 0;
    int dealerValue = 0;

    if(balance == 0) {
        std::cout << "You are busted! Thanks for playing! " << '\n'; //Checks if the player balance its 0, if so it closes the game
        exit(main());
    }
    if(name == "") {
        playerProfile(name); //If a name isnt assigned yet , the condtion will make one be assigned
    }

    std::cout << "***** BlackJack *****" << '\n';
    std::cout << "Playing as: " << name << '\n';
    std::cout << name << "'s Balance: " << balance << "$" <<'\n';
    std::cout << "*********************" << '\n';
    std::cout << "Enter your bet: ";
    std::cin >> bet;

    if(bet < 0) {
        std::cout << "Invalid Bet Amount! " << '\n'; //A negative bet is an ilegal bet,
        main(); //if the user enters in a negative bet, the program invalids it and prompts the user to do one again
    }
    else if(bet <= balance) {
        balance = balance - bet; //Checks if the bet is legal (cant be over the player balance)
    }                            //If so it subtracts the bet from the player's balance and continues
    else {
        std::cout << "Insuficient Funds! " << '\n'; //If the bet its ilegal (over the users balance) this condition is called to inform the user
        main();
    }
    std::cout << "Your balance is now at: " << balance << "$" << '\n'; //Prints the users balance after the bet made
    std::cout << "**********************" << '\n';
    system("pause"); //Throught the code , various instances of this command are called in order to improve game readability (since it stops the code until something its pressed)

    playerCardGenerator(playercards, playercardsName, i, randFactor); //Generates the player's cards
    playerCardGenerator(playercards, playercardsName, i, randFactor);

    playerValue = playercards[0] + playercards[1]; // calculates the players cards value

    if(playerValue > 21) {
        playerValue = playerValue - playerValue;           //When the player is imediatly dealt 2 aces , they get the value of 22 (its the only way to get this number with 2 cards);
        playercards[1] = playercards[1] - playercards[1];  //which makes them lose imediatly, under blackjack rules , the second ace in this condition
        playercards[1] = playercards[1] + 1;               //is only worth 1 point in that case, this conditon checks if the value is above 21
        playerValue = playercards[0] + playercards[1];     //which means 2 aces have been dealt , in that case, it wipes the playervalue, sets the second
    }                                                      //ace to 1 , and sums the playervalue again.

    std::cout << "Your cards: " << playercardsName[0] << " " << playercardsName[1] << '\n';
    std::cout << "Your current total value: " << playerValue << '\n'; //Informs the user about the cards dealt and its values
    if(playerValue == 21) {
        std::cout << "BlackJack! " << '\n'; //If the user gets 2 cards worth a total of 21 points, the game alerts blackjack
    }

    system("pause");

    dealerCardGenerator(dealercards, dealercardsName, j , dealerRandFactor); //Generates the dealer's cards
    dealerCardGenerator(dealercards, dealercardsName, j , dealerRandFactor);

    dealerValue = dealercards[0]; //Note: In the start of the game, the dealer's cards value is only the first one because the second card isn't revealed imediatly

    std::cout << "Dealer cards: " << dealercardsName[0] << " " << "Uknown " << '\n'; //Displays the first card of the dealer and its value, and hides the second one
    std::cout << "Current dealer value: " << dealerValue << '\n';
    system("pause");
    while(choice != 2) { //Forces the user to be in the menu until they decided they want to advance through the game after asking for their desired amount of cards and also
        std::cout << "***** ChoiseMenu *****" << '\n'; //doesnt break the program if the user miss types a number that isnt 1 or 2
        std::cout << "What do you wish to do? " << '\n';
        std::cout << "(1) Ask for more cards" << '\n';
        std::cout << "(2) End your turn , reveal the dealer's cards and see if you won " << '\n';
        std::cout << "Your choice: ";
        std::cin >> choice;
        if(choice == 1) {
            playerValue = playerValue - playerValue; //resets the player value in order to get acurate card values (since the all the indexes of playercards[] will be added)
            playerCardGenerator(playercards, playercardsName, i, randFactor); //invokes the card generator function
            std::cout << "Your cards: "; //displays the cards along the for loop
            for(int a = 0; a < sizeof(playercards) / sizeof(playercards[0]); a++) {
                std::cout << playercardsName[a] << " "; //Every card its displayed (unless it doesnt exist (0))
                playerValue = playerValue + playercards[a]; // adds the values of each card in playercards[] to the player value
                if(playercards[a] == playercards[9]) { //breaks the for loop if the final index is counted
                    break;
                }
            }
            std::cout << "Your cards total value is now: " << playerValue << '\n'; //displays the new player value
            if(playerValue > 21) {
                chooseWinner(playerValue, dealerValue, bet, balance); //If the player's cards value are above 21, its a lose condtion, therefore the choose winner function its called
            }
            else if(playerValue == 21) {
                std::cout << "BlackJack! " << '\n'; //If after the card its , if the player achieves the value of 21 this message is printed to the stream
                system("pause");
            }
            else {
                system("pause"); //If none of the conditons above are prompted , the player is taken again to the choice menu
            }
        }
        else if(choice == 2) { //After the player its happy with their cards they end their turn
            std::cout << "Dealer's cards: " << dealercardsName[0] << " " << dealercardsName[1] << '\n'; // dealers cards revealed
            dealerValue = dealercards[0] + dealercards[1]; // calculate the dealer's cards value
            std::cout << "Total dealer's cards value: " << dealerValue << '\n'; //prints to the stream the dealer's cards new value
            system("pause");
            while(dealerValue < 17) { //If the dealer has cards with the value bellow 17, the while loop will generate new ones until the condtion its met
                std::cout << "Since the dealer's cards values were under 17, he got another card from the deck" << '\n';
                dealerCardGenerator(dealercards, dealercardsName, j , dealerRandFactor); //generates the dealer new cards
                std::cout << "Dealer's cards: ";
                for(int i = 0; i <= cardIndex; i++) {
                    std::cout << dealercardsName[i] << " ";     //displays the dealer's cards
                }
                std::cout << '\n';
                dealerValue += dealercards[cardIndex]; //Adds the new cards to the dealerValue variable (from the index of the new card position of the dealercards[] array
                std::cout << "The dealer's cards total value now is: " << dealerValue << '\n'; //displays the new dealer's cards value
                cardIndex++; //increments the index to be used if the dealerValue variable has a value which is still under 17 - the index will be used to correctly add the next generated card
                if(dealerValue >= 17) {
                    break; // breaks the loop if the dealerValue condtion has been met, if not the loop continues
                }
                system("pause");
            }
            if(dealerValue >= 17) {
                chooseWinner(playerValue, dealerValue, bet, balance); //If the dealerValue above 17 has been met, the chooseWinner Function its called to rule out the winner
            }
        }
        else {
            std::cout << "Invalid Option! " << '\n'; //Prompts if the user miss types a number
        }
    }
    return 0;
}

void playerProfile(std::string &name) {
    std::cout << "Enter your name: ";   //Prompts the user to insert a player name, if they refuse the function is called again
    std::cin >> name;                   //by the first condtion
}


void playerCardGenerator(int playercards[10], std::string playercardsName[10], int &i, int &randFactor) {
    int cardNum; //Integer which decides which card is generated for the player through the switch statment
    srand( 94945 + time(0) * randFactor); // Generates a seed based on a fixed seed + the current time mutiplied by the randomfactor generated
    cardNum = rand() % 13 + 1;                 // in the main function, this way making the pseudorandom numbers be more unpredicteble

    switch(cardNum) {
        case 1:
            playercards[i] = 2; //Asigns the numeric and string values depending on the cardNum integer
            playercardsName[i] = "2";
            break;
        case 2:
            playercards[i] = 3;
            playercardsName[i] = "3";
            break;
        case 3:
            playercards[i] = 4;
            playercardsName[i] = "4";
            break;
        case 4:
            playercards[i] = 5;
            playercardsName[i] = "5";
            break;
        case 5:
            playercards[i] = 6;
            playercardsName[i] = "6";
            break;
        case 6:
            playercards[i] = 7;
            playercardsName[i] = "7";
            break;
        case 7:
            playercards[i] = 8;
            playercardsName[i] = "8";
            break;
        case 8:
            playercards[i] = 9;
            playercardsName[i] = "9";
            break;
        case 9:
            playercards[i] = 10;
            playercardsName[i] = "10";
            break;
        case 10:
            playercards[i] = 10;
            playercardsName[i] = "Jack";
            break;
        case 11:
            playercards[i] = 10;
            playercardsName[i] = "Queen";
            break;
        case 12:
            playercards[i] = 10;
            playercardsName[i] = "King";
            break;
        case 13:
            playercards[i] = 11;
            playercardsName[i] = "Ace";
            break;
    }
    i++; //At the start of the game, the index its set to 0 to assign the values to the first card.
         //After that the index increments itself in order to not assign the next card to the same space, but to the next one
    randFactor = randFactor / 2; //The Random factor its divised by 2 after every generation in order to better randomize (since the random used its pseudorandom)
}

void dealerCardGenerator(int dealercards[10], std::string dealercardsName[10], int &j, int &DealerRandFactor) {
    int cardNumDealer; //Integer which decides which card is generated for the dealer through the switch statment
    srand(57478 + time(0) * DealerRandFactor); // Generates a seed based on a fixed seed + the current time mutiplied by the randomfactor generated
    cardNumDealer = rand() % 13 + 1;                // in the main function, this way making the pseudorandom numbers be more unpredicteble

    switch(cardNumDealer) {
        case 1:
            dealercards[j] = 2; //Asigns the numeric and string values depending on the cardNumDealer integer
            dealercardsName[j] = "2";
            break;
        case 2:
            dealercards[j] = 3;
            dealercardsName[j] = "3";
            break;
        case 3:
            dealercards[j] = 4;
            dealercardsName[j] = "4";
            break;
        case 4:
            dealercards[j] = 5;
            dealercardsName[j] = "5";
            break;
        case 5:
            dealercards[j] = 6;
            dealercardsName[j] = "6";
            break;
        case 6:
            dealercards[j] = 7;
            dealercardsName[j] = "7";
            break;
        case 7:
            dealercards[j] = 8;
            dealercardsName[j] = "8";
            break;
        case 8:
            dealercards[j] = 9;
            dealercardsName[j] = "9";
            break;
        case 9:
            dealercards[j] = 10;
            dealercardsName[j] = "10";
            break;
        case 10:
            dealercards[j] = 10;
            dealercardsName[j] = "Jack";
            break;
        case 11:
            dealercards[j] = 10;
            dealercardsName[j] = "Queen";
            break;
        case 12:
            dealercards[j] = 10;
            dealercardsName[j] = "King";
            break;
        case 13:
            dealercards[j] = 11;
            dealercardsName[j] = "Ace";
            break;
    }
    j++; //At the start of the game, the index its set to 0 to assign the values to the first card.
     //After that the index increments itself in order to not assign the next card to the same space, but to the next one
    DealerRandFactor = DealerRandFactor / 3; //The Random factor its divised by 3 after every generation in order to better randomize (since the random used its pseudorandom)
}                                            //Its 3 this time in order to prevent similar seeds with the player card generator

void chooseWinner(int playerValue, int dealerValue, int bet, double &balance) {
    double winnings; //Double variable which stores the bet return if the player wins
    std::cout << "Your cards value: " << playerValue << '\n';
    std::cout << "The dealer's cards value: " << dealerValue << '\n';
    if(playerValue > 21) { //If the player's cards are above 21, they lose.
        std::cout << "Oh no you have lost since you surpassed 21! As a result you lost your bet of: " << bet << "$" << " And your balance is now at: " << balance << "$" << '\n';
        system("pause");
        main();
    }
    else if(playerValue > dealerValue || dealerValue > 21) { //If the player cards value are above the dealer's
        winnings = bet * 2; // Returns the bet times 2       //Or if the dealer's cards value are above 21 , the player wins double the value of the bet he/she made
        balance = balance + winnings; // Adds the player winnins to the balance
        std::cout << "You won! Your winnings are: " << winnings << "$" << " As a result your balance is now at: " << balance << "$" << '\n';
        system("pause");
        main();
    }
    else if(playerValue == dealerValue) { //If the cards of the player and dealer are the same, they draw, and the bet its returned
        balance = balance + bet;          //returns the player's bet to his/her balance
        std::cout << "You tied! As a result we have returned your bet of: " << bet << "$" << " And your balance is now at: " << balance << "$" << '\n';
        system("pause");
        main();
    }
    else if(playerValue < dealerValue ) { //If the player's cards value are bellow the dealer's they lose the bet
        std::cout << "Oh no you have lost! As a result you lost your bet of: " << bet << "$" << " And your balance is now at: " << balance << "$" << '\n';
        system("pause");
        main();
    }
}

//Note - Every one is allowed use this software / game for free. The only request i make is that
//the name rights of the autor (me) be reserved to me and only me.

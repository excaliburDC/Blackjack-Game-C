#include <stdio.h>
#include<time.h>
#include<stdlib.h>

#define MAX_CARDS 52

typedef enum
{
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
	JACK, QUEEN, KING,ACE
} CardName;

typedef struct
{
    CardName name;
    int value;
} Card;

//FUNCTION FOR MENU SCREEN
void menu()
{
    int choice;


    while(choice != 3)
    {
    // CODE FOR MENU SCREEN
    printf("\n\n\t\t\t         <------ WELCOME TO BLACKJACK ------>");
    printf("\n\n\t1. PLAY");
    printf("\n\n\t2. RULES");
    printf("\n\n\t3. QUIT");
    printf("\n\n\t What do you wanna do ? :  ");
    scanf("%d",&choice);

        switch(choice)
        {
            case 1: system("cls");
                    play();
                    break;

            case 2: system("cls");
                    rules();
                    break;

            case 3: exit(0);
                    break;

            default:
                printf("Invalid Option... \nPlease enter a valid option....");

        }
    }

}

//FUNCTION TO UNDERSTAND INSTRUCTIONS
void rules()
{
    char choice;

    printf("\n\n\t\t\t\t\tRULES\n");
    printf("\t\t\t\t      ---------");
    printf("\n\n\n");
    printf("1. Blackjack may be played with one to eight decks of 52-card decks. For our game we will be using one deck of 52 cards only.");
    printf("\n\n2. Each participant attempts to beat the dealer by getting a count as close to 21 as possible, without going over 21");
    printf("\n\n3. Aces may be counted as 1 or 11 points, 2 to 9 according to pip value, and tens and face cards count as ten points.");
    printf("\n\n4. The value of a hand is the sum of the point values of the individual cards. Except, a BLACKJACK is the highest hand, consisting of an ace and any 10-point card, and it outranks all other 21-point hands");
    printf("\n\n5. The dealer will give two cards to each player and two cards to himself. One of the dealer cards is dealt face up. The facedown card is called the \"hole card.");
    printf("\n\n6. Play begins with the player to the dealer's left. The following are the choices available to the player:");
    printf("\n\n\tStand: Player stands pat with his cards.\n\tHit: Player draws another card (and more if he wishes). If this card causes the player's total points to exceed 21 (known as BREAKING or BUSTING) then he loses");
    printf("\n\n7. After each player has had his turn, the dealer will turn over his hole card. If the dealer has 16 or less, then he will draw another card");
    printf("\n\n8. If the dealer goes over 21 points, then any player who didn't already bust will win.");
    printf("\n\n9. If the dealer does not bust, then the higher point total between the player and dealer will win.  ");

    //if the user wants to go back to menu then he/she can do so by pressing R or r
    printf("\n\n\n\t\tGo back to menu... ");
    printf("\n\t\tPress(R/r):  ");
    scanf("\n%c",&choice);

    while((choice!='R') && (choice!='r')) // If invalid choice entered
    {
        printf("\n");
        printf("Incorrect Choice. Please Enter R or r to go back.\n");
        scanf("%c",&choice);
    }


    if((choice == 'r') || (choice == 'R')) // If yes, continue. Prints menu.
    {
            system("cls");
            menu();
    }


}

//FUNCTION TO INITIALIZE A SINGLE DECK OF CARDS
void deckInit(Card deck[])
{
    int i,current=0;

    for(i=0;i<MAX_CARDS;i++)
    {
        deck[i].name= i%13; //gets the card name;
        if(deck[i].name == KING || deck[i].name == QUEEN || deck[i].name == JACK )
        {
            deck[i].value = 10;   //gets the value for face cards
        }
        else if(deck[i].name == ACE)
        {
            deck[i].value = 11;  //gets the value for ace
        }
        else
        {
            deck[i].value = current % 9 + 2;   //gets the value for other cards
            current++;
        }
    }

}

//FUNCTION TO SHUFFLE CARDS
void shuffle(Card deck[])
{
    Card temp; // holds the card temporarily for shuffling
    int i,j;
    for(i=0;i<MAX_CARDS;i++)
    {
        j=rand() % MAX_CARDS; //selects a new location from MAX_CARDS - 1
        temp=deck[i]; //lets the temp card holder to hold a card between 0-51
        deck[i]=deck[j]; //swaps the current card with the new location
        deck[j]=temp; //swaps the temp card with new location
    }

}

//DISPLAYS THE CARD NAME WITH THEIR RESPECTIVE VALUE
void displayCard(Card card)
{
    switch(card.name)
    {
        case TWO: printf(" Two (%d)", card.value);
                  break;

        case THREE: printf(" Three (%d)", card.value);
                    break;

        case FOUR: printf(" Four (%d)", card.value);
                   break;

        case FIVE: printf(" Five (%d)", card.value);
                   break;

        case SIX: printf(" Six (%d)", card.value);
                  break;

        case SEVEN: printf(" Seven (%d)", card.value);
                    break;

        case EIGHT: printf(" Eight (%d)", card.value);
                    break;

        case NINE: printf(" Nine (%d)", card.value);
                   break;

        case KING: printf(" King (%d)", card.value);
                   break;

        case QUEEN: printf(" Queen (%d)", card.value);
                    break;

        case JACK: printf(" Jack (%d)", card.value);
                   break;

        case ACE: printf(" Ace (%d)", card.value);
                  break;
    }
}

//DEALS THE CARD TO THE PLAYERS
int dealCards(Card deck[],int *current)
{
    displayCard(deck[*current]);
    ++*current;
    return deck[*current-1].value;
}

//BEGINS THE GAME BY DEALING 2 CARDS TO PLAYERS
void beginGame(Card deck[],int *playerScore,int *dealerScore,int *currentCard)
{
    int i;
    printf("\nCards in Hand: \n");
    printf("\nPlayer's cards: ");
    for(i=0;i<2;i++)
    {
        *playerScore+=dealCards(deck,currentCard);

    }
    printf("\nPlayer's Current Score : %d",*playerScore);

    printf("\nDealer's cards: ");
    for(i=0;i<2;i++)
    {
        *dealerScore+=dealCards(deck,currentCard);
    }
    printf("\nDealer's Current Score: %d",*dealerScore);
    if(*dealerScore == 21)
    {
        printf("\n\nIt's a BLACKJACK for the Dealer....\nDealer won...\n");
        endGame();
    }
    else if (*playerScore == 21)
    {
        printf("\n\nIt's a BLACKJACK for the Player....\nPlayer won...\n");
        endGame();
    }
    else if(*playerScore == 21 && *dealerScore == 21)
    {
        printf("\n\nDAMN YOU LUCK, IT'S A TIE\n");
        endGame();
    }
}

void playersTurn(Card deck[],int *playerScore,int *currentCard)
{
    printf("\nPlayer's new card: ");
    *playerScore+=dealCards(deck,currentCard);
    printf("\nPlayer's Current Score: %d",*playerScore);

}

void dealersTurn(Card deck[],int *dealerScore,int *currentCard)
{
    printf("\n\nDealer's Turn...\n");
    while(*dealerScore <=21)
    {
        if(*dealerScore > 17)
        {
            printf("\nDealer chose to STAY...");
            return;
        }
        else
        {
            printf("\nDealer's new card: ");
            *dealerScore+=dealCards(deck,currentCard);
            printf("\nDealer's Current Score: %d",*dealerScore);
            return;


        }

    }


}


void checkWinner(int playerScore,int dealerScore)
{
        if(playerScore > dealerScore  &&  playerScore <= 21)
        {
            printf("\n\nCONGRATS BUDDY, YOU FINALLY BEAT OUR MASTER DEALER\nRespect...");
        }
        else if(playerScore < dealerScore && dealerScore <= 21)
        {
            printf("\n\nUH-OH, OUR MASTER DEALER THRASHED YOU.....\nSORRY BUDDY, BETTER LUCK NEXT TIME :( ");
        }
        else if(playerScore==dealerScore)
        {
            printf("\nUH-OH, IT'S A TIE....");
        }
        else if(playerScore > 21)
        {
             printf("\n\nDamn , it's a BUST.....\nDealer Wins...\nBetter Luck Next Time....\n");
        }
        else if(dealerScore > 21)
        {
             printf("\n\nYay , it's a BUST for the dealer.....\nPlayer Wins...\n");
        }


}

void endGame()
{
    char choice;
    printf("\n\n\t\tTHANK YOU FOR PLAYING BLACKJACK... :)");
    printf("\n\n\t\tPress 'r' or 'R' to go back to menu... ");
    scanf("\n%c",&choice);

    if(choice == 'r' || choice == 'R')
    {
        system("cls");
        menu();
    }
}

//FUNCTION TO IMPLEMENT THE GAME
void play()
{
    Card deck[MAX_CARDS];
    printf("\nStarting New Game...");
    printf("\n\nInitializing Deck....");
    deckInit(deck);
    int playerScore=0,dealerScore=0,currentCard=0,gameTurn=1;
    char option;
    srand(time(NULL));
    printf("\n\nShuffling Deck...\n");
    shuffle(deck);
    beginGame(deck,&playerScore,&dealerScore,&currentCard);


            while((option != 'S' || option !='s') && playerScore<=21 )
            {
                printf("\n\nPlayer's Turn....\n");
                printf("\nDo you want to HIT or STAY ???\n");
                printf("Press 'H' to HIT or 'S' to STAY....\n ");
                scanf(" %c",&option);

                if(option == 'H' || option == 'h')
                {
                    playersTurn(deck,&playerScore,&currentCard);
                    if(playerScore > 21)
                    {
                        checkWinner(playerScore,dealerScore);
                        endGame();
                    }
                    dealersTurn(deck,&dealerScore,&currentCard);
                    if(dealerScore > 21)
                    {
                        checkWinner(playerScore,dealerScore);
                        endGame();
                    }

                }

                if(option == 'S' || option == 's')
                {
                    dealersTurn(deck,&dealerScore,&currentCard);
                    checkWinner(playerScore,dealerScore);
                    endGame();

                }

            }

            checkWinner(playerScore,dealerScore);

}


int main()
{
    menu();

    return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

#define NUM	5

struct poker {
    int value;
    char suit[20];
}card[NUM];

typedef struct poker poker;

void reorderCard(){
	int i, j, temp;
	for (i=0; i<NUM; i++){
		for(j=0; j<NUM-1-i; j++){
			if (card[j].value > card[j+1].value){
				temp = card[j].value;
				card[j].value = card[j+1].value;
				card[j+1].value = temp;
			}
		}
	}
}

void sameCards(int *twos, int *threes, int *fours){
	int arr[14] = {0};
	*twos = *threes = *fours = 0; 
	int i;
	for(i=0; i<NUM; i++){
		arr[card[i].value] += 1;
	}
	
	for (i=0; i<14; i++){
		if (arr[i] == 2){
			*twos = 1;
		}
		
		else if (arr[i] == 3){
			*threes = 1;
		}
		
		else if (arr[i] == 4){
			*fours = 1;
		}
	}
	
}

int isStraight(){
	int i;
	for(i=0; i<NUM-1; i++){
		if (card[i].value+1 != card[i+1].value){
			return 0;
		}
	}
	return 1;
}

int isFlush(){
	int i;
	for (i=0; i<NUM-1; i++){
		if (strcmpi(card[i].suit, card[i+1].suit) > 0){
			return 0;
		}
	}
	return 1;
}

int main(){
    int i;
    printf("Please enter 5 cards.\n");
    for(i=0; i<NUM; i++){
        printf("\nCard %d\n", i+1);
        printf("Value: ");
        scanf("%d", &card[i].value);
        while (getchar() != '\n');
        printf("Suit: ");
        fgets(card[i].suit, sizeof(card[i].suit), stdin);
        card[i].suit[strcspn(card[i].suit, "\n")] = '\0';
    }
    
    reorderCard();
    
    // Pairs
    int twos, threes, fours;
    sameCards(&twos, &threes, &fours);
    
    
    // Suit
    int flush = isFlush();
	
	// Straight
    int straight = isStraight();
    
    printf("Result is: ");
    if (threes && twos) printf("Full house!");
    else if (twos) printf("One pair!");
    else if (threes) printf("Three of a kind!");
    else if (fours) printf("Four of a kind!");
    else if (straight && flush) printf("Straight flush");
    else if (straight) printf("Straight!");
    else if (flush) printf("Flush!");
    if (twos == 0 && threes == 0 && fours == 0 && straight == 0 && flush == 0) printf("Nothing");
}

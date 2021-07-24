// This code compiled with C99
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
Rolls random number and puts it into dice array
*/
void roll(int dice[])
{
    int dice0 = (rand() % 6) + 1;
    int dice1 = (rand() % 6) + 1;
    int dice2 = (rand() % 6) + 1;

    dice[0] = dice0;
    dice[1] = dice1;
    dice[2] = dice2;

}
/*
Formats dice for X-X-X string
*/
void format_dice(int dice[], char dice_string[])
{
    dice_string[0] = dice[0] + '0';
    dice_string[2] = dice[1] + '0';
    dice_string[4] = dice[2] + '0';
}

/*
Calculates dice numbers to according points
*/
int calculate(int dice[])
{
    int dice_value;
    if(dice[0] == 1 && dice[1] == 1 && dice[2] == 1) // 1-1-1 : -10p
    {
        dice_value = -10;
    }
    else if(dice[0] == 6 && dice[1] == 6 && dice[2] == 6) // 6-6-6 : 10p
    {
        dice_value = 10;
    }
    else if(dice[0] == dice[1] && dice[1] == dice[2]) // X-X-X
    {
        dice_value = 5;
    }
    else if(dice[0] == dice[1]) // Y-Y-X
    {
        if(dice[0] > 3) // Y > 3 : Xp
        {
            dice_value = dice[2];
        }
        else // Y < 4 : Xp
        {
            dice_value = -dice[2];
        }
    }
    else if(dice[0] == dice[2]) // Y-X-Y
    {
        if(dice[0] > 3) // Y > 3 : Xp
        {
            dice_value = dice[1];
        }
        else // Y < 4 : Xp
        {
            dice_value = -dice[1];
        }
    }
    else if(dice[1] == dice[2])
    {
        if(dice[1] > 3) // Y > 3 : Xp
        {
            dice_value = dice[0];
        }
        else // Y < 4 : Xp
        {
            dice_value = -dice[0];
        }
    }
    else if(dice[0] + dice[1] + dice[2] == 6) // 1-2-3 : -3p
    {
        dice_value = -3;
    }
    else if(dice[0] + dice[1] + dice[2] == 15) // 4-5-6 : 3p
    {
        dice_value = 3;
    }
    else // other combinations : 0p
    {
        dice_value = 0;
    }
    return dice_value;
}
/*
A game move for one player
*/
void game_move(char player_name[], int point_table[], int player_index)
{
    int dice[3];
    int dice_value;
    char dice_string[5] = {'0','-','0','-','0'};
    
    roll(dice);
    format_dice(dice, dice_string);
    dice_value = calculate(dice);
    point_table[player_index] += dice_value;
    printf("\n\n%s rolled: %s", player_name, dice_string);
    if(dice_value >= 0)
    {
        printf("\n\n%s gained %d points", player_name, dice_value);
    }
    else
    {
        printf("\n\n%s lost %d points", player_name, abs(dice_value));
    }
    

}
/*
Is points of a player enough to win the game?
*/
int is_won(int player_index, int point_table[])
{
    if(point_table[player_index] >= 20)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/*
Main game function
*/
void game(char username[])
{
    char buffer_dump;
    char choice;
    int round_number = 1;
    int point_table[4] = {0, 0, 0, 0};
    char player_name[50];
    int player_index;
    int game_ended = 0;

    srand(time(NULL)); // for random number generation

    while(1) // Round loop
    {
        printf("\n\nPoints Table:\n");

        for(int i = 0; i < 3; i++)
        {
            printf("\nPlayer%d\t\t%d", i+1, point_table[i]);
        }
        printf("\n%s\t\t%d", username, point_table[3]);

        player_index = 0;
        printf("\n\nRound \t%d", round_number);
        // Computer players loop
        while(player_index < 3)
        {
            sprintf(player_name, "Player%d", (player_index + 1));
            game_move(player_name, point_table, player_index);
            if(is_won(player_index, point_table))
            {
                game_ended = 1;
                printf("\n\n%s reached 20 points", player_name);
                printf("\n\nCongratulations! %s have won the game\n", player_name);
                break;
            }
            player_index++;
        }
        if(game_ended)
        {
            break;
        }
        // User playing
        printf("\n\nRoll the dice(y/n)? ");
        scanf("%c", &choice);
        scanf("%c", &buffer_dump);
        if(choice == 'n')
        {
            printf("\nExitting the game");
            break;
        }
        game_move(username, point_table, player_index);
        if(is_won(player_index, point_table))
        {
            game_ended = 1;
            printf("\n\n%s reached 20 points", username);
            printf("\n\nCongratulations! %s have won the game\n", username);
            break;
        }
        round_number++;

    }

    printf("\n\nFinal Points Table:\n");

    for(int i = 0; i < 3; i++)
    {
        printf("\nPlayer%d\t\t%d", i+1, point_table[i]);
    }
    printf("\n%s\t\t%d\n\n", username, point_table[3]);

}


int main()
{
    // Variables
    char username[50];
    char selection = '-';
    char buffer_dump;
    
    // User registration    
    printf("\nPlease enter username: ");
    scanf("%s", username);
    scanf("%c", &buffer_dump);
    printf("\nUser registered as \"%s\"", username);
    
    // Beginning of the game
    printf("\n\nDo you want to start(y/n)? ");
    do
    {
        scanf("%c", &selection);
        scanf("%c", &buffer_dump);
        if(selection == 'y')
        {
            game(username);
            break;
        }
        else if(selection != 'n')
        {
            printf("\n\nEnter a valid option!(y/n): ");    
        }
    } while(selection != 'n');
}

/*
 ********************************************
 * SNAKE LADER GAME by smharis-GITHUB.      *
 * This is an open source contribution      *
 * by smharis on GITHUB. So no copyright    *
 * is required to access or change the code.*
 ********************************************
 */

/*Code starts here*/
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define INFINITE 1
#define GAME_LIMIT 100
#define GAME_INIT 0
#define DICE_MIN 1
#define DICE_MAX 6

/*Customised API to clear screen*/
void clrscr()
{
  system("@cls||clear");
  return;
}


/*
 **************************************************
 * Customised API to generate a random number     *
 * between 1 to 6. It is being called when user   *
 * has to throw the dice.                         *
 **************************************************                        
 */
unsigned int
randr(unsigned int min, unsigned int max)
{
       double scaled = (double)rand()/RAND_MAX;

       return (max - min +1)*scaled + min;
}

int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

/*API to init the hash based on our rule-map */
void
create_hash (int  *hash) {
  if (!hash)
    return;

  /*LADDER Hashing*/
  hash[3]  = 24;
  hash[14] = 42;
  hash[30] = 86;
  hash[37] = 57;
  hash[50] = 96;
  hash[66] = 74;
  /*SNAKE Hashing*/
  hash[95] = 18;
  hash[77] = 45;
  hash[60] = 28;
  hash[34] = 10;
  hash[20] = 2;
}


/*
 ********************************************************************
 * API to calculate user's new position based on dice output.       *
 * It takes user's last position and hashmap and return the updated *
 * position.                                                        *
 ********************************************************************                                                       
 */
void
result (int *userv, int *hash) {
    int user1v = *userv;
    int dice = random_number (DICE_MIN, DICE_MAX);

    printf ("\n-------------------------------------------\n");
    printf ("User got %d on dice\n", dice);
    printf ("-------------------------------------------\n");

   /* Return if user is exceeding more than goalpoint*/
   if ((user1v + dice) > GAME_LIMIT)
     return;

   user1v+=dice;

    if (hash[user1v]) {
      if (user1v - hash[user1v] < GAME_INIT)
        printf ("Hey great, User is promoted from %d to %d\n", user1v, hash[user1v]);
      else
        printf ("Sorry , User is demoted from %d to %d\n", user1v, hash[user1v]);
      user1v = hash[user1v];
    }
    *userv = user1v;
}

/*GAME-BOARD Display*/
void
display () {
  int temp = GAME_LIMIT;
  printf ("-------------------------------------------------------------\n");
  for (int i=10;i>=1;i--) {
    for (int j=10;j>=1;j--) {
      printf ("| %d |",temp);
      temp--;
    }
    printf ("\n");
    printf ("------------------------------------------------------------\n");
  }
  printf ("------------------------------------\n");
  printf ("LADDERS                SNAKES       \n");
  printf ("---------              -------      \n");
  printf ("3  - 24                95 - 18      \n");
  printf ("14 - 42                77 - 45      \n");
  printf ("30 - 86                60 - 28      \n");
  printf ("37 - 57                34 - 10      \n");
  printf ("50 - 96                20 - 2       \n");
  printf ("66 - 74\n");
  printf ("------------------------------------\n");

  return;
}

/*MAIN Routine*/
int
main (void) {
  int user1v = GAME_INIT;
  int user2v = GAME_INIT;
  char user1c,user2c;
  int *hash = (int *)malloc(sizeof(int)*101);

  /*Hash the snake-ladder matrix*/
  create_hash (hash);

  /*Main Thread*/
  while (INFINITE) {

    /*Call gameboard display API for every new turn*/
    display();

    /*User 1*/
    printf ("+-----------+                                              +-----+\n");
    printf ("+   User 1  +  Press any key expect Q/q to throw the dice  + . . +\n");
    printf ("+-----------+                                              + . . +\n");
    printf ("                                                           +-----+\n"); 
    scanf  ("\n%c",&user1c);
    if (user1c == 'q' || user1c == 'Q') {
      printf ("User 1 has left the game so User 2 is the winner\n");
      break;
    }

    /*Throw the dice and evaluate the new position*/
    result (&user1v, hash);
    printf ("\n-------------------------------------------\n");
    printf ("User 1 new position is %d\n", user1v);
    printf ("-------------------------------------------\n");

    /*Condition to check the goalpoint*/
    if (user1v == GAME_LIMIT) {
      printf ("\n-------------------------------------------\n");
      printf("Congrats, User 1 is the WINNER\n");
      printf ("-------------------------------------------\n");
      break;
    }

    /*User 2*/
    printf ("+-----------+                                              +-----+\n");
    printf ("+   User 2  +  Press any key expect Q/q to throw the dice  + . . +\n");
    printf ("+-----------+                                              + . . +\n");
    printf ("                                                           +-----+\n");
    scanf  ("\n%c",&user2c);
    if (user2c == 'q' || user2c == 'Q') {
      printf ("User 2 has left the game so User 1 is the winner\n");
      break;
    }

    /*Throw the dice and evaluate the new position*/
    result (&user2v, hash);
    printf ("\n-------------------------------------------\n");
    printf ("User 2 new position is %d\n", user2v);
    printf ("-------------------------------------------\n");

    /*Condition to check the goalpoint*/
    if (user2v == GAME_LIMIT) {
      printf ("\n-------------------------------------------\n");
      printf("Congrats, User 2 is the WINNER\n");
      printf ("-------------------------------------------\n");
      break;
    }

   printf ("Get ready for next turn .........\n");
   sleep (1);
   clrscr();

  }/*End of infinite loop*/
  
 return 0;
}


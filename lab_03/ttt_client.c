/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ttt.h"
#define MAX_BUFFER_LEN 2048

void
ttt_1(char *host)
{
	CLIENT *clnt;
#ifndef	DEBUG
	clnt = clnt_create (host, TTT, V1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	/*
	 * 	BEGIN CODE
	*/

	
	int player = 0;                              /* Player number - 0 or 1               */
	int go = 0;                                  /* Square selection number for turn     */
	int row = 0;                                 /* Row index for a square               */  
	int column = 0;                              /* Column index for a square            */
	int winner = -1;                              /* The winning player                   */
	int play_res;
	char* buffer;

	play_args playargs;

	char** buffer_1;
	int* play_res_1;
	int* winner_1;

	/* The main game loop. The game continues for up to 9 turns */
	/* As long as there is no winner                            */
	do {
	/* Get valid player square selection */
		do {	      
			/* Print current board */
			buffer_1 = currentboard_1(NULL, clnt);
			if (buffer_1 ==  (char**) NULL){
				clnt_perror(clnt, "currentboard_1 call failed");
			}
			buffer = *buffer_1;
			printf("%s\n", buffer);


			printf("\nPlayer %d, please enter the number of the square "
			 "where you want to place your %c (or 0 to refresh the board): ", player,(player==1)?'X':'O');
			scanf(" %d", &go);

			if (go == 0){
				play_res = 0;
				continue;
			}

			row = --go/3;                                 /* Get row index of square      */
			column = go%3;                                /* Get column index of square   */

			playargs.row = row;
			playargs.column = column;
			playargs.player = player;

			play_res_1 = play_1(&playargs ,clnt);
			if (play_res_1  == (int*) NULL) {
				clnt_perror(clnt, "play_1 call failed");
			}

			play_res = *play_res_1;

			if (play_res != 0) {
				switch (play_res) {
				case 1:
					printf("Position outside board.");
					break;
				case 2:
					printf("Square already taken.");
					break;
				case 3:
					printf("Not your turn.");
					break;
				case 4:
					printf("Game has finished.");
					break;
				}
					printf(" Try again...\n");
			}
		} while(play_res != 0);

		winner_1 = checkwinner_1(NULL, clnt);
		if (winner_1 == (int*) NULL) {
			clnt_perror (clnt, "winner_1 call failed");
		}

		winner = *winner_1;
		
		player = (player+1)%2;                           /* Select player */
		printf("player %d\n", player);

  } while (winner == -1);
  
	/* Game is over so display the final board */
	buffer_1 = currentboard_1(NULL, clnt);
	if (buffer_1 ==  (char**) NULL){
		clnt_perror(clnt, "currentboard_1 call failed");
	}
	buffer = *buffer_1;
	printf("%s\n", buffer);
  
  /* Display result message */
  if(winner == 2)
    printf("\nHow boring, it is a draw\n");
  else
    printf("\nCongratulations, player %d, YOU ARE THE WINNER!\n", winner);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	ttt_1 (host);
exit (0);
}

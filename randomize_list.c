/* randomize a playlist (MUCH faster than python) */

#define MAXSONGS 5000   /* maximum number of songs to read in */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>

/* global variables */

/* file descripters */
int in;
int music;
FILE *PLIST;
FILE *out;

/* playlist */
char playlist[MAXSONGS][150];   /* holds file names of songs */
int random_song_list[MAXSONGS];     /* holds play order */


/**********************/
/*       MAIN         */
/**********************/

int main(int argc, char **argv) {
char *response;
char c;
int ct;
char cmd[130];
int songnum = 1;
int FLAG;
int song_count;
int number, i;
int SFLAG=0;
char *title, *artist, *album;

        /* open playlist */
        PLIST = fopen(argv[1],"r");
        if (PLIST == NULL) {
                perror(argv[1]);
                exit(1);
        }

        /* read in playlist */
        ct = 0;
        while(1) {
                fgets(playlist[ct++],sizeof(playlist),PLIST);
                if (feof(PLIST))
                        break;
        }
        fclose(PLIST);
        song_count = ct-1;
        printf("Read %d Songs\n",song_count);

        /* create a random song list */
        srand48((long)(time(NULL)));
        for (ct=0; ct<song_count+1; ct++)
                random_song_list[ct]=-1;

        /* create a random, non-repeating list */
        ct = 0;
        while (ct < song_count) {
                SFLAG=0;
                number = (int)(drand48() * song_count);
		//printf("ct=%d   number=%d",ct,number);
		if (ct == 0) {	/* always do 1st number */
			random_song_list[ct] = number;
			ct++;
			//printf("\n");
			continue;
		}
                for (i=0; i<ct; i++){   // dup check
                        if (random_song_list[i] == number){
                                //printf("-");
                                SFLAG=1;
                        }
                }
                if (SFLAG==0){
                        random_song_list[ct] = number;
                        //printf("+");
                        ct++;
                }
		//printf("\n");
                continue;
        }

        printf("Created %d songs\n",ct);

	/* now write new playlist to a file */

	PLIST = fopen("rand.m3u","w");
	if (PLIST == NULL) {
		perror("temp.pl");
		exit(1);
	}

	ct = 0;
	while (ct < song_count) {
		fprintf(PLIST,"%s",playlist[random_song_list[ct]]);
		ct++;
	}

	printf("Wrote %d files\n",ct);

	fflush(PLIST);
	fclose(PLIST);

	printf("Done\n");
	exit(0);
}



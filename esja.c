#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MEM_SIZE 16384

/* this program is licensed under the GNU GPLv3 */

/* make way to write and read *mem.
 * way to translate bin or dem to quat
 * way to write a crumb in binary
 *
 * a great milestone would be to skip the wtder
 * and the user would simply input the address of
 * a function (read or write e.g.) to execute
 * and the user could modifie and upgrade those 
 * functions from Esja. the wtd is only substitute
 * while i haven't finished that. Basicly making it
 * a universal turing machine (to turnimate).
 *
 * note that the role model for this computer is the 
 * IBM PC 8086
 * */

typedef uint16_t word;	/* default word, = 8 crumbs */

unsigned int terminal(int *wtdpntr);
int exec(unsigned int bw_location);
int wtder(int *wtd, unsigned int bw_location);

int read_crumb(unsigned int location, unsigned int n);
int write_crumb(unsigned int location, unsigned int n, int v);
int read_quats(unsigned int location, int end, int start);


int mov(int n, word r2);
int add(int n, word r2);

word r[35];	/* defining registers */
int status = 1;
word *mem;	/* main memory of Esja */

int main()
{ 	
	/* mem is saved to ./mem.esjaharddrive when shutdown */
	FILE *hard_disk = fopen("./mem.ehd", "w");	
	mem = malloc(sizeof(word) * MEM_SIZE);		/* mem allocation */
	fread(mem, sizeof(word), MEM_SIZE, hard_disk);
	int wtd;

	while (wtd != -1) {
		wtd = 9;
		unsigned int bw_location;
		bw_location = terminal(&wtd);	/* get the wtd and the file to work with */
		wtder(&wtd, bw_location);
	}
	fwrite(mem, sizeof(word), MEM_SIZE, hard_disk); /* write to .ehd */
	fclose(hard_disk);
}

/* gets user input: wtd (what to do) and a baseword of the file to work with */
unsigned int terminal(int *wtdpntr)
{
	char str[50];
	unsigned int bw_location, argument;

	if (status == 1) {
		printf("number of available crumbs: %d\n", MEM_SIZE * (sizeof(word)*8 / 2));
		printf("Umriturnarrettur: Oll rettindi fraskilin\n");
		status = 0;
	}
	printf(">");
	fgets(str, 50, stdin); /* safe */
	sscanf(str, "%i %u %u", wtdpntr, &bw_location, &argument);
	return bw_location;	/* return location to the baseword */
}

/* the processor,
 * executes a file from the bw_location, stops executing when it hits
 * a zero instruction.
 * */
int exec(unsigned int bw_location)
{
	int n;

	for (n = 0; n < read_quats(mem[bw_location], 2, 7); ++n) {
		printf("%d", read_quats(mem[bw_location], 2, 7) );
	}
}

/* what to do-er */
int wtder(int *wtdpntr, unsigned int bw_location)
{

	printf("%drt\n", *wtdpntr);
	switch (*wtdpntr) {
	case (0) : /* a execute wtd */
		exec(bw_location);
	case (1) : /* the write/create file */
		if (read_crumb(mem[bw_location]) == -2) { /* if the bw_location is uninitalized */
			/* automaticly initilized it as an instruction,
			 * i will add argumentation later 
			 * */
			write_crumb(bw_location, 0, 1);
		}
	}
}
/* read_butt :
 * 	a butt[er] is 4 crumbs(256 values)
 * */
int read_butt(unsigned int location, unsigned int n)
{
	if (n > 8) {
		fprintf(stderr, "read_crumb invalid index");
		return -1;
	}
	if (((mem[location] >> n*2) & 1) == 0 
			&& ((mem[location] >> n*2+1) & 1) == 0) {
		return 0;
	} else if (((mem[location] >> n*2) & 1) == 0 
			&& ((mem[location] >> n*2+1) & 1) == 1) {
		return 1;	
	} else if (((mem[location] >> n*2) & 1) == 1 
			&& ((mem[location] >> n*2+1) & 1) == 0) {
		return 2;
	} else if (((mem[location] >> n*2) & 1) == 1 
			&& ((mem[location] >> n*2+1) & 1) == 1) {
		return 3;
	} else if (mem[location] == 0) {
		return -2; /*uninitalized word*/
	}
}

/* writes a bit pair from v to word location at place n */
int write_crumb(unsigned int location, unsigned int n, int v) 
{
	switch (v) {
	
	/* write to v */
	case (0):
		mem[location] &= ~(1 << n*2);	/* set to 0 */
		mem[location] &= ~(1 << n*2+1);	/* set to 0 */
	case (1): 
		mem[location] &= ~(1 << n*2);	/* set to 0 */
		mem[location] |= (1 << n*2+1);	/* set to 1 */
	case (2):
		mem[location] |= (1 << n*2);	
		mem[location] &= ~(1 << n*2+1);
	case (3):
		mem[location] |= (1 << n*2);
		mem[location] |= (1 << n*2+1);
	default:
		fprintf(stderr, "write_crumb invalid index");
	}

}

/* reads a quaternary number,
 * returns the equlivant dem.
 *
 * location : the word where %start is
 * 
 * */ 	
int read_quats(unsigned int s_location, unsigned int e_location int end, int start)	
{
	unsigned int dem = 0, i = 1;
	int n;

	if (start <= end) {
		return -1;
	}

	for (n = start; n > end; n--) {
		dem += i * (read_crumb(mem[location], n));
		i *= 4;
	}
	return dem;
}

/* write a quaternary number from start to end, 
 * */
int write_quats(unsigned int location, int end, int start, int dem)
{
	int m, n = 1;
	int digits[16384];
	int i = 0;
	
	while (n) {
		m = dem % 4;
		digits[i] = {0, 1, 2, 3}[m];
		n =/ base;
		i++;
	}

	for (i; i > 0; i--) {
		for (n; n > 0; n--) { /* for every word */
			write_crumb();
		}
	}
	
}

int read_bw(unsigned int bw_location) 
{
	if (read_crumb(mem[bw_location], 0) == 0) {
		return 0; /*location is data*/
	} else if (read_crumb(mem[bw_location], 1) == 0 
			&& read_crumb(mem[bw_location], 0) == 1) {
		return 1; /*location is a instruction*/
	} else if (read_crumb(mem[bw_location], 1) == -1) {
		return -1; /* uninitalized word */
	}
	/* need to handle more flags */
}

int write_bw(unsigned int bw_location, int v) 
{
	if (v == 1) {
		write_crumb(9,9,9);
	}
}

int mov(int n, word r2) 
{
	r[n] = r2;
}

int add(int n, word r2)
{
	r[n] = r[n] + r2;
}

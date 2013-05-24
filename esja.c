#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 1728 /* always a multiplict of 12 */

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
 * while i haven't finished that.
 */

typedef uint16_t word;	/* default word, = 8 crumbs */

unsigned int terminal(int *wtdpntr);
int exec(unsigned int bw_location);
int wtder(int *wtd, unsigned int bw_location);

int read_crumb(unsigned int location, unsigned int n);
int write_crumb(unsigned int location, unsigned int n);
int read_quats(unsigned int location, int end, int start);


int mov(int n, word r2);
int add(int n, word r2);

word r[35];	/* defining registers */
int status = 1;
word *mem;	/* main memory of Esja */

int main()
{ 	
	FILE *hard_disk = fopen("./mem.ehd", "w");	/* mem is saved to ./mem.esjaharddrive when shutdown */
	mem = malloc(sizeof(word) * MEM_SIZE);		/* mem allocation */
	int wtd;

	while (wtd != 9) {
		wtd = -1;
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
	unsigned int bw_location;

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

/* executes a file with the bw_location, stops executing when it hits zero instruction */
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
	if (*wtdpntr == 0) { /* a execute wtd */
		puts("ht");
		exec(bw_location);
	} else if (*wtdpntr == 1) { /* the write wtd */
		;
	}
}

int read_crumb(unsigned int location, unsigned int n)	/* reads crumb n in byte c */
{
	if (n > 8) {
		printf("read_crumb invalid index");	/* better error returnment? */
		return 9;
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
	}
}

int write_crumb(unsigned int location, unsigned int n) 
{
	if (n > 8) {
		printf("write_crumb invalid index");	/* i still need a error handler */
	}

	if (n == 0) {
		mem[location] &= ~(1 << n*2);	/* set to 0 */
		mem[location] &= ~(1 << n*2+1);	/* set to 0 */
	} else if (n == 1) {
		mem[location] &= ~(1 << n*2);	/* set to 0 */
		mem[location] |= (1 << n*2+1);	/* set to 1 */
	} else if (n == 2) {
		mem[location] |= (1 << n*2);	
		mem[location] &= ~(1 << n*2+1);
	} else if (n == 3) {
		mem[location] |= (1 << n*2);
		mem[location] |= (1 << n*2+1);
	}
}

int read_quats(unsigned int location, int end, int start)	/* reads a quaternary number, */
{								/* need to make it safe. */
	unsigned int dem = 0, i = 1;
	char n;

	if (start <= end) {
		return 1;
	}

	for (n = start; n > end; n--) {
		dem =+ i * (read_crumb(mem[location], n));
		i *= 4;
	}
	return dem;
}

int read_bw(unsigned int bw_location) 
{
	if (read_crumb(mem[bw_location], 0) == 0) {
		return 0;
	} else if (read_crumb(mem[bw_location], 0) == 1 
			&& read_crumb(mem[bw_location], 0) == 0) {
		return 2;
	} /* need to handle more flags */
}

int mov(int n, word r2) 
{
	r[n] = r2;
}

int add(int n, word r2)
{
	r[n] = r[n] + r2;
}

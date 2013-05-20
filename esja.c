#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 1728 // always a multiplict of 12

// this program is licensed under the GNU GPLv3

// make way to write and read *mem.
// way to translate bin or dem to quat
// way to write a qit in binary
// need to make something to deal with cmnd[n]

int read_bit();
int read_qit();
unsigned int terminal();
int exec(unsigned int location)

int mov();
int add();

typedef uint16_t word;	// default word, = 8 qits
word r[35];	// defining registers
char status = 'a';

int main()
{ 	
	void *mem = malloc(sizeof(word) * MEM_SIZE);	// mem allocation
	char quit_loop;
	while (quit_loop) {
		terminal();	//gets a location of a block to execute
		exec(); 	//executes the block
	}
}

int read_bit(word *c, int n)
{
	static unsigned char mask[] = {128, 64, 32, 16, 8, 4, 2, 1};
	return ((*c & mask[n]) != 0);
}

int read_qit(unsigned int location, unsigned char n)	// reads qit n in byte c
{
	int i;
	if (n > 8) {
		printf("read_qit invalid index");	// better error returnment?
		return 9;
	}
	if (((mem[location] >> n*2) & 1) == 0 && ((mem[location] >> n*2+1) & 1) == 0) {
		return 0;
	} else if (((mem[location] >> n*2) & 1) == 0 && ((mem[location] >> n*2+1) & 1) == 1) {
		return 1;	
	} else if (((mem[location] >> n*2) & 1) == 1 && ((mem[location] >> n*2+1) & 1) == 0) {
		return 2;
	} else if (((mem[location] >> n*2) & 1) == 1 && ((mem[location] >> n*2+1) & 1) == 1) {
		return 3;
	}
}

int write_qit(unsigned int location, char n) 
{
	if (n > 8) {
		printf("write_qit invalid index");	// need a better error thingy
	}

	if (n == 0) {
		mem[location] &= ~(1 << n*2);	// set to 0
		mem[location] &= ~(1 << n*2+1);	// set to 0
	} else if (n == 1) {
		mem[location] &= ~(1 << n*2);	// set to 0
		mem[location] |= (1 << n*2+1);	// set to 1
	} else if (n == 2) {
		mem[location] |= (1 << n*2);
		mem[location] &= ~(1 << n*2+1);
	} else if (n == 3) {
		mem[location] |= (1 << n*2);
		mem[location] |= (1 << n*2+1)
	}
}

unsigned int terminal()
{
	char str[50], *result, n = 0;
	unsigned int location;

	if (status == 'a') {
		printf("number of available qits: %d\n", MEM_SIZE*4);
		printf("Umriturnarrettur: Oll rettindi fraskilin\n");
		status = '0';
	}
	printf(">");
	fgets(str, 47, stdin);
	sscanf(str, "%u", location);
	return location;	// return location to a bw (base word)
}

int exec(int location)	// controle unit
{
	if (word) {
		
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

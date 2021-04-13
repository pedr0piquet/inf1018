#include <stdio.h>

unsigned char switch_byte(unsigned char x)
{
	char b = x<<4;
	char c = x>>4;
	x = b | c;
	return x;
}
unsigned char rotate_left(unsigned char x, int n)
{
	return x << n |  x >> (8 - n);
}
int main() {

	printf("0x%0x\n",switch_byte(0x61));
	printf("0x%0x\n",rotate_left(0x61, 1));
	printf("0x%0x\n",rotate_left(0x61, 2));
	printf("0x0%0x\n",rotate_left(0x61, 7));
  	return 0;
}

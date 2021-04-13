#include <stdio.h>

int odd_ones(unsigned int x){
	/* escreva seu código aqui */
	int bit1 = 0;
	while(x){// se x for true (existir)
		if (x & 1)
        		bit1++;
		x = x>>1;
	}
	return bit1 & 1; //checa se o numero do final é 1 ou 0 (impar ou par)


}
int main() {
	printf("%x tem numero %s de bits 1\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
	printf("%x tem numero %s de bits 1\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
	return 0;
}

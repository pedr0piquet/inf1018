
#include <ctype.h>
#include <stdio.h>
#include <math.h>

int string2num (char *s, int base) {
    int a = 0;
    if (base<=10){
        for (; *s; s++)
            a = a * base + (*s - '0');
    }
    else{
	char c;
	for (c= *s; c; c=*++s){
		if (c > '9')
			c = *s - 39;
		a = a * base + (c - '0');
	}

    }
    return a;
}
int main (void) {
    printf("%d\n", string2num("1a", 16));
    printf("%d\n", string2num("a09b", 16));
    printf("%d\n", string2num("z09b", 36));
    return 0;
}

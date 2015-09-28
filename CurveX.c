/*
 * CurveX.c
 *
 * Created: 9/28/2015 4:23:21 PM
 *  Author: TestPower
 */ 


#include <avr/io.h>

extern void curve25519_donna(unsigned char *output, const unsigned char *a, const unsigned char *b);
void doit(unsigned char *ek,unsigned char *e,unsigned char *k);

void printhex(unsigned int val)
{
	return;
}

void printtext(char *text)
{
	
	return;
}

void doit(unsigned char *ek,unsigned char *e,unsigned char *k)
{
	int i;

	for (i = 0;i < 32;++i) printhex((unsigned int) e[i]);
	for (i = 0;i < 32;++i) printhex((unsigned int) k[i]);
	curve25519_donna(ek,e,k);
	for (i = 0;i < 32;++i) printhex((unsigned int) ek[i]);
}

unsigned char e1k[32];
unsigned char e2k[32];
unsigned char e1e2k[32];
unsigned char e2e1k[32];
unsigned char e1[32] = {3};
unsigned char e2[32] = {5};
unsigned char k[32] = {9};

int main(void)
{
	int loop;
	int i;

	for (loop = 0;loop < 10000;++loop) {
		doit(e1k,e1,k);
		doit(e2e1k,e2,e1k);
		doit(e2k,e2,k);
		doit(e1e2k,e1,e2k);
		
		for (i = 0;i < 32;++i) if (e1e2k[i] != e2e1k[i]) {
			printtext("fail\n");
			return 1;
		}
		
		for (i = 0;i < 32;++i) e1[i] ^= e2k[i];
		for (i = 0;i < 32;++i) e2[i] ^= e1k[i];
		for (i = 0;i < 32;++i) k[i] ^= e1e2k[i];
	}
    
	while(1)
    {
        //TODO:: Please write your application code 
    }
}
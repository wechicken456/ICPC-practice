/*
 * Solution to apivotal question that exceeds cpu time limit.
 * Brute force, try every possibility and check every value. 
 * No optimizations.  Very "stewpid" solution.
 * Works OK for small number of inputs.
 * John Buck Greater NY Chief Judge
 * Sept 7, 2023
 */
#include <stdio.h>

#define	MAXNUM	1000000
int valsp[MAXNUM];
unsigned char cand[MAXNUM];

int main(int argc, char **argv)
{
	int i, j, n, nPiv = 0;
	int bad;

	scanf("%d", &(n));
	for(i = 0; i < n; i++){
		scanf("%d", &(valsp[i]));
	}
	for(i = 0; i < n; i++){
		bad = 0;
		/* check the left side */
		for(j = 0; j < i; j++){
			if(valsp[j] > valsp[i]){
				bad = 1;
			}
		}
		/* check the right side */
		for(j = i+1; j < n; j++){
			if(valsp[j] < valsp[i]){
				bad = 1;
			}
		}
		if(bad == 0){
			cand[i] = 1;
			nPiv++;
		}
	}
	printf("%d", nPiv);
	if(nPiv > 100){
		nPiv = 100;
	}
	for(i = 0; i < n && nPiv > 0; i++){
		if(cand[i] == 1){
			printf(" %d", valsp[i]);
			nPiv--;
		}
	}
	printf("\n");
	return(0);
}


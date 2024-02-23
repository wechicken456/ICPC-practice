#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef unsigned long DWORD;
typedef unsigned char BYTE;
#ifdef WIN32
typedef unsigned __int64 DDWORD;
typedef __int64	SDWORD;
#else
typedef unsigned long long DDWORD;
typedef long long SDWORD;
#endif

DDWORD fact, denom, resval;
SDWORD sub;
int factPow;
char inSeq[256];

int ParseEO(char *inp)
{
	int ind, cnt, lastOdd;
	char c;
	factPow = 0;
	ind = cnt = lastOdd = 0;
	c = inp[ind];
	fact = denom = 1; sub = 0;
	while((c != 0) &&  (c != 'E') && (c != 'O')) {
		ind++;
		c = inp[ind];
	}
	if(c == 0) {
		return 1;
	}
	while((c == 'E') || (c == 'O')) {
		if(c == 'E') {
			inSeq[cnt++] = 2;
			lastOdd = 0;
		} else {
			if(lastOdd) {	// two odds in a row
				return 1;
			}
			inSeq[cnt++] = 1;
			lastOdd = 1;
		}
		ind++;
		c = inp[ind];
	}
	if(c != '2') {	// no terminator
		return 4;
	}
	if(( cnt > 0) && (inSeq[cnt-1] != 1)) { // last code must be odd
		return 2;
	}
	// if there are at least 2 codes 2nd from last must be even
	if((cnt > 1) && (inSeq[cnt-2] != 2)) {
		return 3;
	}
	for(ind = cnt-1; ind >= 0 ; ind--) {
		if(inSeq[ind] == 1) {
			sub += denom;
			denom *= 3;
		} else {
			fact *= 2;
			sub *= 2;
			factPow++;
		}
	}
	return 0;
}

int FindPow()
{
	DDWORD pow, rem, s;
	int cnt = factPow;
	pow = rem = fact;
	s = sub % denom;
	while (pow <= sub) {
		pow *= 2;
		rem = (rem*2) % denom;
		cnt++;
	}
	while ((cnt < 64) && ((rem - s + denom) % denom != 0)) {
		pow *= 2;
		rem = (rem*2) % denom;
		cnt++;
	}
	if(cnt >= 64) {
		return -1;
	}
	resval = (pow - sub)/denom;
	return 0;
}

char inbuf[256];

char prefix[16], in_file_name[32], ans_file_name[32];
int GetPrefix(char *p)
{
	int index;
	while((*p != 0) && isspace(*p)) p++;
	if(*p == 0) {
		return -1;
	}
	index = 0;
	while((index < 15) && (*p != 0) && (!isspace(*p))) {
		prefix[index++] = *p++;
	}
	prefix[index] = 0;
	return 0;
}

int MakeProblem(FILE *infp, FILE *ansfp, int index)
{
	int i, j, cnt, mask, val, Ocnt, notdone, notcnt;
	notdone = 1;
	notcnt = 0;
	while(notdone && (notcnt < 20)) {
		notcnt++;
		cnt = (rand() % 12) + 5;
		val = (rand() >> 3) | (rand() << 6);
		factPow = 0;
		fact = denom = 1; sub = 0;
		for(i = j = 0, Ocnt = 0, mask = 1; i < cnt ; i++, mask <<= 1) {
			if((val & mask) != 0) {
				inbuf[j] = 'O';
				inSeq[j++] = 1;
				Ocnt++;
				inSeq[j] = 2;
				inbuf[j++] = 'E';
			} else {
				inSeq[j] = 2;
				inbuf[j++] = 'E';
			}
		}
		inbuf[j] = 'O';
		inSeq[j++] = 1;
		if(Ocnt < 2) {
			inSeq[j] = 2;
			inbuf[j++] = 'E';
			inbuf[j] = 'O';
			inSeq[j++] = 1;
		}
		cnt = j;
		inbuf[j++] = 0;
		for(i = cnt-1; i >= 0 ; i--) {
			if(inSeq[i] == 1) {
				sub += denom;
				denom *= 3;
			} else {
				fact *= 2;
				sub *= 2;
				factPow++;
			}
		}
		if(FindPow() == 0) {
			notdone = 0;
		}
	}
	if(notdone) {
		fprintf(stderr, "no problem in 20 tries problem %d\n", index);
		return -2;
	}
	fprintf(infp, "%s\n", inbuf);
	fprintf(ansfp, "%llu\n", resval);
	return 0;
}

FILE *infile, *ansfile;

int main(int argc, char **argv)
{
	int judg_cnt, i;
	if(argc < 3) {
		fprintf(stderr, "USAGE: %s judge_cnt prefix \n", argv[0]);
		return -1;
	}
	judg_cnt = atoi(argv[1]);
	if((judg_cnt < 1) || (judg_cnt > 99)) {
		fprintf(stderr, "judg_cnt not in range 1...99\n");
		return -3;
	}
	if(GetPrefix(argv[2]) != 0) {
		fprintf(stderr, "bad prefix \"%s\"\n", argv[3]);
		return -4;
	}
	srand(0x1234);
	for(i = 1; i <= judg_cnt ; i++) {
		sprintf(&(in_file_name[0]), "%s1%03d.in", prefix, i);
		sprintf(&(ans_file_name[0]), "%s1%03d.ans", prefix, i);
		if((infile = fopen(in_file_name, "w")) == NULL) {
			fprintf(stderr, "failed to open judg in file %d \"%s\"\n", 
				i, in_file_name);
			return -7;
		}
		if((ansfile = fopen(ans_file_name, "w")) == NULL) {
			fprintf(stderr, "failed to open judg ans file %d \"%s\"\n", 
				i, ans_file_name);
			return -8;
		}
		MakeProblem(infile, ansfile, i);
		fclose(infile);
		fclose(ansfile);
	}

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define		MIN_KERN_AROUND		8
#define		MAX_KERN_AROUND		24
#define		MIN_KERN_LONG		20
#define		MAX_KERN_LONG		50
#define		MIN_EAR				10
#define		MAX_EAR				50
#define		MIN_KWF				75
#define		MAX_KWF				95

int main(int argc, char **argv)
{
	FILE *fp;
	int nStart, nGen, i, j, a, l, tot, near, kwf;
	char szFileBuf[256], szOutBuf[512];

	if(argc != 3){
		fprintf(stderr, "Usage: %s start_sample_number number_to_generate\n", argv[0]);
		return(1);
	}

	nStart = atoi(argv[1]);
	nGen = atoi(argv[2]);

	for(i = 0; i < nGen; i++){
		snprintf(&(szFileBuf[0]), sizeof(szFileBuf), "%4d.in", nStart + i);
		snprintf(&(szOutBuf[0]), sizeof(szFileBuf), "%4d.ans", nStart + i);
		fp = fopen(&(szFileBuf[0]), "rt");
		if(fp != NULL){
			fprintf(stderr, "%s already exists - remove it and try again if that's what you want\n", &(szFileBuf[0]));
			fclose(fp);
			return(2);
		}
		fp = fopen(&(szFileBuf[0]), "wt");
		if(fp == NULL){
			fprintf(stderr, "Can not create %s\n", &(szFileBuf[0]));
			return(3);
		}
		tot = 0;
		for(j = 0; j < 5; j++){
			a = (rand()>>10) % (MAX_KERN_AROUND - MIN_KERN_AROUND + 1) + MIN_KERN_AROUND;
			l = (rand()>>10) % (MAX_KERN_LONG - MIN_KERN_LONG + 1) + MIN_KERN_LONG;
			fprintf(fp, "%s%d %d", j == 0 ? "" : " ", a, l);
			tot += a*l;
		}
		tot /= 5;
		fputc('\n', fp);
		near = (rand()>>10) % (MAX_EAR - MIN_EAR + 1) + MIN_EAR;
		kwf = (rand()>>10) % (MAX_KWF - MIN_KWF + 1) + MIN_KWF;
		fprintf(fp, "%d %d\n", near, kwf);
		fclose(fp);
		fp = fopen(&(szOutBuf[0]), "wt");
		if(fp == NULL){
			fprintf(stderr, "Can not create %s\n", &(szOutBuf[0]));
			return(4);
		}
		fprintf(fp, "%d\n", (tot * near) / kwf);
		fclose(fp);
	}
	return(0);
}


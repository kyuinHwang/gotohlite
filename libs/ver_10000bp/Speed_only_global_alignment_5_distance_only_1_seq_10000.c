#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct Smax {int max_list; int max_value;};
#define max(a,b) ((((a)>(b)))?(a):(b))
int imut[15][15] = {
{ 10, -8, -8, -8, -8, 2, 2, -8, -8, 2, -8, -2, -2, -2, -4 },
{ -8, 10, -8, -8, -8, 2, -8, 2, 2, -8, -2, -8, -2, -2, -4 },
{ -8, -8, 10, -8, 2, -8, 2, -8, 2, -8, -2, -2, -8, -2, -4 },
{ -8, -8, -8, 10, 2, -8, -8, 2, -8, 2, -2, -2, -2, -8, -4 },
{ -8, -8, 2, 2, -2, -8, -4, -4, -4, -4, -2, -2, -6, -6, -2 },
{ 2, 2, -8, -8, -8, -2, -4, -4, -4, -4, -6, -6, -2, -2, -2 },
{ 2, -8, 2, -8, -4, -4, -2, -8, -4, -4, -6, -2, -6, -2, -2 },
{ -8, 2, -8, 2, -4, -4, -8, -2, -4, -4, -2, -6, -2, -6, -2 },
{ -8, 2, 2, -8, -4, -4, -4, -4, -2, -8, -2, -6, -6, -2, -2 },
{ 2, -8, -8, 2, -4, -4, -4, -4, -8, -2, -6, -2, -2, -6, -2 },
{ -8, -2, -2, -2, -2, -6, -6, -2, -2, -6, -2, -4, -4, -4, -2 },
{ -2, -8, -2, -2, -2, -6, -2, -6, -6, -2, -4, -2, -4, -4, -2 },
{ -2, -2, -8, -2, -6, -2, -6, -2, -6, -2, -4, -4, -2, -4, -2 },
{ -2, -2, -2, -8, -6, -2, -2, -6, -2, -6, -4, -4, -4, -2, -2 },
{ -4, -4, -4, -4, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }};

void free_memory(char *ptr)
{
//    printf("freeing address: %p\n",ptr);
    free(ptr);
}

char* global_alignment(char* aseq,char* bseq,int open,int ext,int rend_open,int rend_ext,int lend_open,int lend_ext)
{
    int match(char A,char B){
		int k,t;
		if (A == 'A') k = 0;
		else if (A == 'T') k = 1;
		else if (A == 'G') k = 2;
		else if (A == 'C') k = 3;
		else if (A == 'S') k = 4;
		else if (A == 'W') k = 5;
		else if (A == 'R') k = 6;
		else if (A == 'Y') k = 7;
		else if (A == 'K') k = 8;
		else if (A == 'M') k = 9;
		else if (A == 'B') k = 10;
		else if (A == 'V') k = 11;
		else if (A == 'H') k = 12;
		else if (A == 'D') k = 13;
		else k = 14;
		if (B == 'A') t = 0;
		else if (B == 'T') t = 1;
		else if (B == 'G') t = 2;
		else if (B == 'C') t = 3;
		else if (B == 'S') t = 4;
		else if (B == 'W') t = 5;
		else if (B == 'R') t = 6;
		else if (B == 'Y') t = 7;
		else if (B == 'K') t = 8;
		else if (B == 'M') t = 9;
		else if (B == 'B') t = 10;
		else if (B == 'V') t = 11;
		else if (B == 'H') t = 12;
		else if (B == 'D') t = 13;
		else t = 14;
//		printf("%c %c %f\n",A,B,imut[k][t]);
		return imut[k][t];
    };

    struct Smax max_count(int A,int B,int C)
    {
		struct Smax a;
		int T;
		T = max(A,B);
		T = max(T,C);
		a.max_value = T;
		if(T == A) a.max_list = 2;
		else if(T == B) a.max_list = 3;
		else a.max_list = 5;
		return a;
    };
    int CC[10000] = {0,};
    int DD[10000] = {0,};
    unsigned long (*TT)[10000] = (unsigned long(*)[10000])malloc(sizeof(unsigned long)*10000*10000);
//    int TT[1500][2000] = {{0,},};
    int lenx,leny,i,j,x,y,flag;
    char temp;
    char aligned_seq1[20000] = "";
    char aligned_seq2[20000] = "";
//    char aligned_sum[8000] = "";
    char* aligned_sum = malloc(33000);
    int leftscore,upscore,diagonalscore,maxscore,candidate1,candidate2,temp_double,bleftscore;
    double imatch,missmatch;
    struct Smax max_info;
    int n_end_open, n_end_gap;
    int n_gap_open;

	lenx = strlen(aseq) + 1;
	leny = strlen(bseq) + 1;
    for(i=0; i<leny+1;i++)
    {
        for(j=0; j<lenx+1;j++)
        {
            TT[i][j] = 0;
        }
    }
//    for(i=0; i<12000;i++){
//        aligned_sum[i] = '\0';
//    }
	// end gap //
	CC[0] = 0;
	for(j = 1; j<lenx;j++) // left end // debug 2015-05-06 lenx-1 => lenx
	{
		CC[j] = lend_open + ((j-1) * lend_ext); //don't used
		DD[j] = lend_open + open  + ((j-1) * lend_ext); //open * 2
		TT[0][j] = 55; // don't used 7
	}
	DD[lenx-1] = lend_open + rend_open  + ((j-1) * lend_ext); // right vertical end region
	// spreading //
	for(i = 1; i<leny-1;i++) {
	  TT[i][0] = 21;
	  temp_double = CC[0];
	  bleftscore = lend_open + open + (i * lend_ext); // left end
      for(j = 1; j<lenx-1;j++) {
	    diagonalscore = temp_double + match(aseq[j-1],bseq[i-1]);
	    temp_double = CC[j];
	    upscore = DD[j];
	    leftscore = bleftscore;
	    max_info = max_count(diagonalscore,upscore,leftscore);
	    CC[j] = max_info.max_value; // + match(aseq[j-1],bseq[i-1]);
	    TT[i][j] = max_info.max_list;
	    candidate1 = bleftscore+ ext;
	    candidate2 = CC[j] + open;
	    if (candidate1 > candidate2)
	    {
	      bleftscore = candidate1;
	      TT[i][j] = TT[i][j]*11;
	    } else
	    {
	      bleftscore = candidate2;
	    }

	    candidate1 = DD[j]+ext;
	    candidate2 = CC[j] + open;
            if (candidate1 > candidate2)
	    {
	      DD[j] = candidate1;
	      TT[i][j] = TT[i][j] * 7;
	    } else{
	      DD[j] = candidate2;
	    }
	  }	
      // vertical right end region //
      diagonalscore = temp_double + match(aseq[j-1],bseq[i-1]);
      temp_double = CC[j];
      upscore = DD[j];
      leftscore = bleftscore;
      max_info = max_count(diagonalscore,upscore,leftscore);
      CC[j] = max_info.max_value; // + match(aseq[j-1],bseq[i-1]);
      TT[i][j] = max_info.max_list;
	  candidate1 = bleftscore+ ext;
	  candidate2 = CC[j] + open;
	  if (candidate1 > candidate2)
	  {
	    bleftscore = candidate1;
	    TT[i][j] = TT[i][j]*11;
	  } else
	  {
	    bleftscore = candidate2;
	  }
      candidate1 = DD[j] + rend_ext;
	  candidate2 = CC[j] + rend_open;
      if (candidate1 > candidate2)
	  {
	    DD[j] = candidate1;
	    TT[i][j] = TT[i][j] * 7;
	  } else{
	    DD[j] = candidate2;
	  }	
      // ~ vertical right end region //
	  CC[0] = lend_open + ((i-1) * lend_ext); // left end
    }
    // horizontal right end region
	TT[i][0] = 21;
	temp_double = CC[0];
	bleftscore = lend_open + rend_open + (i * lend_ext); // left end
    for(j = 1; j<lenx-1;j++) {
	    diagonalscore = temp_double + match(aseq[j-1],bseq[i-1]);
	    temp_double = CC[j];
	    upscore = DD[j];
	    leftscore = bleftscore;
	    max_info = max_count(diagonalscore,upscore,leftscore);
	    CC[j] = max_info.max_value; // + match(aseq[j-1],bseq[i-1]);
	    TT[i][j] = max_info.max_list;
	    candidate1 = bleftscore+ rend_ext;
	    candidate2 = CC[j] + rend_open;
	    if (candidate1 > candidate2)
	    {
	      bleftscore = candidate1;
	      TT[i][j] = TT[i][j]*11;
	    } else
	    {
	      bleftscore = candidate2;
	    }
        /*
	    candidate1 = DD[j]+ext;
	    candidate2 = CC[j] + open;
            if (candidate1 > candidate2)
	    {
	      DD[j] = candidate1;
	      TT[i][j] = TT[i][j] * 7;
	    } else{
	      DD[j] = candidate2;
	    }
        */
	}	
    // vertical right end region //
    diagonalscore = temp_double + match(aseq[j-1],bseq[i-1]);
    temp_double = CC[j];
    upscore = DD[j];
    leftscore = bleftscore;
    max_info = max_count(diagonalscore,upscore,leftscore);
    CC[j] = max_info.max_value; // + match(aseq[j-1],bseq[i-1]);
    TT[i][j] = max_info.max_list;
    // ~ vertical right end region //
    //
    // ~spreading //
    // backtracking
	y = leny - 1;
	x = lenx - 1;
	imatch = 0.0;
	missmatch = 0.0;
	i = 0;
	flag = 2;
    n_gap_open = 0;
    n_end_open = 0;
    n_end_gap = 0;
	while(x != 0 ||  y != 0)
	{
		if (flag == 2)
		{
			if (TT[y][x] % 2 == 0)
			{
				if (aseq[x-1] == bseq[y-1]) imatch++;
					else missmatch++;
				i++;
				x--;
				y--;
				flag = 2;
                aligned_seq1[i-1] = aseq[x];
                aligned_seq2[i-1] = bseq[y];
			}		
			else if (TT[y][x] % 3 == 0)
			{
                n_gap_open += 1;
				i++;
				y--;
				flag = 3;
                aligned_seq1[i-1] = '-';
                aligned_seq2[i-1] = bseq[y];
			}
			else
			{
                n_gap_open += 1;
				i++;
				x--;
				flag = 5;
                aligned_seq1[i-1] = aseq[x];
                aligned_seq2[i-1] = '-';
			}
		}
		else if(flag == 3)
		{
			if (TT[y][x] % 7 == 0)
			{
				i++;
				y--;
                aligned_seq1[i-1] = '-';
                aligned_seq2[i-1] = bseq[y];
			}
			else
			{
				flag = 2;
			}
		}
		else
		{
			if (TT[y][x] % 11 == 0)
			{
				i++;
				x--;
                aligned_seq1[i-1] = aseq[x];
                aligned_seq2[i-1] = '-';
			}
			else
			{
				flag = 2;
			}
		}
	}
    sprintf(aligned_sum,"%s_%s",aligned_seq1,aligned_seq2);
    //                          aligned_seq1[4000];
	aligned_sum[strlen(aligned_seq1) + strlen(aligned_seq2) + 1] = '\0';
    free(TT);
    return aligned_sum;
    // count end gap with tracing and do only end_option != 1
};



void main(int argc, char **argv){
    int g_open = -20;
    int g_ext = -1;
    int g_rend_open = 0;
    int g_rend_ext = 0;
    int g_lend_open = 0;
    int g_lend_ext = 0;
    char* aligned_sum;
// open = -20.0;  ext = -1; end_open = 0; end_ext = 0; end_option = 1;
    aligned_sum = global_alignment(argv[1],argv[2],g_open,g_ext,g_rend_open,g_rend_ext,g_lend_open,g_lend_ext);
    printf("%s\n",aligned_sum);
//  printf("%s\n",aligned_seq1);
//  printf("%s\n",aligned_seq2);
}

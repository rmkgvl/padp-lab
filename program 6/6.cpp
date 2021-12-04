#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#define COUNT 7


char search_words[COUNT][20] = {"eius", "lorem", "ipsum", "qui", "dolor", "sit", "in"};
char file_name[4][100] = {"words1.txt","words2.txt","words3.txt","words4.txt"};
long counts[COUNT];
int line_c = 0;

int is_equal(char* a, const char* key, int ignore_case) {
	char b[20];
	strcpy(b, key);
	int len_a = strlen(a), len_b = strlen(b);

	if(len_a != len_b) 
	{
		return 0;
	}
	
	if(ignore_case) 
	{
		int i;
		for(i = 0; i < len_a; i++) 
		{
			a[i] = tolower(a[i]);
		}
		for(i = 0; i < len_b; i++) 
		{
			b[i] = tolower(b[i]);
		}
	}
	return (strcmp(a, b) ==  0);
}

void read_word(char *temp, FILE *fp) 
{
	int i = 0;
	char ch;

	while ((ch = fgetc(fp)) !=  EOF && !isalpha(ch));

	while (ch !=  EOF && isalpha(ch)) 
	{
		temp[i++] = ch;
		ch = fgetc(fp);
	}

	temp[i] = '\0';
}

long determine_count(const char *file_name, const char *key, int ignore_case) 
{
	int key_index = 0, key_len = strlen(key);
	long word_count = 0;
	char ch;
	FILE *fp = fopen(file_name, "r");
	char temp[40];
	int i = 0;
	while(feof(fp) ==  0) 
	{
		read_word(temp,fp);
		if(is_equal(temp,key,ignore_case) !=  0)
			word_count++;
	}
	return word_count;
}

int main() 
{
	int i, nt = 0, ignore_case = 1;
	char choice, buf;
    printf("input size number of threads time taken\n");
    int size[4] = {1000,5000,10000,50000};
    for(int x=0;x<4;x++)
    {
        for (nt = 1; nt <= 8; nt *= 2)
        {
            for(i = 0; i < COUNT; i++) 
            { 
                counts[i] = 0; 
            }
        
            
            double t = omp_get_wtime();
            #pragma omp parallel for shared(counts, search_words) private(i) num_threads(nt)
            for(i = 0; i < COUNT; i++) 
            {
                counts[i] = determine_count(file_name[x], search_words[i], ignore_case);
            }
            t = omp_get_wtime() - t;
            /*for(i = 0; i < COUNT; i++) 
            { 
                printf("\t%s: %ld",search_words[i], counts[i]); 
            }*/
            printf("\n%d %d %lf\n",size[x], nt, t);
        }
	}
    printf("%d",omp_get_num_procs());
}

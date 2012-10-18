#include "stdio.h"

int main(int argc, char* argv[])
{
    FILE* f_dic = fopen(argv[1], "r");
    FILE* f_words = fopen(argv[2], "w");
    char v[1000];
    while(fscanf(f_dic, "%s", v) != EOF)
    {
	fprintf(f_words, "%s\n", v);
	fgets(v, 1000, f_dic);
    }
    fclose(f_dic);
    fclose(f_words);
}

#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
	
	for(int i=0; i<256; ++i)
		freqs[i]=0;

	for(int i=0; i<size; i++)
		freqs[(int)text[i]]++;

}

HuffmanNode *makeTree(int freqs[256], int *size) {

	PriQueue *heap=makeQueue(256);
	HuffmanNode *huff=(HuffmanNode*)malloc(512*sizeof(HuffmanNode));
  	
	for(int i=0; i<256; ++i)
  	{        
		if(freqs[i] != 0)
		{
			ItemType aux;
            aux.prior=freqs[i];
            aux.content=*size;
            insert(heap, aux);
			huff[*size].value=i;
            huff[*size].left=-1;
			huff[*size].right=-1;
            (*size)++;
        }
    }
        
	if(heap->size == 1)
	{
        ItemType aux=getMin(heap);
        huff[*size].left=aux.content;
        huff[*size].right=-1;
        (*size)++; 
    }
    else
	{
        while(heap->size >= 2)
		{
            ItemType min1, min2, tmp;
            min1=getMin(heap);   
            removeMin(heap);
            min2=getMin(heap);
            removeMin(heap);
            huff[*size].left=min1.content;
            huff[*size].right=min2.content;
            tmp.content=*size;
            tmp.prior=min1.prior+min2.prior;
            insert(heap, tmp);
            (*size)++;
        }
    }
    return huff;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
	if(nodes[index].value != '\0')
	{
        codes[index]=(char*)malloc((strlen(code)+1)*sizeof(char));
        strcpy(codes[index], code);
    }
    else
	{
        strcat(code, "0");
        makeCodes(nodes[index].left, nodes, codes, code);
        code[strlen(code)-1] ='\0';
        strcat(code, "1");
        makeCodes(nodes[index].right, nodes, codes, code);
        code[strlen(code)-1] ='\0';
    }
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	
	int chara_count[256], c=0;

    if(textSize == 0)
	{
        char *blank=(char*)malloc(sizeof(char));
        blank[0]=' ';
        return blank;
    }

    for(int i=0; i <numNodes ; i++)
	{
        chara_count[(int)nodes[i].value]=c;
        c++;
    }
    
    char **codes=(char**)malloc(c*sizeof(char*));

    char *code=(char*)malloc(256*sizeof(char));
    code[0]='\0';
    makeCodes(numNodes-1, nodes, codes, code);
    
    char *cmp=(char*)malloc(256*sizeof(char));
    cmp[0]='\0';
    for(int i=0; i<textSize; i++)
	{
        int idx=chara_count[(int)text[i]];
        strcat(cmp, codes[idx]);
    }

    return cmp;
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	
	char* sentence=malloc(256*sizeof(char));

    int c=numNodes-1, length=0;
    for(int i=0; i<textSize; i++)
	{
        if(text[i] == '0')
        	c=nodes[c].left;
        
        if(text[i] == '1')
            c=nodes[c].right;
        
        if(nodes[c].value != '\0')
		{
            sentence[length]=nodes[c].value;
            length++;
            c=numNodes-1;
        }
    }
    return sentence;
}

#endif


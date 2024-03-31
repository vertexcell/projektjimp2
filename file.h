#ifndef FILE_H
#define FILE_H

typedef struct{
	int x;
	int y;
} Point;

// struktura reprezentujaca
  // blok labiryntu
typedef struct{
	Point min; //lewy gorny rog
	Point max; //prawy dolny rog
} Block;

void fileToChar(char*,char*);
Block newBlock(int, int, int, int);

Block* divideIntoBlocks(point_t);

Point biggestBlock(block_t*);

int max(int, int);

int min(int, int);
#endif

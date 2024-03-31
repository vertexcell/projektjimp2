#include <stdio.h>
#include<stdlib.h>
#include"file.h"
void fileToChar(char* name,char* maze){
		FILE* f = fopen(name, "r");
		if(f == NULL){
			fprintf(stderr, "cannot open file %s\n", name);
			exit(EXIT_FAILURE);
		}
		
		int x = 0, y = 0;
		int c;


} 
Block newBlock(int xmin, int ymin, int xmax, int ymax){
	Point A = {x1, y1};
       	Point B = {x2, y2};

	Block new;	

	new.min = A;
	new.max = B;

	return new;

}

Block* divideIntoBlocks(Point size){
	Block* blocks = (Block*)malloc(sizeof(Block) * 9); // memory for 9 blocks

    int xDivisions[3], yDivisions[3]; // storing coordinates at which maze is divided

    
    for (int i = 0; i < 3; ++i) {
        xDivisions[i] = (size.x * (i + 1) / 3) - (i < 2 ? 1 : 0); 
        if (xDivisions[i] % 2 == 0) xDivisions[i]++;
    }

    
    for (int i = 0; i < 3; ++i) {
        yDivisions[i] = (size.y * (i + 1) / 3) - (i < 2 ? 1 : 0); 
        if (yDivisions[i] % 2 == 0) yDivisions[i]++;
    }

    
    int index = 0; 
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            int startX = x == 0 ? 0 : xDivisions[x - 1] + 1;
            int startY = y == 0 ? 0 : yDivisions[y - 1] + 1;
            int endX = xDivisions[x];
            int endY = yDivisions[y];

            blocks[index++] = new_block(startX, startY, endX, endY);
        }
    }

    return blocks;
}

Point biggestBlock(Block* blocks){
	Point size;
	size.x = 0; size.y = 0;
	for(int i = 0; i < 9; i++){
		size.x = max(blocks[i].max .x-blocks[i].mini.x, size.x);
		size.y = max(blocks[i].maxi.y-blocks[i].mini.y, size.y);
	
	}
}


int max(int a, int b){
	a > b ? return a : return b;
}

int min(int a, int b){
	a < b ? return a : return b;
}


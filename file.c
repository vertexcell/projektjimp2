#include <stdio.h>
#include<stdlib.h>
#include"file.h"
void fileToChar(const char* name, char** vec, Block block, Point size){
		FILE* f = fopen(name, "r");
		if(f == NULL){
			fprintf(stderr, "cannot open file %s\n", name);
			exit(EXIT_FAILURE);
		}
		
		int x = 0, y = 0;
		int c;
		fseek(f, block.min.y*(size.x+1)+block.min.x, SEEK_SET); 
		x = block.min.x;
		y = block.min.y;
		
		while(y < block.max.y){
			while((c = fgetc(f)) != '\n'){
				if(x >= block.min.x && x < block.max.x && y < block.max.y && y >= block.min.y){
					if(c == 'X' || c == 'P' || c == 'K')
						vec[y - block.min.y][x - block.min.x] = 0;
					else
						vec[y - block.min.y][x - block.min.x] = 1;
				}
				x++;
			}
			y++;
			x=0;
		}
		
		fclose(f);

} 
Block newBlock(int xmin, int ymin, int xmax, int ymax){
	Point A = {xmin, ymin};
       	Point B = {xmax, ymax};

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

            blocks[index++] = newBlock(startX, startY, endX, endY);
        }
    }

    return blocks;
}

Point biggestBlock(Block* blocks){
	Point size;
	size.x = 0; size.y = 0;
	for(int i = 0; i < 9; i++){
		size.x = max(blocks[i].max .x-blocks[i].min.x, size.x);
		size.y = max(blocks[i].max.y-blocks[i].min.y, size.y);
	
	}
}


int max(int a, int b){
	if (a>b){
		return a;
	}	
	return b;
}

int min(int a, int b){
	if (a>b){
                return a;
        }
        return b;
}


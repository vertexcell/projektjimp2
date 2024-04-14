#include "maze.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
void read_maze_info(const char* filename, Point* maze_size, Point* start, Point* end){
	FILE* f = fopen(filename, "r");
	if(f == NULL){
		fprintf(stderr, "Nie moge czytac pliku %s\n", filename);
	}
	
	/* znalezienie rozmiaru pliku */
	int c;
	int x = 0, y = 0;
	int row_len_found = 0;
	while((c = fgetc(f)) != EOF){

		if(c == '\n' && !row_len_found){
			maze_size->x = x;
			row_len_found = 1;
		}
		if(c == '\n'){
			y += 1;
		}
		x += 1;
	}
	maze_size->y = y+1;
	
	/* znalezienie wejscia i wyjscia */
	x = 0, y = 0;
	fseek(f, 0, SEEK_SET);
	while((c = fgetc(f)) != EOF){
		if(c == 'P'){
			start->x = x;
			start->y = y;
		}
		if(c == 'K'){
			end->x = x;
			end->y = y;
		}

		x += 1;
		if(c == '\n'){
			y += 1;
			x = 0;
		}
	}
	
	fclose(f);
}
void printDirections(FILE* output, int prevX, int prevY, int x, int y) {
    if (x > prevX) fprintf(output, "Move right\n");
    else if (x < prevX) fprintf(output, "Move left\n");
    else if (y > prevY) fprintf(output, "Move down\n");
    else if (y < prevY) fprintf(output, "Move up\n");
}

void bfs(char **maze, Point start, Point end, Block block, FILE *output) {
    queue_t queue;
    initiate_queue(&queue);

    int** visited = malloc(sizeof(int*) * (block.max.y - block.min.y));
    for (int i = 0; i < block.max.y - block.min.y; i++) {
        visited[i] = calloc((block.max.x - block.min.x), sizeof(int));
    }

    push(&queue, start.y * 10000 + start.x);
    visited[start.y - block.min.y][start.x - block.min.x] = 1;
    int found = 0;

    while (!queue_is_empty(&queue) && !found) {
        int current = pop(&queue);
        int x = current % 10000;
        int y = current / 10000;

        Point directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i].x;
            int newY = y + directions[i].y;
            if (newX >= block.min.x && newX < block.max.x && newY >= block.min.y && newY < block.max.y) {
                if (!visited[newY - block.min.y][newX - block.min.x] && maze[newY - block.min.y][newX - block.min.x] != 'X') {
                    push(&queue, newY * 10000 + newX);
                    visited[newY - block.min.y][newX - block.min.x] = y * 10000 + x;
                    if (newX == end.x && newY == end.y) {
                        found = 1;
                        break;
                    }
                }
            }
        }
    }

    if (found) {
        int x = end.x, y = end.y;
        while (x != start.x || y != start.y) {
            int temp = visited[y - block.min.y][x - block.min.x];
            int prevX = temp % 10000;
            int prevY = temp / 10000;
            printDirections(output, prevX, prevY, x, y);
            x = prevX;
            y = prevY;
        }
    } else {
        fprintf(output, "No path found.\n");
    }

    for (int i = 0; i < block.max.y - block.min.y; i++) {
        free(visited[i]);
    }
    free(visited);
    drop_queue(&queue);
}

void solveMaze(const char* filename) {
    Point mazeSize, start, end;
    read_maze_info(filename, &mazeSize, &start, &end);

    Block *blocks = divideIntoBlocks(mazeSize);
    FILE *output = fopen("directions.txt", "w");

    for (int i = 0; i < 9; i++) {
        // Allocate memory for the block
        char **blockMaze = malloc((blocks[i].max.y - blocks[i].min.y) * sizeof(char*));
        for (int j = 0; j < (blocks[i].max.y - blocks[i].min.y); j++) {
            blockMaze[j] = malloc((blocks[i].max.x - blocks[i].min.x) * sizeof(char));
        }

        // Load the block from the file
        fileToChar(filename, blockMaze, blocks[i], mazeSize);

        // Check if the block contains the start or end to possibly execute BFS
        if ((start.x >= blocks[i].min.x && start.x < blocks[i].max.x && start.y >= blocks[i].min.y && start.y < blocks[i].max.y) ||
            (end.x >= blocks[i].min.x && end.x < blocks[i].max.x && end.y >= blocks[i].min.y && end.y < blocks[i].max.y)) {
            bfs(blockMaze, start, end, blocks[i], output);
        }

        // Free the block memory
        for (int j = 0; j < (blocks[i].max.y - blocks[i].min.y); j++) {
            free(blockMaze[j]);
        }
        free(blockMaze);
    }

    fclose(output);
    free(blocks);
}

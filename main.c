#include <stdio.h>
#include "queue.h"
#include "maze.h"
#include "file.h"


int main(int argc, char**argv) {
    if(argc != 2){
        printf("Niepoprawna liczba argumentów wywołania\n");
    }
    char *input_filename = argv[1];

    Point maze_size, start, end;

    read_maze_info(input_filename, &maze_size, &start, &end);

    FILE *output_file = fopen("lista_sasiedztwa.txt","w");
    FILE *input_file = fopen(argv[1],"r");

    for(int i = 0; i < maze_size.y - 1 ; i += 1) {

        for(int j = 0; j <= maze_size.x; j += 1){
                char c = fgetc(input_file);
                if (c != 'X' && c != '\n') {
                    fprintf(output_file, "%d ", j+i*maze_size.x);

					// z lewej
                    if(j - 1 >= 0){
                        fseek(input_file, -2, SEEK_CUR);
						if(fgetc(input_file) != 'X'){
							fprintf(output_file, "%d ", (j-1)+i*maze_size.x);
						}
						fseek(input_file, 1, SEEK_CUR);
                        }

					//z prawej
					if(j + 1 < maze_size.x){
						if(fgetc(input_file) != 'X'){
							fprintf(output_file, "%d ", (j+1)+i*maze_size.x);
						}
						fseek(input_file, -1, SEEK_CUR);
					}

					//z góry
					if(i - 1 >= 0){
						fseek(input_file, -maze_size.x, SEEK_CUR);
						if(fgetc(input_file) != 'X'){
							fprintf(output_file, "%d ", j+(i-1)*maze_size.x);
						}
						fseek(input_file, maze_size.x-1, SEEK_CUR);
					}

					//z dołu
					if(i + 1 <= maze_size.y){
						fseek(input_file, maze_size.x, SEEK_CUR);
						if(fgetc(input_file) != 'X'){
							fprintf(output_file, "%d ", j+(i+1)*maze_size.x);
						}
						fseek(input_file, -(maze_size.x+1), SEEK_CUR);
					}



						fprintf(output_file, "\n");
                    }

                }

        }
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <maze_file>\n", argv[0]);
        return 1;
    }
    solveMaze(argv[1]); 
    return 0;
}

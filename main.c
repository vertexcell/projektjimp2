#include <stdio.h>
#include "queue.h"

typedef struct{
	int x;
	int y;
} point_t;

void read_maze_info(char* filename, point_t* maze_size, point_t* start, point_t* end){
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

int main(int argc, char**argv) {
    if(argc != 2){
        printf("Niepoprawna liczba argumentów wywołania\n");
    }
    char *input_filename = argv[1];

    point_t maze_size, start, end;

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
    
    return 0;
}
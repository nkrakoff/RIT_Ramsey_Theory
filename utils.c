#include <stdio.h>
#include <stdlib.h>
#include <string.h>



FILE* open_file_r(const char* filename) {
	//opens a file for reading
	FILE* ifile = fopen(filename,"r");
	return ifile;
}

void close_file(FILE* iofile) {
	//closes a file
	fclose(iofile);
}

int get_next_line(FILE* ifile, char* g6) {
	//reads the next line of a graph and puts it in char* g6
	char buff[255];
	if (fgets(buff, 255, ifile)==NULL){
		return 0;
	}
	strcpy(g6,buff);
	return 1;
}

FILE* open_file_w(const char* filename) {
	//opens a file for writing
	FILE* ofile = fopen(filename,"w+");
	return ofile;
}

void write_next_line(FILE* ofile, char* g6) {
	//writes to the next line of the file
	fprintf(ofile, "%s", g6);
}

void set_M(int i,int j,int n, uint8_t* M, uint8_t b){
	//sets the i,jth entry of an adjacency matrix M with n vertices as b  
	*(M + i*n + j) = b;
}

uint8_t get_M(int i,int j,int n, uint8_t* M) {
	//gets the i,jth entry of an adjacency matrix M with n vertices
	return *(M + i*n + j);
}

uint8_t get_correct_g6_index(int n, char* g6) {
	//given a g6 char string and an index n, gets the correct bit of the g6 binary string
	int char_num = n/6;
	char bits = *(g6+char_num);
	bits = bits-63;
	int bit_num = n%6;
	uint8_t bit = (bits >> (5-bit_num)) & 0b0000001;
	return bit;
}

void print_matrix(uint8_t* M, int n) {
	//prints the matrix, for debugging purposes
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n;j++) {
			printf("%d",get_M(i,j,n,M));
		}
		printf("\n");
	}
	
}

int get_num_vertices(uint8_t* g6) {
	//gets the number of vertices of a g6 formatted graph
	//!!!!!WARNING: THIS MUST BE UPDATED IF WE EVER NEED GRAPHS OVER 63 VERTICES!!!!!!!!! 
	return *g6 -63;
}




uint8_t* convert_to_Matrix(char* g6) {
	//converts a g6 formatted graph to a matrix
	int num_v = get_num_vertices(g6);
	g6 = g6 + 1;
	uint8_t	* M = (uint8_t*) calloc(num_v*num_v,1);
	for (int i = 0; i<num_v;i++){
		for(int j = i; j<num_v; j++) {
			int indx = 0;
			for (int k =1; k<j; k++) {
				indx += k;
			}
			set_M(i,j,num_v,M, get_correct_g6_index(indx + i,g6)); 
			set_M(j,i,num_v,M, get_correct_g6_index(indx + i,g6));
			set_M(i,i,num_v,M,0); 			
		}
	}	
	return M;

}

int shareCount(int i, int j, int n, uint8_t* M){
	int count = 0;
	for(int k = 0; k < n; k++){
		if(get_M(i,k,n,M) + get_M(j,k,n,M) == 2){
			count = count + 1;
		}
	}
	return count;
}

int j4Free(int n, uint8_t* M) 
{
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			if(get_M(i,j,n,M) == 1){
				int count = shareCount(i,j,n,M);
				if(count >= 2){
					return 0;
				}
			}
		}
	}
	return 1;
}

int main( int argc, const char* argv[] )
{
	FILE* ifile = open_file_r(argv[1]);
	char* g6 = malloc(sizeof(char)*255);
	get_next_line(ifile, g6);




	
	if (argc > 2) {
		FILE* ofile = open_file_w(argv[2]);
		printf("hello\n");
		while (get_next_line(ifile, g6)==1) {
			write_next_line(ofile,g6);
		}
		close_file(ofile);
	}


	printf(g6);
	int num_v = get_num_vertices(g6);
	uint8_t* M = convert_to_Matrix(g6);
	print_matrix(M, num_v);
	printf("%d",j4Free(num_v, M));
	
	
	
	//no other code past this point
	close_file(ifile);
	free(M);
	free(g6);
}


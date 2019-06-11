#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void set_M(int i,int j,int n, uint8_t* M, uint8_t b){
	*(M + i*n + j) = b;
}

uint8_t get_M(int i,int j,int n, uint8_t* M) {
	return *(M + i*n + j);
}

uint8_t get_correct_g6_index(int n, char* g6) {
	int char_num = n/6;
	char bits = *(g6+char_num);
	bits = bits-63;
	int bit_num = n%6;
	uint8_t bit = (bits >> (5-bit_num)) & 0b0000001;
	return bit;
}

void print_matrix(uint8_t* M, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n;j++) {
			printf("%d",get_M(i,j,n,M));
		}
		printf("\n");
	}
	
}

int get_num_vertices(uint8_t* g6) {
	return *g6 -63;
}




uint8_t* convert_to_Matrix(char* g6) {
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
	// Prints each argument on the command line.
	for( int i = 0; i < argc; i++ )
	{
		printf("%s %s",argv[i], "\n");
	}
	char* test  = (char*) malloc(sizeof(char)*3);
	*test = 'C';
	*(test+1) = 'v';
	*(test+2) = '?';
	//printf("%d\n", get_correct_g6_index(9,test+1));
	int num_v = get_num_vertices(test);
	uint8_t* M = convert_to_Matrix(test);
	print_matrix(M, num_v);
	free(M);
	free(test);
	printf("%d",j4Free(num_v, M));
}


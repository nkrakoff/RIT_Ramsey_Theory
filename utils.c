#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



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
	*(M + i*64 + j) = b;
}

uint8_t get_M(int i,int j,int n, uint8_t* M) {
	//gets the i,jth entry of an adjacency matrix M with n vertices
	return *(M + i*64 + j);
}

uint8_t* add_vertex(uint8_t* M, int num_v, uint8_t* v) {
	//addes a vertex with connections to other vertices, represented by the array v, to the matrix M with num_v vertices
	uint8_t* M_new = (uint8_t*) malloc((num_v+1)*64);
	for (int i = 0; i<num_v;i++) {
		for (int j = 0; j<num_v; j++) {
			set_M(i,j,num_v+1,M_new,get_M(i,j,num_v,M));
		}
	}
	
	for (int i = 0; i<num_v; i++) {
		set_M(i,num_v,num_v+1,M_new, *(v+i));
		set_M(num_v,i,num_v+1,M_new, *(v+i));
	}
	set_M(num_v,num_v,num_v+1,M,0);
	return M_new;
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
	uint8_t	* M = (uint8_t*) calloc(num_v*64,1);
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

char * convert_to_g6(uint8_t* M, int num_v) {
	//converts the adjacency matrix M with num_v vertices into the G6 format
	char * g6 = (char *) malloc(sizeof(char)*255);
	*g6 =  (char) num_v + 63;
	int bit_place = 0;
	int g6_index = 1;
	uint8_t curr = 0;
	for (int j = 0; j<num_v; j++) {
		for (int i = 0; i<j; i++) {
			 uint8_t b = get_M(i,j,num_v,M);
			 curr = curr | (b<<(5-bit_place)); 
			bit_place = (bit_place+1)%6; 
			if (bit_place==0) {
				*(g6+g6_index) = (char) curr+63;
				g6_index++;
				curr = 0;
			}
		}
	}  
	if (bit_place!=0) {
		*(g6+g6_index) = (char) curr + 63;
		*(g6+g6_index+1) = '\n';
		*(g6+g6_index+2) = '\0';
	} else {
		*(g6+g6_index) = '\n';
		*(g6+g6_index+2) = '\0';
	}
	printf(g6);
	return g6;
	
}

int shareCount(int i, int j, int n, uint8_t* M){
	//counts the number of shared neighbors of i and j
	int count = 0;
	for(int k = 0; k < n; k++){
		if(get_M(i,k,n,M) + get_M(j,k,n,M) == 2){
			count = count + 1;
		}
	}
	return count;
}

int j4Free(int n, uint8_t* M) {\
	//checks to see if a graph M on n vertices is J_4 free
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

int j3Free(int num_v, uint8_t* M) {
	//checks to see if a graph M on n vertices is J_3 free
	for (int i = 0; i < num_v; i++) {
		int edge_count = 0;
		  for (int j = 0; j <num_v; j++) {
			  if (get_M(i,j,num_v, M)==1) {
				  edge_count++;
				  if (edge_count >= 2) {
					  return 0;
				  }
			  }
		  }
	}
	return 1;
}

uint8_t*  Induced_subgraph(int n, int* verts, uint8_t* M, int num_v) {
	//returns the induced graph of M with num_v vertices with the n vertices specified in verts
		uint8_t* M_sub = (uint8_t*) malloc(sizeof(uint8_t)*n*n);
		for (int i = 0; i <n; i++) {
			for (int j = 0; j<n; j++) {
				uint8_t b = get_M(*(verts + i), *(verts +j), num_v, M);
				set_M(i,j,n,M_sub, b);
			}
		}
		return M_sub;
}

void compliment(uint8_t* M, int num_v) {
	for (int i = 0; i< num_v; i++) {
		for (int j = 0; j<num_v; j++) {
			if (i!=j) {
				set_M(i,j,num_v,M, 1-get_M(i,j,num_v, M));
			}
		}
	}
}


int find_shared(int i, int j, uint8_t* M, int num_v, int* verts) {
	//finds the shared neighbors of i and j and puts them into verts and returns the size of verts
	int share_count=0;
	for (int k = 0; k < num_v; k++) {
		if (get_M(i, k, num_v, M)==1) {
			if (get_M(j, k, num_v, M)==1) {
				*(verts + share_count) = k;
				share_count++;
			}
		}
	}
	return share_count;
}

int jkFree(int num_v, uint8_t* M, int k) {
	//checks to see if the graph M on num_v vertices is J_k free
	if (num_v < k) {
		return 1;
	}
	if (k==3) {
		return j3Free(num_v, M);
	}
	if (k==4) {
		return j4Free(num_v, M);
	}
	
	
	int *verts = (int *) malloc(sizeof(int)*num_v);
	int k_free = 1;
	for (int i = 0; i < num_v; i++) {
		for (int j = 0; j < num_v; j++) {
			if (get_M(i,j,num_v,M)==1) {
				int share_count = find_shared(i,j,M,num_v,verts);
				uint8_t* M_sub = Induced_subgraph(share_count, verts, M, num_v);
				k_free = jkFree(share_count, M_sub, k-2);
				free(M_sub);
				if (k_free==0) {
					free(verts);
					return 0;
				}
			}
		}
	}
	free(verts);
	return 1;
}


int g6_check_jk_free(char* g6, int k, int k_0) {
	//checks to see if the graph represented in g6 format is J_k free and its compliment is J_k_0 free
	int num_v = get_num_vertices(g6);
	uint8_t* M = convert_to_Matrix(g6);
	int result = 1;
	int count = 0;
	if (k!=-1) {
		result = jkFree(num_v, M, k);

	}
	if (k_0!=-1 && result == 1) {
		compliment(M, num_v);
		result = jkFree(num_v, M, k_0);
	}
	free(M);
	return result;
}



void exhaustive_adder(const char* in_file, const char* out_file) {
	FILE* ifile = open_file_r(in_file);
	char* g6 = malloc(sizeof(char)*255);
	FILE* ofile = open_file_w(out_file);
	int verbose = 0;
		while (get_next_line(ifile, g6)==1) {
			uint8_t* M = convert_to_Matrix(g6);
			int num_v = get_num_vertices(g6);
			uint8_t* v = (uint8_t*) calloc(num_v,1);
			for (int i = 0; i<pow(2,num_v); i++) {
				for (int j = 0; j<num_v; j++) {
					*(v+j) = i>>j & 0x01;
				}
				uint8_t* M_new = add_vertex(M,num_v,v);
				char* g6_new = convert_to_g6(M_new, num_v+1);
				write_next_line(ofile,g6_new);
				free(M_new);
				free(g6_new);
			}
			verbose++;
			printf("Added to %d Graphs\n", verbose);
			free(M);
			free(v);
		}
	free(g6);
	close_file(ofile);
	close_file(ifile);
}




void filter(int k, int k_0, const char* in_file, const char* out_file) {
	//filters through in_file and writes to out_file(or prints) all graphs who are jk_free and J_k_0 free in the compliment
	FILE* ifile = open_file_r(in_file);
	char* g6 = malloc(sizeof(char)*255);
	int verbose = 0;
	int total = 0;
	if (out_file!=NULL) {
		FILE* ofile = open_file_w(out_file);
		while (get_next_line(ifile, g6)==1) {
			verbose = (verbose + 1) % 1000000;
			if (verbose==0) {
				printf("Current Total: %d\n", total);
			}
			
			
			if (g6_check_jk_free(g6, k,k_0)==1) {
				write_next_line(ofile,g6);
				total++;
			}
				
		}
			
		close_file(ofile);
	} else {
		while (get_next_line(ifile, g6)==1) {
			if (g6_check_jk_free(g6, k,k_0)==1) {
				printf("%s",g6);
				total++;
			}
		}
	}
	printf("%d\n",total);
	close_file(ifile);
	free(g6);
	
}





int main( int argc, const char* argv[] )
{	
	
	
	
	
	/*
	char* test = "FEh_?";
	uint8_t* M = convert_to_Matrix(test);
	int num_v = get_num_vertices(test);
	print_matrix(M, num_v);
	num_v = 5;
	//print_matrix(M, get_num_vertices(test));
			
	//char * g6 = convert_to_g6(M, num_v);
	//printf(g6);
	//uint8_t* M_new = add_vertex(M, num_v, v);
	//print_matrix(M_new,num_v+1);
	//free(g6);
	free(M);
	//free(M_new);
	
	*/
	
	
	if (argc<3) {
		char * test = (char *) malloc(4);
		*test = 00000001;
		*(test +1) = 'r';
		printf("%s",test);
		return 0;
	}
	const char* k_char = argv[1];
	if (*k_char=='F') {
		k_char++;
		int count = 0;
		while (*(k_char + count) != 'C' && *(k_char + count) != '\0') {
			count++;
		}
	
		int k_0=0;
		if (*(k_char + count)!='\0') {
			k_0 = atoi(k_char + count+1);
		} else {
			k_0 = -1;
		}
		int k = atoi(k_char);
		if (k==0) {
			k=-1;
		}
		printf("%d\n%d\n", k, k_0);
	
		if (argc==3) {
			filter(k,k_0,argv[2], NULL);
		} else {
			filter(k,k_0, argv[2], argv[3]);
		}
	} else if (*k_char=='A') {
		if (argc>3) {
			exhaustive_adder(argv[2],argv[3]);
		}
	}
	
}


T = [[0,0,0],[1,0,0],[1,1,0]]

L = [[0,0,0,0,0,0,0,0],[1,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,1,0,0,0,0,0],
[0,0,0,0,0,0,0,0],[0,0,0,0,1,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,1,0]]

C = [[1,0,1,0,1,0,1,0],[0,1,0,1,0,1,0,1],[0,1,0,1,1,0,1,0],
[1,0,1,0,0,1,0,1],[1,0,0,1,0,1,1,0],[0,1,1,0,1,0,0,1],[0,1,1,0,0,1,1,0],
[1,0,0,1,1,0,0,1]]

V = [1,1,1,1,1,1,1,1]




def transpose(matrix):
    matrix_t = zip(*matrix)
    return matrix_t   

def block_Diag(matricies):
    dim = 0
    for matrix in matricies:
        for row in matrix:
            dim = dim + len(row)
            
def link_block_row(matricies):

def link_block_col(matricies):
    

def zeros(n,m):
    row_zeros = [0] * m
    for i in range(n)
        matrix_zeros.append(row_zeros)
    return matrix_zeros

def ones(n,m):
    row_ones = [1] * m
    for i in range(n)
        matrix_ones.append(row_ones)
    return matrix_ones
    
def combine_list(first, second):
    list_a = first + second
    return list_a
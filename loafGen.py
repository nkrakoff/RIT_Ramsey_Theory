T = [[0,0,0],[1,0,0],[1,1,0]]

L = [[0,0,0,0,0,0,0,0],[1,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,1,0,0,0,0,0],
[0,0,0,0,0,0,0,0],[0,0,0,0,1,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,1,0]]

C = [[1,0,1,0,1,0,1,0],[0,1,0,1,0,1,0,1],[0,1,0,1,1,0,1,0],
[1,0,1,0,0,1,0,1],[1,0,0,1,0,1,1,0],[0,1,1,0,1,0,0,1],[0,1,1,0,0,1,1,0],
[1,0,0,1,1,0,0,1]]

V = [1,1,1,1,1,1,1,1]

S = [
[0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[1,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0],
[1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1],
[1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1],
[1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0],
[1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0],
[1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1],
[1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1],
[1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0],
[1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
[0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,1,0,0,1],
[0,1,0,0,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0],
[0,1,0,0,1,0,1,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,1,0],
[0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,1],
[0,1,0,1,0,0,1,0,1,1,0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1],
[0,1,0,0,1,1,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,1,0,1,0],
[0,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1,0],
[0,1,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1],
[0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0],
[0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0],
[0,0,1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,0,1,0,0,0,0],
[0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0],
[0,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,0,0,0,0,0,1,0,0],
[0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,0,0,0,1,0,0,0],
[0,0,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1],
[0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,0,0,0,1,0],
]

c_five = [
[0,1,0,0,1],
[1,0,1,0,0],
[0,1,0,1,0],
[0,0,1,0,1],
[0,0,0,1,0]
]

def to_g6(num_verticies, matrix):
    upper_triangle = ""
    for j in range(num_verticies):
        for i in range(num_verticies):
            if i < j:
                upper_triangle = upper_triangle + str(matrix[i][j])

    rem = len(upper_triangle) % 6
    pad = "0" * rem
    bit_vector = upper_triangle + pad
    
    g6 = chr(num_verticies + 63)
    count = 0
    lump = ""
    for e in bit_vector:
        lump = lump + e
        if (count + 1) % 6 == 0:
            g6 = g6 + chr(binaryToDecimal(lump) + 63)
            lump = ""
        count = count + 1
    return(g6)
    
def binaryToDecimal(n): 
    return int(n,2) 

"""
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
"""
    
    
    
to_g6(27, S)
import sys

def main():
    input_file = sys.argv[1]
    if len(sys.argv)>2:
        output_file = sys.argv[2]
    
    
    g = Convert_G6_to_Bin("Dhc")
    g = convert_Bin_to_Matrix(g)
    Matrix_print(g)



def G6_char_to_Bin(c):
    val = ord(c) - 63
    bits = bin(val)
    bits = bits[2:]
    while len(bits) < 6:
        bits = "0" + bits
    return list(bits)
    
def Convert_G6_to_Bin(Str):
    Graph_bin = []
    for i in Str:
        Graph_bin.extend(G6_char_to_Bin(i))
    return Graph_bin
    
    
    
def convert_Bin_to_Matrix(Bin):
    num_v = ''.join(Bin[:6])
    num_v = int(num_v,2)
    m = Bin[6:]
    M = []
    for i in range(num_v):
        M.append([0]*num_v)
    for i in range(num_v):
        for j in range(i+1,num_v):
            indx = 0
            for k in range(1,j):
                indx+=k
            M[i][j] = m[indx + i]
            M[j][i] = m[indx + i]
            M[i][i] = 0
    
            
    return M
        

def Matrix_print(M):
    for i in M:
        print(i)


if __name__== "__main__":
    main()

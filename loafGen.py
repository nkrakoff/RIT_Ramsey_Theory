
sg = [['011111111110000000000000000'],
['101000000001111111100000000'],
['110000000000000000011111111'],
['100010000001111000011110000'],
['100100000000000111100001111'],
['100000100001100110011001100'],
['100001000000011001100110011'],
['100000001001010101010101010'],
['100000010000101010101010101'],
['100000000011001011001101001'],
['100000000100110100110010110'],
['010101010100000000100010111'],
['010101001010000001000101011'],
['010100110010000010001001101'],
['010100101100000100010001110'],
['010011010010001000001110001'],
['010011001100010000010110010'],
['010010110100100000011010100'],
['010010101011000000011101000'],
['001101010010001011100000001'],
['001101001100010101100000010'],
['001100110100100110100000100'],
['001100101011000111000001000'],
['001011010100111000100010000'],
['001011001011011001000100000'],
['001010110011101010001000000'],
['001010101101110100010000000']]



def print_matrix(s):
    for e in s:
        for f in e:
            print(f,end = '')
        print("")
    print("")

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
    print (g6)
    return g6
    
def binaryToDecimal(n): 
    return int(n,2) 


def create_sg():
    s = []
    for i in range(27):
        arr = [0] * 27
        s.append(arr)
    create_triangle(s)
    pair_loafs(s)
    add_loafs(s)
    connect_loafs(s,3,11)
    connect_loafs(s,3,19)
    f = open(sg_pos.txt, "a")
    #finish_connections(s)
    to_g6(27,s)
    
    
    for e in s:
        for f in e:
            print(f,end = '')
        print("")
        
    return
    
def create_triangle(s):
    for i in range(3):
        for j in range(3):
            if (i!=j):
                s[i][j] = 1


    return 

def pair_loafs(s):
    for i in range(3,27,2):
        s[i][i+1]=1
        s[i+1][i]=1
 
 
def add_loafs(s):
    for i in range(3):
        for j in range(8):
            s[i][3+8*i+j] = 1
            s[3+8*i+j][i] = 1

def connect_loafs(s,k,l):
    combos = [[1,1,1,1],[0,0,0,0],[1,1,0,0],[0,0,1,1],[1,0,0,1],[0,1,1,0],[1,0,1,0],[0,1,0,1]]
    connect = []
    for i in range(8):
        arr = [0]*8
        connect.append(arr)
    
    for i in range(8):
        for j in range(4):
            if combos[i][j] == 1:
                connect[i][2*j] = 1
            else:
                connect[i][2*j+1] = 1
    
    for i in range(8):
        for j in range(8):
            s[k+i][l+j] = connect[i][j] 
            s[l+j][k+i] = connect[i][j]

    return
    
def finish_connections(s):
    combos = [[0,1,0,0],[1,0,1,1],[1,0,0,0],[0,1,1,1],[0,0,1,0],[1,1,0,1],[0,0,0,1],[1,1,1,0]]
    connect = []
    for i in range(8):
        arr = [0]*8
        connect.append(arr)
    
    for i in range(8):
        for j in range(4):
            if combos[i][j] == 1:
                connect[i][2*j] = 1
            else:
                connect[i][2*j+1] = 1
                
    for i in range(8):
        for j in range(8):
            s[11+i][19+j] = connect[i][j]
            s[19+j][11+i] = connect[i][j]
    return
    
def swap(s,i,j):
    s[i],s[j] = s[j],s[i]
    for k in range(len(s)):
       s[k][i], s[k][j] = s[k][j], s[k][i]
    
sg_real = []
for i in sg:
   arr = []
   for j in i[0]:
        arr.append(j)
   sg_real.append(arr)

swap(sg_real,12,18)
swap(sg_real,14,16)
swap(sg_real,20,26)
swap(sg_real,22,24)

def insert_vertex(s, i):
    arr = [0]*len(s)
    s.insert(i,arr)
    for e in s:
        e.insert(i,0)
        

#insert_vertex(sg_real,27)
insert_vertex(sg_real,19)
insert_vertex(sg_real,11)

extra1 = [1,0,0,
0,0,0,0,0,0,0,0,
0,
1,0,1,0,1,0,1,0,
1,0,1,0,1,0,1,0,
1]

extra2 = [0,1,0,
1,0,1,0,1,0,1,0,
1,
0,0,0,0,0,0,0,0,
0,1,0,1,0,1,0,1,
1]

extra3 = [0,0,1,
1,0,1,0,1,0,1,0,
1,
1,0,1,0,1,0,1,0,
1,
0,0,0,0,0,0,0,0,
0]

for i in range(len(extra1)):
    sg_real[11][i] = extra1[i]
    sg_real[i][11] = extra1[i]
    sg_real[i][20] = extra2[i]
    sg_real[20][i] = extra2[i]
    #sg_real[29][i] = extra3[i]
    #sg_real[i][29] = extra3[i]



to_g6(29,sg_real)
print_matrix(sg_real)


#create_sg()

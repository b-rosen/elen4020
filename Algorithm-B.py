from mrjob.job import MRJob

count = 0
mat2 = False
matFinish = False
A = []
B = []
rows1 = 0
columns1 = 0
rows2 = 0
columns2 = 0

class MatrixMultiplication2(MRJob):

    def mapper(self, _, line):
        global count, mat2, matFinish, A, B, rows1, columns1, rows2, columns2
        
        line = line.split()
        lineInt = []
        for entry in line:
            lineInt.append(int(entry))
        line = lineInt
        
        if len(line) < 3:
            count = line[0]*line[1]
            if mat2 == False:
                rows1 = line[0]
                columns1 = line[1]
                A = [[0 for i in range(line[1])] for j in range(line[0])]
            else:
                rows2 = line[0]
                columns2 = line[1]
                B = [[0 for j in range(line[1])] for k in range(line[0])]
        elif mat2 == False:
            count -= 1
            A[line[0]][line[1]] = line[2]
            if count == 0:
                mat2 = True
        else:
            count -= 1
            B[line[0]][line[1]] = line[2]
            if count == 0:
                matFinish = True
                
        if matFinish:
            for k in range(0,columns2):
                for i in range(0,rows1):
                    for j in range(0,columns1):
                        yield((i,k),A[i][j])
            
            for i in range(0,rows1):
                for j in range(0,rows2):
                    for k in range(0,columns2):
                        yield((i,k),B[j][k])


    def reducer(self, key, values):
        print(str(key[0]) + ' ' + str(key[1]) + ' ' + str(sum(values)))
        

if __name__ == '__main__':
    MatrixMultiplication2.run()

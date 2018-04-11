from mrjob.job import MRJob
import os
import sys

A = []
B = []
rows1 = 0
columns1 = 0
rows2 = 0
columns2 = 0
lastLine = str()
    

class MatrixMultiplication2(MRJob):
    def mapper(self, _, line):
        global A, B, rows1, columns1, rows2, columns2, lastLine
        
        inLine = line
        line = line.split()
        lineInt = []
        for entry in line:
            lineInt.append(int(entry))
        line = lineInt
        
        if line[0] != rows1 and line[0] != rows2:
            if len(line) < 3:
                if 'A' in os.environ['map_input_file'] and rows1 == 1:
                    A[0][line[0]] = line[1]
                elif 'A' in os.environ['map_input_file'] and columns1 == 1:
                    A[line[0]][0] = line[1]   
                elif 'B' in os.environ['map_input_file']:
                    B[0][line[0]] = line[1]
                else:
                    B[line[0]][0] = line[1]
                    
            elif 'A' in os.environ['map_input_file']:
                A[line[0]][line[1]] = line[2]
            else:
                B[line[0]][line[1]] = line[2]
            
            if inLine.strip() == lastLine.strip() and 'B' in os.environ['map_input_file']:
                for k in range(0,columns2):
                    for i in range(0,rows1):
                        for j in range(0,columns1):
                            yield((i,k),A[i][j])
    
                for i in range(0,rows1):
                    for j in range(0,rows2):
                        for k in range(0,columns2):
                            yield((i,k),B[j][k])


    def reducer(self, key, values):
        global columns1
        sumVal = 0
        values = list(values)
        for j in range(0,columns1):
            tempVal = values[j]*values[columns1+j]
            sumVal += tempVal
        
        if sumVal != 0:
            print(str(key[0]) + ' ' + str(key[1]) + ' ' + str(sumVal))


if __name__ == '__main__':
    fileA = open(str(sys.argv[1]),'r')
    dimensionsA = fileA.readline().split()
    fileA.close()
    fileB = open(str(sys.argv[2]),'r')
    dimensionsB = fileB.readline().split()
    lastLine = fileB.readlines()[-1]
    fileB.close()
    
    rows1 = int(dimensionsA[0])
    columns1 = int(dimensionsA[1])
    rows2 = int(dimensionsB[0])
    columns2 = int(dimensionsB[1])
    
    A = [[0 for i in range(rows1)] for j in range(columns1)]
    B = [[0 for j in range(rows2)] for k in range(columns2)]
    print(str(rows1) + ' ' + str(columns2))
    
    MatrixMultiplication2.run()
    

import random

commonSize = 4
smallMatrix1Dim = (commonSize, 2)
smallMatrix2Dim = (4, commonSize)

commonSize = 200
largeMatrix1Dim = (commonSize, 100)
largeMatrix2Dim = (500, commonSize)

def PrintMatrix(matrix1Dim, matrix2Dim, filename):
    file = open(filename, 'w')
    data = []
    data.append(str(matrix1Dim[0]) + ' ' + str(matrix1Dim[1]))
    for x in range(0, matrix1Dim[0]):
        for y in range(0, matrix1Dim[1]):
            data.append(str(x) + ' ' + str(y) + ' ' + str(random.randint(0, 1000)))

    data.append(str(matrix2Dim[0]) + ' ' + str(matrix2Dim[1]))
    for x in range(0, matrix2Dim[0]):
        for y in range(0, matrix2Dim[1]):
            data.append(str(x) + ' ' + str(y) + ' ' + str(random.randint(0, 1000)))
    data = '\n'.join(data)
    file.write(data)
    file.close()

PrintMatrix(smallMatrix1Dim, smallMatrix2Dim, 'smallMatrices.txt')
PrintMatrix(largeMatrix1Dim, largeMatrix2Dim, 'largeMatrices.txt')

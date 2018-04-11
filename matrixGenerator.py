import random

commonSize = 4
smallMatrix1Dim = (2, commonSize)
smallMatrix2Dim = (commonSize, 4)

commonSize = 200
largeMatrix1Dim = (100, commonSize)
largeMatrix2Dim = (commonSize, 500)

def PrintMatrix(matrixDim, filename):
    file = open(filename, 'w')
    data = []
    data.append(str(matrixDim[0]) + ' ' + str(matrixDim[1]))
    for x in range(0, matrixDim[0]):
        for y in range(0, matrixDim[1]):
            data.append(str(x) + ' ' + str(y) + ' ' + str(random.randint(0, 100)))
    data = '\n'.join(data)
    file.write(data)
    file.close()

PrintMatrix(smallMatrix1Dim, 'smallMatricesA.txt')
PrintMatrix(smallMatrix2Dim, 'smallMatricesB.txt')
PrintMatrix(largeMatrix1Dim, 'largeMatricesA.txt')
PrintMatrix(largeMatrix2Dim, 'largeMatricesB.txt')

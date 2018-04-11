from mrjob.job import MRJob, MRStep
import os
import sys

class MatrixMultiplication(MRJob):
    def steps(self):
        return [
            MRStep(mapper=self.mapper, reducer=self.reducerMulti),
            MRStep(reducer=self.reducerAdd)
        ]

    def mapper(self, _, line):
        global count, secondMatrix

        line = line.split()
        if line != dimensionsA and line != dimensionsB:
            lineInt = []
            for entry in line:
                lineInt.append(int(entry))
            line = lineInt
            if 'A' in os.environ['map_input_file']:
                # Do mapping for first matrix
                if dimensionsA[0] == '1':
                    line.insert(0, 0)
                elif dimensionsA[1] == '1':
                    line.insert(1, 0)
                line.append(1)
                yield (line[1], line)
            else:
                if dimensionsB[0] == '1':
                    line.insert(0, 0)
                elif dimensionsB[1] == '1':
                    line.insert(1, 0)
                # Do mapping for second matrix
                line.append(2)
                yield (line[0], line)

    def reducerMulti(self, key, values):
        matrix1 = []
        matrix2 = []
        for value in values:
            if value[-1] == 1:
                matrix1.append(value)
            else:
                matrix2.append(value)
        for entry1 in matrix1:
            for entry2 in matrix2:
                yield ((entry1[0], entry2[1]), entry1[2]*entry2[2])

    def reducerAdd(self, key, values):
        print (str(key[0]) + ' ' + str(key[1]) + ' ' + str(sum(values)))

if __name__ == '__main__':
    fileA = open(str(sys.argv[1]),'r')
    dimensionsA = fileA.readline().split()
    fileA.close()
    fileB = open(str(sys.argv[2]),'r')
    dimensionsB = fileB.readline().split()
    fileB.close()
    print (dimensionsA[0], dimensionsB[1])
    MatrixMultiplication.run()

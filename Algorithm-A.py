from mrjob.job import MRJob, MRStep

count = 0
secondMatrix = False

class MatrixMultiplication(MRJob):
    def steps(self):
        return [
            MRStep(mapper=self.mapper,
                   reducer=self.reducerMulti),
            MRStep(reducer=self.reducerAdd)
        ]

    def mapper(self, _, line):
        global count, secondMatrix

        line = line.split()
        lineInt = []
        for entry in line:
            lineInt.append(int(entry))
        line = lineInt
        if len(line) < 3:
            if secondMatrix == False:
                count = line[0] * line[1]
                yield ('matrixSize', line[0])
            else:
                yield ('matrixSize', line[1])
        elif secondMatrix == False:
            count -= 1
            if count == 0:
                secondMatrix = True
            # Do mapping for first matrix
            line.append(1)
            yield (line[1], line)
        else:
            # Do mapping for second matrix
            line.append(2)
            yield (line[0], line)

    def reducerMulti(self, key, values):
        if key == 'matrixSize':
            for value in values:
                yield ('matrixSize', value)
        else:
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
        if len(key) == 10:
            output = str()
            for value in values:
                output += str(value) + ' '
            print(output)
        else:
            print(str(key[0]) + ' ' + str(key[1]) + ' ' + str(sum(values)))

if __name__ == '__main__':
    MatrixMultiplication.run()

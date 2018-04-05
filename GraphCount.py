from mrjob.job import MRJob, MRStep
from time import clock

class GraphCount(MRJob):
    def steps(self):
        return [
            MRStep(mapper=self.mapper, reducer=self.reducerMulti),
            MRStep(reducer=self.reducerAdd),
            MRStep(reducer=self.reducerGraph)
        ]

    def mapper(self, _, line):

        line = line.split()
        lineInt = []
        for entry in line:
            lineInt.append(int(entry))
        line = lineInt
        if len(line) >= 3:
            # Do mapping for first matrix
            line.append(1)
            yield (line[1], line)
            line.pop()
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
        total = sum(values)
        if total != 0:
            yield ('connectedNode', key)
            yield ('numberOfNodes', total)
            # print (str(key[0]) + ' ' + str(key[1]) + ' ' + str(total))

    def reducerGraph(self, key, values):
        if key == 'connectedNode':
            output = ['Connected Pairs:\n']
            for value in values:
                for entry in value:
                    output.append(str(entry) + ' ')
                output.append('\n')
            print(''.join(output))
        else:
            print('Number of Connected Node Pairs: ' + str(int(sum(values))))

if __name__ == '__main__':
    start = clock()
    GraphCount.run()
    end = clock()
    print ('\n' + 'Time: ' + str(end - start))

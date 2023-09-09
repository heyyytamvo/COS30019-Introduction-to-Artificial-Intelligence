from queue import Queue
import time

problem = [[], [], []]
first_line = input("Enter the first row: ")
problem[0] = [x for x in first_line.split()]
first_line = input("Enter the second row: ")
problem[1] = [x for x in first_line.split()]
first_line = input("Enter the third row: ")
problem[2] = [x for x in first_line.split()]


Xposi = []
print("The input puzzle is: ")
for i in range(3):
    for j in range(3):
        if (problem[i][j] == 'x'):
            Xposi.append(i)
            Xposi.append(j)
        print(problem[i][j], end=" ")
    print("")



def Checking(matrix):
    current = 1
    for i in range(3):
        for j in range(3):
            if (i == 2) and (j == 2) and (matrix[i][j] == 'x'):
                return True
            if (matrix[i][j] == str(current)):
                current += 1
                continue
            else:
                return False
            

def Swap(matrix, Xposi, newX, newY):
    result = []
    for i in range(3):
        temp = []
        for j in range(3):
            temp.append(matrix[i][j])
        result.append(temp)

    x = Xposi[0]
    y = Xposi[1]

    target = matrix[newX][newY]
    result[x][y] = target
    result[newX][newY] = 'x'

    return result


def printMatrix(matrix):
    for i in range(3):
        for j in range(3):
            print(matrix[i][j], end=" ")
        print("")



class Puzzle:
    def __init__(self, matrix, Xposi, reference):
        self.matrix = matrix
        self.Xposi = Xposi
        self.ref = reference

    def getReference(self):
        return self.ref

    def getXPosi(self):
        return self.Xposi
    
    def getMatrix(self):
        return self.matrix
    

dictReference = {}

# Function checking the valid move for the blank space
def ValidMove(x, y):
    return (x >= 0 and x < 3) and (y >= 0 and y < 3)

#up down left right
directionX = [0, 0, -1, 1]
directionY = [-1, 1, 0, 0]

def BFS_Puzzle(matrix, Xposi):
    waitingQueue = Queue()
    new = Puzzle(matrix, Xposi, None)
    visited = set()
    reference = 0
    waitingQueue.put(new)

    while (waitingQueue.empty() == False):
        current = waitingQueue.get()
        dictReference[reference] = current
        visited.add(str(current.getMatrix()))

        if (Checking(current.getMatrix())):
            return reference

        for i in range(4):
            newX = current.getXPosi()[0] + directionX[i]
            newY = current.getXPosi()[1] + directionY[i]

            if (ValidMove(newX, newY)):
                
                newMatrix = Swap(current.getMatrix(), current.getXPosi(), newX, newY)
                
                if str(newMatrix) not in visited:
                    visited.add(str(newMatrix))
                    newPuzzle = Puzzle(newMatrix, [newX, newY], reference)
                    waitingQueue.put(newPuzzle)
        reference += 1

key = BFS_Puzzle(problem, Xposi)
print("The key is:", key)
solution = []
while key != None:
    puzzle = dictReference[key]
    solution.append(puzzle.getMatrix())
    key = puzzle.getReference()

print("-------------------")
for i in range(len(solution) - 1, -1, -1):
    printMatrix(solution[i])
    time.sleep(0.5)
    print("-------------------")
    
print("Puzzle Solved")
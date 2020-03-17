import random

# n = no of numbers
def randomlist(n):
    List = []
    for i in range(n):
        List.append(random.randrange(1000))
    return List

if __name__ == "__main__":
    List = randomlist(10)
    print(List)
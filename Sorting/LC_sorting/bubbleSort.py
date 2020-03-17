from randomList import randomlist 

List = randomlist(20)
#print(List)

def bubble_sort(List):
    if(len(List)) <= 1:
        return List
    else:
        for i in range(0, len(List)-1):
            for j in range(0, len(List)-1):
                if List[j] > List[j+1]:
                    List[j], List[j+1] = List[j+1], List[j]
            #print("The ", i+1 , " times")
            #print(List)
        return List

if __name__ == "__main__":
    print(List)
    List = bubble_sort(List)
    print(List)
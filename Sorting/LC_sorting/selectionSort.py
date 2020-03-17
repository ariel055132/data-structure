from randomList import randomlist

List = randomlist(20)

def selection_sort(List):
    if (len(List)) <= 1:
        return List
    else:
        # for i in range(0, len(List)-1)
        for i in range(0, len(List)):
            if List[i] != min(List[i:]):
                min_index = List.index(min(List[i:]))
                List[i], List[min_index] = List[min_index], List[i]
        return List



if __name__ == "__main__":
    print(List)
    List = selection_sort(List)
    print(List)
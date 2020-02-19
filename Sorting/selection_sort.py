#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 19 12:01:37 2020
Selection sort implementation (out of space/extra space)
@author: cindy
"""

def Selection_Sort(array):
    sorted = []
    while(len(array) != 0):
        min_index = array.index(min(array))
        sorted.append(array[min_index])
        array.pop(min_index)
    print(sorted)


numbers = [41, 33, 17, 80, 61, 5, 55]
print(numbers)
Selection_Sort(numbers)

'''
PseudoCode:
Use extra space/array to store the sorted array
function sort(array)
    sorted = []
    while length of array > 0
        min = the smallest element in the array
        sorted.add(min)
    end while
array = sorted
end function
'''
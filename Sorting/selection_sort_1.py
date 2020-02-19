#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 19 15:47:30 2020
Selection sort implementation (in-space/no extra space)
@author: cindy
"""

def Selection_Sort(array):
    for i in range(0, len(array)-1):
        min_index = i
        for j in range(i+1, len(array)):
            if (array[min_index] > array[j]):
                min_index = j
        if (min_index != i):
            array[min_index], array[i] = array[i], array[min_index]
    
    
    
numbers = [41, 33, 17, 80, 61, 5, 55]
print(numbers)
Selection_Sort(numbers)
print(numbers)


'''
PseudoCode
function sort(list)
	for i = 0; i < list.length - 1; ++i
		minIndex = i;
		for j = i + 1; j < list.length; ++j
			if list[j] < list[minIndex]
				minIndex = j;
			end if
		end for
		if minIndex != i
			swap(list[minIndex], list[i]);
		end if
	end for
end function
'''
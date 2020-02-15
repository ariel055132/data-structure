#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Feb 15 15:58:39 2020
merge sort
@author: cindy
"""
def Merge_Sort(array):
    if len(array) <= 1:
        return
    else:
        # Start divide the array into halves
        mid = len(array) // 2  
        left_array = array[:mid]
        #print(left_array)
        right_array = array[mid:]
        #print(right_array)
        Merge_Sort(left_array)
        Merge_Sort(right_array)
        
        right_index = 0
        left_index = 0
        merge_index = 0
        
        while right_index < len(right_array) and left_index < len(left_array):
            if(right_array[right_index] < left_array[left_index]):
                array[merge_index] = right_array[right_index]
                right_index = right_index + 1
            else:
                array[merge_index] = left_array[left_index]
                left_index = left_index + 1
            merge_index = merge_index + 1
        
        while right_index < len(right_array):
            array[merge_index] = right_array[right_index]
            right_index = right_index + 1
            merge_index = merge_index + 1
        
        while left_index < len(left_array):
            array[merge_index] = left_array[left_index]
            left_index = left_index + 1
            merge_index = merge_index + 1
            
numbers = [41, 33, 17, 80, 61, 5, 55]
print(numbers)
Merge_Sort(numbers)
print(numbers)
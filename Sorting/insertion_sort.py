#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 19 16:23:43 2020
Insertion Sort implementation 
@author: cindy
"""

def Insertion_Sort(array):
    sorted = []
    for i in range(0, len(array)):
        tmp = array[i]
        j = i - 1
        while j >= 0 and tmp < array[j]:
            array[j+1] = array[j]
            j = j - 1 
        array[j+1] = tmp
        i = i + 1
    return array
        
        
    
numbers = [41, 33, 17, 80, 61, 5, 55]
print(numbers)
Insertion_Sort(numbers)
print(numbers)
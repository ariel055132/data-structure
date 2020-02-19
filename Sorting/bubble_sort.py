#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 19 11:26:48 2020
bubble sort implementation (not optimized)
@author: cindy
"""
def Bubble_Sort(array):
    for i in range(0, len(array)-1):
        for j in range(0, len(array)-1):
            if array[j] > array[j+1]:
                array[j], array[j+1] = array[j+1], array[j]
            

numbers = [41, 33, 17, 80, 61, 5, 55]
print(numbers)
Bubble_Sort(numbers)
print(numbers)

package test;

import java.util.Arrays;
import java.util.Random;
/*
 * Create array with 10 random numbers
 * Finding the largest and smallest elements in the array
 * Do some basic sorting algorithms to them
 */
public class ArrayIntro3 {

	public static void main(String[] args) {
		int[] nums = new int[10];
		for(int i = 0; i < nums.length; i++) {
			Random ran = new Random();
			nums[i] = ran.nextInt(100) + 1;
		}
		/*
		printArray(nums);
		int[] ans = findMaxMin(nums);
		System.out.println();
		System.out.println("Max value is " + ans[0]);
		System.out.println("Min value is " + ans[1]);
		bubbleSort(nums);
		Arrays.sort(nums);
		selectionSort(nums);
		printArray(nums);
		*/
	}
	
	// finding the maximum and minimum value in the array
	public static int[] findMaxMin(int[] array) {
		int[] ans = new int[2];
		int min = array[0];
		int max = array[0];
		for(int i = 0; i < array.length; i++) {
			if (array[i] > max) {
				max = array[i];
			}
			if (array[i] < min) {
				min = array[i];
			}
		}
		ans[0] = max;
		ans[1] = min;
		return ans;
	}
	// use a function to implement printing the array
	public static void printArray(int[] array) {
		for(int i = 0; i < array.length; i++) {
			System.out.print(array[i] + " ");
		}
	}
	// implementating bubble sort
	public static int[] bubbleSort(int[] array) {
		for(int i = 0; i < array.length - 1; i++) {
			for(int j = 0; j < array.length - 1; j++) {
				if(array[j] > array[j+1]) {
					int temp = array[j];
					array[j] = array[j+1];
					array[j+1] = temp;
				}
			}
		}
		return array;
	}
	// implementating selection sort
	public static int[] selectionSort(int[] array) {
		for(int i = 0, minIndex; i < array.length-1; i++) {
			minIndex = i;
			for(int j = i + 1; j < array.length; j++) {
				if(array[j] < array[minIndex]) {
					minIndex = j;
				}
			}
			if(minIndex != i) {
				int temp = array[minIndex];
				array[minIndex] = array[i]; 
				array[i] = temp;
			}
		}
		return array;
	}
}

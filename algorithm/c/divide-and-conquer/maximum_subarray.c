// https://www.geeksforgeeks.org/maximum-subarray-sum-using-divide-and-conquer-algorithm/
// 양의 정수와 음의 정수를 모두 포함할 수 있는 1차원 배열이 주어졌을 때 가장 큰 합을 갖는 연속된 하위 배열의 합을 찾습니다.

// 예를 들어, 주어진 배열이 {-2, -5, 6, -2, -3, 1, 5 , -6}인 경우 최대 하위 배열 합계는 7입니다(강조 표시된 요소 참조).

// 권장 사항: 솔루션으로 이동하기 전에 먼저 " PRACTICE "에서 해결하십시오. 
 
// 순진한 방법 은 두 개의 루프를 실행하는 것입니다. 
// 외부 루프는 시작 요소를 선택하고 내부 루프는 외부 루프에서 선택한 첫 번째 요소와 가능한 최대 합을 찾고 이 최대값을 전체 최대값과 비교합니다. 
// 마지막으로 전체 최대값을 반환합니다. Naive 방법의 시간 복잡도는 O(n^2)입니다.

// Divide and Conquer 접근법을 사용하여 O(nLogn) 시간에 최대 하위 배열 합계를 찾을 수 있습니다. 다음은 분할 정복 알고리즘입니다. 

// 주어진 배열을 두 개의 반으로 나눕니다.
// 다음 세 개의 최대값을 반환합니다.
// 왼쪽 절반의 최대 하위 배열 합계(재귀 호출 만들기)
// 오른쪽 절반의 최대 하위 배열 합계(재귀 호출 만들기)
// 부분배열이 중간점과 교차하는 최대 부분배열 합계
// 라인 2.a와 2.b는 단순 재귀 호출입니다. 하위 배열이 중간점을 가로지르는 최대 하위 배열 합계를 찾는 방법은 무엇입니까? 선형 시간에서 교차 합을 쉽게 찾을 수 있습니다. 
// 아이디어는 간단합니다. 중간 지점에서 시작하여 중간 왼쪽의 특정 지점에서 끝나는 최대 합을 찾은 다음 중간 + 1에서 시작하여 중간 + 1의 오른쪽 지점에서 끝나는 최대 합을 찾습니다. 
// 마지막으로 두 가지를 결합합니다. 왼쪽, 오른쪽 및 둘의 조합 중에서 최대값을 반환합니다.

// 다음은 위의 접근 방식을 구현한 것입니다. 

// 시간 복잡도: maxSubArraySum()은 재귀적 방법으로 시간 복잡도는 다음과 같은 재귀 관계로 표현될 수 있다. 
// T(n) = 2T(n/2) + Θ(n) 
// 위의 순환은 병합 정렬 과 유사하며 순환 트리 방법 또는 마스터 방법을 사용하여 해결할 수 있습니다. Master Method II의 경우에 해당하며, 반복해의 해가 Θ(nLogn)인 경우에 해당한다. 

// 이 문제에 대한 Kadane의 알고리즘 은 O(n) 시간이 걸립니다. 
// 따라서 Kadane의 알고리즘은 Divide and Conquer 접근 방식보다 우수하지만 이 문제는 Divide and Conquer의 위력을 보여주는 좋은 예라고 볼 수 있습니다. 
// 배열을 두 부분으로 나누는 위의 간단한 접근 방식은 시간 복잡도를 O(n^2)에서 O(nLogn)으로 줄입니다.

// A Divide and Conquer based program for maximum subarray
// sum problem
#include <limits.h>
#include <stdio.h>

// A utility function to find maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// A utility function to find maximum of three integers
int max_three(int a, int b, int c) { return max(max(a, b), c); }

// Find the maximum possible sum in arr[] auch that arr[m]
// is part of it
int maxCrossingSum(int arr[], int l, int m, int h)
{
	// Include elements on left of mid.
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = m; i >= l; i--) {
		sum = sum + arr[i];
		if (sum > left_sum)
			left_sum = sum;
	}

	// Include elements on right of mid
	sum = 0;
	int right_sum = INT_MIN;
	for (int i = m + 1; i <= h; i++) {
		sum = sum + arr[i];
		if (sum > right_sum)
			right_sum = sum;
	}

	// Return sum of elements on left and right of mid
	// returning only left_sum + right_sum will fail for
	// [-2, 1]
	return max_three(left_sum + right_sum, left_sum, right_sum);
}

// Returns sum of maximum sum subarray in aa[l..h]
int maxSubArraySum(int arr[], int l, int h)
{
	// Base Case: Only one element
	if (l == h)
		return arr[l];

	// Find middle point
	int m = (l + h) / 2;

	/* Return maximum of following three possible cases
			a) Maximum subarray sum in left half
			b) Maximum subarray sum in right half
			c) Maximum subarray sum such that the subarray
	crosses the midpoint */
	return max_three(maxSubArraySum(arr, l, m),
			maxSubArraySum(arr, m + 1, h),
			maxCrossingSum(arr, l, m, h));
}

/*Driver program to test maxSubArraySum*/
int main()
{
	int arr[] = { 2, 3, 4, 5, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int max_sum = maxSubArraySum(arr, 0, n - 1);
	printf("Maximum contiguous sum is %d\n", max_sum);
	getchar();
	return 0;
}

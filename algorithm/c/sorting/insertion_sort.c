# include <stdio.h>
# include <string.h>

# define MAX_SIZE 5

void insertion_sort(int* data, int n) {
    int i, j, key;
    for(i = 1; i < n; i++) {
        key = data[i];
        j = i-1;
        while(j >= 0 && key < data[j]) {
            data[j+1] = data[j];
            // memcpy(data+j+1, data+j, sizeof(*data) * (i-j));
            j = j - 1;
        }
        data[j+1] = key;
    }
}

// memcpy faster 25~30% above code
// memcpy(dest, src, num) 
// Wiki 에서는 memcpy 같은 경우, 자료를 당겨오기 때문에 역순으로 진행해야한다고 한다.
// 근데 역순으로 굳이 안 해도 잘만 된다...?
void insertion_sort_memcpy(int* data, int n) {
    int i, j, key;
    i = n-1;
    while( i-- > 0) {
        key = data[(j=i)];
        while(++j < n && key > data[j]);

        if (--j == i) continue;
        memcpy(data+i, data+i+1, sizeof(*data) * (j-i));
        data[j] = key;
    }
}

void main() {
    int i;
    int n = MAX_SIZE;
    int data[MAX_SIZE] = {7, 4, 3, 9, 6};

    insertion_sort(data, n);
    // insertion_sort_memcpy(data, n);

    for(i = 0; i < n; i++) {
        printf("%d\n", data[i]);
    }
}
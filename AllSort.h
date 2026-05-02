#ifndef ALL_SORT_H
#define ALL_SORT_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// 定义最大数据量，防止魔法数字
const int MAXN = 200005;

namespace AllSort {

    //1. 冒泡排序
    // 警告：处理 2e5 数据时，这个函数会非常慢（可能需要几十秒），建议只测小数据
    template <typename T>
    void bubble_sort(T a[], int arrlong) {
        for (int i = 1; i <= arrlong; i++) {
            for (int j = 1; j <= arrlong - i; j++) {
                if (a[j] > a[j + 1]) {
                    std::swap(a[j], a[j + 1]);
                }
            }
        }
    }
    template <typename T>
    void bubble_sort(std::vector<T>& vec) {
        bubble_sort(vec.data(), vec.size());
    }

    //2. 选择排序
    // 警告：同上，处理 2e5 数据极慢
    template <typename T>
    void Select_sort(T a[], int arrlong) {
        for (int i = 1; i < arrlong; i++) {
            int id = i;
            for (int j = i + 1; j <= arrlong; j++) {
                if (a[j] < a[id]) {
                    id = j;
                }
            }
            if (id != i) {
                std::swap(a[i], a[id]);
            }
        }
    }
    template <typename T>
    void Select_sort(std::vector<T>& vec) {
        Select_sort(vec.data(), vec.size());
    }

    //3. 计数排序
    // 注意：仅适用于数据值域在 [0, 200000] 范围内的整数
    template <typename T>
    void Count_Sort(T a[], int arrlong) {
        static int c[MAXN];
        static int b[MAXN];

        // 初始化计数数组（只清零用到的部分，加快速度）
        // 注意：这里假设数据是非负整数。如果有负数，此算法需修改偏移量
        for (int i = 0; i <= arrlong; ++i) c[i] = 0;

        for (int i = 1; i <= arrlong; i++) {
            if (a[i] >= 0 && a[i] < MAXN) {
                c[a[i]]++;
            }
        }
        int l = 0;
        // 遍历可能的数值范围
        for (int i = 0; i < MAXN; i++) {
            if (c[i]) {
                for (int j = 1; j <= c[i]; j++) {
                    b[++l] = i;
                }
                c[i] = 0; // 顺手清零
            }
        }
        for (int i = 1; i <= arrlong; i++) {
            a[i] = b[i];
        }
    }
    template <typename T>
    void Count_Sort(std::vector<T>& vec) {
        Count_Sort(vec.data(), vec.size());
    }

    //4. 插入排序
    // 警告：处理 2e5 数据较慢
    template <typename T>
    void Insert_Sort(T a[], int arrlong) {
        for (int i = 1; i <= arrlong; i++) {
            for (int j = i; j > 1; j--) {
                if (a[j] < a[j - 1]) {
                    std::swap(a[j], a[j - 1]);
                }
            }
        }
    }
    template <typename T>
    void Insert_Sort(std::vector<T>& vec) {
        Insert_Sort(vec.data(), vec.size());
    }

    //5. 快速排序 (主力推荐)
    // 适合 2e5 数据，速度快
    template <typename T>
    void Quicksort(T a[], int l, int r) {
        // 使用 static 大数组作为缓冲区，避免递归爆栈
        static int b[MAXN];
        static int c[MAXN];

        if (l >= r) return;

        // 随机化基准值
        srand(time(0));
        int x = a[l + rand() % (r - l + 1)];
        int l1 = 0, l2 = 0, y = 0;

        for (int i = l; i <= r; i++) {
            if (a[i] < x) {
                b[++l1] = a[i];
            }
            else {
                if (a[i] > x) {
                    c[++l2] = a[i];
                }
                else {
                    ++y;
                }
            }
        }
        int p = l;
        for (int i = 1; i <= l1; i++) a[p++] = b[i];
        for (int i = 1; i <= y; i++) a[p++] = x;
        for (int i = 1; i <= l2; i++) a[p++] = c[i];

        // 修正：补上第一个参数 a
        Quicksort(a, l, l + l1 - 1);
        Quicksort(a, l + l1 + y, r);
    }
    template <typename T>
    void Quicksort(std::vector<T>& vec) {
        Quicksort(vec.data(), 1, vec.size());
    }

    //6. 归并排序 (主力推荐)
    // 适合 2e5 数据，稳定且速度快
    template <typename T>
    void MergeSort(T a[], int l, int r) {
        static int c[MAXN]; // 辅助数组

        if (l == r) return;

        int m = (l + r) / 2;
        // 修正：补上第一个参数 a
        MergeSort(a, l, m);
        MergeSort(a, m + 1, r);

        int p1 = l, p2 = m + 1, tot = 0;
        while (p1 <= m && p2 <= r) {
            if (a[p1] <= a[p2]) {
                c[++tot] = a[p1++];
            }
            else {
                c[++tot] = a[p2++];
            }
        }
        while (p1 <= m) c[++tot] = a[p1++];
        while (p2 <= r) c[++tot] = a[p2++];

        for (int i = 1; i <= tot; i++) {
            a[i + l - 1] = c[i];
        }
    }
    template <typename T>
    void MergeSort(std::vector<T>& vec) {
        MergeSort(vec.data(), 1, vec.size());
    }
}

#endif
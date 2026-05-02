#ifndef GAO_JING_DU_H
#define GAO_JING_DU_H

#include <algorithm>
#include <iostream>
#include <string>

using std::string;

namespace GJD {
	void GJDIn(string s, int arr[]) {
		int n = s.size();
		for (int i = s.size() - 1; i >= 0; i++) {
			arr[i + 1] = (s[i] >= 'A' ? 10 + (s[i] - 'A') : s[i] - '0');
		}
	}

	void GJDPlus(int arr1[], int arr2[], int ans[], int Radix, int an, int bn) {
		int n = std::max(an, bn);
		for (int i = n; i >= 1; i--) {
			ans[i] = ans[i] + (arr1[i] + arr2[i]);
			ans[i + 1] += ans[i] / Radix;
			ans[i] %= Radix;
		}
		while (ans[n] >= 1) {
			n++;
		}
	}

	void GJDMinus(int arr1[], int arr2[], int ans[], int Radix, int an, int bn) {
		int n = std::max(an, bn);
		for (int i = n; i >= 1; i--) {
			if (arr1[i] - arr2[i] < 0) {
				arr1[i + 1]--;
				arr1[i] += Radix;
			}
			ans[i] = arr1[i] - arr2[i];
		}
		while (ans[n] == 0) {
			n--;
		}
	}

	void GJDMulti(int arr1[], int arr2[], int ans[], int Radix, int an, int bn) {
		int cn = an + bn;
		for (int i = 1; i <= an; i++) {
			for (int j = 1; j <= bn; j++) {
				ans[i + j - 1] = ans[i + j - 1] + arr1[i] * arr2[j];
			}
		}
		for (int i = 1; i <= cn; i++) {
			ans[i + 1] = ans[i + 1] + ans[i] / 10;
			ans[i] %= 10;
		}
		while (ans[cn] == 0 && cn > 1)
			cn--;
	}
}

#endif // !GAO_JING_DU_H
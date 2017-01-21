#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<queue>
#include<iostream>
using namespace std;
char G[101][101];
int check1[101];
int check2[101];
int cnt1 = -1, cnt2 = 0;
queue<char> q;
int cfg(int n) {
	if (cnt1 == cnt2) {
		return 0;
	}
	else {
		cnt1 = cnt2;
	}
	bool t = true;
	for (int i = 0; i < n; i++) {
		int len = strlen(G[i]);
		t = false;
		for (int j = 3; j < len; j++) {
			if (G[i][j] == '*' && check1[i] != 1) {
				check1[i] = 1;
				q.push(G[i][0]);
				cnt2++;
				t = false;
				break;
			}
			else if (G[i][j] > 91) {
				t = true;
				continue;
			}
			else if (G[i][j] < 91) {
				int s = q.size();
				if (s == 0) {
					t = false;
					break;
				}
				else {
					char temp;
					for (int k = 0; k < s; k++) {
						if (G[i][j] == q.front()) {
							t = true;
							break;
						}
						else {
							t = false;
						}
						temp = q.front();
						q.pop();
						q.push(temp);
					}
					if (!t)
						break;
				}
			}
		}
		if (t&&check1[i] != 1) {
			check1[i] = 1;
			q.push(G[i][0]);
			cnt2++;
		}
	}
	return cfg(n);
}

int visit(int n) {
	if (cnt1 == cnt2) {
		return 0;
	}
	else {
		cnt1 = cnt2;
	}
	if (cnt2 == 0) {
		check2[0] = 1;
		int pos = 0;
		while (G[pos][0] == 'S') {
			for (int i = 3; i < strlen(G[pos]); i++) {
				if (G[pos][i] < 91 && G[pos][i] != 'S' && check1[pos] == 1) {
					q.push(G[pos][i]);
					check2[pos] = 1;
				}
			}
			pos++;
		}
	}
	for (int i = 1; i < n; i++) {
		bool t = false;
		int len = strlen(G[i]);
		int s = q.size();
		if (check2[i] != 1) {
			for (int k = 0; k < s; k++) {
				if (G[i][0] == q.front() || G[i][0] == 'S') {
					t = true;
					for (int j = 3; j < len; j++) {
						if (G[i][j] < 91 && check1[i] == 1)
							q.push(G[i][j]);
					}
					break;
				}
				else
					t = false;
				char temp = q.front();
				q.pop();
				q.push(temp);
			}
		}
		if (t && (check2[i] != 1 && check1[i] == 1)) {
			cnt2++;
			check2[i] = 1;
		}
	}
	return visit(n);
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", G[i]);
	}
	cfg(N);
	int s = q.size();
	for (int i = 0; i < s; i++)
		q.pop();
	cnt1 = -1, cnt2 = 0;
	visit(N);
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (check1[i] == 1 && check2[i] == 1) {
			cnt++;
		}
	}
	printf("%d\n", cnt);
	for (int i = 0; i < N; i++) {
		if (check1[i] == 1 && check2[i] == 1) {
			printf("%s\n", G[i]);
		}
	}
	return 0;
}
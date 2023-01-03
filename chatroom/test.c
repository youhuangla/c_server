/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Tue Jan  3 12:21:12 2023
 ************************************************************************/

#include <stdio.h>
#include "../common/head.h"
#include "../common/common.h"
char ans[50] = {0};
int main() {
	get_value("./a.conf", "SERVERIP");
	printf("%s\n", ans);
	printf("%s\n", get_value("./a.conf", "SERVERIP"));	
	return 0;
}

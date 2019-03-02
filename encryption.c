#include <stdio.h>
#include <math.h>
int main(){
	char c;
		printf("Enter character: ");
		scanf("%c", &c);
		getchar();	
		int x, q=0, t, k, l, num = (char)c, num2=0, binaryTry[8], i=0, j=0, binaryNum[8];
		for(j=0; j<7; j++) binaryNum[j]=0;
		//printf("ASCII code: %d\n", num);
		while(num>0){
			binaryTry[i] = num%2;
			num = num/2;
			i++;
		}
		if(i<7){
			x=i;
			while(x<7){
				binaryTry[x] = 0;
				x++;
				i++;
			}
		}
		for(j=i-1; j>=0; j--){
			binaryNum[q] = binaryTry[j];
			q++;
		}
		/*printf("Binary code: ");
		for(j=0; j<i; j++) printf("%d", binaryNum[j]);
		printf("\n");*/
		for(j=0; j<i; j++) binaryNum[j] = 1 - binaryNum[j];
		/*printf("1st level encoding: ");
		for(j=0; j<i; j++) printf("%d", binaryNum[j]);
		printf("\n");*/
		k = binaryNum[0];
		binaryNum[0] = binaryNum[2];
		binaryNum[2] = k;
		k = binaryNum[3];
		l = binaryNum[4];
		binaryNum[3] = binaryNum[6];
		binaryNum[4] = binaryNum[5];
		binaryNum[5] = l;
		binaryNum[6] = k;
		/*printf("2nd level encoding: ");
		for(j=0; j<i; j++) printf("%d", binaryNum[j]);
		printf("\n");*/
		// performing XOR with 1010101
		int xorNum[7] = {1, 0, 1, 0, 1, 0, 1};
		for(j=0; j<i; j++){
			if(xorNum[j] == 1){
				if(binaryNum[j] == 1) binaryNum[j] = 0;
				else if(binaryNum[j] == 0) binaryNum[j] = 1;
			}
			else if(xorNum[j] == 0){
				if(binaryNum[j] == 1) binaryNum[j] = 1;
				else if(binaryNum[j] == 0) binaryNum[j] = 0;
			}
		}
		/*printf("3rd level encoding: ");
		for(j=0; j<i; j++) printf("%d", binaryNum[j]);
		printf("\n");*/
		t = i-1;
		for(j=0; j<i; j++){
			if(binaryNum[j] == 1) num2 += pow(2, 6-j);
		}
		//printf("num2 = %d\n", num2);		
		char ch = (int)num2;
		printf("Converted to: %c\n", ch);
}
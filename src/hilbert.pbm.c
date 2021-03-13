#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool isDiv (int n) {
	if (n==1|n==2|n==3|n==5|n==7|n==11|n==13|n==17|n==19) {
	return n==1;
	} else {
	return !((n%2)*(n%3)*(n%5)*(n%7)*(n%11)*(n%13)*(n%17)*(n%19));
	};
};

bool isPower(int n) {
    if(n == 0) {
        return 0;
    };
    while(n != 1) {
        if(n % 2 != 0) {
            return 0;
        };
        n = n>>1; 
    };
    return 1;
};

bool isPrime(int num) {
    if (num <= 3) {
        return num > 1;
    } else if (num % 2 == 0 || num % 3 == 0) {
        return 0;
    } else {
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return 0;
            }
        }
        return 1;
    }
}

void move(int j,int pos[], bool pix[], FILE* net){
pos[2]++;
pix[pos[0]+pos[1]*pos[3]] = isPrime(pos[2]);
if(j==1){
pos[1]-=1;
};
if(j==2){
pos[0]+=1;
};
if(j==3){
pos[1]+=1;
};
if(j==4){
pos[0]-=1;
};
};

void hilbert(int r, int d, int l, int u, int i, int pos[], bool pix[], FILE* net){
if(i>0){
i--;
hilbert(d,r,u,l,i,pos,pix,net);
move(r,pos,pix,net);

hilbert(r,d,l,u,i,pos,pix,net);
move(d,pos,pix,net);

hilbert(r,d,l,u,i,pos,pix,net);
move(l,pos,pix,net);

hilbert(u,l,d,r,i,pos,pix,net);
};
};

int main() {
FILE *net;
net = fopen("hilbert.64k", "a");
int n, pos[4];
n = 15;
pos[0] = 0;
pos[1] = 0;
pos[2] = 0;
pos[3] = 1<<n;
fprintf(net, "P1\n");
fprintf(net, "%d %d\n", pos[3], pos[3]);
bool *pix = malloc(pos[3]*pos[3]+1);
hilbert(2,3,4,1,n,pos,pix,net);
for (int i = 0; i < pos[3]*pos[3]; i++) {
putc(49-pix[i], net);
};
return 0;
}


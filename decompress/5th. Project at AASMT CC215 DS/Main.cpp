#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
#include<map>
#include<math.h>
#define COUNT 10

using namespace std;

struct tree
{
	char let;
	tree *left, *right;
};

struct Map
{
	char let;
	string bincod;
};

int mi = 0;
Map mapi[520];

int getthemap(){
		FILE *F1 = fopen("source.txt", "r+"), *F2 = fopen("bins.txt", "w+b");
		string xa;
		int d=150, da = 0;
		while (d != EOF){
			d = getc(F1);
				xa += (char)d;
				if ((char)d == '^'){
					d = getc(F1);
					if ((char)d == '_'){
						d = getc(F1);
						if ((char)d == '^'){
							while (d != EOF){
								da = 1;
								break;
							}
						}
					}
				if (da)
					break;
			}
		}
		int k = 0;
		for (int i = 0; i < xa.size(); i++){
			if (xa[i] == '^' && xa[i - 1] != '^'){
				for (int j = k; j <= i; j++){
					fprintf(F2, "%c", xa[j]);
					k++;
				}
				fprintf(F2, "\r\n");
			}
		}
		fclose(F2);
		FILE *F3 = fopen("bins.txt", "r+b");
		char arr[50];
		while (fgets(arr, 50, F3) != NULL){
			mapi[mi].let = arr[0];
			for (int v = 1; v < strlen(arr); v++){
				if (arr[v] == '^'){
					break;
				}
				mapi[mi].bincod += arr[v];
			}
			mi++;
		}
		int xp = ftell(F1);
		fclose(F1);
		fclose(F3);
		return xp;
	}


tree *maketree(tree*t){
	tree * itr;
	for (int i = 0; i < mi; i++){
		itr = t;
		for (int j = 0; j < mapi[i].bincod.size(); j++){
			if (mapi[i].bincod[j] == '0'){
				if (itr->left == NULL){
					tree* temp = (tree*)malloc(sizeof(tree));
					temp->let = '~';
					temp->left = temp->right = NULL;
					itr->left = temp;
					itr = itr->left;
				}
				else{
					itr = itr->left;
				}
			}
			if (mapi[i].bincod[j] == '1'){
				if (itr->right == NULL){
					tree* tempo = (tree*)malloc(sizeof(tree));
					tempo->let = '~';
					tempo->left = tempo->right = NULL;
					itr->right = tempo;
					itr = itr->right;
				}
				else{
					itr = itr->right;
				}
			}
		}
		itr->let = mapi[i].let;
	}
	return t;
}

void getthebins(int dd){
	FILE * FF = fopen("source.txt", "r+b"), *FW = fopen("BINSi.txt", "w+b");
	fseek(FF, dd, SEEK_SET);
	long d = getc(FF);
	while (d != EOF){
		char bin[50];
		itoa(d,bin, 2);
		if (getc(FF) == EOF){
			fprintf(FW, "%s", bin);
			//fprintf(FW, "\r\n");
		}
		else{
			fseek(FF, -1, SEEK_CUR);
			if (strlen(bin) < 8){
				int ssd = 8 - strlen(bin);
				for (int i = strlen(bin)-1; i >= 0; i--){
					bin[i + ssd] = bin[i];
					}
				for (int i = 0; i < ssd; i++){
					bin[i] = '0';
				}
				bin[8] = '\0';
				fprintf(FW, "%s", bin);
				//fprintf(FW,"\r\n");
			}
			else{
				fprintf(FW, "%s", bin);
				//fprintf(FW, "\r\n");
			}
		}
		d = getc(FF);
	}
	fclose(FF);
	fclose(FW);
}


int isLeaf(tree* ll){
	return !(ll->left) && !(ll->right);
}

void decomp(tree *t){
	FILE *FD = fopen("BINSi.txt", "r+b"),*DF = fopen("decomp.txt","w+");
	tree *itr = t;
	string decomp;
	long d = getc(FD);
	while (d != EOF){
		if (d == (int)'0'){
			itr = itr->left;
		}
		else{
			itr = itr->right;
		}
		if (itr == NULL){
			decomp += '\n';
			itr = t;
		}
		else if (itr->left==NULL && itr->right==NULL && itr != NULL){
			decomp += itr->let;
			itr = t;
		}
		d = getc(FD);
	}
	for (int i = 0; i < decomp.size(); i++){
		fprintf(DF, "%c", decomp[i]);
	}
	fclose(FD);
	fclose(DF);
}

void print2DUtil(tree*root, int space)
{
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->right, space);

	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%c\n",root->let);

	// Process left child
	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(tree *root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}


int main(){
	tree *ag = (tree*)malloc(sizeof(tree));
	ag->let = '~';
	ag->left = ag->right = NULL;;
	int dd = getthemap();
	ag = maketree(ag);
	//print2D(ag);
	getthebins(dd);
	decomp(ag);
	getch();
	remove("bins.txt");
	remove("BINSi.txt");
	return 0;
}
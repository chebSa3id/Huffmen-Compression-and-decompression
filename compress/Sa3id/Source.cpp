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

struct LL{
	char let;
	int frq;
	LL *next,*left,*right;
};

struct Map{
	char let;
	int frq;
	string bincod;
};

//GLOBAL VARS
FILE *F = fopen("source.txt", "w+");//1)used in getcodes,//make the table and start decompress max tommoro should be fineshed
string code = "";
int mi = 0;
Map mapi[520];



LL * infr(LL *head,char a){
	if(head==NULL){
		LL*head = (LL*)malloc(sizeof(LL));
		head->let=a;
		head->frq=1;
		head->next=head->left=head->right=NULL;
		mapi[mi].let = a;
		mapi[mi].frq = 1;
		mi++;
		return head;
	}
	LL*itr=head;
	while(itr!=NULL){
		if(itr->let==a){
			itr->frq=itr->frq+1;
			for (int i = 0; i < mi; i++){
				if (mapi[i].let == a){
					mapi[i].frq += 1;
				}
			}
			return head;
		}itr = itr->next;
	}
	LL* temp = (LL*)malloc(sizeof(LL));
		temp->let=a;
		temp->frq=1;
		temp->next=head;
		temp->left = NULL;
		temp->right = NULL;
		mapi[mi].let = a;
		mapi[mi].frq = 1;
		mi++;
		return temp;
}

void pr(LL *head){
    int i=1;
    LL *itr = head;
    while(itr != NULL){
		printf("Node %d : %c   %d\n",i,itr->let,itr->frq);
        itr=itr->next;
        i++;
    }
}
void swap( LL *a, LL *b)
{
    char temp = a->let;
    a->let = b->let;
    b->let = temp;

	int tempo = a->frq;
	a->frq = b->frq;
    b->frq = tempo;
	
	LL* tempi = a->left;
	a->left = b->left;
    b->left = tempi;	
	
	LL* tempn = a->right;
	a->right = b->right;
    b->right = tempn;
}
void bubbleSort(LL *start)
{
    int swapped, i;
    LL *ptr1=start;
    LL *lptr = NULL;

    if (ptr1 == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr)
		{
			if (ptr1->frq == ptr1->next->frq && (ptr1->left != NULL && ptr1->right != NULL)){
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
            if (ptr1->frq > ptr1->next->frq)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

LL*maketree(LL* head){
	LL*itr = head;
	while(itr->next!=NULL){
		bubbleSort(itr);
		LL*temp=(LL*)malloc(sizeof(LL));
		temp->let='~';
		temp->frq=(itr->frq)+(itr->next->frq);
		temp->next=itr->next->next;
		temp->left=itr;
		temp->right=itr->next;
		itr=temp;
	}
	return itr;
}


int isLeaf(LL* ll){
	return !(ll->left) && !(ll->right);
}

void printCodes(LL* root, string str)
{
	if (!root)
		return;
	if (root->let != '~')
	{
		fprintf(F, "%c", root->let);
		for (int i = 0; i < str.size(); i++){
			fprintf(F, "%c", str[i]);
		}
		for (int j = 0; j < mi; j++){
			if (mapi[j].let == root->let){
				mapi[j].bincod = str;
			}
		}
		fprintf(F, "^^");
	}
	printCodes(root->left, str + '0');
	printCodes(root->right, str + '1');
}

void makeabin(){
	FILE *F3 = fopen("given.txt", "r+b"), *F2 = fopen("Bins.txt", "w+b");
	if (F3 == NULL){ printf("FILE is not here.\n"); getch(); }
	int c = getc(F3);
	string bins;
	while (c != EOF){
		for (int i = 0; i < mi; i++){
			if (char(c) == mapi[i].let){
				bins += mapi[i].bincod;
			}
		}
		c = getc(F3);
	}
	for (int j = 0; j < bins.size(); j++){
		fprintf(F2, "%c", bins[j]);
	}
	fclose(F3);
	fclose(F2);
}

void comperss(){
	FILE *F1 = fopen("Bins.txt", "r+b"), *F2 = fopen("source.txt", "a+b");
	int d = getc(F1);
	int i = 0;
	char arr[9];
	while (d != EOF){
		arr[i] = d;
		i++;
		if (i == 8){
			long w = strtol(arr,0,2);
			printf("%c -> ", (char)w);
			fprintf(F2, "%c", (char)w);
			for (int j = 0; j < i; j++){
				printf("%c", arr[j]);
				arr[j] = 0;
			}
			i = 0; printf("\n");
		}
		d = getc(F1);
	}
	if (i != 0){
		long aw = strtol(arr, 0, 2);
		printf("%c -> ", (char)aw); 
		fprintf(F2, "%c", (char)aw);
		for (int j = 0; j < i; j++){
			printf("%c", arr[j]);
		}
	}
	fclose(F1);
	fclose(F2);
}

void finshing(){
char y[] = "^_^";
FILE *FW = fopen("source.txt", "r+");
fseek(FW, -2, SEEK_END);
int xo = ftell(FW);
fseek(FW, xo, SEEK_SET);//move to beginning of line
fprintf(FW, "%s", y);
fflush(FW);
fclose(FW);
}

void print2DUtil(LL*root, int space)
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
	printf("%d-%c\n", root->frq,root->let);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(LL *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

int main(){
	LL *ll = NULL;
	FILE *F1=fopen("given.txt","r");
	if (F1 == NULL){
		printf("The FILE not Found !"); getchar(); return 0;
	}
	int c = getc(F1);
	while(c != EOF){
		ll=infr(ll,c);
		c=getc(F1);
	}
	fclose(F1);
	if (ll->next == NULL){
		printf("No possible Compress.\n");
		getch();
		return 0;
	}
	ll=maketree(ll);
	printCodes(ll,code);
	fclose(F);
	finshing();
	makeabin();
	printf("\n");
	comperss();
	system("cls");
	for (int i = 0; i < mi; i++){
		printf("%c : %d  ->", mapi[i].let, mapi[i].frq);
		cout << mapi[i].bincod<<endl;
	}
	getchar();
	system("cls");
	//print2D(ll);
	getchar();
	remove("Bins.txt");
	return 0;
}
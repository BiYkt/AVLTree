# include<stdio.h>
# include<stdlib.h>

# define LH +1
# define EH 0
# define RH -1
 

typedef int RcdType;
typedef int Status;

typedef struct BBSTNode{
	RcdType data;
	int bf;
	struct BBSTNode *lchild, *rchild;
} BBSTNode,*BBSTree;

Status SearchBBSTree(BBSTree &T, RcdType e); //查找函数 
void R_Rotate(BBSTree &p); //右旋函数
void L_Rotate(BBSTree &p); //左旋函数 
void LeftBalance(BBSTree &T); //左平衡处理操作
void RightBalance(BBSTree &T); //右平衡处理操作
Status InsertAVL(BBSTree &T, RcdType e, int &taller); //平衡二叉树插入函数
Status DeleteBBSTree(BBSTree &T, RcdType e, int &shorter); //平衡二叉树删除函数 
void SplitBBST(BBSTree &T, RcdType key, BBSTree &T1, BBSTree &T2); //分裂平衡二叉树函数 
void Split(BBSTree T, RcdType key, BBSTree &T1, BBSTree &T2); // 分裂操作 
void PrintBBSTree(BBSTree &T , int lev); //凹入表输出函数 
void Page(); //主菜单输出函数 

int main(){
	BBSTree T;
	BBSTree T1 = NULL, T2 = NULL;
	Page();
	int i, j, k, s,key,taller,lev;
	int de, shorter;
	shorter = 0;
	taller = lev =  0;
	scanf("%d", &i);
	while(i != 0){
		switch(i){
			case 1:
				printf("请输入要插入的结点的值\n");
				scanf("%d", &j);
				InsertAVL(T, j, taller);
				printf("插入后平衡二叉树形状如下:\n");
				PrintBBSTree(T , lev);
				break;
			case 2:
				printf("请输入要查找的结点的值\n");
				scanf("%d", &k);
				s = SearchBBSTree(T, k);
				if(s == 1){
					printf("查找成功\n");
				}else{
					printf("查找失败\n");
				}
				break;
			case 3:
					printf("请输入要删除的结点的值\n");
					scanf("%d", &de);
					DeleteBBSTree(T, de, shorter);
					printf("删除后平衡二叉树形状如下:\n");
					PrintBBSTree(T , lev);
					break;	
			case 4: 
					printf("请输入分裂的关键字\n");
					scanf("%d", &key);
					SplitBBST(T, key, T1, T2);
					printf("分裂后T1的形状如下\n");
					PrintBBSTree(T1 , lev);
					printf("分裂后T2的形状如下\n");
					PrintBBSTree(T2 , lev);			
		}
		Page();
		scanf("%d",&i);
	}
}

void Page(){
	printf("=========================================================\n");
	printf("=      输入数字1来执行平衡二叉树的插入功能              =\n");
	printf("=      输入数字2来执行平衡二叉树的查找功能              =\n");
	printf("=      输入数字3来执行平衡二叉树的删除功能              =\n");
	printf("=      输入数字4来执行平衡二叉树的分裂功能              =\n");
	printf("=            输入数字0来退出此程序                      =\n");
	printf("=========================================================\n"); 
	 
}

//先输出右子树，再输出根节点，再输出左子树 
void PrintBBSTree(BBSTree &T, int lev){
	int i;
	if(T->rchild) PrintBBSTree(T->rchild, lev+1);
	for(i = 0; i<lev; i++) printf("  ");
	printf("%d\n",T->data);
	if(T->lchild) PrintBBSTree(T->lchild, lev+1);
}

Status SearchBBSTree(BBSTree &T, RcdType e){
	if(!T){
		return 0;
	}else if(e == T->data){
		return 1;
	}else if(e < T->data){
		return SearchBBSTree(T->lchild, e);
	}else{
		return SearchBBSTree(T->rchild, e);
	}
		
}

void R_Rotate(BBSTree &p){
	BBSTree lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

void L_Rotate(BBSTree &p){
	BBSTree rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

void LeftBalance(BBSTree &T){
	BBSTree lc, rd;
	lc = T->lchild;
	switch(lc->bf){
	case LH:
		T->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:
		rd = lc->lchild;
		switch(rd->bf){
			case LH: T->bf = RH; lc->bf = EH; break;
			case EH: T->bf = lc->bf = EH; break;
			case RH: T->bf = EH; lc->bf = LH; break;
		}
		rd->bf = EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
		break;
	}
}

void RightBalance(BBSTree &T){
	BBSTree rc,ld;
	rc = T->rchild;
	switch(rc->bf){
		case RH:
			T->bf = rc->bf = EH;
			L_Rotate(T);
			break;
		case LH:
			ld = rc->lchild;
			switch(ld->bf){
				case LH: T->bf = EH; rc->bf = RH; break;
				case EH: T->bf = rc->bf = EH; break;
				case RH: T->bf = LH; rc->bf = EH; break;
			}
			ld->bf = EH;
			R_Rotate(T->rchild);
			L_Rotate(T);
			break; 
	}	
}

Status InsertAVL(BBSTree &T, RcdType e, int &taller){
	if(NULL == T){
		T = (BBSTree)malloc(sizeof(BBSTNode));
		T->data = e;
		T->bf = EH;
		T->lchild = T->rchild = NULL;
		taller = 1;
	}else if(e == T->data){
		taller = 0;
		return 0;
	}else if(e < T->data){
		if(0 == InsertAVL(T->lchild, e, taller)) return 0;
		if(1 == taller){
			switch(T->bf){
				case LH: LeftBalance(T);
						 taller = 0;
						 break;
				case EH: T->bf = LH; 
						 taller = 1;
						 break;
				case RH: T->bf = EH;
						 taller = 0;
						 break;
			}
		}
	}else{
		if(0 == InsertAVL(T->rchild, e, taller)) return 0;
		if(1 == taller){
			switch(T->bf){
				case LH: T->bf = EH;
						 taller = 0;
						 break;
				case EH: T->bf = RH; 
						 taller = 1;
						 break;
				case RH: RightBalance(T);
						 taller = 0;
						 break;
			}
		}	
	}
}

Status DeleteBBSTree(BBSTree &T, RcdType e, int &shorter) {
    if (NULL == T) {
        return 0;
    } else if (T->data == e) {
        BBSTree p = NULL;
        if (NULL == T->lchild) {
            p = T;
            T = T->rchild;
            free(p);
            shorter = 1;
        } else if (T->rchild == NULL) {
            p = T;
            T = T->lchild;
            free(p);
            shorter = 1; 
        } else {
            p = T->lchild;
            //找到前驱结点 
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            T->data = p->data;
            // 在左子树中删除前驱结点
            DeleteBBSTree(T->lchild, p->data, shorter);
        }
    } else if (T->data > e) {
        if (DeleteBBSTree(T->lchild, e, shorter) == 0) {
            return 0;
        }
        if (shorter == 1) {
            switch (T->bf) {
                case LH: {
                    T->bf = EH;
                    shorter = 1;
                    break;
                } case EH: {
                    T->bf = RH;
                    shorter = 0;
                    break;
                } case RH: {
                    RightBalance(T);
                    if (T->rchild->bf == EH) {
                        shorter = 0;
                    } else {
                        shorter = 1;
                    }
                    break;
                }
            }
        }
    } else {
        if (DeleteBBSTree(T->rchild, e, shorter) == 0) {
            return 0;
        }
        if (shorter == 1) {
            switch (T->bf) {
                case LH: {
                    LeftBalance(T);
                    if (T->lchild->bf == EH) {
                        shorter = 0;
                    } else {
                        shorter = 1;
                    }
                    break;
                } case EH: {
                    T->bf = LH;
                    shorter = 0;
                    break;
                } case RH: {
                    T->bf = EH;
                    shorter = 1;
                    break;
                }
            }
        }
    }
    return 1;
}

void Split(BBSTree T, RcdType key, BBSTree &T1, BBSTree &T2){
	int taller = 0;
	if(T!=NULL){
		Split(T->lchild, key, T1, T2);		
		if(T->data > key){
			InsertAVL(T1, T->data, taller);
		}else{
			InsertAVL(T2, T->data, taller);
		}
		Split(T->rchild, key, T1, T2);
	}	
}

void SplitBBST(BBSTree &T, RcdType key, BBSTree &T1, BBSTree &T2){	
	BBSTree t1 = NULL, t2 = NULL;
	Split(T, key, t1, t2);
	T1 = t1;
	T2 = t2;
}

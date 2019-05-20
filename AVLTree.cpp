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

Status SearchBBSTree(BBSTree &T, RcdType e); //���Һ��� 
void R_Rotate(BBSTree &p); //��������
void L_Rotate(BBSTree &p); //�������� 
void LeftBalance(BBSTree &T); //��ƽ�⴦�����
void RightBalance(BBSTree &T); //��ƽ�⴦�����
Status InsertAVL(BBSTree &T, RcdType e, int &taller); //ƽ����������뺯��
Status DeleteBBSTree(BBSTree &T, RcdType e, int &shorter); //ƽ�������ɾ������ 
void SplitBBST(BBSTree &T, RcdType key, BBSTree &T1, BBSTree &T2); //����ƽ����������� 
void Split(BBSTree T, RcdType key, BBSTree &T1, BBSTree &T2); // ���Ѳ��� 
void PrintBBSTree(BBSTree &T , int lev); //������������ 
void Page(); //���˵�������� 

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
				printf("������Ҫ����Ľ���ֵ\n");
				scanf("%d", &j);
				InsertAVL(T, j, taller);
				printf("�����ƽ���������״����:\n");
				PrintBBSTree(T , lev);
				break;
			case 2:
				printf("������Ҫ���ҵĽ���ֵ\n");
				scanf("%d", &k);
				s = SearchBBSTree(T, k);
				if(s == 1){
					printf("���ҳɹ�\n");
				}else{
					printf("����ʧ��\n");
				}
				break;
			case 3:
					printf("������Ҫɾ���Ľ���ֵ\n");
					scanf("%d", &de);
					DeleteBBSTree(T, de, shorter);
					printf("ɾ����ƽ���������״����:\n");
					PrintBBSTree(T , lev);
					break;	
			case 4: 
					printf("��������ѵĹؼ���\n");
					scanf("%d", &key);
					SplitBBST(T, key, T1, T2);
					printf("���Ѻ�T1����״����\n");
					PrintBBSTree(T1 , lev);
					printf("���Ѻ�T2����״����\n");
					PrintBBSTree(T2 , lev);			
		}
		Page();
		scanf("%d",&i);
	}
}

void Page(){
	printf("=========================================================\n");
	printf("=      ��������1��ִ��ƽ��������Ĳ��빦��              =\n");
	printf("=      ��������2��ִ��ƽ��������Ĳ��ҹ���              =\n");
	printf("=      ��������3��ִ��ƽ���������ɾ������              =\n");
	printf("=      ��������4��ִ��ƽ��������ķ��ѹ���              =\n");
	printf("=            ��������0���˳��˳���                      =\n");
	printf("=========================================================\n"); 
	 
}

//���������������������ڵ㣬����������� 
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
            //�ҵ�ǰ����� 
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            T->data = p->data;
            // ����������ɾ��ǰ�����
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

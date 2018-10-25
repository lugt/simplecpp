#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct stvector
{
	unsigned int mem_len;/*申请的内存长度，单位字节*/
	unsigned int user_len;/*已经使用的内存长度，单位字节*/
	unsigned int ele_num;/*当前元素个数*/
	unsigned int type_len;/*存放数据类型的长度，单位字节*/
	char* head;/*数据头指针*/
	char* end;/*数据尾指针*/	
}vector;
 
/*
*函数功能:创建vector *函数参数: *       len: 初次开辟的元素个数*/
#define create_vector(vem, tyoom, len) \
	if(len >=0)\
		{\
	        vem = (vector*) malloc(sizeof(vector));	\
		vem->type_len = sizeof(tyoom);\
		vem->ele_num = 0;\
		vem->user_len = 0;\
		vem->mem_len = (len*sizeof(tyoom)*2);\
		char* vec_creat_ptr1 = (char*)malloc(vem->mem_len);\
		vem->head = vec_creat_ptr1;\
		vem->end = vec_creat_ptr1;\
	}

/*
*函数功能:测试容器是不是已经占满内存
*函数参数:
*       vec: vec结构指针
*/
int isfull(vector* vec)
{
	int ret = -1;
	if((vec->mem_len-vec->user_len)<=(2*vec->type_len)){
		ret = 0;
		}
	return ret;
}
/*
*函数功能:重新开辟更大的空间来存放元素
*函数参数:
*       vec: vec结构指针
*/
int resize(vector* vec)
{
  int * op = new int[100];
  op[101] = 10;
  //        int ret = -1;
	char* ptr  = (char *)malloc(2*vec->mem_len);
	if(ptr!=NULL){
		memcpy(ptr,vec->head,vec->user_len);
		free(vec->head);
		vec->head = ptr;
		vec->end = vec->head+vec->user_len;
		vec->mem_len = 2*vec->mem_len;
		//		ret = 0;
	}
	return 0;
}
/*
*函数功能:在容器尾部添加元素
*函数参数:
*       vec: vec结构指针
*       value:所要添加元素，务必要保证元素类型一致
*/
#define push_back(vex,value)({\
	int vec_psbk_ret = -1;\
	if(vex!=NULL){\
		if(isfull(vex) ==0){\
			resize(vex);\
		}\
		memcpy(vex->end,(void*)&value,vex->type_len);	\
		vex->end = (char *) ((char *) vex->end + (int) vex->type_len);	\
		vex->user_len += vex->type_len;\
		vex->ele_num++;\
		vec_psbk_ret = 0;\
		}\
	vec_psbk_ret;\
})
/*
*函数功能:删除容器尾部的元素
*函数参数:
*       vec: vec结构指针
*       type:传入的存放数据的类型
*/
#define pop_back(vecx,tp)({\
	int vec_ppbk_ret = -1;\
	if(vecx->ele_num!=0){\
		vecx->end -= vecx->type_len;\
		vecx->user_len -= vecx->type_len;\
		vecx->ele_num--;\
		vec_ppbk_ret = 0;\
	}\
	vec_ppbk_ret;\
})
/*
*函数功能:定位位置为i的元素值
*函数参数:
*       vec: vec结构指针
*       type:传入的存放数据的类型
*       i: 在容器中的位置，注意位置是从0开始的
*/
#define at(vex,tp,i) ({\
	tp vec_at_ret;\
	if((i)<vex->ele_num && (i)>=0){\
		char* vec_at_ptr = vex->end - vex->type_len;\
		vec_at_ret = *(tp*)vec_at_ptr;\
	}else{\
	  vec_at_ret = NULL;\
	}\
	vec_at_ret;\
})
/*
*函数功能:在位置i处插入元素
*函数参数:
*       vec: vec结构指针
*       i:在容器中的位置，注意位置是从0开始的
*       value: 插入的元素
*/
#define insert(vex,i,value)({\
	int vec_inst_ret = -1;\
	if(isfull(vex) == 0){\
		resize(vex);\
	}\
	if((i)<=vex->ele_num && (i)>=0){\
	  char* vec_inst_ptr1 = vex->end + vex->type_len;	\
		char* vec_inst_ptr2 = vex->end; \
		int vec_inst_num = vex->ele_num - (i) -1;\
		char* vec_inst_ptr3 = vex->head + ((i)*vex->type_len);	\
		while(vec_inst_num--){\
			memcpy(vec_inst_ptr1,vec_inst_ptr2,vex->type_len);\
			vec_inst_ptr1 -= vex->type_len;\
			vec_inst_ptr2 -= vex->type_len;\
		}\
		memcpy(vec_inst_ptr3, (void*) &value, vex->type_len);\
		vex->user_len += vex->type_len;\
		vex->end += vex->type_len;\
		vex->ele_num++;\
		vec_inst_ret = 0;\
	}\
	vec_inst_ret;\
})
/*
*函数功能:在位置i处删除元素
*函数参数:
*       vec: vec结构指针
*       i:删除元素在容器中的位置
*/
#define erase(vex,i)({\
	int vec_erase_ret = -1;\
	if(vex->ele_num != 0){\
		if((i)>=0 && (i)<vex->ele_num){\
			char* vec_erase_ptr1 = vex->head + (vex->type_len*(i));\
			char* vec_erase_ptr2 = vec_erase_ptr1 + vex->type_len;\
			int vec_erase_num = vex->ele_num+(i)+1;\
			while(vec_erase_num--){\
				memcpy(vec_erase_ptr1,vec_erase_ptr2,vex->type_len);\
				vec_erase_ptr1 +=vex->type_len;\
				vec_erase_ptr2 +=vex->type_len;\
			}\
			vex->ele_num--;\
			vex->user_len -= vex->type_len;\
			vex->end -= vex->type_len;\
		}\
	}\
	vec_erase_ret;\
})
/*
*函数功能:返回容器当前第一个元素的值
*函数参数:
*       vec: vec结构指针
*       type:传入的存放数据的类型
* 返回值:该类型的元素
*/
#define front(vec,type)({\
 	type vec_front_ret;\
 	if(vec->ele_num != 0){\
		vec_front_ret = at(vec, type, 0);\
        }else{\
                vec_front_ret = NULL;\
        }\
 	vec_front_ret;\
})
/*
*函数功能:返回容器尾部的元素
*函数参数:
*       vec: vec结构指针
*       type:传入的存放数据的类型
* 返回值:该类型的元素
*/
#define back(vec,type)({\
	type vec_back_ret;\
	if(vec->ele_num !=0){\
		vec_back_ret = at(vec,type,(vec->ele_num-1));\
	}\
	vec_back_ret;\
})
/*
*函数功能:返回容器内申请的最大元素个数
*函数参数:
*       vec: vec结构指针
*/
int capacity(vector* vec)
{
	int ret = 0;
	if(vec != NULL)
	ret = vec->mem_len/vec->type_len;
	return ret;
}
/*
*函数功能:返回当前容器内元素个数
*函数参数:
*       vec: vec结构指针
*/
int size(vector* vec)
{
	int ret = 0;
	if(vec != NULL)
          ret = vec->user_len / vec->type_len;
	return ret;
}
/*
*函数功能:清除vector中所有元素
*函数参数:
*       vec: vec结构指针
*/
int clear(vector* vec)
{
	int ret = -1;
	if(vec !=NULL)
		{
		free(vec->head);
		vec->ele_num = 0;
		vec->end = vec->head;
		vec->user_len = 0;		
	}
	return ret;
}
/*
*函数功能:返回迭代容器首位置
*函数参数:
*       vec: vec结构指针
*/
int begin(vector* vec)
{
  return 0;
}
  
int end(vector* vec)
{
    return (vec->ele_num-1);
}

int pos;
char *treedata;
int n;

struct treenode{
    char data;
    treenode **child;
    treenode(){
        child=new treenode*[n];
    }
};

treenode *creat_tree()
{
    if(pos>=strlen(treedata))
        return NULL;
    char ch=treedata[pos];
    pos+=2;
    if(ch=='0')
        return NULL;

    treenode *node=new treenode();
    node->data=ch;

    for(int i=0;i<n;i++)
        node->child[i]=creat_tree();

    return node;
}

struct btreenode{
    char data;
    char str[501];
    btreenode *left;
    btreenode *right;
    btreenode():
      left(NULL),right(NULL)
  {}
};

typedef btreenode* bnode;

vector *ye;

btreenode* TreeToBinaryTree(treenode *treeRoot)
{
    if (!treeRoot)
        return NULL;

    btreenode* binaryRoot = new btreenode();
    binaryRoot->data=treeRoot->data;
    int i;
    for(i=0;i<n;i++){
        binaryRoot->left=TreeToBinaryTree(treeRoot->child[i]);
        if(binaryRoot->left)
            break;
    }

    btreenode *brotherChild = binaryRoot->left;

    if(brotherChild){
        for(int j=i+1;j<n;j++){
            brotherChild->right=TreeToBinaryTree(treeRoot->child[j]);
            if(!brotherChild->right){
                if(j<n-1)
                    continue;
            }
            brotherChild=brotherChild->right;
        }
        if(brotherChild)
            brotherChild->right=NULL;
    }
    return binaryRoot;
}


void get_huffman_code(btreenode* &node){
    if(!node)
        return ;
    btreenode* p=node;
    vector *qcp;
    create_vector(qcp, bnode, 1);
    vector *q = qcp;
    erase(q, 0);
    insert(q, 0, p);
    while(size(q) > 0){
        p=front(q, bnode);
        pop_back(q, bnode);
        if(p->left){
	  push_back(q, p->left);
          strcpy(p->left->str,p->str);
	  char* ptr=p->left->str;
          while(*ptr!='\0')
                ptr++;

            *ptr='0';
            ptr++;
            *ptr='\0';
        }
        if(p->right){
	  push_back(q, p->right);
          strcpy(p->right->str,p->str);
          char *ptr=p->right->str;
          while(*ptr!='\0')
                ptr++;

            *ptr='1';
            ptr++;
            *ptr='\0';
        }
    }
}

void getcode(btreenode* root){
    if(!root->left && !root->right)
      push_back(ye,root);

    if(root->left)
        getcode(root->left);

    if(root->right)
        getcode(root->right);

    return ;
}

int main()
{
    int t;
    create_vector(ye, bnode, 1);
    scanf("%d%d", &t, &n);
    getchar();
    treenode **root=new treenode*[t];
    for(int i=0;i<t;i++){
        pos=0;
	treedata = new char[501];
	scanf("%s", treedata);
	if(!treedata) {
	  return 1;
	}
        root[i]=creat_tree();
    }


    btreenode **b=new btreenode*[t];

    for(int i=0;i<t;i++)
        b[i]=TreeToBinaryTree(root[i]);

    btreenode *btree=b[0];
    for(int i=0;i<t-1;i++)
        b[i]->right=b[i+1];

    b[t-1]->right=NULL;

    btree->str[0]='\0';

    get_huffman_code(btree);
    getcode(btree);

    for(int i=0;i<size(ye);i++){
      for(int j=0;j<strlen(at(ye,bnode,i)->str);j++){
	printf("%s", at(ye,bnode,i)->str[j]);
	if(j!=strlen(at(ye,bnode,i)->str)-1)
	      putchar(' ');
	      //cout<<" ";
            else
	      putchar('\n');
	    //  cout<<endl;
        }
    }

    return 0;
}

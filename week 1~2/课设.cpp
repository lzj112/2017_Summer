/*************************************************************************
学生管理系统 
    
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 20
#define l sizeof(data)
#define l2 sizeof(mima)

typedef struct data   		//学生信息 
{
    char Name[MAX_LEN];
    int Number;
    int score;
    struct data *next;
}data;

typedef struct mima 		//注册信息 
{
    char  name[10];
    char passwd[20];
    struct mima *next;
}mima;

data *init ()  //创建头 
{
    data *head;
    head=(data *)malloc(l);
    head->next=NULL;
    return head;
}

void insert(data *head) 	//插入学生信息 
{
    data *p1,*p2;
    p1=(data *)malloc(l);
    scanf("%s %d %d",p1->Name,&p1->Number,&p1->score);
    while(p1->Name[0]!='#')
    {
        p1->next=head->next;
        head->next=p1;
        p1=(data *)malloc(l);
        scanf("%s %d %d",p1->Name,&p1->Number,&p1->score);
    }
}

void change(data *head,int num)			//修改学生信息 
{
	data *p,*p1;
    p=head;
    int flag=1;
   
        p1=head->next;
        while(p1)
        {
            if(p1->Number ==num)
             break;
            p=p->next;
            p1=p1->next;
        }
        if(p1==NULL)
        printf("查无此人！，请检查输入信息。");
        else 
        {
        	printf("请重新输入该学生的姓名 学好 成绩信息：\n");
        	scanf("%s %d %d",p1->Name ,&p1->Number ,&p1->score );
			printf("修改成功\n");
		}
		
}


void del(data *head) 		//删除学生信息 
{
    data *p,*p1;
    p=head;
    int num;
    int flag=1;
   
        printf("请输入要删除的学生的学号：");
        scanf("%d",&num);
        p1=head->next;
        while(p1)
        {
            if(p1->Number ==num)
             break;
            p=p->next;
            p1=p1->next;
        }
        if(p1==NULL)
        printf("查无此人！，请检查输入信息。");
        else 
        p->next=p1->next;
}


void displayall(data *head)			//显示全部学生信息 
{
    data *p;
    p=head->next;
    while(p)
    {
        printf("%s %d %d\n",p->Name,p->Number,p->score);
        p=p->next;

    }
    printf("\n");
}


void sort(data *head)			//排序 
{
    data *end,*p,*p1,*p2;
    for(end=NULL;end!=head;end=p)
    for(p=p1=head;p1->next->next !=NULL;p1=p1->next)
    {
        if(p1->next->score < p1->next->next->score)
        {
            p2=p1->next->next;
            p1->next->next=p2->next;
            p2->next=p1->next;
            p1->next=p2;
            p=p1->next->next;
        }
    }
}


void displayone(data *head,int num)			//显示one学生信息 
{
    data *p;
    p=head->next;
    int flag=0;
    while(p)
    {
        if(p->Number ==num)
        {
        	flag=1;
			printf("%s %d %d\n",p->Name,p->Number,p->score);
			break;
		}
        p=p->next;

    }
    if(flag==0)
    printf("查无此人!");
    printf("\n");
}

void read(data *head)				//从文件读取学生信息到链表 
{
	FILE *fp;
	fp=fopen("student.txt","rt");
	if(fp==NULL)
	{
		printf("read error");
		exit(0);
	}
	data *p1,*p2,*p3;
    p3=head;
	p2=p1=(data *)malloc(l);
	head->next = p1;
	while(fscanf(fp,"%s %d %d",p1->Name ,&p1->Number ,&p1->score )!=EOF)
	{
		p1=(data *)malloc(l);
		p2->next = p1;
		p2=p1;
        p3=p3->next;
	}
    p3->next=NULL;
    fclose(fp);
}

void save(data *head)           //保存学生信息到文件
{
    FILE *fp;
	fp=fopen("student.txt","w+");
    if(fp==NULL)
    {
        printf("save error");
        exit(0);
    }
    data *p=head->next;
	while(p)
    {
        fprintf(fp,"%s %d %d\n",p->Name,p->Number,p->score);
        p=p->next;
    }
    fclose(fp);
}

void sign_in(mima *head)          //注册账号密码
{
    FILE *fp;
    fp=fopen("denglu.txt","a");
    if(fp==NULL)
    {
        printf("error!");
        exit(0);
    }
    mima *p,*p2,*p3;
    int flag;
    p2=(mima *)malloc(l2);
    p=(mima *)malloc(l2);
    while(1)
    {
    	flag=0;
    	p3=head;
    	printf("\n请输入账号(由数字组成)：");
    	scanf("%s",p->name);
    	while(p3)
    	{
    		if(strcmp(p3->name ,p->name )==0)
    		{
    			printf("账号已存在，重新输入\n");
    			flag=1;
    			break;
			}
			p3=p3->next ;
		}
		if(flag==0)
		break;
	}
    while(1)
    {
    	printf("\n请输入密码：");
	scanf("%s",p->passwd);
    	printf("\n请确认密码：");
    scanf("%s",p2->passwd);
     if(strcmp(p->passwd ,p2->passwd )==0)
     break;
     else
     printf("两次密码不同，请重新输入密码。");
	}
    
    fprintf(fp,"%s %s\n",p->name,p->passwd);
    printf("\n注册成功！\n");
    fclose(fp);
}
void daoru(mima *head) 				//从文件导入注册信息到链表 
{


	FILE *fp;
	fp=fopen("denglu.txt","r");
	if(fp==NULL)
	{
		printf("daoru error");
		exit(0);
	}
	mima *p1,*p2,*p3;
    p3=head;
	p2=p1=(mima *)malloc(l2);
	head->next = p1;
	int i=0;
	while(fscanf(fp,"%s %s",p1->name ,p1->passwd)!=EOF)
	{
		p1=(mima *)malloc(l2);
		p2->next = p1;
		p2=p1;
        p3=p3->next;
	}
    p3->next=NULL;
    fclose(fp);

}

int log_in(mima *head)             //登录账号
{
    int t;
	printf("\n1.教师登陆\n2.学生登陆\n"); 
	scanf("%d",&t);
	while(t!=1&&t!=2)
	{
		printf("\n错误，重新选择\n");
		scanf("%d",&t);
	}
    mima *p1,*p;
    p1=head;
    p=(mima *)malloc(l2);
    int flag;
    printf("请输入账号：");
    scanf("%s",p->name);
    getchar();
    printf("\n请输入密码：");
   scanf("%s",p->passwd);
    while(p1)
    {
    	if(strcmp(p->name ,p1->name )==0&&strcmp(p->passwd ,p1->passwd )==0)
    	{
    		flag=1;
		}
		p1=p1->next ;
	}
	if(flag==0)
	{
		printf("\n账号或密码错误！\n");
		return 0;
	}
	else 
	{
		printf("\n登陆成功\n");
    }
    if(t==1)
    return 1;
    if(t==2)
    return 2;
}

void xiugai(mima *head)                    //忘记密码 
{
	FILE *fp;
	fp=fopen("denglu.txt","w");
	if(fp==NULL)
	{
		printf("xiugai error");
		return ;
	}
	mima *p,*p1,*p2;
	p1=(mima *)malloc(l2);
	int flag=0;
	while(1)
	{
        p=p2=head->next;
	printf("\n请输入账号：");
	scanf("%s",p1->name );		
	while(p2)
	{
		
		if(strcmp(p1->name ,p2->name )==0)
		{
			flag=1;
			break;
		}
		p2=p2->next ;
	}
	if(flag==0)
	printf("\n该账号不存在\n");
	else
	break;
	}
	while(1)
	{
		printf("\n请输入新密码：");
		scanf("%s",p1->passwd );
		printf("\n请确认密码：");
		scanf("%s",p2->passwd );
        if(strcmp(p1->passwd,p2->passwd)==0)
		{
			
			while(p)
			{
				
				fprintf(fp,"%s %s\n",p->name ,p->passwd );
				p=p->next ;
			}
            fclose(fp);
			return ;
		}
		else 
		printf("\n两次密码不同\n");
	}
}

void avg(data *head)          //求平均值
{
	data *p;
	p=head->next ;
	float i=0.0;
	int sum=0;
	float aver;
	while(p)
	{
		i++;
		sum+=p->score ;
		p=p->next ;
	}
	sum=sum*1.0;
	aver=sum/i;
	printf("\n平均分为：%.2f\n",aver);
}

void all(data *head)
{
	data *p=head->next ;
	int i=0;
	while(p)
	{
		i++;
		p=p->next ;
	}
	printf("\n---------------系统内学生数量为%d人------------------\n",i);
}

void fail(data *head)
{
	data *p;
	int i,choose;
	while(1)
	{
		p=head->next;
		i=0,choose=0;
		printf("\n1.查看不及格人数；");
		printf("\n2.查看不及格学生信息；");
		printf("\n3.查看不及格率；");
		printf("\n4.按0返回主菜单.\n");
		while(1)
		{
			scanf("%d",&choose);
			if(choose>=0&&choose<4)
			break;
			else
			printf("\n输入错误选项，请重新输入;\n");
		}
		if(choose==1)
		{
			while(p)
			{
				if(p->score <60)
				i++;
				p=p->next;
			}
			printf("\n不及格人数为%d\n",i);
		}
		if(choose==2)
		{
			while(p)
			{
				if(p->score <60)
				printf("\n%s %d %d",p->Name ,p->Number ,p->score );
				p=p->next ;
			}
		 } 
		 if(choose==3)
		 {
		 	float i=0;
		 	float a=0;
		 	float fai;
		 	while(p)
		 	{
		 		i++;
		 		if(p->score <60)
		 		a++;
		 		p=p->next ;
			 }
			 fai=a/i;
			 printf("\n不及格率为%.2f\n",fai);
		 }
		 if(choose==0)
		 return ;
			
	}	
}

int menu(data *head)		//菜单 
{
	all(head);
	printf("###########################################################\n");
    printf("	欢迎使用该系统  \n");
    printf("\t1.插入学生信息;\n");
    printf("\t2.删除学生信息; \n");
    printf("\t3.按成绩为学生排序; \n");
    printf("\t4.输出全部学生信息; \n");
    printf("\t5.输出单个学生信息; \n");
    printf("\t6.修改学生信息； \n");
    printf("\t7.查看平均分；\n");
    printf("\t8.查看不及格的信息；\n");
    printf("\t9.保存学生信息;\n");
    printf(" 请按数字键进行操作,按0推出系统 \n");
    printf("###########################################################\n");
    int choose;
    scanf("%d",&choose);
    while(choose>9||choose<0)
    {
     
   	 printf("输入错误选项，请重新输入：");
     scanf("%d",&choose);
	}
    return choose;
}

int menu2(data *head)		//菜单 
{
	all(head);
	printf("###########################################################\n");
    printf("	欢迎使用该系统  \n");
    printf("\t1.查询信息; \n");
    printf("\t2.查看平均分；\n");
    printf(" 按0推出系统 \n");
    printf("###########################################################\n");
    int choose;
    scanf("%d",&choose);
    while(choose>2||choose<0)
    {
     
   	 printf("输入错误选项，请重新输入：");
     scanf("%d",&choose);
	}
    return choose;
}

int main()
{
    int choose,a,b;
    data *head;
    head = init();
    read(head);
    if(head == NULL)
    {
        printf("系统错误！");
        return -1;
    }
	mima *head2=(mima *)malloc(l2);
	while(1)
	{
		daoru(head2);
		printf("\n1.登陆 \n2.无账号，注册\n3.忘记密码\n");
		scanf("%d",&a);
		while(a!=1&&a!=2&&a!=3)
		{
			printf("输入错误,请重新输入\n");
			scanf("%d",&a);
		}
		if(a==1)
		{
			b=log_in(head2);
		}
		if(a==2)
		{
			sign_in(head2);
		}
		if(a==3)
		{
			xiugai(head2);
		}
		if(b==1||b==2)
		break;
	}
	if(b==1)
    while(choose = menu(head))
    {
        switch(choose)
        {
            case 1:
            {
            	printf("请依次输入学生姓名 学号及成绩：(学生姓名输入""#""时结束)\n"); 
                insert(head);
                break;
            }
            case 2:
            {
                del(head);
                break;
            }
            case 3:
            {
                sort(head);
                break;
            }
            case 4:
            {
                displayall(head);
                break;
            }
            case 5:
			{
				int num;
				printf("输入该生学号：");
				scanf("%d",&num);
				displayone(head,num);
				break;
			 } 
			 case 6:
			 	{
			 		int num;
			 		printf("请输入要修改学生的学号：");
					 scanf("%d",&num);
					 change(head,num); 
				 }
			case 7:
			{
				avg(head);
				break;
			 } 
			 case 8:
			 {
			 		fail(head);
			 		break;
			}
			case 9:
				{
					save(head);
					break;
				}
		}
   
    }
    if(b==2)
    while(choose=menu2(head))
    {
    	switch(choose)
        {
            case 1:
			{
				int num;
				printf("输入该生学号：");
				scanf("%d",&num);
				displayone(head,num);
				break;
			 } 
			 
			case 2:
			{
				avg(head);
				break;
			 } 
		
		}
	}
    
    
    return 0;
}




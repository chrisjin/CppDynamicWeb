#ifndef ______LIST
#define ______LIST
#include<windows.h>
#include<stdio.h>
template <typename T>
class List
{
       public:
        typedef struct Node
        {
            T s;
            Node *next;
            Node *up;
        }Node;
        Node *head;
        Node *p;
        Node *anew;
        int size;
        CRITICAL_SECTION se;
       public:
        List(){size=0;head=(Node *)malloc(sizeof(Node));p=head;p->next=NULL;p->up=NULL;}
        ~List();
        void push_back(const T& a)
        {
               //printf("dddd\n");
               InitializeCriticalSection(&se);
               EnterCriticalSection(&se);
               anew= (Node *)malloc(sizeof(Node));
               memcpy(&anew->s,&a,sizeof(T)); 
               anew->next=NULL;
               anew->up=p;
               p->next=anew;
               p=anew;
               size++;
               LeaveCriticalSection(&se);
        }

        T& operator[](int pos)
        {
             Node *a=head->next;
             for(int i=0;i<pos;i++)
             {
               a=a->next;           
             }
             return a->s;
              
        }
        T pop()
        {
            T s;
            InitializeCriticalSection(&se);
            EnterCriticalSection(&se);
            p->up->next=NULL; 
            Node *a=p;
            p=p->up;
            size--;
            s=a->s;
            //free(a);
            LeaveCriticalSection(&se);
            return s; 
            
        }
        T top()
        {
              return p->s;     
        }
        T take()
        {
            InitializeCriticalSection(&se);
             EnterCriticalSection(&se);
              Node *del=head->next;
              Node *temp=del;
              T a=del->s;
              
              if(del->next)
              del->next->up=head;
              else p=del->up;
              
              if(del->up)
              del->up->next=del->next;
              size--;
              if(temp)
              free(temp);
              LeaveCriticalSection(&se);
              return a;     
        }
        void clear()
        {
             InitializeCriticalSection(&se);
             EnterCriticalSection(&se);
             Node *a=head->next;
             Node *temp;
             while(1)
             {
                 temp=a;
                 if(temp!=NULL)
                 {
                 a=a->next;  
                 free(temp);
                 }
                 else
                 break;
                         
                           
             }
             p=head;p->next=NULL;p->up=NULL;
             LeaveCriticalSection(&se);  
             
             
        }


      
};
template <typename T>
List<T>::~List()
{
             InitializeCriticalSection(&se);
             EnterCriticalSection(&se);
             Node *a=head->next;
             Node *temp;
             while(1)
             {
                 temp=a;
                 if(temp!=NULL)
                 {
                 a=a->next;  
                 free(temp);
                 }
                 else
                 break;
                         
                           
             }
             p=head;p->next=NULL;p->up=NULL;
             LeaveCriticalSection(&se);  
               
}

#endif


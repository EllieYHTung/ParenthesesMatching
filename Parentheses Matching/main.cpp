//
//  main.cpp
//  Parentheses Matching
//
//  Created by YunHua Tung on 2019/4/4.
//  Copyright © 2019 YunHua Tung. All rights reserved.
//

#include <iostream>
using namespace std;
template <class B>
class Node{
public:
    B element;
    Node<B>* previous;
    Node<B>* next;
};

template <class C>
class LinkList{
public:
    LinkList(){
        headerNode->previous=headerNode->next=headerNode;
        count=0;
    }
    ~LinkList(){    //1.寫得對嗎？
        Node<C>* temp=headerNode->previous;
        while(temp!=headerNode){
            Node<C>* deleteNode=temp;
            temp=temp->previous;
            delete deleteNode;
        }
        delete headerNode;
    }
    void insertAtIndex(int _index, C _element){
        Node<C>* temp=headerNode;
        if(_index>count){
            temp=headerNode->previous;
        }else{
            for(int i=0;i<_index;i++){
                temp=temp->next;
            }
        }
        insert(temp, _element);
    }
    void removeElement(C _element){
        Node<C>* temp=headerNode->next;
        while(temp!=headerNode){
            if(temp->element==_element){
                remove(temp);
            }
            temp=temp->next;
        }
    }
    C getElementAtIndex(int _index){
        Node<C>* temp=headerNode;
        for(int i=0;i<=_index;i++){
            temp=temp->next;
        }
        return temp->element;
    }
    void printOut()const{
        Node<C>* temp=headerNode->next;
        while(temp!=headerNode){
            cout<<temp->element<<"->";
            temp=temp->next;
        }
        cout<<endl;
    }
    bool empty()const{
        if(headerNode->next!=headerNode){
            return false;
        }
        return true;
    }
    int size()const{
        return count;
    }
    
protected:
    Node<C>* headerNode=new Node<C>;
    int count;
    void insert(Node<C>* _beforeNode, C _element){
        Node<C>* insertNode=new Node<C>;
        Node<C>* _afterNode=_beforeNode->next;
        _beforeNode->next=insertNode;
        insertNode->next=_afterNode;
        _afterNode->previous=insertNode;
        insertNode->previous=_beforeNode;
        insertNode->element=_element;
        count++;
    }
    void remove(Node<C>* _removeNode){
        Node<C>* _beforeNode=_removeNode->previous;
        Node<C>* _afterNode=_removeNode->next;
        _beforeNode->next=_afterNode;
        _afterNode->previous=_beforeNode;
        delete _removeNode;
        count--;
    }
};

template <class D>
class Stack_RightTop{
    
public:
    ~Stack_RightTop(){
        delete stack_righttop;
    }
    void push(D _element){
        stack_righttop->insertAtIndex(stack_righttop->size(), _element);
    }
    void pop(){
        int _index=stack_righttop->size();
        D _element=stack_righttop->getElementAtIndex(_index-1);
        
        stack_righttop->removeElement(_element);
    }
    D top(){
        int _index=stack_righttop->size();
        return stack_righttop->getElementAtIndex(_index-1);
    }
    bool empty()const{
        return stack_righttop->empty();
    }
    int size()const{
        return stack_righttop->size();
    }
    void printOut()const{
        stack_righttop->printOut();
    }
protected:
    LinkList<D>* stack_righttop=new LinkList<D>;
    
};


int main(int argc, const char * argv[]) {
    Stack_RightTop<int> a;
    char inputString[]={'(','1','+','4',')','(','+','(','2','*','5',')',')','/','2','\0'};  //((1+4)(+(2*5))/2
    
    for(int i=0;i<sizeof(inputString);i++){
        
        if(inputString[i]=='('){
            a.push(i);
        }else if(inputString[i]==')'){
            if(a.size()==0){
                cout<<"A ')' Reduncdent at position:"<<i<<endl;
            }else{
                cout<<"Paired: ("<<a.top()<<","<<i<<")"<<endl;
                a.pop();
            }
        }
    }
    if(a.size()!=0){
        cout<<"A '(' Reduncdent at position:"<<a.top()<<endl;
    }else{
        cout<<"Expression Paired!"<<endl;
    }
    
    
    
    
    
    return 0;
}

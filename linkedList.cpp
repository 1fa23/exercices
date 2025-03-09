#include <iostream>


class Node{
    public:
      int data;
      Node* next;

      Node(int value) : data(value) , next(nullptr) {}

};

class LinkedList{

    public:
      // le premier noead
      Node* head;

      LinkedList() : head(nullptr) {};

      void append(int value){
        Node* newNode= new Node(value);

        if(!head){
            head=newNode;
        }
        else {
            // on continue de parcourir la liste jusqu'a atteindre la fin
            Node* temp=head;
            while(temp->next){
                temp=temp->next;
            }

            temp->next=newNode;
        }

      }

      void display(){
        Node* temp=head;
        while(temp){
            std::cout<<temp->data<<" ";
            temp=temp->next;

        }
      }
};


int main(){

    return(0);
}
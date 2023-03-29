#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

pthread_mutex_t mutex;

struct Node{
    int id;
    int size;
    int index;
    Node * right;
    Node * left;

    Node():right(NULL), left(NULL){}
    Node(int id, int size_, int index)
        :id(id), size(size), index(index), right(NULL), left(NULL){}
};

class HeapManager {
    public:
        HeapManager():head(NULL){}

        int initHeap(int size) {
            head = new Node(-1, size, 0);
            print();
            return 1;
        }

        int myMalloc(int ID, int size) {
            pthread_mutex_lock(&mutex);

            Node *current = head;
            bool flag = false;
            while(current) {
                if (current->id == -1 && current->size >= size) {
                    int left = current->size - size;


                    if (left > 0) {
                        current->id = ID;
                        current->size = size;
                        Node *right_node = new Node(-1, left, current->index + size);
                        right_node->right = current->right;
                        right_node->left = current;
                        current->right = right_node;

                        if (right_node->right) {
                            right_node->right->left = right_node;
                        }
                    }
                    else {
                        current->id = ID;
                        current->size = size;
                    }
                    flag = true;
                    break;
                }
                current = current->right;
            }

            if (flag) {
                cout << "Allocated for thread " << ID << endl;
                print();
                pthread_mutex_unlock(&mutex);
                return current->index;
            }
            else {
                cout << "Can not allocate, requested size "<< size << " for thread "<< ID << " is bigger than remaining size " << endl;
                print();
                pthread_mutex_unlock(&mutex);
                return -1;
            }

        }

        int myFree (int ID, int index) {
            pthread_mutex_lock(&mutex);
            Node *current = head;

            bool flag = false;

            while (current) {
                if (current->id == ID && current->index == index) {
                    current->id = -1;

                    if (current->left && current->left->id == -1) {

                        current->size += current->left->size;
                        current->index = current->left->index;
                        
                        if (current->left->left) {
                            current->left = current->left->left;
                        }
                        else {
                            current->left = NULL;
                            head = current;
                        }

                        if (current->left) {
                            current->left->right = current;
                        }
                        
                    }

                    if (current->right && current->right->id == -1) {
                        current->size += current->right->size;

                        if (current->right->right) {
                            current->right = current->right->right;
                        }
                        else {
                            current->right = NULL;
                        }

                        if (current->right) {
                            current->right->left = current;
                        }
                    }
                    flag = true;
                    break;
                }

                current = current->right;

            }

            if (flag) {
                cout << "Freed for thread " << ID << endl;
                print();
                pthread_mutex_unlock(&mutex);
                return 1;
            }
            else {
                cout << "No allocated memory found for thread "<< ID << " at index "<< index  << endl;
                print();
                pthread_mutex_unlock(&mutex);
                return -1;
            }
        }

        void print() {
            Node *current = head;

            bool flag = false;
            while (current) {
                if (flag) {
                    cout << "---";
                }
                flag = true;

                cout << "[" << current->id << "]" << "[" << current->size << "]" << "[" << current->index << "]";
                current = current->right;
            }
            cout << endl;

        }
    private:
        Node *head;

};
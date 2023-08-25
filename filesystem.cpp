#include<iostream>
using namespace std;

// BST implemented structure of folder system.
class FolderContainer {
    char *data;
    FolderContainer *root;
    FolderContainer *left,*right;
    bool created=false;

    // Constructor used while inserting data.
    FolderContainer(char* data,int size) {
        root = new FolderContainer();
        root->data = (char*)malloc(size);
        memcpy(root->data,data,size);
        root->left = nullptr;
        root->right = nullptr;
    }
public:
    // Constructor used in 
    FolderContainer() {
        root = new FolderContainer();
        root->data = (char*)malloc(2);
        memcpy(root->data,"/",2);
        root->left = nullptr;
        root->right = nullptr;
    }

    bool insert(char* data) {
        this->created = false;
        insertinto(this->root,data);
        return this->created;
    }

    void show() {
        display(this->root);
    }
private:
    void display(FolderContainer *root) {
        if(root) {
            display(root->left);
            printf("&s\n",root->data);
            display(root->right);
        }
    }

    FolderContainer* insertinto(FolderContainer *root,char* data) {
        if(root == nullptr) {
            this->created = true;
            return new FolderContainer(data,strlen(data));
        }
        if(strcmp(data,root->data) > 0) {
            root->right = insertinto(root,data);
        }
        else if(strcmp(data,root->data) < 0) {
            root->left = insertinto(root,data);
        }
        return root;
    }
};

class File {
    char *data;
    int size=0;
public:
    File(char data[],int size) {
        this->data = (char*)malloc(size);
        this->data = data;
        this->size = size;
    }
    void show() {
        for(int start=0 ; start<size ; ++start) {
            printf("%c",this->data[start]);
        }
        printf("\n");
    }
};

class Folder {
    char *name;
    
};

int main() {
    #ifndef ONLINE_JUDGE  
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    File a("This is the file",16);
    a.show();
}
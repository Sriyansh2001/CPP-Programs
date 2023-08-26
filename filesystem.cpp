#include<iostream>
#include<cstring>
using namespace std;

class Folder;
class File;
class FileStorage;

// Structure of File.
class File {
    char *data;
    char *name;
    int namesize=0;
    int datasize=0;
    Folder *parent;
public:
    // File Constructor to create file with some name.
    File(char name[],Folder *parent) {
        namesize = strlen(name);
        this->name = (char*)malloc(namesize+1);
        memcpy(this->name,name,namesize+1);
        this->parent = parent;
    }

    // return name
    char* getname() {
        return this->name;
    }

    // Insert data info file.
    void insertdata(char data[]) {
        datasize = strlen(data);
        this->data = (char*)malloc(datasize+1);
        memcpy(this->data,data,datasize+1);
    }

    // Go to Parent
    Folder* getparent() {
        return this->parent;
    }

    // Show the content of file.
    void show() {
        for(int start=0 ; start<datasize ; ++start) {
            printf("%c",this->data[start]);
        }
        printf("\n");
    }
};


class FileStorage {
    File *file;
    FileStorage *left,*right;
    // Constructor to create the file storage object while inserting file.
    FileStorage(File *file) {
        this->file = file;
        left = nullptr;
        right = nullptr;
    }
public:
    FileStorage() {

    }

    // To insert the file into FileStorage.
    FileStorage* insert(FileStorage *root,File *file) {
        if(root == nullptr) {
            return new FileStorage(file);
        }
        if(strcmp(root->file->getname(),file->getname()) < 0) {
            root->right = insert(root->right,file);
        }
        else if(strcmp(root->file->getname(),file->getname()) > 0) {
            root->left = insert(root->left,file);
        }
        return root;
    }

    // To display files in the current directory.
    void display(FileStorage *root) {
        if(root != nullptr) {
            display(root->left);
            printf("%s",root->file->getname());
            display(root->right);
        }
    }

    File* open(FileStorage* root,char name[]) {
        if(root == nullptr) {
            return nullptr;
        }
        if(strcmp(root->file->getname(),name) < 0) {
            return open(root->right,name);
        }
        else if(strcmp(root->file->getname(),name) > 0) {
            return open(root->left,name);
        }
        return root->file;
    }
};

class SubFiles {
    FileStorage *root;
    bool created = false;
public:
    // Constructor used in Initialization.
    SubFiles() {
        root = nullptr;
    }

    void insert(File* file) {
        root = root->insert(root,file);
    }

    void display() {
        root->display(root);
    }

    File* open(char name[]) {
        return root->open(root,name);
    }
};

class SubFolders {

};

class Folder {
    Folder *parent;
    char *name;
    int namesize=0;
    SubFiles *subfiles;
    SubFolders *subfolders;
public:
    // Folder Contructor to Initialize the Folder.
    Folder(Folder *root,char name[]) {
        this->parent = root;
        namesize = strlen(name);
        this->name = (char*)malloc(namesize);
        memcpy(this->name,name,namesize+1);
        subfiles = new SubFiles;
    }

    // To create file inside the folder.
    void createFile(Folder* root,char name[]) {
        File *file = new File(name,root);
        this->subfiles->insert(file);
    }

    // To create Folder inside the folder.
    void createFolder(char name[]) {

    }

    // Name of current folder.
    char* getname() {
        return name;
    }

    // Go to inner folder.
    void openFolder(char name[]) {

    }

    // Open File
    File* openFile(char name[]) {
        return this->subfiles->open(name);
    }

    // To go backward
    void back(Folder *root) {
        if(this->parent == nullptr) {
            return ;
        }
        root = root->parent;
    }

    // Display all files 
    void display() {
        subfiles->display();
    }
};

int main() {
    // #ifndef ONLINE_JUDGE  
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif
    // File a("Name",nullptr);
    // printf("No error\n");
    // a.insertdata("This is file data");
    // a.show();
    // printf("\n");
    Folder *root = new Folder(nullptr , "/");
    printf("%s\n",root->getname());
    root->createFile(root,"A");
    root->createFile(root,"B");
    root->createFile(root,"C");
    File* file = root->openFile("A");
    file->insertdata("This is data");
    file->show();
    root->display();
}
#include<iostream>
#include<cstring>
using namespace std;

// Defining class names.
class Folder;
class File;
class FileStorage;
class SubFolders;
class SubFiles;

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
            printf("%s ",root->file->getname());
            display(root->right);
        }
    }
    // Opens a particular file.
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

// SubFiles class to handle File class.
class SubFiles {
    FileStorage *root;
    bool created = false;
public:
    // Constructor used in Initialization.
    SubFiles() {
        root = nullptr;
    }
    // Insert File into folder.
    void insert(File* file) {
        root = root->insert(root,file);
    }   
    // Display all the files.
    void display() {
        root->display(root);
    }
    // Opens a particular file.
    File* open(char name[]) {
        return root->open(root,name);
    }
};


class SubFolders {
    Folder *folder;
    SubFolders *left,*right;
    // Constructor to create the file storage object while inserting file.
    SubFolders(Folder *folder) {
        this->folder = folder;
        left = nullptr;
        right = nullptr;
    }
public:
    // Defining function names.
    SubFolders* insert(SubFolders *root,Folder *folder);
    void display(SubFolders *root);
    Folder* open(SubFolders* root,char name[]);
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
        subfolders = nullptr;
    }

    // To create file inside the folder.
    void createFile(Folder* root,char name[]) {
        File *file = new File(name,root);
        this->subfiles->insert(file);
    }

    // To create Folder inside the folder.
    void createFolder(Folder *root,char name[]) {
        Folder *folder = new Folder(root,name);
        subfolders = subfolders->insert(subfolders,folder);
    }

    // Name of current folder.
    char* getname() {
        return name;
    }

    // Go to inner folder.
    Folder* openFolder(char name[]) {
        return this->subfolders->open(subfolders,name);
    }

    // Open File
    File* openFile(char name[]) {
        return this->subfiles->open(name);
    }

    // To go backward
    Folder* back(Folder *root) {
        if(root->parent == nullptr) {
            return root;
        }
        root = root->parent;
        return root;
    }

    // Display all files 
    void display() {
        printf("Folders : ");
        subfolders->display(subfolders);
        printf("\n");
        printf("Files :  ");
        subfiles->display();
        printf("\n");
    }
};


    // To insert the file into FileStorage.
SubFolders* SubFolders::insert(SubFolders *root,Folder *folder) {
        if(root == nullptr) {
            return new SubFolders(folder);
        }
        if(strcmp(root->folder->getname(),folder->getname()) < 0) {
            root->right = insert(root->right,folder);
        }
        else if(strcmp(root->folder->getname(),folder->getname()) > 0) {
            root->left = insert(root->left,folder);
        }
        return root;
    }

    // To display files in the current directory.
void SubFolders::display(SubFolders *root) {
        if(root != nullptr) {
            display(root->left);
            printf("%s ",root->folder->getname());
            display(root->right);
        }
    }
    // To open the folders.
Folder* SubFolders::open(SubFolders* root,char name[]) {
        if(root == nullptr) {
            return nullptr;
        }
        if(strcmp(root->folder->getname(),name) < 0) {
            return open(root->right,name);
        }
        else if(strcmp(root->folder->getname(),name) > 0) {
            return open(root->left,name);
        }
        return root->folder;
    }

// Driver Program.
int main() {
    #ifndef ONLINE_JUDGE  
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    Folder *root = new Folder(nullptr , (char*)"/");
    Folder *folder;
    char name[10];
    int fileinput;
    File* file;
    int input;

    printf("%s\n",root->getname());
    printf("Guide For Folder");
    printf("To Display : 1\n");
    printf("To Create File : 2\n");
    printf("To Create Folder : 3\n");
    printf("To Open File : 4\n");
    printf("To Open Folder : 5\n");
    printf("To Go back to prev Folder 6\n\n");

    
    printf("Guide For File\n");
    printf("To Display data : 1\n");
    printf("To insert data : 2\n");
    printf("To Go back to prev Folder 3\n\n\n");
    while(true) {
        scanf("%d",&input);
        if(input >= 7) {
            break;
        }
        cin.ignore();
        switch(input) {
            case 1:
                root->display();
                break;
            case 2:
                cin.getline(name,10);
                root->createFile(root,name);
                break;
            case 3:
                cin.getline(name,10);
                root->createFolder(root,name);
                break;
            case 4:
                cin.getline(name,10);
                file = root->openFile(name);
                if(file == nullptr) {
                    printf("File does not exits\n");
                    break;
                }
                fileinput=0;
                while(fileinput != 3) {
                    scanf("%d",&fileinput);
                    cin.ignore();
                    switch(fileinput) {
                        case 1:
                            file->show();
                            break;
                        case 2: 
                            char data[100];
                            cin.getline(data,100);
                            file->insertdata(data);
                            break;
                        default:
                            fileinput = 3;
                            break;
                    }
                }
                break;
            case 5:
                cin.getline(name,10);
                folder = root->openFolder(name);
                if(folder != nullptr) {
                    root = folder;
                }
                break;
            case 6:
                root = root->back(root);
            default:
                break;
        }
    }
}
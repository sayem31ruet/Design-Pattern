#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Component
class FileSystemItem {
public:
    virtual void showDetails(int indent = 0) = 0;
    virtual int getSize() = 0;
    virtual ~FileSystemItem() {}
};

// Leaf
class File : public FileSystemItem {
private:
    string name;
    int sizeInKB;
public:
    File(string n, int s) : name(n), sizeInKB(s) {}
    void showDetails(int indent = 0) override {
        cout << string(indent, ' ') << "- " << name
             << " (" << sizeInKB << " KB)" << endl;
    }
    int getSize() override {
        return sizeInKB;
    }
};

// Composite
class Folder : public FileSystemItem {
private:
    string name;
    vector<FileSystemItem*> children;
public:
    Folder(string n) : name(n) {}
    void add(FileSystemItem* item) {
        children.push_back(item);
    }
    void showDetails(int indent = 0) override {
        cout << string(indent, ' ') << "+ " << name << "/" << endl;
        for (FileSystemItem* item : children) {
            item->showDetails(indent + 4);
        }
    }
    int getSize() override {
        int total = 0;
        for (FileSystemItem* item : children) {
            total += item->getSize();
        }
        return total;
    }
    ~Folder() {
        for (FileSystemItem* item : children) {
            delete item;
        }
    }
};

int main() {
    Folder* root = new Folder("ProjectFolder");
    Folder* src  = new Folder("src");
    Folder* docs = new Folder("docs");

    src->add(new File("main.cpp", 5));
    src->add(new File("utils.cpp", 3));
    docs->add(new File("report.pdf", 10));

    root->add(new File("readme.txt", 2));
    root->add(src);
    root->add(docs);

    root->showDetails();
    cout << endl << "Total size: " << root->getSize() << " KB" << endl;

    delete root;
    return 0;
}
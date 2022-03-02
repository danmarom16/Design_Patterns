#include <iostream>
using namespace std;

class Document{
public:
    void copy(){
        cout << "Document Copied" << endl;
    }
    void paste(){
        cout << "Document Pasted" << endl;
    }
};

class Command{
public:
    virtual void execute() = 0;
};

class CopyCommand : public Command{
private:
    Document& d;
public:
    CopyCommand(Document& document) : d(document){};
    void execute() override{
        cout << "debug: Hey From CopyCommand" << endl;
        d.copy();
    }
};

class PasteCommand : public Command{
private:
    Document& d;
public:
    PasteCommand(Document& document) : d(document){};
    void execute() override{
        d.paste();
    }
};

class MenuItemInvoke{
public:
    void Clicked(Command* c){
        cout << "debug: Hey From MenuItemInvoke" << endl;
        c->execute();
    }
};

class KeyBoardInvoke{
public:
    void KeyInvoke (Command* c){
        cout << "debug: Hey From KeyBoardInvoke" << endl;
        c->execute();
    }
};

int main() {

    // set-up
    Document document;
    Command* cc = new CopyCommand(document);
    Command* pc = new PasteCommand(document);
    MenuItemInvoke mii;
    KeyBoardInvoke kbi;

    // Invoke copy
    cout << "Copy Invoking:" << endl;
    cout << "First Invoked With Click - " << endl;
    mii.Clicked(cc);
    cout << "Second Invoked With KeyBoard - " << endl;
    kbi.KeyInvoke(cc);

    cout << "---------" << endl;

    // Invoke paste
    cout << "Copy Invoking:" << endl;
    cout << "First Invoked With Click - " << endl;
    mii.Clicked(pc);
    cout << "Second Invoked With KeyBoard - " << endl;
    kbi.KeyInvoke(pc);

    cout << "Done!" << endl;
    return 0;
}

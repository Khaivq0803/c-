#include <iostream>
#include <string>
#include <ctime>
#include <vector> 
#include <iomanip>
#include <fstream>

using namespace std;

const int FINE_PER_DAY = 1000;  

int daysBetween(time_t start, time_t end) {
    return (end - start) / (60 * 60 * 24);
}
struct Student {
    int MSSV;
    string FullName;
    string lop;
    vector<int> IDMuon; 
    time_t borrowDate; 
    time_t returnDate; 
};
struct NodeSt {
    Student data;
    NodeSt* next;
};

struct StList {
    NodeSt* head;
    NodeSt* tail;
    int sizeSt; 

    StList() {  
        head = tail = NULL;
        sizeSt = 0;
    }

    NodeSt* createNodeSt(Student student);  
    void StaddFirst(Student student);  
    void addSt(int Mssv, string FullName, string lop, vector<int> idMuons); 
    void returnBook(int Mssv, int idTra);  
    void output(); 
    NodeSt*findStudent(int Mssv, const string& FullName, const string& lop);
    bool checkMSSV(int Mssv);
    void removeStudent(int Mssv);
    void swap(NodeSt*a, NodeSt*b);
    void bubbleSort();
};

NodeSt* StList::createNodeSt(Student student) {
    NodeSt* p = new NodeSt();
    p->data = student;  
    p->next = NULL;
    return p;
}

void StList::StaddFirst(Student student) {
    NodeSt* p = createNodeSt(student);
    if (head == NULL) {
        head = tail = p;
    } else {
        p->next = head;
        head = p;
    }
    sizeSt++;
}

void StList::addSt(int Mssv, string FullName, string lop, vector<int> idMuons) {
    Student st = {Mssv, FullName, lop, idMuons};
    time(&st.borrowDate); 
    st.returnDate = 0; 
    StaddFirst(st);
    cout << "Da tao the muon" << endl;
}

void StList::returnBook(int MSSV, int idTra) {
    NodeSt* i = head;  
    while (i != NULL) {  
        if (i->data.MSSV == MSSV) { 
            bool found = false;

            
            for (size_t j = 0; j < i->data.IDMuon.size(); ++j) {
                if (i->data.IDMuon[j] == idTra) {
                    found = true;  
                    time(&i->data.returnDate);  

                    int borrowDays = daysBetween(i->data.borrowDate, i->data.returnDate);
                    int daysLate = borrowDays - 60;

                    cout << "Sinh vien " << i->data.FullName << " da tra sach co ID " << idTra;
                    if (daysLate > 0) {
                        int fine = daysLate * FINE_PER_DAY;
                        cout << ". Phat: " << fine << " VND do tra muon " << daysLate << " ngay." << endl;
                    } else {
                        cout << ". khong co phat do tra dung han." << endl;
                    }

                    i->data.IDMuon.erase(i->data.IDMuon.begin() + j);
                    break; 
                }
            }

            if (!found) {
                cout << "Sinh vien khong muon sach voi ID nay." << endl;
            }
            return; 
        }
        i = i->next; 
    }
}

NodeSt* StList::findStudent(int Mssv, const string& FullName, const string& lop) {
    NodeSt* i = head;
    while (i != NULL) {
        if (i->data.MSSV == Mssv && i->data.FullName == FullName && i->data.lop == lop) {
            return i; 
        }
        i = i->next;
    }
    return NULL; 
}

bool StList::checkMSSV(int Mssv) {
    NodeSt* p = head;  
    while (p != NULL) {
        if (p->data.MSSV == Mssv) {
            return true; 
        }
        p = p->next; 
    }
    return false; 
}

void StList::removeStudent(int Mssv) {
    NodeSt* i = head;
    NodeSt* a = NULL;

    while (i != NULL) {
        if (i->data.MSSV == Mssv && i->data.IDMuon.empty()) {  
            if (a == NULL) {  
                head = i->next;
                delete i;
            } else { 
                a->next = i->next;
                delete i;
            }

            sizeSt--;  
            return;  
        }
        
        
        a = i;
        i = i->next;
    }
}

void StList::swap(NodeSt* a, NodeSt* b) {
    Student temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
}

void StList::bubbleSort(){
    char x;
    cout<<"ban muon hien thi theo: "<<endl;
    cout << "1. MSSV" << endl;
    cout << "2. Ho Ten" << endl;
    cout << "3. Lop" << endl;
    cout << "Hay nhap lua chon (1-3): ";
    cin >> x;

    if (x < '1' || x > '3') {
        cout << "Lua chon khong hop le." << endl;
        return; 
    }

    if (head == NULL) {
        cout << "Danh sach rong" << endl;
        return; 
    }

    bool swapped;
    do {
        swapped = false;
        NodeSt* p = head;

        while (p->next != NULL) {
            NodeSt* nextNode = p->next; 
            bool ss = false;

            if (x == '1') {
                ss = (p->data.MSSV > nextNode->data.MSSV);
            } else if (x == '2') {
                ss = (p->data.FullName > nextNode->data.FullName);
            } else if (x == '3') {
                ss = (p->data.lop > nextNode->data.lop);
            }

            if (ss) {
                swap(p, nextNode); 
                swapped = true; 
            }
            p = p->next; 
        }
    } while (swapped);
}

void StList::output() {
    bubbleSort();
    cout << left << setw(10) << "MSSV"
         << " | " << setw(25) << "Ho Ten"
         << " | " << setw(15) << "Lop"
         << " | " << setw(30) << "Danh Sach Muon" << endl;
    cout << string(90, '-') << endl; 

    NodeSt* i = head;
    while (i != NULL) {
        cout << left << setw(10) << i->data.MSSV
             << " | " << setw(25) << i->data.FullName
             << " | " << setw(15) << i->data.lop
             << " | ";

        
        if (!i->data.IDMuon.empty()) {
            for (size_t j = 0; j < i->data.IDMuon.size(); ++j) {
                cout << i->data.IDMuon[j];
                if (j < i->data.IDMuon.size() - 1) {
                    cout << ", "; 
                }
            }
        } else {
            cout << "Khong co sach"; 
        }

        cout << endl;
        i = i->next;
    }
}

struct Book {
    int id;
    string name; 
    string tacgia;
    string theloai;
    int soluong;
};
struct Node {
    Book data;
    Node* next;
};

struct BList {
    Node* head;
    Node* tail;
    int size; 

    BList() {  
        head = tail = NULL;
        size = 0;
    }

    Node* createNode(Book book);  
    void addFirst(Book book);  
    void addBook(int id, string name, string tacgia, string theloai, int soluong);  
    void FindBook(string x);  
    void UpdateBook(int id);
    bool checkid(int id);
    int checkslg(int id);
    void Out(); 
    void giamsach(vector<int> idMuons);
    void tangsach(vector<int> idTra);
    void removeBook(int id);
    void bubbleSort1();
    void swap1(Node* a, Node* b);
};

Node* BList::createNode(Book book) {
    Node* p = new Node();
    p->data = book;
    p->next = NULL;
    return p;
}

void BList::addFirst(Book book) {
    Node* p = createNode(book);
    if (head == NULL) {
        head = tail = p;
    } else {
        p->next = head;
        head = p;
    }
    size++;
}

bool BList::checkid(int id) {
    Node* p = head;  
    while (p != NULL) {
        if (p->data.id == id) {
            return true; 
        }
        p = p->next; 
    }
    return false; 
}

void BList::addBook(int id, string name, string tacgia, string theloai, int soluong) {
    bool found1 = false;
    Node* p = head;
    while (p != NULL) {
        if (p->data.name == name && p->data.tacgia == tacgia && p->data.theloai == theloai) {
            cout << "Thong tin vua nhap trung voi sach da co. Vui long nhap thong tin khac." << endl;
            found1 = true;
            break; 
        }
        p = p->next; 
    }
    if (!found1) {
        Book book = {id, name, tacgia, theloai, soluong};  
        addFirst(book); 
        cout << "Them sach thanh cong!" << endl;  
    }
}
void BList::removeBook(int id) {
    Node* p = head;
    Node* a = NULL;

    while (p != NULL) {
        if (p->data.id == id) {  
            if (a == NULL) {  
                head = p->next;
                if (p == tail) {
                    tail = NULL;  
                }
            } else {
                a->next = p->next;
                if (p == tail) {
                    tail = a;  
                }
            }
            delete p;
            size--;
            cout << "Da xoa sach voi ID " << id << " khoi danh sach." << endl;
            return;
        }
        a = p;
        p = p->next;
    }
    cout << "Khong tim thay sach voi ID " << id << " trong danh sach." << endl;
}

void BList::FindBook(string x) {
    bool found = false; 
    for(Node*i=head;i != NULL; i=i->next) {
        if (x == i->data.name || x== i->data.tacgia || x == i->data.theloai ) {
            cout << "Da tim thay sach theo tim kiem: " << endl;
            cout << "ID: " << i->data.id << endl;
            cout << "Ten sach: " << i->data.name << endl;
            cout << "Tac gia: " << i->data.tacgia << endl;
            cout << "The loai: " << i->data.theloai << endl;
            cout << "So luong: " << i->data.soluong << endl;
            found = true; 
            break;
        }
    }
    if (!found) {
        int id=stoi(x);
        for (Node* i = head; i != NULL; i = i->next) {
            if (id == i->data.id) {
            cout << "Da tim thay sach theo tim kiem: " << endl;
            cout << "ID: " << i->data.id << endl;
            cout << "Ten sach: " << i->data.name << endl;
            cout << "Tac gia: " << i->data.tacgia << endl;
            cout << "The loai: " << i->data.theloai << endl;
            cout << "So luong: " << i->data.soluong << endl;
            found = true; 
            break;
            }
        }
    }
    if (!found) {
        cout << "Khong tim thay sach." << endl; 
    }
}

void BList::UpdateBook(int id) {
    Node* i = head; 
    while (i != NULL) {
        if (i->data.id == id) {
            cout << "Thong tin hien tai:" << endl;
            cout << "ID: " << i->data.id << endl;
            cout << "Ten sach: " << i->data.name << endl;
            cout << "Tac gia: " << i->data.tacgia << endl;
            cout << "The loai: " << i->data.theloai << endl;
            cout << "So luong: " << i->data.soluong << endl;

            cout << "Nhap ten sach moi: ";
            cin.ignore(); 
            getline(cin, i->data.name);
            cout << "Nhap tac gia moi: ";
            getline(cin, i->data.tacgia);
            cout << "Nhap the loai moi: ";
            getline(cin, i->data.theloai);
            cout << "Nhap so luong moi: ";
            cin >> i->data.soluong;

            cout << "Cap nhat thong tin sach thanh cong!" << endl;
            return; 
        }
        i = i->next; 
    }
    cout << "Khong tim thay sach voi ID: " << id << endl; 
}

int BList::checkslg(int id) {
    Node* p = head;  
    while (p != NULL) {
        if (p->data.id == id) {
            return p->data.soluong; 
        }
        p = p->next; 
    }
    return 0; 
}

void BList::giamsach(vector<int> idMuons) {
    for (size_t i = 0; i < idMuons.size(); i++) {
        int id = idMuons[i];
        Node* p = head;

        while (p != NULL) {
            if (p->data.id == id) {
                p->data.soluong--; 
                break;
            }
            p = p->next; 
        }
    }
}

void BList::tangsach(vector<int> idTra) {
    for (size_t i = 0; i < idTra.size(); i++) {
        int id = idTra[i];
        Node* p = head;  

        while (p != NULL) {
            if (p->data.id == id) {
                p->data.soluong++; 
                break;
            }
            p = p->next; 
        }
    }
}

void BList::swap1(Node* a, Node* b) {
    Book temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
}

void BList::bubbleSort1(){
    char x;
    cout<<"ban muon hien thi theo: "<<endl;
    cout << "1. ID" << endl;
    cout << "2. Ten Sach" << endl;
    cout << "3. Tac gia" << endl;
    cout << "4. The Loai" << endl;
    cout << "Hay nhap lua chon (1-4): ";
    cin >> x;

    if (x < '1' || x > '4') {
        cout << "Lua chon khong hop le." << endl;
        return; 
    }

    if (head == NULL) {
        cout << "Danh sach rong" << endl;
        return; 
    }

    bool swapped;
    do {
        swapped = false;
        Node* p = head;

        while (p->next != NULL) {
            Node* nextNode = p->next; 
            bool ss = false;

            if (x == '1') {
                ss = (p->data.id > nextNode->data.id);
            } else if (x == '2') {
                ss = (p->data.name > nextNode->data.name);
            } else if (x == '3') {
                ss = (p->data.tacgia > nextNode->data.tacgia);
            }else if (x == '4') {
                ss = (p->data.theloai > nextNode->data.theloai);
            }

            if (ss) {
                swap1(p, nextNode); 
                swapped = true; 
            }
            p = p->next; 
        }
    } while (swapped);
}

void BList::Out() {
    bubbleSort1();
    cout << left << setw(10) << "ID"
         << " | " << setw(25) << "Ten Sach"
         << " | " << setw(20) << "Tac Gia"
         << " | " << setw(15) << "The Loai"
         << " | " << setw(10) << "So Luong" << "|"<<endl;
    cout << string(93, '-') << endl; 
    
    Node* i = head;
    while (i != NULL) {
        cout << left << setw(10) << i->data.id
             << " | " << setw(25) << i->data.name
             << " | " << setw(20) << i->data.tacgia
             << " | " << setw(15) << i->data.theloai
             << " | " << setw(10) << i->data.soluong << "|"<< endl;
        i = i->next;
    }
}


int main() {
    BList list;  
    StList st;

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Them sach" << endl;
        cout << "2. Sua thong tin sach" << endl;
        cout << "3. Tim kiem sach" << endl;
        cout << "4. Tao the muon sach" << endl;
        cout << "5. Xem danh sach sach" << endl;
        cout << "6. Xem danh sach muon sach" << endl;
        cout << "7. Tra sach" << endl;
        cout << "8. Xoa sach" << endl;
        cout << "9. Thoat" << endl;

        int choice;
        cout << "Chon chuc nang (1-9): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string name, tacgia, theloai;
                int id, soluong;
                
                do {
                    cout << "Nhap ma sach (id >= 1): ";
                    cin >> id;
                    if (id < 1) {
                        cout << "ID phai lon hon hoac bang 1. Vui long nhap lai.\n";
                    } else if (list.checkid(id)) {
                        cout << "Sach voi ID " << id << " da ton tai. Vui long nhap ID khac.\n";
                        id = -1; 
                    }
                } while (id < 1);
                cin.ignore();
                cout << "Nhap ten sach: ";
                getline(cin, name);
                cout << "Nhap ten tac gia: ";
                getline(cin, tacgia);
                cout << "Nhap the loai: ";
                getline(cin, theloai);
                cout << "Nhap so luong sach: ";
                cin >> soluong;

                list.addBook(id, name, tacgia, theloai, soluong);
                break;
            }
            case 2: {
                int id;
                cout << "Nhap ID sach muon sua doi: ";
                cin >> id;
                list.UpdateBook(id);
                break;
            }
            case 3: {
                string x;
                cout << "Nhap thong tin can tim: ";
                cin.ignore();
                getline(cin, x);
                list.FindBook(x);
                break;
            }
            case 4: {
                int Mssv;
                string FullName, lop;
                cout << "Nhap MSSV: ";
                cin >> Mssv; 
                cin.ignore(); 
                cout << "Nhap ten sinh vien: ";
                getline(cin, FullName);
                cout << "Nhap lop: ";
                getline(cin, lop);
            
                NodeSt* existingStudent = st.findStudent(Mssv, FullName, lop);
                vector<int> idMuons; 
                int idMuon;
                char choice;
            
                if (existingStudent) {
                    cout << "Sinh vien da ton tai, them ID sach vao danh sach muon." << endl;
                } else {
                    cout << "Tao the muon moi cho sinh vien." << endl;
                }
            
                do {
                    cout << "Nhap ID cua sach muon muon: ";
                    cin >> idMuon;
            
                    if (list.checkid(idMuon)) {
                        if (list.checkslg(idMuon) > 0) {
                            idMuons.push_back(idMuon); 
                            cout << "Da them ID sach muon " << idMuon << " vao danh sach muon." << endl;
                        } else {
                            cout << "Sach voi ID " << idMuon << " hien khong con so luong!" << endl;
                        }
                    } else {
                        cout << "ID sach khong ton tai!" << endl;
                    }
            
                    cout << "Ban co muon nhap ID sach khac? (y/n): ";
                    cin >> choice;
                } while (choice == 'y' || choice == 'Y');
            
                if (!idMuons.empty()) { 
                    if (existingStudent) {
                        for (size_t j = 0; j < idMuons.size(); j++) {
					        existingStudent->data.IDMuon.push_back(idMuons[j]);
					    }
                        cout << "Da them ID sach vao the muon cua sinh vien." << endl;
                    } else {
                        st.addSt(Mssv, FullName, lop, idMuons); 
                        list.giamsach(idMuons); 
                    }
                } else {
                    cout << "Khong co ID sach hop le de muon!" << endl;
                }
                break;
            }

            case 5: {
                cout << "Danh sach sach:" << endl;
                list.Out();
                break;
            }
            case 6: {
                cout << "Danh sach muon sach:" << endl;
                st.output();
                break;
            }
            case 7: {
                int Mssv;
                cout << "Nhap MSSV: ";
                cin >> Mssv;
                
                if (st.checkMSSV(Mssv)) {
                    vector<int> idTras;
                    
                    char traTiep;
                    do {
                        int idTra;
                        cout << "Nhap ID cua sach muon tra: ";
                        cin >> idTra;
                        
                        st.returnBook(Mssv, idTra);  
                        idTras.push_back(idTra);    
                        
                        cout << "Ban co muon tra them sach khong? (y/n): ";
                        cin >> traTiep;
                    } while (traTiep == 'y' || traTiep == 'Y');
                    
                    st.removeStudent(Mssv);
                    list.tangsach(idTras);  
            
                } else {
                    cout << "Khong tim thay sinh vien voi MSSV nay." << endl;
                }
                break;
            }

            case 8: {
                int id;
                cout << "Nhap ID sach muon xoa: ";
                cin >> id;
                if(list.checkid(id)){
                   list.removeBook(id);
                }
                else{
                    cout<<"khong co sach nay." << endl;
                }
                
                break;
            }
            case 9:
                cout << "Thoat chuong trinh!" << endl;
                return 0;
            default:
                cout << "Chuc nang khong hop le. Vui long chon lai!" << endl;
        }
    }

    return 0;
}

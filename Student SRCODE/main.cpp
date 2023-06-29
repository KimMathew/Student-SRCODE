#include <iostream>

using namespace std;

class Node{
public:
    int data;
    Node* next;

    string name;
    string srcode;
    string subj;
    string profName;
    string sched;
};

void title(){
    cout << "\t\t\t\t\t\t============================" << endl;
    cout << "\t\t\t\t\t\t|Student Information System|" << endl;
    cout << "\t\t\t\t\t\t============================" << endl;
}

void displayOptions(){
    cout << "------------------------------";
    cout << "\n[1] Add students";
    cout << "\n[2] Display All Students";
    cout << "\n[3] Search student via SRCODE";
    cout << "\n[4] Delete a specific student";
    cout << "\n[5] Exit the Program";
    cout << "\n------------------------------";
}

void displayDetails(Node* head, int isSize){
    cout << "------------------------------------" << endl;
    cout << "\t  Student Details:" << endl;
    cout << "------------------------------------" << endl;

    Node* curr = head;
    int studentNo = 1;
    while(curr != NULL){
        cout << "Student No:" << studentNo << ": " << curr->name;
        cout << "\t\t" << "SR-CODE: " << curr->srcode << endl;
        curr = curr->next;
        studentNo++;
    }
}

void insertNode(Node** head, string name, string srcode, string subj, string profName, string sched){
    Node* newNode = new Node();
    newNode->name = name;
    newNode->srcode = srcode;
    newNode->subj = subj;
    newNode->profName = profName;
    newNode->sched = sched;
    newNode->next = NULL;

    if(*head == NULL){
        *head = newNode;
    }
    else{
        Node* curr = *head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

Node* searchNode(Node* head, string isSearch){
    Node* curr = head;
    while(curr != NULL){
        if(curr->srcode == isSearch){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void deleteNode(Node** head, string srcode, int& isSize){
    if ((*head)->srcode == srcode) { //if head is to delete
        Node* temp = *head;
        *head = (*head)->next;
        delete temp;
        cout << "\nStudent with SR-CODE: [" << srcode << "] has been deleted.";
        isSize--;
        return;
    }

    Node* curr = *head;
    Node* prev = NULL;

    while (curr != NULL && curr->srcode != srcode) { //search for the match srcode
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) { //displays if the node is not found
        cout << "\nStudent with SR-CODE: [" << srcode << "] does not exist.";
        return;
    }

    prev->next = curr->next; //make the previous node points on what the node to delete is pointing to
    delete curr;
    cout << "\nStudent with SR-CODE: [" << srcode << "] has been deleted.";
    isSize--;
}

int main()
{
    Node* head = NULL;
    string isSearch, tryAgain, isBack, isDelete, choice, choice2;
    string name, srcode, subj, profName, sched;
    int temp;
    int isSize;

    bool isMain = true;
    while(isMain){
        system("CLS");
        title();
        displayOptions();
        cout << "\nYour Choice: ";
        cin >> choice;

        if(choice == "1"){
            system("CLS");
            title();
            cout << "\nEnter the number of students: ";

            while(!(cin >> isSize)){
                cout << "\nInvalid Input!" << endl << endl;
                cout << "Please input again: ";
                cin.clear();
                while(cin.get() != '\n');
            }
            cout << endl;

            for(int i = 0; i < isSize; i++){
                cout << "---Enter the data for Student No." << i + 1 << " out of " << isSize << "---";
                cout << "\nEnter the name of Student No." << i + 1 << ": ";
                cin >> name;
                cout << "Enter the SRCODE: ";
                cin >> srcode;
                cout << "Enter the subject: ";
                cin >> subj;
                cout << "Enter the Professor Name: ";
                cin >> profName;
                cout << "Enter the Schedule Time: ";
                cin >> sched;
                cout << endl;

                insertNode(&head, name, srcode, subj, profName, sched);
            }
            continue;
        }
        else if(choice == "2"){
            system("CLS");
            title();
            displayDetails(head, isSize);
            cout << "------------------------------------" << endl;

            cout << "\nPress any key to go back: ";
            cin.ignore();
            cin.get();

            continue;
        }
        else if(choice == "3"){
            system("CLS");
            title();

            bool again = true;
            while(again){
                cout << "\nEnter the SRCODE to display the specific details: ";
                cin >> isSearch;

                for(int i = 0; i < isSize; i++){
                    Node* foundNode = searchNode(head, isSearch);
                    if(foundNode != NULL){
                        cout << "\nStudent: " << foundNode->name;
                        cout << "\t\t" << "SR-CODE: " << foundNode->srcode;
                        cout << "\t\t" << "Subject: " << foundNode->subj;
                        cout << "\t\t" << "Professor: " << foundNode->profName;
                        cout << "\t\t" << "Schedule: " << foundNode->sched << endl;
                        again = false;
                        temp = 1;

                        bool again2 = true;
                        while(again2){
                            cout << "\nDo you want to search again? [Y]/[N]: ";
                            cin >> choice2;

                            if(choice2 == "Y" || choice2 == "y"){
                                again2 = false;
                                again = true;
                            }
                            else if(choice2 == "N" || choice2 == "n"){
                                again2 = false;
                                again = false;
                            }
                            else{
                                cout << "\nInvalid Input! Please Try Again!" << endl;
                            }
                        }
                        break;
                    }
                }
                if(temp == 0){
                    cout << "\nThe student identified by the given ID does not exist. Please try again!" << endl;
                }
            }
        }
        else if(choice == "4"){ //delete
            system("CLS");
            title();

            if(head == NULL){ //display if the list is empty
                cout << "\nThere is no student to delete.";
            }
            else{
                cout << "\nEnter the SRCODE of the student you want to delete: ";
                cin >> isDelete;

                deleteNode(&head, isDelete, isSize);
            }

            cout << "\n\nPress any key to go back: ";
            cin.ignore();
            cin.get();

            continue;
        }
        else if(choice == "5"){ //Exits the program
            break;
        }
        else{ //error handler
            "\nInvalid Input! Please Try Again!";
        }
    }
    return 0;
}

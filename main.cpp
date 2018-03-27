#include<iostream>
#include<stdio.h>
#include<string.h>
#include<map>
#include<iterator>
using namespace std;

/*
* List
*/

template <typename E>
class List
{
    void operator = (const List&) {}
    List(const List&) {}
    
    public:
        //constructors and destructors
        List() {}
        virtual ~List() {}
        
        //Return the number of elements in the List
        virtual int NumberOfElements() const = 0;
        
        //Return the Location of current element
        virtual int CurrentLocation() const = 0;
        
        //Return the data of current element
        //virtual const E& getData() const = 0;
        
        //clear all the data from the List
        virtual void clear() = 0;
        
        //insert a data in the List at current location
        virtual void insert(const E& data) = 0;
        
        //insert a data in the end of the List
        //virtual void append(const E& data) = 0;
        
        //delete a data at the current Location
        virtual E remove() = 0;
        
        //set the current Location to the start of the List
        //virtual void setListLocationToStart() = 0;
        
        //set the current Location to the end of the List
        //virtual void setListLocationToEnd() = 0;
        
        //set the current Location to the element on left side
        // of current element
        //virtual void previousElement() = 0;
        
        //set the current Location to the element on left side
        // of current element
        //virtual void nextElement() = 0;
        
        //Set current Location to a new Location
        virtual int setToNewLocation(int location) = 0;
        
};

/*
* Array List
*/

template <typename E>
class arrayList: public List<E>
{
    int arraySize; // maximum size of the list
    int currentSize; // number of data elements stored
    int currentLocation; // location pointer of the list
    E* dataArray; // Array for storing the data
    
    public:
        //constructors and destructors
        arrayList(int size)
        {
            arraySize = size;
            currentSize = currentLocation = 0;
            dataArray = new E[arraySize];
        }
        ~arrayList()
        {
            delete [] dataArray;    
        }
        
        // Return number of elements currently
        
        int NumberOfElements() const {
            return currentSize;
        }
        
        // Return Current Location
        
        int CurrentLocation() const {
            return currentLocation;
        }
        
        
        // clears the array
        
        void clear(){
            for(int i = 0;i < currentSize;i++){
                dataArray[i] = 0;
            }
            currentSize = 0;
            currentLocation = 0;
        }
        
        // insert element
        
        void insert(const E& data){
            // if currentSize != arraySize
            if(currentSize < arraySize){
                cout << "Inside insert " << endl;
                dataArray[currentSize] = data;
                currentSize++;
            }
            else{
                cout << "List limit Reached.." << endl;
            }
        }
        
        // Removes current Element
        E remove(){
            // removed (backup variable)
            if(currentSize == 0){
                cout << "Queue is empty" << endl;
                return 0;
            }
            E removed = dataArray[0];
            for(int i = 0;i < currentSize-1;i++){
                dataArray[i]=dataArray[i+1];
            }
            dataArray[currentSize-1] = 0;
            currentSize--;
            return removed;
        }
        
        int setToNewLocation(int location){
            currentLocation = location;
        }
        
        void display(){
            cout << "Queue Size: " << arraySize << endl;
            cout << "Current Size: " << currentSize << endl;
            cout << "\nElements: " << endl;
            for(int i = 0;i<currentSize;i++){
                cout << dataArray[i] << " ";
            }
        }
};

 
template <typename E>
class Queue
{
    void operator = (const Queue&) {}
    Queue(const Queue&) {}
    
    public:
        //constructors and destructors
        Queue() {}
        virtual ~Queue() {}
        
        // Insert an element at the end of the queue
        virtual void insert(const E &) = 0;
        
        //Remove the first element of the queue
        virtual E remove() = 0;
        
        // Return the length of the queue
        virtual int length() const = 0;
        
        //Return a copy of the first element
        virtual const E& FirstElement() const= 0;
        
        // Remove all the elements from the Queue
        // and free the occupied memory without causing
        // memory leak
        virtual void clearQueue() = 0;
        
};    

template <typename E>
class QueueArrayList:  public Queue<E>
{
    int maximumSize;  //maximum size of the array list
    int firstElement; //index of the first element
    int lastElement; //index of the last element
    arrayList<E>* QueueArray; // Array for storing the data
    
    
    public:
        //constructors and destructors
        //constructors and destructors
        QueueArrayList(int size)
        {
            maximumSize = size;
            QueueArray = new arrayList<E>(size);
            firstElement = lastElement = 0;
        }
        ~QueueArrayList()
        {
            delete QueueArray;    
        }
        
        // Insertion
        void insert(const E &input){
        
            lastElement = QueueArray->NumberOfElements();
            QueueArray->insert(input);
        }
        E remove(){
            E removed = QueueArray->remove();
            lastElement = QueueArray->NumberOfElements();
            return removed;
        }
        
        int length() const {
            return QueueArray->NumberOfElements();
        }
        const E& FirstElement() const {
            return firstElement;
        }
        void clearQueue(){
            QueueArray->clear();
        }
        // to print information
        void display(){
            QueueArray->display();
        }
};

struct node{
    char letter;
    node* next;
    
    node(){
        letter = '\0';
        next = NULL;
    }
};

/*
// Whenever a command is added,
// Increment number_of_commands.
*/

const int number_of_commands = 5;

const string commands[number_of_commands] = { "del", "add", "push", "disp", "exit"};
void command_info(string about){
    map <string, string> command_info;

    command_info.insert(pair <string, string> ("del", "Deletes current Element"));
    command_info.insert(pair <string, string> ("add", "[-operand] adds Element in the Queue"));
    command_info.insert(pair <string, string> ("disp", "Displays Information" ));
    command_info.insert(pair <string, string> ("exit", "Exits the program"));
    
    map <string, string> :: iterator itr;
    if(about == ""){
        cout << "hate" << endl;
        for(itr = command_info.begin(); itr != command_info.end(); itr++){
            cout << "\t" << itr->first << " - " << itr->second << endl;
        }
    }
    else{
        cout << "Else" << endl;
        cout << command_info.find(about)->first << endl;
        cout << "\t" << command_info.find(about)->first << " - " << command_info.find(about)->second << endl;
    }
}

bool match(char *a, string b){
	if(strlen(a) != b.length()){
		return false;
	}
	else{
		for(int i = 0;i < strlen(a);i++){
			if(a[i] != b[i]){
				return false;
			}
		}
	}
	return true;
}

class command{
    node* head;
    node* now;
    int size;
    public:
        command(){
            head = now = new node();
            size = 0;
        }
        ~command(){
            delete head;
            delete now;
        }
        void put(char ch){
            if(size == 0){
                now->letter = ch;
                now = now->next;
            }
        }
        void to_head(){
             now = head;
        }
};

int main(){
    cout << "Quelisa 0.1.2 |Developed by Sanket Chaudhari|" << endl;
    cout << "type \"help\" to see command list." << endl;
    string command_is, username, queue_operand, queue_operator;
    char dummy, temp[20];
    cout << "Username: "; cin >> username;
    scanf("%c", &dummy);
    //cin.getline(username, 80);
    bool space = false, start = false, end = false;
    bool got_a_match = false;
    int line_no = 0, i_1;
    char ch;
    while(true){
        cout << username << "[" << line_no << "]>> ";       
        space = got_a_match = false;
        int i_0 = 0, operand = 0;
        char input[80];
        
        while((ch = getchar()) != '\n'){
            if(space){
                if(ch == ' '){
                    break;
                }
                int temp_0 = ch - '0';
                cout << temp_0 << endl;
                operand = 10*operand + temp_0;
                i_0 += 1;
            }
            else{
                input[i_0] = ch;
                i_0 += 1;            
            }
            if(ch == ' '){
                space = true;
                i_0 = 0;
            }
        }
        input[i_0] = '\0'; // NULL 
        
        if(i_0 != 0){
            for(i_1 = 0;i_1 < number_of_commands; i_1++){
                if(match(input, commands[i_1])){
                    got_a_match = true;
                    command_is = commands[i_1];
                    break;
                }
            }
            if(command_is == "exit"){
                break; 
            }
            else if(match(input,"help")){
                i_0 = 0;
                cout << "Press Enter to see all commands or enter keyword.." << endl;
                cout << "help>> ";
                while((ch = getchar()) != '\n'){
                    if(space){
                        break;
                    }
                    if(ch == ' ' ){
                        space = true;
                    }
                    else{
                        temp[i_0] = ch;
                        i_0++;
                    }
                }
                temp[i_0] = '\0';
                if(i_0 != 0){
                    for(i_1 = 0;i_1 < number_of_commands; i_1++){
                        if(match(temp, commands[i_1])){
                            got_a_match = true;
                            command_is = commands[i_1];
                            break;
                        }
                    }
                    
                    if(got_a_match){
                        command_info(command_is);
                    }
                    else{
                        command_info("\0");
                    }
                }
                else{
                    command_info("\0");
                }
            }
            else if(got_a_match){
                switch(i_1){
                    case 2:cout << "ins";break;
                    default:break;
                }
                cout << endl;
            }
            else{
                cout << "Invalid Command " << input << endl;
                cout << "                ^" << endl;
                cout << "Try \"help\" ! " << endl;
            }
            line_no++;
        }
    }
    cout << "Thank You for using Quelisa." << endl;
    return 0;
}


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
        virtual const E& getData(int) const = 0;
        
        //clear all the data from the List
        virtual void clear() = 0;
        
        //insert a data in the List at current location
        virtual bool insert(const E& data) = 0;
        
        //delete a data at the current Location
        virtual E remove() = 0;
        
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
        const E& getData(int ind) const {
            return dataArray[ind];
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
        
        bool insert(const E& data){
            // if currentSize != arraySize
            if(currentSize < arraySize){
                dataArray[currentSize] = data;
                currentSize++;
                return true;
            }
            else{
                cout << "Queue limit Reached.." << endl;
                return false;
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
            cout << endl << "[ ";
            for(int i = currentSize-1;i>-1;i--){
                cout << dataArray[i] << " ";
            }
            cout << "]" << endl;
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
        virtual bool insert(const E &) = 0;
        
        //Remove the first element of the queue
        virtual E remove() = 0;
        
        // Return the length of the queue
        virtual int length() const = 0;
        
        //Return a copy of the first element
        virtual const E& FirstElement() const= 0;
        
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
        bool insert(const E &input){
        
            lastElement = QueueArray->NumberOfElements();
            return QueueArray->insert(input);
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
            return QueueArray->getData(firstElement);
        }
        void clearQueue(){
            QueueArray->clear();
        }
        // to print information
        void display(){
            QueueArray->display();
        }
};


/*
// Whenever a command is added,
// Increment number_of_commands.
*/

const int number_of_commands = 6;

const string commands[number_of_commands] = { "del", "add", "first", "clear", "disp", "exit"};

void command_info(string about){
    map <string, string> command_info;

    command_info.insert(pair <string, string> ("del", "Deletes current Element"));
    command_info.insert(pair <string, string> ("add", "Use `add [-operand]` `add 1` to add Element in Queue"));
    command_info.insert(pair <string, string> ("disp", "Displays Information" ));
    
    command_info.insert(pair <string, string> ("first", "Get First Element of the Queue" ));
    command_info.insert(pair <string, string> ("clear" , "Clears the Queue" ));
    command_info.insert(pair <string, string> ("exit", "Exits the program"));
    map <string, string> :: iterator itr;
    if(about == ""){
        for(itr = command_info.begin(); itr != command_info.end(); itr++){
            cout << "\t" << itr->first << " - " << itr->second << endl;
        }
    }
    else{
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


int main(){
    cout << "Quelisa 1.1.2 |Developed by Sanket Chaudhari|" << endl;
    cout << "type \"help\" to see command list." << endl;
    int size, line_no = 0, i_1;
    string command_is, username;
    char dummy, temp[20], ch;
    cout << "Username: "; cin >> username;
    cout << "Enter size of Queue: "; cin >> size;
    QueueArrayList <int> queue(size);
    scanf("%c", &dummy);
    bool space = false, start = false, end = false, got_a_match = false;
    while(true){
        cout << username << "[" << line_no << "]>> ";
             
        space = got_a_match = false;
        int i_0 = 0, queue_operand = 0;
        char queue_operator[80], operand_char_error;
        bool operand = false, operand_int_error = false;
        
        /* while loop for getting operator and operand */
        
        while((ch = getchar()) != '\n'){
        
            /* space variable checks whether input is operand or operator */
            if(space){
                if(ch == ' '){
                    break;
                }
                int temp_0 = ch - '0';
                if((temp_0 < 0 || temp_0 > 9) && not operand_int_error){
                    operand_char_error = ch;
                    operand_int_error = true;
                }
                queue_operand = 10*queue_operand + temp_0;
                i_0 += 1;
                operand = true;
            }
            else if(ch == ' '){
               space = true;
               i_0 = 0;
            }
            else{
                queue_operator[i_0] = ch;
                i_0 += 1;
                queue_operator[i_0] = '\0'; // NULL
                
            }
            if(ch == ' '){
                space = true;
                
                i_0 = 0;
            }
        }
        if(operand_int_error){
            cout << "Please Enter an Integer. Invalid character `" << operand_char_error << "` found !" << endl;
            continue;
        }
        /* Checks for opeartions and functions to call */
        if(i_0 != 0){
            for(i_1 = 0;i_1 < number_of_commands; i_1++){
                if(match(queue_operator, commands[i_1])){
                    got_a_match = true;
                    command_is = commands[i_1];
                    break;
                }
            }
            if(command_is == "exit"){
                break; 
            }
            else if(match(queue_operator,"help")){ /* Matches the function with pre-order operand */
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
            /*
            * Insert occurs only when operand is provided
            * and have space in Queue.
            */
                switch(i_1){
                    case 0: cout << "- " << queue.remove() << endl;break;
                    case 1: if(operand and queue.insert(queue_operand)){
                                cout << "+ " << queue_operand << endl;
                            }else if(!operand){
                                cout << "Provide an operand to perform operation." << endl;
                            };break;
                    case 2: cout << queue.FirstElement() << endl;break;
                    case 3: queue.clearQueue();break;
                    case 4: queue.display();break;
                    default:break;
                }
            }
            else{
                cout << "Invalid Command " << queue_operator << endl;
                cout << "                ^" << endl;
                cout << "Try \"help\" ! " << endl;
            }
            line_no++;
        }
    }
    cout << "Thank You for using Quelisa." << endl;
    return 0;
}


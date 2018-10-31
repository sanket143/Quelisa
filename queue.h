#include <iostream>

using namespace std;

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
            return currentLocation;
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



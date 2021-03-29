#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
using namespace std;
vector<pair<string, vector<int> > > result;
vector<pair<string, vector<string> > > test;
int arr[65][65];
int expect[65][65];
int tim[65][65];
int n;
struct element{
    int r;
    int c;
    int t;
    bool operator < (const element& n1) const{
        return t<n1.t;  
    }
    bool operator > (const element& n1) const{
        return t>n1.t;  
    }
    bool operator == (const element& n1) const{ //== not =
        return t==n1.t;  
    }
    element(int r=0,int c=0,int t=0):r(r),c(c),t(t){} //syntax
}arrayst [4230];


void read_csv(string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    //vector<pair<string, vector<int>>> result;

    // Create an input filestream
    ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Helper vars
    string line, colname;
    int val;
    string info;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        getline(myFile, line);

        // Create a stringstream from line
        stringstream ss(line);

        // Extract each column name
        while(getline(ss, colname, ';')){ //columns separated by ; not ,
            
            // Initialize and add <colname, int vector> pairs to result
            if (colname.compare("test_result")==0 || colname.compare("Name")==0 || colname.compare("id_Number")==0)
                { //id_Number needs to come in as string, if val, too big
                    vector<string> p;
                    test.push_back(make_pair(colname, p)); //syntax to make pair
                    //cout << colname;
                    
                    
                }
            else {
                vector<int> p;
                result.push_back(make_pair(colname, p));
                //cout << colname;
                }
            //cout << endl;
        }
        //cout << endl;
    }

    // Read data, line by line
    while(getline(myFile, line))
    {
        // Create a stringstream of the current line
        stringstream ss(line);
        
        // Keep track of the current column index
        int colIdx = 0;
        int t =0;
        // Extract each integer
        while(getline(ss, info, ';')){
            /*cout << info << endl;
            cout << colIdx << endl;
            cout << t << endl;
            cout << result.size() << endl;*/
            if (colIdx==0){
                test.at(0).second.push_back(info);
                if(ss.peek() == ';') ss.ignore();
                colIdx++;
                //cout << info << " ";
            }
            else if (colIdx==1){
                test.at(1).second.push_back(info);
                if(ss.peek() == ';') ss.ignore();
                colIdx++;
                //cout << info << " ";
            }
            else if (colIdx==5){
                test.at(2).second.push_back(info);
                if(ss.peek() == ';') ss.ignore();
                colIdx++;
                //cout << info << " ";
            }

            else {
                // Add the current integer to the 'colIdx' column's values vector
                stringstream degree(info);
                val = 0;
                degree >> val;
                //val = stoi(info);
                result.at(t).second.push_back(val);
                //cout << info << " ";
                //cout << endl;
                //cout << val << " ";
            
                // If the next token is a comma, ignore it and move on
                if(ss.peek() == ';') ss.ignore();
            
                // Increment the column index
                colIdx++;
                t++;
            }
            
        }
    }

    // Close file
    myFile.close();
}

void write_csv(string filename, vector<pair<string, vector<int>>> dataset,vector<pair<string, vector<string>>> tresult){
    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size
    
    // Create an output filestream object
    ofstream myFile(filename);
    
    // Send column names to the stream
    for(int j = 0; j < tresult.size(); ++j)
    {
        myFile << tresult.at(j).first;
        //if(j != dataset.size() - 1) 
        myFile << ";"; // No comma at end of line
    }
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ";"; // No comma at end of line
    }
    
    myFile << "\n";
    
    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < tresult.size(); ++j)
        {
            myFile << tresult.at(j).second.at(i);
            //if(j != tresult.size() - 1) 
            myFile << ";"; // No comma at end of line
        }

        for(int j = 0; j < dataset.size(); ++j)
        {
            if (dataset.at(j).second.at(i)==2000000001) myFile << "NULL";
            else { myFile << dataset.at(j).second.at(i);}
           
            if(j != dataset.size() - 1) myFile << ";"; // No comma at end of line
        }
        
        
        myFile << "\n";
    }
    // Close the file
    myFile.close();
}


void swap(element a [], int i, int j){  
    element temp = a[i];
    a[i]=a[j];
    a[j]=temp;
}

void maintainHeap (element arr[], int n, int i){  
    int c =0;
    while (2*i+2<=n){
        if (2*i+2 >= n){
            c = 2*i+1;
        }
        else {
            if (arr[2*i+2]<arr[2*i+1]){
            c = 2*i+2;
            }
            else {c=2*i+1;}
        }
        if (arr[c]<arr[i]){
            swap(arr,c,i);
            i = c;
        }
        else return;
    }
}

void extractMin(element arr[],int &n){ 
    element lastElement = arr[n-1];
    arr[0] = lastElement;
    n = n-1;
    maintainHeap(arr,n,0); 
}

void buildHeap (element arr[], int n){
    int k = (n/2)-1;
    for (int i = k; i>=0; i--){
        maintainHeap(arr,n,i);
    }
}

void insertNode(element arr[], int &n, element key){ 
    n = n+1; 
    arr[n-1] = key;
    buildHeap(arr,n);
}

element minimum (element arr[]){
    return arr[0];
}




void bfs(){
   
   while (n>0){
        element small = minimum (arrayst);
        extractMin(arrayst,n);
    
        int k = small.r;
        int p = small.c;
        //cout << k << " " << p << endl;
    
        if (k+1<=65 && arr[k+1][p]==0){
            tim[k+1][p]= min (tim[k+1][p],tim[k][p]+expect[k+1][p]);
            //n = sizeof(arrayst) / sizeof(arrayst[0]);  //no need this because insertNode already changes n 
            insertNode(arrayst, n, element (k+1, p, tim[k+1][p]));
            arr[k+1][p]=1;
        }
        if (k-1>0 && arr[k-1][p]==0){
            tim[k-1][p]= min(tim[k-1][p],tim[k][p]+expect[k-1][p]);
            //n = sizeof(arrayst) / sizeof(arrayst[0]);
            insertNode(arrayst, n, element (k-1, p, tim[k-1][p]));
            arr[k-1][p]=1;
        }
        if (p+1<=65 && arr[k][p+1]==0){
            tim[k][p+1]= min(tim[k][p+1],tim[k][p]+expect[k][p+1]);
            //n = sizeof(arrayst) / sizeof(arrayst[0]);
            insertNode(arrayst, n, element (k, p+1, tim[k][p+1]));
            arr[k][p+1]=1;
        } 
        if (p-1>0 && arr[k][p-1]==0){
            tim[k][p-1]= min(tim[k][p-1],tim[k][p]+expect[k][p-1]);
            //n = sizeof(arrayst) / sizeof(arrayst[0]);
            insertNode(arrayst, n, element (k, p-1, tim[k][p-1]));
            arr[k][p-1]=1;
        } 
        //n = sizeof(arrayst) / sizeof(arrayst[0]);
        buildHeap (arrayst, n);
   }
       
}

int main() {
   
    read_csv("audiences_info_6.csv");
    

    // Write to another file to check that this was successful
    //write_csv("three_cols_copy.csv", three_cols);
    //write_csv("ones_copy.csv", ones);
    for (int i=0; i<=65; i++){
        for (int j=0; j<=65; j++){
            arr[i][j]=-1;
            expect[i][j] =-1;
        }
    }
    //memset(arr,-1,sizeof(arr));
    //memset(expect,-1,sizeof(expect));
    

    for (int i=0; i<result.at(0).second.size(); i++){
        if (test.at(2).second[i]=="True"){
            arr[result.at(0).second[i]][result.at(1).second[i]]=1;
        } 
        else {
            arr[result.at(0).second[i]][result.at(1).second[i]]=0;
        }
    }
    for (int i=0; i<result.at(0).second.size(); i++){
        expect[result.at(0).second[i]][result.at(1).second[i]]=result.at(3).second[i]*0.06;
    }

    for (int i=0; i<=65; i++){
        for (int j=0; j<=65; j++){
            if (arr[i][j]==1) {
                tim[i][j]=0;
            }
            else {tim[i][j] = 2000000001;}
        }
    }
    int number =0;
    n=0;
    for (int i=1; i<=65; i++){
        for (int j=1; j<=65; j++){
            if (arr[i][j]==1)
            {
                arrayst[number] = element (i, j, 0);
                n++;
                number++;
                
            }
        }
    }
    //cout << "h" << endl;

    bfs();
    //cout << "e" << endl;

    int ret =-1;
    for (int i=1; i<=65; i++){
        for (int j=1; j<=65; j++){
             if (tim[i][j]!= 2000000001 && tim[i][j]>ret){
                 ret = tim[i][j];
             }
        }
    }
    cout << ret << endl;//question 1

    vector<int> expt (result.at(0).second.size());
    result.push_back(make_pair("ExposureTime", expt));
    for (int i=1; i<=65; i++){
        for (int j=1; j<=65; j++){
            for (int k=0; k<=result.at(0).second.size(); k++){
                if (result.at(0).second[k]==i && result.at(1).second[k]==j){
                    result.at(4).second[k]=tim[i][j];
                }
            }
        }
    }

    write_csv("alert_info_6.csv", result, test);

    return 0;
}

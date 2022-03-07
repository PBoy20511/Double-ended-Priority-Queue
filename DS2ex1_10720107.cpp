//10720107 陳丕中 
#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include <cmath>

using namespace std ;

typedef struct CT {
	string content ; // All the content from the school
	int numStudent ; // number of numStudent
} CollegeType ;

class ClassList {
	
	vector< CollegeType > collegeSet ; 
	//vector< int > heapTree;
	string fileNum ; 
	string mission;
	int root;
	int r_bottom;
	int l_bottom;
	int L;
	
	public:
		
	ClassList(){
		fileNum = "" ;
		root=0;
		r_bottom=0;
		l_bottom=0;
	} // ClassList
	
	bool Load( string fileName ) ;
	int compare( int A, int B );
  void Print();
  void printArray(vector<int> &hT) ;
  
	void MissionOne();
	void Maxinsert(vector<int> &hT, int newNum) ;
	void Maxheapify(vector<int> &hT, int i);
	int HeapLeftmostBottom(vector<int> &hT);
	void PrintInfo();
	
	void MissionTwo();
	
}; // class ClassList

bool ClassList::Load( string fileName ) {
    // Load a file, turn it into a vector
    
    fileNum = fileName ;
    FILE *infile = NULL ;
    bool success = false ;
    fileName = "input" + fileName + ".txt" ;
    //fileName = "input.txt" ;
    infile = fopen(fileName.c_str(), "r" ) ;

	if ( infile == NULL )
		;
	else{

        char tempChar ;
        for ( int i = 0 ; i < 3 ; i++ )
        	while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' )
            	;

        CollegeType aCollege ;
        aCollege.content = "" ;
        aCollege.numStudent = 0 ;
        
		int numTab = 0 ;
		string numStudent = "" ;
		
        while ( fscanf( infile, "%c", &tempChar ) != EOF ) {
        	aCollege.content = aCollege.content + tempChar ;
        	while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' ) {
        		aCollege.content = aCollege.content + tempChar ;
        		if ( tempChar == '\t' )
        			numTab++ ;
        		else if ( numTab == 6 )
        			numStudent = numStudent + tempChar ;
        	} //while
        		
        	aCollege.numStudent = atoi( numStudent.c_str() ) ;
        	
          collegeSet.push_back( aCollege ) ;
            
          aCollege.content = "" ;
          aCollege.numStudent = 0 ;
          numStudent = "" ;
          numTab = 0 ;
            
        } // while

        success = true ;
        fclose( infile ) ;

	} // else

	return success ;

} // Load

void ClassList::printArray(vector<int> &hT){
  for (int i = 0; i < hT.size(); ++i)
    cout << hT[i] << " ";
  cout << "\n";
} // printArray

void ClassList::PrintInfo(){
	cout << "\n<" << mission << ">\n" ;
  cout << "root: [" << root+1 << "] " << collegeSet[root].numStudent <<"\n";
	cout << "bottom: [" << r_bottom+1 << "] " << collegeSet[r_bottom].numStudent <<"\n";
	cout << "leftmost bottom: [" << l_bottom+1 << "] " << collegeSet[l_bottom].numStudent <<"\n";
}//PrintInfo

int ClassList::compare( int A, int B ){ // A>B:1  A<B:0  A==B:-1
	if( collegeSet[A].numStudent > collegeSet[B].numStudent ){
		return 1;
	} // if
	else if( collegeSet[A].numStudent < collegeSet[B].numStudent ){
		return 0;
	} // else if
	else{
		return -1;
	} // else
}//compare

void ClassList::Maxheapify(vector<int> &hT, int i){
  int size = hT.size();
  int largest = i; // largest用來記錄包含root與child, 三者之中Key最大的node
  int l = 2 * i + 1;// 取得left child
  int r = 2 * i + 2;// 取得right child
  if (l < size && compare(hT[l], hT[largest])==1)//hT[l] > hT[largest]
    largest = l;
  if (r < size && compare(hT[r], hT[largest])==1)
    largest = r;

  if (largest != i){ // 如果目前root的Key不是三者中的最大
    int temp = hT[i];
    hT[i] = hT[largest];
    hT[largest] = temp;// 就調換root與三者中Key最大的node之位置
    
    Maxheapify(hT, largest);  // 調整新的subtree成Max Heap
  }
} // heapify Max

void ClassList::Maxinsert(vector<int> &hT, int newNum){
  int size = hT.size();
  if (size == 0){
    hT.push_back(newNum);
  }//if
  else{
    hT.push_back(newNum);
    for (int i = size / 2 ; i >= 0; i--){
      Maxheapify(hT, i);
    }//for
  }//else
  
} // insert

int ClassList::HeapLeftmostBottom(vector<int> &hT){
  int index=0;
  int i=0;
  while( index < hT.size() ){
  	i=index;
		index=index*2+1;
	}//while
	
	return hT[i];
}//findHeapBottom

void ClassList::MissionOne(){
  vector<int> heapTree;
  mission = "Max heap";
  
  for( int i=0; i<collegeSet.size() ; i++ ){
  	Maxinsert(heapTree, i);
	}//for

  root = heapTree[0];
  r_bottom = heapTree[heapTree.size()-1];
  l_bottom = HeapLeftmostBottom(heapTree);
  PrintInfo();

} // MissionOne

typedef struct deapNode{
	int key;
	int index;
}dN;

class Deap{

public: 
vector<dN> Deap;
int L=1; // location of index

void initTree(int size){
	dN temp;
	for( int i=0; i<=size+1; i++ ){
		Deap.push_back(temp);
	}//for
} // initTree()

dN LeftmostBottom(){
  int index=0;
  int i=0;
  while( index < Deap.size() ){
  	i=index;
		index=index*2+1;
	}//while
	// 0 0 1 2 3 4 5 6 7 8
	return Deap[i];
}//findHeapBottom
 
string Position(int index) { // start from the third node
  while(index > 3){
   	index/=2;
	} //while  
  //return index; //2 left heap, 3 right-max heap
  if( index==2 ){
  	return "Min";
	}//if
	else{
		return "Max";
	}//else
} // Judge


//每層兩兩節點的間距為2^(樹層-2)，min邊：節點-間距
int CorrespondingMin(int index) {
  int i=index;
	int space=1;
  
  while(index > 3){
    index/=2;
    space*=2; // how many level
	} //while 
	
  return i-space;
} // MinPartner

//max邊：節點+間距
int CorrespondingMax(int index) { // index is the current index(which is L)
  if(index == 2) { //the first one
  	return 2; //return itself because it got nothing left(first one)
	}//if
		  
  int i=index;
	int space=1;
  
  while(index > 3){
    index/=2;
    space*=2; // how many level
	} //while   
	
  if(i+space > L) {
  	return (i+space)/2;
	}//if
	
  return i+space;
} // MaxPartner

void MinInsert(int index, int newNum) {

  int parent=index/2;
  while(parent > 1 && Deap[parent].key > newNum ){ 
    Deap[index].key=Deap[parent].key; 
    Deap[index].index=Deap[parent].index;
		index=parent;
		parent=index/2; 
	} //while  
  Deap[index].key=newNum; 
  Deap[index].index = L;
    
} // minInsert

void MaxInsert(int index, int newNum) {
	
  int parent=index/2;
  while(parent > 1 && Deap[parent].key < newNum){ 
    Deap[index].key=Deap[parent].key; 
    Deap[index].index=Deap[parent].index;
		index=parent;
		parent=index/2;
	}//while   
  Deap[index].key=newNum; 
  Deap[index].index = L;
  
}//MaxInsert

void DeapInsert(int newNum) {
    L++;
    if(L==2){
        Deap[2].key=newNum;
        Deap[2].index = L;
        return;
    }//if
    int pIndex=L;
		int cIndex; // corresponding index

  string position=Position(pIndex);
  
  if( position=="Max" ){
  	cIndex = CorrespondingMin(pIndex); // index
  	
  	if(newNum < Deap[cIndex].key){ 
      Deap[pIndex].key=Deap[cIndex].key;
      Deap[pIndex].index=Deap[cIndex].index;
			MinInsert(cIndex, newNum);
		}//if
    else 
			MaxInsert(pIndex, newNum);
	}//if
	else if( position=="Min" ){
	  cIndex=CorrespondingMax(pIndex);
	  
    if(newNum > Deap[cIndex].key){ 
      Deap[pIndex].key=Deap[cIndex].key; 
      Deap[pIndex].index=Deap[cIndex].index;
			MaxInsert(cIndex, newNum);
		} //if 
    else 
			MinInsert(pIndex, newNum);
	} // else if
	
	
} // Deap_Insert

void DeapDone(){
	Deap.erase(Deap.begin());

}//DeapDone

void Print(){
	
	cout << "\n<DEAP>";
	dN l_bottom = LeftmostBottom();
	cout << "\nBottom[" << Deap[Deap.size()-1].index-1 << "]: "<< Deap[Deap.size()-1].key;
	cout << "\nLeftMost bottom:["<<  l_bottom.index-1<< "]:" << l_bottom.key ;
	cout << "\n";

} // Print


};//Deap

void ClassList::MissionTwo(){
  Deap deapTree;
  deapTree.initTree(collegeSet.size());
  
  for( int i=0; i<collegeSet.size() ; i++ ){
  	deapTree.DeapInsert(collegeSet[i].numStudent);
	}//for
	
  deapTree.DeapDone();
  deapTree.Print();

} // MissionTwo

int main() {
	string fileNum;
	int cmd;
	
	cout << "> Welcome!\n> Input the cmd ([0]Quit [1]MaxHeap [2]DEAP):\n> ";
	cin >> cmd;
	while( cmd != 0 ){
		
		if( cmd==1 ){
			cout << "> Enter FileNum:\n> ";
			cin >> fileNum;
			ClassList inputData;
			if( inputData.Load( fileNum ) ){
			  inputData.MissionOne();
		  }//if
		  else{
		  	cout << "> No Such Input File!!\n";
			} //else
		} // if
		else if( cmd==2 ){
			cout << "> Enter FileNum:\n> ";
			cin >> fileNum;
			ClassList inputData;
			if( inputData.Load( fileNum ) ){
			  inputData.MissionTwo();
		  }//if
		  else{
		  	cout << "> No Such Input File!!\n";
			} //else
		}//if
		else{
			cout << "No such cmd!\n";
		}//else
	
	
  	cout << "\n\n> Input the cmd ([0]Quit [1]MaxHeap [2]DEAP):\n> ";
		cin >> cmd; 
	}//while 
	
	cout <<"> Bye Bye!";
} //main

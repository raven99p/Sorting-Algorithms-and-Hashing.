 //Binary Search Tree Program
    #include <iostream>
    #include <cstdlib>
    #include <fstream>
    #include <iomanip>
    #include <stdio.h>
    #include <vector>
    const int PRIME = 7; 
    using namespace std;
    typedef string treeType;
    
    
///////////////////////////GENERAL UTILITY FUNCTIONS//////////////////
void printStudentInfo (string AM, string First_name, string Last_name, double grade) // needs to be before the print functions of the BST
{			 
	cout<< left << setw(9) 
	<< AM << setw(13) 
	<< First_name << setw(17) 
	<< Last_name << setw(5) << setprecision(2) << right 
	<< grade << endl;
}
void printTitles()
{
	cout<< left << setw(9) 
	<< "AM" << setw(13) 
	<< "FIRST NAME" << setw(17) 
	<< "LAST NAME" 
	<< "GRADE" << endl 
	<< fixed << showpoint;
}


//////////////////END OF GENERAL UTILITY FUNCTIONS//////////////////
    class Student{
    	private:
    		string AM, firstName, lastName;
    		double grade;
    	public:
    		Student();
    		Student(string AM, string firstName, string lastName, double grade);
    		string getAM();
    		string getFirstName();
    		string getLastName();
    		double getGrade();
    		void setAM(string newAM);
    		void setFirstName(string newFirstName);
    		void setLastName(string newLastName);
    		void setGrade(double newGrade);
	};
	
	class BinarySearchTree
	{
		private:
			struct tree_node
			{
				tree_node* left;
				tree_node* right;
				//treeType data
				Student data;
			};
			tree_node* root;
		public:
			
			BinarySearchTree()
			{
				root = NULL;
			}
			bool isEmpty() const { return root==NULL; }
			void print_inorder();
			void inorder(tree_node*);
			void print_preorder();
            void preorder(tree_node*);
            void print_postorder();
            void postorder(tree_node*);
            void insert_AM_wise(Student);
            void insert_grade_wise(Student);
            void remove(string);
            void search(string key);
            void changeFirstName(string key, string newfirstname);
            void changeLastName(string key, string newlastname);
            void changeGrade(string key, double newgrade);
            //grade_wise BST functions
            double find_lowest_grade();
            double find_highest_grade();
            void find_students_with_lowest_grade(tree_node*, double);
            void print_students_with_lowest_grade(double);
            void find_students_with_highest_grade(tree_node*, double);
            void print_students_with_highest_grade(double);
	};
	
	//Student empty constructor
	Student::Student()
	{
	}
	
	Student::Student(string newAM, string newFirstName, string newLastName, double newGrade)
	{
		AM = newAM;
		firstName = newFirstName;
		lastName = newLastName;
		grade = newGrade;
	}
	
	////////// getters //////////
	string Student::getAM() {
		return AM;
	}
	string Student::getFirstName() {
		return firstName;
	}
	string Student::getLastName() {
		return lastName;
	}
	double Student::getGrade() {
		return grade;
	}
	///////// setters //////////
	void Student::setAM(string newAM) {
		AM = newAM;
	}
	void Student::setFirstName(string newFirstName) {
		firstName = newFirstName;
	}
	void Student::setLastName(string newLastName) {
		lastName = newLastName;
	}
	void Student::setGrade(double newGrade) {
		grade = newGrade;
	}
	/*-----------------------------/
	/ Smaller elements go left    /
	/ larger elements go right   /
/*--------------- BST functions -----------------------*/
////////insert, remove//////////////
	void BinarySearchTree::insert_AM_wise(Student s)
    {
        tree_node* t = new tree_node; //make new node
        tree_node* parent;
        t->data = s; //the data of the new node is that of the Student s
        t->left = NULL; //ensure it has no left child
        t->right = NULL; //ensure it has no right child
        parent = NULL; //ensure it has no parent
        // is this a new tree?
        if(isEmpty()) root = t; //if it is a new tree, make this the root
        else
        {
            //Note: ALL insertions are as leaf nodes
            tree_node* curr;
            curr = root;
            // Find the Node's parent
            while(curr)
            {
                parent = curr;
                if(t->data.getAM() > curr->data.getAM()) curr = curr->right; //if the parent's AM is "bigger" than the current's, put the current on the right
                else curr = curr->left;
            }
            if(t->data.getAM() < parent->data.getAM()) //if t's AM is "smaller" make it the left node of the parent
               parent->left = t; 
            else
               parent->right = t;
        }
    }
    void BinarySearchTree::insert_grade_wise(Student s) //students with the same grade as the last one, go left.
    {
        tree_node* t = new tree_node; //make new node
        tree_node* parent; 
        t->data = s; //the data of the new node is that of the Student s
        t->left = NULL; //ensure it has no left child
        t->right = NULL; //ensure it has no right child
        parent = NULL; //ensure it has no parent
        // is this a new tree?
        if(isEmpty()) root = t; //if it is a new tree, make this the root
        else
        {
            //Note: ALL insertions are as leaf nodes
            tree_node* curr;
            curr = root;
            // Find the Node's parent
            while(curr)
            {
                parent = curr;
                if(t->data.getGrade() > curr->data.getGrade()) curr = curr->right; //if the parent's grade is bigger than the current's, put the current on the right
                else curr = curr->left;
            }
            if(t->data.getGrade() <= parent->data.getGrade()) //if t's grade is smaller than or equal make it the left node of the parent
               parent->left = t; 
            else
               parent->right = t;
        }
    }
    void BinarySearchTree::remove(string p)
    {
        //Locate the element
        bool found = false;
        if(isEmpty())
        {
            cout<<" This Tree is empty! "<<endl;
            return;
        }
        tree_node* curr;
        tree_node* parent;
        curr = root;
        while(curr != NULL)
        {
             if(curr->data.getAM() == p)
             {
                found = true;
                break;
             }
             else
             {
                 parent = curr;
                 if(p>curr->data.getAM()) curr = curr->right;
                 else curr = curr->left;
             }
        }
        if(!found)
    		 {
            cout<<" Data not found! "<<endl;
            return;
        }
    		 // 3 cases :
        // 1. We're removing a node with a single child
        // 2. We're removing a leaf node
        // 3. we're removing a node with 2 children
        
        // 1. Node with single child
        if((curr->left == NULL && curr->right != NULL) || 
		   (curr->left != NULL && curr->right == NULL)) //if one of the two sides are empty
        {
           if(curr->left == NULL && curr->right != NULL) //right child is present, no left child
           {
               if(parent->left == curr)
               {
                 parent->left = curr->right;
                 delete curr;
               }
               else
               {
                 parent->right = curr->right;
                 delete curr;
               }
           }
           else // left child present, no right child
           {
              if(parent->left == curr)
               {
                 parent->left = curr->left;
                 delete curr;
               }
               else
               {
                 parent->right = curr->left;
                 delete curr;
               }
           }
         return;
        }
    	//2. We're looking at a leaf node
    		 if( curr->left == NULL && curr->right == NULL)
        {
            if(parent->left == curr) parent->left = NULL;
            else parent->right = NULL;
    		 		 delete curr;
    		 		 return;
        }
        //3. Node with 2 children
        // replace node with smallest value in right subtree
        if (curr->left != NULL && curr->right != NULL)
        {
            tree_node* chkr;
            chkr = curr->right;
            if((chkr->left == NULL) && (chkr->right == NULL)) //right child of curr node is a leaf
            {
                curr = chkr;
                delete chkr;
                curr->right = NULL;
            }
            else // right child has children
            {
                //if the node's right child has a left child
                // Move all the way down left to locate smallest element
                if((curr->right)->left != NULL)
                {
                    tree_node* lcurr;
                    tree_node* lcurrp;
                    lcurrp = curr->right;
                    lcurr = (curr->right)->left;
                    while(lcurr->left != NULL) //find the leftdown-most child
                    {
                       lcurrp = lcurr; //make lcurrp be (curr->right)->left
                       lcurr = lcurr->left; // add a "->left" every time to reach deeper
                    }
    		curr->data = lcurr->data; //the data of curr becomes the data of the found leaf
                    delete lcurr; 
                    lcurrp->left = NULL; // we delete the leftdown-most leaf we found
               }
               else
               {
                   tree_node* tmp;
                   tmp = curr->right; 
                   curr->data = tmp->data;
    	    	   curr->right = tmp->right;
                   delete tmp;
               }
            }
    		 return;
        }
    }
    /////////////grade-wise tree functions////////
    void BinarySearchTree::print_students_with_lowest_grade(double lowestGrade) //OK
    {
    	find_students_with_lowest_grade(root,lowestGrade);
	}
	void BinarySearchTree::find_students_with_lowest_grade(tree_node* p, double lowestGrade) //OK
	{
		if(p != NULL)
        {	
        	if(p->left) find_students_with_lowest_grade(p->left, lowestGrade);
        	if(p->data.getGrade()==lowestGrade) 
			{
            printStudentInfo(p->data.getAM(),p->data.getFirstName(),p->data.getLastName(),p->data.getGrade());
			}
			if(p->right) find_students_with_lowest_grade(p->right, lowestGrade);
        }
        
    }
    void BinarySearchTree::print_students_with_highest_grade(double highestGrade) //OK
    {
    	find_students_with_highest_grade(root, highestGrade);
	}
	void BinarySearchTree::find_students_with_highest_grade(tree_node* p, double highestGrade) //OK
	{
		if(p != NULL)
        {	
        	if(p->right) find_students_with_lowest_grade(p->right, highestGrade);
        	if(p->data.getGrade()==highestGrade) 
			{
            printStudentInfo(p->data.getAM(),p->data.getFirstName(),p->data.getLastName(),p->data.getGrade());
			}
			if(p->left) find_students_with_lowest_grade(p->left, highestGrade);
        }
	}
    /////functions to find the lowest/highest grades//////////////
	double BinarySearchTree::find_lowest_grade()
	{  
		tree_node* curr = root;
		/* loop down to find the leftmost leaf */
		while (curr->left != NULL)  
		{  
		    curr = curr->left;
		}  
		return(curr->data.getGrade());
	} 
	double BinarySearchTree::find_highest_grade()
	{  
		tree_node* curr = root;
		/* loop down to find the leftmost leaf */
		while (curr->right != NULL)  
		{  
		    curr = curr->right;
		}  
		return(curr->data.getGrade());
	}
	////////traversals functions////////////////
    void BinarySearchTree::print_inorder() 
    {
      inorder(root);
    }
    void BinarySearchTree::inorder(tree_node* p) 
    {
        if(p != NULL)
        {
            if(p->left) inorder(p->left); //if current node has a left child, call the function for that child
            printStudentInfo(p->data.getAM(),p->data.getFirstName(),p->data.getLastName(),p->data.getGrade()); 
            if(p->right) inorder(p->right); 
        }
        else return;
    }
    void BinarySearchTree::print_preorder() 
    {
        preorder(root);
    }
    void BinarySearchTree::preorder(tree_node* p) 
    {
        if(p != NULL)
        {
            printStudentInfo(p->data.getAM(),p->data.getFirstName(),p->data.getLastName(),p->data.getGrade());
            if(p->left) preorder(p->left);
            if(p->right) preorder(p->right);
        }
        else return;
    }
    void BinarySearchTree::print_postorder() 
    {
        postorder(root);
    }
    void BinarySearchTree::postorder(tree_node* p)
    {
        if(p != NULL)
        {
            if(p->left) postorder(p->left);
            if(p->right) postorder(p->right);
            printStudentInfo(p->data.getAM(),p->data.getFirstName(),p->data.getLastName(),p->data.getGrade());
        }
        else return;
    }
    /////search, change, insert functions/////////////////
    void BinarySearchTree::search(string key)
    {
        bool found = false;
        if(isEmpty())
        {
            cout<<" This Tree is empty! "<<endl;
            return;
        }
        tree_node* curr;
        tree_node* parent;
        curr = root;
        while(curr != NULL)
        {
             if(curr->data.getAM() == key)
             {
                found = true;
                cout << "The info for " << key << " is:"<<endl;
                printStudentInfo(curr->data.getAM(),curr->data.getFirstName(),curr->data.getLastName(),curr->data.getGrade());
                break;
             }
             else
             {
                 parent = curr;
                 if(key>curr->data.getAM()) curr = curr->right;
                 else curr = curr->left;
             }
        }
        if(!found)
    		 {
            cout<<" Data not found! "<<endl;
            return;
        }
    }
    void BinarySearchTree::changeFirstName(string p, string newFirstName) 
	{
        bool found = false;
        if(isEmpty())
        {
            cout<<" This Tree is empty! "<<endl;
            return;
        }
        tree_node* curr;
        tree_node* parent;
        curr = root;
        while(curr != NULL)
        {
             if(curr->data.getAM() == p)
             {
                found = true;
                break;
             }
             else
             {
                 parent = curr;
                 if(p>curr->data.getAM()) curr = curr->right;
                 else curr = curr->left;
             }
        }
        if(!found)
    		 {
            cout<<" Person not found. "<<endl;
            return;
        }
        //change the first name associated with the node
        curr->data.setFirstName(newFirstName);
        cout<< "First name changed successfully. New info for "<<p<<" is:"<<endl;
        printStudentInfo(curr->data.getAM(),curr->data.getFirstName(),curr->data.getLastName(),curr->data.getGrade());
    }
    void BinarySearchTree::changeLastName(string p, string newLastName) 
	{
        bool found = false;
        if(isEmpty())
        {
            cout<<" This Tree is empty! "<<endl;
            return;
        }
        tree_node* curr;
        tree_node* parent;
        curr = root;
        while(curr != NULL)
        {
             if(curr->data.getAM() == p)
             {
                found = true;
                break;
             }
             else
             {
                 parent = curr;
                 if(p>curr->data.getAM()) curr = curr->right;
                 else curr = curr->left;
             }
        }
        if(!found)
    		 {
            cout<<" Person not found. "<<endl;
            return;
        }
        //change the first name associated with the node
        curr->data.setLastName(newLastName);
        cout<< "Last name changed successfully. New info for "<<p<<" is:"<<endl;
        printStudentInfo(curr->data.getAM(),curr->data.getFirstName(),curr->data.getLastName(),curr->data.getGrade());
    }
    void BinarySearchTree::changeGrade(string p, double newGrade) 
	{
        bool found = false;
        if(isEmpty())
        {
            cout<<" This Tree is empty! "<<endl;
            return;
        }
        tree_node* curr;
        tree_node* parent;
        curr = root;
        while(curr != NULL)
        {
             if(curr->data.getAM() == p)
             {
                found = true;
                break;
             }
             else
             {
                 parent = curr;
                 if(p>curr->data.getAM()) curr = curr->right;
                 else curr = curr->left;
             }
        }
        if(!found)
    		 {
            cout<<" Person not found. "<<endl;
            return;
        }
        //change the first name associated with the node
        curr->data.setGrade(newGrade);
        cout<< "Grade changed successfully. New info for "<<p<<" is:"<<endl;
        printStudentInfo(curr->data.getAM(),curr->data.getFirstName(),curr->data.getLastName(),curr->data.getGrade());
    }
    void fillTree( BinarySearchTree *b)
    {
        ifstream file;
        file.open("foitites.txt");
        if(!file) {
            cout<<" Error opening file. " << endl;
        }
        //variables used to load data into the tree
        string AM, firstName, lastName;
        double grade;
        Student s;
        while(file >> AM >> firstName >> lastName >> grade)
        {
            s.setAM(AM);
            s.setFirstName(firstName);
            s.setLastName(lastName);
            s.setGrade(grade);
          /*  cout 
			<< s.getAM() << "  " 
			<< s.getFirstName() << "  " 
			<< s.getLastName() << "  "
			<< s.getGrade() <<endl; */ //just to ensure that every entry is takes in correctly
            (*b).insert_AM_wise(s);
            
        }
        file.close();	
    }
    void fill_tree_grade_wise( BinarySearchTree *b) 
    {
        ifstream file;
        file.open("foitites.txt");
        if(!file) {
            cout<<" Error opening file. " << endl;
        }
        //variables used to load data into the tree
        string AM, firstName, lastName;
        double grade;
        Student s;
        while(file >> AM >> firstName >> lastName >> grade)
        {
            s.setAM(AM);
            s.setFirstName(firstName);
            s.setLastName(lastName);
            s.setGrade(grade);
            
            (*b).insert_grade_wise(s);
        }
        file.close();	
    }
/////////////////////HASHING PART UTILITY FUNCTIONS///////////////////////////////////////////////
int convertToASCII(string word) //OK
{
	int key = 0;
    for (int i = 0; i < word.length(); i++)
    {
        char x = word.at(i);
        key = key + int(x);
        //cout << int(x) << endl;
    }
    return key;
}
void print2DVector(vector<vector<int> > vec) //OK
{
	for(int i=0; i< vec.size(); i++)
	{
		cout<<endl;	
		
		for(int j=0; j< vec[i].size(); j++)
		{
			cout<<vec[i][j]<<" ";
		}
	}
}
void print_hash_table(vector<vector<Student> > vec) //OK
{
	for(int i=0; i< vec.size(); i++)
	{
		cout<<endl;	
		cout<<" "<<i<<". ";
		for(int j=0; j< vec[i].size(); j++)
		{
			cout<<vec[i][j].getAM()<<" ";
		}
	}
	cout<<endl;
}
void fillHashTable(vector< vector<Student> >& hash_table) //OK
{
		//opening the file//
		ifstream myFile;
        myFile.open("foitites.txt");
        int thisRow;
        
        //variables used to load data into the hash table
		string AM, First_name, Last_name;
		double grade;
		Student s;
		
        
        if (!myFile)
		{
			cout<<"unable to open file ";
			exit(1);	
		} 
		while (myFile >> AM >> First_name >> Last_name >> grade )
		{
			thisRow = convertToASCII(AM) % PRIME ; //assigning the row to be the ASCII sum of the AM mod the PRIME
			while(hash_table.size()<=thisRow)		
			hash_table.push_back(vector<Student>()); //mandatory push_back to make new row
		}	
	myFile.clear();
	myFile.seekg(0);
	
        
		while (myFile >> AM >> First_name >> Last_name >> grade ) //while we're reading from the file
		{
			int i=0;
			thisRow = convertToASCII(AM) % PRIME ; 
			s.setAM(AM);
    		s.setFirstName(First_name);
    		s.setLastName(Last_name);
    		s.setGrade(grade);		
			hash_table[thisRow].push_back(s);

		}	
	myFile.close();
}
void Insert_Student(vector< vector<Student> >& hash_table,string AM ,string First_name,string Last_name,double grade)
{
	int That_Row;
	That_Row = convertToASCII(AM) % PRIME;
	Student ss;
	ss.setAM(AM);
    ss.setFirstName(First_name);
    ss.setLastName(Last_name);
    ss.setGrade(grade);		
	hash_table[That_Row].push_back(ss);
		
}
/////////////////////////END OF UTILITY FUNCTIONS///////////////////////////////
    
int main()
    {
    	int choice;
    	while(1)
		{
    	   cout<<"-------------------------------------------------- "<<endl;
    	   cout<<"Welcome to The Project. May the force be with you."<<endl;
    	   cout<<"-------------------------------------------------- "<<endl;
           cout<<"1. Load the file in a Binary Search Tree AM-wise"<<endl;
           cout<<"2. Load the file in a Binary Search Tree grade-wise"<<endl;
           cout<<"3. Load the file using Hashing chains "<<endl;
           
           cout<<"Enter your choice : ";
           cin>>choice;
           
           
		   switch(choice){
////////////////////////////////////////////BST//////////////////////////////////////////////////////////	   	
		   			case 1 : {
		   				
							bool stillRunning = true;
							BinarySearchTree b;
	    					string AM, firstName, lastName;
    						double grade;
    						int ch;
    						string yesOrNo;
    						Student tmp;
					    	Student tmp1;
					    	fillTree(&b);
					    	cout<<" In-Order Traversal "<<endl;
                        	cout<<" -------------------"<<endl;
                        	printTitles();
					    	b.print_inorder();
					   	
					    	while(stillRunning)
       						{
         						cout<<endl<<endl;
								cout
								<<" Binary Search Tree Operations "<<endl
           						<<" ----------------------------- "<<endl
           						<<" 0. Search             "<<endl
           						<<" 1. Insertion/Creation "<<endl
           						<<" 2. In-Order Traversal "<<endl
           						<<" 3. Pre-Order Traversal "<<endl
           						<<" 4. Post-Order Traversal "<<endl
           						<<" 5. Removal "<<endl
           						<<" 6. Change a student's info "<<endl
           						<<" 7. Return to main menu "<<endl
           						<<" 8. Exit "<<endl
           						<<" Enter your choice : ";
           						cin>>ch;
           

           					switch(ch) //switch for BST
           					{
								case 0 : {
											cout <<" Enter the AM of the student to search for: "<<endl;
										 	cin>>AM;
									     	b.search(AM);
                        				break; //break of case 1.0
								}
               					case 1 : {
								   			cout<<" Enter AM to be inserted: ";
                        					cin>>AM;
	                        				cout << endl << " Enter first name: " << endl;
	                        				cin >> firstName;
	                        				cout << endl << " Enter last name: ";
	                        				cin>>lastName;
	                        				cout << endl << " Enter grade: " << endl;
	                        				cin >> grade;
	                        				tmp.setAM(AM);
	                        				tmp.setFirstName(firstName);
	                        				tmp.setLastName(lastName);
	                        				tmp.setGrade(grade);
	                        				b.insert_AM_wise(tmp);
	                        			break;//break of case 1.1
								}
               					case 2 : {
										   		cout<<endl;
		                        				cout<<" In-Order Traversal "<<endl;
		                        				cout<<" -------------------"<<endl;
												printTitles();
		                        				b.print_inorder();
		                        		break;//break of case 1.2
                        		}
               					case 3 : {
								   			cout<<endl;
                        					cout<<" Pre-Order Traversal "<<endl;
                        					cout<<" -------------------"<<endl;
                        					printTitles();
                        					b.print_preorder();
                        				break;//break of case 1.3
                        		}
               					case 4 : {	
								   			cout<<endl;
                        					cout<<" Post-Order Traversal "<<endl;
                        					cout<<" --------------------"<<endl;
                        					printTitles();
                       						b.print_postorder();
                        				break;//break of case 1.4
                        		}
               					case 5 : {
								   			cout<<" Enter data to be deleted : ";
                        					cin>>AM;
                        					b.remove(AM);
                        				break;//break of case 1.5
                        		}
           						case 6 : {
								   			cout<<" Enter the AM of the person whose info you wish to change: " <<endl;
                        					cin>>AM;
                        					cout<<"Do you want to change his first name? Y/N :";
                        				while(1){
                        					cin>>yesOrNo;
                        					if( yesOrNo == "Y" || yesOrNo == "y" || yesOrNo == "N" || yesOrNo == "n") 
                        						break;
											}
                        					if (yesOrNo == "Y" || yesOrNo == "y"){
												cout<<"Enter the new first name: ";
												cin>>firstName;
												b.changeFirstName(AM,firstName);
											}
											cout<<endl<<"Do you want to change his last name? Y/N :";
                        				while(1){
                        					cin>>yesOrNo;
                        					if( yesOrNo == "Y" || yesOrNo == "y" || yesOrNo == "N" || yesOrNo == "n") 
                        						break;
											}
                        					if (yesOrNo == "Y" || yesOrNo == "y"){
												cout<<"Enter the new last name: ";
												cin>>lastName;
												b.changeLastName(AM,lastName);
											}
											cout<<endl<<"Do you want to change his grade? Y/N :";
                        				while(1){
                        					cin>>yesOrNo;
                        					if( yesOrNo == "Y" || yesOrNo == "y" || yesOrNo == "N" || yesOrNo == "n") 
                        					break;
											}
                        					if (yesOrNo == "Y" || yesOrNo == "y"){
												cout<<"Enter the new grade: ";
												cin>>grade;
							   					b.changeGrade(AM,grade);
 											}
                        					cout<<endl;
                        				break;//break of case 1.6
                        		}
                        		case 7 : {
                        				stillRunning = false;
									break; //break of case 1.7
								}
               					case 8 : {
								   			system("CLS");
											cout<<"It's over Anakin. I have the high ground.";
											return 0; 
										break; //break of case 1.8
               					}
           					}//end of BST outmost switch
							}//end of BST outmost while
						break; //break of case 1 BST option
					}
/////////////////////////////////////////////////////////////HASH TABLE/////////////////////////////////////////////////////////////

					case 2 : {
								bool stillRunning = true;
								BinarySearchTree b;
								int ch;
								Student s;
								fill_tree_grade_wise(&b);
								cout<<" In-Order Traversal "<<endl;
                        		cout<<" -------------------"<<endl;
                        		printTitles();
                        		b.print_inorder();
                        		
                        		while(stillRunning)
       							{
	         						cout<<endl<<endl;
									cout
									<<" Grade-wise Binary Search Tree Operations "<<endl
	           						<<" ----------------------------- "<<endl
	           						<<" 0. Search for the students with the LOWEST grade"<<endl
	           						<<" 1. Search for the students with the HIGHEST grade"<<endl
	           						<<" 2. Return to main menu "<<endl
	           						<<" 3. Exit "<<endl
	           						<<" Enter your choice : ";
	           						cin>>ch;
	           						
	           						switch(ch){
	
	           								case 0 : {	
	           											double lowestGrade = b.find_lowest_grade();
										   				cout
														<<"The lowest grade in the database is "<<lowestGrade<<endl	
										   				<<"The students with grade "<<lowestGrade<<" are: "<<endl;
										   				printTitles();
										   				b.print_students_with_lowest_grade(lowestGrade);
											break; //break of case 2.0
										   }
											case 1 : {
														double highestGrade = b.find_highest_grade();
														cout
														<<"The highest grade in the database is "<<highestGrade<<endl	
										   				<<"The students with grade "<<highestGrade<<" are: "<<endl;
										   				printTitles();
										   				b.print_students_with_highest_grade(highestGrade);
												break; //break of case 2.1
											}
											case 2 : { 
														stillRunning = false;
												break; //break from case 2.2
											} 
											case 3 : { 	
														system("CLS");
														cout<<"It's over Anakin. I have the high ground.";
														return 0; }	//exit the programm
									} //end of switch
								} //end of while
								break; //break from case 2		
					} //end of case 2
					////////////HASH CHAINS//////////////////////////			
		   			case 3 : {	
		   						bool stillRunning = true;
					   			int That_Row;
								Student ss;	
					   			int row;
								int i=0;
								bool flag = true;
								int test=0;
								bool flag2 = true;
								string new_name,am,AM,First_name,Last_name;
								string NEW_AM,NEW_FIRST_NAME,NEW_LAST_NAME;
								double NEW_GRADE;
								double grade,new_grade;	
								//string shiit;
								int choice,choice2;	
								//vector< vector<int> >  foititis;
								vector< vector<Student> > hash_table;	
								int colCounter=0;
								fillHashTable(hash_table);
							
							
							while(stillRunning){
								cout
								<<" ----------------------------- "<<endl
								<<" Hash Table Operations "<<endl
						        <<" ----------------------------- "<<endl
						        <<" 0. Search             "<<endl
						        <<" 1. Edit "<<endl
						        <<" 2. Delete "<<endl
						        <<" 3. Insert student"<<endl
								<<" 4. Return to main menu "<<endl
								<<" 5. Exit"<<endl;
						        
						        cin>>choice;
							
							
							switch(choice)
							{
								//Search for a student
								case 0 : {
											cout<<endl<<"Type exit to exit the search menu. \nEnter AM of the student: ";
										 	cin>>am;
										 
											row = convertToASCII(am) % PRIME;
											if(am=="exit" || am=="EXIT" || am=="Exit") break;
											else
											{
												for(int j=0; j < hash_table[row].size(); j++){ //check if the student exists. get the column index if yes
											 		if(am==hash_table[row][j].getAM()) {
											 			 printStudentInfo(
													 	hash_table[row][j].getAM(), 
														 hash_table[row][j].getFirstName(), 
														 hash_table[row][j].getLastName(), 
														 hash_table[row][j].getGrade()); 
											 		 	break;
													}
											    	else if (j == hash_table[row].size() - 1) cout<<"Student with AM: "<<am<<" not found."<<endl;
												}	
											}
									    break; //break of case 3.0
								}
								//Edit the student's info	 
								case 1 : {

											cout<<endl<<"Type exit to exit the edit menu. \nEnter AM of the student: ";
										 	cin>>am;
										 	row = convertToASCII(am) % PRIME;
										 	if(am=="exit" || am=="EXIT" || am=="Exit") break;
										 	else
										 	{
										 		for(int j=0; j < hash_table[row].size(); j++){ //check if the student exists. get the column index if yes
										 			if(am==hash_table[row][j].getAM()) break;
												 	
											 		colCounter++;
										    		if (colCounter == hash_table[row].size() - 1){
										    		cout<<"Student with AM: "<<am<<" not found."<<endl;
										    		flag=false;
													}
										    	}
											}
										 	while(flag){
										 		cout
										 	<<"5. Edit First Name"<<endl
										 	<<"6. Edit Last Name"<<endl
										 	<<"7. Edit Grade"<<endl
										 	<<"8. Exit edit menu"<<endl;
										 	cin>>choice2;
										 
										 	switch(choice2)
										 	{
										 		//edit the first name
											 	case 5 : {
															cout<<"Enter new First name: ";
															cin>>new_name;
															hash_table[row][colCounter].setFirstName(new_name);
																	
															printStudentInfo(
															hash_table[row][colCounter].getAM(), 
															hash_table[row][colCounter].getFirstName(), 
															hash_table[row][colCounter].getLastName(), 
															hash_table[row][colCounter].getGrade());
														  
													break; //break of case 3.1.5
											}
												//edit the last name 	
												case 6 : {
															 cout<<"Enter new Last name: ";
															 cin>>new_name;
																
														   	 hash_table[row][colCounter].setLastName(new_name);
																
															 printStudentInfo(
															 hash_table[row][colCounter].getAM(), 
															 hash_table[row][colCounter].getFirstName(), 
															 hash_table[row][colCounter].getLastName(), 
															 hash_table[row][colCounter].getGrade());	
															 
													break;	//break of case 3.1.6
												}
												//edit grade
												case 7 : {
															cout<<"Enter new grade: ";
												
														 	 cin>>new_grade;
															 //defensive programming to ensure a double between 0 and 10 is entered
															 while(cin.fail() || !(new_grade>=0 && new_grade<=10)){
															 	cin.clear();
								  							 	cin.ignore();
															 	cout<<"Please enter a double value between 0 and 10: ";
															 	cin>>new_grade;
															 }	
															 hash_table[row][colCounter].setGrade(new_grade);
																
															 printStudentInfo(
															 hash_table[row][colCounter].getAM(), 
															 hash_table[row][colCounter].getFirstName(), 
															 hash_table[row][colCounter].getLastName(), 
															 hash_table[row][colCounter].getGrade());
															 
													break;//break of case 3.1.7
												}
												case 8 : {
															flag = false; //exit the inner switch
											 	}
											 } //////////end of inner switch/////////////
											 colCounter=0;
											 
									break; //break of case 3.1
								}	
												
							}//case 1 
								//Delete hash number from hash table.
								case 2 : {
										 	print_hash_table(hash_table);
										  	cout<<endl<<"Type exit to exit the delete menu. \nEnter AM of the student: ";
										 	cin>>am;
											row = convertToASCII(am) % PRIME;
											if(am=="exit" || am=="EXIT" || am=="Exit") break;
											else
											{
											
												for(int j=0; j < hash_table[row].size(); j++)
												{
													//check if the student exists. get the column index if yes
											 		if(am==hash_table[row][j].getAM())	
											 		{
												 		hash_table[row].erase(hash_table[row].begin() + j);
														cout<<"The student with AM "<<am<<" has been deleted."<<endl;
														print_hash_table(hash_table);
											 	 		break;	
													}
											 		colCounter++;
											    	if (colCounter == hash_table[row].size() - 1)
													cout<<"Student with AM: "<<am<<" not found."<<endl;
												}
											}
										 break; //break of case 3.2
										}
								//insert student
								case 3 : 
										{
											cout<<endl;
											print_hash_table(hash_table);
											cout<<endl<<"Enter the AM of the student: ";
										 	cin>>NEW_AM;					 	
										 	if(NEW_AM=="exit" || NEW_AM=="EXIT" || NEW_AM=="Exit") break;
											else
											{
												cout<<"Enter the First name of the student: ";
										 		cin>>NEW_FIRST_NAME;
										 		cout<<"Enter the Last name of the student: ";
										 		cin>>NEW_LAST_NAME;
										 		cout<<"Enter the Grade of the student: ";
										 		cin>>NEW_GRADE;	
										 		while(cin.fail() || !(NEW_GRADE>=0 && NEW_GRADE<=10))
												{
													cin.clear();
								  					cin.ignore();
													cout<<"Please enter a double value between 0 and 10: ";
													cin>>NEW_GRADE;
												} 									 		
												Insert_Student(hash_table,NEW_AM,NEW_FIRST_NAME,NEW_LAST_NAME,NEW_GRADE);
												cout<<"Student added successfully. "<<endl;									
											}
											print_hash_table(hash_table);
											break; //break of case 3.3
										}
								 case 4 : {
								 			stillRunning = false;
									break;
								 }
								 case 5 : {
											system("CLS");
											cout<<"It's over Anakin. I have the high ground.";
											return 0; break; //break of case 3.4
										}   
										
										
										
							}//end of hashing outmost switch
								
								
								}//end of hashing outmost while
							}//end of hash chains case
					}//end of switch to choose BST or HASH
				}//end of outmost while
						    	
			}//end of main


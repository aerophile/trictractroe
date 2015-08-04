/* *************************************************************************************************************
 *    
 *     Title: Tric Trac Troe (a Tic Tac Toe game)
 *     Author: shubham Gupta
 *     Description: An attempt in making tic tac toe  game based machine learning System 
 *     contact: shubham0075+mlp@gmail.com
 * 
 ***************************************************************************************************************/

#include <iostream>
#include <stdlib.h>
using namespace std;





class position
{
	public:
	
	int id;            //used to identify a position of tic tac toe
	
	int next_moves[3]; //used to store the human learned move 
	
	int box[10];       //actual storage of elements of tic tac toe
	//int moves;         //number of moves in the current position. This has been started from a min 4 to max 9
	int skill_counter; //keeps count of entreis into next_moves...useful for getting skill rating of AI

		position(){
			next_moves[0]=next_moves[1]=next_moves[2]=-1;
			skill_counter=0;
	    int i=9;
		while(i >0)
		   {box[i]=0;
		    i--;
		   }
		  box[i]=99;}
		
		void disp(){
			cout<<endl<<"  "<<render(this->box[1])<<" | "<<render(this->box[2])<<" | "<<render(this->box[3])<<endl;
			char a[]="------------";
			cout<<" "<<a;
			cout<<endl<<"  "<<render(this->box[4])<<" | "<<render(this->box[5])<<" | "<<render(this->box[6])<<endl;
			cout<<" "<<a;
			cout<<endl<<"  "<<render(this->box[7])<<" | "<<render(this->box[8])<<" | "<<render(this->box[9])<<endl;
			       }
			       
		char render(int digit){
			if(digit==0)
			  return ' ';
			else if(digit==1)
			  return 'X';
			else 
			  return 'O';}	         
		  
		  
		 void raw_disp(){
			 cout<<endl<<"  "<<this->box[1]<<this->box[2]<<this->box[3]<<this->box[4]<<this->box[5]<<this->box[6]<<this->box[7]<<this->box[8]<<this->box[9];} 
   
  
         bool isValid(){
			 
			 
			 //checks invalid positions by comparing number of x and o's
			 int x=0,o=0,i=1;
			    while (i<10){
					if (this->box[i]==1)
					  x++;
					if (this->box[i]==2)
					  o++;  
					i++;} 
					
					
			//checks fo multiple wins
			 int win=0,count=1;
			  //rows win check
			  while(count<8){
			  if(this->box[count]==this->box[count+1] && this->box[count+1]==this->box[count+2] && this->box[count]!=0)
			     {win++;} 
			     count+=3; }
			    //column win check 
			     count=1;
			  while(count<4){
			  if(this->box[count]==this->box[count+3] && this->box[count+3]==this->box[count+6] && this->box[count]!=0)
			     {win++;}  
			     count++;}
			     //diagonal win check
			     count=1;
			     if(this->box[count]==this->box[count+4] && this->box[count+4]==this->box[count+8] && this->box[count]!=0)
			     {win++;} 
			     //other diagonal win check
			     count=3;
			     if(this->box[count]==this->box[count+2] && this->box[count+2]==this->box[count+4] && this->box[count]!=0)
			     {win++;}   
			     
			     
			   			     		
				//valid or invalid result return	
				if((o-x)>1||(x-o)>1  || win>1 || (o+x)<4 )
				 return false;
				else
				  return true; 	
					
					}  
  
         bool isEqual(position c){
			 int i=1;
			 while(i<10)
			 {if(this->box[i]!=c.box[i])
				 break;
				 
				 i++;}
				 
				 if (i==10)
				   return true;
				  else
				    return false; 
			 }
  
         bool isWin()
          {//checks for a winner
			 int win=0,count=1;
			  //rows win check
			  while(count<8){
			  if(this->box[count]==this->box[count+1] && this->box[count+1]==this->box[count+2] && this->box[count]!=0)
			     {win++;} 
			     count+=3; }
			    //column win check 
			     count=1;
			  while(count<4){
			  if(this->box[count]==this->box[count+3] && this->box[count+3]==this->box[count+6] && this->box[count]!=0)
			     {win++;}  
			     count++;}
			     //diagonal win check
			     count=1;
			     if(this->box[count]==this->box[count+4] && this->box[count+4]==this->box[count+8] && this->box[count]!=0)
			     {win++;} 
			     //other diagonal win check
			     count=3;
			     if(this->box[count]==this->box[count+2] && this->box[count+2]==this->box[count+4] && this->box[count]!=0)
			     {win++;} 
			     
			     if(win==1)
			        return true;
			     else 
			         return false;
			     }
  
  
   };



position a[20000]; //global declaration of position array that contains all the possible valid positions of tic tac toe


class game: public position {
	public:
	
	
	void play()
	{ int i=1,move;
		while(i<10){//play main loop
						system("clear");
						int current_player=(i%2)==1?1:2;
						this->disp();
						cout<<endl<<render(current_player)<<" to move\n";
						cin>>move;
								if(move<10 && move>0 && this->box[move]==0)
								  {this->box[move]= (i%2)==1?1:2;
									  this->learn();
									  
									  if(this->isWin()){
										 { system("clear");
											 this->disp();
											 cout<<"Winner is "<<render(current_player);
											 break;}
										 }
									  i++;
							
									  }
								 else
									{cout<<endl<<"move not valid\n";}
									
							}
		if (i==10 && this->isWin()!=true){
			system("clear");
			this->disp();
		    cout<<"\n This Game is Drawn\n";}}
		    
		    
		    
		    
		    void learn(){
				int counter=0,climit=19684;
					while(counter<climit)
					{
						if(this->isEqual(a[counter]))
						  {cout<<"\n Position id is : "<<a[counter].id;
							  break;}
						counter++;
						}
				}
		
	
	};



position trinary(int counter1){ 
	position b;
	int i=1;
	while(i<10 && counter1!=0){
		
			b.box[i]=counter1 % 3;
		    counter1=counter1 / 3;
		i++;}
	return b;	
	
	}



int main(){
	//some testing code  used to generate the different valid tic tac toe positions posible in a game 
	 
	 
	int counter=19683,countofvalid=0;
	while(counter>0){
		a[counter]=trinary(counter);
		a[counter].id=counter;
	    
	    
	    if(a[counter].isValid()){
			cout<<a[counter].id<<" \t ";
	    a[counter].disp();
	    countofvalid++;}
	    counter--;}
	 //cout<<"\n Number of valid positions "<<countofvalid; 
	 
	 
	 
	
	 
	 game g;
	 g.play();
 }

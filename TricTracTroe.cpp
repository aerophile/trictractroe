/* *************************************************************************************************************
 *    
 *     Title: Tric Trac Troe (a Tic Tac Toe game)
 *     Author: shubham Gupta
 *     Description: A tic tac toe  game based machine learning System 
 *     contact: shubham0075+mlp@gmail.com
 * 
 ***************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

int game_sequences[11][25000],gscounter=0,gamecount=0;
int instances1,instances2;

class position
{
	public:
	
	int id;            //used to identify a position of tic tac toe
	
	int next_moves[3]; //used to store the human learned move 
	
	int box[10];       //actual storage of elements of tic tac toe
	//int moves;         //number of moves in the current position. This has been started from a min 4 to max 9
	int skill_counter; //keeps count of entries into next_moves...useful for getting skill rating of AI

		position(){
			next_moves[0]=next_moves[1]=next_moves[2]=-1;
			skill_counter=0;
			
	    int i=9;
		while(i >0)   //initialising the position to all boxes having zeroes
		   {box[i]=0;
		    i--;
		   }
		  box[i]=99;//last box of position initialised to 99 
		  }
		
		void disp(){  //main display function used.It also has the tic tac toe grid display and it is used to display by default
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
			 //mainly for diagnostic use, it displays the ternary number directly corresponding to the position of the tic tactoe game's position.
			 
			 cout<<endl<<"  "<<this->box[1]<<this->box[2]<<this->box[3]<<this->box[4]<<this->box[5]<<this->box[6]<<this->box[7]<<this->box[8]<<this->box[9];} 
   
  
         bool isValid(){
			 
			 
			 //checks invalid positions by comparing number of x and o's since the difference can't be higher than one in a valid game
			 int x=0,o=0,i=1;
			    while (i<10){
					if (this->box[i]==1)
					  x++;
					if (this->box[i]==2)
					  o++;  
					i++;} 
					
					
			//checks fo multiple wins   //only one win is possible in a valid game
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
			     
			     
			   			     		
				//valid or invalid result return	//sums up all of the previous check conditions in the function.
				if((o-x)>1||(x-o)>1  || win>1 || (o+x)<4 )
				 return false;
				else
				  return true; 	
					
					}  
  
         bool isEqual(position c){//to compare two positions and return true if they are equal.
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

class random_fast_move
{public:
	int move_array[10],move_array_limit;
	
	       random_fast_move(){
			 move_array_limit=9; //this will return all numbers from 1 to 9 in a much better and quicker way as opposed to directly using random function
			for(int j=0;j<10;j++)
			move_array[j]=j+1;
			}
			
			int chose_moveby_random()
			{
							int amove_index,move1;
							amove_index=rand() % (move_array_limit);
							move1= move_array[amove_index];
							
							for(int j1=amove_index;j1<move_array_limit;j1++)
							  {move_array[j1]=move_array[j1+1];}
							move_array_limit--;
							return move1;
				}};

/*
 class learnt_stack{
	 public:
	 //static int numb;
	 int game_learn[11];
	 
	 learnt_stack(){
						 int count=0;
						  while(count<12)
							  {game_learn[count]=-1;
							  count++;}
							  
							  
							//numb++;  
		 }
	 
	 }; */
	 
	 
	 
	

position a[20000]; //global declaration of position array that contains all the possible valid positions of tic tac toe
//learnt_stack b[20000];

position trinary(int);
int compare_and_move(int,int);
int research_next_move(int);

class game: public position {
	public:
	
	int game_sequence[11];//use to store all the position ids of the game's moves which will be further analysed in case of win or draw
	                      // index 0 is used for storing game info,index 1 will always be 0, from index 2 to 10 are the actual Position ids that matter  
	  game(){
		  int count=0;
		  while(count<12)
			  {game_sequence[count]=-1;
			  count++;
			  
			  }
		    }
	void play(int play_mode)
	{ if(play_mode==4)
		{  int pid;
			 do{
					cout<<"id of position to displayed ( -1 for exit ):";
					
					cin>>pid;
					a[pid].disp();
    			}while(pid!=-1);
		}
		
		
		
		else if(play_mode==1)
		{int i=1,move;
		while(i<10){//play main loop
						system("clear");
						int current_player=(i%2)==1?1:2;
						this->disp();
						int currentid,nextid;
						currentid=this->getId(); 
						cout<<endl<<render(current_player)<<" to move\n";
						cin>>move;
								if(move<10 && move>0 && this->box[move]==0) //conditions for a valid move
								  {this->box[move]= (i%2)==1?1:2;
									  this->game_sequence[i]=currentid;
									  nextid=this->getId();
									  a[currentid].next_moves[0]=nextid;
									  a[currentid].skill_counter++;
									  
									  
									  
									  if(this->isWin()){
										 { this->game_sequence[i+1]=nextid;
											 system("clear");
											 this->disp();
											 cout<<"Winner is "<<render(current_player)<<endl;
											 
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
		    cout<<"\n This Game is Drawn\n";
		    this->game_sequence[i+1]=this->getId();
		    
		 
		    
		    }}
		    
		    //player vs computer function...using the inteligence
		    
		else if(play_mode==2)
		{int i=1,move;
		 int move_source=0;//to tell where the move came from
		while(i<10){//play main loop
						system("clear");
						
						int current_player=(i%2)==1?1:2;
						this->disp();
						cout<<"\n move by "<<move_source<<endl;
						int currentid,nextid;
						currentid=this->getId(); 
						cout<<endl<<render(current_player)<<" to move\n";
						
						if(current_player==1){
						cin>>move;
						move_source=4;
		    								if(move<10 && move>0 && this->box[move]==0) //conditions for a valid move
												  {this->box[move]= (i%2)==1?1:2;
													  this->game_sequence[i]=currentid;
													  nextid=this->getId();}
													  
											else
									            {cout<<endl<<"move not valid\n";}}
									            
									            
						else if(current_player==2){
							int move_done=0;
							while(move_done==0){
								
								
								
							//move choosing here
							if (research_next_move(currentid)==-5)
							    {move=rand() % 9 + 1;
								 move_source=1;
								}
		
							else
								{move=compare_and_move(currentid,research_next_move(currentid));
									move_source=2;
									if (move==-1)
									{move=rand() % 9 + 1;
									 move_source=3;}
								}
						    
						    //int a5;cout<<"\n  move received is  "<<move<" dgsd";cin>>a5;
							
							 if(move<10 && move>0 && this->box[move]==0) //conditions for a valid move
			                      {this->box[move]= (i%2)==1?1:2;
								   this->game_sequence[i]=currentid;
								   nextid=this->getId();
								   move_done=1;
								  }
													  }}
									        
									  
									  
									  if(this->isWin())
										 { this->game_sequence[i+1]=nextid;
											 system("clear");
											 this->disp();
											 cout<<"Winner is "<<render(current_player)<<endl;
											 
											 break;}
										 
									  i++;
							
									  }

									
							
		if (i==10 && this->isWin()!=true){
			system("clear");
			this->disp();
		    cout<<"\n This Game is Drawn\n";
		    this->game_sequence[i+1]=this->getId();
		                                 }
		                                 
		        }
		    
		    
		    //playmode 3 refine
		    
	
		    
		    
		    else if(play_mode==3)
		{int i=1,move;
			random_fast_move obj;
		     gamecount++;
			
				
		while(i<10){//play main loop
						system("clear");
						int current_player=(i%2)==1?1:2;
						this->disp();
						int currentid,nextid;
						currentid=this->getId(); 
						cout<<endl<<render(current_player)<<" to move\n";
						
						move=obj.chose_moveby_random();//use for new class
						//move=rand() % 9 + 1;//random function used cstdlib
						/* debug code for new chose random class based assignment
						 * for(int k=0;k<9;k++)
						cout<<obj.move_array[k]<<" ";
						int b1;
						cin>>b1;*/
						
						
						
						
								if(move<10 && move>0 && this->box[move]==0) //conditions for a valid move
								  {this->box[move]= (i%2)==1?1:2; // determing whether to put 1 or 2 i.e. O or X
									  
									  //this->game_sequence[move]=currentid; i made a mistake here...game sequence array will be stored sequentially and not by move position 
									     this->game_sequence[i]=currentid;
									  nextid=this->getId();
									  a[currentid].next_moves[0]=nextid;
									  a[currentid].skill_counter++;
									  
									  //debug code below
									  cout<<currentid<<" v   "<<nextid<<endl;
									  
									  
									  if(this->isWin()){
										 { 
											 this->game_sequence[i+1]=nextid;
											 
											 
											 system("clear");
											 this->disp();
											 cout<<"Winner is "<<render(current_player)<<endl;
											 game_sequence[0]=current_player;//storing the winner at the beginning of the array game_sequence 
											 break;}
										 }
									  i++;
							
									  }
								 //else
									//cout<<endl<<"move not valid\n";
									
							} 
							
		if (i==10 && this->isWin()!=true){
			system("clear");
			this->disp();
		    cout<<"\n This Game is Drawn\n"; game_sequence[0]=3; //storing a draw stuation
		    
		    this->game_sequence[i]=this->getId();
		    
		   } 
		   
		   
		   for(int l=0;l<11;l++){
		  game_sequences[l][gscounter]=game_sequence[l];
		    // b[gscounter].game_learn[l]=game_sequence[l];
		  }
		   gscounter++;
		   /*not working error code 134
		    * fstream fileobj;
		   fileobj.open("learnt.txt",ios::out);
		   fileobj.put("hoooo haaa");
		   fileobj.close();*/
		    
		   
		   
		   
		   }
		    
		    
		    else if(play_mode==5){
							int counter=0;
							
							if (instances1==0)
							cout<<"\nno games played yet\n";
							else{
						 while(counter<instances1){
							
							 cout<<counter<<" | ";
						 for(int l=0;l<11;l++){
							   cout<<game_sequences[l][counter]<<" ";
							   //cout<<b[counter].game_learn[l]<<" ";
							   }
							   cout<<endl;
							   counter++;
							   }
						 cout<<"no brains just played "<<gamecount<<"games against itself";
									}}
		   
		   
		   
		    }
		    
		    
		    int getId(){
				int counter=0,climit=19684;
					while(counter<climit)
					{
						if(this->isEqual(a[counter]))
						  {return a[counter].id;}
						counter++;
						}
				   }
		    
		 /*   void learn(){
				int counter=0,climit=19684;
					while(counter<climit)
					{
						if(this->isEqual(a[counter]))
						  {cout<<"\n Position id is : "<<a[counter].id;
							  break;}
						counter++;
						}
				}*/
		
	
	};
	


int research_next_move(int currentid){
	int i=0;
	while(i<instances1){
		
		 for(int l=0;l<11;l++){
		   if(game_sequences[l][i]==currentid && (game_sequences[0][i]==2 ))//|| game_sequences[0][i]==3)) to allow fro draw cases also enable this
		    return game_sequences[l+1][i];
		   }
		
		i++;
		}
		
		return -5;
	}
	
 int compare_and_move(int pid1,int pid2){
	position a2 = trinary(pid1);
	position b2 = trinary(pid2);
	
	int i=1;
	for(;i<10;i++)
	{if (a2.box[i] != b2.box[i])
		return i;
		}
	if (i==10)
		return -6;
 }
 
position trinary(int counter1){ 
	//converts the decimal number into a ternary number of base 3 (I incorrectly named it trinary based on binary) 
	//this function also asssigns the number to a position after ternary conversion and that position is ultimately returned.
	//using this ternary system i am able to represent 0 as a blank, 1 as X and 2 as O. the render() function is responsible for converting 
	//the numbers to these symbols while displaying the numbers. 
	position b;
	int i=1;
	while(i<10 && counter1!=0){
		
			b.box[i]=counter1 % 3;
		    counter1=counter1 / 3;
		i++;}
	return b;	
	
	}



void generate_positions(){
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
	}
	


int main(){
	//some testing code  used to generate the different valid tic tac toe positions posible in a game 
	 generate_positions();
	 
	 int play_mode=-1,instances=1;
	 char carryon='y';
	 
	 while(carryon=='y' || carryon=='Y'){
	  cout<<"Enter game modes\n(1)human vs Human\n(2)Humaan vs Nobrains\n(3) Two crazy Nobrains \n(4) show a position \n(5) show games played experience\n";
	 cin>>play_mode;
	 if(play_mode==3)
		 {cout<<"\nEnter number of games to play :";
			 
		  cin>>instances;//1;
		  
		 //instances2=instances1;
		 //instances2/=1000;
		//for(instances=1000;(instances2)>0;(instances2)--)
		instances1=instances;
		 while(instances>0)
		 {game* g = new game;
		 g->play(play_mode);
		 instances--;
		 //delete g;
		 }
		
		 }
      else{
		  game* g = new game;
		  g->play(play_mode);
		  }	 
	 
	
	 cout<<"\ncarry on ?  ";
	 cin>>carryon;}
 }
 
 

	 

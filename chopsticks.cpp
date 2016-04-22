#include<iostream>
using namespace std;

const int MOVE_HORIZON= 6;

struct player{
  int right_hand;
  int left_hand;
  double long  option[12];
  double long num_moves;
  double long num_wins;
};


bool death(player player1);
int add(int player1_hand, int player2_hand);
bool right_exchange(player *player1, int value);
bool left_exchange(player *player1, int value);
bool player1_recursion(player *p1, player *p2, int rounds);
void clear_options(player *q);
void determine_move(player *p1, player *p2, int index);

int main(){
  player compet1;
  player compet2;
  bool stop_game=true;
  clear_options(&compet1);
  clear_options(&compet2);
  while(stop_game){
    clear_options(&compet1);
    clear_options(&compet2);
    cout<<"Player 1 right hand:"<<endl;
    cin>>compet1.right_hand;

    cout<<"Player 1 left hand:"<<endl;
    cin>>compet1.left_hand;

    cout<<"Player 2 right hand:"<<endl;
    cin>>compet2.right_hand;

    cout<<"Player 2 left hand:"<<endl;
    cin>>compet2.left_hand;

    int rounds=2*MOVE_HORIZON;
    if(player1_recursion(&compet1, &compet2, rounds)){
      cout<<"Player 1 right hand: "<<compet1.right_hand<<endl;
      cout<<"Player 1 left hand: "<<compet1.left_hand<<endl;
      cout<<"Player 2 right hand: "<<compet2.right_hand<<endl;
      cout<<"Player 2 left hand: "<<compet2.left_hand<<endl;
      cout<<"Forced Win"<<endl;//////
    }
    else{
      int max=0;
      int index=0;
      for(int i=0; i<12; i++){
	if(compet1.option[i]>=max){
	  max=compet1.option[i];
	  index=i;
	}
      }
      determine_move(&compet1, &compet2, index);
      cout<<"Player 1 right hand: "<<compet1.right_hand<<endl;
      cout<<"Player 1 left hand: "<<compet1.left_hand<<endl;
      cout<<"Player 2 right hand: "<<compet2.right_hand<<endl;
      cout<<"Player 2 left hand: "<<compet2.left_hand<<endl;
      cout<<"Strength: "<<max<<endl;
      cout<<"Move: "<<index<<endl;
    }

    for(int i=0; i<12; i++){
      cout<<"Move "<<i<<": "<<compet1.option[i]<<endl;
    }

    if(death(compet1)){
      cout<<"player 2 wins!"<<endl;
      stop_game=false;
    }

    else if(death(compet2)){
      cout<<"player 1 wins!"<<endl;
      stop_game=false;
    }
      
  }
   
  return 0;
}

void determine_move(player *p1, player *p2, int index){
  player  player1=*p1;
  player player2=*p2;
  if(index==0){
    p2->right_hand=add(player1.right_hand, player2.right_hand);
    return;
  }
  else if(index==1){
    p2->left_hand=add(player1.right_hand, player2.left_hand);
    return;
  } 
  else if(index==2){
    p2->left_hand=add(player1.left_hand, player2.left_hand);
    return;
  }
  else if(index==3){
    p2->right_hand=add(player1.left_hand, player2.right_hand);
    return;
  }
  else if(index%2==0){
    left_exchange(p1, index/2-1);
  }
  else
    right_exchange(p1, (index-3)/2);

}
void clear_options(player *q){
  for(int i=0; i<12; i++){
    q->option[i]=0;
  }
  q->num_moves=0;
  q->num_wins=0;
}
bool player1_recursion(player *p1, player *p2, int rounds){
  int storage1;
  int storage2;
  bool bool1;
  bool val=true;
  rounds--;
  if(rounds<=0)
    return false;
  player  player1=*p1;
  player player2=*p2;
   storage1=player1.right_hand;
   storage2=player2.right_hand;
   if(player1.right_hand>0 && player2.right_hand>0){
     player2.right_hand=add(player1.right_hand, player2.right_hand);
     p2->right_hand=player2.right_hand;
     if(rounds%2==0)
       bool1=death(player1);
     else
       bool1=death(player2);
     
     if(rounds%2==0)
       p2->num_moves++;
     if(rounds%2==0 && death(*p2))///
       p2->num_wins=p2->num_wins-2;
     if(bool1){
       if(rounds%2==0)
	 p2->num_wins++;
       return true;
     }
     else{
       if(player1_recursion( p2,  p1, rounds)){
	 p2->right_hand=player2.right_hand;
	 p2->left_hand=player2.left_hand;
	 p1->right_hand=player1.right_hand;
	 p1->left_hand=player1.left_hand;
	 if(rounds%2==0)
           p2->num_wins++;
	 if(rounds%2!=0)
	   return true;
       }
       else if(rounds%2==0)
	 val=false;
     }
     p1->num_moves=1;//
     if(2*MOVE_HORIZON-1==rounds){
       p1->option[0]=p1->num_wins/p1->num_moves;
       p1->num_moves=0;
       p1->num_wins=0;
     }
  }
  player1.right_hand=storage1;
  player2.right_hand=storage2;
  p2->right_hand=player2.right_hand;
  p2->left_hand=player2.left_hand;
  p1->right_hand=player1.right_hand;
  p1->left_hand=player1.left_hand;

   storage1=player1.right_hand;
   storage2=player2.left_hand;
   if(player1.right_hand>0 && player2.left_hand>0){
     player2.left_hand=add(player1.right_hand, player2.left_hand);
     p2->left_hand=player2.left_hand;
     if(rounds%2==0)
       bool1=death(player1);
     else
       bool1=death(player2);
     if(rounds%2==0)
       p2->num_moves++;

     if(rounds%2==0 && death(*p2))///
	p2->num_wins=p2->num_wins-2;

     if(bool1){
       if(rounds%2==0)
	 p2->num_wins++;
       return true;
     }
     else{
       if(player1_recursion( p2,p1 , rounds)){
	 p2->left_hand=player2.left_hand;
	 p2->right_hand=player2.right_hand;
	 p1->right_hand=player1.right_hand;
	 p1->left_hand=player1.left_hand;
	 if(rounds%2==0)
           p2->num_wins++;
	 if(rounds%2!=0)
	   return true;
       }
       else if(rounds%2==0)
         val=false;
     }
  }
   p1->num_moves=1;//
   if(2*MOVE_HORIZON-1==rounds){
     p1->option[1]=p1->num_wins/p1->num_moves;
	 p1->num_moves=0;
       p1->num_wins=0;
   }
  player1.right_hand=storage1;
  player2.left_hand=storage2;
  p2->left_hand=player2.left_hand;
  p2->right_hand=player2.right_hand;
  p1->right_hand=player1.right_hand;
  p1->left_hand=player1.left_hand;

   storage1=player1.left_hand;
   storage2=player2.left_hand;
   if(player1.left_hand>0 && player2.left_hand>0){ 
     player2.left_hand=add(player1.left_hand, player2.left_hand);
     p2->left_hand=player2.left_hand;
     if(rounds%2==0)
       bool1=death(player1);
     else
       bool1=death(player2);
     if(rounds%2==0)
       p2->num_moves++;
     if(rounds%2==0 && death(*p2))///
       p2->num_wins=p2->num_wins-2;
     if(bool1){
       p2->left_hand=player2.left_hand;
       if(rounds%2==0)
	 p2->num_wins++;
       return true;
     }
     else{
       if(player1_recursion( p2,  p1, rounds)){
	 p2->left_hand=player2.left_hand;
	 p2->right_hand=player2.right_hand;
	 p1->right_hand=player1.right_hand;
	 p1->left_hand=player1.left_hand;
	 if(rounds%2==0)
           p2->num_wins++;
	 if(rounds%2!=0)
	 return true;
       }
     else if(rounds%2==0)
       val=false;
     }
   }
   p1->num_moves=1;//
   if(2*MOVE_HORIZON-1==rounds){
     p1->option[2]=p1->num_wins/p1->num_moves;
	 p1->num_moves=0;
       p1->num_wins=0;
   }
  player1.left_hand=storage1;
  player2.left_hand=storage2;
  p2->left_hand=player2.left_hand;
  p2->right_hand=player2.right_hand;
  p1->right_hand=player1.right_hand;
  p1->left_hand=player1.left_hand;

   storage1=player1.left_hand;
   storage2=player2.right_hand;
   if(player1.left_hand>0 && player2.right_hand>0){
     player2.right_hand=add(player1.left_hand, player2.right_hand);
     p2->right_hand=player2.right_hand;
     if(rounds%2==0)
       bool1=death(player1);
     else
       bool1=death(player2);
     if(rounds%2==0)
       p2->num_moves++;
     if(rounds%2==0 && death(*p2))///
       p2->num_wins=p2->num_wins-2;
     if(bool1){
       p2->right_hand=player2.right_hand;
       if(rounds%2==0)
	 p2->num_wins++;
       return true;
     }
     else{
       if(player1_recursion( p2, p1, rounds)){
	 p2->right_hand=player2.right_hand;
	 p2->left_hand=player2.left_hand;
	 p1->right_hand=player1.right_hand;
	 p1->left_hand=player1.left_hand;
	 if(rounds%2==0)
           p2->num_wins++;
	 if(rounds%2!=0)
	   return true;
       }
       else if(rounds%2==0)
         val=false;
     }
   }
   p1->num_moves=1;//
   if(2*MOVE_HORIZON-1==rounds){
     p1->option[3]=p1->num_wins/p1->num_moves;
	 p1->num_moves=0;
       p1->num_wins=0;
   }
  player1.left_hand=storage1;
  player2.right_hand=storage2;
  p2->right_hand=player2.right_hand;
  p2->left_hand=player2.left_hand;
  p1->right_hand=player1.right_hand;
  p1->left_hand=player1.left_hand;

  int new_storage1;
  int new_storage2;
  int x=3;
  for(int i=1; i<5; i++){
    storage1=p1->right_hand;
    storage2=p1->left_hand;
    if(p1->left_hand>0 && !left_exchange(p1, i)){
      new_storage1=p1->right_hand;
      new_storage2=p1->left_hand;
      if(!(new_storage1==storage2 && new_storage2==storage1)){
	if(rounds%2==0)
	  p2->num_moves++;
	if(player1_recursion(p2, p1, rounds)){
	  p1->right_hand=new_storage1;
	  p1->left_hand=new_storage2;
	  p2->right_hand=player2.right_hand;
	  p2->left_hand=player2.left_hand;
	  if(rounds%2==0)
	    p2->num_wins++;
	  if(rounds%2!=0)
	    return true;
	}
	else if(rounds%2==0)
	  val=false;
      }
    }
    p1->num_moves=1;//
    if(2*MOVE_HORIZON-1==rounds){
       x++;
       p1->option[x]=p1->num_wins/p1->num_moves;
	 p1->num_moves=0;
       p1->num_wins=0;
    }
    p1->right_hand=storage1;
    p1->left_hand=storage2;
    p2->right_hand=player2.right_hand;
    p2->left_hand=player2.left_hand;
    if(p1->right_hand>0 && !right_exchange(p1, i)){
      new_storage1=p1->right_hand;
      new_storage2=p1->left_hand;
      if(!(new_storage1==storage2 && new_storage2==storage1)){
	if(rounds%2==0)
	  p2->num_moves++;
	if(player1_recursion(p2, p1, rounds)){
	  p1->right_hand=new_storage1;
	  p1->left_hand=new_storage2;
	  p2->right_hand=player2.right_hand;
	  p2->left_hand=player2.left_hand;
	  if(rounds%2==0)
            p2->num_wins++;
	  if(rounds%2!=0)
	    return true;
	}
    
	else if(rounds%2==0)
	  val=false;
      }
    }
    p1->num_moves=1;//
    if(2*MOVE_HORIZON-1==rounds){
      x++;
      p1->option[x]=p1->num_wins/p1->num_moves;
         p1->num_moves=0;
       p1->num_wins=0;
    }
    p1->right_hand=storage1;
    p1->left_hand=storage2;
    p2->left_hand=player2.left_hand;
    p2->right_hand=player2.right_hand;
  }
  if(rounds%2==0)
    return val;
  else
    return false;
}

int add(int player1_hand, int player2_hand)
{
  
  if(player1_hand>0 && player2_hand>0)
    return (player1_hand+player2_hand)%5;
  else 
    return player2_hand;
}

bool right_exchange(player *player1, int value)
{
  if(value<=player1->right_hand)
    {
      player1->left_hand=(player1->left_hand+value)%5;
      player1->right_hand=(player1->right_hand-value)%5;
      if(death(*player1))
	return true;
      else
	return false;
    }
  else
    return true;
}

bool  left_exchange(player *player1, int value)
{
  if(value<=player1->left_hand)
    {
      player1->right_hand=(player1->right_hand+value)%5;
      player1->left_hand=(player1->left_hand-value)%5;
      if(death(*player1))
	return true;
      else
	return false;
    }
  else
    return true;
}

bool death(player player1)
{
  if(player1.right_hand==0 && player1.left_hand==0)
    return true;
  else
    return false;
}
   

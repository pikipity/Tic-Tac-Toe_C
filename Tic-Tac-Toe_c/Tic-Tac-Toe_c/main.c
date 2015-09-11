# include <stdio.h>
# define boolean char
# define True 1
# define False 0

void game_move(char *pieces, char next_pieces, char *turn){
    if (*turn==0){
        pieces[2]=pieces[1];
        pieces[1]=pieces[0];
        pieces[0]=next_pieces;
    }else{
        pieces[5]=pieces[4];
        pieces[4]=pieces[3];
        pieces[3]=next_pieces;
    }
    if (*turn==0) {
        *turn=1;
    }else{
        *turn=0;
    }
}

void game_display(char pieces[6]){
    // human: A, B, C
    //Computer 1, 2, 3
    char default_displayment[6]="______";
    if (pieces[1]==0 && pieces[2]==0){
        if (pieces[3]==0 && pieces[4]==0 && pieces[5]==0) {
            default_displayment[0]='A';
        }else{
            default_displayment[0]='A';
            default_displayment[3]='1';
        }
    }else if (pieces[2]==0){
        if (pieces[4]==0 && pieces[5]==0) {
            default_displayment[1]='A';
            default_displayment[0]='B';
            default_displayment[3]='1';
        }else{
            default_displayment[1]='A';
            default_displayment[0]='B';
            default_displayment[4]='1';
            default_displayment[3]='2';
        }
    }else{
        if (pieces[5]==0) {
            default_displayment[0]='C';
            default_displayment[1]='B';
            default_displayment[2]='A';
            default_displayment[3]='2';
            default_displayment[4]='1';
        }else{
            default_displayment[0]='C';
            default_displayment[1]='B';
            default_displayment[2]='A';
            default_displayment[3]='3';
            default_displayment[4]='2';
            default_displayment[5]='1';
        }
    }
    char game_displayment[9]="_________";
    for (char i=1; i<10; i++) {
        for (char k=0; k<6; k++) {
            if (pieces[k]==i) {
                game_displayment[i-1]=default_displayment[k];
            }
        }
    }
    printf("%c|%c|%c\n%c|%c|%c\n%c|%c|%c\n\n",game_displayment[0],game_displayment[1]
           ,game_displayment[2],game_displayment[3],game_displayment[4],game_displayment[5]
           ,game_displayment[6],game_displayment[7],game_displayment[8]);
}

void game_user_input(char * pieces, char * turn){
    int next_piece=0;
    while(1){
        printf("Input: ");
        scanf("%i",&next_piece);
        if (next_piece>0 && next_piece<10) {
            boolean exist=False;
            for (char i=0; i<6; i++) {
                if (pieces[i]==next_piece) {
                    exist=True;
                    break;
                }
            }
            if (exist) {
                printf("Input exists. Please input again.\n");
            }else{
                game_move(pieces, next_piece, turn);
                game_display(pieces);
                break;
            }
        }else{
            printf("Input must be 1~9!! Please input again.\n");
        }
    }
}

boolean element_in_array(char element, char * array, char start_point,
                         char end_point){
    boolean result=0;
    for (char i=start_point; i<end_point; i++) {
        if (element==array[i]) {
            result=1;
            break;
        }
    }
    return result;
}

char evaluation(char * pieces){
    char result=0; //0: no result, 1: human win, 2: computer win
    if ((element_in_array(1,pieces,0,3) && element_in_array(2,pieces,0,3) && element_in_array(3,pieces,0,3))
        ||
        (element_in_array(4,pieces,0,3) && element_in_array(5,pieces,0,3) && element_in_array(6,pieces,0,3))
        ||
        (element_in_array(7,pieces,0,3) && element_in_array(8,pieces,0,3) && element_in_array(9,pieces,0,3))
        ||
        (element_in_array(1,pieces,0,3) && element_in_array(4,pieces,0,3) && element_in_array(7,pieces,0,3))
        ||
        (element_in_array(2,pieces,0,3) && element_in_array(5,pieces,0,3) && element_in_array(8,pieces,0,3))
        ||
        (element_in_array(3,pieces,0,3) && element_in_array(6,pieces,0,3) && element_in_array(9,pieces,0,3))
        ||
        (element_in_array(1,pieces,0,3) && element_in_array(5,pieces,0,3) && element_in_array(9,pieces,0,3))
        ||
        (element_in_array(3,pieces,0,3) && element_in_array(5,pieces,0,3) && element_in_array(7,pieces,0,3))
        ) {
        result=1;
    }else if(
             (element_in_array(1,pieces,3,6) && element_in_array(2,pieces,3,6) && element_in_array(3,pieces,3,6))
             ||
             (element_in_array(4,pieces,3,6) && element_in_array(5,pieces,3,6) && element_in_array(6,pieces,3,6))
             ||
             (element_in_array(7,pieces,3,6) && element_in_array(8,pieces,3,6) && element_in_array(9,pieces,3,6))
             ||
             (element_in_array(1,pieces,3,6) && element_in_array(4,pieces,3,6) && element_in_array(7,pieces,3,6))
             ||
             (element_in_array(2,pieces,3,6) && element_in_array(5,pieces,3,6) && element_in_array(8,pieces,3,6))
             ||
             (element_in_array(3,pieces,3,6) && element_in_array(6,pieces,3,6) && element_in_array(9,pieces,3,6))
             ||
             (element_in_array(1,pieces,3,6) && element_in_array(5,pieces,3,6) && element_in_array(9,pieces,3,6))
             ||
             (element_in_array(3,pieces,3,6) && element_in_array(5,pieces,3,6) && element_in_array(7,pieces,3,6))
        ){
        result=2;
    }
    return result;
}

char score(char pieces[6], char turn){
    char result1=0;//human
    char result2=0;//computer
    for (char i=1; i<4; i++) {
        if (element_in_array(3*i-2,pieces,0,3)+element_in_array(3*i-1,pieces,0,3)+element_in_array(3*i,pieces,0,3)==3) {
            result1+=10;
        }else if (element_in_array(3*i-2,pieces,0,3)+element_in_array(3*i-1,pieces,0,3)+element_in_array(3*i,pieces,0,3)==2){
            if (element_in_array(3*i-2,pieces,3,6)+element_in_array(3*i-1,pieces,3,6)+element_in_array(3*i,pieces,3,6)==0) {
                result1+=5;
            }else{
                result2+=5;
            }
        }else if (element_in_array(3*i-2,pieces,0,3)+element_in_array(3*i-1,pieces,0,3)+element_in_array(3*i,pieces,0,3)==1){
            if (element_in_array(3*i-2,pieces,3,6)+element_in_array(3*i-1,pieces,3,6)+element_in_array(3*i,pieces,3,6)==0) {
                result1+=1;
            }else{
                result2+=1;
            }
        }
    }
    for (char i=1; i<4; i++) {
        if (element_in_array(i,pieces,0,3)+element_in_array(3+i,pieces,0,3)+element_in_array(6+i,pieces,0,3)==3) {
            result1+=10;
        }else if (element_in_array(i,pieces,0,3)+element_in_array(3+i,pieces,0,3)+element_in_array(6+i,pieces,0,3)==2){
            if (element_in_array(i,pieces,3,6)+element_in_array(3+i,pieces,3,6)+element_in_array(6+i,pieces,3,6)==0) {
                result1+=5;
            }else{
                result2+=5;
            }
        }else if (element_in_array(i,pieces,0,3)+element_in_array(3+i,pieces,0,3)+element_in_array(6+i,pieces,0,3)==1){
            if (element_in_array(i,pieces,3,6)+element_in_array(3+i,pieces,3,6)+element_in_array(6+i,pieces,3,6)==0) {
                result1+=1;
            }else{
                result2+=1;
            }
        }
    }
    for (char i=1; i<3; i++) {
        if (element_in_array(5-2*i,pieces,0,3)+element_in_array(5,pieces,0,3)+element_in_array(5+2*i,pieces,0,3)==3) {
            result1+=10;
        }else if (element_in_array(5-2*i,pieces,0,3)+element_in_array(5,pieces,0,3)+element_in_array(5+2*i,pieces,0,3)==2){
            if (element_in_array(5-2*i,pieces,3,6)+element_in_array(5,pieces,3,6)+element_in_array(5+2*i,pieces,3,6)==0) {
                result1+=5;
            }else{
                result2+=5;
            }
        }else if (element_in_array(5-2*i,pieces,0,3)+element_in_array(5,pieces,0,3)+element_in_array(5+2*i,pieces,0,3)==1){
            if (element_in_array(5-2*i,pieces,3,6)+element_in_array(5,pieces,3,6)+element_in_array(5+2*i,pieces,3,6)==0) {
                result1+=1;
            }else{
                result2+=1;
            }
        }
    }
    
    for (char i=1; i<4; i++) {
        if (element_in_array(3*i-2,pieces,3,6)+element_in_array(3*i-1,pieces,3,6)+element_in_array(3*i,pieces,3,6)==3) {
            result2+=10;
        }else if (element_in_array(3*i-2,pieces,3,6)+element_in_array(3*i-1,pieces,3,6)+element_in_array(3*i,pieces,3,6)==2){
            if (element_in_array(3*i-2,pieces,0,3)+element_in_array(3*i-1,pieces,0,3)+element_in_array(3*i,pieces,0,3)==0) {
                result2+=5;
            }else{
                result1+=5;
            }
        }else if (element_in_array(3*i-2,pieces,3,6)+element_in_array(3*i-1,pieces,3,6)+element_in_array(3*i,pieces,3,6)==1){
            if (element_in_array(3*i-2,pieces,0,3)+element_in_array(3*i-1,pieces,0,3)+element_in_array(3*i,pieces,0,3)==0) {
                result2+=1;
            }else{
                result1+=1;
            }
        }
    }
    for (char i=1; i<4; i++) {
        if (element_in_array(i,pieces,3,6)+element_in_array(3+i,pieces,3,6)+element_in_array(6+i,pieces,3,6)==3) {
            result2+=10;
        }else if (element_in_array(i,pieces,3,6)+element_in_array(3+i,pieces,3,6)+element_in_array(6+i,pieces,3,6)==2){
            if (element_in_array(i,pieces,0,3)+element_in_array(3+i,pieces,0,3)+element_in_array(6+i,pieces,0,3)==0) {
                result2+=5;
            }else{
                result1+=5;
            }
        }else if (element_in_array(i,pieces,3,6)+element_in_array(3+i,pieces,3,6)+element_in_array(6+i,pieces,3,6)==1){
            if (element_in_array(i,pieces,0,3)+element_in_array(3+i,pieces,0,3)+element_in_array(6+i,pieces,0,3)==0) {
                result2+=1;
            }else{
                result1+=1;
            }
        }
    }
    for (char i=1; i<3; i++) {
        if (element_in_array(5-2*i,pieces,3,6)+element_in_array(5,pieces,3,6)+element_in_array(5+2*i,pieces,3,6)==3) {
            result2+=10;
        }else if (element_in_array(5-2*i,pieces,3,6)+element_in_array(5,pieces,3,6)+element_in_array(5+2*i,pieces,3,6)==2){
            if (element_in_array(5-2*i,pieces,0,3)+element_in_array(5,pieces,0,3)+element_in_array(5+2*i,pieces,0,3)==0) {
                result2+=5;
            }else{
                result1+=5;
            }
        }else if (element_in_array(5-2*i,pieces,3,6)+element_in_array(5,pieces,3,6)+element_in_array(5+2*i,pieces,3,6)==1){
            if (element_in_array(5-2*i,pieces,0,3)+element_in_array(5,pieces,0,3)+element_in_array(5+2*i,pieces,0,3)==0) {
                result2+=1;
            }else{
                result1+=1;
            }
        }
    }
    
    if (turn==0) {
        return result1-result2;
    }else{
        return result2-result1;
    }
    
}

void nagmaxsearch(char * result, char act_pieces[6], char act_turn, char depth, char possible_piece)
{
    //result[0]=score, result[1]=best_piece
    if (depth==0) {
        result[0]=score(act_pieces, act_turn);
        result[1]=possible_piece;
        return;
    }else{
        result[0]=-50;
        result[1]=0;
        for (char piece=1; piece<10; piece++) {
            if (!element_in_array(piece, act_pieces, 0, 6)) {
                char pieces[6];
                for (char i=0; i<6; i++) {
                    pieces[i]=act_pieces[i];
                }
                char turn=act_turn;
                game_move(pieces, piece, &turn);
                char part_result[2]={0,0};
                nagmaxsearch(part_result, pieces, turn, depth-1, piece);
                part_result[0]*=-1;
                if (part_result[0]>result[0]) {
                    result[0]=part_result[0];
                    result[1]=piece;
                }
            }
        }
    }
}


int main(int argc, const char * argv[])
{
    //Init Game
    char pieces[6]={0,0,0,0,0,0}; // first 3: human, last 3 for computer
    char preview_steps=3;
    char turn=0; //0: human, 1: compute
    char result=0;
    //
    while(1){
        if (turn==0) {
            //human input
            printf("Human Turn\n1|2|3\n4|5|6\n7|8|9\n");
            game_user_input(pieces, &turn);
        }else{
            //computer calculate
            printf("Computer Turn\n");
            char inference_result[2]={0,0};
            nagmaxsearch(inference_result, pieces, turn, preview_steps, 0);
            game_move(pieces, inference_result[1], &turn);
            game_display(pieces);
        }
        //display result
        result=evaluation(pieces);
        if (result==1) {
            printf("Human Win\n");
            break;
        }else if (result==2){
            printf("Computer Win\n");
            break;
        }
    }
    //
    return 0;
}


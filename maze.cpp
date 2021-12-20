/* 
maze.cpp

Author: Kevin Shu

Short description of this file:
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;

   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
   mymaze = read_maze(argv[1], &rows, &cols); // FILL THIS IN
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   // when working on Checkpoint 3, you will call maze_search here.
   // here. but for Checkpoint 1, just assume we found the path.
   result = maze_search(mymaze, rows, cols); // TO BE CHANGED
   
   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // ADD CODE HERE to delete all memory 
   // that read_maze allocated
   for (int i = 0; i<rows; i++){
      delete[] mymaze[i];
   }
   delete[] mymaze;


   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
   int Scount = 0;
   int Fcount = 0;
   Location start;
   Queue q(rows*cols);
   bool solved = false;

   for (int i = 0; i< rows; i++){
      for (int j = 0; j< cols; j++){
         if (maze[i][j] == 'S'){
            start.row = i;
            start.col = j;
            Scount++;
         }
         if (maze[i][j] == 'F'){
            Fcount++;
         }
      }
   }
   if (Fcount != 1 || Scount != 1){
      return -1;
   }

   // initializing visited matrix to all equal 0 and setting start to 1
   int** visited = new int*[rows];
   for (int i = 0; i<rows; i++){
      visited[i] = new int[cols];
      for (int j = 0; j< cols; j++){
         visited[i][j] = 0;
      }
   }
   visited[start.row][start.col] = 1;
   
   //initializing predecessor matrix to all have locations of (-1, -1)
   Location** pred = new Location*[rows];
   for (int i = 0; i< rows; i++){
      pred[i] = new Location[cols];
      for (int j = 0; j< cols; j++){
         pred[i][j].row = -1;
         pred[i][j].col = -1;
      }
   }

   //start BFS algorithm
   q.add_to_back(start);
   Location curr;
   while (!q.is_empty()){
      curr = q.remove_from_front();
      //Checking the northern position
      if (curr.row-1>=0){
         if (maze[curr.row-1][curr.col] != '#' && visited[curr.row-1][curr.col] == 0){
            if (maze[curr.row-1][curr.col] == 'F'){
               //track back now
               while(maze[curr.row][curr.col] != 'S'){
                  Location temp;
                  maze[curr.row][curr.col] = '*';
                  temp.row = pred[curr.row][curr.col].row;
                  temp.col = pred[curr.row][curr.col].col;
                  curr.row = temp.row;
                  curr.col = temp.col;
               }
               solved = true;
            }
            else{
               Location north;
               north.row = curr.row-1;
               north.col = curr.col;
               q.add_to_back(north);
               visited[curr.row-1][curr.col] = 1;
               pred[curr.row-1][curr.col].row=curr.row;
               pred[curr.row-1][curr.col].col=curr.col; 
            }
         }  
      }
      //checking southern position
      if (curr.row + 1<rows){
         if (maze[curr.row+1][curr.col] != '#' && visited[curr.row+1][curr.col] == 0){
            if (maze[curr.row+1][curr.col] == 'F'){
               //track back now
               while(maze[curr.row][curr.col] != 'S'){
                  Location temp;
                  maze[curr.row][curr.col] = '*';
                  temp.row = pred[curr.row][curr.col].row;
                  temp.col = pred[curr.row][curr.col].col;
                  curr.row = temp.row;
                  curr.col = temp.col;
               }
               solved = true;
            }
            else{
               Location south;
               south.row = curr.row+1;
               south.col = curr.col;
               q.add_to_back(south);
               visited[curr.row+1][curr.col] = 1;
               pred[curr.row+1][curr.col].row=curr.row;
               pred[curr.row+1][curr.col].col=curr.col; 
            }
         }  
      }
      //Checking eastern position
      if (curr.col+1<cols){
         if (maze[curr.row][curr.col+1] != '#' && visited[curr.row][curr.col+1] == 0){
            if (maze[curr.row][curr.col+1] == 'F'){
               //track back now
               while(maze[curr.row][curr.col] != 'S'){
                  Location temp;
                  maze[curr.row][curr.col] = '*';
                  temp.row = pred[curr.row][curr.col].row;
                  temp.col = pred[curr.row][curr.col].col;
                  curr.row = temp.row;
                  curr.col = temp.col;
               }
               solved = true;
            }
            else{
               Location east;
               east.row = curr.row;
               east.col = curr.col+1;
               q.add_to_back(east);
               visited[curr.row][curr.col+1] = 1;
               pred[curr.row][curr.col+1].row=curr.row;
               pred[curr.row][curr.col+1].col=curr.col; 
            }
         }  
      }
      //Checking western position
      if (curr.col-1>=0){
         if (maze[curr.row][curr.col-1] != '#' && visited[curr.row][curr.col-1] == 0){
            if (maze[curr.row][curr.col-1] == 'F'){
               //track back now
               while(maze[curr.row][curr.col] != 'S'){
                  Location temp;
                  maze[curr.row][curr.col] = '*';
                  temp.row = pred[curr.row][curr.col].row;
                  temp.col = pred[curr.row][curr.col].col;
                  curr.row = temp.row;
                  curr.col = temp.col;
               }
               solved = true;
            }
            else{
               Location north;
               north.row = curr.row;
               north.col = curr.col-1;
               q.add_to_back(north);
               visited[curr.row][curr.col-1] = 1;
               pred[curr.row][curr.col-1].row=curr.row;
               pred[curr.row][curr.col-1].col=curr.col; 
            }
         }  
      }
      
      if (solved){
         break;
      }
   }

   for (int i=0;i<rows;i++){
       delete[] pred[i];
       delete[] visited[i]; 
   }
   delete [] visited;
   delete [] pred; 
   if (solved){
       return 1;
   }

   return 0; // DELETE this stub, it's just for Checkpoint 1 to compile.
}

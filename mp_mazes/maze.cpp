/* Your code here! */
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "maze.h"
#include <queue>
#include <algorithm>


SquareMaze::SquareMaze(){ 
    height_ = width_ = 0;
 //leaving the constructor empty so that it doesnt make a random image when we call sqaure maze with no height and width passed in as paramete
}

    /**
     * Makes a new SquareMaze of the given height and width.
     *
     * If this object already represents a maze it will clear all the
     * existing data before doing so. You will start with a square grid (like
     * graph paper) with the specified height and width. You will select
     * random walls to delete without creating a cycle, until there are no
     * more walls that could be deleted without creating a cycle. Do not
     * delete walls on the perimeter of the grid.
     *
     * Hints: You only need to store 2 bits per square: the "down" and
     * "right" walls. The finished maze is always a tree of corridors.)
     *
     * @param width The width of the SquareMaze (number of cells)
     * @param height The height of the SquareMaze (number of cells)
     */
void SquareMaze::makeMaze(int width, int height){
    // if the maze already exists clear all data from the vector
    Dset.elementvect.clear(); 
    height_ = height;
    width_ = width;
    squarevect.resize(width,std::vector<square>(height));// i resize my vector of structs as with the given height and width
    Dset.addelements(width*height);

    // now we call the random function to get a random value between 0 to height*width

    while(Dset.size(0) < width*height){ // we keep on andomly generating the value untill size of the root is less than the total size of the width

    int randwall = rand() % 2; // either 0 or 1 to check which wall we want to break 0-> right; 1 -> bottom
    int x_ = rand() % width;
    int y_ = rand() % height;

    // CHECK 1: if wall of the idx is on the perimeter of the maze:  
    if(x_ == width - 1 && randwall == 0){ // rightmost perimenter so it cant have 1 to delete the wall so break 
        continue;
    }
    if (y_ == height - 1 && randwall == 1){ //bottomost perimeter, so it cant have 0 to delete the wall so break
        continue;
    }


    // CHECK 2: if the wall is already broken
    if(randwall == 0 ){
        if(!(squarevect[x_][y_].down)){continue;}
    }
    if(randwall == 1 ){
        if(!(squarevect[x_][y_].right)){continue;}
    }    
    // CHECK 3:  It shouldn't form a  loop 
    // depending on the wall to be broken we find the cordinate
    int next = 0;
    if(randwall == 0){
        if(x_ <= width -1 ){
        next = x_ + 1 + (y_)*width; 
    }
    else{continue;}
    }
    else{
        if(y_ <= height -1 ){
        next = x_ + (y_+1)*width; 
    }
    else{continue;}
    }
    // if the find of both the sets are not equal then we can break the wall 
    int a = Dset.find(next);
    int b = Dset.find(x_ + (y_*width));
    if(a != b){
        setWall(x_,y_,randwall,false);
        Dset.setunion(a,b);
    }
}
}

bool SquareMaze::canTravel(int x, int y, int dir) const{ 
    // this functions is responsible for taking in the x and y coordinate and then checking if we can move in a certain direction depending on the parameter that is passed on
    // 4 dir conditiions to check in 4 directions
    // out of bounds check
    if(x >= width_  || y >= height_ ){
        return false;
    }
    // 4 direction check 
    if(dir == 0 && squarevect[x][y].right){
        return false;
    }
    else if(dir == 1 && squarevect[x][y].down){
        return false;
        }
    else if(dir == 2){
        if (x <= 0 || (squarevect[x-1][y].right)){
            return false;
        } 
            return true;
    }
    else if(dir == 3){
        if (y <= 0 || (squarevect[x][y-1].down)){
            return false;
        } 
            return true;
    }
    // all possible conditions that can be false are set as false
    else {
        return true; // indicating that it can be travelled
    }
}

    /**
     * Sets whether or not the specified wall exists.
     *
     * This function should be fast (constant time). You can assume that in
     * grading we will not make your maze a non-tree and then call one of the
     * other member functions. setWall should not prevent cycles from
     * occurring, but should simply set a wall to be present or not present.
     * Our tests will call setWall to copy a specific maze into your
     * implementation.
     *
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir Either 0 (right) or 1 (down), which specifies which wall to
     * set (same as the encoding explained in canTravel). You only need to
     * support setting the bottom and right walls of every square in the grid.
     * @param exists true if setting the wall to exist, false otherwise
     */
    void SquareMaze::setWall(int x, int y, int dir, bool exists){ 
        if(x >= height_ || y >= width_ || x < 0 || y < 0){
            return ;
            }
        // so for the given coordinate, set the wall to wtv is the value of exists
        if(dir == 0 ){
            squarevect[x][y].right = exists;
        }
        else if (dir == 1){
            squarevect[x][y].down = exists;
        }
    }

    /**
     * Solves this SquareMaze.
     *
     * For each square on the bottom row (maximum y coordinate), there is a
     * distance from the origin (i.e. the top-left cell), which is defined as
     * the length (measured as a number of steps) of the only path through
     * the maze from the origin to that square.
     *
     * Select the square in the bottom row with the largest distance from the
     * origin as the destination of the maze. solveMaze() returns the
     * winning path from the origin to the destination as a vector of
     * integers, where each integer represents the direction of a step, using
     * the same encoding as in canTravel().
     *
     * If multiple paths of maximum length exist, use the one with the
     * destination cell that has the smallest x value.
     *
     * Hint: this function should run in time linear in the number of cells
     * in the maze.
     *
     * @return a vector of directions taken to solve the maze
     */
    std::vector<int> SquareMaze::solveMaze(){
        // each square on the bottom row 
        // length of each cell from the top left corner(origin)
        std::vector<std::vector<int>> distance(width_,std::vector<int>(height_,-1)); // this vector stores the information about the visitation rights
        std::queue<std::pair<int, int>> tempque; // this queue is for BFS without recurrsion ; It is storing each cell that is possible to stored, this stores the x and y coordinate
        std::vector<int> result; // vector to store the direction along the way

        // PART 1: so our implementation is used to set calculate the distance of each of our point from the origin
        // PART 2: once we do that, we find the largest distance in the bottomost row and and then set that to be our end point
        // PART 3: once we have our end point we back trace to our location while putting in the direction onto our direction vector


     // PART 1 : so we created a 2d vector called distance, which will store the distance from origin to all the values and set all of it to -1
     std::pair<int,int> origin(0,0);
     tempque.push(origin); // push the initial origin onto the queue
     distance[0][0] = 0; // distance to itself should be zero 
     while(tempque.empty()== false){
        std::pair<int, int> tempoint;
        tempoint = tempque.front();
        tempque.pop();
        // Back tracing algorithim for right bottom left top ->
        // Check if it can go right 
        if (canTravel(tempoint.first,tempoint.second,0) && (distance[tempoint.first+1][tempoint.second] == -1) ){ // right
            distance[tempoint.first + 1][tempoint.second] = distance[tempoint.first][tempoint.second] + 1;
            tempque.push(std::make_pair(tempoint.first + 1,tempoint.second));
        }
        if (canTravel(tempoint.first,tempoint.second,1) && (distance[tempoint.first][tempoint.second + 1] == -1) ){ // bottom
            distance[tempoint.first][tempoint.second+1] = distance[tempoint.first][tempoint.second] + 1;
            tempque.push(std::make_pair(tempoint.first,tempoint.second + 1));
        }
        if (canTravel(tempoint.first,tempoint.second,2) && (distance[tempoint.first-1][tempoint.second] == -1) ){ // left 
            distance[tempoint.first - 1][tempoint.second] = distance[tempoint.first][tempoint.second] + 1;
            tempque.push(std::make_pair(tempoint.first - 1,tempoint.second));
        }
        if (canTravel(tempoint.first,tempoint.second,3) && (distance[tempoint.first][tempoint.second-1] == -1) ){ // top 
            distance[tempoint.first][tempoint.second - 1] = distance[tempoint.first][tempoint.second] + 1;
            tempque.push(std::make_pair(tempoint.first,tempoint.second - 1));
        }        
     }

     // PART 2 : Find the largest distance in the bottom row
     int maxdist = 0;
     int max_x;
     int y = 0 ;
     for(int i = 0; i < width_ ; i++){
        if(distance[i][height_-1] > maxdist){
            maxdist = distance[i][height_-1];
            max_x = i;
        }
     }
     //so now we have to traverse from 0,0 to max_x,width_-1;
     // our result vecctor will be maxdist long
     // we start and we domt have to worry about backtracing because we have already taken care of calculating the distance in such a way that the path with incrmenting distance is already creating a path
     // so If we just follow that and push those values on to the vector we should end up with our locations
     // PART 3 : once we have our end point we back trace to our location while putting in the direction onto our result vector
     int tempdist = 0;
     int tempx = max_x;
     int tempy = height_-1;

    while(tempdist != maxdist){
        if(canTravel(tempx,tempy,0) && (distance[tempx+1][tempy] == distance[tempx][tempy]- 1)){ // right 
            result.push_back(2);
            tempdist++;
            tempx = tempx + 1;
            continue;
        }
         if(canTravel(tempx,tempy,1) && (distance[tempx][tempy+1] == distance[tempx][tempy]- 1)){ // bottom 
            result.push_back(3);
            tempdist++;
            tempy = tempy + 1;
            continue;
         }
        if(canTravel(tempx,tempy,2) && (distance[tempx-1][tempy] == distance[tempx][tempy]- 1)){ // left
            result.push_back(0);
            tempdist++;
            tempx = tempx - 1;
            continue;
        }
        if(canTravel(tempx,tempy,3) && (distance[tempx][tempy-1] == distance[tempx][tempy]- 1)){ // top
            result.push_back(1);
            tempdist++;
            tempy = tempy - 1;
            continue;
        }
            
    }
    std::reverse(result.begin(), result.end());
    return result;
    }

    /**
     * Draws the maze without the solution.
     *
     * First, create a new PNG. Set the dimensions of the PNG to
     * (width*10+1,height*10+1). where height and width were the arguments to
     * makeMaze. Blacken the entire topmost row and leftmost column of
     * pixels, except the entrance (1,0) through (9,0). 

     * For each square in the maze, call its maze coordinates (x,y). If the right wall exists,
     * then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from
     * 0 to 10. If the bottom wall exists, then blacken the pixels with
     * coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
     *
     * The resulting PNG will look like the sample image, except there will
     * be no exit from the maze and the red line will be missing.
     *
     * @return a PNG of the unsolved SquareMaze
     */
    cs225::PNG* SquareMaze::drawMaze() const{ 
        cs225::PNG* image = new cs225::PNG((width_ * 10)+1, (height_*10)+1);
        // To blacken the topmost row and leftmost coloumn
        for(int i = 10; i < (width_ * 10)+1 ; i++){
            image->getPixel(i,0).l=0;
        }
        for(int j = 0; j < (height_*10)+1 ; j++){
            image->getPixel(0,j).l=0;
        }
    // now we set the walls for each maze
    for(int i = 0; i < width_ ; i++){
        for(int j = 0; j < height_ ; j++){
            if(squarevect[i][j].right){
                for(int k = 0 ; k<=10 ; k++){
                image->getPixel((i+1)*10,j*10+k).l = 0;
                }
            }
            if(squarevect[i][j].down){
                for(int k = 0 ; k<=10 ; k++){
                image->getPixel(i*10+k,(j+1)*10).l = 0;
                }
            }
        }
    }
    return image;
    }

    /**
     * This function calls drawMaze, then solveMaze; it modifies the PNG
     * from drawMaze to show the solution vector and the exit.
     *
     * Start at pixel (5,5). Each direction in the solution vector
     * corresponds to a trail of 11 red pixels in the given direction. If the
     * first step is downward, color pixels (5,5) through (5,15) red. (Red is
     * 0,1,0.5,1 in HSLA). Then if 1the second step is right, color pixels (5,15)
     * through (15,15) red. Then if the third step is up, color pixels
     * (15,15) through (15,5) red. Continue in this manner until you get to
     * the end of the solution vector, so that your output looks analogous
     * the above picture.
     *
     * Make the exit by undoing the bottom wall of the destination square:
     * call the destination maze coordinates (x,y), and whiten the pixels
     * with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
     *
     * @return a PNG of the solved SquareMaze
     */
    cs225::PNG* SquareMaze::drawMazeWithSolution(){ 

    cs225::PNG* sol_png = drawMaze();
    std::vector<int> direcvect = solveMaze(); // this vector will give us the direction in which we want to move in
    // for(unsigned int i = 0; i < direcvect.size(); i++) {
    //     std::cout << direcvect[i] << " ";
    // }
     
    int startx = 5;
    int starty = 5;
    for(unsigned int i = 0; i < direcvect.size(); i++){
        // if (startx >= width_){
        //     startx = startx % width_;
        // }
        // if (starty >= height_){
        //     starty = starty % height_;
        // }
        int j = direcvect[i];
        if(j == 0){ // draw in right direction for 11 pixels
            for(int j = 0; j < 11 ; j++){
                sol_png->getPixel(startx + j,starty).h = 0;
                sol_png->getPixel(startx + j,starty).s = 1;
                sol_png->getPixel(startx + j,starty).l = 0.5;
                sol_png->getPixel(startx + j,starty).a = 1;
            }
            startx+=10;

        }
        else if(j == 1){ // draw in down direction for 11 pixels
            for(int j = 0; j < 11 ; j++){
                sol_png->getPixel(startx,starty + j).h = 0;
                sol_png->getPixel(startx,starty + j).s = 1;
                sol_png->getPixel(startx,starty + j ).l = 0.5;
                sol_png->getPixel(startx,starty + j).a = 1;
            }
            starty+=10;
        }
        else if(j == 2){ // draw in left direction for 11 pixels
            for(int j = 0; j < 11 ; j++){
                sol_png->getPixel(startx - j,starty).h = 0;
                sol_png->getPixel(startx - j,starty).s = 1;
                sol_png->getPixel(startx - j,starty).l = 0.5;
                sol_png->getPixel(startx - j,starty).a = 1;
            }
            startx-=10;
        }
        else if(j == 3){ // draw in up direction for 11 pixels 
            for(int j = 0; j < 11 ; j++){
                sol_png->getPixel(startx,starty - j).h = 0;
                sol_png->getPixel(startx,starty - j ).s = 1;
                sol_png->getPixel(startx,starty - j).l = 0.5;
                sol_png->getPixel(startx,starty - j).a = 1;
            }
            starty-=10;
        }
    }
    startx = startx - 5; 
    starty = starty + 5; 
        
    for (int k = 1; k <= 9; k ++) {
        sol_png->getPixel(startx + k, starty).l = 1;
        }
    
    return sol_png;
    }



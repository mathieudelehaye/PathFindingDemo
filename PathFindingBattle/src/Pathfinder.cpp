#include "pathfinder.h"

Pathfinder::Pathfinder(Room* ar) : openNodes (ar->horizontalSize, ar->verticalSize, 0), 
closedNodes (ar->horizontalSize, ar->verticalSize, 0), 
dir_map (ar->horizontalSize, ar->verticalSize, 0) { 
    associatedRoom = ar; 
    computedPath= ""; 
    computedPathLength = 0; 
    computingTimeInMs = 0.0; 
}

/** why do we maintain a priority queue?
* it's for maintaining the open list: eve 
* A priority queue is a data structure in which only the largest element can be retrieved (popped).
* It's problem is that finding an node in the queue is a slow operation.
**/
bool Pathfinder::calculatePath(const int & xStart, const int & yStart,const int & xFinish, const int & yFinish) {
    clock_t start = clock(); // assess computing time 
    priority_queue<Node> pq[2]; //we define 2 priority list which is needed for our priority change of a node 'algo'
    Node * startNode; Node * currentNode; Node * neighborNode;  
    int index = 0, nodeX, nodeY, neighborX, neighborY, parentDir, destDir, fsmState = 1;  
    bool quitFSM = false;
    string path="";

    //first reset maps
    resetMaps();
    #ifdef DEBUG_PATHFINDING
        // openNodes.display();
    #endif 

    //create start node
    startNode = new Node(xStart,yStart,0,0);
    startNode->updatePriority(xFinish, yFinish);
    // push it into the priority queue
    pq[index].push(*startNode);
    //add it to the list of open nodes
    openNodes.setValueAt(startNode->getxPos(),startNode->getyPos(),startNode->getPriority());
    #ifdef DEBUG_PATHFINDING
        // openNodes.display();
        // cout << "Initial node: " << xStart << " " << yStart << " " << xFinish << " " << yFinish << "\n"; 
    #endif 

    //A* search
    // initial string path is empty 
    while(!quitFSM)
    {
        switch(fsmState)
        {
            case 1: 
                //while priority queue is not empty; continue
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 1 "; 
                #endif
                if(pq[index].empty()) fsmState = 10;
                else fsmState = 2;
                break;
            case 2:
                //get current node with the higest priority from the priority list.  In first instance this is the start node
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 2 "; 
                #endif
                currentNode = new Node(pq[index].top().getxPos(),
                pq[index].top().getyPos(),
                pq[index].top().getDistance(),
                pq[index].top().getPriority());  
                //remove node from priority queue
                pq[index].pop();
                openNodes.setValueAt(currentNode->getxPos(),currentNode->getyPos(),0);  //remove node from open list
                #ifdef DEBUG_PATHFINDING
                    // openNodes.display();
                #endif 
                closedNodes.setValueAt(currentNode->getxPos(),currentNode->getyPos(),1); //add current node to closed list
                // if current node = goal => finished => retrace route back using parents nodes
                if (currentNode->getxPos()==xFinish && currentNode->getyPos()==yFinish) fsmState = 3;
                else {
                    currentNode->resetNeighborSearch();  // reset current node neighbor search 
                    fsmState = 4;
                }
                break;
            case 3:
                // quit searching if goal is reached
                //currentNode is now the goalNode
                // compute final path and return it.  
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 3 "; 
                #endif
                nodeX=currentNode->getxPos();
                nodeY=currentNode->getyPos();
                while (!(nodeX==xStart && nodeY==yStart)){
                    /* We start at goal and work backwards moving from node to parent
                    * which will take us to the starting node
                    */
                    parentDir=dir_map.getValueAt(nodeX,nodeY);
                    destDir=(parentDir+Position::nbrDir/2)%Position::nbrDir;//invert dir 
                    path = Tools::NumberToString(destDir)+path; //we work our way back
                    #ifdef DEBUG_PATHFINDING
                        cout<<"\nparentDir: "<<parentDir<<" nbrDir: "<<Position::nbrDir<<" destDir: "<<destDir<<" path: "<<path<<" ";  
                    #endif 
                    //iterate trough our dir_map using our defined directions
                    nodeX+=Position::dirX[parentDir];
                    nodeY+=Position::dirY[parentDir];
                }
                //garbage collection; the memory allocated with 'new' should be freed to avoid memory leaks
                delete currentNode;
                while (!pq[index].empty()){
                    pq[index].pop();
                }   
                fsmState = 10; 
                break;
            case 4:
                //while direction queue is not empty, continue
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 4 "; 
                #endif
                if(!currentNode->foundNeighbor()) fsmState = 2;
                else fsmState = 5;
                break;
            case 5:
                //add all possible neighbors to the openlist + define parents for later tracing back (4 directions: right, up, left & down; but we want to make it as extendable as possible) 
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 5 "; 
                #endif
                neighborX = currentNode->getNeighborX (); neighborY = currentNode->getNeighborY ();
                #ifdef DEBUG_PATHFINDING
                    cout<<"\ncurrentNode->getxPos(): "<<currentNode->getxPos()<<" currentNode->getyPos(): "<<currentNode->getyPos()<<" neighborX: "<<neighborX<<" neighborY: "<<neighborY<<" ";  
                #endif 
                //check boundaries, ignore if on closed list (was already evaluted) or if unwalkable 
                if (!(neighborX <1 || neighborY <1 || neighborX > (associatedRoom->horizontalSize) || neighborY > (associatedRoom->verticalSize) || closedNodes.getValueAt(neighborX,neighborY)==1 || 
                    associatedRoom->obstacle_map.getValueAt(neighborX, neighborY)==1)) fsmState = 6;
                else fsmState = 4;
                break;
            case 6:
                //ok -> generate neighbor node
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 6 " ; 
                #endif
                neighborNode = new Node (neighborX,neighborY,currentNode->getDistance(),currentNode->getPriority());
                //calculate the fscore of the node
                neighborNode->updatePriority(xFinish,yFinish);
                neighborNode->updateDistance();
                //if neighbor not in openset => add it
                #ifdef DEBUG_PATHFINDING
                    cout<<"neighborX: "<<neighborX<<", neighborY: "<<neighborY<<", openNodes[neighborX][neighborY]: "<<openNodes.getValueAt(neighborX,neighborY)<<", associatedRoom->verticalSize: "<<associatedRoom->verticalSize
                    <<", associatedRoom->horizontalSize: "<<associatedRoom->horizontalSize<<"\n"; 
                    // openNodes.display();
                    cout<<"neighborX: "<<neighborX<<", neighborY: "<<neighborY<<", openNodes[neighborX][neighborY]: "<<openNodes.getValueAt(neighborX,neighborY)<<"\n"; 
                #endif                     
                if(openNodes.getValueAt(neighborX,neighborY)==0) fsmState = 7;
                else fsmState = 8; 
                break;
            case 7:
                //add node to open set and priority queue, fill out direction map
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 7 "; 
                #endif
                openNodes.setValueAt(neighborX,neighborY,neighborNode->getPriority());
                #ifdef DEBUG_PATHFINDING
                    // openNodes.display();
                #endif 
                //add it to the priority queue (by dereferencing our neighborNode object
                //pq is of type node; push inserts a new element;
                //the content is initialized as a copy
                pq[index].push(*neighborNode);
                //set the parent to the node we are currently looking at
                parentDir=(currentNode->getNeighborDir()+Position::nbrDir/2)%Position::nbrDir;
                dir_map.setValueAt(neighborX,neighborY,parentDir);
                #ifdef DEBUG_PATHFINDING
                    cout<<"\nneighborX: "<<neighborX<<" neighborY: "<<neighborY<<" Position::nbrDir: "<<Position::nbrDir<<" "<<" parentDir: "<<parentDir<<" ";  
                #endif
                //if neighbor is already on open set
                //check if path to that node is a better one (=lower gscore) if we use the current node to get there
                fsmState = 4; 
                break;
            case 8:
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 8 "; 
                    // openNodes.display();
                #endif 
                if(openNodes.getValueAt(neighborX,neighborY)>neighborNode->getPriority()) fsmState = 9;  
                else {
                    delete neighborNode;
                    fsmState = 4;     
                }
                break;
            case 9:
                /** lower gscore: change parent of the neighbore node to the select square
                * recalculate fscore
                * the value of the fscore should also be changed inside the node which resides inside our priority queue
                * however as mentioned before this is a very slow operation (is going to be the bottleneck of this implemention probably) 
                * we will have to manuall scan for the right node and then change it.
                *
                * this check is very much needed, but the number of times this if condition is true is limited
                */
                //update fscore inside the open list
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 9 "; 
                #endif
                // openNodes[neighborX][neighborY]=neighborNode->getPriority();
                #ifdef DEBUG_PATHFINDING
                    // openNodes.display();
                #endif 
                //update the parent node
                dir_map.setValueAt(neighborX,neighborY,(currentNode->getNeighborDir()+Position::nbrDir/2)%Position::nbrDir);
                //we copy the nodes from one queue to the other
                //except the -old-current node will be ignored
                #ifdef DEBUG_PATHFINDING
                    cout<<"index: "<<index<<", pq[index].top().getxPos(): "<<pq[index].top().getxPos()<<", pq[index].top().getyPos(): "<<pq[index].top().getyPos()<<", neighborX: "<<neighborX<<", neighborY: "<<neighborY<<"\n"; 
                #endif
                while (!((pq[index].top().getxPos()==neighborX) && (pq[index].top().getyPos()==neighborY))){
                    pq[1-index].push(pq[index].top());
                    pq[index].pop();
                } 
                pq[index].pop(); //remove the -old-current node
                /** ?? **/
                if(pq[index].size()>pq[1-index].size()){ //??? is this extra check necessary?
                    index=1-index; //index switch 1->0 or 0->1
                }
                while(!pq[index].empty()){
                    pq[1-index].push(pq[index].top());
                    pq[index].pop();
                }
                /** ?? **/
                index=1-index; //index switch 1->0 or 0->1
                pq[index].push(*neighborNode); //and the -new-current node will be pushed in instead
                fsmState = 4;
                break;
            case 10:
                #ifdef DEBUG_PATHFINDING_C_NUMBERS
                    cout<<"case 10\n"; 
                #endif
                quitFSM = true;  
                break;
        }
    }
    //update data members and return the generated path 
    clock_t end = clock();
    computedPath= path; 
    computedPathLength = strlen(path.c_str()); 
    computingTimeInMs = double(end - start);
    return true;    // mdelehaye  
}

void Pathfinder::resetMaps() {
    openNodes.reset();
    closedNodes.reset(); 
    dir_map.reset(); 
}

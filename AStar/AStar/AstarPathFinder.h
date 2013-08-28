//------------------------------------------------------------------------------
// PROJECT: The A* Pathfinder base Class
// FILE:   ASTARPATHFINDER.H
// OVERVIEW:
//    -Pretty good working Astar Pathfinder Algorithm  Class.
//    -Based on SPATH.C Author: unknown (thanks)
//					 http://www-cs-students.stanford.edu/~amitp/Articles/spath.zip
//    -Easy to implement, also with Your
//     favorite tiles based map but nevertheless a
//     little bit tricky to handle.
//    -Needs to be optimized or modified, perhaps a pointer to
//     a spritelist to reinitialisize the A* tilemap
//     and prevent sprite collosion.
//	   Let me hear about it.
//	   Have fun!
// Revision: 1.1
// Last Update: 31.08.97
// AUTHOR: pat@das-netz.de Germany 25.07.97
// 为测试程序进行了修改	---TAO	
//
//------------------------------------------------------------------------------

#if !defined(ASTARPATHFINDER_INCLUDE_)
#define ASTARPATHFINDER_INCLUDE_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
//#include "Internal.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
 
//#define SHIFT 6   // change this to reflect the the size.
		           // Ex. 64x64 tile equals 2^6. or a shift of 6
#define TILESIZE 1  // change this also to reflect tile size. 64x64.

class AstarPathfinder
{
	private:
		struct NODE {     // node structure
            long f, h;
    	   	int g, tmpg;
			int x, y;
			int NodeNum;
   	    	NODE *Parent;
    	    NODE *Child[8]; // a node may have upto 8+(NULL) children.
			NODE *NextNode;  // for filing purposes
		};
		NODE *OPEN;    // the node list pointers
		NODE *CLOSED;
		NODE *PATH; // pointer to the best path

		struct STACK {      // the stack structure
	   		NODE *NodePtr;
	        STACK *NextStackPtr;
		};
		STACK *Stack;
		BOOL isPath;   
		int ROWS, // tilemap data members, need to be initialisize
            COLS,         // with current map's width and height
            TOTAL_TILES; // to allocate memory for the
		BYTE *TileMap;  // pointer to the A* own tilemap data array
	public:
      // Modify only these 3 public member functions to support Your favorite Map
	  AstarPathfinder(void);
      ~AstarPathfinder();
	  void InitAstarTileMap(BYTE *pMap, int w,int h);                

      BOOL NewPath(int sx, int sy, int dx, int dy);  // Must be called and be true
      // before getting the node entries. It frees the lists,
      // calls ::Findpath() and returns true if path is accessible

      BOOL ReachedGoal(void); // Call and check this function before using these 3 following
      BOOL PathNextNode(void) 
	  {	if(PATH->Parent != NULL) 
		{	PATH = PATH->Parent; 
			return TRUE;
		}
		else
		{	return FALSE;
		}
	  }
      int NodeGetX(void)      { return PATH->x; }
      int NodeGetY(void)      { return PATH->y; }

      // other usefull functions (do not change them they are used by the A* algorithm)
      int TileNum(int x, int y); // returns tilenum
	  int FreeTile(int x, int y); // returns 1 = true if we can move on it


	private:
      void FreeNodes(void);// frees lists memory
      // The A* Algorithm and it's stuff
      void FindPath(int sx, int sy, int dx, int dy);
	  NODE *ReturnBestNode(void);
	  void GenerateSuccessors(NODE *BestNode, int dx, int dy);
	  void GenerateSucc(NODE *BestNode,int x, int y, int dx, int dy);
      NODE *CheckOPEN(int tilenum);
      NODE *CheckCLOSED(int tilenum);
      void Insert(NODE *Successor);
      void PropagateDown(NODE *Old);
      void Push(NODE *Node); // stack functions
      NODE *Pop(void);
};

#endif // ASTARPATHFINDER_INCLUDE_


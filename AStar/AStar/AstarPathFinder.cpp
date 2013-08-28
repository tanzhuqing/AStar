//------------------------------------------------------------------------------
// PROJECT: The A* Pathfinder base Class
// FILE:   ASTAR.CPP
// OVERVIEW:
//    -Pretty good working Astar Pathfinder Algorithm Class.
//    -Based on SPATH.C Author: unknown (thanks)
//          	 http://www-cs-students.stanford.edu/~amitp/Articles/spath.zip
//    -Easy to implement, also with Your
//     favorite tiles based map but nevertheless a
//     little bit tricky to handle.
//    -Needs to be optimized or modified, perhaps a pointer to
//     a spritelist to reinitialisize the A* tilemap
//     and avoid sprite collosion.
//	   Let me hear about it.
//    Have fun!
// REVISION: 1.1
// Last Update: 31.08.97
// AUTHOR: pat@das-netz.de Germany 25.07.97
//------------------------------------------------------------------------------
#include "StdAfx.h"
#include "AstarPathFinder.h"
//#include "DirectDrawClass.h"

////////////////////////////////////////////////////////////////////////////////
//                           Constructor Destructor                           //
////////////////////////////////////////////////////////////////////////////////

AstarPathfinder::AstarPathfinder()
{
	Stack   = ( STACK* )calloc(1,sizeof( STACK ));
	isPath  = FALSE;
	OPEN    = NULL;
	CLOSED  = NULL;
	PATH    = NULL;
	TileMap = NULL;	// Sets the A* Tilemap append on CDXMap
}

////////////////////////////////////////////////////////////////////////////////

AstarPathfinder::~AstarPathfinder()
{
	FreeNodes();
	free(Stack);
	if (TileMap != NULL) 
	{	delete TileMap;
		TileMap = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//                             Public Member Functions                        //
////////////////////////////////////////////////////////////////////////////////

void AstarPathfinder::InitAstarTileMap(BYTE *pMap, int w,int h)
{
	COLS = w;	// 障碍图的宽度
	ROWS = h;	// 障碍图的高度
	TOTAL_TILES = ROWS * COLS; // 障碍图的尺寸
	unsigned long BufSize;
	BufSize = (TOTAL_TILES + 7) >> 3;

	if(TileMap != NULL) 
	{	delete TileMap;
		TileMap = NULL;
	}
	TileMap = new BYTE[BufSize];
	memcpy(TileMap, pMap, BufSize);
}

////////////////////////////////////////////////////////////////////////////////

BOOL AstarPathfinder::NewPath(int sx,int sy, int dx,int dy)//(dx,dy)目的节点，(sx,sy)源节点，入口函数
{
	if ( FreeTile(dx,dy)&&FreeTile(sx,sy) && (TileNum(sx,sy)!=TileNum(dx,dy)) )
	{
		FreeNodes(); // clear node lists
		FindPath(sx,sy,dx,dy);
		if (PATH == NULL)
			return (isPath=FALSE);
		else
			return (isPath=TRUE);
	}
	else
		return (isPath=FALSE);
}

////////////////////////////////////////////////////////////////////////////////

BOOL AstarPathfinder::ReachedGoal(void) // check it's return value before getting
{                                      // the node entries
	//if ( isPath ) return TRUE;  // this looks a little bit strange？？？？？？？？？？？？？"!isPath" 
	if ( PATH->Parent == NULL )  // but prevents illegal calls of ::PathNextNode()
		return FALSE;             // or ::PathGet*()
	else
		return TRUE;
}

////////////////////////////////////////////////////////////////////////////////

int AstarPathfinder::TileNum(int x, int y)
{	if (x<0 || x>=COLS || y<0 || y>=ROWS) return 0;
	return (y*COLS + x); // The reason I add COLS+1 to
	// tile number is because I want the tile number to start at the 2nd
	// the column and the 2nd row. Because if we do this we don't have to have
	// a special case to test if at a boundary. In the function BoundaryTiles
	// I place 1's around the boundary, in this way when I call the function
	// FreeTile() it returns false because we can't go there.
}

////////////////////////////////////////////////////////////////////////////////

int AstarPathfinder::FreeTile(int x, int y)//检查行为x（x从0开始），列为y（y从0开始）的位置为1还是0
{	//  returns 1 if tile is free(nothing on it).
	//  Note: if TileMap[equation]==0 it means free so just !(not) it.
	if (x<0 || x>=COLS || y<0 || y>=ROWS) 
	{	return 0;
	}
	else
	{	int bytes, bits, val, index;
		index = y * COLS + x;
		bytes = index >> 3;
		bits  = index & 0x07;
		val = TileMap[bytes] >> (7 - bits);
		if((val & 0x01) == 0)
		{	return 1;
		}
		else
		{	return 0;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//								      Private Member Functions                        //
////////////////////////////////////////////////////////////////////////////////

void AstarPathfinder::FreeNodes(void)//清空开闭列表
{	NODE *Node, *OldNode;
	if ( OPEN != NULL )
	{	Node = OPEN->NextNode;
		while ( Node != NULL )
		{	OldNode = Node;
			Node = Node->NextNode;
			free(OldNode);
		}
	}

	if ( CLOSED != NULL )
	{	Node = CLOSED->NextNode;
		while ( Node != NULL )
		{	OldNode = Node;
			Node = Node->NextNode;
			free(OldNode);
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
//                               A* Algorithm                                 //
////////////////////////////////////////////////////////////////////////////////

void AstarPathfinder::FindPath(int sx, int sy, int dx, int dy)//(dx,dy)目的节点，(sx,sy)源节点，入口函数
{
	NODE *Node, *BestNode;
	int TileNumDest;

	TileNumDest = TileNum(sx, sy);//？？？？？？？？？？？？？？？？？？？？？？？？？？？？(dx,dy)
	OPEN	=( NODE* )calloc(1,sizeof( NODE ));
	CLOSED	=( NODE* )calloc(1,sizeof( NODE ));

	Node=( NODE* )calloc(1,sizeof( NODE ));
	Node->g = 0;
	Node->h = (dx-sx)*(dx-sx) + (dy-sy)*(dy-sy);  // should really use sqrt().
	Node->f = Node->g+Node->h;
	Node->NodeNum = TileNum(dx, dy);
	Node->x = dx;
	Node->y = dy;

	OPEN->NextNode=Node;        // make Open List point to first node
	for (;;)
	{
		BestNode=ReturnBestNode();
        if (BestNode==NULL)    // if we've found the end, break and finish
			break;
		else if (BestNode->NodeNum == TileNumDest)    // if we've found the end, break and finish
			break;//？？？？？？？？？？？？？？？？？？？？？？？？？？？？？无法到达就死循环

		
		GenerateSuccessors(BestNode,sx,sy);//？？？？？？？？？？？？(dx,dy)
	}
	PATH = BestNode;
}

////////////////////////////////////////////////////////////////////////////////

AstarPathfinder::NODE
*AstarPathfinder::ReturnBestNode(void)//返回开列表中的f最小的节点，并将此节点插入关闭列表
{
	NODE *tmp;
	char message[128];

	if ( OPEN->NextNode == NULL )
	{
		sprintf(message,"No more nodes on OPEN: Perhaps tilenum destination not reachable!");
		MessageBox(0, message, "Error A* Pathfinder", MB_OK | MB_ICONERROR);
//		PostQuitMessage(0);
		return NULL;;
	}

	// Pick Node with lowest f, in this case it's the first node in list
	// because we sort the OPEN list wrt lowest f. Call it BESTNODE.

	tmp = OPEN->NextNode;   // point to first node on OPEN
	OPEN->NextNode = tmp->NextNode;    // Make OPEN point to nextnode or NULL.

	// Next take BESTNODE (or temp in this case) and put it on CLOSED

	tmp->NextNode = CLOSED->NextNode;
	CLOSED->NextNode = tmp;

	return(tmp);
}

////////////////////////////////////////////////////////////////////////////////

void AstarPathfinder::GenerateSuccessors(NODE *BestNode, int dx, int dy)
{
	int x, y;

	// Upper-Left
	if ( FreeTile(x=BestNode->x-TILESIZE, y=BestNode->y-TILESIZE) )//为真表示不能通过
		GenerateSucc(BestNode,x,y,dx,dy);
	// Upper
	if ( FreeTile(x=BestNode->x, y=BestNode->y-TILESIZE) )
		GenerateSucc(BestNode,x,y,dx,dy);
	// Upper-Right
	if ( FreeTile(x=BestNode->x+TILESIZE, y=BestNode->y-TILESIZE) )
		GenerateSucc(BestNode,x,y,dx,dy);
	// Right
	if ( FreeTile(x=BestNode->x+TILESIZE, y=BestNode->y) )
		GenerateSucc(BestNode,x,y,dx,dy);
	// Lower-Right
	if ( FreeTile(x=BestNode->x+TILESIZE, y=BestNode->y+TILESIZE) )
		GenerateSucc(BestNode,x,y,dx,dy);
	// Lower
	if ( FreeTile(x=BestNode->x, y=BestNode->y+TILESIZE) )
		GenerateSucc(BestNode,x,y,dx,dy);
	// Lower-Left
	if ( FreeTile(x=BestNode->x-TILESIZE, y=BestNode->y+TILESIZE) )
		GenerateSucc(BestNode,x,y,dx,dy);
	// Left
	if ( FreeTile(x=BestNode->x-TILESIZE, y=BestNode->y) )
		GenerateSucc(BestNode,x,y,dx,dy);
}

////////////////////////////////////////////////////////////////////////////////

void AstarPathfinder::GenerateSucc(NODE *BestNode,int x, int y, int dx, int dy)
///////////////////(x,y)是BESTNODE，(dx,dy)是目的节点
{
	int g, TileNumS, c = 0;
	NODE *Old, *Successor;

	g = BestNode->g+1;	    // g(Successor)=g(BestNode)+cost of getting from BestNode to Successor
	TileNumS = TileNum(x,y);  // identification purposes

	if ( (Old=CheckOPEN(TileNumS)) != NULL ) // if equal to NULL then not in OPEN list, else it returns the Node in Old
	{
		for( c = 0; c < 8; c++)
	   	if( BestNode->Child[c] == NULL ) // Add Old to the list of BestNode's Children (or Successors).
	   		break;
		BestNode->Child[c] = Old;

		if ( g < Old->g )  // if our new g value is < Old's then reset Old's parent to point to BestNode
		{
			Old->Parent = BestNode;
			Old->g = g;
			Old->f = g + Old->h;
		}
	}
	else if ( (Old=CheckCLOSED(TileNumS)) != NULL ) // if equal to NULL then not in CLOSE list, else it returns the Node in Old
	{	for( c = 0; c< 8; c++)
			if ( BestNode->Child[c] == NULL ) // Add Old to the list of BestNode's Children (or Successors).
				break;
		BestNode->Child[c] = Old;

		if ( g < Old->g )  // if our new g value is < Old's then reset Old's parent to point to BestNode
		{
	   	    Old->Parent = BestNode;
	   	    Old->g = g;
	   	    Old->f = g + Old->h;
	   	    PropagateDown(Old);  // Since we changed the g value of Old, we need
					   	         // to propagate this new value downwards, i.e.
					 	         // do a Depth-First traversal of the tree!
		}
	}
	else
	{
		Successor = ( NODE* )calloc(1,sizeof( NODE ));
		Successor->Parent = BestNode;
		Successor->g = g;
		Successor->h = (x-dx)*(x-dx) + (y-dy)*(y-dy);  // should do sqrt(), but since we don't really
		Successor->f = g+Successor->h;     // care about the distance but just which branch looks
		Successor->x = x;                 // better this should suffice. Anyayz it's faster.
		Successor->y = y;
		Successor->NodeNum = TileNumS;
		Insert(Successor);     // Insert Successor on OPEN list wrt f
		for( c =0; c < 8; c++)
			if ( BestNode->Child[c] == NULL ) // Add Old to the list of BestNode's Children (or Successors).
	  		    break;
		BestNode->Child[c] = Successor;
	}
}

////////////////////////////////////////////////////////////////////////////////

AstarPathfinder::NODE
*AstarPathfinder::CheckOPEN(int tilenum)//遍历找完开列表，看tilenum是否在其中
{
	NODE *tmp;

	tmp = OPEN->NextNode;
	while ( tmp != NULL )
	{
		if ( tmp->NodeNum == tilenum )
	   		return (tmp);
		else
	  		tmp = tmp->NextNode;
	}
	return(NULL);
}

////////////////////////////////////////////////////////////////////////////////

AstarPathfinder::NODE
*AstarPathfinder::CheckCLOSED(int tilenum)//遍历找完闭列表，看tilenum是否在其中
{
	NODE *tmp;

	tmp = CLOSED->NextNode;

	while ( tmp != NULL )
	{
		if ( tmp->NodeNum == tilenum )
			return(tmp);
		else
	   		tmp = tmp->NextNode;
	}
	return(NULL);
}

////////////////////////////////////////////////////////////////////////////////

void AstarPathfinder::Insert(NODE *Successor)//在开列表中从小到大排序
{
	NODE *tmp1, *tmp2;
	int f;

	if ( OPEN->NextNode == NULL )
	{
		OPEN->NextNode = Successor;
		return;
	}

       // insert into OPEN successor wrt f
	f = Successor->f;
	tmp1 = OPEN;
	tmp2 = OPEN->NextNode;

	while ( (tmp2 != NULL) && (tmp2->f < f) )
	{
		tmp1 = tmp2;
		tmp2 = tmp2->NextNode;
	}

	Successor->NextNode = tmp2;
	tmp1->NextNode = Successor;
}

////////////////////////////////////////////////////////////////////////////////

void AstarPathfinder::PropagateDown(NODE *Old)
{
	int c, g;
	NODE *Child, *Father;

	g = Old->g;            // alias.
	for ( c = 0; c < 8; c++)
	{
		if ( (Child=Old->Child[c]) == NULL )   // create alias for faster access.
			break;
		if ( g+1 < Child->g)
		{	Child->g = g+1;
			Child->f = Child->g + Child->h;
	  	    Child->Parent = Old;           // reset parent to new path.
			Push(Child);                 // Now the Child's branch need to be
		}     // checked out. Remember the new cost must be propagated down.
	}

	while ( Stack->NextStackPtr != NULL )
	{
		Father = Pop();
		for (c = 0; c<8; c++)
		{  	if ( (Child=Father->Child[c]) == NULL )  // we may stop the propagation 2 ways: either
	  			break;
			if ( Father->g+1 < Child->g ) // there are no children, or that the g value of
	  		{                          // the child is equal or better than the cost we're propagating
				Child->g = Father->g+1;
	    		Child->f = Child->g+Child->h;
	    		Child->Parent = Father;
	    		Push(Child);
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
//                              STACK FUNCTIONS                               //
////////////////////////////////////////////////////////////////////////////////

void AstarPathfinder::Push(NODE *Node)
{
	STACK *tmp;

	tmp =( STACK* )calloc(1,sizeof( STACK ));
	tmp->NodePtr = Node;
	tmp->NextStackPtr = Stack->NextStackPtr;
	Stack->NextStackPtr = tmp;
}

////////////////////////////////////////////////////////////////////////////////

AstarPathfinder::NODE
*AstarPathfinder::Pop(void)//返回节点指针
{
	NODE *tmp;
	STACK *tmpSTK;

	tmpSTK = Stack->NextStackPtr;
	tmp = tmpSTK->NodePtr;

	Stack->NextStackPtr = tmpSTK->NextStackPtr;
	free(tmpSTK);
	return(tmp);
}

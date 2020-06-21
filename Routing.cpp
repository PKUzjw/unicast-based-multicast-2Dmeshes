#include "Routing.h"
#include "assert.h"
#include<math.h>
/*******

  if ALGORITHM == 1, west-first 
  if ALGORITHM == 2, dor-routing


  ***********/
extern int ALGORITHM;

NodeInfo*	Routing::forward(Message& s){
	return forward((*torus)[s.routpath[0].node], (*torus)[s.dst]);
}


int Routing::chkWrplnk(Q2DTorusNode* cur, Q2DTorusNode* dst){ 
	int curx = cur->x;
	int cury = cur->y;

	
	int dstx = dst->x;
	int dsty = dst->y;


	int wraplink = 0;

  if(((curx < dstx) && (dstx - curx) > (k/2)) || ((curx > dstx) && (curx - dstx) > (k/2)))
	  wraplink ++;

  if(((cury < dsty) && (dsty - cury) > (k/2)) || ((cury > dsty) && (cury - dsty) > (k/2)))
	  wraplink ++;

 

  return wraplink;
}


NodeInfo*	Routing::forward(Q2DTorusNode* cur, Q2DTorusNode* dst){
	assert(cur && dst && (cur != dst));
	
	next->node = -1;
	next->buff = NULL;

	//int wraplink = chkWrplnk( cur,  dst);
	int wraplink = 0;//实现的是mesh网络，所以没有环链路，wraplink为0

	if (wraplink == 0)  return noWrapLinkrt( cur,  dst);

//	if (wraplink == 1)  return oneWrapLinkrt(cur, dst);

//	if (wraplink == 2)  return twoWrapLinkrt( cur, dst);

}


/**********

		 check whether buff1 has enough buffer,
		 n	is the buffer number , if buff1 used, then record it:
		 chn is R1 or R2 used,and record is the buffer(such as bufferxneg)
		 
		 ***********/

bool Routing::checkBuffer(Buffer *buff1 , int &chn ,Buffer*& record){  
	bool k = false;	
	if(	buff1->linkused == true) {
		return k;
	}

//	if (chn == R2){
//	    if(buff1->r2 >= MESSLENGTH){
//	        k= true;
//	        buff1->linkused = true;
//	    }
//	}else{
//	    if(buff1->r1 >= MESSLENGTH){
//	        chn = R1;
//	        k = true;
//	        buff1->linkused = true;
//	    }else if(buff1->r2 >= MESSLENGTH){
//	        chn = R2;
//	        k = true;
//	        buff1->linkused = true;
//	    }
//	}
 	if( chn == R1){
//        cout << buff1->r1 << " " << MESSLENGTH << endl;
		if(buff1->r1 >= MESSLENGTH ){
			k = true;
			buff1->linkused = true;
		}
	}
 	if(chn == R2){
// 	    cout << "hahhaha"<< endl;
// 	    cout << buff1->r2 << " " << MESSLENGTH << endl;
 	    if(buff1->r2 >= MESSLENGTH){
 	        k = true;
 	        buff1->linkused = true;
 	    }
 	}
//	else{
//		if(  buff1->r1 >= MESSLENGTH){
//			chn = R1;
//			k = true;
//			buff1->linkused = true;
//		}
//		else if(buff1->r2 >= MESSLENGTH){
//			chn = R2;
//			k = true;
//			buff1->linkused = true;
//		}
//	}
	if ( k ) {
		record = buff1;
		buff1->bufferMin(chn, MESSLENGTH);	
	}
	return k;
}

int		Routing::prefer(Buffer *buff1, Buffer *buff2, Buffer *buff3, Buffer *buff4, int xdis, int ydis, int& chnx1 , int& chny1, int& chnx2, int& chny2, Buffer*& record){
//检查是否有足够的缓存，链路是否可用
            if(buff2 != NULL && buff4!= NULL && xdis > 0 && ydis > 0){
                if(checkBuffer(buff2, chnx1, record)) return 1;
                else if(checkBuffer(buff2, chnx2, record)) return 13;
                else if(checkBuffer(buff4, chny1, record)) return 2;
                else return 0;
            }
            else if(buff2 != NULL && buff3!= NULL && xdis > 0 && ydis < 0){
                if(checkBuffer(buff2, chnx1, record)) return 3;
                else if(checkBuffer(buff2, chnx2, record)) return 14;
                else if(checkBuffer(buff3, chny2, record)) return 4;
                else return 0;
            }
            else if(buff1 != NULL && buff4!= NULL && xdis < 0 && ydis > 0){
                if(checkBuffer(buff1, chnx1, record)) return 5;
                else if(checkBuffer(buff1, chnx2, record)) return 15;
                else if(checkBuffer(buff4, chny1, record)) return 6;
                else return 0;
            }
            else if(buff1 != NULL && buff3!= NULL && xdis < 0 && ydis < 0){
                if(checkBuffer(buff1, chnx1, record)) return 7;
                else if(checkBuffer(buff1, chnx2, record)) return 16;
                else if(checkBuffer(buff3, chny2, record)) return 8;
                else return 0;
            }
            else if(buff2 != NULL && xdis > 0 && ydis == 0){
                if(checkBuffer(buff2, chnx1, record)) return 9;
                else if(checkBuffer(buff2, chnx2, record)) return 17;
                else return 0;
            }
            else if(buff1 != NULL && xdis < 0 && ydis == 0){
                if(checkBuffer(buff1, chnx1, record)) return 10;
                else if(checkBuffer(buff1, chnx1, record)) return 18;
                else return 0;
            }
            else if(buff4 != NULL && xdis == 0 && ydis > 0){
                if(checkBuffer(buff4, chny1, record)) return 11;
                else return 0;
            }
            else if(buff3 != NULL && xdis == 0 && ydis < 0){
                if(checkBuffer(buff3, chny2, record)) return 12;
                else return 0;
            }
            else   return 0;
//			if( buff1 != NULL && buff2 == NULL)
//					if(checkBuffer(buff1, chn1, record))
//						 return 1;
//					else return 0;
//
//			if (buff1 != NULL && buff2 != NULL)
//					if (checkBuffer(buff1, chn1, record))
//						return 1;
//					else return 0;
//
//			if( buff1 == NULL && buff2 != NULL)
//					if(checkBuffer(buff2, chn2, record))
//						 return 2;
//					else return 0;
//
//			if (buff1 == NULL && buff2 == NULL)
//						return 0;

			/*int bufferslc = 0;
			int var;

			if( chn1 == R1 && chn2 == R1) var = 1;
			if( chn1 == R1 && chn2 == R2) var = 2;

			if( chn1 == R2 && chn2 == R1) var = 3;
			if( chn1 == R2 && chn2 == R2) var = 4;

			switch (var){
			case 1: case 3: case 4:
				if(checkBuffer(buff1, chn1,record )){
								bufferslc = 1;
								return bufferslc;
				}

				if(checkBuffer(buff2, chn2,record )){
								bufferslc = 2;
								return bufferslc;
				}
				return bufferslc;

			case 2: 

				if(checkBuffer(buff2, chn2,record )){
								bufferslc = 2;
								return bufferslc;
				}

				if(checkBuffer(buff1, chn1,record )){
								bufferslc = 1;
								return bufferslc;
				}
					return bufferslc;
			}*/
}


NodeInfo*	Routing::noWrapLinkrt(Q2DTorusNode* cur, Q2DTorusNode* dst){  //routing without wraplink.
	assert( cur && dst && (cur != dst));
	int curx = cur->x;
	int cury = cur->y;

   	//R1 preferred, leave more space for escape channel R2.
	int dstx = dst->x;
	int dsty = dst->y;

	int xdis = dstx - curx;//x方向的偏移
	int ydis = dsty - cury;//y方向的偏移


    int bufferslc ; // 0 no buffer available, 1: select  x direction buffer,2 y direction, 3 z direction
	int var1; // 表示下一步x要走的方向，0: -x, 1:不变, 2: +x
	int var2; // 表示下一步y要走的方向，0: -x, 1:不变, 2: +x


	int vchx1;   // virtual channel of x axis
    int vchx2;   // virtual channel of x axis
    int vchy1;   // virtual channel of y axis
	int vchy2;   // virtual channel of y axis

/*
	if( xdis < 0) var1 = 0;
	else { 
		if( xdis == 0) var1 = 1;
		else if( xdis > 0) var1 = 2;
	}
	
	if (xdis == 0)
	{
		if (ydis < 0) var2 = 0;
		else {
			if (ydis == 0) var2 = 1;
			else if (ydis > 0) var2 = 2;
		}
	}
	else
	{
		var2 = 1;//xy路由算法：x方向的偏移不为0时,不能走y方向
	}
*/
//    if(xdis < 0 && ydis < 0){
//        int  tempRand;
//        tempRand = abs(rand()) % 100;
//        if(temprand > 50){
//            var1 = 0;
//            var2 = 1;
//        }else{
//            var1 = 1;
//            var2 = 0;
//        }
//    }else if(xdis < 0 && ydis == 0){
//        var1 = 0;
//        var2 = 1;
//    }else if(xdis > 0 && ydis < 0){
//        int  tempRand;
//        tempRand = abs(rand()) % 100;
//        if(tempRand > 50){
//            var1 = 2;
//            var2 = 1;
//        }else{
//            var1 = 1;
//            var2 = 0;
//        }
//    }else if(xdis > 0 && ydis == 0){
//        var1 = 2;
//        var2 = 1;
//    }else if(xdis == 0 && ydis < 0){
//        var1 = 1;
//        var2 = 0;
//    }else if(xdis == 0 && ydis == 0){
//        var1 = 1;
//        var2 = 1;
//    }


     
	

	Buffer* xlink[3] = {cur->bufferxneglink, NULL, cur->bufferxposlink};
	Buffer* ylink[3] = {cur->bufferyneglink, NULL, cur->bufferyposlink};

	
	int xlinknode[3] = {cur->linkxneg, -1, cur->linkxpos};
	int ylinknode[3] = {cur->linkyneg, -1, cur->linkypos};

	int virtualch[3] = {R2, 0, R1};

/**********************************************

	ALGORITHM == 2   dor ROUTING 路由算法的实现，这里实现的xy

  *****************************************************/


	if(ALGORITHM == 2){
//		if( var1 != 1) {
//			vchx = R2;
//			vchy = R1;
//
//		}
//		else{
//			vchy = R2;
//		}
		vchx1 = R1;
		vchy1 = R1;
        vchx2 = R2;
		vchy2 = R2;

//		bufferslc =	prefer(xlink[var1], ylink[var2], vchx, vchy, next->buff);
//        switch(bufferslc){
//            case 0:
//                next->node = -1;
//                break;
//            case 1:
//                next->node = xlinknode[var1];
//                next->channel = vchx;
//                break;
//            case 2:
//                next->node = ylinknode[var2];
//                next->channel = vchy;
//                break;
//        }
        bufferslc =	prefer(xlink[0], xlink[2], ylink[0], ylink[2], xdis, ydis, vchx1, vchy1, vchx2, vchy2, next->buff);
        switch(bufferslc){
            case 0:
                next->node = -1;
                break;
            case 1:
                next->node = xlinknode[2];
                next->channel = vchx1;
                break;
            case 2:
                next->node = ylinknode[2];
                next->channel = vchy1;
                break;
            case 3:
                next->node = xlinknode[2];
                next->channel = vchx1;
                break;
            case 4:
                next->node = ylinknode[0];
                next->channel = vchy2;
                break;
            case 5:
                next->node = xlinknode[0];
                next->channel = vchx1;
                break;
            case 6:
                next->node = ylinknode[2];
                next->channel = vchy1;
                break;
            case 7:
                next->node = xlinknode[0];
                next->channel = vchx1;
                break;
            case 8:
                next->node = ylinknode[0];
                next->channel = vchy2;
                break;
            case 9:
                next->node = xlinknode[2];
                next->channel = vchx1;
                break;
            case 10:
                next->node = xlinknode[0];
                next->channel = vchx1;
                break;
            case 11:
                next->node = ylinknode[2];
                next->channel = vchy1;
                break;
            case 12:
                next->node = ylinknode[0];
                next->channel = vchy2;
                break;
            case 13:
                next->node = xlinknode[2];
                next->channel = vchx2;
                break;
            case 14:
                next->node = xlinknode[2];
                next->channel = vchx2;
                break;
            case 15:
                next->node = xlinknode[0];
                next->channel = vchx2;
                break;
            case 16:
                next->node = xlinknode[0];
                next->channel = vchx2;
                break;
            case 17:
                next->node = xlinknode[2];
                next->channel = vchx2;
                break;
            case 18:
                next->node = xlinknode[0];
                next->channel = vchx2;
                break;
        }
        return next;
	}
}

/*
NodeInfo* Routing::oneWrapLinkrt(Q2DTorusNode* cur, Q2DTorusNode* dst){  //routing one wraplink. 
	assert( cur && dst && (cur != dst));
	int curx = cur->x;
	int cury = cur->y;

	//R1 preferred, leave more space for escape channel R2.
	int dstx = dst->x;
	int dsty = dst->y;

	int xdis = dstx - curx;
	int ydis = dsty - cury;

	
	
    int bufferslc ; // 0 no buffer available, 1: select  x direction buffer,2 y direction, 3 z direction
	int var1;
	int var2;

	

	int vchx = R1;   // virtual channel of x axis
	int vchy = R1;


	if( xdis < 0) var1 = 0;
	else { 
		if( xdis == 0) var1 = 1;
		else if( xdis > 0) var1 = 2;
	}

	if( ydis < 0) var2 = 0;
	else { 
		if( ydis == 0) var2 = 1;
		else if( ydis > 0) var2 = 2;
	}

	

	Buffer* xlink[3] = {cur->bufferxneglink, NULL, cur->bufferxposlink};
	Buffer* ylink[3] = {cur->bufferyneglink, NULL, cur->bufferyposlink};

	
	int xlinknode[3] = {cur->linkxneg, -1, cur->linkxpos};
	int ylinknode[3] = {cur->linkyneg, -1, cur->linkypos};
	

	if(xdis > k/2  || xdis < -k/2){
		Buffer* temp = xlink[0];
		xlink[0] = xlink[2];
		xlink[2] = temp;

		int temp2 = xlinknode[0];
		xlinknode[0] = xlinknode[2];
		xlinknode[2] = temp2;
		if( xdis > k/2 && cur->x == 0) vchx = R2;
		if( xdis < -k/2 && cur->x == k-1) vchx = R2;
	}

	
	if(ydis > k/2  || ydis < -k/2){
		 Buffer* temp = ylink[0];
		ylink[0] = ylink[2];
		ylink[2] = temp;

		int temp2 = ylinknode[0];
		ylinknode[0] = ylinknode[2];
		ylinknode[2] = temp2;
		if( ydis > k/2 && cur->y == 0) vchy = R2;
		if( ydis < -k/2 && cur->y == k-1) vchy = R2;
	}

	
	


		bufferslc =	prefer(xlink[var1], ylink[var2], vchx, vchy,  next->buff);
				switch(bufferslc){
					case 0:
					next->node = -1;
						break;
					case 1:
						next->node = xlinknode[var1];
						next->channel = vchx;
						break;
					case 2:
						next->node = ylinknode[var2];
						next->channel = vchy;
						break;
				
					}
	return next;
	}
    

NodeInfo*	Routing::twoWrapLinkrt(Q2DTorusNode* cur, Q2DTorusNode* dst){
			assert( cur && dst && (cur != dst));
	int curx = cur->x;
	int cury = cur->y;
	
	//R1 preferred, leave more space for escape channel R2.
	int dstx = dst->x;
	int dsty = dst->y;

	int xdis = dstx - curx;
	int ydis = dsty - cury;


	
	
    int bufferslc ; // 0 no buffer available, 1: select  x direction buffer,2 y direction, 3  direction
	int var1;
	int var2;
	
	

	int vchx = R1;   // virtual channel of x axis
	int vchy = R1;


	if( xdis < 0) var1 = 0;
	else { 
		if( xdis == 0) var1 = 1;
		else if( xdis > 0) var1 = 2;
	}

	if( ydis < 0) var2 = 0;
	else { 
		if( ydis == 0) var2 = 1;
		else if( ydis > 0) var2 = 2;
	}



	Buffer* xlink[3] = {cur->bufferxposlink, NULL, cur->bufferxneglink};
	Buffer* ylink[3] = {cur->bufferyposlink, NULL, cur->bufferyneglink};

	
	int xlinknode[3] = {cur->linkxpos, -1, cur->linkxneg};
	int ylinknode[3] = {cur->linkypos, -1, cur->linkyneg};




		bufferslc =	prefer(xlink[var1], ylink[var2], vchx, vchy, next->buff);
				switch(bufferslc){
					case 0:
					next->node = -1;
						break;
					case 1:
						next->node = xlinknode[var1];
						next->channel = vchx;
						break;
					case 2:
						next->node = ylinknode[var2];
						next->channel = vchy;
						break;
					
					}
	return next;
}
*/


#include "globals.h"
#include "ball_detector.h"

/*
This ball_detector function need as input the desired distance treshold that needs to be check. If within
this distange there is an object it will return the distance of this object, otherwise 0.
*/

int ball_detector(int dist){
	int act_dist,y;
	act_dist = us->distance; 
	if ( act_dist > dist ) 
		y =  0;
	else if (act_dist =< dist )
		y =  act_dist;

	return y;
}

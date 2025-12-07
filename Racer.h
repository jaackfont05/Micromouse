/*
 * Racer.h
 *
 *  Created on: Nov 12, 2025
 *      Author: bill_booth
 */

#ifndef RACER_H_
#define RACER_H_

#include "SDL_Plotter.h"
#include "constants.h"

using namespace std;

enum DIRECTION {NORTH, SOUTH, EAST, WEST};


class Racer{

private:
	point location, prevLocation;
	color color;
	int   size;
	bool  alive;

public:
	Racer();
	Racer(const Racer&);
	Racer operator=(const Racer&);

	bool   racing(){return alive;}
	void   move(int direction);
	void   draw(SDL_Plotter& g);
	void   erase(SDL_Plotter& g);
	Uint32 look(DIRECTION direction, SDL_Plotter& g);
	point  getLocation(){return location;}
	point  getPrevLocation(){return prevLocation;}

};

Racer::Racer(): location(point(0,0)), size(block-padding), alive{true}{}

void Racer::move(int direction){
	prevLocation = location;
	switch(direction){
		case EAST: location.x++; break;
		case NORTH: location.y--; break;
		case WEST: location.x--; break;
		case SOUTH: location.y++; break;
	}
}


void Racer::draw(SDL_Plotter& g){
	erase(g);
	int startX = location.x * block + buffer + padding/2;
	int startY = location.y * block + buffer + padding/2;

	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			g.plotPixel(startX + x, startY + y,0,0,255);
		}
	}

}


Uint32 Racer::look(DIRECTION direction, SDL_Plotter& g){
	int startX = location.x * block + buffer + padding/2;
	int startY = location.y * block + buffer + padding/2;
    Uint32 see;

    switch(direction){
		case NORTH: startY -= padding/2+1; break;
		case SOUTH: startY += size + padding/2+1; break;
		case EAST:  startX += size + (padding)/2; break;
		case WEST:  startX -= (padding)/2; break;
    }

	cout <<"x = " << startX  << " y = " <<startY << " ";
	see = g.getColor(startX , startY);
	//g.plotPixel(startX , startY,255,25,25);

	return see;
}

void Racer::erase(SDL_Plotter& g){

	int startX = prevLocation.x * block + buffer + padding/2;
	int startY = prevLocation.y * block + buffer + padding/2;

	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			g.plotPixel(startX + x, startY + y,255,255,255);
		}
	}


}

/*
 *
    const int block = 22;
    const int buffer = 100;
    const int padding = 6;
    const int wallThickness = 3; // must be odd
 *
 */

#endif /* RACER_H_ */


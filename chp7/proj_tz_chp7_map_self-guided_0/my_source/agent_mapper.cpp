/*
 * agent_mapper.cpp
 *
 * An associative map defines the agent's associative memory of the
 * physical environment... this is what "meaning" the agent associates
 * with a given context string; the context string tells the agent
 * the relative locations of the landmarks from its vantage point,
 * in terms of the eight map directions, defined in orient_t.
 * For example, if the agent "sees" Landmark A to the North-West,
 * Landmark B to South, and Landmark C to the East, it should be
 *  in Region 1.
 *
 *  Created on: Jul. 5, 2019
 *      Author: takis
 */

// components from STD Library
#include <vector>
#include <iostream>
#include <string>
#include <map>
// my own includes
#include <gsl/gsl_blas.h>
#include "agentlib.h"

// declare STD uses
using std::map;				using std::string;
using std::vector;			using std::cout;
using std::cin;				using std::endl;

// main code
int main()
{
	map<string, region_t>		global_map;
	bool						mappingfinished=false;	// flag indicating completion of associative map;
	vector<string> orient_str	= {"No","NE","Ea","SE","So","SW","We","NW"}; // strings corresponding to orient_t directions

	/* retrieve known contexts from file, knownfeatures.data */
	vector<read_data_t>		read_data;
	read_data = loadKnownContextsfromFile("knownfeatures.data");

	/* transfer data to global map */
	loadGlobalMapwithFileData(global_map, read_data);

	/* initialize physical environment */
	vvs_t	physenv;					// variable storing the "literal" environment in which agent navigates
	for (vvs_sz_t i=0; i!=Nx; ++i)
	{
		for (vvs_sz_t j=0; j!=Ny; ++j)
		{
			physenv[i][j]=" ";
		}
	}

	/* create FIVE landmarks at fixed locations */
	string				landmarks="ABCDE"; // there must be at least 5 characters in this string
	vector<loc_t>		v_lm;	// variables storing the locations of landmarks A through E in the physical environment
	loc_t				lmA = {5, 5};	v_lm.push_back(lmA);
	loc_t				lmB = {50, 50};	v_lm.push_back(lmB);
	loc_t				lmC = {85, 7};	v_lm.push_back(lmC);
	loc_t				lmD = {3, 90};	v_lm.push_back(lmD);
	loc_t				lmE = {80, 83};	v_lm.push_back(lmE);

	map<string, loc_t> 	m_lm;	// container of landmarks with key-location relationship
	string::const_iterator siter=landmarks.begin();		// iterator for landmarks string

	if (landmarks.size() < v_lm.size())
	{
		cout << "Error--- there are more landmarks than landmark labels!" << endl;
		return 1; // provide an error code
	}
	vector<loc_t>::size_type i=0;
	// invariant: siter points to the next landmark to be incorporated
	while (siter != landmarks.end())
	{
		m_lm[*siter]=v_lm[i];
		physenv[v_lm[i].X][v_lm[i].Y]=*siter;
		++i;
		++siter;
	}

	/* start building the associative map */
	loc_t				r0={0,0}; 				// agent's initial position
	loc_t				r1=r0;
	orient_t 			theta=North;			// agent's orientation
	scan_direction_t	scan_sense = SE;		// initial scanning sense
	loc_t				rA=r0;					// upper left corner of search space
	loc_t				rB={Nx-1, Ny-1};		// bottom right corner of search space
	scan(mappingfinished, scan_sense, rA, rB, r0, global_map, physenv, m_lm);

	return 0;
}


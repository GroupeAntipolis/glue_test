/*
 * Copyright (C) 2015, Marco Carta-Gullung, GroupeAntipolis.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
using namespace std;

#include "graph_manager.h"
#include "random_gen.h"
#include <unistd.h> //STDIN_FILENO
#include "math_nodes.h" // involved in maths tests (I)
#include "logical_nodes.h"  // involved in logical tests(II)
#include "math.h"
#include <fenv.h>
#include <stdio.h>
#include <termios.h>    	//termios, TCSANOW, ECHO, ICANON	


void pressKey()
{
    //the struct termios stores all kinds of flags which can manipulate the I/O Interface
    //I have an old one to save the old settings and a new 
    static struct termios oldt, newt;
    printf("Press key to continue....\n");

    //tcgetattr gets the parameters of the current terminal
    //STDIN_FILENO will tell tcgetattr that it should write the settings
    // of stdin to oldt
    tcgetattr( STDIN_FILENO, &oldt);
    //now the settings will be copied 
    newt = oldt;

    //two of the c_lflag will be turned off
    //ECHO which is responsible for displaying the input of the user in the terminal
    //ICANON is the essential one! Normally this takes care that one line at a time will be processed
    //that means it will return if it sees a "\n" or an EOF or an EOL
    newt.c_lflag &= ~(ICANON | ECHO );  	

    //Those new settings will be set to STDIN
    //TCSANOW tells tcsetattr to change attributes immediately. 
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    //now the char wil be requested
    getchar();

    //the old settings will be written back to STDIN
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

}

void manager_train(graph_manager* mg)
{
	mg->start_training();

	for(int t=0;t<100;t++)
	{
		sleep(30);
		/**/if(mg->getScore()==0)
		break;
	} 
	mg->stop_training();
}

int main (int argc, char *argv[])
{
	/*feenableexcept(FE_INVALID);
	feenableexcept(FE_INVALID   | 
                   FE_DIVBYZERO | 
                   FE_OVERFLOW  | 
                   FE_UNDERFLOW);*/

	// if u comment this one, glue can't do algebra (it can't work at all ;) )
	math_lib_registration();
	// if u comment this test II will never be passed ... (only approximated)
	logic_lib_registration();
	
	// Our rnd generator (see sources in (include))
	random_gen rnd;

	cout << "Glue Test Routine !" << endl;
	cout << "This will test a glue graph in diffrent tasks: " << endl;
	pressKey();

	int ch=0;
	// we declare a graph object !!
	
	cout << "Test I, Maths : Glue should discover a math function on the form :" << endl;
	cout << "E(a,b,c,d) = (c * d * cos( b /a ))" << endl << endl;
	cout << "declare a graph manager object .." << endl;
	cout << "created graph will have 4 in & 1 out .." << endl;
	
	pressKey();
	
	//graph_manager(int pin,int pout,int min_nodes,int max_nodes);
	graph_manager* mgm=new graph_manager(4,1,5,50);


	mgm->test_geometer();

	g_nbr inputs[4];
	g_nbr output[1];

	cout << "we build 10 trainings .." << endl;
	// we build 10 trainings
	for(int t=0;t<100;t++)
	{
		inputs[0]=(g_nbr)rnd.next_double();
		inputs[1]=(g_nbr)rnd.next_double();
		inputs[2]=(g_nbr)rnd.next_double();
		inputs[3]=(g_nbr)rnd.next_double();
		output[0]=inputs[2]*inputs[3]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*inputs[1];

		cout << "training" << t << ":  " << inputs[2] << " * " << inputs[3] << " * cos( " << inputs[1] << " / " << inputs[0] << " ) = " << inputs[2]*inputs[3]*cos(inputs[1]/inputs[0]) << endl;

		mgm->add_training(inputs,output);
	}

	cout << "manager have " << mgm->get_training_count() << " trainings .." << endl;/**/

	// test some things

	/*mgm->test_glue();*/

	// start the training for 20 sec

	cout << "Test I, Training: Glue will be trained until it can solve it." << endl;
	
	pressKey();
	
	manager_train(mgm);
	
	cout << "" << endl;
	cout << "Test I, Test Graph: we test 10 queries ..." << endl;
	

	for(int t=0;t<10;t++)
	{
		inputs[0]=(g_nbr)rnd.next_double();
		inputs[1]=(g_nbr)rnd.next_double();
		inputs[2]=(g_nbr)rnd.next_double();
		inputs[3]=(g_nbr)rnd.next_double();

		cout << "ground(" << t << "):  " << inputs[2] << " * " << inputs[3] << " * cos( " << inputs[1] << " / " << inputs[0] << " ) = " << inputs[2]*inputs[3]*cos(inputs[1]/inputs[0]) << endl;

		mgm->activate(inputs,output);
		//output[0]=inputs[0]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*inputs[1];
		
		cout << "graph(" << t << "):  " << inputs[2] << " * " << inputs[3] << " * cos( " << inputs[1] << " / " << inputs[0] << " ) = " << output[0] << endl << endl;
		
	}

	delete(mgm);
	
		// we declare a graph object !!
	
	cout << endl << endl << "Test II, Logic : Glue should discover the INDEX of its INPUT having non zero value :" << endl;
	cout << endl;
	cout << "declare a graph manager object .." << endl;
	cout << "created graph will have 4 in & 1 out .." << endl;
	
	pressKey();
	
	mgm=new graph_manager(4,1,5,50);

	cout << "we build 100 trainings .." << endl;
	// we build 10 trainings
	for(int t=0;t<100;t++)
	{
		inputs[0]=0; //(g_nbr)rnd.next_double();
		inputs[1]=0;
		inputs[2]=0;
		inputs[3]=0;
		
		ch=rnd.next(4);
		
		inputs[ch]=(g_nbr)rnd.next_double();
		//inputs[ch]=1;
		
		
		cout << "Non-zero index is " <<  ch << endl;

		output[0]=ch;
		

		mgm->add_training(inputs,output);
	}

	cout << "manager have " << mgm->get_training_count() << " trainings .." << endl;/**/

	// test some things

	/*mgm->test_glue();*/

	// start the training for 20 sec

	cout << "Test II, Training: Glue will be trained until it can solve it." << endl;
	
	pressKey();
	
	manager_train(mgm);
	
	cout << "" << endl;
	cout << "Test II, Test Graph: we test 10 queries ..." << endl;
	
	g_nbr res;
	for(int t=0;t<10;t++)
	{
		inputs[0]=0; //(g_nbr)rnd.next_double();
		inputs[1]=0;
		inputs[2]=0;
		inputs[3]=0;
		
		ch=rnd.next(4);
		
		inputs[ch]=(g_nbr)rnd.next_double();
		//inputs[ch]=1;
		
		
		cout << "Non-zero index is " <<  ch << endl;

		mgm->activate(inputs,output);
		//output[0]=inputs[0]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*inputs[1];
		
		cout << "Predicted non-zero index is " <<  output[0] << endl;
		
	}

	delete(mgm);
	
	return 0;
};


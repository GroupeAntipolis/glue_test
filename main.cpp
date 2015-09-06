#include <iostream>
using namespace std;

#include "graph_manager.h"
#include "random_gen.h"
#include <unistd.h>
#include "math_nodes.h"
#include "math.h"
#include <fenv.h>

int main (int argc, char *argv[])
{
	/*feenableexcept(FE_INVALID);
	feenableexcept(FE_INVALID   | 
                   FE_DIVBYZERO | 
                   FE_OVERFLOW  | 
                   FE_UNDERFLOW);*/

	math_lib_registration();
	random_gen rnd;

	cout << "Test de GLUE!" << endl;

	// we declare a graph object !!
	cout << "declare a graph manager object .." << endl;
	cout << "created graph will have 2 in & 1 out .." << endl;
	graph_manager* mgm=new graph_manager(4,1,5,200);


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

		cout << t << "." << inputs[0] << "*" << inputs[1] << "+" << inputs[0] << "=" << output[0] << endl;

		mgm->add_training(inputs,output);
	}

	cout << "manager have " << mgm->get_training_count() << " trainings .." << endl;/**/

	// test some things

	/*mgm->test_glue();*/

	// start the training for 20 sec


	mgm->start_training();

	for(int t=0;t<100;t++)
	{
		sleep(30);
		/**/if(mgm->getScore()==0)
		break;
	} 
	mgm->stop_training();
	
	cout << "we test 10 queries .." << endl;
	// we build 10 trainings
	g_nbr res;
	for(int t=0;t<10;t++)
	{
		inputs[0]=(g_nbr)rnd.next_double();
		inputs[1]=(g_nbr)rnd.next_double();
		inputs[2]=(g_nbr)rnd.next_double();
		inputs[3]=(g_nbr)rnd.next_double();
		res=inputs[2]*inputs[3]*cos(inputs[1]/inputs[0]);
		mgm->activate(inputs,output);
		//output[0]=inputs[0]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*inputs[1];
		
		cout << t << "." << inputs[0] << "*" << inputs[1] << "+" << inputs[0] << "=" << res << " g=" << output[0] << endl;
		
		mgm->add_training(inputs,output);
	}

	delete(mgm);
	return 0;
};


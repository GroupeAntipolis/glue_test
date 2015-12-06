# Glue Example Code #

## Glue ##

Glue(1) is a machine learning algorithm similar to genetic programming (GP), except that it does not use a concept of population. Clearly, Glue optimizes a single candidate solution to the given problem in contrast to GP. This excluded any crossover operator (evolutionary operators), but a reverse mutation operator is introduced. To solve a problem,  Glue optimizes (transforms) a graph whose nodes are operators.

(See more on <a href="http://marco.carta.fr/marco/homepage/spip.php?rubrique26&page=rubrique">this page</a>.)


## Glue node ##

This unix example software is dedicated to machine learning tasks with reals.
Feel free to ask any <i>numerical</i> (coherent(2)) question to your glue graph. 

## Build from source ##
	
	`$ sh compile_gluetest.sh`
	
## Execute example ##

	`$ sh exec_glue.sh`
	
## Modify example ##	
	
	Original source
	
	 ./main.cpp
	 
	 Includes
	 
	 ./include/
	 
	 Libraries
	 
	 ./libglue/
	
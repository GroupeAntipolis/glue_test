rm -rf ../libglue
mkdir ../libglue

rm ../include/*.h

cp ~/dev/Projects/LIBRARIES/CPP/glue/libglue.a ../libglue/
cp ~/dev/Projects/LIBRARIES/CPP/SmartData/bin/libSmartData.a ../libglue/
cp ~/dev/Projects/LIBRARIES/CPP/rng/bin/librng.a ../libglue/


cp ~/dev/Projects/LIBRARIES/CPP/glue/*.h ../include/
cp ~/dev/Projects/LIBRARIES/CPP/SmartData/*.h ../include/
cp ~/dev/Projects/LIBRARIES/CPP/rng/*.h ../include/

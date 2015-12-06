rm -rf ../libglue
mkdir ../libglue

rm ../include/*.h

cp /mnt/ntfs/prog/Projects/LIBRARIES/CPP/glue/bin/Release/libglue.a ../libglue/
cp /mnt/ntfs/prog/Projects/LIBRARIES/CPP/SmartDataCPP/bin/Release/libSmartDataCPP.a ../libglue/
cp /mnt/ntfs/prog/Projects/LIBRARIES/CPP/rng/bin/Release/librng.a ../libglue/


cp /mnt/ntfs/prog/Projects/LIBRARIES/CPP/glue/*.h ../include/
cp /mnt/ntfs/prog/Projects/LIBRARIES/CPP/SmartDataCPP/*.h ../include/
cp /mnt/ntfs/prog/Projects/LIBRARIES/CPP/rng/*.h ../include/

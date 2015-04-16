cd MyoushuJava/src/MyoushuJava
del *.java
cd ../..
cd dist
del *.jar
cd ../..
swig -java -c++ -v -I../include -IMyoushuJava -package MyoushuJava -outdir MyoushuJava/src/MyoushuJava -o MyoushuJava/MyoushuJava.cpp Myoushu.i

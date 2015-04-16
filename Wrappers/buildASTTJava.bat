cd ASTTJava\src\ASTTJava
del *.java
cd ..\..
cd dist
del *.jar
cd ..\..
swig -java -c++ -v -I..\include -I..\Myoushu\Wrappers\MyoushuJava -package ASTTJava -outdir ASTTJava\src\ASTTJava -o ASTTJava\ASTTJava.cpp astt.i
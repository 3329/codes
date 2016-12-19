select_ds:
	proc select_ds
	gcc select_ds.c -omain  -I${ORACLE_HOME}/precomp/public -lclntsh
select_mul:
	proc select_mul
	gcc select_mul.c -omain -I${ORACLE_HOME}/precomp/public -lclntsh
procplus:
	proc db code=cpp mode=ansi parse=none oname=db.cpp
	g++ main.cpp db.cpp -omain -I${ORACLE_HOME}/precomp/public -lclntsh
null:
	proc null
	gcc null.c -omain -I${ORACLE_HOME}/precomp/public -lclntsh

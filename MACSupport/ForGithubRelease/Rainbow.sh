./CppSide/AllPheriperalsCPP &  PIDCPP=$!
python3 ./PythonSide/main.py -easteregg false -operationmode 2 &  PIDPY=$!
wait $PIDCPP
wait $PIDPY

./CppSide/AllPheriperalsCPP &  PIDCPP=$!
python3 ./PythonSide/main.py -easteregg false -operationmode 1 &  PIDPY=$!
wait $PIDCPP
wait $PIDPY

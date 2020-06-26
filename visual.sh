VISUAL_PATH=src/visual
success=false

if [ "$1" != "" ] ; then
    if [[ "$1" == "--flow-one"  || "$1" == "--flow-ten" ||\
"$1" == "--flow-thousand" || "$1" == "--big" ||\
"$1" == "--big-superposition" ]] && [ -f "lem-in" ]\
&& [ -f "generator" ] ; then
        ./generator $1 > map.txt
        sleep 1
        ./lem-in < map.txt > output.txt
        ./lem-in --paths < map.txt > paths.txt
        python3 $VISUAL_PATH/parser.py output.txt paths.txt > $VISUAL_PATH/data.json
        success=true
    elif [ -f "lem-in" ] && [ -f $1 ] ; then
        ./lem-in < $1 > output.txt
        ./lem-in --paths < $1 > paths.txt
        sleep 1
        python3 $VISUAL_PATH/parser.py output.txt paths.txt > $VISUAL_PATH/data.json
        success=true
    fi
    if [ "$success" == "true" ] ; then
        php -S localhost:8082/src/visual/ & 
        open -a "Google Chrome" http://localhost:8082/src/visual/
    else
        echo "ERROR"
    fi
fi

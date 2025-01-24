#include <iostream>
#include <queue>
#include <string>
using namespace std;

//함수원형들
string statement(string);
char var(char);
string expr(string);
string dec(char);
string number(string);
string bexpr(string);
string aexpr(string);
string relop(string);
string factor(string);
string term(string);

//x,y,z의 값들을 출력하기 위해 전역변수로 선언해둔다.
string x,y,z;

//program함수
void program(string array){
    //이제 문자열에 ;이 들어간 것을 판단해야한다.
    //문자열을 뒤로 이동시키면서 ;가 나오면 그 전까지의 문자열을 판단하게끔 시행한다.
    int index = 0;
    int count =0;
    queue<string> que;
    string answer ;
    string blankArray;
    //이렇게 해둠으로써 statement가 여러번 반복되었을 경우를 처리할 수 있다.
    for(int i =0; i < (int)array.length(); i++){
        //여기서 세미콜론이 있는지 걸러준다.
        if(array[i] == ';'){
            count ++;
            string expression;
            expression = array.substr(index,i-index);
            //잘못된 값이 입력된 경우에는 종료한다.
            answer = statement(expression);
            if(answer== "wrong"){
                return ;
            }
            index = i+1;
            blankArray.clear();
            if (answer == "ok"){
                continue;
            }
            //print를 통해서 값을 출력해야 하는 경우에는 큐에 넣어줍니다.
            que.push(answer);
        }else{
            if(array[i]!=' '){
                blankArray+=(array[i]);
            }
        }
    }
    //; 뒤에 문자열이 남아있을 때에 대한 에러처리를 하기 위함입니다.
    if(!blankArray.empty()){
        cout << "syntax error!!\n";
        return ;
    }
    // 세미콜론의 개수를 세서 세미콜론이 한 개도 없는 경우에는 syntax error를 출력하는 것이다.
    if(count == 0){
        cout << "syntax error!!\n";
        return ;
    }
    //print로 출력해야하는 것들을 출력해줍니다.
    while(!que.empty()){
        cout << que.front() << " ";
        que.pop();
    }
    cout << "\n";
}

//statement 함수
string statement(string array){
    char varialbe;
    int equalCount = 0;
    int printCount = 0;
    //print인 경우를 먼저 처리해줘야 한다.
    if(array.find("print")  != string::npos){
        //뒤에 다른 변수가 없는지 확인해줘야 한다.
        int varCheck =0;
        //print 문자열이 몇번 쓰였는지 확인하기 위해서 사용하는 것이다.
        for(int i =0; i< (int)array.length();i++){
            if(array[i] == ' '){
            //빈 공간의 경우 넘어간다.
            }else if(array[i] == 'p'){
                //print가 쓰여있는 경우에 시행되는 것이기에 이렇게 이게 순서대로 쓰여있는지 확인한다.
                if(array[++i]=='r'){
                    if(array[++i] == 'i'){
                        if(array[++i] == 'n'){
                            if(array[++i]=='t'){
                                printCount ++;
                                //바로 뒤에 ;가 나오는 경우에 대한 예외처리를 한다.
                                if(array[i+1]==';'){
                                    cout << "syntax error!!\n";
                                    return "wrong";
                                }
                                if(array[i+1]== 'x'||array[i+1] =='y'||array[i+1]== 'z'){
                                    cout << "syntax error!!\n";
                                    return "wrong";
                                }
                                if(printCount != 1){
                                    cout << "syntax error!!\n";
                                    return "wrong";
                                }
                            }
                            else{
                                cout << "syntax error!!\n";
                                return "wrong";
                            }
                        }
                        else{
                            cout << "syntax error!!\n";
                            return "wrong";
                        }
                    }
                    else{
                        cout << "syntax error!!\n";
                        return "wrong";
                    }
                }else{
                    cout << "syntax error!!\n";
                    return "wrong";
                }
            }else{
                //print를 제외한 다른 단어에 대해서 var로 확인한다.
                if(varCheck==0){
                    //var이 올바르지 않을 경우 q를 리턴한다.
                    if(var(array[i])=='q'){
                        cout << "syntax error!!\n";
                        return "wrong";
                    }
                    varCheck++;
                    varialbe = var(array[i]);
                }else{
                    cout << "syntax error!!\n";
                    return "wrong";
                }
            }
        }
        //print가 있고 변수가 x , y , z로 입력된 경우에는 해당 값에 대한 출력을 해준다.
        if(printCount==1) {
            try {
            if (var(varialbe) == 'x') {
                return x;
            } else if (var(varialbe) == 'y') {

                return y;
            } else if (var(varialbe) == 'z') {

                return z;
            }
        }catch(...){
                cout << "syntax error!!\n";
                return "wrong";
            }
        }
    }else {
        //print가 없고 "=" 이 들어와 있는 경우다.
        char buffer;
        int variableCount = 0;
        for(int i = 0;i < (int)array.length(); i++){
            if(array[i] == ' '){
                //비어있는 경우에는 무시한다.
            }else if(array[i] == '='){
                if(array[i+1]!=' '){
                    cout << "syntax error!!\n";
                    return "wrong";
                }
                if(equalCount==0){
                    equalCount++;
                    //이제 뒤에 있는 것들을 expr로 넘기면 된다.
                    string newArray = array.substr(i+1);
                    //i+1부터의 값을 넘겨주면 된다.
                    //아까 var로 검사했던 값에 따라서 x,y,z에 해당하는 값을 할당해주면 된다.
                    if(buffer == 'x'){
                            x = expr(newArray);
                            if(x == "wrong"){
                                cout << "syntax error!!\n";
                                return "wrong";
                            }
                            return "ok";
                    }
                    else if(buffer == 'y'){
                            y = expr(newArray);
                            if(y == "wrong"){
                                cout << "syntax error!!\n";
                                return "wrong";
                            }
                             return "ok";
                    }else if(buffer == 'z'){
                            z  = expr(newArray);
                            if(z == "wrong"){
                                cout << "syntax error!!\n";
                                return "wrong";
                            }
                            return "ok";
                    }
                    }else{
                        cout << "syntax error!!\n";
                        return "wrong";
                    }
            }else if(var(array[i])!='q'){
                //x, y, z가 = 앞에 들어온 경우다.
                // = 뒤에 나온 경우와 변수가 = 전에 2번 나온 경우에 대한 예외처리이다.
                if(equalCount ==0){
                    if(variableCount==0){
                        buffer = var(array[i]);
                        variableCount++;
                    }else{
                        cout << "syntax error!!\n";
                        return "wrong";
                    }
                }else{
                    cout << "syntax error!!\n";
                    return "wrong";
                }
            }else if(var(array[i])=='q'){
                //x, y, z 대신에 다른 문자가 들어온 경우다.
                cout << "syntax error!!\n";
                return "wrong";
            }
        }
    }

    if(equalCount ==0 && printCount ==0){
        cout << "syntax error!!\n";
        return "wrong";
    }
    return "ok";
}

//expr함수입니다.
string expr(string newArray){
    //이 부분은 RD파서처럼 작동하지 못하고 뒤의 연산자가 무엇인지 확인해야 합니다.
    int bexprCount =0;
    string token;
    //공백을 기준으로 하나의 토큰으로 만듦니다.
    for (int i = 0; i < (int)newArray.length(); i++) {
     char ch = newArray[i];
        if (ch != ' ') {
            token += ch;
        } else {
            if (!token.empty()) {
                //아래의 논리연산자가 하나라도 있는 경우에는 bexpr로 판단하여 넘깁니다.
                if(token[0]=='='||token[0] == '!' || token[0] == '>' || token[0] == '<'){
                    bexprCount++;
                    break;
                }
                token.clear();
            }
        }
    }

    if(bexprCount ==0){
        //aexpr
        return aexpr(newArray);
    }else{
        //bexpr
        return bexpr(newArray);
    }
}

//bexpr 함수입니다.
string bexpr(string array){
    string token;
    int numberCount = 0;
    long long int number1;
    long long int number2;
    string logic;
    //순차적으로 공백을 기준으로 3개의 토큰을 입력받아 순서대로 처리해줍니다. 만약에 순서대로 입력이 되지 않는 경우에는 에러를 발생시킵니다.
    for (int i = 0; i < (int)array.length(); i++) {
        char ch = array[i];
        if (ch != ' ') {
            token += ch;
        } else {
            if (!token.empty()) {
                try {
                    if(numberCount == 0){
                        if(number(token)=="wrong"){
                            return "wrong";
                        }
                        number1 = stoll(number(token));
                        numberCount++;
                    } else if(numberCount == 1) {
                        if(relop(token)=="wrong"){
                            return "wrong";
                        }
                        logic = (relop(token));
                        numberCount++;
                    } else if(numberCount == 2) {
                        if(number(token)=="wrong"){
                            return "wrong";
                        }
                        number2 = stoll(number(token));
                        numberCount++;
                    }
                } catch (const invalid_argument& e) {
                    return "wrong";
                } catch (const out_of_range& e) {
                    return "wrong";
                }
                token.clear();
            }
        }
    }
    if(!token.empty()){
        return "wrong";
    }
    //들어온 토큰의 개수가 3개가 아닌 경우 에러를 출력합니다.
    if(numberCount !=3){
        return "wrong";
    }
    //아까 저장해두었던 logic에 대한 계산을 진행해줍니다.
    if(logic == "=="){
        if(number1 == number2){
            return "TRUE";
        }
        else{
            return "FALSE";
        }
    }else if(logic == "!=") {
        if(number1 != number2){
            return "TRUE";
        }
        else{
            return "FALSE";
        }
    }else if(logic == "<"){
        if(number1 < number2){
            return "TRUE";
        }else{
            return "FALSE";
        }
    }else if(logic == ">"){
        if(number1 > number2){
            return "TRUE";
        }else {
            return "FALSE";
        }
    }else if(logic == "<="){
        if(number1 <= number2){
            return "TRUE";
        }else {
            return "FALSE";
        }
    }else if(logic == ">="){
        if(number1 >= number2){
            return "TRUE";
        }else{
            return "FALSE";
        }
    }else{
        return "wrong";
    }
}
//논리연산자가 제대로 들어왔는지 판단하는 함수입니다.
string relop(string array){
    if(array == "=="){
        return array;
    }else if(array == "!="){
        return array;
    }else if(array =="<"){
        return  array;
    }else if(array == ">"){
        return array;
    }else if(array =="<="){
        return  array;
    }else if(array == ">="){
        return  array;
    }else{
        return "wrong";
    }
}


// term 함수
string term(string array) {
    string token;
    string pastToken;
    queue<string> que;
    string answer = "";
    int first = 0;

    for (int i = 0; i < (int)array.length(); i++) {
        char ch = array[i];
        if (ch != ' ') {
            token += ch;
        } else {
            if (!token.empty()) {
                if (token == "*" || token == "/") {
                    // *이나 /가 들어왔을 때는 큐에 연산자를 넣어서 다음 피연산자가 들어오면 계산해줍니다.
                    if (first == 0) {
                        que.push(token);
                    } else {
                        que.push(token);
                        if (que.front() == "*") {
                            //첫 번째 경우가 아니면 큐에서 연산자를 꺼내 연산합니다.
                            try {
                                answer = to_string(stoll(answer) * stoll(pastToken));
                            } catch (const std::invalid_argument& e) {
                                return "wrong";
                            } catch (const std::out_of_range& e) {
                                return "wrong";
                            }
                            que.pop();
                        } else {
                            try {
                                answer = to_string(stoll(answer) / stoll(pastToken));
                            } catch (const std::invalid_argument& e) {
                                return "wrong";
                            } catch (const std::out_of_range& e) {
                                return "wrong";
                            }
                            que.pop();
                        }
                    }
                    first++;
                } else {
                    pastToken = factor(token);
                    if (pastToken == "wrong") {
                        return "wrong";
                    }
                    if (first == 0) {
                        if (answer == "") {
                            answer = pastToken;
                        } else {
                            return "wrong";
                        }
                    }
                }
            }
            token.clear();
        }
    }

    // 마지막 남은 연산자 계산
    if (first != 0) {
        try {
            if (que.front() == "*") {
                answer = to_string(stoll(answer) * stoll(pastToken));
            } else {
                answer = to_string(stoll(answer) / stoll(pastToken));
            }
            que.pop();
            if (!que.empty()) {
                return "wrong";
            }
        } catch (const std::invalid_argument& e) {
            return "wrong";
        } catch (const std::out_of_range& e) {
            return "wrong";
        }
    }

    return answer;
}
// aexpr 함수
string aexpr(string array) {
    int arrayCount = 0;
    string newArray;
    int first = 0;
    string answer;
    queue<char> que;

    for(int i =0; i< (int)array.length();i++){
        if(array[i]=='+'||array[i]=='-'){
            newArray = array.substr(arrayCount,i-arrayCount);
            if(term(newArray)=="wrong"){
                return "wrong";
            }
            if(first == 0){
                answer = term(newArray);
            }
            if(first !=0){
                if(que.front()=='+') {
                    try {
                        answer = to_string(stoll(answer) + stoll(term(newArray)));
                    } catch (...) {
                        return "wrong";
                    }
                    que.pop();
                } else if(que.front()=='-'){
                    try {
                        int termVal = stoll(term(newArray));
                        if(termVal < 0){
                            return "wrong";
                        }
                        answer = to_string(stoll(answer) - termVal);
                    } catch (...) {
                        return "wrong";
                    }
                    que.pop();
                }
            }
            que.push(array[i]);
            first++;
            arrayCount = i+1;
        }
    }

    // 연산자 맨 뒤에 있는 term에 대한 처리
    newArray = array.substr(arrayCount,array.length()-arrayCount);
    if(term(newArray)=="wrong"){
        return "wrong";
    }
    if(!que.empty()) {
        if (que.front() == '+') {
            try {
                answer = to_string(stoll(answer) + stoll(term(newArray)));
            } catch (...) {
                return "wrong";
            }
            que.pop();
        } else if (que.front() == '-') {
            try {
                long long int termVal = stoll(term(newArray));
                if(termVal < 0){
                    return "wrong";
                }
                answer = to_string(stoll(answer) - termVal);
            } catch (...) {
                return "wrong";
            }
            que.pop();
        }
    }
    if(first==0){
        try {
            long long int termVal = stoll(term(newArray));
            if(termVal < 0){
                return "wrong";
            }
            answer = to_string(termVal);
        } catch (...) {
            return "wrong";
        }
    }
    return answer;
}

//factor함수입니다.
string factor (string array){
    return  number(array);
}
//number함수입니다.
string number (string array){
    string numberArray ="";
    for(int i=0; i< (int)array.length();i++){
        if(dec(array[i])=="wrong"){
            return "wrong";
        }
        numberArray.append(dec(array[i]));
    }
    return numberArray;
}
//dec함수입니다.
string dec(char number){
    string numberArray;
    switch (number) {
        case '0' :
            numberArray = "0";
            break;
        case '1' :
            numberArray = "1";
            break;
        case '2' :
            numberArray = "2";
            break;
        case '3' :
            numberArray = "3";
            break;
        case '4' :
            numberArray = "4";
            break;
        case '5' :
            numberArray = "5";
            break;
        case '6' :
            numberArray = "6";
            break;
        case '7' :
            numberArray = "7";
            break;
        case '8' :
            numberArray = "8";
            break;
        case '9' :
            numberArray = "9";
            break;
        default :
            numberArray = "wrong";
            break;
    }
    return numberArray;
}
//var함수입니다.
char var(char variable) {
    //x,y,z가 들어간 경우에는 각각을 리턴해준다.
    if(variable == 'x' || variable == 'y' || variable == 'z'){
        return variable;
    }else{
        return 'q';
    }
}

int main(void){
    while(true){
        string inputString;

        getline(cin,inputString);
        if(inputString == "terminate"){
            //terminate가 입력되면 종료
            cout << "Terminate program!\n";
            break;
        }
        else if (inputString.empty()){
            //그냥 엔터만 입력되었을 때의 에러처리
            cout << "syntax error!!\n";
        }
        else{
            //처음에 시작되면 전역변수들을 초기화시켜준다.
            x="0";
            y="0";
            z="0";
            program(inputString);

        }
    }
    return 0;
}
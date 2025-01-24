#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;
// using ll = long long int;
//declaration으로 쓴 것들을 처리하기 위해서 필요한 map함수입니다.
map< std::string, long long int> globalMap;
//que도 전역변수로 공유해서 do-while로 나오는 값들을 출력할 수 있도록 설정
queue<string> que;
//함수원형들
string statement(string);
string declaration(string);
string var(string);
string dec(char number);
string number(string);
string bexpr(string);
string aexpr(string);
string relop(string);
string factor(string);
string term(string);
string type(string);
char alphabet(char);

int printCounting;


// 맨 앞의 공백만 제거하는 함수
string ltrim(const string& str) {
    size_t start = str.find_first_not_of(" \t");
    return (start == string::npos) ? "" : str.substr(start);
}

// 문자열의 맨 앞과 끝의 공백을 제거하는 함수
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//do while문에서 수행해야할 것에 대해서 반복적으로 수행시키기 위해서 만들어진 함수입니다.
string loopWhile(string array){

    //이 부분이 이제 do while문에서 실행될 부분입니다.
    int index = 0;
    int count =0;
    string answer ;
    string blankArray;
    //이렇게 해둠으로써 statement가 여러번 반복되었을 경우를 처리할 수 있다.
    for(int i =0; i < (long long int)array.length(); i++){
        string doWhileInput = "";

        //do while이 들어오는 경우에 대해서 먼저 예외처리를 진행시켜줍니다.
        if(array[i] == 'd'){
            doWhileInput += 'd';
            if(array[++i]=='o'){
                if(array[++i]== ' '){
                    doWhileInput += 'o';
                    int checkPoint;
                    stack<char> stk1;
                    for(int p = i+1; p< (long long int)array.length();p++){
                        char c = array[p];
                        if (c == '{') {
                            stk1.push(c);
                        } else if (c == '}') {
                            if (stk1.empty()) {
                                return "wrong"; //짝이 맞지 않는 경우
                            }
                            stk1.pop();
                            if (stk1.empty()) {
                                doWhileInput += c;
                                checkPoint = p+1;
                                break;
                            }
                        }
                        doWhileInput += c;
                }
                //do 까지 확인 한 것 이제 while이 안에 있는지 확인하면 됩니다.
                //이제는 닫은 중괄호까지 doWhileInput에 들어가 있는 상태
                stack<char> stk2;
                for(int p = checkPoint; p< (long long int)array.length();p++){
                    char c = array[p];
                    if (c == '(') {
                        stk2.push(c);
                    } else if (c == ')') {
                        if (stk2.empty()) {
                            return "wrong"; //짝이 맞지 않는 경우
                        }
                        stk2.pop();
                        if (stk2.empty()) {
                            doWhileInput += c;
                            //이건 소괄호까지 끝난 후 뒤에 ;가 있는지만 확인하면 됩니다.
                            checkPoint = p+1;
                            break;
                        }
                    }
                    doWhileInput += c;
                }
                //이제 맨 뒤의 ;만 확인해주면 된다.
                for(int p = checkPoint;p<(long long int)array.length();p++){   
                    if(array[p]==';'){
                        checkPoint = p;
                        break;
                    }
                }
                //i를 checkPoint위치로 설정해두고 
                i = checkPoint;
                index = i+1;
                //wrong이 들어오면 리턴

                if(statement(doWhileInput)=="wrong"){
                    return "wrong";
                }
            }
        }

    }else if(array[i] == ';'){
                    
                    count ++;
                    string expression;
                    
                    expression = array.substr(index,i-index);
                    //잘못된 값이 입력된 경우에는 종료한다.
                    //"="나 "print"가 없는 경우에는 declaration을 사용합니다.
                    if((expression.find("=") != std::string::npos)||(expression.find("print") != std::string::npos)){
                        //출력해야할 값들을 넣어줍니다.
                        answer = statement(expression);
                        if(answer== "wrong"){
                            return "wrong";
                        }
                    
                        index = i+1;
                        blankArray.clear();
                        //그냥 정의만할 때는 ok를 리턴하기에 그냥 넘어가줍니다.
                        if (answer == "ok"){
                            continue;
                        }
                        //print를 통해서 값을 출력해야 하는 경우에는 큐에 넣어줍니다.
                        que.push(answer);
                    }else{
                        //state가 아닌 경우는 에러처리를 진행시켜줍니다.
                        return "wrong";
                    }
                    }else{
                        if(array[i]!=' '){
                            blankArray+=(array[i]);
                        }
                }
                }
                //; 뒤에 문자열이 남아있을 때에 대한 에러처리를 하기 위함입니다.
                if(!blankArray.empty()){
                    return "wrong";
                }
                // 세미콜론의 개수를 세서 세미콜론이 한 개도 없는 경우에는 syntax error를 출력하는 것이다.
                if(count == 0){
                    return "wrong";
                }
                return "ok";
}


//program함수
void program(string array){
    //이제 문자열에 ;이 들어간 것을 판단해야한다.
    //문자열을 뒤로 이동시키면서 ;가 나오면 그 전까지의 문자열을 판단하게끔 시행한다.
    int index = 0;
    int count =0;

    int StateCount = 0;
    string answer ;
    string blankArray;

    for(int i =0; i < (long long int)array.length(); i++){
    string doWhileInput = "";

        //do while문이 처음으로 등장하였을 때 program에서 처리해주는 방법입니다.
        if(array[i] == 'd'){
            doWhileInput += 'd';
            if(array[++i]=='o'){
                if(array[++i]== ' '){
                    doWhileInput += 'o';
                    int checkPoint;
                    stack<char> stk1;
                    for(int p = i+1; p< (long long int)array.length();p++){
                        char c = array[p];
                        if (c == '{') {
                            stk1.push(c);
                        } else if (c == '}') {
                            if (stk1.empty()) {
                                cout << "Syntax Error!!\n";
                                return ; //짝이 맞지 않는 경우
                            }
                            stk1.pop();
                            if (stk1.empty()) {
                                //이거를 처음에 넣어주고 뒤를 처리하기 위해서는 이렇게 해줍니다.
                                //array의 어디까지가 들어갔는지 확인하기 위해서 checkPoint설정
                                doWhileInput += c;
                                checkPoint = p+1;
                                break;
                            }
                        }
                        doWhileInput += c;
                }
                //do 까지 확인 한 것 이제 while이 안에 있는지 확인하면 됩니다.
                //이제는 닫은 중괄호까지 doWhileInput에 들어가 있는 상태
                stack<char> stk2;
                for(int p = checkPoint; p< (long long int)array.length();p++){
                    char c = array[p];
                    if (c == '(') {
                        stk2.push(c);
                    } else if (c == ')') {
                        if (stk2.empty()) {
                            cout << "Syntax Error!!\n";
                            return ; //짝이 맞지 않는 경우
                        }
                        stk2.pop();
                        if (stk2.empty()) {
                            //이거를 처음에 넣어주고 뒤를 처리하기 위해서는 이렇게 해줍니다.
                            //array의 어디까지가 들어갔는지 확인하기 위해서 checkPoint설정
                            doWhileInput += c;
                            //이건 소괄호까지 끝난 후 뒤에 ;가 있는지만 확인하면 됨
                            checkPoint = p+1;
                            break;
                        }
                    }
                    doWhileInput += c;
                }
                //이제 맨 뒤의 ;만 확인해주면 된다.
                for(int p = checkPoint;p <(long long int)array.length();p++){   
                    if(array[p]==';'){
                        checkPoint = p;
                        break;
                    }
                }
                //i를 checkPoint위치로 설정해두고 
                i = checkPoint;
                index = i+1;
                //wrong이 들어오면 리턴
                if(statement(doWhileInput)=="wrong"){
                     cout << "Syntax Error!!\n";
                    return ;
                }
            }
        }
    }else if(array[i] == ';'){
            count ++;
            string expression;
            //;를 빼고 값을 넣어주는 형식일거임
            expression = array.substr(index,i-index);
            //잘못된 값이 입력된 경우에는 종료한다.
            //"="나 "print"가 없는 경우에는 declaration을 사용합니다.
            if((expression.find("=") != std::string::npos)||(expression.find("print") != std::string::npos)){
                //아닌 경우에는 statement로 넣어줍니다.
                //출력해야할 값들을 넣어줍니다.
                answer = statement(expression);
                if(answer== "wrong"){
                    //여기서 cout하는 것도 고려해볼 수 있다.
                    cout << "Syntax Error!!\n";
                    return ;
                }
                StateCount += 1;
            
                index = i+1;
                blankArray.clear();
                //그냥 정의만할 때는 ok를 리턴하기에 그냥 넘어가줍니다.
                if (answer == "ok"){
                    continue;
                }
                //print를 통해서 값을 출력해야 하는 경우에는 큐에 넣어줍니다.
                que.push(answer);

            }else{
                if(StateCount == 0){
                    //여기가 declartion이 있는 경우입니다.
                    if(array[i-1] != ' '){
                        cout << "Syntax Error!!\n";
                        return;
                    }
                    if(declaration(expression)=="wrong"){
                        cout << "Syntax Error!!\n";
                        return;
                    }
                    index = i+1;
                    blankArray.clear();
                }else{
                    //state가 나온 뒤에 declaration이 나온 경우를 막기 위해서 입니다.
                    cout << "Syntax Error!!\n";
                    return ;
                }
            }
        }else{
            if(array[i]!=' '){
                blankArray+=(array[i]);
            }
    }
    }
    //; 뒤에 문자열이 남아있을 때에 대한 에러처리를 하기 위함입니다.
    if(!blankArray.empty()){
        cout << "Syntax Error!!\n";
        return ;
    }
    // 세미콜론의 개수를 세서 세미콜론이 한 개도 없는 경우에는 syntax error를 출력하는 것이다.
    if(count == 0){
        cout << "Syntax Error!!\n";
        return ;
    }
    //print로 출력해야하는 것들을 출력해줍니다.
    while(!que.empty()){
        cout << que.front() << " ";
        que.pop();
    }
    if(printCounting != 0){
        cout << "\n";
    }
}

//declaration함수
string declaration(string array){

    vector<string> tokens;

    //한글자씩 비교할 수 없기에 토큰으로 잘라서 벡터에 넣어주고 그것을 비교합니다.
    istringstream iss(array);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    //토큰의 개수가 2개가 아니면 2를 리턴
    if(tokens.size() !=2){
        return "wrong";
    }

    if(type(tokens[0])=="wrong"){
        return  "wrong";
    }

    if(var(tokens[1])=="wrong"){
            return "wrong";
    }
    //map안에 값을 넣어줍니다.
    
    //초기에는 0으로 초기화시켜줘야 하기 떄문에 0을 넣어줍니다.
    globalMap.insert(make_pair(var(tokens[1]),0));
    return "ok";
}



//statement 함수
string statement(string array){
    string answer;

    int equalCount = 0;
    int printCount = 0;
    string content;

    //do-while문에 대한 예외처리를 가장 먼저 해줘야 한다.
    if((array.find("do")  != string::npos)&&(array.find("while")  != string::npos)){
        stack<char> stk;
        //do랑 while이 있지 않는 이상 do-while이 안되게끔 하는 것입니다.
        int checkPoint;
        for(int i = 0; i<(long long int)array.length();i++){
            if(array[i] == ' '){
            //빈 공간은 없앱니다.
            }else if(array[i] == 'd'){
                if(array[++i]=='o'){
                    array = array.substr(i+1);
                    array = ltrim(array);
                    //중괄호를 여는게 없는 경우에는 리턴해준다.
                    if(array[0] != '{'){
                        return "wrong";
                    }
                    //하나 넣어놔줘야함
                    stk.push('{');
                    for(int p = 1; p< (int)array.length();p++){
                        char c = array[p];
                        if (c == '{') {
                            stk.push(c);
                        } else if (c == '}') {
                            if (stk.empty()) {
                                return "wrong"; //짝이 맞지 않는 경우
                            }
                            stk.pop();
                            if (stk.empty()) {
                                //이거를 처음에 넣어주고 뒤를 처리하기 위해서는 이렇게 해줍니다.
                                //array의 어디까지가 들어갔는지 확인하기 위해서 checkPoint설정
                                checkPoint = p+1;
                                //닫는 중괄호 뺌
                                break;
                            }
                        }
                        content += c;
                    }

                    //이렇게 한 번 수행시키고 while문 판단하고 무한 루프를 돌려주면 됩니다.
                    //이 부분이 이제 do while문에서 실행될 부분입니다.
                    if(loopWhile(content)=="wrong"){
                        return "wrong";
                    }
                    //checkPoint부터 끝까지를 저장시켜준다.
                    string newArray = array.substr(checkPoint);
                    newArray = ltrim(newArray);
                    string newContent;
                    //while문을 읽어들여가는 과정이 이제 필요하다.

                    if(newArray.length() <= 5){
                        return "wrong";    
                    }
                    if(newArray[0]!='w'){
                        return "wrong";
                    }
                    if(newArray[1]!='h'){
                        return "wrong";
                    }
                    if(newArray[2]!='i'){
                        return "wrong";
                    }
                    if(newArray[3]!='l'){
                        return "wrong";
                    }
                    if(newArray[4]!='e'){
                        return "wrong";
                    }
                    newArray = newArray.substr(5);
                    newArray = ltrim(newArray);
                    if(newArray[0] != '('){
                        return "wrong";
                    }
                    //하나넣어줘야 한다.
                    stk.push('(');

                    for(int p = 1; p< (int)newArray.length();p++){
                        char c = newArray[p];
                        if (c == '(') {
                            stk.push(c);
                        } else if (c == ')') {
                            if (stk.empty()) {
                                return "wrong"; //짝이 맞지 않는 경우
                            }
                            stk.pop();
                            if (stk.empty()) {
                                //이거를 처음에 넣어주고 뒤를 처리하기 위해서는 이렇게 해줍니다.
                                //array의 어디까지가 들어갔는지 확인하기 위해서 checkPoint설정
                                checkPoint = p+1;
                                break;
                            }
                        }
                        newContent += c;
                    }
                    //아예 문법적으로 틀린 경우에는 에러처리
                    if(bexpr(newContent)=="wrong"){
                        return "wrong";
                    }

                   int ccount = 0;
                   while(bexpr(newContent)=="TRUE"){
                        loopWhile(content);
                   }
                   return "ok";
                }
            }
        }

    //do while 문 안에 print가 있을 수 있기에 그 부분을 잘 처리해야합니다.

    }else if(array.find("print")  != string::npos){
        //뒤에 다른 변수가 없는지 확인해줘야 한다.
        int varCheck =0;
        //print 문자열이 몇번 쓰였는지 확인하기 위해서 사용하는 것이다.
        for(int i =0; i< (long long int)array.length();i++){
            if(array[i] == ' '){
            //빈 공간의 경우 넘어간다.
            
            }else if(array[i] == 'p'){
                //print가 쓰여있는 경우에 시행되는 것이기에 이렇게 이게 순서대로 쓰여있는지 확인한다.
                if(array[++i]=='r'){
                    if(array[++i] == 'i'){
                        if(array[++i] == 'n'){
                            if(array[++i]=='t'){
                                printCount ++;
                                printCounting ++;
                                //바로 뒤에 ;가 나오는 경우에 대한 예외처리를 한다.
                                if(array[i+1]==';'){
                                    return "wrong";
                                }
                                //print뒤에 공백이 아닌 경우에 에러처리를 진행해줍니다.
                                if(array[i+1]!=' '){
                                    return "wrong";
                                }
                                
                                if(printCount != 1){
                                    return "wrong";
                                }
                            }
                            else{
                                return "wrong";
                            }
                        }
                        else{
                            return "wrong";
                        }
                    }
                    else{
                        return "wrong";
                    }
                }else{
                    return "wrong";
                }
            }else{
                //print를 제외한 다른 단어에 대해서 bexpr, aexpr로 확인한다.
                if(varCheck==0){
                    //문자열 끝까지를 잘라서 넣어준다.
                    string expressionArray = array.substr(i,(long long int)array.length());
                    expressionArray = ltrim(expressionArray);
                    if(expressionArray.empty()){
                        return "wrong";
                    }
                    //논리연산자가 바로 나올 경우에는 bexpr로 넣어주어야 합니다.
                    if((expressionArray[0] == '=')|| (expressionArray[0] == '!')||(expressionArray[0] == '>')||(expressionArray[0] == '<')){

                        if((answer = bexpr(expressionArray))=="wrong"){
                            return "wrong";
                        }
                    }else{
                        if((answer = aexpr(expressionArray))=="wrong"){
                            return "wrong";
                        }

                    }

                    varCheck++;
                    //다 넣어줬으면 반복문을 반복할 이유가 없기에 종료시켜준다.
                    break;
                }else{
                    //print가 아니라 다른게 먼저 나왔을 때에 대한 예외처리입니다.
                    return "wrong";
                }
            }
        }
        //print가 있을 때 답을 리턴시켜서 queue에 넣어줍니다.
        if(printCount==1) {
            try {
                if(answer.empty()){
                    return "wrong";
                }
                return answer;
        }catch(...){
                return "wrong";
            }
        }



        }//여기까지가 print가 있는 경우
        else {
        //정의 하는 경우입니다.
        //print가 없고 "=" 이 들어와 있는 경우다.
            string buffer;
            string answerings;
            int variableCount = 0;
            int blankCount = 0;
            for(int i = 0;i < (int)array.length(); i++){
                if(array[i] == ' '){
                    //비어있는 경우에는 무시한다.
                    blankCount ++;
                }else if(array[i] == '='){
                    if(array[i+1]!=' '){
                        return "wrong";
                    }
                    if(equalCount==0){
                        equalCount++;
                        //이건 앞에 있는 변수의 값이다.
                        string forwardArray = array.substr(0,i);
                        //이제 뒤에 있는 것들을 aexpr로 넘기면 된다.
                        string newArray = array.substr(i+1);
                        //i+1부터의 값을 넘겨주면 된다.

                        if((buffer = var(forwardArray))=="wrong"){
                            return "wrong";
                        }
        
                        if((answerings = aexpr(newArray))=="wrong"){
                            return "wrong";
                        }
                        map<string, long long int>::iterator it = globalMap.find(buffer);
                        // Answer가 맵에 있을 경우 정수로 변환하여 출력
                        if (it != globalMap.end()) {
                            int AnswerInt = it->second;
                            it->second  = stoll(answerings);
                            //결과를 문자열로 리턴해서 보내줘야함.
                            return "ok";
                        }else{
                            return "wrong";
                        }
                    }
            }
        }
        }

        if(equalCount ==0 && printCount ==0){
            return "wrong";
        }
    return "ok";
}



//bexpr 함수입니다.
string bexpr(string array){
    string token;
    int numberCount = 0;
    long long int number1;
    long long int number2;
    string logic;
    //이 토큰 두 개의 값을 가지고 연산을 해서 진행하는 것입니다.
    string atoken1;
    string atoken2;
    int heee = 0;
    //순차적으로 공백을 기준으로 3개의 토큰을 입력받아 순서대로 처리해줍니다. 만약에 순서대로 입력이 되지 않는 경우에는 에러를 발생시킵니다.
    for (int i = 0; i < (long long int)array.length(); i++) {
        char ch = array[i];
        if (ch != ' ') {
            token += ch;
        } else {
            if (!token.empty()) {
                try {
                    if(numberCount == 0){
                        //맨 처음에는 relop이 들어와야하니까 판단해준다.
                        if((logic = relop(token))=="wrong"){
                                return "wrong";
                        }
                        numberCount ++;

                        for (int p = i+1; p < (long long int)array.length(); p++) {
                            //밑의 조건들이 등장하였을 때 다음의 것도 밑의 조건들을 만족하는지 판단하는 과정이 필요합니다.
                            //처음에 등장하는 부분들은 전부 atoken1에 넘김
;
                            if((array[p] == ')')||((array[p] >=48)&&(array[p]<=57))||((array[p]>=65)&&(array[p]<=90))||((array[p]>=97)&&(array[p]<=122))){
                                //다음 것이 공백인 경우
                                if(array[p+1]==' '){
                                        
                                    for (int k = p+1; k < (long long int)array.length(); k++) {
                                        if(array[k]== ' '){
                                        
                                        }else if((array[k]=='+')||(array[k]=='-')||(array[k]=='*')||(array[k]=='/')){
                                            //연산자는 건너뛰어줍니다.
                                            break;
                                        }else{
                                            //뒤의 이것들이 나온 경우 뒤는 전부 atoken2 다.
                                        
                                            if((array[k] == '(')||((array[k] >=48)&&(array[k]<=57))||((array[k]>=65)&&(array[k]<=90))||((array[k]>=97)&&(array[k]<=122))){ 
                                                atoken2 = array.substr(k);
                                                atoken1 = array.substr(i+1,k-(i+1));
                                                i = k;
                                                heee = 1;
                                                break;
                                                //뒷부분은 다 atoken2로 넘깁니다.
                                            }
                                        }
                                }  
                                if(heee ==1){
                                    break; 
                                }
                            }
                        }
                    }
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

    string answer1;
    if((answer1=aexpr(atoken1))=="wrong"){
        return "wrong";
    }
    string answer2;
    if((answer2=aexpr(atoken2))=="wrong"){
        return "wrong";
    }
    
    number1 = stoll(answer1);
    number2 = stoll(answer2);
    
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
    stack<char> stk;
    array = ltrim(array);
    for (int i = 0; i < (long long int)array.length(); i++) {
        char ch = array[i];
        //여기서 그냥 ( 안에 있는 것들은 쭉 추가해서 넣어주게끔 설정해줘야한다.
        if(ch == '('){
            if(token.empty() == false) {
                // '('앞에 문자열들이 붙어 있는 경우입니다.
                return "wrong";
            }
            stk.push('(');
            for(int p = i+1; p< (long long int)array.length();p++){
                        char c = array[p];
                        if (c == '(') {
                            stk.push(c);
                        } else if (c == ')') {
                            if (stk.empty()) {
                                return "wrong"; //짝이 맞지 않는 경우
                            }
                            stk.pop();
                            if (stk.empty()) {
                                return aexpr(token);
                                token.clear();
                                break;
                            }
                        }
                        token += c;
                    }
        }else if (ch != ' ')  {
            token += ch;
        }
    }
       
    if((token[0] >= 48 )&& (token[0] <= 57)){
        //숫자가 들어온 경우에는 number를 호출해주고 다른 문자가 들어온 경우에는 var를 호출해주는 식으로 작성하면 됩니다.
        //숫자를 출력해줘야하니가
        return number(token);
    }else{
        
        string Answer;
        if((Answer= var(token))=="wrong"){
            return "wrong";
        }

        map<string, long long int>::iterator it = globalMap.find(Answer);
        // Answer가 맵에 있을 경우 정수로 변환하여 출력
        if (it != globalMap.end()) {
            long long int AnswerInt = it->second;
            //결과를 문자열로 리턴해서 보내줘야함.
            return to_string(AnswerInt);
        } else {
            //찾는게 없는 경우입니다.
            return "wrong";
        }
    }
    //중간에 안넘어가고 이상하게 간 것이기 때문에 wrong을 리턴
    return "wrong";
}


// aexpr 함수
string aexpr(string array) {
    int arrayCount = 0;
    string newArray = "";
    int first = 0;
    string answer = "";
    queue<char> que;
    int openBracket = 0;
    stack<char> stk;
    string content = "";
    
    //연산할 때 사용해야하는 왼쪽 것의 값입니다.
    string lhd = "";

    for(int i =0; i< (long long int)array.length();i++){


        //처음이 괄호로 나오는 경우에 대한 예외처리
        if(array[i] == '('){
            //괄호 안의 내용을 추출하는 경우
            for(int p = i; p< (int)array.length();p++){

                char c = array[p];
                if (c == '(') {
                    stk.push(c);
                } else if (c == ')') {
                    if (stk.empty()) {
                        return "wrong"; //짝이 맞지 않는 경우
                    }
                    stk.pop();
                    if (stk.empty()) {
                        //이러면 ()를 붙힌 채 term에게 넘기는 형태입니다.
                        content += c;

                        if((lhd = term(content))=="wrong"){
                            return "wrong";
                        }
                        //이거를 처음에 넣어주고 뒤를 처리하기 위해서는 이렇게 해줍니다.
                        i = p+1;
                    }
                }
                content += c;
            }
        }

        if(array[i]=='+'||array[i]=='-'||array[i]=='*'||array[i]=='/'){
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
                } else if(que.front()=='*'){
                    try {
                        int termVal = stoll(term(newArray));
                        if(termVal < 0){
                            return "wrong";
                        }
                        answer = to_string(stoll(answer) * termVal);
                    } catch (...) {
                        return "wrong";
                    }
                    que.pop();
                } else if(que.front()=='/'){
                    try {
                        int termVal = stoll(term(newArray));
                        if(termVal < 0){
                            return "wrong";
                        }
                        answer = to_string(stoll(answer) / termVal);
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
        }else if (que.front() == '*') {
            try {
                long long int termVal = stoll(term(newArray));
                if(termVal < 0){
                    return "wrong";
                }
                answer = to_string(stoll(answer) * termVal);
            } catch (...) {
                return "wrong";
            }
            que.pop();
        }else if (que.front() == '/') {
            try {
                long long int termVal = stoll(term(newArray));
                if(termVal < 0){
                    return "wrong";
                }
                answer = to_string(stoll(answer) / termVal);
            } catch (...) {
                return "wrong";
            }
            que.pop();
        }
    }
    if(first==0){
        try {
            long long int termVal = stoll(term(newArray));
            
            answer = to_string(termVal);
        } catch (...) {
            return "wrong";
        }
    }
    return answer;
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
string var(string array){
    string numberArray ="";
    array = trim(array);

    for(int i=0; i< (int)array.length();i++){
        if(alphabet(array[i]) =='\0'){
            return "wrong";
        }
        numberArray.push_back(alphabet(array[i]));
    }
    return numberArray;
}


//alphabet함수입니다
char alphabet(char variable){

    switch (variable) {
        case 'a' : return 'a';
        case 'b' : return 'b';
        case 'c' : return 'c';
        case 'd' : return 'd';
        case 'e' : return 'e';
        case 'f' : return 'f';
        case 'g' : return 'g';
        case 'h' : return 'h';
        case 'i' : return 'i';
        case 'j' : return 'j';
        case 'k' : return 'k';
        case 'l' : return 'l';
        case 'm' : return 'm';
        case 'n' : return 'n';
        case 'o' : return 'o';
        case 'p' : return 'p';
        case 'q' : return 'q';
        case 'r' : return 'r';
        case 's' : return 's';
        case 't' : return 't';
        case 'u' : return 'u';
        case 'v' : return 'v';
        case 'w' : return 'w';
        case 'x' : return 'x';
        case 'y' : return 'y';
        case 'z' : return 'z';
        default : return '\0';

    }
}


//type 함수입니다.
string type(string array){

    if(array == "int"){
        return array;
    }else{
        //int가 아닌 다른 값이 들어온 경우에는 에러를 처리해줍니다.
        return "wrong";
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
            cout << "Syntax Error!!\n";
        }
        else{
            //처음에 시작되면 전역변수들을 초기화시켜준다.
            globalMap.clear();
            //큐도 전부 비워줍니다.
             while (!que.empty()) {
                    que.pop();
            }
            printCounting = 0;
            program(inputString);

        }
    }
    return 0;
}
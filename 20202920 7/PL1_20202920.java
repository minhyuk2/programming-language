import java.util.Queue;
import java.util.LinkedList;
import java.util.Scanner;

public class PL1_20202920 {
    // x, y, z 변수 값들을 저장하기 위한 전역 변수
    static String x = "0";
    static String y = "0";
    static String z = "0";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); // Scanner 객체 생성
        while (true) {
            String inputString = scanner.nextLine(); // 표준 입력에서 한 줄을 읽음
            x = "0";
            y = "0";
            z = "0";
            if (inputString.equals("terminate")) {
                System.out.println("Terminate program!");
                break;
            } else if (inputString.isEmpty()) {
                System.out.println("syntax error!!");
            } else {
                program(inputString);
            }
        }
        scanner.close(); // Scanner 사용 종료 후 닫기
    }
    // program 함수
    static void program(String array) {
        int index = 0;
        int count = 0;
        String answer;

        Queue<String> que = new LinkedList<>();
        StringBuilder blankArray = new StringBuilder();

        for (int i = 0; i < array.length(); i++) {
            if (array.charAt(i) == ';') {
                count++;
                String expression = array.substring(index, i);
                answer = statement(expression);
                if (answer.equals("wrong")) {
                    return;
                }
                index = i + 1;
                blankArray.setLength(0);
                if (!answer.equals("ok")) {
                    que.add(answer);
                }
            } else {
                if (array.charAt(i) != ' ') {
                    blankArray.append(array.charAt(i));
                }
            }
        }
        if (!blankArray.isEmpty()) {
            System.out.println("syntax error!!");
            return;
        }

        if (count == 0) {
            System.out.println("syntax error!!");
            return;
        }

        while (!que.isEmpty()) {
            System.out.print(que.poll() + " ");
        }
        System.out.println();
    }

    // statement 함수
    static String statement(String array) {
        char variable = 0;
        int equalCount = 0;
        int printCount = 0;
        //statement는 print가 있는지 = 가 있는지에 따라 판단해야하기에 이렇게 사용합니다.
        //문자열이 print를 포함하는 경우에 대한 처리입니다.
        if (array.contains("print")) {
            int varCheck = 0;
            for (int i = 0; i < array.length(); i++) {
                if (array.charAt(i) == ' ') {
                    // 공백은 무시
                } else if (array.charAt(i) == 'p') {
                    if (array.charAt(++i) == 'r') {
                        if (array.charAt(++i) == 'i') {
                            if (array.charAt(++i) == 'n') {
                                if (array.charAt(++i) == 't') {
                                    printCount++;
                                    //print 뒤에 ;가 오는 경우에 대한 예외처리
                                    if (array.charAt(i + 1) == ';') {
                                        System.out.println("syntax error!!");
                                        return "wrong";
                                    }
                                    //print 뒤에 바로 x,y,z가 오는 것에 대한 예외처리
                                    if(array.charAt(i+1)=='x'||array.charAt(i+1)=='y'||array.charAt(i+1) == 'z'){
                                        System.out.println("syntax error!!");
                                        return "wrong";
                                    }
                                    if (printCount != 1) {
                                        System.out.println("syntax error!!");
                                        return "wrong";
                                    }
                                } else {
                                    System.out.println("syntax error!!");
                                    return "wrong";
                                }
                            } else {
                                System.out.println("syntax error!!");
                                return "wrong";
                            }
                        } else {
                            System.out.println("syntax error!!");
                            return "wrong";
                        }
                    } else {
                        System.out.println("syntax error!!");
                        return "wrong";
                    }
                } else {
                    if (varCheck == 0) {
                        if (var(array.charAt(i)) == 'q') {
                            System.out.println("syntax error!!");
                            return "wrong";
                        }
                        varCheck++;
                        variable = var(array.charAt(i));
                    } else {
                        System.out.println("syntax error!!");
                        return "wrong";
                    }
                }
            }
            //해당하는 변수에 대한 것을 출력해줍니다.
            if (printCount == 1) {
                if (var(variable) == 'x') {
                    return x;
                } else if (var(variable) == 'y') {
                    return y;
                } else if (var(variable) == 'z') {
                    return z;
                }else{
                    System.out.print("syntax error!!");
                    return "wrong";
                }
            }
        } else {
            // 대입연산자에 대한 연산과정을 처리하기 위해 expr함수를 호출하여 재귀적으로 시행시켜줍니다.
            char buffer = 0;
            int variableCount = 0;
            for (int i = 0; i < array.length(); i++) {
                if (array.charAt(i) == ' ') {
                    // 공백은 무시
                } else if (array.charAt(i) == '=') {
                    try {
                        if (array.charAt(i + 1) != ' ') {
                            System.out.println("syntax error!!");
                            return "wrong";
                        }
                        if (equalCount == 0) {
                            equalCount++;
                            String newArray = array.substring(i + 1);
                            if (buffer == 'x') {
                                x = expr(newArray);
                                if (x.equals("wrong")) {
                                    System.out.println("syntax error!!");
                                    return "wrong";
                                }
                                return "ok";
                            } else if (buffer == 'y') {
                                y = expr(newArray);
                                if (y.equals("wrong")) {
                                    System.out.println("syntax error!!");
                                    return "wrong";
                                }
                                return "ok";
                            } else if (buffer == 'z') {
                                z = expr(newArray);
                                if (z.equals("wrong")) {
                                    System.out.println("syntax error!!");
                                    return "wrong";
                                }
                                return "ok";
                            }
                        } else {
                            System.out.println("syntax error!!");
                            return "wrong";
                        }
                    }
                catch(NullPointerException | StringIndexOutOfBoundsException e){
                    System.out.println("syntax error!!");
                    return "wrong";
                }
                }else if (var(array.charAt(i)) != 'q') {
                    if (equalCount == 0) {
                        if (variableCount == 0) {
                            buffer = var(array.charAt(i));
                            variableCount++;
                        } else {
                            System.out.println("syntax error!!");
                            return "wrong";
                        }
                    } else {
                        System.out.println("syntax error!!");
                        return "wrong";
                    }
                } else if (var(array.charAt(i)) == 'q') {
                    System.out.println("syntax error!!");
                    return "wrong";
                }
            }
        }

        if (equalCount == 0 && printCount == 0) {
            System.out.println("syntax error!!");
            return "wrong";
        }
        return "ok";
    }

    // expr 함수
    static String expr(String newArray) {
        int bexprCount = 0;
        String token = "";
        //한글자씩 읽어들이며 토큰을 만들어서 연산자가 어떤 것이 들어오냐에 따라 aexpr과 bexpr를 다르게 합니다.
        for (int i = 0; i < newArray.length(); i++) {
            if (newArray.charAt(i) != ' ') {
                token += newArray.charAt(i);
            } else {
                if (!token.isEmpty()) {
                    if (token.charAt(0) == '=' || token.charAt(0) == '!' || token.charAt(0) == '>' || token.charAt(0) == '<') {
                        bexprCount++;
                        break;
                    }
                    token = "";
                }
            }
        }
        if (bexprCount == 0) {
            return aexpr(newArray);
        } else {
            return bexpr(newArray);
        }
    }

    // bexpr 함수
    static String bexpr(String array) {
        String token = "";
        int numberCount = 0;
        long number1 = 0;
        long number2 = 0;
        String logic = "";
        for (int i = 0; i < array.length(); i++) {
            if (array.charAt(i) != ' ') {
                token += array.charAt(i);
            } else {
                if (!token.isEmpty()) {
                    try {
                        if (numberCount == 0) {
                            if (number(token).equals("wrong")) {
                                return "wrong";
                            }
                            number1 = Long.parseLong(number(token));
                            numberCount++;
                        } else if (numberCount == 1) {
                            if (relop(token).equals("wrong")) {
                                return "wrong";
                            }
                            logic = relop(token);
                            numberCount++;
                        } else if (numberCount == 2) {
                            if (number(token).equals("wrong")) {
                                return "wrong";
                            }
                            number2 = Long.parseLong(number(token));
                            numberCount++;
                        }
                    } catch (NumberFormatException e) {
                        return "wrong";
                    }
                    token = "";
                }
            }
        }
        if (!token.isEmpty()) {
            return "wrong";
        }
        if (numberCount != 3) {
            return "wrong";
        }
        if (logic.equals("==")) {
            return number1 == number2 ? "TRUE" : "FALSE";
        } else if (logic.equals("!=")) {
            return number1 != number2 ? "TRUE" : "FALSE";
        } else if (logic.equals("<")) {
            return number1 < number2 ? "TRUE" : "FALSE";
        } else if (logic.equals(">")) {
            return number1 > number2 ? "TRUE" : "FALSE";
        } else if (logic.equals("<=")) {
            return number1 <= number2 ? "TRUE" : "FALSE";
        } else if (logic.equals(">=")) {
            return number1 >= number2 ? "TRUE" : "FALSE";
        } else {
            return "wrong";
        }
    }

    // relop 함수
    static String relop(String array) {
        switch (array) {
            case "==":
            case "!=":
            case "<":
            case ">":
            case "<=":
            case ">=":
                return array;
            default:
                return "wrong";
        }
    }

    // aexpr 함수
    static String aexpr(String array) {
        int arrayCount = 0;
        String newArray;
        int first = 0;
        String answer = "";
        Queue<Character> que = new LinkedList<>();

        for (int i = 0; i < array.length(); i++) {
            if (array.charAt(i) == '+' || array.charAt(i) == '-') {
                newArray = array.substring(arrayCount, i);
                if (term(newArray).equals("wrong")) {
                    return "wrong";
                }
                if (first == 0) {
                    answer = term(newArray);
                }
                if (first != 0) {
                    if (que.peek() == '+') {
                        try {
                            answer = String.valueOf(Long.parseLong(answer) + Long.parseLong(term(newArray)));
                        } catch (NumberFormatException e) {
                            return "wrong";
                        }
                        que.poll();
                    } else if (que.peek() == '-') {
                        try {
                            long termVal = Long.parseLong(term(newArray));
                            if (termVal < 0) {
                                return "wrong";
                            }
                            answer = String.valueOf(Long.parseLong(answer) - termVal);
                        } catch (NumberFormatException e) {
                            return "wrong";
                        }
                        que.poll();
                    }
                }
                que.add(array.charAt(i));
                first++;
                arrayCount = i + 1;
            }
        }

        newArray = array.substring(arrayCount);
        if (term(newArray).equals("wrong")) {
            return "wrong";
        }
        if (!que.isEmpty()) {
            if (que.peek() == '+') {
                try {
                    answer = String.valueOf(Long.parseLong(answer) + Long.parseLong(term(newArray)));
                } catch (NumberFormatException e) {
                    return "wrong";
                }
                que.poll();
            } else if (que.peek() == '-') {
                try {
                    long termVal = Long.parseLong(term(newArray));
                    if (termVal < 0) {
                        return "wrong";
                    }
                    answer = String.valueOf(Long.parseLong(answer) - termVal);
                } catch (NumberFormatException e) {
                    return "wrong";
                }
                que.poll();
            }
        }
        if (first == 0) {
            try {
                long termVal = Long.parseLong(term(newArray));
                if (termVal < 0) {
                    return "wrong";
                }
                answer = String.valueOf(termVal);
            } catch (NumberFormatException e) {
                return "wrong";
            }
        }
        return answer;
    }

    // term 함수
    static String term(String array) {
        String token = "";
        String pastToken = "";
        Queue<String> que = new LinkedList<>();
        String answer = "";
        int first = 0;

        for (int i = 0; i < array.length(); i++) {
            if (array.charAt(i) != ' ') {
                token += array.charAt(i);
            } else {
                if (!token.isEmpty()) {
                    if (token.equals("*") || token.equals("/")) {
                        if (first == 0) {
                            que.add(token);
                        } else {
                            que.add(token);
                            if (que.peek().equals("*")) {
                                try {
                                    answer = String.valueOf(Long.parseLong(answer) * Long.parseLong(pastToken));
                                } catch (NumberFormatException e) {
                                    return "wrong";
                                }
                                que.poll();
                            } else {
                                try {
                                    answer = String.valueOf(Long.parseLong(answer) / Long.parseLong(pastToken));
                                } catch (NumberFormatException e) {
                                    return "wrong";
                                }
                                que.poll();
                            }
                        }
                        first++;
                    } else {
                        pastToken = factor(token);
                        if (pastToken.equals("wrong")) {
                            return "wrong";
                        }
                        if (first == 0) {
                            if (answer.equals("")) {
                                answer = pastToken;
                            } else {
                                return "wrong";
                            }
                        }
                    }
                }
                token = "";
            }
        }

        if (first != 0) {
            if (que.peek().equals("*")) {
                try {
                    answer = String.valueOf(Long.parseLong(answer) * Long.parseLong(pastToken));
                } catch (NumberFormatException e) {
                    return "wrong";
                }
                que.poll();
            } else {
                try {
                    answer = String.valueOf(Long.parseLong(answer) / Long.parseLong(pastToken));
                } catch (NumberFormatException e) {
                    return "wrong";
                }
                que.poll();
            }
            if (!que.isEmpty()) {
                return "wrong";
            }
        }

        return answer;
    }

    // factor 함수
    static String factor(String array) {
        String numberResult = number(array);
        if (numberResult.equals("wrong")) {
            return "wrong";
        }
        return numberResult;
    }

    // number 함수
    static String number(String array) {
        StringBuilder numberArray = new StringBuilder();
        for (int i = 0; i < array.length(); i++) {
            String decResult = dec(array.charAt(i));
            if (decResult.equals("wrong")) {
                return "wrong";
            }
            numberArray.append(decResult);
        }
        return numberArray.toString();
    }

    // dec 함수
    static String dec(char number) {
        switch (number) {
            case '0':
                return "0";
            case '1':
                return "1";
            case '2':
                return "2";
            case '3':
                return "3";
            case '4':
                return "4";
            case '5':
                return "5";
            case '6':
                return "6";
            case '7':
                return "7";
            case '8':
                return "8";
            case '9':
                return "9";
            default:
                return "wrong";
        }
    }

    // var 함수
    static char var(char variable) {
        if (variable == 'x' || variable == 'y' || variable == 'z') {
            return variable;
        } else {
            return 'q';
        }
    }
}

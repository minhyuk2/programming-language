import queue

# 전역 변수로 x, y, z 선언
x = "0"
y = "0"
z = "0"


# factor 함수
def factor(array):
    return number(array)


# number 함수
def number(array):
    number_array = ""
    for char in array:
        dec_result = dec(char)
        if dec_result == "wrong":
            return "wrong"
        number_array += dec_result
    return number_array


# dec 함수
def dec(number):
    #0-9의 값인지 판단하여 그렇지 않은 경우에는 wrong을 리턴한다.
    if number in "0123456789":
        return number
    else:
        return "wrong"


# var 함수
def var(variable):
    if variable in ['x', 'y', 'z']:
        return variable
    else:
        return 'q'


# term 함수
def term(array):
    token = ""
    past_token = ""
    que = queue.Queue()
    answer = ""
    first = 0

    for char in array:
        if char != ' ':
            token += char
        else:
            if token:
                if token == "*" or token == "/":
                    if first == 0:
                        que.put(token)
                    else:
                        que.put(token)
                        try:
                            if que.queue[0] == "*":
                                answer = str(int(answer) * int(past_token))
                            else:
                                answer = str(int(answer) // int(past_token))
                            que.get()
                        except (ValueError, ZeroDivisionError):
                            return "wrong"
                    first += 1
                else:
                    past_token = factor(token)
                    if past_token == "wrong":
                        return "wrong"
                    if first == 0:
                        if not answer:
                            answer = past_token
                        else:
                            return "wrong"
            token = ""

    if first != 0:
        try:
            if que.queue[0] == "*":
                answer = str(int(answer) * int(past_token))
            else:
                answer = str(int(answer) // int(past_token))
            que.get()
            if que.queue:
                return "wrong"
        except (ValueError, ZeroDivisionError):
            return "wrong"

    return answer


# aexpr 함수
def aexpr(array):
    array_count = 0
    first = 0
    answer = ""
    que = queue.Queue()
    for i in range(len(array)):
        if array[i] == '+' or array[i] == '-':
            new_array = array[array_count:i]
            term_result = term(new_array)
            if term_result == "wrong":
                return "wrong"
            if first == 0:
                answer = term_result
            if first != 0:
                try:
                    if que.queue[0] == '+':
                        answer = str(int(answer) + int(term_result))
                    elif que.queue[0] == '-':
                        term_val = int(term_result)
                        if term_val < 0:
                            return "wrong"
                        answer = str(int(answer) - term_val)
                    que.get()
                except ValueError:
                    return "wrong"
            que.put(array[i])
            first += 1
            array_count = i + 1

    new_array = array[array_count:]
    term_result = term(new_array)
    if term_result == "wrong":
        return "wrong"
    if not que.empty():
        try:
            if que.queue[0] == '+':
                answer = str(int(answer) + int(term_result))
            elif que.queue[0] == '-':
                term_val = int(term_result)
                if term_val < 0:
                    return "wrong"
                answer = str(int(answer) - term_val)
            que.get()
        except ValueError:
            return "wrong"
    if first == 0:
        try:
            term_val = int(term_result)
            if term_val < 0:
                return "wrong"
            answer = str(term_val)
        except ValueError:
            return "wrong"

    return answer


# relop 함수
def relop(array):
    if array in ["==", "!=", "<", ">", "<=", ">="]:
        return array
    else:
        return "wrong"


# bexpr 함수
def bexpr(array):
    token = ""
    number_count = 0
    number1 = 0
    number2 = 0
    logic = ""

    for char in array:
        if char != ' ':
            token += char
        else:
            if token:
                try:
                    if number_count == 0:
                        number1 = int(token)
                        number_count += 1
                    elif number_count == 1:
                        logic = relop(token)
                        number_count += 1
                    elif number_count == 2:
                        number2 = int(token)
                        number_count += 1
                except ValueError:
                    return "wrong"
            token = ""

    if token:
        return "wrong"

    if number_count != 3:
        return "wrong"

    if logic == "==":
        return "TRUE" if number1 == number2 else "FALSE"
    elif logic == "!=":
        return "TRUE" if number1 != number2 else "FALSE"
    elif logic == "<":
        return "TRUE" if number1 < number2 else "FALSE"
    elif logic == ">":
        return "TRUE" if number1 > number2 else "FALSE"
    elif logic == "<=":
        return "TRUE" if number1 <= number2 else "FALSE"
    elif logic == ">=":
        return "TRUE" if number1 >= number2 else "FALSE"
    else:
        return "wrong"


# expr 함수
def expr(new_array):
    bexpr_count = 0
    token = ""
    for char in new_array:
        if char != ' ':
            token += char
        else:
            if token:
                if token[0] in ['=', '!', '>', '<']:
                    bexpr_count += 1
                    break
            token = ""

    if bexpr_count == 0:
        return aexpr(new_array)
    else:
        return bexpr(new_array)


# statement 함수
def statement(array):
    global x, y, z
    variable = ''
    equal_count = 0
    print_count = 0

    if "print" not in array:
        buffer = ''
        variable_count = 0
        for char in array:
            if char == ' ':
                continue
            elif char == '=':
                try:
                    if array[array.index(char) -1] != ' ':
                        print("syntax error!!")
                        return 1
                    if array[array.index(char) + 1] != ' ':
                        print("syntax error!!")
                        return 1
                    if equal_count == 0:
                        equal_count += 1
                        new_array = array[array.index(char) + 2:]
                        try:
                            if buffer == 'x':
                                x = expr(new_array)
                                if x == "wrong":
                                    print("syntax error!!")
                                    return 1
                                return
                            elif buffer == 'y':
                                y = expr(new_array)
                                if y == "wrong":
                                    print("syntax error!!")
                                    return 1
                                return
                            elif buffer == 'z':
                                z = expr(new_array)
                                if z == "wrong":
                                    print("syntax error!!")
                                    return 1
                                return
                        except ValueError:
                            print("syntax error!!")
                            return 1
                    else:
                        print("syntax error!!")
                        return 1
                except IndexError:
                    print("syntax error!!")
                    return 1
            elif var(char) != 'q':
                if equal_count == 0:
                    if variable_count == 0:
                        buffer = var(char)
                        variable_count += 1
                    else:
                        print("syntax error!!")
                        return 1
                else:
                    print("syntax error!!")
                    return 1
            elif var(char) == 'q':
                print("syntax error!!")
                return 1

    if "print" in array:
        variable_count = 0
        for i in range(len(array)):
            if array[i] == ' ':
                continue
            elif array[i] == 'p':
                if array[i:i + 6] == "print ":
                    print_count += 1
                    if print_count != 1:
                        print("syntax error!!")
                        return 1
                    i += 6
                    while i < len(array):
                        if array[i] != ' ':
                            if variable_count == 0:
                                if var(array[i]) == 'q':
                                    print("syntax error!!")
                                    return 1
                                variable = var(array[i])
                            else:
                                print("syntax error!!")
                                return 1
                            variable_count += 1
                        elif array[i] == ';':
                            continue
                        i += 1
                    break
                else:
                    print("syntax error!!")
                    return 1
            else:
                print("syntax error!!")
                return 1
        if print_count == 1:
            if variable == '':
                print("syntax error!!")
                return
            elif variable == 'x':
                return x
            elif variable == 'y':
                return y
            elif variable == 'z':
                return z

    if equal_count == 0 and print_count == 0:
        print("syntax error!!")
        return 1


def program(array):
    index = 0
    count = 0
    que = []
    # 빈 문자열을 저장하기 위한 변수
    blank_array = ""

    # 문자열을 반복하면서 세미콜론이 있는지 확인
    for i in range(len(array)):
        if array[i] == ';':
            count += 1
            # 세미콜론이 나오면 그 전까지의 문자열을 expression으로 저장
            expression = array[index:i]
            # expression을 statement 함수에 전달하여 처리
            answer = statement(expression)
            if answer == 1:
                return
            index = i + 1
            blank_array = ""  # 빈 문자열 초기화
            if answer == 0:
                continue
            if (answer == x) or (answer == y) or (answer == z):
                que.append(answer)
        else:
            if array[i] != ' ':
                blank_array += array[i]

    # 빈 문자열이 아니라면 문법 오류 출력
    if blank_array:
        print("syntax error!!")
        return

    # 세미콜론이 없는 경우 문법 오류 출력
    if count == 0:
        print("syntax error!!")
        return

    # 결과 출력
    for item in que:
        print(item, end=" ")
    print()


# 메인 함수
def main():
    global x, y, z

    while True:
        input_string = input()

        if input_string == "terminate":
            print("Terminate program!")
            break
        elif not input_string:
            print("syntax error!!")
        else:
            x = "0"
            y = "0"
            z = "0"
            program(input_string)


if __name__ == "__main__":
    main()

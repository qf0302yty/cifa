class cifa:
    file_object = ''#文件句柄
    line_number = 0 #记录行号
    state = 0 #状态
    ResWord = ['int','if','then','else','printf','return','until','read','write','include','print'
               ,'break','continue','goto','float','double','const','class','define','for','open','while'
               ,'do','long','switch','case','void','elif','enum','extern','import','main','boolean','true','false']#保留字
    error_message = []#保存错误信息,存储元组,元组第一个参数是行号,第二个参数是错误字符
    char_message = []#识别的字符串,存储元组,元组第一个参数是类型,第二个参数是该字符串
    string = ''
    def __init__(self,file_name):
        self.file_object = file_name
        self.state = 0
        self.line_number = 0
        self.error_message = []
        self.annotate_message = []
        self.char_message = []
        self.string = ''
    def Start_convert(self):
        all_content = self.file_object.split('\n')
        for line in all_content:#一行行的处理
            # line = line.strip('\n')#去除换行fu
            self.line_number += 1#没处理一行行号加一
            line_length = len(line)
            i = 0
            # self.string = ''#存储一个字符串
            while i < line_length:
                ch = line[i]#读取该行的一个字符
                i += 1
                if self.state == 0:#初始状态
                    self.string = ch
                    if ch.isalpha() or ch == '_':
                        self.state = 1
                    elif ch.isdigit() and ch != '0':
                        self.state = 3
                    elif ch == '+':
                        self.state = 5
                    elif ch == '-':
                        self.state = 9
                    elif ch == '*':
                        self.state = 13
                    elif ch == '/':
                        self.state = 16
                    elif ch == '=':
                        self.state = 20
                    elif ch == '<':
                        self.state = 21
                        i -= 1
                    elif ch == '{':
                        self.state = 22
                        i -= 1
                    elif ch == '}':
                        self.state = 23
                        i -= 1
                    elif ch == ';':
                        i -= 1
                        self.state = 24
                    elif ch == '>':
                        self.state = 25
                        i -= 1
                    elif ch == '?':
                        i -= 1
                        self.state = 27
                    elif ch == '[':
                        i -= 1
                        self.state = 28
                    elif ch == ']':
                        i-= 1
                        self.state = 29
                    elif ch == '$':
                        i -= 1
                        self.state = 30
                    elif ch == '%':
                        i -= 1
                        self.state = 31
                    elif ch == '|':
                        i -= 1
                        self.state = 32
                    elif ch == '&':
                        i -= 1
                        self.state = 33
                    elif ch == '(':
                        i -= 1
                        self.state = 34
                    elif ch == ')':
                        i -= 1
                        self.state = 35
                    elif ch == '"':
                        self.state = 36
                    elif ch == ':':
                        i -= 1
                        self.state = 37
                    elif ch == '.':
                        i -= 1
                        self.state = 38
                    elif ch.isspace():
                        self.state = 46
                    elif ch == "'":
                        self.state = 47
                    elif ch == ',':
                        i -= 1
                        self.state = 49
                    elif ch == '!':
                        i -= 1
                        self.state = 50
                    elif ch == '#':
                        i -= 1
                        self.state = 51
                    elif ch == '0':
                        self.state = 55
                    else:
                        self.state = 60#不可识别状态
                        i -= 1
                elif self.state == 1:#判断字母数字
                    while ch.isalpha() or ch.isdigit() or ch == '_':
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    self.state = 2
                    i -= 2#回退2个字符
                elif self.state == 2:
                    if self.string in self.ResWord:
                        content = ['关键字',self.string]
                    else:
                        content = ['标识符',self.string]
                    #print content
                    self.char_message.append(content)
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 3:
                    while ch.isdigit():
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    if ch == 'E':
                        self.string += ch
                        self.state = 42
                    elif ch == '.':
                        self.string += ch
                        self.state = 40
                    else:
                        self.state = 4
                        i -= 2#回退2个字符
                elif self.state == 4:
                    content = ['十进制数',self.string]
                    self.char_message.append(content)
                    #print self.string
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 5:
                    if ch == '+':
                        self.state = 6
                        i -= 1
                    elif ch == '=':
                        self.state = 7
                        i -= 1
                    else:
                        self.state = 8
                        i -= 2
                elif self.state == 6:#判断++
                    content = ['算术运算符',self.string + ch]
                    self.char_message.append(content)
                    #print self.string + ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 7:#判断+=
                    content = ['算术运算符',self.string + ch]
                    self.char_message.append(content)
                    #print self.string + ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 8:#判断+
                    content = ['算术运算符',ch]
                    self.char_message.append(content)
                    #print ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 9:
                    if ch == '-':
                        self.state = 10
                        i -= 1
                    elif ch == '=':
                        self.state = 11
                        i -= 1
                    else:
                        self.state = 12
                        i -= 2
                elif self.state == 10:
                    content = ['算术运算符',self.string + ch]
                    self.char_message.append(content)
                    #print self.string + ch#判断--
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 11:#判断-=
                    content = ['算术运算符',self.string + ch]
                    self.char_message.append(content)
                    #print self.string + ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 12:#判断-
                    content = ['算术运算符',ch]
                    self.char_message.append(content)
                    #print ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 13:
                    if ch == '=':
                        self.state = 14
                        i -= 1
                    else:
                        self.state = 15
                        i -= 2
                elif self.state == 14:#判断*=
                    content = ['算术运算符',self.string + ch]
                    self.char_message.append(content)
                    #print self.string + ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 15:#判断*
                    content = ['算术运算符',ch]
                    self.char_message.append(content)
                    #print ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 16:
                    if ch == '/':
                        self.state = 17
                        i -= 1
                    elif ch == '=':
                        self.state = 18
                        i -= 1
                    elif ch =='*':
                        self.state = 26
                        i -= 1
                    else:
                        self.state = 19
                        i -= 2
                elif self.state == 17:#判断//
                    # content = ['特殊符号',self.string + ch]
                    # self.char_message.append(content)
                    self.string += ch
                    content = ['注释',self.string + line[i:]]
                    self.char_message.append(content)
                    self.string = ''  # 回到初始情况
                    self.state = 0  # 回到状态0
                    break
                    #print content
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 18:#判断/=
                    content = ['特殊符号',self.string + ch]
                    self.char_message.append(content)
                    #print self.string + ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 19:#判断/
                    content = ['特殊符号',ch]
                    self.char_message.append(content)
                    #print ch
                    self.string = ''#回到初始情况
                    self.state = 0#回到状态0
                elif self.state == 20:
                    if ch == '=':
                        self.state = 53
                        i -= 1
                    else:
                        self.state = 54
                        i -= 2
                elif self.state == 21:
                    content = ['算术运算符','<']
                    self.char_message.append(content)
                    #print '<'
                    self.state = 0
                    self.string = ''
                elif self.state == 22:
                    content = ['界符','{']
                    self.char_message.append(content)
                    #print '{'
                    self.state = 0
                    self.string = ''
                elif self.state == 23:
                    content = ['界符','}']
                    self.char_message.append(content)
                    #print '}'
                    self.state = 0
                    self.string = ''
                elif self.state == 24:
                    content = ['界符',';']
                    self.char_message.append(content)
                    #print ';'
                    self.state = 0
                    self.string = ''
                elif self.state == 25:
                    content = ['算数运算符', '>']
                    self.char_message.append(content)
                    # print '>'
                    self.state = 0
                    self.string = ''
                elif self.state == 26:
                    while ch != "*":
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    if ch == '*':
                        self.string += ch
                        self.state = 39
                    if ch == all_content[-1]:
                        content = ['注释', self.string]
                        # print content
                        self.char_message.append(content)
                        self.string = ''  # 回到初始情况
                        self.state = 0  # 回到状态0
                elif self.state == 27:
                    content = ['特殊符号', '?']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 28:
                    content = ['界符', '[']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 29:
                    content = ['界符', ']']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 30:
                    content = ['特殊符号', '$']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 31:
                    content = ['算术运算符', '%']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 32:
                    content = ['逻辑运算符', '|']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 33:
                    content = ['逻辑运算符', '&']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 34:
                    content = ['界符', '(']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 35:
                    content = ['界符', ')']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 36:
                    while ch != '"':
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    self.string += ch
                    self.state = 45
                    i -= 1
                elif self.state == 37:
                    content = ['特殊符号', ':']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 38:
                    content = ['特殊符号', '.']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 39:
                    while ch == "*":
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    if ch == '/':
                        self.string += ch
                        self.state = 52
                        i -= 1
                    else:
                        self.string += ch
                        self.state = 26
                elif self.state == 40:
                    if ch.isdigit():
                        self.string += ch
                        self.state = 41
                    else:
                        self.string = self.string[:-1]
                        i -= 2  # 回退3个字符(退掉.)
                elif self.state == 41:
                    while ch.isdigit():
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    if ch == 'E':
                        self.string += ch
                        self.state = 42
                    else:
                        self.state = 4
                        i -= 2  # 回退2个字符
                elif self.state == 42:
                    if ch == '+' or ch == '-':
                        self.string += ch
                        self.state = 43
                    elif ch.isdigit():
                        self.string += ch
                        self.state = 44
                    else:
                        self.state = 4
                        self.string = self.string[:-1]
                        i -= 3  # 回退3个字符(退掉E)
                elif self.state == 43:
                    if ch.isdigit():
                        self.string += ch
                        self.state = 44
                    else:
                        self.state = 4
                        self.string = self.string[:-2]
                        i -= 4  # 回退3个字符(退掉+/-,E)
                elif self.state == 44:
                    while ch.isdigit():
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    self.state = 4
                    i -= 2  # 回退2个字符
                elif self.state == 45:
                    content = ['字符常数', self.string]
                    # print content
                    self.char_message.append(content)
                    self.string = ''  # 回到初始情况
                    self.state = 0  # 回到状态0
                elif self.state == 46:
                    while ch.isspace():
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    self.state = 0
                    i -= 1
                elif self.state == 47:
                    while ch != "'":
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    self.string += ch
                    self.state = 48
                    i -= 1
                elif self.state == 48:
                    content = ['字符常数', self.string]
                    # print content
                    self.char_message.append(content)
                    self.string = ''  # 回到初始情况
                    self.state = 0  # 回到状态0
                elif self.state == 49:
                    content = ['特殊符号', ',']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 50:
                    content = ['逻辑运算符', '!']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 51:
                    content = ['特殊符号', '#']
                    self.char_message.append(content)
                    self.state = 0
                    self.string = ''
                elif self.state == 52:
                    content = ['注释', self.string]
                    # print content
                    self.char_message.append(content)
                    self.string = ''  # 回到初始情况
                    self.state = 0  # 回到状态0
                elif self.state == 53:
                    content = ['逻辑运算符', self.string + ch]
                    self.char_message.append(content)
                    # print '='
                    self.state = 0
                    self.string = ''
                elif self.state == 54:
                    content = ['算数运算符', '=']
                    self.char_message.append(content)
                    # print '='
                    self.state = 0
                    self.string = ''
                elif self.state == 55:
                    if ch.isdigit() and ch != '0':
                        self.string += ch
                        self.state = 56
                    elif ch == 'x':
                        self.string += ch
                        self.state = 57
                    elif ch == '.':
                        self.string += ch
                        self.state = 40
                    else:
                        self.state = 4
                        i -= 2
                elif self.state == 56:
                    while ch.isdigit():
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    self.state = 58
                    i -= 2  # 回退2个字符
                elif self.state == 57:
                    while ch.isdigit():
                        self.string += ch
                        if i < line_length:
                            ch = line[i]
                            i += 1
                        else:
                            break
                    self.state = 59
                    i -= 2  # 回退2个字符
                elif self.state == 58:
                    content = ['八进制数', self.string]
                    self.char_message.append(content)
                    # print self.string
                    self.string = ''  # 回到初始情况
                    self.state = 0  # 回到状态0
                elif self.state == 59:
                    content = ['十六进制数', self.string]
                    self.char_message.append(content)
                    # print self.string
                    self.string = ''  # 回到初始情况
                    self.state = 0  # 回到状态0
                elif self.state == 60:
                    content = ['行号:'+str(self.line_number),ch]
                    self.error_message.append(content)
                    #print 'error:' + ch
                    self.state = 0
                    self.string = ''
        #print self.state
    def Get_error(self):#获取错误信息
        return self.error_message

    def Get_char(self):#获取识别信息
        return self.char_message
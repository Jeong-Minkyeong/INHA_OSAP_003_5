#ifndef RULE_OF_THREE_H
#define RULE_OF_THREE_H

//복사 생성자와 대입 연산자 모두 필요없으므로 사용불가 처리
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete;    \
    TypeName& operator=(const TypeName&) = delete;

#endif 

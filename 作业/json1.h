#ifndef JSON_H__
#define JSON_H__

typedef enum
{
    JSON_NULL,        //0
    JSON_FALSE,       //1
    JSON_TRUE        //2
} json_type;

typedef struct
{
    json_type type;
} json_value;             //json对象

enum
{
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,//只包含空白
    JSON_PARSE_INVALID_VALUE,//不是其他字面值
    JSON_PARSE_ROOT_NOT_SINGULAR//空白之后还有其他字符
};

int json_parse(json_value *v, const char *json);//解析json,返回值为上述枚举值，无措返回JSON_PARSE_OK

json_type json_get_type(const json_value *v);

#endif /* JSON_H__ */
#include "json1.h"
#include <assert.h> /* assert() */
#include <stdlib.h> /* NULL */

#define EXPECT(c,ch)                                                            \
    do                                                                          \
    {                                                                           \
          assert(*c->json==(ch));                                               \
          c->json++;                                                            \
                                                                                \
                                                                                \
    } while (0)

typedef struct
{
    const char *json;
} json_context;

static void json_parse_whitespace(json_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;  //为空，返回c为\0，不是，返回c变为该指针
}
/* null  = "null" */
static int json_parse_null(json_context *c, json_value *v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
    {
        return JSON_PARSE_INVALID_VALUE;   //字符串不是null，不属于其他字面值
    }


    c->json += 3;//指针移动到后边
    if(c->json[0]==' '&&(c->json[1]>0&&c->json[1]<128))
        return JSON_PARSE_ROOT_NOT_SINGULAR;        //在值之后，空格之后还有其他字符，输出JSON_PARSE_ROOT_NOT_SINGULAR

    v->type = JSON_NULL;                    //获得处理类型
    return JSON_PARSE_OK;
}
static int json_prase_bool(json_context *c,json_value *v)
{
    if(c->json[0]=='t')
    {
        EXPECT(c,'t');
        if(c->json[0]!='r'||c->json[1]!='u'||c->json[2]!='e');
        return JSON_PARSE_INVALID_VALUE;       //不属于另外的字面值

        c->json+=3;
        if(c->json[0]==' '&&(c->json[1]>0&&c->json[1]<128))
        return JSON_PARSE_ROOT_NOT_SINGULAR;

        v->type = JSON_TRUE;
        return JSON_PARSE_OK;
    }

    if(c->json[0] == 'f')
    {
        EXPECT(c,'f');
        if(c->json[0]!='a'||c->json[1]!='l'||c->json[2]!='s'||c->json[3] != 'e')
        return JSON_PARSE_INVALID_VALUE;

        c->json+=3;
        if(c->json[0]==' '&&(c->json[1]>=0&&c->json[1]<128))
        return JSON_PARSE_ROOT_NOT_SINGULAR;        //

        v->type = JSON_FALSE;
        return JSON_PARSE_OK;
    }
}
/* value = null / false / true */
/* 提示：下面代码没处理 false / true，将会是练习之一 */
static int json_parse_value(json_context *c, json_value *v)
{
    switch (*c->json)
    {
    case 'n':                              //解析字符串中是否存在null
        return json_parse_null(c, v);
    case '\0':
        return JSON_PARSE_EXPECT_VALUE;  //空，返回该值
    case 't':                               //解析true
        return json_prase_bool(c,v);
    case 'f':                              //解析false
        return json_prase_bool(c,v);
    default:
        return JSON_PARSE_INVALID_VALUE;
    }
}

/* 以下实现没处理最后的 空白符 和 JSON_PARSE_ROOT_NOT_SINGULAR */
int json_parse(json_value *v, const char *json)
{
    json_context c;
    assert(v != NULL);         //确保v不是NULL
    c.json = json;              //获得json，并代替其去判断，改变
    v->type = JSON_NULL;
    json_parse_whitespace(&c);       //为空，返回c为\0，不是，返回c变为该指针
    return json_parse_value(&c, v);   //根据不同的结果返回不同的值
}

json_type json_get_type(const json_value *v)//（判断是否存在json，并得到）如果输入的json存在，返回json
{
    assert(v != NULL);
    return v->type;
}

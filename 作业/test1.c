#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                                                           \
    do                                                                                                             \
    {                                                                                                              \
        test_count++;                                                                                              \
        if (equality)                                                                                              \
            test_pass++;                                                                                           \
        else                                                                                                       \
        {                                                                                                          \
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
            main_ret = 1;                                                                                          \
        }                                                                                                          \
    } while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

static void test_parse_null()  //需要修改，令第二个EXPECT_EQ_INT通过
{
    json_value v;
    v.type = JSON_FALSE;           //初始化是false
    EXPECT_EQ_INT(JSON_PARSE_OK, json_parse(&v, "null"));//是null则返回null独属字面值，但是不符合期望，不是则返回..ok，符合期望
    EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));         //不是null时，符合期望，不会报错，是null时，报错
}

static void test_parse_expect_value()//判断是否只包含空白
{
    json_value v;

    v.type = JSON_FALSE;
    EXPECT_EQ_INT(JSON_PARSE_EXPECT_VALUE, json_parse(&v, ""));
    EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));

    v.type = JSON_FALSE;
    EXPECT_EQ_INT(JSON_PARSE_EXPECT_VALUE, json_parse(&v, " "));
    EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));
}

static void test_parse_invalid_value()//测试是否不是这三种字面值
{
    json_value v;
    v.type = JSON_FALSE;
    EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, json_parse(&v, "nul"));    //
    EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));

    v.type = JSON_FALSE;
    EXPECT_EQ_INT(JSON_PARSE_INVALID_VALUE, json_parse(&v, "?"));
    EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));
}

static void test_parse_root_not_singular()//要做的地方，修正这个函数，（函数用来判断空白之后是否还有其他字符）
{
    json_value v;
    v.type = JSON_FALSE;//确保用json_parse时v初始值，不会报错
    EXPECT_EQ_INT(JSON_PARSE_OK, json_parse(&v, "null x"));//判断是否有null(可能要修改json_parse)
    EXPECT_EQ_INT(JSON_NULL, json_get_type(&v));
}
//添加的测试true类型的函数
static void test_prase_true()
{
    json_value v;
    v.type = JSON_FALSE;
    EXPECT_EQ_INT(JSON_PASE_OK,json_prase(&v,"true"));
    EXPECT_EQ_INT(JSON_TRUE,json_get_type(&v));
}
//添加的测试false类型的函数
static void test_prase_flase()
{
    json_value v;
    v.type = JSON_TRUE;
    EXPECT_EQ_INT(JSON_PASE_OK,json_prase(&v,"false"));
    EXPECT_EQ_INT(JSON_FALSE,json_get_type(&v));
}
static void test_parse()
{
    test_parse_null();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main()
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count); 
    
    return main_ret;
}
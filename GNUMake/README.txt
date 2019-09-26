 GNUmake 的一些语法 
 eg:
    下面的例子，判断$(CC)变量是否是“gcc”, 如果是的话, 则使用GNU函数编译目标

    objects = xxx.o yyy.o
    libs_for_gcc = -lgnu
    normal_libs = 

    foo:$(objects)
    ifeq($(CC), gcc)
        $(CC) -o foo $(objects) $(libs_for_gcc)    //$(CC) = gcc 执行这条
    else
        $(CC) -o foo $(objects) $(normal_libs)
    endif

    参数中我们还可以make函数
        ifeq($(strip &(foo)),)
        strip 函数，如果这个函数返回值是空(empty)，执行语句生效
    相同类似语法还有
    ifneq
    如果两个参数不同为真
    ifdef
    判断变量或者函数返回值是否有值， 有值表达式为真
    ifndef 
    与ifdef相反，没有值为真

    nate:特别注意的是，make是在读取Makefile时就计算条件表达式的值，并根据条件表达式的值来选择语句，所以，你最好不要
    把自动化变量（如“$@”等）放入条件表达式中，因为自动化变量是在运行时才有的

eg:
    make中经长会出现 :$(objects):%.o:%.c  、$<之类的变量
    
    objects = foo.o bar.o
    all:$(objects)
    $(objects):%.o:%c
        $(cc) -c $(CFLAGS) $< -o $@
    上面的例子中，指明目标 objects 中获取，%o 表示所有 .o 结尾的文件为目标，
    %c 表示所有.c 结尾的为依赖，$< 和 $@ 是自动变量， $< 为所有的依赖
    $@ 为所有的目标 

    wildcard函数
    当变量的定义和函数使用时，通配符将失效，这种情况下我们用这个函数
    eg" $(patsubst %.c, %.o, $(wildcard *.c))"
    patsubst函数
    替换应用
    eg: foo:a.o b.o c.o
        bar:$(foo:.o=.c)
    ontdir函数
    去除路径
    eg:  src=$(wildcard *.c ./sub/*.c)
         dir=$(notdir $(src))
         obj=$(patsubs %.c, %.o, $(dir))

         第一行输出 a.c b.c ./sub/sa.c ./sub/sb.c
         第二行输出 a.c b.c sa.c sb.c
         第三行输出 a.o b.o sa.o sb.o
    -include filename
    这种指令的作用就是对任何不存在的makefile 文件都不产生错误
    (即使警告也不产生) 如果希望和其他版本的make 兼容使用这个函数
    sinclude 代替 -include

    addprefix函数
    该addprefix就是用于添加前缀的
    suffix函数
    取后缀函数——suffix
    basename函数
    取前缀函数
    加后缀函数——addsuffix
    示例：$(addsuffix .c,foo bar)返回值是“foo.c bar.c”
    加前缀函数——addprefix
    $(addprefix src/,foo bar)返回值是“src/foo src/bar”
    连接函数——join
    示例：$(join aaa bbb , 111 222 333)返回值是“aaa111 bbb222 333”

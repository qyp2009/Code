static int val_a = 1; // 初始化的静态变量
int val_b = 2;        // 全局变量
const int val_c = 3;  // const 全局变量
static int val_d;     // 未初始化的静态变量
int val_e;            // 未初始化的全局变量
int main(int argc, char *argv[])
{
    static int val_f = 5;  // 初始化的局部静态变量
    static int val_g;      //未初始化局部静态变量
    int    val_h = 6;      //初始化局部变量
    int    val_i;          //未初始化局部变量
    const  int val_j = 7;  //const局部变量
    return 0;
}

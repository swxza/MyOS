// 这里给显存地址(0xb8000)写数据即可
void printf(char* str){
    static unsigned short* VideoMemory=(unsigned short*)0xb8000;
    for(int i=0; str[i]!='\0';++i){
        VideoMemory[i]=(VideoMemory[i] & 0xFF00)|str[i];
    }
}

//操作系统构造函数委托方法
typedef void(*constructor)();
//全局定义构造委托
constructor start_ctors;
//全局定义析构委托
constructor end_ctors;

//轮询函数，并且执行
extern "C" void system_constructors(){
	for(constructor* i= &start_ctors; i != &end_ctors; i++){
		(*i)();
	}
}


// warning: ISO C++11 does not allow conversion from string literal to 'char *' [-Wwritable-strings]
// 这是由于下面定义方法是C, 使用extern "C" 表示是C语言
// void kernelMain(void * multiboot_structure, unsigned int magicnumber){
extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber){ 
    printf((char*)"Hello World");
    while(1);
}

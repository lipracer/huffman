<html>
# huffman
根目录下为测试文件 文本文件与二进制文件，测试通过，可以完全还原文件

./huffman -c 输入文件 输出文件
./huffman -u 输出文件 输入文件

huffman实现：
原理：
字符频率排序使用二叉堆（非stl make_heap）
还未实现对大文件支持，目前只是单次申请大内存
</html>

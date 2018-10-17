<html>
# huffman  </br>
1. 根目录下为测试文件 文本文件与二进制文件，测试通过，可以完全还原文件  </br>


2. 命令：  </br>
编码：./huffman -c 输入文件 输出文件  </br>
解码：./huffman -u 输出文件 输入文件  </br>

huffman实现：  </br>
原理： </br>
1. 字符频率排序使用二叉堆（非stl make_heap） </br>
2. 还未实现对大文件支持，目前只是单次申请大内存  </br>
</html>

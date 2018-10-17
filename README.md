<html>
# huffman  </br>
根目录下为测试文件 文本文件与二进制文件，测试通过，可以完全还原文件  </br>

./huffman -c 输入文件 输出文件  </br>
./huffman -u 输出文件 输入文件  </br>

huffman实现：  </br>
原理： </br>
字符频率排序使用二叉堆（非stl make_heap） </br>
还未实现对大文件支持，目前只是单次申请大内存  </br>
</html>

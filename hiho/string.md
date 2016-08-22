关于字符串的算法
- 字符串匹配问题
  各种算法本质上都是FSM
  
  拿正则表达式来说，首先parse regex，生成一个DFA/NFA，然后对NFA/DFA进行模拟。
  
  一个DFA是每个状态的出边只对应一个符号，到达确定的下一状态
  
  NFA则不是，一个符号对应的出边可以到达多个状态。
  
  一个NFA可以通过 e-closure 算法转换成接受相同语言的 DFA。对NFA进行模拟时间效率较低，为O(MN),DFA则为O（M）
  ，但是DFA对一些正则式产生的的状态数会成指数增长。而且DFA支持的feature不如NFA多，大多数需要capture，回溯等功能的regex
  都采用NFA实现。

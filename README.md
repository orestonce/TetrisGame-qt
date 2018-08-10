# TetrisGame-qt
QT版俄罗斯方块

## 简介 ：
1. 程序分为QT-GUI和CORE部分。
2. 采用观察者模式，core通过notify调用Observer的onSubjectChanged通知GUI变化，而不用GUI每次主动检测core的变更。
3. core只使用了c++标准库函数，可以轻松移植到任何支持c++11的平台上。

## 一些截图
![游戏进行中](https://github.com/orestonce/TetrisGame-qt/blob/master/snapshot/TetrisGame-qt.png)

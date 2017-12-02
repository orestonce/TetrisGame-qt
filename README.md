# TetrisGame-qt
QT版俄罗斯方块

## 简介 ：
1. 程序分为QT-GUI和CORE部分。
2. 采用观察者模式，core通过notify调用Observer的onSubjectChanged通知GUI变化，而不用GUI每次主动检测core的变更。

## 一些截图
![游戏进行中](https://github.com/orestonce/TetrisGame-qt/blob/master/snapshot/TetrisGame-qt.png)
